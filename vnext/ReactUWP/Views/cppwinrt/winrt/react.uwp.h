﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v1.0.190111.3

#pragma once

#include "winrt/base.h"


static_assert(winrt::check_version(CPPWINRT_VERSION, "1.0.190111.3"), "Mismatched component and base headers.");
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/impl/Windows.UI.Xaml.2.h"
#include "winrt/impl/Windows.UI.Xaml.Automation.Peers.2.h"
#include "winrt/impl/Windows.UI.Xaml.Automation.Provider.2.h"
#include "winrt/impl/react.uwp.2.h"

namespace winrt::impl {

template <typename D> react::uwp::DynamicAutomationPeer consume_react_uwp_IDynamicAutomationPeerFactory<D>::CreateInstance(Windows::UI::Xaml::FrameworkElement const& owner) const
{
    react::uwp::DynamicAutomationPeer value{ nullptr };
    check_hresult(WINRT_SHIM(react::uwp::IDynamicAutomationPeerFactory)->CreateInstance(get_abi(owner), put_abi(value)));
    return value;
}

template <typename D>
struct produce<D, react::uwp::IDynamicAutomationPeer> : produce_base<D, react::uwp::IDynamicAutomationPeer>
{};

template <typename D>
struct produce<D, react::uwp::IDynamicAutomationPeerFactory> : produce_base<D, react::uwp::IDynamicAutomationPeerFactory>
{
    int32_t WINRT_CALL CreateInstance(void* owner, void** value) noexcept final
    {
        try
        {
            *value = nullptr;
            typename D::abi_guard guard(this->shim());
            WINRT_ASSERT_DECLARATION(CreateInstance, WINRT_WRAP(react::uwp::DynamicAutomationPeer), Windows::UI::Xaml::FrameworkElement const&);
            *value = detach_from<react::uwp::DynamicAutomationPeer>(this->shim().CreateInstance(*reinterpret_cast<Windows::UI::Xaml::FrameworkElement const*>(&owner)));
            return 0;
        }
        catch (...) { return to_hresult(); }
    }
};

}

WINRT_EXPORT namespace winrt::react::uwp {

inline DynamicAutomationPeer::DynamicAutomationPeer(Windows::UI::Xaml::FrameworkElement const& owner) :
    DynamicAutomationPeer(impl::call_factory<DynamicAutomationPeer, react::uwp::IDynamicAutomationPeerFactory>([&](auto&& f) { return f.CreateInstance(owner); }))
{}

}

namespace winrt::impl {

}

WINRT_EXPORT namespace winrt::experimental::reflect {

template <>
struct base_type<react::uwp::DynamicAutomationPeer> { using type = Windows::UI::Xaml::Automation::Peers::FrameworkElementAutomationPeer; };
}

WINRT_EXPORT namespace std {

template<> struct hash<winrt::react::uwp::IDynamicAutomationPeer> : winrt::impl::hash_base<winrt::react::uwp::IDynamicAutomationPeer> {};
template<> struct hash<winrt::react::uwp::IDynamicAutomationPeerFactory> : winrt::impl::hash_base<winrt::react::uwp::IDynamicAutomationPeerFactory> {};
template<> struct hash<winrt::react::uwp::DynamicAutomationPeer> : winrt::impl::hash_base<winrt::react::uwp::DynamicAutomationPeer> {};

}
