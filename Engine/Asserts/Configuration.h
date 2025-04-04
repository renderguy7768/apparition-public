/*
    This file provides configurable settings that can be used to control assert's behavior
*/

#ifndef APPARITION_ASSERTS_CONFIGURATION_H
#define APPARITION_ASSERTS_CONFIGURATION_H

// By default asserts are only enabled for debug builds,
// but you can #define it differently as necessary
#ifdef _DEBUG
    #define APPARITION_ASSERTS_ARE_ENABLED
#endif

#ifdef APPARITION_ASSERTS_ARE_ENABLED
// For platforms and debuggers that support it
// it can be useful to output the assert message to the debugger
// so that there's a record of the message
    #define APPARITION_ASSERTS_SHOULD_PRINT_TO_DEBUGGER
#endif

#endif