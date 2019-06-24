#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ObjectScanner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.UserConstructionScript
struct AAttach_ObjectScanner_C_UserConstructionScript_Params
{
};

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.ReceiveBeginPlay
struct AAttach_ObjectScanner_C_ReceiveBeginPlay_Params
{
};

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.ReceiveTick
struct AAttach_ObjectScanner_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.UpdateScannerVisuals
struct AAttach_ObjectScanner_C_UpdateScannerVisuals_Params
{
};

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.PlayAttachEffects3P
struct AAttach_ObjectScanner_C_PlayAttachEffects3P_Params
{
};

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.ExecuteUbergraph_Attach_ObjectScanner
struct AAttach_ObjectScanner_C_ExecuteUbergraph_Attach_ObjectScanner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
