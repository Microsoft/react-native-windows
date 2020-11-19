<!-- Do not edit this file. It is automatically generated by API Documenter. -->

[Home](./index.md) &gt; [@office-iss/react-native-win32](./react-native-win32.md) &gt; [ITouchableWin32Props](./react-native-win32.itouchablewin32props.md) &gt; [filterKeys](./react-native-win32.itouchablewin32props.filterkeys.md)

## ITouchableWin32Props.filterKeys property

Filters keys for touchableHandleKeyPress / touchableHandleKeyPressDown events. Space and Enter keys result in touchableHandleKeyPress(Down) in the event that no filterKeys function is provided as a callback. All keyboard events will result in onKeyUp and onKeyDown getting fired regardless of filterKeys.

<b>Signature:</b>

```typescript
filterKeys?: (str: string) => boolean;
```