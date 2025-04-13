#include "Asserts.h"

#ifdef APPARITION_ASSERTS_ARE_ENABLED
#include <cstdarg>  // for variadic arguments
#include <cstdio>   // for vsnprintf

bool apparition::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreak(const unsigned int i_lineNumber, const char* const i_file, bool& io_shouldThisAssertBeIgnoredInTheFuture, const char* const i_message, ...)
{
    // Construct the message
    std::ostringstream message;
    {
        message << "An assertion failed on line (" << i_lineNumber << ") of " << i_file;
        constexpr size_t bufferSize = 1024;
        char buffer[bufferSize];

        va_list insertions;
        va_start(insertions, i_message);
        const int formattingResult = vsnprintf(buffer, bufferSize, i_message, insertions);
        va_end(insertions);

        if (formattingResult != 0)
        {
            message << ":\n\n";
            if (formattingResult > 0)
            {
                message << buffer;
                if (formattingResult >= bufferSize)
                {
                    message << "\n\n"
                        "(The internal buffer of size " << bufferSize
                        << " bytes was not big enough to hold the formatted message of length " << (formattingResult + 1) << ")";
                }
            }
            else
            {
                message << "An encoding error occurred! The unformatted message is: \"" << i_message << "\"!";
            }
        }
        else
        {
            message << "!";
        }
    }

    // Display it and break if necessary
    return ShowMessageIfAssertionIsFalseAndReturnWhetherToBreakPlatformSpecific(message, io_shouldThisAssertBeIgnoredInTheFuture);
}

// When no platform defines this platform specific function,
// this default implementation is used
#if !defined(APPARITION_OS_API_WINDOWS)
bool apparition::Asserts::ShowMessageIfAssertionIsFalseAndReturnWhetherToBreakPlatformSpecific(std::ostringstream& io_message, bool& io_shouldThisAssertBeIgnoredInTheFuture)
{
    // Always try to break at-least once per execution
    // if no platform specific implementation is found
    if (!io_shouldThisAssertBeIgnoredInTheFuture)
    {
        io_shouldThisAssertBeIgnoredInTheFuture = true;
        return true;
    }
    return false;
}
#endif

#endif