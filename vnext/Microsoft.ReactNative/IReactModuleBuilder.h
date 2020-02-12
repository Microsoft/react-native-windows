#pragma once
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "ABICxxModule.h"
#include "ReactHost/React.h"
#include "cxxreact/CxxModule.h"
#include "winrt/Microsoft.ReactNative.h"

namespace winrt::Microsoft::ReactNative {

struct ReactModuleBuilder : winrt::implements<ReactModuleBuilder, IReactModuleBuilder> {
  ReactModuleBuilder(Mso::CntPtr<Mso::React::IReactContext> &&reactContext) noexcept;

 public: // IReactModuleBuilder
  void SetEventEmitterName(hstring const &name) noexcept;
  void AddMethod(hstring const &name, MethodReturnType returnType, MethodDelegate const &method) noexcept;
  void AddSyncMethod(hstring const &name, SyncMethodDelegate const &method) noexcept;
  void AddConstantProvider(ConstantProvider const &constantProvider) noexcept;
  void AddEventHandlerSetter(hstring const &name, ReactEventHandlerSetter const &eventHandlerSetter) noexcept;

 public:
  std::unique_ptr<facebook::xplat::module::CxxModule> MakeCxxModule(
      std::string const &name,
      IInspectable &nativeModule) noexcept;

 private:
  static MethodResultCallback MakeMethodResultCallback(facebook::xplat::module::CxxModule::Callback callback) noexcept;

 private:
  std::string m_eventEmitterName;
  std::vector<facebook::xplat::module::CxxModule::Method> m_methods;
  std::vector<ConstantProvider> m_constants;
  std::vector<ABICxxModuleEventHandlerSetter> m_eventHandlerSetters;
  Mso::CntPtr<Mso::React::IReactContext> m_reactContext;
};

} // namespace winrt::Microsoft::ReactNative
