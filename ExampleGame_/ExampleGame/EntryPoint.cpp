#include "Engine/Asserts/Asserts.h"
#include "Engine/Results/Results.h"
#include "cExampleGame.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <malloc.h>
#include <string>

#pragma region TestingVanillaAsserts
static void TestingVanillaAsserts(void)
{
    std::cout << "Testing asserts" << std::endl;

    // These will never assert
    assert(true);
    assert(1);
    assert(-157);
    assert(11 == 11 && "Will never assert cause 11 equals 11");

    // FIX FIRST TO SEE NEXT ASSERT!!!
    // These should always assert
    assert(false);
    assert(0);
    // CANNOT WRITE FORMATTED MESSAGES
    // assert(15 == 14, "Will always assert cause %d not equal to %d", 15, 14);
    assert(15 == 14 && "Will always assert cause 15 not equal to 14");

    for (size_t i = 0; i < 100; ++i)
    {
        // CANNOT WRITE FORMATTED MESSAGES
        // assert(false, "Assert in a loop: ITERATION = %zu", i);
        assert(false && "Assert in a loop: ITERATION = %zu" && i);
    }
}
#pragma endregion

#pragma region TestingApparitionAsserts
static void TestingApparitionAsserts(void)
{
    std::cout << "Testing asserts" << std::endl;

    // These will never assert
    APPARITION_ASSERT(true);
    APPARITION_ASSERT(1);
    APPARITION_ASSERT(-157);
    APPARITION_ASSERTF(11 == 11, "Will never assert cause 11 equals 11");

    // These should always assert
    APPARITION_ASSERT(false);
    APPARITION_ASSERT(0);
    APPARITION_ASSERTF(15 == 14, "Will always assert cause %d not equal to %d", 15, 14);

    // Looping to test the No and Cancel button of the MessageBox
    for (size_t i = 0; i < 100; ++i)
    {
        APPARITION_ASSERTF(false, "Assert in a loop: ITERATION = %zu", i);
    }
}
#pragma endregion

#pragma region TestingVanillaResults

static bool TestingVanillaResults_Internal_MemoryAllocation(void)
{
    std::cout << "Testing results - Memory Allocation" << std::endl;

    bool result;
    constexpr size_t MemoryToAllocate = static_cast<size_t>(100);
    void* someMemory = malloc(MemoryToAllocate);

    result = someMemory != nullptr;

    if (result)
    {
        free(someMemory);
        someMemory = nullptr;
    }

    return result;
}

static bool TestingVanillaResults_Internal_FileIO(void)
{
    std::cout << "Testing results - File IO" << std::endl;

    bool result = true;

    const std::filesystem::path filePath = "D://example.txt";

    // Check if file path is valid
    if (std::filesystem::exists(filePath))
    {
        // Check if the file is a file that can be read
        if (std::filesystem::is_regular_file(filePath))
        {
            std::ifstream file(filePath);

            // Check if file was opened successfully
            if (file.is_open())
            {
                // Read all contents and dump the read string to console
                std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                std::cout << "Contents of " << filePath << ":" << std::endl;
                std::cout << fileContents << std::endl;

                // Close file and check if file is no longer open
                file.close();
                if (file.is_open())
                {
                    result = false;
                }
            }
            else
            {
                result = false;
            }
        }
        else
        {
            result = false;
        }
    }
    else
    {
        result = false;
    }

    return result;
}

static void TestingVanillaResults(void)
{
    // Testing Memory Alloc
    {
        bool result = TestingVanillaResults_Internal_MemoryAllocation();
        if (result)
        {
            std::cout << "Everything went as expected" << std::endl;
        }
        else
        {
            std::cerr << "Generic Error" << std::endl;
        }
        std::cout << std::endl;
    }

    // Testing File IO
    {
        bool result = TestingVanillaResults_Internal_FileIO();
        if (result)
        {
            std::cout << "Everything went as expected" << std::endl;
        }
        else
        {
            std::cerr << "Generic Error" << std::endl;
        }
        std::cout << std::endl;
    }
}

#pragma endregion

#pragma region TestingApparitionResults
static apparition::Results::cResult TestingApparitionResults_Internal_MemoryAllocation(void)
{
    std::cout << "Testing results - Memory Allocation" << std::endl;

    apparition::Results::cResult result;

    APPARITION_ASSERT(result == apparition::Results::Undefined);

    constexpr size_t MemoryToAllocate = static_cast<size_t>(100);
    APPARITION_ASSERTF(MemoryToAllocate, "Why are we trying to allocate 0 bytes of memory");
    void* someMemory = malloc(MemoryToAllocate);
    if (someMemory == nullptr)
    {
        result = apparition::Results::OutOfMemory;
    }
    else
    {
        result = apparition::Results::Success;
    }

    if (result == apparition::Results::Success)
    {
        free(someMemory);
        someMemory = nullptr;
    }

    return result;
}

static apparition::Results::cResult TestingApparitionResults_Internal_FileIO(void)
{
    std::cout << "Testing results - File IO" << std::endl;

    apparition::Results::cResult result = apparition::Results::Success;

    const std::filesystem::path filePath = "D://example.txt";

    // The following code can be improved with logging and scope guards

    // Check if file path is valid
    if (std::filesystem::exists(filePath))
    {
        // Check if the file is a file that can be read
        if (std::filesystem::is_regular_file(filePath))
        {
            std::ifstream file(filePath);

            // Check if file was opened successfully
            if (file.is_open())
            {
                // Read all contents and dump the read string to console
                std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                std::cout << "Contents of " << filePath << ":" << std::endl;
                std::cout << fileContents << std::endl;

                // Close file and check if file is no longer open
                file.close();
                if (file.is_open())
                {
                    APPARITION_ASSERTF(false, "File %s was not closed", filePath.string().c_str());
                    result = apparition::Results::Failure;
                }
            }
            else
            {
                // custom user-defined result
                APPARITION_ASSERTF(false, "Check file %s input stream", filePath.string().c_str());
                result = apparition::Results::Application::FileReadFailed;
            }
        }
        else
        {
            APPARITION_ASSERTF(false, "Check file %s type", filePath.string().c_str());
            result = apparition::Results::InvalidFile;
        }
    }
    else
    {
        APPARITION_ASSERTF(false, "Check path %s", filePath.string().c_str());
        result = apparition::Results::FileDoesntExist;
    }

    return result;
}

static void TestingApparitionResults(void)
{
    // Testing Memory Alloc
    {
        apparition::Results::cResult result = TestingApparitionResults_Internal_MemoryAllocation();
        APPARITION_ASSERT(result);
        // The following code can be improved with logging
        if (result == apparition::Results::Success)
        {
            std::cout << "Everything went as expected" << std::endl;
        }
        else if (result == apparition::Results::OutOfMemory)
        {
            std::cerr << "Failed to allocate memory" << std::endl;
        }
        else
        {
            std::cerr << "Generic Error" << std::endl;
        }
        std::cout << std::endl;
    }

    // Testing File IO
    {
        apparition::Results::cResult result = TestingApparitionResults_Internal_FileIO();
        APPARITION_ASSERT(result);
        // The following code can be improved with logging
        if (result == apparition::Results::Success)
        {
            std::cout << "Everything went as expected" << std::endl;
        }
        else if (result == apparition::Results::InvalidFile)
        {
            std::cerr << "Failed to read the file, it was invalid" << std::endl;
        }
        else if (result == apparition::Results::FileDoesntExist)
        {
            std::cerr << "Failed to open the file, check file path" << std::endl;
        }
        else if (result == apparition::Results::Application::FileReadFailed)
        {
            std::cerr << "Failed to read the file" << std::endl;
        }
        else
        {
            std::cerr << "Generic Error" << std::endl;
        }
        std::cout << std::endl;
    }
}
#pragma endregion

int main(void)
{
    TestingVanillaAsserts();
    // TestingApparitionAsserts();
    // TestingVanillaResults();
    // TestingApparitionResults();

    return 0;
}