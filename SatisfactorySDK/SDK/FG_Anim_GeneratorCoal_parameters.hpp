#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_GeneratorCoal_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.BlueprintUpdateAnimation
struct UAnim_GeneratorCoal_C_BlueprintUpdateAnimation_Params
{
	float*                                             DeltaTimeX;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_steamVfxNotify
struct UAnim_GeneratorCoal_C_AnimNotify_steamVfxNotify_Params
{
};

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenEnteredProducingState
struct UAnim_GeneratorCoal_C_AnimNotify_CoalGenEnteredProducingState_Params
{
};

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenLeftProducingState
struct UAnim_GeneratorCoal_C_AnimNotify_CoalGenLeftProducingState_Params
{
};

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenEnteredOfflineState
struct UAnim_GeneratorCoal_C_AnimNotify_CoalGenEnteredOfflineState_Params
{
};

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenLeftOfflineState
struct UAnim_GeneratorCoal_C_AnimNotify_CoalGenLeftOfflineState_Params
{
};

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.ExecuteUbergraph_Anim_GeneratorCoal
struct UAnim_GeneratorCoal_C_ExecuteUbergraph_Anim_GeneratorCoal_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
