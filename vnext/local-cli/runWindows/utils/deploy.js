/**
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 * @format
 */
// @ts-check
'use strict';

const {spawn, execSync} = require('child_process');
const fs = require('fs');
const http = require('http');
const path = require('path');
const glob = require('glob');
const parse = require('xml-parser');
const WinAppDeployTool = require('./winappdeploytool');
const {
  newInfo,
  newSuccess,
  newError,
  newWarn,
  newSpinner,
  commandWithProgress,
  runPowerShellScriptFunction,
} = require('./commandWithProgress');

function pushd(pathArg) {
  const cwd = process.cwd();
  process.chdir(pathArg);
  return () => process.chdir(cwd);
}

function getBuildConfiguration(options) {
  return (
    (options.release ? 'Release' : 'Debug') + (options.bundle ? 'Bundle' : '')
  );
}

function shouldLaunchApp(options) {
  return options.launch;
}

function getAppPackage(options) {
  const configuration = getBuildConfiguration(options);
  const packageFolder =
    options.arch === 'x86'
      ? `{*_x86_${configuration}_*,*_Win32_${configuration}_*}`
      : `*_${options.arch}_${configuration}_*`;
  const appPackageGlob = `windows/{*/AppPackages,AppPackages/*}/${packageFolder}`;
  let appPackage = glob.sync(appPackageGlob)[0];

  if (!appPackage && options.release) {
    // in the latest vs, Release is removed
    newWarn(
      'No package found in *_Release_* folder, remove _Release_ and check again',
    );
    appPackage = glob.sync(
      `windows/{*/AppPackages,AppPackages/*}/*_${options.arch}_*`,
    )[0];
  }

  if (!appPackage) {
    throw new Error(
      `Unable to find app package using search path: "${appPackageGlob}"`,
    );
  }
  return appPackage;
}

function getWindowsStoreAppUtils(options) {
  const popd = pushd(options.root);
  const windowsStoreAppUtilsPath = path.resolve(
    __dirname,
    'WindowsStoreAppUtils.ps1',
  );
  execSync(`powershell Unblock-File "${windowsStoreAppUtilsPath}"`);
  popd();
  return windowsStoreAppUtilsPath;
}

function getAppxManifest(options) {
  const configuration = getBuildConfiguration(options);
  const appxManifestGlob = `windows/{*/bin/${
    options.arch
  }/${configuration},${configuration}/*}/AppxManifest.xml`;
  const appxPath = glob.sync(path.join(options.root, appxManifestGlob))[0];

  if (!appxPath) {
    throw new Error(
      `Unable to find AppxManifest from "${
        options.root
      }", using search path: "${appxManifestGlob}" `,
    );
  }
  return parse(fs.readFileSync(appxPath, 'utf8'));
}

function handleResponseError(e) {
  if (e.message.indexOf('Error code -2146233088')) {
    throw new Error(`No Windows Mobile device was detected: ${e.message}`);
  } else {
    throw new Error(`Unexpected error deploying app: ${e.message}`);
  }
}

// Errors: 0x80073d10 - bad architecture
async function deployToDevice(options, verbose) {
  const appPackageFolder = getAppPackage(options);

  const deployTarget = options.target
    ? options.target
    : options.emulator
    ? 'emulator'
    : 'device';
  const deployTool = new WinAppDeployTool();
  const appxManifest = getAppxManifest(options);
  const shouldLaunch = shouldLaunchApp(options);
  const identity = appxManifest.root.children.filter(function(x) {
    return x.name === 'mp:PhoneIdentity';
  })[0];
  const appName = identity.attributes.PhoneProductId;

  const device = deployTool.findDevice(deployTarget);

  try {
    await deployTool.uninstallAppPackage(appName, device, verbose);
  } catch (e) {
    newWarn('Failed to uninstall app from ' + device.name);
  }

  const appxFile = glob.sync(path.join(appPackageFolder, '*.appx'))[0];
  try {
    await deployTool.installAppPackage(
      appxFile,
      device,
      shouldLaunch,
      false,
      verbose,
    );
  } catch (e) {
    if (e.message.indexOf('Error code 2148734208 for command') !== -1) {
      await deployTool.installAppPackage(
        appxFile,
        device,
        shouldLaunch,
        true,
        verbose,
      );
    } else {
      handleResponseError(e);
    }
  }
}

async function deployToDesktop(options, verbose) {
  const appPackageFolder = getAppPackage(options);
  const windowsStoreAppUtils = getWindowsStoreAppUtils(options);
  const appxManifest = getAppxManifest(options);
  const identity = appxManifest.root.children.filter(function(x) {
    return x.name === 'Identity';
  })[0];
  const appName = identity.attributes.Name;
  const script = glob.sync(
    path.join(appPackageFolder, 'Add-AppDevPackage.ps1'),
  )[0];

  const args = ['remoteDebugging', options.proxy ? 'true' : 'false'];

  const popd = pushd(options.root);

  await runPowerShellScriptFunction(
    'Removing old version of the app',
    windowsStoreAppUtils,
    `Uninstall-App ${appName}`,
    verbose,
  );

  await runPowerShellScriptFunction(
    'Enabling Developer Mode',
    windowsStoreAppUtils,
    `EnableDevMode "${script}"`,
    verbose,
  );

  await runPowerShellScriptFunction(
    'Installing new version of the app',
    windowsStoreAppUtils,
    `Install-App "${script}" -Force`,
    verbose,
  );

  const appFamilyName = execSync(
    `powershell -c $(Get-AppxPackage -Name ${appName}).PackageFamilyName`,
  )
    .toString()
    .trim();

  if (!appFamilyName) {
    throw new Error(
      'Fail to check the installed app, maybe developer mode is off on Windows',
    );
  }

  const loopbackText = 'Verifying loopbackExempt';
  const loopbackSpinner = newSpinner(loopbackText);

  await commandWithProgress(
    loopbackSpinner,
    loopbackText,
    'CheckNetIsolation',
    `LoopbackExempt -a -n=${appFamilyName}`.split(' '),
    verbose,
  );

  if (shouldLaunchApp(options)) {
    await runPowerShellScriptFunction(
      'Starting the app',
      windowsStoreAppUtils,
      `Start-Locally ${appName} ${args}`,
      verbose,
    );
  } else {
    newInfo('Skip the step to start the app');
  }

  popd();
}

function startServerInNewWindow(options, verbose) {
  return new Promise(resolve => {
    if (options.packager) {
      http
        .get('http://localhost:8081/status', res => {
          if (res.statusCode === 200) {
            newSuccess('React-Native Server already started');
          } else {
            newError('React-Native Server not responding');
          }
          resolve();
        })
        .on('error', () => resolve(launchServer(options, verbose)));
    } else {
      resolve();
    }
  });
}

function launchServer(options, verbose) {
  newSuccess('Starting the React-Native Server');
  const launchPackagerScript = path.resolve(
    __dirname,
    '../../../Scripts/launchPackager.bat',
  );
  const opts = {
    cwd: options.root,
    detached: true,
    stdio: verbose ? 'inherit' : 'ignore',
  };

  return Promise.resolve(
    spawn('cmd.exe', ['/C', 'start', launchPackagerScript], opts),
  );
}

module.exports = {
  getBuildConfiguration,
  deployToDesktop,
  deployToDevice,
  startServerInNewWindow,
};
