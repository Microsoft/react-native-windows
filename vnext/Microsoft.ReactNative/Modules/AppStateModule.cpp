// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "AppStateModule.h"
#include <Utils/Helpers.h>
#include <XamlUtils.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include "Unicode.h"

namespace Microsoft::ReactNative {

void AppState::Initialize(winrt::Microsoft::ReactNative::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
  m_active = true;

  // We need to register for notifications from the XAML thread.
  if (auto dispatcher = reactContext.UIDispatcher()) {
    dispatcher.Post([this]() {
      if (auto currentApp = xaml::TryGetCurrentApplication()) {
        m_enteredBackgroundRevoker = currentApp.EnteredBackground(
            winrt::auto_revoke,
            [weakThis = weak_from_this()](
                winrt::IInspectable const & /*sender*/,
                winrt::Windows::ApplicationModel::EnteredBackgroundEventArgs const & /*e*/) noexcept {
              if (auto strongThis = weakThis.lock()) {
                strongThis->SetActive(false);
              }
            });

        m_leavingBackgroundRevoker = currentApp.LeavingBackground(
            winrt::auto_revoke,
            [weakThis = weak_from_this()](
                winrt::IInspectable const & /*sender*/,
                winrt::Windows::ApplicationModel::LeavingBackgroundEventArgs const & /*e*/) noexcept {
              if (auto strongThis = weakThis.lock()) {
                strongThis->SetActive(true);
              }
            });
      } else {
        assert(react::uwp::IsXamlIsland());
      }
    });
  }
}

void AppState::GetCurrentAppState(
    std::function<void(React::JSValue const &)> const &success,
    std::function<void(React::JSValue const &)> const &error) noexcept {
  success(m_active ? "active" : "background");
}

void AppState::AddListener(std::string && /*eventName*/) noexcept {
  // noop
}

void AppState::RemoveListeners(double /*count*/) noexcept {
  // noop
}

void AppState::SetActive(bool active) noexcept {
  m_active = active;
  m_context.JSDispatcher().Post([this]() { AppStateDidChange({m_active ? "active" : "background"}); });
}

} // namespace Microsoft::ReactNative
