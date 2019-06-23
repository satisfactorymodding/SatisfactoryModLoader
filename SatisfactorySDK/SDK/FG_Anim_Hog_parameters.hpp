#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Hog_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Anim_Hog.Anim_Hog_C.CalculateAnimGraphVariables
struct UAnim_Hog_C_CalculateAnimGraphVariables_Params
{
};

// Function Anim_Hog.Anim_Hog_C.OnPointDamageTaken
struct UAnim_Hog_C_OnPointDamageTaken_Params
{
	struct FVector*                                    shootDIrection;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_Hog.Anim_Hog_C.OnAnyDamageTaken
struct UAnim_Hog_C_OnAnyDamageTaken_Params
{
};

// Function Anim_Hog.Anim_Hog_C.OnRadialDamageTaken
struct UAnim_Hog_C_OnRadialDamageTaken_Params
{
};

// Function Anim_Hog.Anim_Hog_C.AnimNotify_Notify_Hog_LeftIdle
struct UAnim_Hog_C_AnimNotify_Notify_Hog_LeftIdle_Params
{
};

// Function Anim_Hog.Anim_Hog_C.BlueprintUpdateAnimation
struct UAnim_Hog_C_BlueprintUpdateAnimation_Params
{
	float*                                             DeltaTimeX;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_Hog.Anim_Hog_C.ExecuteUbergraph_Anim_Hog
struct UAnim_Hog_C_ExecuteUbergraph_Anim_Hog_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
