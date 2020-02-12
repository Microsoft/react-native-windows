// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include "FrameworkElementViewManager.h"

namespace react {
namespace uwp {

struct ShadowNodeBase;

class REACTWINDOWS_EXPORT ControlViewManager : public FrameworkElementViewManager {
  using Super = FrameworkElementViewManager;

 public:
  ControlViewManager(const std::shared_ptr<IReactInstance> &reactInstance);

  folly::dynamic GetNativeProps() const override;
  void UpdateProperties(ShadowNodeBase *nodeToUpdate, const folly::dynamic &reactDiffMap) override;
  void TransferProperties(XamlView oldView, XamlView newView) override;

 protected:
  void OnViewCreated(XamlView view) override;
};

} // namespace uwp
} // namespace react
