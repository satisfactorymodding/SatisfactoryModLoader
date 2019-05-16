#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_TimeManagement_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function TimeManagement.TimeManagementBlueprintLibrary.Multiply_SecondsFrameRate
struct UTimeManagementBlueprintLibrary_Multiply_SecondsFrameRate_Params
{
	float                                              TimeInSeconds;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFrameRate                                  FrameRate;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FFrameTime                                  ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function TimeManagement.TimeManagementBlueprintLibrary.GetTimecode
struct UTimeManagementBlueprintLibrary_GetTimecode_Params
{
	struct FTimecode                                   ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function TimeManagement.TimeManagementBlueprintLibrary.Conv_TimecodeToString
struct UTimeManagementBlueprintLibrary_Conv_TimecodeToString_Params
{
	struct FTimecode                                   InTimecode;                                               // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               bForceSignDisplay;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function TimeManagement.TimeManagementBlueprintLibrary.Conv_QualifiedFrameTimeToSeconds
struct UTimeManagementBlueprintLibrary_Conv_QualifiedFrameTimeToSeconds_Params
{
	struct FQualifiedFrameTime                         InFrameTime;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function TimeManagement.TimeManagementBlueprintLibrary.Conv_FrameRateToSeconds
struct UTimeManagementBlueprintLibrary_Conv_FrameRateToSeconds_Params
{
	struct FFrameRate                                  InFrameRate;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
