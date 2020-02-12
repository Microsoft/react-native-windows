/**
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 *
 * @format
 * @flow strict
 */

'use strict';

module.exports = {
  DeprecatedAccessibilityTraits: [
    'none',
    'button',
    'link',
    'header',
    'search',
    'image',
    'selected',
    'plays',
    'key',
    'text',
    'summary',
    'disabled',
    'frequentUpdates',
    'startsMedia',
    'adjustable',
    'allowsDirectInteraction',
    'pageTurn',
  ],
  DeprecatedAccessibilityComponentTypes: [
    'none',
    'button',
    'radiobutton_checked',
    'radiobutton_unchecked',
  ],
  // This must be kept in sync with the AccessibilityRolesMask in RCTViewManager.m
  DeprecatedAccessibilityRoles: [
    'none',
    'button',
    'link',
    'search',
    'image',
    'keyboardkey',
    'text',
    'adjustable',
    'imagebutton',
    'header',
    'summary',
    'alert',
    'checkbox',
    'combobox',
    'menu',
    'menubar',
    'menuitem',
    'progressbar',
    'radio',
    'radiogroup',
    'scrollbar',
    'spinbutton',
    'switch',
    'tab',
    'tablist',
    'timer',
    'toolbar',
    'list', // RNW-only
    'listitem', // RNW-only
  ],
  // This must be kept in sync with the AccessibilityStatesMask in RCTViewManager.m
  DeprecatedAccessibilityStates: [
    'selected',
    'disabled',
    'checked',
    'unchecked',
    'busy',
    'expanded',
    'collapsed',
  ],
};
