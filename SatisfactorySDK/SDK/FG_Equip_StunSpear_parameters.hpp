#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_StunSpear_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_StunSpear.Equip_StunSpear_C.UserConstructionScript
struct AEquip_StunSpear_C_UserConstructionScript_Params
{
};

// Function Equip_StunSpear.Equip_StunSpear_C.ReceiveTick
struct AEquip_StunSpear_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_StunSpear.Equip_StunSpear_C.SwordAttack
struct AEquip_StunSpear_C_SwordAttack_Params
{
};

// Function Equip_StunSpear.Equip_StunSpear_C.PlayStunEffects
struct AEquip_StunSpear_C_PlayStunEffects_Params
{
};

// Function Equip_StunSpear.Equip_StunSpear_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct AEquip_StunSpear_C_BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function Equip_StunSpear.Equip_StunSpear_C.WasUnEquipped
struct AEquip_StunSpear_C_WasUnEquipped_Params
{
};

// Function Equip_StunSpear.Equip_StunSpear_C.WasEquipped
struct AEquip_StunSpear_C_WasEquipped_Params
{
};

// Function Equip_StunSpear.Equip_StunSpear_C.OnHitTarget
struct AEquip_StunSpear_C_OnHitTarget_Params
{
};

// Function Equip_StunSpear.Equip_StunSpear_C.ExecuteUbergraph_Equip_StunSpear
struct AEquip_StunSpear_C_ExecuteUbergraph_Equip_StunSpear_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
