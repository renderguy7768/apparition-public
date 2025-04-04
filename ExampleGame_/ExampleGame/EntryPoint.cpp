#include "Engine/Asserts/Asserts.h"

#include <iostream>

static void TestingAsserts(void)
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

int main(void)
{
	TestingAsserts();
	return 0;
}