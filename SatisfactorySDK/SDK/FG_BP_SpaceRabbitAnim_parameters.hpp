#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpaceRabbitAnim_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.CalculateAnimGraphValues
struct UBP_SpaceRabbitAnim_C_CalculateAnimGraphValues_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.BlueprintUpdateAnimation
struct UBP_SpaceRabbitAnim_C_BlueprintUpdateAnimation_Params
{
	float*                                             DeltaTimeX;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.OnRadialDamageTaken
struct UBP_SpaceRabbitAnim_C_OnRadialDamageTaken_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.OnPointDamageTaken
struct UBP_SpaceRabbitAnim_C_OnPointDamageTaken_Params
{
	struct FVector*                                    shootDIrection;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.AnimNotify_AudioNotify_SpaceBunny_RTPC_2
struct UBP_SpaceRabbitAnim_C_AnimNotify_AudioNotify_SpaceBunny_RTPC_2_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.AnimNotify_AudioNotify_SpaceBunny_RTPC_3
struct UBP_SpaceRabbitAnim_C_AnimNotify_AudioNotify_SpaceBunny_RTPC_3_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.AnimNotify_AudioNotify_SpaceBunny_RTPC_4
struct UBP_SpaceRabbitAnim_C_AnimNotify_AudioNotify_SpaceBunny_RTPC_4_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.AnimNotify_AudioNotify_SpaceBunny_SupressBreath
struct UBP_SpaceRabbitAnim_C_AnimNotify_AudioNotify_SpaceBunny_SupressBreath_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.AnimNotify_AudioNotify_SpaceBunny_ReleaseBreath
struct UBP_SpaceRabbitAnim_C_AnimNotify_AudioNotify_SpaceBunny_ReleaseBreath_Params
{
};

// Function BP_SpaceRabbitAnim.BP_SpaceRabbitAnim_C.ExecuteUbergraph_BP_SpaceRabbitAnim
struct UBP_SpaceRabbitAnim_C_ExecuteUbergraph_BP_SpaceRabbitAnim_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
