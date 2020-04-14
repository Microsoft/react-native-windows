/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @flow strict-local
 * @format
 */

'use strict';

import type {BubblingEventHandler, WithDefault} from '../../Types/CodegenTypes';
import type {ColorValue} from '../../StyleSheet/StyleSheetTypes';
import type {ViewProps} from '../View/ViewPropTypes';
import * as React from 'react';

import codegenNativeComponent from '../../Utilities/codegenNativeComponent';
import codegenNativeCommands from 'react-native/Libraries/Utilities/codegenNativeCommands';
import type {HostComponent} from '../../Renderer/shims/ReactNativeTypes';
import type {NativeOrDynamicColorType} from '../../StyleSheet/NativeOrDynamicColorType'; // [Windows]

type SwitchChangeEvent = $ReadOnly<{|
  value: boolean,
|}>;

type NativeProps = $ReadOnly<{|
  ...ViewProps,

  // Props
  disabled?: WithDefault<boolean, false>,
  value?: WithDefault<boolean, false>,
  tintColor?: ?ColorValue | NativeOrDynamicColorType, // [Windows]
  onTintColor?: ?ColorValue | NativeOrDynamicColorType, // [Windows]
  thumbTintColor?: ?ColorValue | NativeOrDynamicColorType, // [Windows]

  // Deprecated props
  thumbColor?: ?ColorValue | NativeOrDynamicColorType, // [Windows]
  trackColorForFalse?: ?ColorValue | NativeOrDynamicColorType, // [Windows]
  trackColorForTrue?: ?ColorValue | NativeOrDynamicColorType, // [Windows]

  // Events
  onChange?: ?BubblingEventHandler<SwitchChangeEvent>,
|}>;

type ComponentType = HostComponent<NativeProps>;

interface NativeCommands {
  +setValue: (viewRef: React.ElementRef<ComponentType>, value: boolean) => void;
}

export const Commands: NativeCommands = codegenNativeCommands<NativeCommands>({
  supportedCommands: ['setValue'],
});

export default (codegenNativeComponent<NativeProps>('Switch', {
  paperComponentName: 'RCTSwitch',
  excludedPlatform: 'android',
}): ComponentType);
