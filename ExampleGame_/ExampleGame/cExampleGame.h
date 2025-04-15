#pragma once

#include "Engine/Results/Results.h"

namespace apparition
{
    namespace Results
    {
        namespace Application
        {
            // You can add specific results for your application here:
            //    * The System should always be Application
            //    * The __LINE__ macro is used to make sure that every result has a unique ID.
            //        That means, however, that all results _must_ be defined in this single file
            //        or else you could have two different ones with equal IDs.
            //    * Note that you can define multiple Success codes.
            //        This can be used if the caller may want to know more about how a function succeeded.
            constexpr cResult FileReadFailed(eResult::IsFailure, eSystem::Application, __LINE__, static_cast<uint8_t>(eSeverity::Error));
        }
    }
}