#pragma once

#ifndef USE_WINUI3
#include <Microsoft.UI.Composition.Effects.BorderEffect.g.h>
#define BORDEREFFECT_NAMESPACE winrt::Microsoft::UI::Composition::Effects
#else
#define BORDEREFFECT_NAMESPACE winrt::Microsoft::ReactNative
#include <BorderEffect.g.h>
#endif

#pragma warning(push)
#pragma warning(disable : 28285 28196 6387 6319 26812)

#include "Microsoft.UI.Composition.Effects_Impl.h"

namespace BORDEREFFECT_NAMESPACE::implementation {
class BorderEffect : public BorderEffectT<BorderEffect, winrt::Microsoft::UI::Composition::Effects::implementation::EffectBase> {
 public:
  DECLARE_D2D_GUID(CLSID_D2D1Border);
  DECLARE_SINGLE_SOURCE(Source);
  DECLARE_POD_PROPERTY(ExtendX, winrt::CanvasEdgeBehavior, winrt::CanvasEdgeBehavior::Clamp, true);
  DECLARE_POD_PROPERTY(ExtendY, winrt::CanvasEdgeBehavior, winrt::CanvasEdgeBehavior::Clamp, true);
  DECLARE_NAMED_PROPERTY_MAPPING(
      {L"ExtendX", D2D1_BORDER_PROP_EDGE_MODE_X, PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT},
      {L"ExtendY", D2D1_BORDER_PROP_EDGE_MODE_Y, PropertyMapping::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT});

 public:
  IFACEMETHODIMP GetPropertyCount(_Out_ UINT *count) override {
    *count = 2;
    return S_OK;
  }

  IFACEMETHODIMP GetProperty(UINT index, _Outptr_ abi::IPropertyValue **value) override {
    return UsePropertyFactory(value, [=]() {
      switch (index) {
        case D2D1_BORDER_PROP_EDGE_MODE_X:
          return winrt::PropertyValue::CreateUInt32((UINT32)m_ExtendX);
        case D2D1_BORDER_PROP_EDGE_MODE_Y:
          return winrt::PropertyValue::CreateUInt32((UINT32)m_ExtendY);
        default:
          throw winrt::hresult_invalid_argument();
      }
    });
  }
};
} // namespace BORDEREFFECT_NAMESPACE::implementation

#pragma warning(pop)
