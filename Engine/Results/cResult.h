/*
    The cResult class defines the custom Result a function can return
    and the functions to understand its meaning
*/

#ifndef APPARITION_RESULTS_CRESULT_H
#define APPARITION_RESULTS_CRESULT_H

#include <cstdint>

namespace apparition
{
    namespace Results
    {
        // Usually all that a caller cares about is whether a result is a success or a failure
        enum class eResult : bool
        {
            IsSuccess = true,
            IsFailure = false
        };

        // A result can come from any "system" enumerated below:
        enum class eSystem : uint8_t
        {
            General,        // Generic results that any system can use

            Application,    // You can use this to create errors specific to your game
            Graphics,
            Logging,
            Platform,

            Count           // This must be last
        };
        static_assert(static_cast<uint8_t>(eSystem::Count) <= 0x80, "A result's system ID must fit into 7 bits");

        // The "severity" of a result is an unsigned 8-bit value where larger values correspond to bigger problems:
        enum class eSeverity : uint8_t
        {
            AllOkay = 0,        // Nothing went wrong
            Warning = 1,        // This could be used with success or failure
            Error = 127,      // Something went wrong and the caller should take action accordingly
            Fatal = 255       // The program will exit or crash
        };

        // Although the severities named above are explicitly provided
        // the actual severity in a result can be any unsigned 8-bit value
        // indicating how relatively severe it is compared to other results

        // This class is just a wrapper for a 32-bit unsigned value, where different bits have different meanings
        // Since all the functions are constexpr they need to inlined because if one wants compile-time results the definitions should be visible in the header file
        class cResult final
        {
        public:
            // A result will implicitly convert to true (success) or false (failure)
            constexpr operator bool() const { return IsSuccess(); }

            // Explicit functions are also provided for cases where they makes code more readable
            constexpr bool IsFailure() const { return !IsSuccess(); }

            // The top bit indicates success if set (or failure if not set)
            #define APPARITION_RESULTS_SUCCESS_MASK 0x80000000

            constexpr bool IsSuccess() const
            {
                return (m_Value & APPARITION_RESULTS_SUCCESS_MASK) != 0;
            }

            // The next 7 bits are the system that defined the result
            #define APPARITION_RESULTS_SYSTEM_MASK 0x7f000000
            #define APPARITION_RESULTS_SYSTEM_SHIFT 24

            constexpr eSystem GetSystem() const
            {
                return static_cast<eSystem>((m_Value & APPARITION_RESULTS_SYSTEM_MASK) >> APPARITION_RESULTS_SYSTEM_SHIFT);
            }

            // The next 8 bits are the relative severity of the result
            #define APPARITION_RESULTS_SEVERITY_MASK 0x00ff0000
            #define APPARITION_RESULTS_SEVERITY_SHIFT 16

            constexpr uint8_t GetSeverity() const
            {
                return static_cast<uint8_t>((m_Value & APPARITION_RESULTS_SEVERITY_MASK) >> APPARITION_RESULTS_SEVERITY_SHIFT);
            }

            // The final 16 bits are an arbitrary ID assigned by the system when defining the result.
            // No function is provided to get the ID.
            // Instead, the caller is expected to compare the entire result against the named result object.
            // e.g.: if (myResult == apparition::Results::OutOfMemory)

            constexpr bool operator ==(const cResult i_rhs) const { return m_Value == i_rhs.m_Value; }
            constexpr bool operator !=(const cResult i_rhs) const { return m_Value != i_rhs.m_Value; }

            // Defines a result
            explicit constexpr cResult(const eResult i_isSuccess,
                                       const eSystem i_system,
                                       const uint16_t i_id,
                                       const uint8_t i_severity = static_cast<uint8_t>(eSeverity::Error)) :
                m_Value((static_cast<bool>(i_isSuccess) ? APPARITION_RESULTS_SUCCESS_MASK : 0u) |
                        (static_cast<uint8_t>(i_system) << APPARITION_RESULTS_SYSTEM_SHIFT) |
                        (i_severity << APPARITION_RESULTS_SEVERITY_SHIFT) |
                        i_id) {}

            #define APPARITION_RESULTS_UNDEFINED_ID ~0u

            // An undefined result is treated as an error
            explicit constexpr cResult() :
                cResult(eResult::IsFailure, eSystem::General, static_cast<uint16_t>(APPARITION_RESULTS_UNDEFINED_ID)) {}

            #undef APPARITION_RESULTS_SUCCESS_MASK
            #undef APPARITION_RESULTS_SYSTEM_MASK
            #undef APPARITION_RESULTS_SYSTEM_SHIFT
            #undef APPARITION_RESULTS_SEVERITY_MASK
            #undef APPARITION_RESULTS_SEVERITY_SHIFT
            #undef APPARITION_RESULTS_UNDEFINED_ID

        private:
            uint32_t m_Value;
        };
    }
}

#endif