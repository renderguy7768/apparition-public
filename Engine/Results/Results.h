/*
    This file defines general results that any system can use
*/

#ifndef APPARITION_RESULTS_H
#define APPARITION_RESULTS_H

#include "cResult.h"

namespace apparition
{
    namespace Results
    {
        // General non-specific success/failure results
        constexpr cResult Success(eResult::IsSuccess, eSystem::General, __LINE__, static_cast<uint8_t>(eSeverity::AllOkay));
        constexpr cResult Failure(eResult::IsFailure, eSystem::General, __LINE__);

        // This is returned when something is wrong with a file
        // (the file exists, but there is something wrong with its contents e.g. it is formatted incorrectly)
        constexpr cResult InvalidFile(eResult::IsFailure, eSystem::General, __LINE__);

        // This is returned when a required file doesn't exist
        constexpr cResult FileDoesntExist(eResult::IsFailure, eSystem::General, __LINE__);

        // This is returned when something fails because not enough memory was available
        constexpr cResult OutOfMemory(eResult::IsFailure, eSystem::General, __LINE__);

        // This is returned when something fails because some context-specific amount of time passed
        // (e.g. the task might have succeeded if more time had been spent,
        // the task might succeed if tried again at a later time, etc.)
        constexpr cResult TimeOut(eResult::IsFailure, eSystem::General, __LINE__, static_cast<uint8_t>(eSeverity::Warning));

        // This can be compared against if the caller wants to know if no value was assigned
        constexpr cResult Undefined;
    }
}

#endif