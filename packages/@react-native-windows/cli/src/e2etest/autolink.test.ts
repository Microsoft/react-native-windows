import path from 'path';
import { projectConfigWindows } from '../config/projectConfig';
import {AutolinkWindows} from '../runWindows/utils/autolink';
import {DOMParser} from 'xmldom';
import { ensureWinUI3Project } from './projectConfig.utils';

test('autolink with no windows project', () => {
    expect(() => {
      // eslint-disable-next-line no-new
      new AutolinkTest({}, {}, {check: true, logging: false});
    }).toThrowError();
  });

  test('autolink with incomplete windows project', () => {
    expect(() => {
      const autolink = new AutolinkTest(
        {windows: {}},
        {},
        {check: true, logging: false},
      );
      autolink.validateRequiredAppProperties();
    }).toThrowError();
  });

  class AutolinkTest extends AutolinkWindows {
    public getWindowsProjectConfig() {
      return this.windowsAppConfig;
    }
    public experimentalFeaturesProps = '';
    protected getExperimentalFeaturesPropsXml(){
        return {path: 'ExperimentalFeatures.props', content: new DOMParser().parseFromString(this.experimentalFeaturesProps, 'application/xml')};
    }
    protected async updateFile(filepath: string, content: string) {
        if (filepath === 'ExperimentalFeatures.props') {
            this.experimentalFeaturesProps = content;
        } else {
            throw new Error(`Unknown path: ${filepath}`);
        }
        return true;
    }
}


  test('autolink fixup sln', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.'}},
      {},
      {check: true, logging: false, sln: 'foo'},
    );
    expect(autolink.getWindowsProjectConfig().solutionFile).toBeUndefined();
    expect(() => {
      autolink.validateRequiredAppProperties();
    }).toThrow();
    autolink.fixUpForSlnOption();
    expect(autolink.getWindowsProjectConfig().solutionFile).toEqual('foo');
    expect(() => {
      autolink.validateRequiredAppProperties();
    }).toThrow();
  });

  test('autolink fixup proj', async done => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {},
      {
        check: true,
        logging: false,
        proj: 'projects/WithWinUI3/windows/WithWinUI3/WithWinUI3.vcxproj',
      },
    );
    expect(autolink.getWindowsProjectConfig().solutionFile).toEqual('foo.sln');
    expect(autolink.getWindowsProjectConfig().project).toBeUndefined();

    const folder = path.resolve('src/e2etest/projects/', 'WithWinUI3');
    await ensureWinUI3Project(folder);
    expect(() => {
      autolink.validateRequiredProjectProperties();
    }).toThrow();
    autolink.fixUpForProjOption();

    const projectConfig = autolink.getWindowsProjectConfig().project;
    expect(projectConfig).not.toBeUndefined();
    expect(projectConfig.projectName).toEqual('WithWinUI3');
    autolink.validateRequiredProjectProperties();
    done();
  });

  test('empty cpp autolink dependencies', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {},
      {
        check: true,
        logging: false,
        proj: 'projects/WithWinUI3/windows/WithWinUI3/WithWinUI3.vcxproj',
      },
    );
    const replacements = autolink.getCppReplacements();
    expect(replacements.cppIncludes).toEqual('');
    expect(replacements.cppPackageProviders).toEqual(
      '\n    UNREFERENCED_PARAMETER(packageProviders);',
    );
  });

  test('one invalid cpp autolink dependency', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {
        superModule: {
          name: 'superModule',
          root: 'theRoot',
          platforms: {
            windows: {},
          },
          assets: [],
          hooks: {},
          params: [],
        },
      },
      {
        check: true,
        logging: false,
        proj: 'projects/WithWinUI3/windows/WithWinUI3/WithWinUI3.vcxproj',
      },
    );
    const replacements = autolink.getCppReplacements();
    expect(replacements.cppIncludes).toEqual('');
    expect(replacements.cppPackageProviders).toEqual(
      '\n    UNREFERENCED_PARAMETER(packageProviders);',
    );
  });

  test('one invalid cs autolink dependency', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {
        superModule: {
          name: 'superModule',
          root: 'theRoot',
          platforms: {
            windows: {},
          },
          assets: [],
          hooks: {},
          params: [],
        },
      },
      {
        check: true,
        logging: false,
        proj:
          'projects/SimpleCSharpApp/windows/SimpleCSharpApp/SimpleCSharpApp.csproj',
      },
    );
    const replacements = autolink.getCsReplacements();
    expect(replacements.csUsingNamespaces).toEqual('');
    expect(replacements.csReactPackageProviders).toEqual('');
  });

  test('one valid cpp autolink dependency', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {
        superModule: {
          name: 'superModule',
          root: 'theRoot',
          platforms: {
            windows: {
              sourceDir: __dirname,
              projects: [
                {
                  directDependency: true,
                  projectFile: 'superModule.vcxproj',
                  cppHeaders: ['Garfield.h', 'Snoopy.h'],
                  cppPackageProviders: ['FamousAnimalCartoons'],
                },
              ],
            },
          },
          assets: [],
          hooks: {},
          params: [],
        },
      },
      {
        check: true,
        logging: false,
        proj: 'projects/WithWinUI3/windows/WithWinUI3/WithWinUI3.vcxproj',
      },
    );
    const replacements = autolink.getCppReplacements();
    expect(replacements.cppIncludes).toMatch(/#include <Garfield.h>/);
    expect(replacements.cppIncludes).toMatch(/#include <Snoopy.h>/);
    expect(replacements.cppPackageProviders).toContain(
      'packageProviders.Append(winrt::FamousAnimalCartoons())',
    );
  });

  test('one valid cs autolink dependency', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {
        superModule: {
          name: 'superModule',
          root: 'theRoot',
          platforms: {
            windows: {
              sourceDir: __dirname,
              projects: [
                {
                  directDependency: true,
                  csNamespaces: ['Garfield'],
                  projectFile: 'superModule.vcxproj',
                  cppHeaders: ['Garfield.h', 'Snoopy.h'],
                  csPackageProviders: ['FamousAnimalCartoons'],
                },
              ],
            },
          },
          assets: [],
          hooks: {},
          params: [],
        },
      },
      {
        check: true,
        logging: false,
        proj:
          'projects/SimpleCSharpApp/windows/SimpleCSharpApp/SimpleCSharpApp.csproj',
      },
    );
    const replacements = autolink.getCsReplacements();
    expect(replacements.csUsingNamespaces).toContain('using Garfield;');
    expect(replacements.csReactPackageProviders).toContain(
      'packageProviders.Add(new FamousAnimalCartoons())',
    );
  });

  test('Indirect autolink dependency', () => {
    const autolink = new AutolinkTest(
      {windows: {folder: __dirname, sourceDir: '.', solutionFile: 'foo.sln'}},
      {
        superModule: {
          name: 'superModule',
          root: 'theRoot',
          platforms: {
            windows: {
              sourceDir: __dirname,
              projects: [
                {
                  directDependency: true,
                  projectFile: 'superModule.vcxproj',
                  cppHeaders: ['Garfield.h', 'Snoopy.h'],
                  cppPackageProviders: ['FamousAnimalCartoons'],
                },
                {
                  directDependency: false,
                  projectFile: 'indirect.vcxproj',
                }
              ],
            },
          },
          assets: [],
          hooks: {},
          params: [],
        },
      },
      {
        check: true,
        logging: false,
        proj: 'projects/WithIndirectDependency/windows/WithIndirectDependency/WithIndirectDependency.vcxproj',
      },
    );
    const replacements = autolink.getCppReplacements();
    expect(replacements.cppIncludes).toMatch(/#include <Garfield.h>/);
    expect(replacements.cppIncludes).toMatch(/#include <Snoopy.h>/);
    expect(replacements.cppPackageProviders).toContain(
      'packageProviders.Append(winrt::FamousAnimalCartoons())',
    );
  });
