/*
    This file lists external pre-built libraries that this library depends on
*/

#ifndef APPARITION_ASSERTS_EXTERNAL_LIBRARIES_H
#define APPARITION_ASSERTS_EXTERNAL_LIBRARIES_H

// Include Files
//==============

#include "../Configuration.h"

// External Libraries
//===================

#if defined(APPARITION_ASSERTS_ARE_ENABLED) && defined(APPARITION_OS_API_WINDOWS)
    #pragma comment(lib, "User32.lib")
#endif

#endif