#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_VolumeFogSmall_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.UpdateBrightness
struct ABP_VolumeFogSmall_C_UpdateBrightness_Params
{
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.UserConstructionScript
struct ABP_VolumeFogSmall_C_UserConstructionScript_Params
{
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.LostSignificance
struct ABP_VolumeFogSmall_C_LostSignificance_Params
{
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.GainedSignificance
struct ABP_VolumeFogSmall_C_GainedSignificance_Params
{
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveEndPlay
struct ABP_VolumeFogSmall_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveTick
struct ABP_VolumeFogSmall_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveBeginPlay
struct ABP_VolumeFogSmall_C_ReceiveBeginPlay_Params
{
};

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ExecuteUbergraph_BP_VolumeFogSmall
struct ABP_VolumeFogSmall_C_ExecuteUbergraph_BP_VolumeFogSmall_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
