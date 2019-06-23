#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ProfileSpline_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ProfileSpline.BP_ProfileSpline_C.CheckDoneRespawning
struct ABP_ProfileSpline_C_CheckDoneRespawning_Params
{
	bool                                               bDoneSpawning;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.GetPlayerController
struct ABP_ProfileSpline_C_GetPlayerController_Params
{
	bool                                               bIsValid;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class APlayerController*                           PlayerController;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.UserConstructionScript
struct ABP_ProfileSpline_C_UserConstructionScript_Params
{
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.ReceiveTick
struct ABP_ProfileSpline_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.FetchPlayerPawn
struct ABP_ProfileSpline_C_FetchPlayerPawn_Params
{
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.StartProfile
struct ABP_ProfileSpline_C_StartProfile_Params
{
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.EnsurePlayerDoneSpawning
struct ABP_ProfileSpline_C_EnsurePlayerDoneSpawning_Params
{
};

// Function BP_ProfileSpline.BP_ProfileSpline_C.ExecuteUbergraph_BP_ProfileSpline
struct ABP_ProfileSpline_C_ExecuteUbergraph_BP_ProfileSpline_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
