// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once
#ifndef MICROSOFT_REACTNATIVE_JSI_JSIAPI
#define MICROSOFT_REACTNATIVE_JSI_JSIAPI
#include "../ReactContext.h"
#include "JsiAbiApi.h"

// Use __ImageBase to get current DLL handle.
// http://blogs.msdn.com/oldnewthing/archive/2004/10/25/247180.aspx
extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace winrt::Microsoft::ReactNative {

// Get JSI Runtime from the current JS dispatcher thread.
// If it is not found, then create it and store it in the context.Properties().
// Make sure that the JSI runtime holder is removed when the instance is unloaded.
facebook::jsi::Runtime &GetOrCreateContextRuntime(ReactContext const &context) noexcept {
  ReactDispatcher jsDispatcher = context.JSDispatcher();
  VerifyElseCrashSz(jsDispatcher.HasThreadAccess(), "Must be in JS thread");

  // The JSI runtime is not available if we do Web debugging when JS is running in web browser.
  JsiRuntime abiJsiRuntime = context.Handle().JSRuntime().as<JsiRuntime>();
  VerifyElseCrashSz(abiJsiRuntime, "JSI runtime is not available");

  // See if the JSI runtime was previously created.
  JsiAbiRuntime *runtime = JsiAbiRuntime::GetFromJsiRuntime(abiJsiRuntime);
  if (!runtime) {
    // Create the runtime
    std::unique_ptr<JsiAbiRuntime> runtimeHolder = std::make_unique<JsiAbiRuntime>(abiJsiRuntime);
    runtime = runtimeHolder.get();

    // We want to keep the JSI runtime while current instance is alive.
    // The JSI runtime object must be local to our DLL.
    // We create a property name based on the current DLL handle.
    HMODULE currentDll = reinterpret_cast<HMODULE>(&__ImageBase);
    std::wstring jsiRuntimeLocalName = L"jsiRuntime_" + std::to_wstring(reinterpret_cast<uintptr_t>(currentDll));
    using ValueType = ReactNonAbiValue<std::unique_ptr<JsiAbiRuntime>>;
    ReactPropertyId<ValueType> jsiRuntimeProperty{L"ReactNative.InstanceData", jsiRuntimeLocalName.c_str()};
    ValueType runtimeValue{std::in_place, std::move(runtimeHolder)};
    context.Properties().Set(jsiRuntimeProperty, runtimeValue);

    // We remove the JSI runtime from properties when React instance is destroyed.
    auto destroyInstanceNotificationId{
        ReactNotificationId<InstanceDestroyedEventArgs>{L"ReactNative.InstanceSettings", L"InstanceDestroyed"}};
    context.Notifications().Subscribe(
        destroyInstanceNotificationId,
        jsDispatcher,
        [ context, jsiRuntimeProperty ](
            winrt::Windows::Foundation::IInspectable const & /*sender*/,
            ReactNotificationArgs<InstanceDestroyedEventArgs> const &args) noexcept {
          context.Properties().Remove(jsiRuntimeProperty);
          args.Subscription().Unsubscribe(); // Unsubscribe after we handle the notification.
        });
  }

  return *runtime;
}

// Call provided lambda with the facebook::jsi::Runtime& parameter.
// For example: ExecuteJsi(context, [](facebook::jsi::Runtime& runtime){...})
// The code is executed synchronously if it is already in JSDispatcher, or asynchronously otherwise.
template <class TCodeWithRuntime>
void ExecuteJsi(ReactContext const &context, TCodeWithRuntime const &code) {
  ReactDispatcher jsDispatcher = context.JSDispatcher();
  if (jsDispatcher.HasThreadAccess()) {
    // Execute immediately if we are in JS thread.
    code(GetOrCreateContextRuntime(context));
  } else {
    // Otherwise, schedule work in JS thread.
    jsDispatcher.Post([ context, code ]() noexcept { code(GetOrCreateContextRuntime(context)); });
  }
}

} // namespace winrt::Microsoft::ReactNative

#endif // MICROSOFT_REACTNATIVE_JSI_JSIAPI
