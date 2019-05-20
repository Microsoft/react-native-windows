// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <IReactInstance.h>

#include <Threading/WorkerMessageQueueThread.h>

#include <winrt/Windows.UI.Core.h>

#include <map>
#include <memory>
#include <string>


namespace facebook { namespace react {
struct NativeModuleProvider;
}}
namespace react { namespace uwp {
struct ViewManagerProvider;
}}

namespace react { namespace uwp {

class UwpReactInstance : public IReactInstance, public ::std::enable_shared_from_this<UwpReactInstance>
{
public:
  // Creation
  UwpReactInstance(
    const std::shared_ptr<facebook::react::NativeModuleProvider>& moduleProvider
  , const std::shared_ptr<ViewManagerProvider>& viewManagerProvider = nullptr);

  void Start(const std::shared_ptr<IReactInstance>& spThis, const ReactInstanceSettings& settings) override;

  // IReactInstance implementation
  void AttachMeasuredRootView(IXamlRootView* pRootView, folly::dynamic&& initProps) override;
  void DetachRootView(IXamlRootView* pRootView) override;
  LiveReloadCallbackCookie RegisterLiveReloadCallback(std::function<void()> callback) override;
  void UnregisterLiveReloadCallback(LiveReloadCallbackCookie& cookie) override;
  ErrorCallbackCookie RegisterErrorCallback(std::function<void()> callback) override;
  void UnregisterErrorCallback(ErrorCallbackCookie& cookie) override;
  void DispatchEvent(int64_t viewTag, std::string eventName, folly::dynamic&& eventData) override;
  void CallJsFunction(std::string&& moduleName, std::string&& method, folly::dynamic&& params) noexcept override;
  const std::shared_ptr<facebook::react::MessageQueueThread>& JSMessageQueueThread() const noexcept override;
  const std::shared_ptr<facebook::react::MessageQueueThread>& DefaultNativeMessageQueueThread() const noexcept override;
  facebook::react::INativeUIManager* NativeUIManager() const noexcept override;
  bool NeedsReload() const noexcept override { return m_needsReload; }
  void SetAsNeedsReload() noexcept override { m_needsReload = true; }
  std::shared_ptr<facebook::react::Instance> GetInnerInstance() const noexcept override { return m_instanceWrapper->GetInstance(); }
  bool IsInError() const noexcept override { return m_isInError; }
  const std::string& LastErrorMessage() const noexcept override { return m_errorMessage; }
  void loadBundle(std::string&& jsBundleRelativePath) override { if (!m_isInError) m_instanceWrapper->loadBundle(std::move(jsBundleRelativePath)); };

  // Test hooks
  void SetTestHook(std::string&& testHookName, std::function<void()> testHook) override;
  void CallTestHook(std::string&& testHookName) override;
  void SetTestHook(std::string&& testHookName, std::function<void(folly::dynamic&&)> testHook) override;
  void CallTestHook(std::string&& testHookName, folly::dynamic&& params) override;
  void SetTestHook(std::string&& testHookName, std::function<void(react::uwp::XamlView)> testHook) override;
  void CallTestHook(std::string&& testHookName, react::uwp::XamlView params) override;

  // Public functions
  std::shared_ptr<facebook::react::MessageQueueThread> GetNewUIMessageQueue() const;

private:
  void OnHitError(const std::string& error) noexcept;

private:
  std::shared_ptr<WorkerMessageQueueThread> m_initThread;
  std::shared_ptr<facebook::react::MessageQueueThread> m_jsThread;
  std::shared_ptr<facebook::react::MessageQueueThread> m_defaultNativeThread;
  std::shared_ptr<facebook::react::IUIManager> m_uiManager;
  std::shared_ptr<facebook::react::InstanceWrapper> m_instanceWrapper;
  winrt::Windows::UI::Core::CoreDispatcher m_uiDispatcher{ nullptr };
  std::shared_ptr<facebook::react::NativeModuleProvider> m_moduleProvider;
  std::shared_ptr<ViewManagerProvider> m_viewManagerProvider;
  std::map<LiveReloadCallbackCookie, std::function<void()>> m_liveReloadCallbacks;
  std::map<ErrorCallbackCookie, std::function<void()>> m_errorCallbacks;
  bool m_needsReload { false };
  bool m_started{ false };
  std::atomic_bool m_isInError{ false };
  std::string m_errorMessage;

  std::map<std::string, std::function<void()>> m_voidTestHooks;
  std::map<std::string, std::function<void(folly::dynamic&&)>> m_dynamicTestHooks;
  std::map<std::string, std::function<void(XamlView)>> m_viewTestHooks;
};

} }
