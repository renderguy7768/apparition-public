#include "../Asserts.h"

#if defined(APPARITION_ASSERTS_ARE_ENABLED) && defined(APPARITION_OS_API_WINDOWS)
#include "Engine/Windows/Includes.h"

namespace
{
    static constexpr uint32_t s_MessageBoxType    = MB_YESNOCANCEL;
    static constexpr char     s_MessageBoxTitle[] = "Assertion Failed!";
}

bool apparition::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreakPlatformSpecific(std::ostringstream& io_message, bool& io_shouldThisAssertBeIgnoredInTheFuture)
{
    io_message << "\n\n";

#ifdef APPARITION_ASSERTS_SHOULD_PRINT_TO_DEBUGGER
    if (IsDebuggerPresent() != FALSE)
    {
        OutputDebugStringA(io_message.str().c_str());
    }
#endif

    io_message << "Do you want to break into the debugger (if it's attached)?"
        " Choose \"Yes\" to break, \"No\" to continue, or \"Cancel\" to disable this assertion until the program exits.";
    const HWND activeWindowHandleInThisThread = GetActiveWindow(); // Can be NULL if window is out of input focus
    const int result = MessageBoxA(activeWindowHandleInThisThread, io_message.str().c_str(), s_MessageBoxTitle, s_MessageBoxType);
    if ((result == IDYES) ||
        // MessageBox() returns 0 on failure; if this happens the code breaks rather than trying to diagnose why
        (result == 0))
    {
        return true;
    }

    if (result == IDCANCEL)
    {
        io_shouldThisAssertBeIgnoredInTheFuture = true;
    }
    return false;
}
#endif
