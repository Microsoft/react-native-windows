/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @providesModule DatePickerIOS
 */

'use strict';

var React = require('React');
var StyleSheet = require('StyleSheet');
var Text = require('Text');
var View = require('View');

class DummyDatePickerIOS extends React.Component {
  render() {
    return (
      <View style={[styles.dummyDatePickerIOS, this.props.style]}>
        <Text style={styles.datePickerText}>DatePickerIOS is not supported on this platform!</Text>
      </View>
    );
  }
}

var styles = StyleSheet.create({
  dummyDatePickerIOS: {
    height: 100,
    width: 300,
    backgroundColor: '#ffbcbc',
    borderWidth: 1,
    borderColor: 'red',
    alignItems: 'center',
    justifyContent: 'center',
    margin: 10,
  },
  datePickerText: {
    color: '#333333',
    margin: 20,
  }
});

module.exports = DummyDatePickerIOS;
