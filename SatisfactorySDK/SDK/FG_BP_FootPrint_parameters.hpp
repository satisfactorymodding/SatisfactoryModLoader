#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FootPrint_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_FootPrint.BP_FootPrint_C.UserConstructionScript
struct ABP_FootPrint_C_UserConstructionScript_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.ReceiveBeginPlay
struct ABP_FootPrint_C_ReceiveBeginPlay_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.FootOnGrass
struct ABP_FootPrint_C_FootOnGrass_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.DestroyFootPrint
struct ABP_FootPrint_C_DestroyFootPrint_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.FootOnSand
struct ABP_FootPrint_C_FootOnSand_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.AdjustToGround
struct ABP_FootPrint_C_AdjustToGround_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.ReceiveTick
struct ABP_FootPrint_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FootPrint.BP_FootPrint_C.ReceiveActorBeginOverlap
struct ABP_FootPrint_C_ReceiveActorBeginOverlap_Params
{
	class AActor**                                     OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FootPrint.BP_FootPrint_C.BeginFade
struct ABP_FootPrint_C_BeginFade_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.FootOnGravel
struct ABP_FootPrint_C_FootOnGravel_Params
{
};

// Function BP_FootPrint.BP_FootPrint_C.ExecuteUbergraph_BP_FootPrint
struct ABP_FootPrint_C_ExecuteUbergraph_BP_FootPrint_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
