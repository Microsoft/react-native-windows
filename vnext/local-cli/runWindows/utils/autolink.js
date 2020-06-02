/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 * @format
 */
// @ts-check

const execSync = require('child_process').execSync;
const fs = require('fs');
const path = require('path');
const chalk = require('chalk');

const {newSpinner} = require('./commandWithProgress');
const vstools = require('./vstools');

function verboseMessage(message, verbose) {
  if (verbose) {
    console.log(message);
  }
}

function updateFile(filePath, expectedContents, verbose, checkMode) {
  const fileName = chalk.bold(path.basename(filePath));
  verboseMessage(`Reading ${fileName}...`, verbose);
  const actualContents = fs.existsSync(filePath)
    ? fs
        .readFileSync(filePath)
        .toString()
        .replace(/\r\n/g, '\n')
    : '';

  const contentsChanged = expectedContents !== actualContents;

  if (contentsChanged) {
    verboseMessage(chalk.yellow(`${fileName} needs to be updated.`), verbose);
    if (!checkMode) {
      verboseMessage(`Writing ${fileName}...`, verbose);
      fs.writeFileSync(filePath, expectedContents.replace(/\n/g, '\r\n'), {
        encoding: 'utf8',
        flag: 'w',
      });
    }
  } else {
    verboseMessage(`No changes to ${fileName}.`, verbose);
  }

  return contentsChanged;
}

function exitProcessWithStatusCode(statusCode, loggingWasEnabled) {
  if (!loggingWasEnabled && statusCode !== 0) {
    console.log(
      `Error: Re-run the command with ${chalk.bold(
        '--logging',
      )} for more information.`,
    );
  }
  process.exit(statusCode);
}

async function updateAutoLink(config, args, options) {
  const verbose = options.logging;

  const checkMode = options.check;

  var changesNecessary = false;

  const spinner = newSpinner(
    checkMode ? 'Checking auto-linked files...' : 'Auto-linking...',
  );

  verboseMessage('', verbose);

  const execString = 'react-native config';
  let output;
  try {
    verboseMessage(`Running ${chalk.bold('react-native config')}...`, verbose);

    output = execSync(execString).toString();

    verboseMessage(output, verbose);

    verboseMessage('Parsing output...', verbose);

    const rnConfig = JSON.parse(output);
    const windowsAppConfig = rnConfig.project.windows;

    if (!windowsAppConfig) {
      throw 'Windows auto-link only supported on windows app projects.';
    }

    verboseMessage('Found Windows app project, parsing...', verbose);

    const solutionFile = path.join(
      windowsAppConfig.folder,
      windowsAppConfig.sourceDir,
      windowsAppConfig.solutionFile,
    );

    const projectFile = path.join(
      windowsAppConfig.folder,
      windowsAppConfig.sourceDir,
      windowsAppConfig.project.projectFile,
    );

    const projectDir = path.dirname(projectFile);
    const projectLang = windowsAppConfig.project.projectLang;

    verboseMessage('Parsing dependencies...', verbose);

    const dependencies = rnConfig.dependencies;

    let windowsDependencies = {};

    for (const dependencyName in dependencies) {
      const windowsDependency = dependencies[dependencyName].platforms.windows;

      if (windowsDependency) {
        verboseMessage(
          `Found dependency ${chalk.bold(dependencyName)}.`,
          verbose,
        );
        windowsDependencies[dependencyName] = windowsDependency;
      }
    }

    // Generating cs/h files for app code consumption
    if (projectLang === 'cs') {
      let csUsingNamespaces = '';
      let csReactPacakgeProviders = '';

      for (const dependencyName in windowsDependencies) {
        windowsDependencies[dependencyName].projects.forEach(project => {
          if (project.directDependency) {
            csUsingNamespaces += `\n\n// Namespaces from ${dependencyName}`;
            project.csNamespaces.forEach(namespace => {
              csUsingNamespaces += `\nusing ${namespace};`;
            });

            csReactPacakgeProviders += `\n            // IReactPackageProviders from ${dependencyName}`;
            project.csPackageProviders.forEach(packageProvider => {
              csReactPacakgeProviders += `\n            packageProviders.Add(new ${packageProvider}());`;
            });
          }
        });
      }

      const csFile = path.join(projectDir, 'AutolinkedNativeModules.g.cs');

      verboseMessage(
        `Calculating ${chalk.bold(path.basename(csFile))}...`,
        verbose,
      );

      const csContents = `// AutolinkedNativeModules.g.cs contents generated by "react-native autolink-windows"

using System.Collections.Generic;${csUsingNamespaces}

namespace Microsoft.ReactNative.Managed
{
    internal static class AutolinkedNativeModules
    {
        internal static void RegisterAutolinkedNativeModulePackages(IList<IReactPackageProvider> packageProviders)
        {${csReactPacakgeProviders}
        }
    }
}
`;

      changesNecessary =
        updateFile(csFile, '\uFEFF' + csContents, verbose, checkMode) ||
        changesNecessary;
    } else if (projectLang === 'cpp') {
      let cppIncludes = '';
      let cppPackageProviders = '';

      for (const dependencyName in windowsDependencies) {
        windowsDependencies[dependencyName].projects.forEach(project => {
          if (project.directDependency) {
            cppIncludes += `\n\n// Includes from ${dependencyName}`;
            project.cppHeaders.forEach(header => {
              cppIncludes += `\n#include <${header}>`;
            });

            cppPackageProviders += `\n    // IReactPackageProviders from ${dependencyName}`;
            project.cppPackageProviders.forEach(packageProvider => {
              cppPackageProviders += `\n    packageProviders.Append(winrt::${packageProvider}());`;
            });
          }
        });
      }

      const cppFile = path.join(projectDir, 'AutolinkedNativeModules.g.cpp');

      verboseMessage(
        `Calculating ${chalk.bold(path.basename(cppFile))}...`,
        verbose,
      );

      const cppContents = `// AutolinkedNativeModules.g.cpp contents generated by "react-native autolink-windows"
#include "pch.h"
#include "AutolinkedNativeModules.g.h"${cppIncludes}

// clang-format off
namespace winrt::Microsoft::ReactNative
{

void RegisterAutolinkedNativeModulePackages(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::ReactNative::IReactPackageProvider> const& packageProviders)
{${cppPackageProviders}
}

}
`;

      changesNecessary =
        updateFile(cppFile, cppContents, verbose, checkMode) ||
        changesNecessary;
    }

    // Generating targets for app project consumption
    let projectReferencesForTargets = '';

    for (const dependencyName in windowsDependencies) {
      windowsDependencies[dependencyName].projects.forEach(project => {
        if (project.directDependency) {
          const dependencyProjectFile = path.join(
            windowsDependencies[dependencyName].folder,
            windowsDependencies[dependencyName].sourceDir,
            project.projectFile,
          );

          const relDependencyProjectFile = path.relative(
            projectDir,
            dependencyProjectFile,
          );

          projectReferencesForTargets += `\n    <!-- Projects from ${dependencyName} -->`;
          projectReferencesForTargets += `\n    <ProjectReference Include="$(ProjectDir)${relDependencyProjectFile}">
      <Project>${project.projectGuid}</Project>
    </ProjectReference>`;
        }
      });
    }

    const targetFile = path.join(
      projectDir,
      'AutolinkedNativeModules.g.targets',
    );

    verboseMessage(
      `Calculating ${chalk.bold(path.basename(targetFile))}...`,
      verbose,
    );

    const targetContents = `<?xml version="1.0" encoding="utf-8"?>
<Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <!-- AutolinkedNativeModules.g.targets contents generated by "react-native autolink-windows" -->
  <ItemGroup>${projectReferencesForTargets}
  </ItemGroup>
</Project>
`;

    changesNecessary =
      updateFile(targetFile, targetContents, verbose, checkMode) ||
      changesNecessary;

    // Generating project entries for solution
    let projectsForSolution = [];

    for (const dependencyName in windowsDependencies) {
      // Process projects
      windowsDependencies[dependencyName].projects.forEach(project => {
        const dependencyProjectFile = path.join(
          windowsDependencies[dependencyName].folder,
          windowsDependencies[dependencyName].sourceDir,
          project.projectFile,
        );

        projectsForSolution.push({
          projectFile: dependencyProjectFile,
          projectName: project.projectName,
          projectLang: project.projectLang,
          projectGuid: project.projectGuid,
        });
      });
    }

    verboseMessage(
      `Calculating ${chalk.bold(path.basename(solutionFile))} changes...`,
      verbose,
    );

    projectsForSolution.forEach(project => {
      const contentsChanged = vstools.addProjectToSolution(
        solutionFile,
        project,
        verbose,
        checkMode,
      );
      changesNecessary = changesNecessary || contentsChanged;
    });

    spinner.succeed();

    if (!changesNecessary) {
      console.log(
        `${chalk.green('Success:')} No auto-linking changes necessary.`,
      );
    } else if (checkMode) {
      console.log(
        `${chalk.yellow(
          'Warning:',
        )} Auto-linking changes were necessary but ${chalk.bold(
          '--check',
        )} specified. Run ${chalk.bold(
          "'npx react-native autolink-windows'",
        )} to apply the changes.`,
      );
      exitProcessWithStatusCode(0, verbose);
    } else {
      console.log(`${chalk.green('Success:')} Auto-linking changes completed.`);
    }
  } catch (e) {
    spinner.fail();
    console.log(chalk.red('Error:') + ' ' + e.toString());
    exitProcessWithStatusCode(1, verbose);
  }
}

module.exports = {
  name: 'autolink-windows',
  description: 'performs autolinking',
  func: updateAutoLink,
  options: [
    {
      command: '--logging',
      description: 'Verbose output logging',
      default: false,
    },
    {
      command: '--check',
      description: 'Only check whether any autolinked files need to change',
      default: false,
    },
  ],
};
