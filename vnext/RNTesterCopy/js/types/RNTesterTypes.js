/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @format
 * @flow
 */

'use strict';

import type {ComponentType} from 'react';
import * as React from 'react';

export type RNTesterProps = $ReadOnly<{|
  navigator?: ?$ReadOnlyArray<
    $ReadOnly<{|
      title: string,
      component: ComponentType<any>,
      backButtonTitle: string,
      passProps: any,
    |}>,
  >,
|}>;

export type RNTesterExampleModuleItem = $ReadOnly<{|
  title: string,
  platform?: string,
  description?: string,
  render: () => React.Node,
|}>;

export type RNTesterExampleModule = $ReadOnly<{|
  title: string,
  description: string,
  displayName?: ?string,
  framework?: string,
  examples: Array<RNTesterExampleModuleItem>,
  simpleExampleContainer?: ?boolean,
|}>;

export type RNTesterExample = $ReadOnly<{|
  key: string,
  module: RNTesterExampleModule,
  supportsTVOS?: boolean,
|}>;
