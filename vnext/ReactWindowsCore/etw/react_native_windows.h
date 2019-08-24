//**********************************************************************`
//* This is an include file generated by Message Compiler.             *`
//*                                                                    *`
//* Copyright (c) Microsoft Corporation. All Rights Reserved.          *`
//**********************************************************************`
#pragma once

//*****************************************************************************
//
// Notes on the ETW event code generated by MC:
//
// - Structures and arrays of structures are treated as an opaque binary blob.
//   The caller is responsible for packing the data for the structure into a
//   single region of memory, with no padding between values. The macro will
//   have an extra parameter for the length of the blob.
// - Arrays of nul-terminated strings must be packed by the caller into a
//   single binary blob containing the correct number of strings, with a nul
//   after each string. The size of the blob is specified in characters, and
//   includes the final nul.
// - If a SID is provided, its length will be determined by calling
//   GetLengthSid.
// - Arrays of SID are treated as a single binary blob. The caller is
//   responsible for packing the SID values into a single region of memory with
//   no padding.
// - The length attribute on the data element in the manifest is significant
//   for values with intype win:UnicodeString, win:AnsiString, or win:Binary.
//   The length attribute must be specified for win:Binary, and is optional for
//   win:UnicodeString and win:AnsiString (if no length is given, the strings
//   are assumed to be nul-terminated). For win:UnicodeString, the length is
//   measured in characters, not bytes.
// - For an array of win:UnicodeString, win:AnsiString, or win:Binary, the
//   length attribute applies to every value in the array, so every value in
//   the array must have the same length. The values in the array are provided
//   to the macro via a single pointer -- the caller is responsible for packing
//   all of the values into a single region of memory with no padding between
//   values.
// - Values of type win:CountedUnicodeString, win:CountedAnsiString, and
//   win:CountedBinary can be generated and collected on Vista or later.
//   However, they may not decode properly without the Windows 10 2018 Fall
//   Update.
// - Arrays of type win:CountedUnicodeString, win:CountedAnsiString, and
//   win:CountedBinary must be packed by the caller into a single region of
//   memory. The format for each item is a UINT16 byte-count followed by that
//   many bytes of data. When providing the array to the generated macro, you
//   must provide the total size of the packed array data, including the UINT16
//   sizes for each item. In the case of win:CountedUnicodeString, the data
//   size is specified in WCHAR (16-bit) units. In the case of
//   win:CountedAnsiString and win:CountedBinary, the data size is specified in
//   bytes.
//
//*****************************************************************************

#include <wmistr.h>
#include <evntrace.h>
#include <evntprov.h>

#if !defined(ETW_INLINE)
#define ETW_INLINE DECLSPEC_NOINLINE __inline
#endif

#if defined(__cplusplus)
extern "C" {
#endif

//
// MCGEN_DISABLE_PROVIDER_CODE_GENERATION macro:
// Define this macro to have the compiler skip the generated functions in this
// header.
//
#ifndef MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//
// MCGEN_USE_KERNEL_MODE_APIS macro:
// Controls whether the generated code uses kernel-mode or user-mode APIs.
// - Set to 0 to use Windows user-mode APIs such as EventRegister.
// - Set to 1 to use Windows kernel-mode APIs such as EtwRegister.
// Default is based on whether the _ETW_KM_ macro is defined (i.e. by wdm.h).
// Note that the APIs can also be overridden directly, e.g. by setting the
// MCGEN_EVENTWRITETRANSFER or MCGEN_EVENTREGISTER macros.
//
#ifndef MCGEN_USE_KERNEL_MODE_APIS
  #ifdef _ETW_KM_
    #define MCGEN_USE_KERNEL_MODE_APIS 1
  #else
    #define MCGEN_USE_KERNEL_MODE_APIS 0
  #endif
#endif // MCGEN_USE_KERNEL_MODE_APIS

//
// MCGEN_HAVE_EVENTSETINFORMATION macro:
// Controls how McGenEventSetInformation uses the EventSetInformation API.
// - Set to 0 to disable the use of EventSetInformation
//   (McGenEventSetInformation will always return an error).
// - Set to 1 to directly invoke MCGEN_EVENTSETINFORMATION.
// - Set to 2 to to locate EventSetInformation at runtime via GetProcAddress
//   (user-mode) or MmGetSystemRoutineAddress (kernel-mode).
// Default is determined as follows:
// - If MCGEN_EVENTSETINFORMATION has been customized, set to 1
//   (i.e. use MCGEN_EVENTSETINFORMATION).
// - Else if the target OS version has EventSetInformation, set to 1
//   (i.e. use MCGEN_EVENTSETINFORMATION).
// - Else set to 2 (i.e. try to dynamically locate EventSetInformation).
// Note that an McGenEventSetInformation function will only be generated if one
// or more provider in a manifest has provider traits.
//
#ifndef MCGEN_HAVE_EVENTSETINFORMATION
  #ifdef MCGEN_EVENTSETINFORMATION             // if MCGEN_EVENTSETINFORMATION has been customized,
    #define MCGEN_HAVE_EVENTSETINFORMATION   1 //   directly invoke MCGEN_EVENTSETINFORMATION(...).
  #elif MCGEN_USE_KERNEL_MODE_APIS             // else if using kernel-mode APIs,
    #if NTDDI_VERSION >= 0x06040000            //   if target OS is Windows 10 or later,
      #define MCGEN_HAVE_EVENTSETINFORMATION 1 //     directly invoke MCGEN_EVENTSETINFORMATION(...).
    #else                                      //   else
      #define MCGEN_HAVE_EVENTSETINFORMATION 2 //     find "EtwSetInformation" via MmGetSystemRoutineAddress.
    #endif                                     // else (using user-mode APIs)
  #else                                        //   if target OS and SDK is Windows 8 or later,
    #if WINVER >= 0x0602 && defined(EVENT_FILTER_TYPE_SCHEMATIZED)
      #define MCGEN_HAVE_EVENTSETINFORMATION 1 //     directly invoke MCGEN_EVENTSETINFORMATION(...).
    #else                                      //   else
      #define MCGEN_HAVE_EVENTSETINFORMATION 2 //     find "EventSetInformation" via GetModuleHandleExW/GetProcAddress.
    #endif
  #endif
#endif // MCGEN_HAVE_EVENTSETINFORMATION

//
// MCGEN_EVENTWRITETRANSFER macro:
// Override to use a custom API.
//
#ifndef MCGEN_EVENTWRITETRANSFER
  #if MCGEN_USE_KERNEL_MODE_APIS
    #define MCGEN_EVENTWRITETRANSFER   EtwWriteTransfer
  #else
    #define MCGEN_EVENTWRITETRANSFER   EventWriteTransfer
  #endif
#endif // MCGEN_EVENTWRITETRANSFER

//
// MCGEN_EVENTREGISTER macro:
// Override to use a custom API.
//
#ifndef MCGEN_EVENTREGISTER
  #if MCGEN_USE_KERNEL_MODE_APIS
    #define MCGEN_EVENTREGISTER        EtwRegister
  #else
    #define MCGEN_EVENTREGISTER        EventRegister
  #endif
#endif // MCGEN_EVENTREGISTER

//
// MCGEN_EVENTSETINFORMATION macro:
// Override to use a custom API.
// (McGenEventSetInformation also affected by MCGEN_HAVE_EVENTSETINFORMATION.)
//
#ifndef MCGEN_EVENTSETINFORMATION
  #if MCGEN_USE_KERNEL_MODE_APIS
    #define MCGEN_EVENTSETINFORMATION  EtwSetInformation
  #else
    #define MCGEN_EVENTSETINFORMATION  EventSetInformation
  #endif
#endif // MCGEN_EVENTSETINFORMATION

//
// MCGEN_EVENTUNREGISTER macro:
// Override to use a custom API.
//
#ifndef MCGEN_EVENTUNREGISTER
  #if MCGEN_USE_KERNEL_MODE_APIS
    #define MCGEN_EVENTUNREGISTER      EtwUnregister
  #else
    #define MCGEN_EVENTUNREGISTER      EventUnregister
  #endif
#endif // MCGEN_EVENTUNREGISTER

//
// MCGEN_PENABLECALLBACK macro:
// Override to use a custom function pointer type.
// (Should match the type used by MCGEN_EVENTREGISTER.)
//
#ifndef MCGEN_PENABLECALLBACK
  #if MCGEN_USE_KERNEL_MODE_APIS
    #define MCGEN_PENABLECALLBACK      PETWENABLECALLBACK
  #else
    #define MCGEN_PENABLECALLBACK      PENABLECALLBACK
  #endif
#endif // MCGEN_PENABLECALLBACK

//
// MCGEN_GETLENGTHSID macro:
// Override to use a custom API.
//
#ifndef MCGEN_GETLENGTHSID
  #if MCGEN_USE_KERNEL_MODE_APIS
    #define MCGEN_GETLENGTHSID(p)      RtlLengthSid((PSID)(p))
  #else
    #define MCGEN_GETLENGTHSID(p)      GetLengthSid((PSID)(p))
  #endif
#endif // MCGEN_GETLENGTHSID

//
// MCGEN_EVENT_ENABLED macro:
// Controls how the EventWrite[EventName] macros determine whether an event is
// enabled. The default behavior is for EventWrite[EventName] to use the
// EventEnabled[EventName] macros.
//
#ifndef MCGEN_EVENT_ENABLED
#define MCGEN_EVENT_ENABLED(EventName) EventEnabled##EventName()
#endif

//
// MCGEN_EVENT_BIT_SET macro:
// Implements testing a bit in an array of ULONG, optimized for CPU type.
//
#ifndef MCGEN_EVENT_BIT_SET
#  if defined(_M_IX86) || defined(_M_X64)
#    define MCGEN_EVENT_BIT_SET(EnableBits, BitPosition) ((((const unsigned char*)EnableBits)[BitPosition >> 3] & (1u << (BitPosition & 7))) != 0)
#  else
#    define MCGEN_EVENT_BIT_SET(EnableBits, BitPosition) ((EnableBits[BitPosition >> 5] & (1u << (BitPosition & 31))) != 0)
#  endif
#endif // MCGEN_EVENT_BIT_SET

//
// MCGEN_ENABLE_CHECK macro:
// Determines whether the specified event would be considered as enabled
// based on the state of the specified context. Slightly faster than calling
// McGenEventEnabled directly.
//
#ifndef MCGEN_ENABLE_CHECK
#define MCGEN_ENABLE_CHECK(Context, Descriptor) (Context.IsEnabled && McGenEventEnabled(&Context, &Descriptor))
#endif

#if !defined(MCGEN_TRACE_CONTEXT_DEF)
#define MCGEN_TRACE_CONTEXT_DEF
typedef struct _MCGEN_TRACE_CONTEXT
{
    TRACEHANDLE            RegistrationHandle;
    TRACEHANDLE            Logger;      // Used as pointer to provider traits.
    ULONGLONG              MatchAnyKeyword;
    ULONGLONG              MatchAllKeyword;
    ULONG                  Flags;
    ULONG                  IsEnabled;
    UCHAR                  Level;
    UCHAR                  Reserve;
    USHORT                 EnableBitsCount;
    PULONG                 EnableBitMask;
    const ULONGLONG*       EnableKeyWords;
    const UCHAR*           EnableLevel;
} MCGEN_TRACE_CONTEXT, *PMCGEN_TRACE_CONTEXT;
#endif // MCGEN_TRACE_CONTEXT_DEF

#if !defined(MCGEN_LEVEL_KEYWORD_ENABLED_DEF)
#define MCGEN_LEVEL_KEYWORD_ENABLED_DEF
//
// Determines whether an event with a given Level and Keyword would be
// considered as enabled based on the state of the specified context.
// Note that you may want to use MCGEN_ENABLE_CHECK instead of calling this
// function directly.
//
FORCEINLINE
BOOLEAN
McGenLevelKeywordEnabled(
    _In_ PMCGEN_TRACE_CONTEXT EnableInfo,
    _In_ UCHAR Level,
    _In_ ULONGLONG Keyword
    )
{
    //
    // Check if the event Level is lower than the level at which
    // the channel is enabled.
    // If the event Level is 0 or the channel is enabled at level 0,
    // all levels are enabled.
    //

    if ((Level <= EnableInfo->Level) || // This also covers the case of Level == 0.
        (EnableInfo->Level == 0)) {

        //
        // Check if Keyword is enabled
        //

        if ((Keyword == (ULONGLONG)0) ||
            ((Keyword & EnableInfo->MatchAnyKeyword) &&
             ((Keyword & EnableInfo->MatchAllKeyword) == EnableInfo->MatchAllKeyword))) {
            return TRUE;
        }
    }

    return FALSE;
}
#endif // MCGEN_LEVEL_KEYWORD_ENABLED_DEF

#if !defined(MCGEN_EVENT_ENABLED_DEF)
#define MCGEN_EVENT_ENABLED_DEF
//
// Determines whether the specified event would be considered as enabled based
// on the state of the specified context. Note that you may want to use
// MCGEN_ENABLE_CHECK instead of calling this function directly.
//
FORCEINLINE
BOOLEAN
McGenEventEnabled(
    _In_ PMCGEN_TRACE_CONTEXT EnableInfo,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor
    )
{
    return McGenLevelKeywordEnabled(EnableInfo, EventDescriptor->Level, EventDescriptor->Keyword);
}
#endif // MCGEN_EVENT_ENABLED_DEF

#if !defined(MCGEN_CONTROL_CALLBACK)
#define MCGEN_CONTROL_CALLBACK

DECLSPEC_NOINLINE __inline
VOID
__stdcall
McGenControlCallbackV2(
    _In_ LPCGUID SourceId,
    _In_ ULONG ControlCode,
    _In_ UCHAR Level,
    _In_ ULONGLONG MatchAnyKeyword,
    _In_ ULONGLONG MatchAllKeyword,
    _In_opt_ PEVENT_FILTER_DESCRIPTOR FilterData,
    _Inout_opt_ PVOID CallbackContext
    )
/*++

Routine Description:

    This is the notification callback for Windows Vista and later.

Arguments:

    SourceId - The GUID that identifies the session that enabled the provider.

    ControlCode - The parameter indicates whether the provider
                  is being enabled or disabled.

    Level - The level at which the event is enabled.

    MatchAnyKeyword - The bitmask of keywords that the provider uses to
                      determine the category of events that it writes.

    MatchAllKeyword - This bitmask additionally restricts the category
                      of events that the provider writes.

    FilterData - The provider-defined data.

    CallbackContext - The context of the callback that is defined when the provider
                      called EtwRegister to register itself.

Remarks:

    ETW calls this function to notify provider of enable/disable

--*/
{
    PMCGEN_TRACE_CONTEXT Ctx = (PMCGEN_TRACE_CONTEXT)CallbackContext;
    ULONG Ix;
#ifndef MCGEN_PRIVATE_ENABLE_CALLBACK_V2
    UNREFERENCED_PARAMETER(SourceId);
    UNREFERENCED_PARAMETER(FilterData);
#endif

    if (Ctx == NULL) {
        return;
    }

    switch (ControlCode) {

        case EVENT_CONTROL_CODE_ENABLE_PROVIDER:
            Ctx->Level = Level;
            Ctx->MatchAnyKeyword = MatchAnyKeyword;
            Ctx->MatchAllKeyword = MatchAllKeyword;
            Ctx->IsEnabled = EVENT_CONTROL_CODE_ENABLE_PROVIDER;

            for (Ix = 0; Ix < Ctx->EnableBitsCount; Ix += 1) {
                if (McGenLevelKeywordEnabled(Ctx, Ctx->EnableLevel[Ix], Ctx->EnableKeyWords[Ix]) != FALSE) {
                    Ctx->EnableBitMask[Ix >> 5] |= (1 << (Ix % 32));
                } else {
                    Ctx->EnableBitMask[Ix >> 5] &= ~(1 << (Ix % 32));
                }
            }
            break;

        case EVENT_CONTROL_CODE_DISABLE_PROVIDER:
            Ctx->IsEnabled = EVENT_CONTROL_CODE_DISABLE_PROVIDER;
            Ctx->Level = 0;
            Ctx->MatchAnyKeyword = 0;
            Ctx->MatchAllKeyword = 0;
            if (Ctx->EnableBitsCount > 0) {
                RtlZeroMemory(Ctx->EnableBitMask, (((Ctx->EnableBitsCount - 1) / 32) + 1) * sizeof(ULONG));
            }
            break;

        default:
            break;
    }

#ifdef MCGEN_PRIVATE_ENABLE_CALLBACK_V2
    //
    // Call user defined callback
    //
    MCGEN_PRIVATE_ENABLE_CALLBACK_V2(
        SourceId,
        ControlCode,
        Level,
        MatchAnyKeyword,
        MatchAllKeyword,
        FilterData,
        CallbackContext
        );
#endif // MCGEN_PRIVATE_ENABLE_CALLBACK_V2

    return;
}

#endif // MCGEN_CONTROL_CALLBACK

#ifndef McGenEventWrite_def
#define McGenEventWrite_def
DECLSPEC_NOINLINE __inline
ULONG __stdcall
McGenEventWrite(
    _In_ PMCGEN_TRACE_CONTEXT Context,
    _In_ PCEVENT_DESCRIPTOR Descriptor,
    _In_opt_ LPCGUID ActivityId,
    _In_range_(1, 128) ULONG EventDataCount,
    _Inout_updates_(EventDataCount) EVENT_DATA_DESCRIPTOR* EventData
    )
{
    const USHORT UNALIGNED* Traits;

    // Some customized MCGEN_EVENTWRITETRANSFER macros might ignore ActivityId.
    UNREFERENCED_PARAMETER(ActivityId);

    Traits = (const USHORT UNALIGNED*)(UINT_PTR)Context->Logger;

    if (Traits == NULL) {
        EventData[0].Ptr = 0;
        EventData[0].Size = 0;
        EventData[0].Reserved = 0;
    } else {
        EventData[0].Ptr = (ULONG_PTR)Traits;
        EventData[0].Size = *Traits;
        EventData[0].Reserved = 2; // EVENT_DATA_DESCRIPTOR_TYPE_PROVIDER_METADATA
    }

    return MCGEN_EVENTWRITETRANSFER(
        Context->RegistrationHandle,
        Descriptor,
        ActivityId,
        NULL,
        EventDataCount,
        EventData);
}
#endif // McGenEventWrite_def

#if !defined(McGenEventRegisterUnregister)
#define McGenEventRegisterUnregister

#pragma warning(push)
#pragma warning(disable:6103)
DECLSPEC_NOINLINE __inline
ULONG __stdcall
McGenEventRegister(
    _In_ LPCGUID ProviderId,
    _In_opt_ MCGEN_PENABLECALLBACK EnableCallback,
    _In_opt_ PVOID CallbackContext,
    _Inout_ PREGHANDLE RegHandle
    )
/*++

Routine Description:

    This function registers the provider with ETW.

Arguments:

    ProviderId - Provider ID to register with ETW.

    EnableCallback - Callback to be used.

    CallbackContext - Context for the callback.

    RegHandle - Pointer to registration handle.

Remarks:

    Should not be called if the provider is already registered (i.e. should not
    be called if *RegHandle != 0). Repeatedly registering a provider is a bug
    and may indicate a race condition. However, for compatibility with previous
    behavior, this function will return SUCCESS in this case.

--*/
{
    ULONG Error;

    if (*RegHandle != 0)
    {
        Error = 0; // ERROR_SUCCESS
    }
    else
    {
        Error = MCGEN_EVENTREGISTER(ProviderId, EnableCallback, CallbackContext, RegHandle);
    }

    return Error;
}
#pragma warning(pop)

DECLSPEC_NOINLINE __inline
ULONG __stdcall
McGenEventUnregister(_Inout_ PREGHANDLE RegHandle)
/*++

Routine Description:

    Unregister from ETW and set *RegHandle = 0.

Arguments:

    RegHandle - the pointer to the provider registration handle

Remarks:

    If provider has not been registered (i.e. if *RegHandle == 0),
    return SUCCESS. It is safe to call McGenEventUnregister even if the
    call to McGenEventRegister returned an error.

--*/
{
    ULONG Error;

    if(*RegHandle == 0)
    {
        Error = 0; // ERROR_SUCCESS
    }
    else
    {
        Error = MCGEN_EVENTUNREGISTER(*RegHandle);
        *RegHandle = (REGHANDLE)0;
    }

    return Error;
}

#endif // McGenEventRegisterUnregister

#endif // MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Provider "React-Native-Windows-Provider" event count 14
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Provider GUID = cec49226-329e-4ea2-a16a-c37c6c0b2cd7
EXTERN_C __declspec(selectany) const GUID REACT_NATIVE_WINDOWS = {0xcec49226, 0x329e, 0x4ea2, {0xa1, 0x6a, 0xc3, 0x7c, 0x6c, 0x0b, 0x2c, 0xd7}};

#ifndef REACT_NATIVE_WINDOWS_Traits
#define REACT_NATIVE_WINDOWS_Traits NULL
#endif // REACT_NATIVE_WINDOWS_Traits

//
// Tasks
//
#define REACT_NATIVE_WINDOWS_TASK_Systrace 0x1

//
// Event Descriptors
//
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_BEGIN_SECTION = {0x1, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_BEGIN_SECTION_value 0x1
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_END_SECTION = {0x2, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_END_SECTION_value 0x2
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_ASYNC_BEGIN_SECTION = {0x3, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_ASYNC_BEGIN_SECTION_value 0x3
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_ASYNC_END_SECTION = {0x4, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_ASYNC_END_SECTION_value 0x4
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_ASYNC_BEGIN_FLOW = {0x5, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_ASYNC_BEGIN_FLOW_value 0x5
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_ASYNC_END_FLOW = {0x6, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_ASYNC_END_FLOW_value 0x6
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR JS_COUNTER = {0x7, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define JS_COUNTER_value 0x7
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_BEGIN_SECTION = {0x8, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_BEGIN_SECTION_value 0x8
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_END_SECTION = {0x9, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_END_SECTION_value 0x9
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_ASYNC_BEGIN_SECTION = {0xa, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_ASYNC_BEGIN_SECTION_value 0xa
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_ASYNC_END_SECTION = {0xb, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_ASYNC_END_SECTION_value 0xb
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_ASYNC_BEGIN_FLOW = {0xc, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_ASYNC_BEGIN_FLOW_value 0xc
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_ASYNC_END_FLOW = {0xd, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_ASYNC_END_FLOW_value 0xd
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR NATIVE_COUNTER = {0xe, 0x0, 0x0, 0x4, 0x0, 0x1, 0x0};
#define NATIVE_COUNTER_value 0xe

//
// MCGEN_DISABLE_PROVIDER_CODE_GENERATION macro:
// Define this macro to have the compiler skip the generated functions in this
// header.
//
#ifndef MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//
// Event Enablement Bits
//
EXTERN_C __declspec(selectany) DECLSPEC_CACHEALIGN ULONG React_Native_Windows_ProviderEnableBits[1];
EXTERN_C __declspec(selectany) const ULONGLONG React_Native_Windows_ProviderKeywords[1] = {0x0};
EXTERN_C __declspec(selectany) const unsigned char React_Native_Windows_ProviderLevels[1] = {4};

//
// Provider context
//
EXTERN_C __declspec(selectany) MCGEN_TRACE_CONTEXT REACT_NATIVE_WINDOWS_Context = {0, (ULONG_PTR)REACT_NATIVE_WINDOWS_Traits, 0, 0, 0, 0, 0, 0, 1, React_Native_Windows_ProviderEnableBits, React_Native_Windows_ProviderKeywords, React_Native_Windows_ProviderLevels};

//
// Provider REGHANDLE
//
#define React_Native_Windows_ProviderHandle (REACT_NATIVE_WINDOWS_Context.RegistrationHandle)

//
// This macro is set to 0, indicating that the EventWrite[Name] macros do not
// have an Activity parameter. This is controlled by the -km and -um options.
//
#define REACT_NATIVE_WINDOWS_EventWriteActivity 0

//
// Register with ETW using the control GUID specified in the manifest.
// Invoke this macro during module initialization (i.e. program startup,
// DLL process attach, or driver load) to initialize the provider.
// Note that if this function returns an error, the error means that
// will not work, but no action needs to be taken -- even if EventRegister
// returns an error, it is generally safe to use EventWrite and
// EventUnregister macros (they will be no-ops if EventRegister failed).
//
#ifndef EventRegisterReact_Native_Windows_Provider
#define EventRegisterReact_Native_Windows_Provider() McGenEventRegister(&REACT_NATIVE_WINDOWS, McGenControlCallbackV2, &REACT_NATIVE_WINDOWS_Context, &React_Native_Windows_ProviderHandle)
#endif

//
// Register with ETW using a specific control GUID (i.e. a GUID other than what
// is specified in the manifest). Advanced scenarios only.
//
#ifndef EventRegisterByGuidReact_Native_Windows_Provider
#define EventRegisterByGuidReact_Native_Windows_Provider(Guid) McGenEventRegister(&(Guid), McGenControlCallbackV2, &REACT_NATIVE_WINDOWS_Context, &React_Native_Windows_ProviderHandle)
#endif

//
// Unregister with ETW and close the provider.
// Invoke this macro during module shutdown (i.e. program exit, DLL process
// detach, or driver unload) to unregister the provider.
// Note that you MUST call EventUnregister before DLL or driver unload
// (not optional): failure to unregister a provider before DLL or driver unload
// will result in crashes.
//
#ifndef EventUnregisterReact_Native_Windows_Provider
#define EventUnregisterReact_Native_Windows_Provider() McGenEventUnregister(&React_Native_Windows_ProviderHandle)
#endif

//
// Enablement check macro for JS_BEGIN_SECTION
//
#define EventEnabledJS_BEGIN_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_BEGIN_SECTION
//
#define EventWriteJS_BEGIN_SECTION(tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
        MCGEN_EVENT_ENABLED(JS_BEGIN_SECTION) \
        ? McTemplateU0xsssssssss(&REACT_NATIVE_WINDOWS_Context, &JS_BEGIN_SECTION, tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) : 0
#define EventWriteJS_BEGIN_SECTION_AssumeEnabled(tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
        McTemplateU0xsssssssss(&REACT_NATIVE_WINDOWS_Context, &JS_BEGIN_SECTION, tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)

//
// Enablement check macro for JS_END_SECTION
//
#define EventEnabledJS_END_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_END_SECTION
//
#define EventWriteJS_END_SECTION(tag, profileName, duration) \
        MCGEN_EVENT_ENABLED(JS_END_SECTION) \
        ? McTemplateU0xsg(&REACT_NATIVE_WINDOWS_Context, &JS_END_SECTION, tag, profileName, duration) : 0
#define EventWriteJS_END_SECTION_AssumeEnabled(tag, profileName, duration) \
        McTemplateU0xsg(&REACT_NATIVE_WINDOWS_Context, &JS_END_SECTION, tag, profileName, duration)

//
// Enablement check macro for JS_ASYNC_BEGIN_SECTION
//
#define EventEnabledJS_ASYNC_BEGIN_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_ASYNC_BEGIN_SECTION
//
#define EventWriteJS_ASYNC_BEGIN_SECTION(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(JS_ASYNC_BEGIN_SECTION) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_BEGIN_SECTION, tag, profileName, cookie, duration) : 0
#define EventWriteJS_ASYNC_BEGIN_SECTION_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_BEGIN_SECTION, tag, profileName, cookie, duration)

//
// Enablement check macro for JS_ASYNC_END_SECTION
//
#define EventEnabledJS_ASYNC_END_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_ASYNC_END_SECTION
//
#define EventWriteJS_ASYNC_END_SECTION(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(JS_ASYNC_END_SECTION) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_END_SECTION, tag, profileName, cookie, duration) : 0
#define EventWriteJS_ASYNC_END_SECTION_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_END_SECTION, tag, profileName, cookie, duration)

//
// Enablement check macro for JS_ASYNC_BEGIN_FLOW
//
#define EventEnabledJS_ASYNC_BEGIN_FLOW() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_ASYNC_BEGIN_FLOW
//
#define EventWriteJS_ASYNC_BEGIN_FLOW(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(JS_ASYNC_BEGIN_FLOW) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_BEGIN_FLOW, tag, profileName, cookie, duration) : 0
#define EventWriteJS_ASYNC_BEGIN_FLOW_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_BEGIN_FLOW, tag, profileName, cookie, duration)

//
// Enablement check macro for JS_ASYNC_END_FLOW
//
#define EventEnabledJS_ASYNC_END_FLOW() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_ASYNC_END_FLOW
//
#define EventWriteJS_ASYNC_END_FLOW(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(JS_ASYNC_END_FLOW) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_END_FLOW, tag, profileName, cookie, duration) : 0
#define EventWriteJS_ASYNC_END_FLOW_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &JS_ASYNC_END_FLOW, tag, profileName, cookie, duration)

//
// Enablement check macro for JS_COUNTER
//
#define EventEnabledJS_COUNTER() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for JS_COUNTER
//
#define EventWriteJS_COUNTER(tag, profileName, value) \
        MCGEN_EVENT_ENABLED(JS_COUNTER) \
        ? McTemplateU0xsd(&REACT_NATIVE_WINDOWS_Context, &JS_COUNTER, tag, profileName, value) : 0
#define EventWriteJS_COUNTER_AssumeEnabled(tag, profileName, value) \
        McTemplateU0xsd(&REACT_NATIVE_WINDOWS_Context, &JS_COUNTER, tag, profileName, value)

//
// Enablement check macro for NATIVE_BEGIN_SECTION
//
#define EventEnabledNATIVE_BEGIN_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_BEGIN_SECTION
//
#define EventWriteNATIVE_BEGIN_SECTION(tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
        MCGEN_EVENT_ENABLED(NATIVE_BEGIN_SECTION) \
        ? McTemplateU0xsssssssss(&REACT_NATIVE_WINDOWS_Context, &NATIVE_BEGIN_SECTION, tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) : 0
#define EventWriteNATIVE_BEGIN_SECTION_AssumeEnabled(tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
        McTemplateU0xsssssssss(&REACT_NATIVE_WINDOWS_Context, &NATIVE_BEGIN_SECTION, tag, profileName, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)

//
// Enablement check macro for NATIVE_END_SECTION
//
#define EventEnabledNATIVE_END_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_END_SECTION
//
#define EventWriteNATIVE_END_SECTION(tag, profileName, duration) \
        MCGEN_EVENT_ENABLED(NATIVE_END_SECTION) \
        ? McTemplateU0xsg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_END_SECTION, tag, profileName, duration) : 0
#define EventWriteNATIVE_END_SECTION_AssumeEnabled(tag, profileName, duration) \
        McTemplateU0xsg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_END_SECTION, tag, profileName, duration)

//
// Enablement check macro for NATIVE_ASYNC_BEGIN_SECTION
//
#define EventEnabledNATIVE_ASYNC_BEGIN_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_ASYNC_BEGIN_SECTION
//
#define EventWriteNATIVE_ASYNC_BEGIN_SECTION(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(NATIVE_ASYNC_BEGIN_SECTION) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_BEGIN_SECTION, tag, profileName, cookie, duration) : 0
#define EventWriteNATIVE_ASYNC_BEGIN_SECTION_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_BEGIN_SECTION, tag, profileName, cookie, duration)

//
// Enablement check macro for NATIVE_ASYNC_END_SECTION
//
#define EventEnabledNATIVE_ASYNC_END_SECTION() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_ASYNC_END_SECTION
//
#define EventWriteNATIVE_ASYNC_END_SECTION(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(NATIVE_ASYNC_END_SECTION) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_END_SECTION, tag, profileName, cookie, duration) : 0
#define EventWriteNATIVE_ASYNC_END_SECTION_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_END_SECTION, tag, profileName, cookie, duration)

//
// Enablement check macro for NATIVE_ASYNC_BEGIN_FLOW
//
#define EventEnabledNATIVE_ASYNC_BEGIN_FLOW() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_ASYNC_BEGIN_FLOW
//
#define EventWriteNATIVE_ASYNC_BEGIN_FLOW(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(NATIVE_ASYNC_BEGIN_FLOW) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_BEGIN_FLOW, tag, profileName, cookie, duration) : 0
#define EventWriteNATIVE_ASYNC_BEGIN_FLOW_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_BEGIN_FLOW, tag, profileName, cookie, duration)

//
// Enablement check macro for NATIVE_ASYNC_END_FLOW
//
#define EventEnabledNATIVE_ASYNC_END_FLOW() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_ASYNC_END_FLOW
//
#define EventWriteNATIVE_ASYNC_END_FLOW(tag, profileName, cookie, duration) \
        MCGEN_EVENT_ENABLED(NATIVE_ASYNC_END_FLOW) \
        ? McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_END_FLOW, tag, profileName, cookie, duration) : 0
#define EventWriteNATIVE_ASYNC_END_FLOW_AssumeEnabled(tag, profileName, cookie, duration) \
        McTemplateU0xsdg(&REACT_NATIVE_WINDOWS_Context, &NATIVE_ASYNC_END_FLOW, tag, profileName, cookie, duration)

//
// Enablement check macro for NATIVE_COUNTER
//
#define EventEnabledNATIVE_COUNTER() MCGEN_EVENT_BIT_SET(React_Native_Windows_ProviderEnableBits, 0)

//
// Event write macros for NATIVE_COUNTER
//
#define EventWriteNATIVE_COUNTER(tag, profileName, value) \
        MCGEN_EVENT_ENABLED(NATIVE_COUNTER) \
        ? McTemplateU0xsd(&REACT_NATIVE_WINDOWS_Context, &NATIVE_COUNTER, tag, profileName, value) : 0
#define EventWriteNATIVE_COUNTER_AssumeEnabled(tag, profileName, value) \
        McTemplateU0xsd(&REACT_NATIVE_WINDOWS_Context, &NATIVE_COUNTER, tag, profileName, value)

#endif // MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//
// MCGEN_DISABLE_PROVIDER_CODE_GENERATION macro:
// Define this macro to have the compiler skip the generated functions in this
// header.
//
#ifndef MCGEN_DISABLE_PROVIDER_CODE_GENERATION

//
// Template Functions
//
//
//Template from manifest : tidCounter
//
#ifndef McTemplateU0xsd_def
#define McTemplateU0xsd_def
ETW_INLINE
ULONG
McTemplateU0xsd(
    _In_ PMCGEN_TRACE_CONTEXT Context,
    _In_ PCEVENT_DESCRIPTOR Descriptor,
    _In_ const unsigned __int64  _Arg0,
    _In_opt_ PCSTR  _Arg1,
    _In_ const signed int  _Arg2
    )
{
#define McTemplateU0xsd_ARGCOUNT 3

    EVENT_DATA_DESCRIPTOR EventData[McTemplateU0xsd_ARGCOUNT + 1];

    EventDataDescCreate(&EventData[1],&_Arg0, sizeof(const unsigned __int64)  );

    EventDataDescCreate(&EventData[2],
                        (_Arg1 != NULL) ? _Arg1 : "NULL",
                        (_Arg1 != NULL) ? (ULONG)((strlen(_Arg1) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[3],&_Arg2, sizeof(const signed int)  );

    return McGenEventWrite(Context, Descriptor, NULL, McTemplateU0xsd_ARGCOUNT + 1, EventData);
}
#endif // McTemplateU0xsd_def

//
//Template from manifest : tidAsyncSection
//
#ifndef McTemplateU0xsdg_def
#define McTemplateU0xsdg_def
ETW_INLINE
ULONG
McTemplateU0xsdg(
    _In_ PMCGEN_TRACE_CONTEXT Context,
    _In_ PCEVENT_DESCRIPTOR Descriptor,
    _In_ const unsigned __int64  _Arg0,
    _In_opt_ PCSTR  _Arg1,
    _In_ const signed int  _Arg2,
    _In_ const double  _Arg3
    )
{
#define McTemplateU0xsdg_ARGCOUNT 4

    EVENT_DATA_DESCRIPTOR EventData[McTemplateU0xsdg_ARGCOUNT + 1];

    EventDataDescCreate(&EventData[1],&_Arg0, sizeof(const unsigned __int64)  );

    EventDataDescCreate(&EventData[2],
                        (_Arg1 != NULL) ? _Arg1 : "NULL",
                        (_Arg1 != NULL) ? (ULONG)((strlen(_Arg1) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[3],&_Arg2, sizeof(const signed int)  );

    EventDataDescCreate(&EventData[4],&_Arg3, sizeof(const double)  );

    return McGenEventWrite(Context, Descriptor, NULL, McTemplateU0xsdg_ARGCOUNT + 1, EventData);
}
#endif // McTemplateU0xsdg_def

//
//Template from manifest : tidEndSection
//
#ifndef McTemplateU0xsg_def
#define McTemplateU0xsg_def
ETW_INLINE
ULONG
McTemplateU0xsg(
    _In_ PMCGEN_TRACE_CONTEXT Context,
    _In_ PCEVENT_DESCRIPTOR Descriptor,
    _In_ const unsigned __int64  _Arg0,
    _In_opt_ PCSTR  _Arg1,
    _In_ const double  _Arg2
    )
{
#define McTemplateU0xsg_ARGCOUNT 3

    EVENT_DATA_DESCRIPTOR EventData[McTemplateU0xsg_ARGCOUNT + 1];

    EventDataDescCreate(&EventData[1],&_Arg0, sizeof(const unsigned __int64)  );

    EventDataDescCreate(&EventData[2],
                        (_Arg1 != NULL) ? _Arg1 : "NULL",
                        (_Arg1 != NULL) ? (ULONG)((strlen(_Arg1) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[3],&_Arg2, sizeof(const double)  );

    return McGenEventWrite(Context, Descriptor, NULL, McTemplateU0xsg_ARGCOUNT + 1, EventData);
}
#endif // McTemplateU0xsg_def

//
//Template from manifest : tidBeginSection
//
#ifndef McTemplateU0xsssssssss_def
#define McTemplateU0xsssssssss_def
ETW_INLINE
ULONG
McTemplateU0xsssssssss(
    _In_ PMCGEN_TRACE_CONTEXT Context,
    _In_ PCEVENT_DESCRIPTOR Descriptor,
    _In_ const unsigned __int64  _Arg0,
    _In_opt_ PCSTR  _Arg1,
    _In_opt_ PCSTR  _Arg2,
    _In_opt_ PCSTR  _Arg3,
    _In_opt_ PCSTR  _Arg4,
    _In_opt_ PCSTR  _Arg5,
    _In_opt_ PCSTR  _Arg6,
    _In_opt_ PCSTR  _Arg7,
    _In_opt_ PCSTR  _Arg8,
    _In_opt_ PCSTR  _Arg9
    )
{
#define McTemplateU0xsssssssss_ARGCOUNT 10

    EVENT_DATA_DESCRIPTOR EventData[McTemplateU0xsssssssss_ARGCOUNT + 1];

    EventDataDescCreate(&EventData[1],&_Arg0, sizeof(const unsigned __int64)  );

    EventDataDescCreate(&EventData[2],
                        (_Arg1 != NULL) ? _Arg1 : "NULL",
                        (_Arg1 != NULL) ? (ULONG)((strlen(_Arg1) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[3],
                        (_Arg2 != NULL) ? _Arg2 : "NULL",
                        (_Arg2 != NULL) ? (ULONG)((strlen(_Arg2) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[4],
                        (_Arg3 != NULL) ? _Arg3 : "NULL",
                        (_Arg3 != NULL) ? (ULONG)((strlen(_Arg3) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[5],
                        (_Arg4 != NULL) ? _Arg4 : "NULL",
                        (_Arg4 != NULL) ? (ULONG)((strlen(_Arg4) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[6],
                        (_Arg5 != NULL) ? _Arg5 : "NULL",
                        (_Arg5 != NULL) ? (ULONG)((strlen(_Arg5) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[7],
                        (_Arg6 != NULL) ? _Arg6 : "NULL",
                        (_Arg6 != NULL) ? (ULONG)((strlen(_Arg6) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[8],
                        (_Arg7 != NULL) ? _Arg7 : "NULL",
                        (_Arg7 != NULL) ? (ULONG)((strlen(_Arg7) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[9],
                        (_Arg8 != NULL) ? _Arg8 : "NULL",
                        (_Arg8 != NULL) ? (ULONG)((strlen(_Arg8) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    EventDataDescCreate(&EventData[10],
                        (_Arg9 != NULL) ? _Arg9 : "NULL",
                        (_Arg9 != NULL) ? (ULONG)((strlen(_Arg9) + 1) * sizeof(char)) : (ULONG)sizeof("NULL"));

    return McGenEventWrite(Context, Descriptor, NULL, McTemplateU0xsssssssss_ARGCOUNT + 1, EventData);
}
#endif // McTemplateU0xsssssssss_def

#endif // MCGEN_DISABLE_PROVIDER_CODE_GENERATION

#if defined(__cplusplus)
};
#endif

#define MSG_opcode_Info                      0x30000000L
#define MSG_level_Informational              0x50000004L
