﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.190111.3

#pragma once

WINRT_EXPORT namespace winrt::Windows::UI::Xaml {

struct CornerRadius;
struct DependencyProperty;
struct FrameworkElement;
struct Thickness;
struct UIElement;

}

WINRT_EXPORT namespace winrt::Windows::UI::Xaml::Automation::Provider {

struct IRawElementProviderSimple;

}

WINRT_EXPORT namespace winrt::Windows::UI::Xaml::Controls {

struct Border;

}

WINRT_EXPORT namespace winrt::Windows::UI::Xaml::Media {

struct Brush;

}

WINRT_EXPORT namespace winrt::react::uwp {

enum class AccessibilityRoles : int32_t
{
    None = 0,
    Button = 1,
    Link = 2,
    Search = 3,
    Image = 4,
    KeyboardKey = 5,
    Text = 6,
    Adjustable = 7,
    ImageButton = 8,
    Header = 9,
    Summary = 10,
    Unknown = 11,
    CountRoles = 12,
};

enum class AccessibilityStates : int32_t
{
    Selected = 0,
    Disabled = 1,
    CountStates = 2,
};

struct IDynamicAutomationPeer;
struct IDynamicAutomationPeerFactory;
struct IDynamicAutomationProperties;
struct IDynamicAutomationPropertiesStatics;
struct IViewControl;
struct IViewPanel;
struct IViewPanelStatics;
struct DynamicAutomationPeer;
struct DynamicAutomationProperties;
struct ViewControl;
struct ViewPanel;
struct AccessibilityInvokeEventHandler;

}

namespace winrt::impl {

template <> struct category<react::uwp::IDynamicAutomationPeer>{ using type = interface_category; };
template <> struct category<react::uwp::IDynamicAutomationPeerFactory>{ using type = interface_category; };
template <> struct category<react::uwp::IDynamicAutomationProperties>{ using type = interface_category; };
template <> struct category<react::uwp::IDynamicAutomationPropertiesStatics>{ using type = interface_category; };
template <> struct category<react::uwp::IViewControl>{ using type = interface_category; };
template <> struct category<react::uwp::IViewPanel>{ using type = interface_category; };
template <> struct category<react::uwp::IViewPanelStatics>{ using type = interface_category; };
template <> struct category<react::uwp::DynamicAutomationPeer>{ using type = class_category; };
template <> struct category<react::uwp::DynamicAutomationProperties>{ using type = class_category; };
template <> struct category<react::uwp::ViewControl>{ using type = class_category; };
template <> struct category<react::uwp::ViewPanel>{ using type = class_category; };
template <> struct category<react::uwp::AccessibilityRoles>{ using type = enum_category; };
template <> struct category<react::uwp::AccessibilityStates>{ using type = enum_category; };
template <> struct category<react::uwp::AccessibilityInvokeEventHandler>{ using type = delegate_category; };
template <> struct name<react::uwp::IDynamicAutomationPeer>{ static constexpr auto & value{ L"react.uwp.IDynamicAutomationPeer" }; };
template <> struct name<react::uwp::IDynamicAutomationPeerFactory>{ static constexpr auto & value{ L"react.uwp.IDynamicAutomationPeerFactory" }; };
template <> struct name<react::uwp::IDynamicAutomationProperties>{ static constexpr auto & value{ L"react.uwp.IDynamicAutomationProperties" }; };
template <> struct name<react::uwp::IDynamicAutomationPropertiesStatics>{ static constexpr auto & value{ L"react.uwp.IDynamicAutomationPropertiesStatics" }; };
template <> struct name<react::uwp::IViewControl>{ static constexpr auto & value{ L"react.uwp.IViewControl" }; };
template <> struct name<react::uwp::IViewPanel>{ static constexpr auto & value{ L"react.uwp.IViewPanel" }; };
template <> struct name<react::uwp::IViewPanelStatics>{ static constexpr auto & value{ L"react.uwp.IViewPanelStatics" }; };
template <> struct name<react::uwp::DynamicAutomationPeer>{ static constexpr auto & value{ L"react.uwp.DynamicAutomationPeer" }; };
template <> struct name<react::uwp::DynamicAutomationProperties>{ static constexpr auto & value{ L"react.uwp.DynamicAutomationProperties" }; };
template <> struct name<react::uwp::ViewControl>{ static constexpr auto & value{ L"react.uwp.ViewControl" }; };
template <> struct name<react::uwp::ViewPanel>{ static constexpr auto & value{ L"react.uwp.ViewPanel" }; };
template <> struct name<react::uwp::AccessibilityRoles>{ static constexpr auto & value{ L"react.uwp.AccessibilityRoles" }; };
template <> struct name<react::uwp::AccessibilityStates>{ static constexpr auto & value{ L"react.uwp.AccessibilityStates" }; };
template <> struct name<react::uwp::AccessibilityInvokeEventHandler>{ static constexpr auto & value{ L"react.uwp.AccessibilityInvokeEventHandler" }; };
template <> struct guid_storage<react::uwp::IDynamicAutomationPeer>{ static constexpr guid value{ 0x96D2FA46,0xD93B,0x5EB4,{ 0x9E,0xD8,0xFC,0x60,0x2C,0xB5,0xB7,0x8F } }; };
template <> struct guid_storage<react::uwp::IDynamicAutomationPeerFactory>{ static constexpr guid value{ 0x0F0A64B1,0xCCEF,0x54F1,{ 0xB9,0x05,0x0C,0x58,0x26,0xCB,0x6C,0xC4 } }; };
template <> struct guid_storage<react::uwp::IDynamicAutomationProperties>{ static constexpr guid value{ 0xB70AAC96,0x549C,0x52C1,{ 0xA1,0x24,0xAE,0x0C,0xA4,0x96,0xC8,0x05 } }; };
template <> struct guid_storage<react::uwp::IDynamicAutomationPropertiesStatics>{ static constexpr guid value{ 0xA92AD1FD,0xB630,0x5CDB,{ 0x85,0x61,0x9F,0xEC,0xEC,0xA8,0xB9,0x66 } }; };
template <> struct guid_storage<react::uwp::IViewControl>{ static constexpr guid value{ 0xDD899021,0xA952,0x5F5A,{ 0xA5,0xC1,0xAC,0x9E,0x85,0x08,0x09,0xBD } }; };
template <> struct guid_storage<react::uwp::IViewPanel>{ static constexpr guid value{ 0x3925A064,0xC58F,0x57D5,{ 0x80,0xF6,0xF6,0x09,0xFD,0x2D,0x42,0x2C } }; };
template <> struct guid_storage<react::uwp::IViewPanelStatics>{ static constexpr guid value{ 0x844BE4A4,0xF166,0x5B49,{ 0x8E,0x82,0x5E,0xA6,0x16,0x19,0xF0,0x10 } }; };
template <> struct guid_storage<react::uwp::AccessibilityInvokeEventHandler>{ static constexpr guid value{ 0xCF396F1D,0x7B41,0x5E44,{ 0xB2,0xD5,0xBA,0xB5,0x86,0xC7,0xEE,0x33 } }; };
template <> struct default_interface<react::uwp::DynamicAutomationPeer>{ using type = react::uwp::IDynamicAutomationPeer; };
template <> struct default_interface<react::uwp::DynamicAutomationProperties>{ using type = react::uwp::IDynamicAutomationProperties; };
template <> struct default_interface<react::uwp::ViewControl>{ using type = react::uwp::IViewControl; };
template <> struct default_interface<react::uwp::ViewPanel>{ using type = react::uwp::IViewPanel; };

template <> struct abi<react::uwp::IDynamicAutomationPeer>{ struct type : IInspectable
{
};};

template <> struct abi<react::uwp::IDynamicAutomationPeerFactory>{ struct type : IInspectable
{
    virtual int32_t WINRT_CALL CreateInstance(void* owner, void** value) noexcept = 0;
};};

template <> struct abi<react::uwp::IDynamicAutomationProperties>{ struct type : IInspectable
{
};};

template <> struct abi<react::uwp::IDynamicAutomationPropertiesStatics>{ struct type : IInspectable
{
    virtual int32_t WINRT_CALL get_AccessibilityRoleProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL SetAccessibilityRole(void* element, react::uwp::AccessibilityRoles value) noexcept = 0;
    virtual int32_t WINRT_CALL GetAccessibilityRole(void* element, react::uwp::AccessibilityRoles* result) noexcept = 0;
    virtual int32_t WINRT_CALL get_AccessibilityStateDisabledProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL SetAccessibilityStateDisabled(void* element, bool value) noexcept = 0;
    virtual int32_t WINRT_CALL GetAccessibilityStateDisabled(void* element, bool* result) noexcept = 0;
    virtual int32_t WINRT_CALL get_AccessibilityStateSelectedProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL SetAccessibilityStateSelected(void* element, bool value) noexcept = 0;
    virtual int32_t WINRT_CALL GetAccessibilityStateSelected(void* element, bool* result) noexcept = 0;
    virtual int32_t WINRT_CALL get_AccessibilityInvokeEventHandlerProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL SetAccessibilityInvokeEventHandler(void* element, void* value) noexcept = 0;
    virtual int32_t WINRT_CALL GetAccessibilityInvokeEventHandler(void* element, void** result) noexcept = 0;
};};

template <> struct abi<react::uwp::IViewControl>{ struct type : IInspectable
{
    virtual int32_t WINRT_CALL GetPanel(void** result) noexcept = 0;
};};

template <> struct abi<react::uwp::IViewPanel>{ struct type : IInspectable
{
    virtual int32_t WINRT_CALL InsertAt(uint32_t index, void* value) noexcept = 0;
    virtual int32_t WINRT_CALL RemoveAt(uint32_t index) noexcept = 0;
    virtual int32_t WINRT_CALL Clear() noexcept = 0;
    virtual int32_t WINRT_CALL FinalizeProperties() noexcept = 0;
    virtual int32_t WINRT_CALL GetOuterBorder(void** result) noexcept = 0;
    virtual int32_t WINRT_CALL get_BorderThickness(struct struct_Windows_UI_Xaml_Thickness* value) noexcept = 0;
    virtual int32_t WINRT_CALL put_BorderThickness(struct struct_Windows_UI_Xaml_Thickness value) noexcept = 0;
    virtual int32_t WINRT_CALL get_BorderBrush(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL put_BorderBrush(void* value) noexcept = 0;
    virtual int32_t WINRT_CALL get_CornerRadius(struct struct_Windows_UI_Xaml_CornerRadius* value) noexcept = 0;
    virtual int32_t WINRT_CALL put_CornerRadius(struct struct_Windows_UI_Xaml_CornerRadius value) noexcept = 0;
    virtual int32_t WINRT_CALL get_ClipChildren(bool* value) noexcept = 0;
    virtual int32_t WINRT_CALL put_ClipChildren(bool value) noexcept = 0;
};};

template <> struct abi<react::uwp::IViewPanelStatics>{ struct type : IInspectable
{
    virtual int32_t WINRT_CALL get_BorderThicknessProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL get_BorderBrushProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL get_CornerRadiusProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL get_ClipChildrenProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL get_TopProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL SetTop(void* element, double value) noexcept = 0;
    virtual int32_t WINRT_CALL GetTop(void* element, double* result) noexcept = 0;
    virtual int32_t WINRT_CALL get_LeftProperty(void** value) noexcept = 0;
    virtual int32_t WINRT_CALL SetLeft(void* element, double value) noexcept = 0;
    virtual int32_t WINRT_CALL GetLeft(void* element, double* result) noexcept = 0;
};};

template <> struct abi<react::uwp::AccessibilityInvokeEventHandler>{ struct type : IUnknown
{
    virtual int32_t WINRT_CALL Invoke() noexcept = 0;
};};

template <typename D>
struct consume_react_uwp_IDynamicAutomationPeer
{
};
template <> struct consume<react::uwp::IDynamicAutomationPeer> { template <typename D> using type = consume_react_uwp_IDynamicAutomationPeer<D>; };

template <typename D>
struct consume_react_uwp_IDynamicAutomationPeerFactory
{
    react::uwp::DynamicAutomationPeer CreateInstance(Windows::UI::Xaml::FrameworkElement const& owner) const;
};
template <> struct consume<react::uwp::IDynamicAutomationPeerFactory> { template <typename D> using type = consume_react_uwp_IDynamicAutomationPeerFactory<D>; };

template <typename D>
struct consume_react_uwp_IDynamicAutomationProperties
{
};
template <> struct consume<react::uwp::IDynamicAutomationProperties> { template <typename D> using type = consume_react_uwp_IDynamicAutomationProperties<D>; };

template <typename D>
struct consume_react_uwp_IDynamicAutomationPropertiesStatics
{
    Windows::UI::Xaml::DependencyProperty AccessibilityRoleProperty() const;
    void SetAccessibilityRole(Windows::UI::Xaml::UIElement const& element, react::uwp::AccessibilityRoles const& value) const;
    react::uwp::AccessibilityRoles GetAccessibilityRole(Windows::UI::Xaml::UIElement const& element) const;
    Windows::UI::Xaml::DependencyProperty AccessibilityStateDisabledProperty() const;
    void SetAccessibilityStateDisabled(Windows::UI::Xaml::UIElement const& element, bool value) const;
    bool GetAccessibilityStateDisabled(Windows::UI::Xaml::UIElement const& element) const;
    Windows::UI::Xaml::DependencyProperty AccessibilityStateSelectedProperty() const;
    void SetAccessibilityStateSelected(Windows::UI::Xaml::UIElement const& element, bool value) const;
    bool GetAccessibilityStateSelected(Windows::UI::Xaml::UIElement const& element) const;
    Windows::UI::Xaml::DependencyProperty AccessibilityInvokeEventHandlerProperty() const;
    void SetAccessibilityInvokeEventHandler(Windows::UI::Xaml::UIElement const& element, react::uwp::AccessibilityInvokeEventHandler const& value) const;
    react::uwp::AccessibilityInvokeEventHandler GetAccessibilityInvokeEventHandler(Windows::UI::Xaml::UIElement const& element) const;
};
template <> struct consume<react::uwp::IDynamicAutomationPropertiesStatics> { template <typename D> using type = consume_react_uwp_IDynamicAutomationPropertiesStatics<D>; };

template <typename D>
struct consume_react_uwp_IViewControl
{
    react::uwp::ViewPanel GetPanel() const;
};
template <> struct consume<react::uwp::IViewControl> { template <typename D> using type = consume_react_uwp_IViewControl<D>; };

template <typename D>
struct consume_react_uwp_IViewPanel
{
    void InsertAt(uint32_t index, Windows::UI::Xaml::UIElement const& value) const;
    void RemoveAt(uint32_t index) const;
    void Clear() const;
    void FinalizeProperties() const;
    Windows::UI::Xaml::Controls::Border GetOuterBorder() const;
    Windows::UI::Xaml::Thickness BorderThickness() const;
    void BorderThickness(Windows::UI::Xaml::Thickness const& value) const;
    Windows::UI::Xaml::Media::Brush BorderBrush() const;
    void BorderBrush(Windows::UI::Xaml::Media::Brush const& value) const;
    Windows::UI::Xaml::CornerRadius CornerRadius() const;
    void CornerRadius(Windows::UI::Xaml::CornerRadius const& value) const;
    bool ClipChildren() const;
    void ClipChildren(bool value) const;
};
template <> struct consume<react::uwp::IViewPanel> { template <typename D> using type = consume_react_uwp_IViewPanel<D>; };

template <typename D>
struct consume_react_uwp_IViewPanelStatics
{
    Windows::UI::Xaml::DependencyProperty BorderThicknessProperty() const;
    Windows::UI::Xaml::DependencyProperty BorderBrushProperty() const;
    Windows::UI::Xaml::DependencyProperty CornerRadiusProperty() const;
    Windows::UI::Xaml::DependencyProperty ClipChildrenProperty() const;
    Windows::UI::Xaml::DependencyProperty TopProperty() const;
    void SetTop(Windows::UI::Xaml::UIElement const& element, double value) const;
    double GetTop(Windows::UI::Xaml::UIElement const& element) const;
    Windows::UI::Xaml::DependencyProperty LeftProperty() const;
    void SetLeft(Windows::UI::Xaml::UIElement const& element, double value) const;
    double GetLeft(Windows::UI::Xaml::UIElement const& element) const;
};
template <> struct consume<react::uwp::IViewPanelStatics> { template <typename D> using type = consume_react_uwp_IViewPanelStatics<D>; };

}
