// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"

#include <Views/SIPEventHandler.h>
#include <Views/ShadowNodeBase.h>
#include "Impl/ScrollViewUWPImplementation.h"
#include "ScrollViewManager.h"

namespace react::uwp {

namespace ScrollViewCommands {
constexpr const char *ScrollTo = "scrollTo";
constexpr const char *ScrollToEnd = "scrollToEnd";
}; // namespace ScrollViewCommands

class ScrollViewShadowNode : public ShadowNodeBase {
  using Super = ShadowNodeBase;

 public:
  ScrollViewShadowNode();
  ~ScrollViewShadowNode();
  void dispatchCommand(const std::string &commandId, const folly::dynamic &commandArgs) override;
  void createView() override;
  void updateProperties(const folly::dynamic &&props) override;

 private:
  void AddHandlers(const winrt::ScrollViewer &scrollViewer);
  void EmitScrollEvent(
      const winrt::ScrollViewer &scrollViewer,
      int64_t tag,
      const char *eventName,
      double x,
      double y,
      double zoom);
  template <typename T>
  std::tuple<bool, T> getPropertyAndValidity(folly::dynamic propertyValue, T defaultValue);
  void SetScrollMode(const winrt::ScrollViewer &scrollViewer);
  void UpdateZoomMode(const winrt::ScrollViewer &scrollViewer);

  float m_zoomFactor{1.0f};
  bool m_isScrollingFromInertia = false;
  bool m_isScrolling = false;
  bool m_isHorizontal = false;
  bool m_isScrollingEnabled = true;
  bool m_changeViewAfterLoaded = false;
  bool m_dismissKeyboardOnDrag = false;

  std::shared_ptr<SIPEventHandler> m_SIPEventHandler;

  xaml::FrameworkElement::SizeChanged_revoker m_scrollViewerSizeChangedRevoker{};
  xaml::FrameworkElement::SizeChanged_revoker m_contentSizeChangedRevoker{};
  winrt::ScrollViewer::ViewChanged_revoker m_scrollViewerViewChangedRevoker{};
  winrt::ScrollViewer::ViewChanging_revoker m_scrollViewerViewChangingRevoker{};
  winrt::ScrollViewer::DirectManipulationCompleted_revoker m_scrollViewerDirectManipulationCompletedRevoker{};
  winrt::ScrollViewer::DirectManipulationStarted_revoker m_scrollViewerDirectManipulationStartedRevoker{};
  xaml::Controls::Control::Loaded_revoker m_controlLoadedRevoker{};
};

ScrollViewShadowNode::ScrollViewShadowNode() {}

ScrollViewShadowNode::~ScrollViewShadowNode() {
  m_SIPEventHandler.reset();
}

void ScrollViewShadowNode::dispatchCommand(const std::string &commandId, const folly::dynamic &commandArgs) {
  const auto scrollViewer = GetView().as<winrt::ScrollViewer>();
  if (scrollViewer == nullptr)
    return;

  if (commandId == ScrollViewCommands::ScrollTo) {
    double x = commandArgs[0].asDouble();
    double y = commandArgs[1].asDouble();
    bool animated = commandArgs[2].asBool();
    scrollViewer.ChangeView(x, y, nullptr, !animated /*disableAnimation*/);
  } else if (commandId == ScrollViewCommands::ScrollToEnd) {
    bool animated = commandArgs[0].asBool();
    bool horiz = scrollViewer.HorizontalScrollMode() == winrt::ScrollMode::Auto;
    if (horiz)
      scrollViewer.ChangeView(scrollViewer.ScrollableWidth(), nullptr, nullptr, !animated /*disableAnimation*/);
    else
      scrollViewer.ChangeView(nullptr, scrollViewer.ScrollableHeight(), nullptr, !animated /*disableAnimation*/);
  }
}

void ScrollViewShadowNode::createView() {
  Super::createView();

  const auto scrollViewer = GetView().as<winrt::ScrollViewer>();
  scrollViewer.TabIndex(0);
  const auto scrollViewUWPImplementation = ScrollViewUWPImplementation(scrollViewer);
  scrollViewUWPImplementation.ScrollViewerSnapPointManager();

  AddHandlers(scrollViewer);

  m_scrollViewerSizeChangedRevoker =
      scrollViewer.SizeChanged(winrt::auto_revoke, [scrollViewUWPImplementation](const auto &, const auto &) {
        scrollViewUWPImplementation.UpdateScrollableSize();
      });

  m_scrollViewerViewChangedRevoker = scrollViewer.ViewChanged(
      winrt::auto_revoke, [this, scrollViewUWPImplementation](const auto &sender, const auto & /*args*/) {
        const auto scrollViewerNotNull{sender.as<winrt::ScrollViewer>()};
        const auto zoomFactor{scrollViewerNotNull.ZoomFactor()};
        if (m_zoomFactor != zoomFactor) {
          m_zoomFactor = zoomFactor;
          scrollViewUWPImplementation.UpdateScrollableSize();
        }
      });

  m_contentSizeChangedRevoker = scrollViewUWPImplementation.ScrollViewerSnapPointManager()->SizeChanged(
      winrt::auto_revoke, [this, scrollViewUWPImplementation](const auto &, const auto &) {
        scrollViewUWPImplementation.UpdateScrollableSize();
      });
}

void ScrollViewShadowNode::updateProperties(const folly::dynamic &&reactDiffMap) {
  m_updating = true;

  const auto scrollViewer = GetView().as<winrt::ScrollViewer>();
  if (scrollViewer == nullptr)
    return;

  for (const auto &pair : reactDiffMap.items()) {
    const std::string &propertyName = pair.first.getString();
    const folly::dynamic &propertyValue = pair.second;

    if (propertyName == "horizontal") {
      const auto [valid, horizontal] = getPropertyAndValidity(propertyValue, false);
      if (valid) {
        m_isHorizontal = horizontal;
        ScrollViewUWPImplementation(scrollViewer).SetHorizontal(horizontal);
        SetScrollMode(scrollViewer);
      }
    }
    if (propertyName == "scrollEnabled") {
      const auto [valid, scrollEnabled] = getPropertyAndValidity(propertyValue, true);
      if (valid) {
        m_isScrollingEnabled = scrollEnabled;
        SetScrollMode(scrollViewer);
      }
    } else if (propertyName == "showsHorizontalScrollIndicator") {
      const auto [valid, showsHorizontalScrollIndicator] = getPropertyAndValidity(propertyValue, true);
      if (valid) {
        scrollViewer.HorizontalScrollBarVisibility(
            showsHorizontalScrollIndicator ? winrt::ScrollBarVisibility::Visible : winrt::ScrollBarVisibility::Hidden);
      }
    } else if (propertyName == "showsVerticalScrollIndicator") {
      const auto [valid, showsVerticalScrollIndicator] = getPropertyAndValidity(propertyValue, true);
      if (valid) {
        scrollViewer.VerticalScrollBarVisibility(
            showsVerticalScrollIndicator ? winrt::ScrollBarVisibility::Visible : winrt::ScrollBarVisibility::Hidden);
      }
    } else if (propertyName == "minimumZoomScale") {
      const auto [valid, minimumZoomScale] = getPropertyAndValidity(propertyValue, 1.0);
      if (valid) {
        scrollViewer.MinZoomFactor(static_cast<float>(minimumZoomScale));
        UpdateZoomMode(scrollViewer);
      }
    } else if (propertyName == "maximumZoomScale") {
      const auto [valid, maximumZoomScale] = getPropertyAndValidity(propertyValue, 1.0);
      if (valid) {
        scrollViewer.MaxZoomFactor(static_cast<float>(maximumZoomScale));
        UpdateZoomMode(scrollViewer);
      }
    } else if (propertyName == "zoomScale") {
      const auto [valid, zoomScale] = getPropertyAndValidity(propertyValue, 1.0);
      if (valid) {
        m_zoomFactor = static_cast<float>(zoomScale);
        m_changeViewAfterLoaded = !scrollViewer.ChangeView(nullptr, nullptr, m_zoomFactor);
      }
    } else if (propertyName == "snapToInterval") {
      const auto [valid, snapToInterval] = getPropertyAndValidity(propertyValue, 0.0);
      if (valid) {
        ScrollViewUWPImplementation(scrollViewer).SnapToInterval(static_cast<float>(snapToInterval));
      }
    } else if (propertyName == "snapToOffsets") {
      const auto [valid, snapToOffsets] = getPropertyAndValidity(propertyValue, winrt::single_threaded_vector<float>());
      if (valid) {
        ScrollViewUWPImplementation(scrollViewer).SnapToOffsets(snapToOffsets.GetView());
      }
    } else if (propertyName == "snapToStart") {
      const auto [valid, snaptoStart] = getPropertyAndValidity(propertyValue, true);
      if (valid) {
        ScrollViewUWPImplementation(scrollViewer).SnapToStart(snaptoStart);
      }
    } else if (propertyName == "snapToEnd") {
      const auto [valid, snapToEnd] = getPropertyAndValidity(propertyValue, true);
      if (valid) {
        ScrollViewUWPImplementation(scrollViewer).SnapToEnd(snapToEnd);
      }
    } else if (propertyName == "keyboardDismissMode") {
      m_dismissKeyboardOnDrag = false;
      if (propertyValue.isString()) {
        m_dismissKeyboardOnDrag = (propertyValue.getString() == "on-drag");
        if (m_dismissKeyboardOnDrag) {
          m_SIPEventHandler = std::make_unique<SIPEventHandler>(GetViewManager()->GetReactContext());
          m_SIPEventHandler->AttachView(GetView(), false /*fireKeyboardEvents*/);
        }
      }
    } else if (propertyName == "snapToAlignment") {
      const auto [valid, snapToAlignment] = getPropertyAndValidity(propertyValue, winrt::SnapPointsAlignment::Near);
      if (valid) {
        ScrollViewUWPImplementation(scrollViewer).SnapPointAlignment(snapToAlignment);
      }
    } else if (propertyName == "pagingEnabled") {
      const auto [valid, pagingEnabled] = getPropertyAndValidity(propertyValue, false);
      if (valid) {
        ScrollViewUWPImplementation(scrollViewer).PagingEnabled(pagingEnabled);
      }
    }
  }

  Super::updateProperties(std::move(reactDiffMap));
  m_updating = false;
}

void ScrollViewShadowNode::AddHandlers(const winrt::ScrollViewer &scrollViewer) {
  m_scrollViewerViewChangingRevoker =
      scrollViewer.ViewChanging(winrt::auto_revoke, [this](const auto &sender, const auto &args) {
        const auto scrollViewerNotNull = sender.as<winrt::ScrollViewer>();

        // If we are transitioning to inertial scrolling.
        if (m_isScrolling && !m_isScrollingFromInertia && args.IsInertial()) {
          m_isScrollingFromInertia = true;

          EmitScrollEvent(
              scrollViewerNotNull,
              m_tag,
              "topScrollEndDrag",
              args.NextView().HorizontalOffset(),
              args.NextView().VerticalOffset(),
              args.NextView().ZoomFactor());

          EmitScrollEvent(
              scrollViewerNotNull,
              m_tag,
              "topScrollBeginMomentum",
              args.NextView().HorizontalOffset(),
              args.NextView().VerticalOffset(),
              args.NextView().ZoomFactor());
        }

        EmitScrollEvent(
            scrollViewerNotNull,
            m_tag,
            "topScroll",
            args.NextView().HorizontalOffset(),
            args.NextView().VerticalOffset(),
            args.NextView().ZoomFactor());
      });

  m_scrollViewerDirectManipulationStartedRevoker =
      scrollViewer.DirectManipulationStarted(winrt::auto_revoke, [this](const auto &sender, const auto &) {
        m_isScrolling = true;

        if (m_dismissKeyboardOnDrag && m_SIPEventHandler) {
          m_SIPEventHandler->TryHide();
        }

        const auto scrollViewer = sender.as<winrt::ScrollViewer>();
        EmitScrollEvent(
            scrollViewer,
            m_tag,
            "topScrollBeginDrag",
            scrollViewer.HorizontalOffset(),
            scrollViewer.VerticalOffset(),
            scrollViewer.ZoomFactor());
      });

  m_scrollViewerDirectManipulationCompletedRevoker =
      scrollViewer.DirectManipulationCompleted(winrt::auto_revoke, [this](const auto &sender, const auto &) {
        const auto scrollViewer = sender.as<winrt::ScrollViewer>();
        if (m_isScrollingFromInertia) {
          EmitScrollEvent(
              scrollViewer,
              m_tag,
              "topScrollEndMomentum",
              scrollViewer.HorizontalOffset(),
              scrollViewer.VerticalOffset(),
              scrollViewer.ZoomFactor());
        } else {
          EmitScrollEvent(
              scrollViewer,
              m_tag,
              "topScrollEndDrag",
              scrollViewer.HorizontalOffset(),
              scrollViewer.VerticalOffset(),
              scrollViewer.ZoomFactor());
        }

        m_isScrolling = false;
        m_isScrollingFromInertia = false;
      });
  m_controlLoadedRevoker = scrollViewer.Loaded(winrt::auto_revoke, [this](const auto &sender, const auto &) {
    if (m_changeViewAfterLoaded) {
      const auto scrollViewer = sender.as<winrt::ScrollViewer>();
      scrollViewer.ChangeView(nullptr, nullptr, static_cast<float>(m_zoomFactor));
      m_changeViewAfterLoaded = false;
    }
  });
}

void ScrollViewShadowNode::EmitScrollEvent(
    const winrt::ScrollViewer &scrollViewer,
    int64_t tag,
    const char *eventName,
    double x,
    double y,
    double zoom) {
  const auto scrollViewerNotNull = scrollViewer;

  folly::dynamic offset = folly::dynamic::object("x", x)("y", y);

  folly::dynamic contentInset = folly::dynamic::object("left", 0)("top", 0)("right", 0)("bottom", 0);

  folly::dynamic contentSize =
      folly::dynamic::object("width", scrollViewerNotNull.ExtentWidth())("height", scrollViewerNotNull.ExtentHeight());

  folly::dynamic layoutSize =
      folly::dynamic::object("width", scrollViewerNotNull.ActualWidth())("height", scrollViewerNotNull.ActualHeight());

  folly::dynamic eventJson =
      folly::dynamic::object("target", tag)("responderIgnoreScroll", true)("contentOffset", offset)(
          "contentInset", contentInset)("contentSize", contentSize)("layoutMeasurement", layoutSize)("zoomScale", zoom);

  folly::dynamic params = folly::dynamic::array(tag, eventName, eventJson);
  GetViewManager()->GetReactContext().CallJSFunction("RCTEventEmitter", "receiveEvent", std::move(params));
}

template <typename T>
std::tuple<bool, T> ScrollViewShadowNode::getPropertyAndValidity(folly::dynamic propertyValue, T defaultValue) {
  if (propertyValue.isNull()) {
    return std::make_tuple(true, defaultValue);
  }

  if constexpr (std::is_same<T, bool>()) {
    if (propertyValue.isBool()) {
      return std::make_tuple(true, propertyValue.getBool());
    }
  }

  if constexpr (std::is_same<T, double>()) {
    if (propertyValue.isDouble()) {
      return std::make_tuple(true, propertyValue.getDouble());
    }
    if (propertyValue.isInt()) {
      return std::make_tuple(true, static_cast<double>(propertyValue.getInt()));
    }
  }

  if constexpr (std::is_same<T, winrt::IVector<float>>()) {
    if (propertyValue.isArray()) {
      return std::make_tuple(true, [propertyValue]() {
        const auto vector = winrt::single_threaded_vector<float>();
        for (const auto &val : propertyValue) {
          if (val.isDouble())
            vector.Append(static_cast<float>(val.getDouble()));
          else if (val.isInt())
            vector.Append(static_cast<float>(val.getInt()));
        }
        return vector;
      }());
    }
  }

  if constexpr (std::is_same<T, winrt::SnapPointsAlignment>()) {
    if (propertyValue.isString()) {
      return std::make_tuple(true, static_cast<T>([snapToAlignment = propertyValue.getString()]() {
                               if (snapToAlignment == "end") {
                                 return winrt::SnapPointsAlignment::Far;
                               } else if (snapToAlignment == "center") {
                                 return winrt::SnapPointsAlignment::Center;
                               } else {
                                 return winrt::SnapPointsAlignment::Near;
                               }
                             }()));
    }
  }

  return std::make_tuple(false, defaultValue);
}

void ScrollViewShadowNode::SetScrollMode(const winrt::ScrollViewer &scrollViewer) {
  const auto horizontalScrollingEnabled = m_isScrollingEnabled && m_isHorizontal;
  const auto verticalScrollingEnabled = m_isScrollingEnabled && !m_isHorizontal;
  scrollViewer.HorizontalScrollMode(horizontalScrollingEnabled ? winrt::ScrollMode::Auto : winrt::ScrollMode::Disabled);
  scrollViewer.VerticalScrollMode(verticalScrollingEnabled ? winrt::ScrollMode::Auto : winrt::ScrollMode::Disabled);
}

void ScrollViewShadowNode::UpdateZoomMode(const winrt::ScrollViewer &scrollViewer) {
  scrollViewer.ZoomMode(
      scrollViewer.MinZoomFactor() != scrollViewer.MaxZoomFactor() ? winrt::ZoomMode::Enabled
                                                                   : winrt::ZoomMode::Disabled);
}

ScrollViewManager::ScrollViewManager(const Mso::React::IReactContext& context) : Super(context) {}

const char *ScrollViewManager::GetName() const {
  return "RCTScrollView";
}

folly::dynamic ScrollViewManager::GetCommands() const {
  // Upstream JS will dispatch the string directly instead of ever actually calling this, but providing a real
  // implementation is simple enough in case anything changes.
  return folly::dynamic::object(ScrollViewCommands::ScrollTo, ScrollViewCommands::ScrollTo)(
      ScrollViewCommands::ScrollToEnd, ScrollViewCommands::ScrollToEnd);
}

folly::dynamic ScrollViewManager::GetNativeProps() const {
  auto props = Super::GetNativeProps();

  props.update(folly::dynamic::object("horizontal", "boolean")("scrollEnabled", "boolean")(
      "showsHorizontalScrollIndicator", "boolean")("showsVerticalScrollIndicator", "boolean")(
      "minimumZoomScale", "float")("maximumZoomScale", "float")("zoomScale", "float")("snapToInterval", "float")(
      "snapToOffsets", "array")("snapToAlignment", "number")("snapToStart", "boolean")("snapToEnd", "boolean")(
      "pagingEnabled", "boolean")("keyboardDismissMode", "string"));

  return props;
}

facebook::react::ShadowNode *ScrollViewManager::createShadow() const {
  return new ScrollViewShadowNode();
}

folly::dynamic ScrollViewManager::GetExportedCustomDirectEventTypeConstants() const {
  auto directEvents = Super::GetExportedCustomDirectEventTypeConstants();
  directEvents["topScrollBeginMomentum"] = folly::dynamic::object("registrationName", "onMomentumScrollBegin");
  directEvents["topScrollEndMomentum"] = folly::dynamic::object("registrationName", "onMomentumScrollEnd");
  directEvents["topScrollBeginDrag"] = folly::dynamic::object("registrationName", "onScrollBeginDrag");
  directEvents["topScrollEndDrag"] = folly::dynamic::object("registrationName", "onScrollEndDrag");
  directEvents["topScroll"] = folly::dynamic::object("registrationName", "onScroll");

  return directEvents;
}

XamlView ScrollViewManager::CreateViewCore(int64_t /*tag*/) {
  const auto scrollViewer = winrt::ScrollViewer{};

  scrollViewer.HorizontalScrollBarVisibility(winrt::ScrollBarVisibility::Auto);
  scrollViewer.VerticalScrollBarVisibility(winrt::ScrollBarVisibility::Auto);
  scrollViewer.VerticalSnapPointsAlignment(winrt::SnapPointsAlignment::Near);
  scrollViewer.VerticalSnapPointsType(winrt::SnapPointsType::Mandatory);
  scrollViewer.HorizontalSnapPointsType(winrt::SnapPointsType::Mandatory);

  const auto snapPointManager = SnapPointManagingContentControl::Create();
  scrollViewer.Content(*snapPointManager);

  return scrollViewer;
}

void ScrollViewManager::AddView(const XamlView &parent, const XamlView &child, [[maybe_unused]] int64_t index) {
  assert(index == 0);

  auto scrollViewer = parent.as<winrt::ScrollViewer>();
  auto snapPointManager = scrollViewer.Content().as<SnapPointManagingContentControl>();
  snapPointManager->Content(child);
}

void ScrollViewManager::RemoveAllChildren(const XamlView &parent) {
  auto scrollViewer = parent.as<winrt::ScrollViewer>();
  auto snapPointManager = scrollViewer.Content().as<SnapPointManagingContentControl>();
  snapPointManager->Content(nullptr);
}

void ScrollViewManager::RemoveChildAt(const XamlView &parent, [[maybe_unused]] int64_t index) {
  assert(index == 0);
  RemoveAllChildren(parent);
}

void ScrollViewManager::SnapToInterval(const XamlView &parent, float interval) {
  if (parent) {
    if (const auto scrollViewer = parent.as<winrt::ScrollViewer>()) {
      ScrollViewUWPImplementation(scrollViewer).SnapToInterval(interval);
    }
  }
}

void ScrollViewManager::SnapToOffsets(const XamlView &parent, const winrt::IVectorView<float> &offsets) {
  if (parent) {
    if (const auto scrollViewer = parent.as<winrt::ScrollViewer>()) {
      ScrollViewUWPImplementation(scrollViewer).SnapToOffsets(offsets);
    }
  }
}

} // namespace react::uwp
