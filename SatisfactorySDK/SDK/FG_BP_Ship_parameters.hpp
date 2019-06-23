#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Ship_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Ship.BP_Ship_C.UserConstructionScript
struct ABP_Ship_C_UserConstructionScript_Params
{
};

// Function BP_Ship.BP_Ship_C.GainedSignificance
struct ABP_Ship_C_GainedSignificance_Params
{
};

// Function BP_Ship.BP_Ship_C.LostSignificance
struct ABP_Ship_C_LostSignificance_Params
{
};

// Function BP_Ship.BP_Ship_C.ReceiveBeginPlay
struct ABP_Ship_C_ReceiveBeginPlay_Params
{
};

// Function BP_Ship.BP_Ship_C.ReceiveEndPlay
struct ABP_Ship_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Ship.BP_Ship_C.ExecuteUbergraph_BP_Ship
struct ABP_Ship_C_ExecuteUbergraph_BP_Ship_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
