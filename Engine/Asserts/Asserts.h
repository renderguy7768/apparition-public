/*
    This file provides more advanced assert functionality than the standard library

    Assertions (or "asserts") are a run-time mechanism of error checking
    that are used during development to verify programmer assumptions.
    You assert that some condition should be true,
    and if that assertion is false the code will stop immediately and tell you so,
    allowing you to find the bug and fix it.
    Asserts are not included in the shipping game (for performance reasons),
    and so they are not a replacement for standard error checking.
    Instead, you should use them as "sanity checks"
    to make sure that something that should never happen never does.
*/

#ifndef APPARITION_ASSERTS_H
#define APPARITION_ASSERTS_H

#include "Configuration.h"

#ifdef APPARITION_ASSERTS_ARE_ENABLED
#include <sstream> // for std::ostringstream because it can't be forward declared easily

namespace apparition
{
    namespace Asserts
    {
        bool ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak(const unsigned int i_lineNumber, const char* const i_file, bool& io_shouldThisAssertBeIgnoredInTheFuture, const char* const i_message, ...);

        bool ShowMessageIfAssertionIsFalseAndReturnWhetherToBreakPlatformSpecific(std::ostringstream& io_message, bool& io_shouldThisAssertBeIgnoredInTheFuture);
    }
}

// Breaking could be defined in Asserts.cpp to avoid any platform-specific code here in the header file, but then the debugger would break in Asserts.cpp rather than in the file where the failed assert is
#if defined(APPARITION_OS_API_WINDOWS)
#include "Engine/Windows/Includes.h"
#include <intrin.h>
#define APPARITION_ASSERTS_BREAK() \
do \
{ \
    if (IsDebuggerPresent() != FALSE) \
    { \
        __debugbreak(); \
    } \
} while (false)
#else
#error "No implementation exists for breaking in the debugger when an assert fails"
#endif

#define APPARITION_ASSERT(i_assertion) \
do \
{ \
    static bool shouldThisAssertBeIgnored = false; \
    if (!shouldThisAssertBeIgnored && !static_cast<bool>(i_assertion) && apparition::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak(__LINE__, __FILE__, shouldThisAssertBeIgnored, "")) \
    { \
        APPARITION_ASSERTS_BREAK(); \
    } \
} while (false)

#define APPARITION_ASSERTF(i_assertion, i_messageToDisplayWhenAssertionIsFalse, ...) \
do \
{ \
    static bool shouldThisAssertBeIgnored = false; \
    if (!shouldThisAssertBeIgnored && !static_cast<bool>(i_assertion) && apparition::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak(__LINE__, __FILE__, shouldThisAssertBeIgnored, i_messageToDisplayWhenAssertionIsFalse, __VA_ARGS__)) \
    { \
        APPARITION_ASSERTS_BREAK(); \
    } \
} while (false)

#else
// The macros do nothing when asserts aren't enabled
#define APPARITION_ASSERT(i_assertion) (void)0
#define APPARITION_ASSERTF(i_assertion, i_messageToDisplayWhenAssertionIsFalse, ...) (void)0
#endif

#endif
