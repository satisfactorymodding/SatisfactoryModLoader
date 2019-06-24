#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GasPillar_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_GasPillar.BP_GasPillar_C.UserConstructionScript
struct ABP_GasPillar_C_UserConstructionScript_Params
{
};

// Function BP_GasPillar.BP_GasPillar_C.ReceiveBeginPlay
struct ABP_GasPillar_C_ReceiveBeginPlay_Params
{
};

// Function BP_GasPillar.BP_GasPillar_C.GainedSignificance
struct ABP_GasPillar_C_GainedSignificance_Params
{
};

// Function BP_GasPillar.BP_GasPillar_C.LostSignificance
struct ABP_GasPillar_C_LostSignificance_Params
{
};

// Function BP_GasPillar.BP_GasPillar_C.ReceiveEndPlay
struct ABP_GasPillar_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GasPillar.BP_GasPillar_C.ExecuteUbergraph_BP_GasPillar
struct ABP_GasPillar_C_ExecuteUbergraph_BP_GasPillar_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
