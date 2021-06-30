/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 * @format
 */

import React from 'react';
import {Switch, Text, TextInput, View} from 'react-native';
const RNTesterBlock = require('../../components/RNTesterBlock');
const RNTesterPage = require('../../components/RNTesterPage');

export class DisplayNoneExample extends React.Component<{}> {
  state = {
    displayNone: false,
    textState: 'TextInput...',
  };

  public render() {
    return (
      <RNTesterPage>
        <RNTesterBlock title="Display:none style with TextInput">
          <View>
            <View>
              <Text>toggle display:none TextInput</Text>
              <Switch
                onValueChange={this._handlePress}
                value={this.state.displayNone}
                testID="toggle-display:none"
              />
            </View>
            <View style={{display: this.state.displayNone ? 'none' : 'flex'}}>
              <TextInput
                style={{height: 40, borderColor: 'gray', borderWidth: 1}}
                onChangeText={text => this._handleChangeText(text)}
                value={this.state.textState}
                testID="example-textbox"
              />
            </View>
          </View>
        </RNTesterBlock>
      </RNTesterPage>
    );
  }

  _handlePress = () => {
    this.setState({displayNone: !this.state.displayNone});
  };

  _handleChangeText = (text: string) => {
    this.setState({textState: text});
  };
}

export const displayName = (_undefined?: string) => {};
export const title = 'Display:none Style';
export const description = 'Tests that "display: none" is propagated to native';
export const examples = [
  {
    render: function(): JSX.Element {
      return <DisplayNoneExample />;
    },
  },
];
