#pragma once
#ifdef ASSEMBLY_ANALYZER_SHARED
 #ifdef BUILDING_ASSEMBLY_ANALYZER
  #define AA_API __declspec(dllexport)
 #else //BUILDING_ASSEMBLY_ANALYZER
  #define AA_API __declspec(dllimport)
 #endif //BUILDING_ASSEMBLY_ANALYZER
#else //ASSEMBLY_ANALYZER_SHARED
 #define AA_API
#endif //ASSEMBLY_ANALYZER_SHARED

//Struct that holds the information about function
struct FunctionInfo {
    //Whenever pointer represents a valid function at all
    bool bIsValid;
    //Whenever this function represents a virtual function call thunk and doesn't represent the real function
    bool bIsVirtualFunction;
    //Real resolved function address, or NULL if this function represents a virtual function
    void* RealFunctionAddress;
    //Offset to the function pointer inside of the vtable, if bIsVirtualFunction is set
    unsigned int VirtualTableFunctionOffset;
};

typedef void(*LogDebugMessageFunctionType)(const char*);

/** Sets up function used for debugging logging, if it's enabled by build configuration */
AA_API void SetDebugLoggingHook(LogDebugMessageFunctionType LogDebugMessage);

/**
 * Performs analysis of the provided function pointer, resolving details such as
 * real code pointer (excluding thunks), whenever it is a virtual function thunk,
 * and the offset to the virtual table if provided function is virtual
 *
 * @param FunctionPtr pointer to the function's code to analyze
 * @return information about the function
 */
AA_API FunctionInfo DiscoverFunction(unsigned char* FunctionPtr);