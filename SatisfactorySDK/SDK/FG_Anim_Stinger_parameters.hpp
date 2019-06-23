#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Stinger_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Anim_Stinger.Anim_Stinger_C.CalculateAnimGraphVariables
struct UAnim_Stinger_C_CalculateAnimGraphVariables_Params
{
};

// Function Anim_Stinger.Anim_Stinger_C.OnRadialDamageTaken
struct UAnim_Stinger_C_OnRadialDamageTaken_Params
{
};

// Function Anim_Stinger.Anim_Stinger_C.OnPointDamageTaken
struct UAnim_Stinger_C_OnPointDamageTaken_Params
{
	struct FVector*                                    shootDIrection;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_Stinger.Anim_Stinger_C.AnimNotify_Notify_Stinger_Entered_Idle
struct UAnim_Stinger_C_AnimNotify_Notify_Stinger_Entered_Idle_Params
{
};

// Function Anim_Stinger.Anim_Stinger_C.AnimNotify_Notify_Stinger_Entered_Walk
struct UAnim_Stinger_C_AnimNotify_Notify_Stinger_Entered_Walk_Params
{
};

// Function Anim_Stinger.Anim_Stinger_C.BlueprintUpdateAnimation
struct UAnim_Stinger_C_BlueprintUpdateAnimation_Params
{
	float*                                             DeltaTimeX;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_Stinger.Anim_Stinger_C.ExecuteUbergraph_Anim_Stinger
struct UAnim_Stinger_C_ExecuteUbergraph_Anim_Stinger_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
