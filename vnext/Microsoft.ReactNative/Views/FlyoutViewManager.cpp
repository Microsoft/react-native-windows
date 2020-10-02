// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"

#include <Views/ShadowNodeBase.h>
#include "FlyoutViewManager.h"
#include "TouchEventHandler.h"
#include "ViewPanel.h"

#include <Modules/NativeUIManager.h>
#include <UI.Xaml.Controls.Primitives.h>
#include <UI.Xaml.Controls.h>
#include <UI.Xaml.Documents.h>
#include <UI.Xaml.Input.h>
#include <UI.Xaml.Media.h>
#include <Utils/Helpers.h>
#include <Utils/PropertyHandlerUtils.h>

#ifdef USE_WINUI3
namespace winrt::Microsoft::UI::Xaml::Controls::Primitives {
using IFlyoutBase5 = ::xaml::Controls::Primitives::IFlyoutBase;
using IFlyoutBase6 = ::xaml::Controls::Primitives::IFlyoutBase;
}; // namespace winrt::Microsoft::UI::Xaml::Controls::Primitives
#endif

namespace winrt {
using namespace xaml::Controls;
using namespace xaml::Controls::Primitives;
using namespace xaml::Interop;
using namespace winrt::Windows::UI::Xaml::Interop;
} // namespace winrt

static const std::unordered_map<std::string, winrt::FlyoutPlacementMode> placementModeMinVersion = {
    {"top", winrt::FlyoutPlacementMode::Top},
    {"top-edge-aligned-left", winrt::FlyoutPlacementMode::Top},
    {"top-edge-aligned-right", winrt::FlyoutPlacementMode::Top},
    {"bottom", winrt::FlyoutPlacementMode::Bottom},
    {"bottom-edge-aligned-left", winrt::FlyoutPlacementMode::Bottom},
    {"bottom-edge-aligned-right", winrt::FlyoutPlacementMode::Bottom},
    {"left", winrt::FlyoutPlacementMode::Left},
    {"left-edge-aligned-top", winrt::FlyoutPlacementMode::Left},
    {"left-edge-aligned-bottom", winrt::FlyoutPlacementMode::Left},
    {"right", winrt::FlyoutPlacementMode::Right},
    {"right-edge-aligned-top", winrt::FlyoutPlacementMode::Right},
    {"right-edge-aligned-bottom", winrt::FlyoutPlacementMode::Right},
    {"full", winrt::FlyoutPlacementMode::Full}};

static const std::unordered_map<std::string, winrt::FlyoutPlacementMode> placementModeRS5 = {
    {"top", winrt::FlyoutPlacementMode::Top},
    {"bottom", winrt::FlyoutPlacementMode::Bottom},
    {"left", winrt::FlyoutPlacementMode::Left},
    {"right", winrt::FlyoutPlacementMode::Right},
    {"full", winrt::FlyoutPlacementMode::Full},
    {"top-edge-aligned-left", winrt::FlyoutPlacementMode::TopEdgeAlignedLeft},
    {"top-edge-aligned-right", winrt::FlyoutPlacementMode::TopEdgeAlignedRight},
    {"bottom-edge-aligned-left", winrt::FlyoutPlacementMode::BottomEdgeAlignedLeft},
    {"bottom-edge-aligned-right", winrt::FlyoutPlacementMode::BottomEdgeAlignedRight},
    {"left-edge-aligned-top", winrt::FlyoutPlacementMode::LeftEdgeAlignedTop},
    {"left-edge-aligned-bottom", winrt::FlyoutPlacementMode::LeftEdgeAlignedBottom},
    {"right-edge-aligned-top", winrt::FlyoutPlacementMode::RightEdgeAlignedTop},
    {"right-edge-aligned-bottom", winrt::FlyoutPlacementMode::RightEdgeAlignedBottom}};

template <>
struct json_type_traits<winrt::FlyoutPlacementMode> {
  static winrt::FlyoutPlacementMode parseJson(const folly::dynamic &json) {
    auto placementMode = !!(winrt::Flyout().try_as<winrt::IFlyoutBase5>()) ? placementModeRS5 : placementModeMinVersion;
    auto iter = placementMode.find(json.asString());

    if (iter != placementMode.end()) {
      return iter->second;
    }

    return winrt::FlyoutPlacementMode::Right;
  }
};

namespace react::uwp {

class FlyoutShadowNode : public ShadowNodeBase {
  using Super = ShadowNodeBase;

 public:
  FlyoutShadowNode() = default;
  virtual ~FlyoutShadowNode();

  void AddView(ShadowNode &child, int64_t index) override;
  void createView() override;
  static void OnFlyoutClosed(const Mso::React::IReactContext &context, int64_t tag, bool newValue);
  void onDropViewInstance() override;
  void removeAllChildren() override;
  void updateProperties(const folly::dynamic &&props) override;
  winrt::Flyout GetFlyout();
  void AdjustDefaultFlyoutStyle(float maxWidth, float maxHeight);

  bool IsWindowed() override {
    return true;
  }

 private:
  void SetTargetFrameworkElement();
  winrt::Popup GetFlyoutParentPopup() const;
  winrt::FlyoutPresenter GetFlyoutPresenter() const;
  void OnShowFlyout();
  xaml::FrameworkElement m_targetElement = nullptr;
  winrt::Flyout m_flyout = nullptr;
  bool m_isLightDismissEnabled = true;
  bool m_isOpen = false;
  int64_t m_targetTag = -1;
  float m_horizontalOffset = 0;
  float m_verticalOffset = 0;
  bool m_isFlyoutShowOptionsSupported = false;
  winrt::FlyoutShowOptions m_showOptions = nullptr;

  std::unique_ptr<TouchEventHandler> m_touchEventHanadler;
  std::unique_ptr<PreviewKeyboardEventHandlerOnRoot> m_previewKeyboardEventHandlerOnRoot;

  winrt::Flyout::Closing_revoker m_flyoutClosingRevoker{};
  winrt::Flyout::Closed_revoker m_flyoutClosedRevoker{};
  int64_t m_tokenContentPropertyChangeCallback{0};
  winrt::Flyout::Opened_revoker m_flyoutOpenedRevoker{};
  winrt::XamlRoot::Changed_revoker m_xamlRootChangedRevoker{};
};

FlyoutShadowNode::~FlyoutShadowNode() {
  m_touchEventHanadler->RemoveTouchHandlers();
  m_previewKeyboardEventHandlerOnRoot->unhook();
}

void FlyoutShadowNode::AddView(ShadowNode &child, int64_t /*index*/) {
  auto childView = static_cast<ShadowNodeBase &>(child).GetView();
  m_touchEventHanadler->AddTouchHandlers(childView);
  m_previewKeyboardEventHandlerOnRoot->hook(childView);

  if (m_flyout != nullptr) {
    m_flyout.Content(childView.as<xaml::UIElement>());
    if (winrt::FlyoutPlacementMode::Full == m_flyout.Placement()) {
      // When using FlyoutPlacementMode::Full on a Flyout with an embedded
      // Picker, the flyout is not centered correctly. Below is a temporary
      // workaround that resolves the problem for flyouts with fixed size
      // content by adjusting the flyout presenter max size settings prior to
      // layout. This will unblock those scenarios while the work on a more
      // exhaustive fix proceeds.  Tracked by Issue #2969
      if (auto fe = m_flyout.Content().try_as<xaml::FrameworkElement>()) {
        AdjustDefaultFlyoutStyle((float)fe.Width(), (float)fe.Height());
      }
    }
  }
}

void FlyoutShadowNode::createView() {
  Super::createView();

  m_flyout = winrt::Flyout();
  m_isFlyoutShowOptionsSupported = !!(winrt::Flyout().try_as<winrt::IFlyoutBase5>());

  if (m_isFlyoutShowOptionsSupported)
    m_showOptions = winrt::FlyoutShowOptions();

  m_touchEventHanadler = std::make_unique<TouchEventHandler>(GetViewManager()->GetReactContext());
  m_previewKeyboardEventHandlerOnRoot =
      std::make_unique<PreviewKeyboardEventHandlerOnRoot>(GetViewManager()->GetReactContext());

  m_flyoutClosingRevoker = m_flyout.Closing(
      winrt::auto_revoke, [=](winrt::FlyoutBase /*flyoutbase*/, winrt::FlyoutBaseClosingEventArgs args) {
        if (!m_updating && !m_isLightDismissEnabled && m_isOpen) {
          args.Cancel(true);
        }
      });

  m_flyoutClosedRevoker = m_flyout.Closed(winrt::auto_revoke, [=](auto &&, auto &&) {
    if (!m_updating) {
      if (m_targetElement != nullptr) {
        // When the flyout closes, attempt to move focus to
        // its anchor element to prevent cases where focus can land on
        // an outer flyout content and therefore trigger a unexpected flyout
        // dismissal
        xaml::Input::FocusManager::TryFocusAsync(m_targetElement, winrt::FocusState::Programmatic);
      }

      OnFlyoutClosed(GetViewManager()->GetReactContext(), m_tag, false);
      m_xamlRootChangedRevoker.revoke();
    }
  });

  // After opening the flyout, turn off AllowFocusOnInteraction so that
  // focus cannot land in the top content element of the flyout. If focus
  // lands in the flyout presenter, then on moving focus somewhere else,
  // including the children on the flyout presenter, the flyout can dismiss.
  // (Wait until after opening, so that the flyout presenter has a chance to
  // move focus to the first focusable element in the flyout.)
  //
  m_flyoutOpenedRevoker = m_flyout.Opened(winrt::auto_revoke, [=](auto &&, auto &&) {
    m_flyout.AllowFocusOnInteraction(false);

    if (!m_updating) {
      if (auto flyoutPresenter = GetFlyoutPresenter()) {
        // When multiple flyouts/popups are overlapping, XAML's theme
        // shadows don't render properly. As a workaround we enable a
        // z-index translation based on an elevation derived from the count
        // of open popups/flyouts. We apply this translation on open of the
        // flyout. (Translation is only supported on RS5+, eg. IUIElement9)
        if (auto uiElement9 = GetView().try_as<xaml::IUIElement9>()) {
          auto numOpenPopups = CountOpenPopups();
          if (numOpenPopups > 0) {
            winrt::Numerics::float3 translation{0, 0, (float)16 * numOpenPopups};
            flyoutPresenter.Translation(translation);
          }
        }

        flyoutPresenter.AllowFocusOnInteraction(false);
      }
    }
  });

  // Turning AllowFocusOnInteraction off at the root of the flyout and
  // flyout presenter turns it off for all children of the flyout. In order to
  // make sure that interactions with the content of the flyout still work as
  // expected, AllowFocusOnInteraction is turned on the content element when
  // the Content property is updated.
  m_tokenContentPropertyChangeCallback = m_flyout.RegisterPropertyChangedCallback(
      winrt::Flyout::ContentProperty(), [=](xaml::DependencyObject sender, xaml::DependencyProperty dp) {
        if (auto flyout = sender.try_as<winrt::Flyout>()) {
          if (auto content = flyout.Content()) {
            if (auto fe = content.try_as<xaml::FrameworkElement>()) {
              fe.AllowFocusOnInteraction(true);
            }
          }
        }
      });

  // Set XamlRoot on the Flyout to handle XamlIsland/AppWindow scenarios.
  if (auto flyoutBase6 = m_flyout.try_as<winrt::IFlyoutBase6>()) {
    if (auto uiManager = static_cast<NativeUIManager *> (GetViewManager()->GetReactContext().NativeUIManager())) {
      if (auto xamlRoot = uiManager->tryGetXamlRoot()) {
        flyoutBase6.XamlRoot(xamlRoot);
        m_xamlRootChangedRevoker = xamlRoot.Changed(winrt::auto_revoke, [this](auto &&, auto &&) {
          if (m_isLightDismissEnabled) {
            onDropViewInstance();
          }
        });
      }
    }
  }
}

/*static*/ void FlyoutShadowNode::OnFlyoutClosed(const Mso::React::IReactContext& context, int64_t tag, bool newValue) {
  folly::dynamic eventData = folly::dynamic::object("target", tag)("isOpen", newValue);
  context.DispatchEvent(tag, "topDismiss", std::move(eventData));
}

void FlyoutShadowNode::onDropViewInstance() {
  if (m_isOpen) {
    m_isOpen = false;
    m_flyout.Hide();
  }
}

void FlyoutShadowNode::removeAllChildren() {
  m_flyout.ClearValue(winrt::Flyout::ContentProperty());
}

void FlyoutShadowNode::updateProperties(const folly::dynamic &&props) {
  m_updating = true;
  bool updateTargetElement = false;
  bool updateIsOpen = false;
  bool updateOffset = false;

  if (m_flyout == nullptr)
    return;

  for (auto &pair : props.items()) {
    const std::string &propertyName = pair.first.getString();
    const folly::dynamic &propertyValue = pair.second;

    if (propertyName == "horizontalOffset") {
      if (propertyValue.isNumber())
        m_horizontalOffset = static_cast<float>(propertyValue.asDouble());
      else
        m_horizontalOffset = 0;

      updateOffset = true;
    } else if (propertyName == "isLightDismissEnabled") {
      if (propertyValue.isBool())
        m_isLightDismissEnabled = propertyValue.asBool();
      else if (propertyValue.isNull())
        m_isLightDismissEnabled = true;
      if (m_isOpen) {
        auto popup = GetFlyoutParentPopup();
        if (popup != nullptr) {
          popup.IsLightDismissEnabled(m_isLightDismissEnabled);
        }
      }
    } else if (propertyName == "isOpen") {
      if (propertyValue.isBool()) {
        bool isOpen = m_isOpen;
        m_isOpen = propertyValue.asBool();
        if (isOpen != m_isOpen) {
          updateIsOpen = true;
        }
      }
    } else if (propertyName == "placement") {
      auto placement = json_type_traits<winrt::FlyoutPlacementMode>::parseJson(propertyValue);
      m_flyout.Placement(placement);
    } else if (propertyName == "target") {
      if (propertyValue.isNumber()) {
        m_targetTag = static_cast<int64_t>(propertyValue.asDouble());
        updateTargetElement = true;
      } else
        m_targetTag = -1;
    } else if (propertyName == "verticalOffset") {
      if (propertyValue.isNumber())
        m_verticalOffset = static_cast<float>(propertyValue.asDouble());
      else
        m_verticalOffset = 0;

      updateOffset = true;
    } else if (propertyName == "isOverlayEnabled") {
      auto overlayMode = winrt::LightDismissOverlayMode::Off;
      if (propertyValue.isBool() && propertyValue.asBool()) {
        overlayMode = winrt::LightDismissOverlayMode::On;
      }

      m_flyout.LightDismissOverlayMode(overlayMode);
    }
  }

  if (updateTargetElement || m_targetElement == nullptr) {
    SetTargetFrameworkElement();
    winrt::FlyoutBase::SetAttachedFlyout(m_targetElement, m_flyout);
  }

  if (updateOffset && m_isFlyoutShowOptionsSupported) {
    winrt::Point newPoint(m_horizontalOffset, m_verticalOffset);
    m_showOptions.Position(newPoint);
  }

  if (updateIsOpen) {
    if (m_isOpen) {
      OnShowFlyout();
    } else {
      m_flyout.Hide();
    }
  }

  // TODO: hook up view props to the flyout (m_flyout) instead of setting them
  // on the dummy view.
  // Super::updateProperties(std::move(props));
  m_updating = false;
}

winrt::Flyout FlyoutShadowNode::GetFlyout() {
  return m_flyout;
}

void FlyoutShadowNode::OnShowFlyout() {
  AdjustDefaultFlyoutStyle(50000, 50000);
  if (m_isFlyoutShowOptionsSupported) {
    m_flyout.ShowAt(m_targetElement, m_showOptions);
  } else {
    winrt::FlyoutBase::ShowAttachedFlyout(m_targetElement);
  }

  auto popup = GetFlyoutParentPopup();
  if (popup != nullptr) {
    popup.IsLightDismissEnabled(m_isLightDismissEnabled);
  }
}

void FlyoutShadowNode::SetTargetFrameworkElement() {
  if (m_targetTag > 0) {
    if (auto uiManager = static_cast<NativeUIManager *>(GetViewManager()->GetReactContext().NativeUIManager())) {
      auto pNativeUIManagerHost = uiManager->getHost();
      ShadowNodeBase *pShadowNodeChild =
          static_cast<ShadowNodeBase *>(pNativeUIManagerHost->FindShadowNodeForTag(m_targetTag));

      if (pShadowNodeChild != nullptr) {
        auto targetView = pShadowNodeChild->GetView();
        m_targetElement = targetView.as<xaml::FrameworkElement>();
      }
    }
  } else {
    m_targetElement = xaml::Window::Current().Content().as<xaml::FrameworkElement>();
  }
}

void FlyoutShadowNode::AdjustDefaultFlyoutStyle(float maxWidth, float maxHeight) {
  winrt::Style flyoutStyle({XAML_NAMESPACE_STR L".Controls.FlyoutPresenter", winrt::TypeKind::Metadata});
  flyoutStyle.Setters().Append(winrt::Setter(xaml::FrameworkElement::MaxWidthProperty(), winrt::box_value(maxWidth)));
  flyoutStyle.Setters().Append(winrt::Setter(xaml::FrameworkElement::MaxHeightProperty(), winrt::box_value(maxHeight)));
  flyoutStyle.Setters().Append(winrt::Setter(xaml::Controls::Control::PaddingProperty(), winrt::box_value(0)));
  flyoutStyle.Setters().Append(winrt::Setter(xaml::Controls::Control::BorderThicknessProperty(), winrt::box_value(0)));
  flyoutStyle.Setters().Append(
      winrt::Setter(xaml::FrameworkElement::AllowFocusOnInteractionProperty(), winrt::box_value(false)));
  flyoutStyle.Setters().Append(winrt::Setter(
      xaml::Controls::Control::BackgroundProperty(),
      winrt::box_value(xaml::Media::SolidColorBrush{winrt::Colors::Transparent()})));
  m_flyout.FlyoutPresenterStyle(flyoutStyle);
}

winrt::Popup FlyoutShadowNode::GetFlyoutParentPopup() const {
  // TODO: Use VisualTreeHelper::GetOpenPopupsFromXamlRoot when running against
  // RS6
  winrt::Windows::Foundation::Collections::IVectorView<winrt::Popup> popups =
      winrt::VisualTreeHelper::GetOpenPopups(xaml::Window::Current());
  if (popups.Size() > 0)
    return popups.GetAt(0);
  return nullptr;
}

winrt::FlyoutPresenter FlyoutShadowNode::GetFlyoutPresenter() const {
  if (m_flyout == nullptr || m_flyout.Content() == nullptr)
    return nullptr;

  auto parent = winrt::VisualTreeHelper::GetParent(m_flyout.Content());
  if (parent == nullptr)
    return nullptr;

  auto scope = parent.try_as<winrt::FlyoutPresenter>();
  while (parent != nullptr && scope == nullptr) {
    parent = winrt::VisualTreeHelper::GetParent(parent);
    scope = parent.try_as<winrt::FlyoutPresenter>();
  }

  return scope;
}

FlyoutViewManager::FlyoutViewManager(const Mso::React::IReactContext& context) : Super(context) {}

const char *FlyoutViewManager::GetName() const {
  return "RCTFlyout";
}

XamlView FlyoutViewManager::CreateViewCore(int64_t /*tag*/) {
  return winrt::make<winrt::react::uwp::implementation::ViewPanel>().as<XamlView>();
}

facebook::react::ShadowNode *FlyoutViewManager::createShadow() const {
  return new FlyoutShadowNode();
}

folly::dynamic FlyoutViewManager::GetNativeProps() const {
  auto props = Super::GetNativeProps();

  props.update(
      folly::dynamic::object("horizontalOffset", "number")("isLightDismissEnabled", "boolean")("isOpen", "boolean")(
          "placement", "number")("target", "number")("verticalOffset", "number")("isOverlayEnabled", "boolean"));

  return props;
}

folly::dynamic FlyoutViewManager::GetExportedCustomDirectEventTypeConstants() const {
  auto directEvents = Super::GetExportedCustomDirectEventTypeConstants();
  directEvents["topDismiss"] = folly::dynamic::object("registrationName", "onDismiss");

  return directEvents;
}

void FlyoutViewManager::SetLayoutProps(
    ShadowNodeBase &nodeToUpdate,
    const XamlView & /*viewToUpdate*/,
    float /*left*/,
    float /*top*/,
    float width,
    float height) {
  auto *pFlyoutShadowNode = static_cast<FlyoutShadowNode *>(&nodeToUpdate);

  if (auto flyout = pFlyoutShadowNode->GetFlyout()) {
    if (winrt::FlyoutPlacementMode::Full == flyout.Placement()) {
      pFlyoutShadowNode->AdjustDefaultFlyoutStyle(width, height);
    }
  }
}

} // namespace react::uwp
