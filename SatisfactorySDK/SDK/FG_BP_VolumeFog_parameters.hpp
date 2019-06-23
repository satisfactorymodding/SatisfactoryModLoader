#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_VolumeFog_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_VolumeFog.BP_VolumeFog_C.UpdateBrightness
struct ABP_VolumeFog_C_UpdateBrightness_Params
{
};

// Function BP_VolumeFog.BP_VolumeFog_C.UserConstructionScript
struct ABP_VolumeFog_C_UserConstructionScript_Params
{
};

// Function BP_VolumeFog.BP_VolumeFog_C.LostSignificance
struct ABP_VolumeFog_C_LostSignificance_Params
{
};

// Function BP_VolumeFog.BP_VolumeFog_C.GainedSignificance
struct ABP_VolumeFog_C_GainedSignificance_Params
{
};

// Function BP_VolumeFog.BP_VolumeFog_C.ReceiveEndPlay
struct ABP_VolumeFog_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_VolumeFog.BP_VolumeFog_C.ReceiveTick
struct ABP_VolumeFog_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_VolumeFog.BP_VolumeFog_C.ReceiveBeginPlay
struct ABP_VolumeFog_C_ReceiveBeginPlay_Params
{
};

// Function BP_VolumeFog.BP_VolumeFog_C.ExecuteUbergraph_BP_VolumeFog
struct ABP_VolumeFog_C_ExecuteUbergraph_BP_VolumeFog_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
