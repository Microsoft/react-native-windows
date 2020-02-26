#pragma once

#include <ReactCommon/JSCallInvoker.h>
#include <ReactCommon/TurboModule.h>
#include "TurboModuleRegistry.h"

namespace facebook {
namespace react {

class TurboModuleManager {
 public:
  TurboModuleManager(
      std::shared_ptr<TurboModuleRegistry> turboModuleRegistry,
      std::shared_ptr<JSCallInvoker> jsInvoker);

  std::shared_ptr<TurboModule> getModule(const std::string &moduleName) noexcept;
  bool hasModule(const std::string &moduleName) noexcept;
  std::vector<std::string> getEagerInitModuleNames() noexcept;
  void onInstanceDestroy() noexcept;

 private:
  std::unordered_map<std::string, std::shared_ptr<TurboModule>> m_modules;
  std::shared_ptr<JSCallInvoker> m_jsInvoker;
  std::shared_ptr<TurboModuleRegistry> m_turboModuleRegistry;
};
} // namespace react
} // namespace facebook
