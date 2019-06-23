#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_SpaceRabbit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.GetLookAtDecription
struct AChar_SpaceRabbit_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.IsUseable
struct AChar_SpaceRabbit_C_IsUseable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateUseState
struct AChar_SpaceRabbit_C_UpdateUseState_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent*                         componentHit;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.SetupLootTimer
struct AChar_SpaceRabbit_C_SetupLootTimer_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnRep_mLootTableIndex
struct AChar_SpaceRabbit_C_OnRep_mLootTableIndex_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.RollLoot
struct AChar_SpaceRabbit_C_RollLoot_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.SetNewFriend
struct AChar_SpaceRabbit_C_SetNewFriend_Params
{
	class AActor*                                      newFriend;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StopBackwardWalk
struct AChar_SpaceRabbit_C_StopBackwardWalk_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateWalkBackMovement
struct AChar_SpaceRabbit_C_UpdateWalkBackMovement_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateWalkBackDirection
struct AChar_SpaceRabbit_C_UpdateWalkBackDirection_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StartWalkBack
struct AChar_SpaceRabbit_C_StartWalkBack_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UserConstructionScript
struct AChar_SpaceRabbit_C_UserConstructionScript_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnUseStop
struct AChar_SpaceRabbit_C_OnUseStop_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.RegisterInteractingPlayer
struct AChar_SpaceRabbit_C_RegisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StartIsLookedAt
struct AChar_SpaceRabbit_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StopIsLookedAt
struct AChar_SpaceRabbit_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UnregisterInteractingPlayer
struct AChar_SpaceRabbit_C_UnregisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveTick
struct AChar_SpaceRabbit_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakeDamage
struct AChar_SpaceRabbit_C_NotifyOnTakeDamage_Params
{
	class AActor**                                     damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             damageAmount;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType**                                DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController**                                instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor**                                     damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveDied
struct AChar_SpaceRabbit_C_ReceiveDied_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakePointDamage
struct AChar_SpaceRabbit_C_NotifyOnTakePointDamage_Params
{
	class AActor**                                     damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController**                                instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    HitLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent**                        HitComponent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName*                                      BoneName;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    ShotFromDirection;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType**                                DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor**                                     damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakeRadialDamage
struct AChar_SpaceRabbit_C_NotifyOnTakeRadialDamage_Params
{
	class AActor**                                     damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController**                                instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType**                                DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor**                                     damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveBeginPlay
struct AChar_SpaceRabbit_C_ReceiveBeginPlay_Params
{
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.PlayConsumeItemEffect
struct AChar_SpaceRabbit_C_PlayConsumeItemEffect_Params
{
	class UClass**                                     itemDescriptor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int*                                               amount;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnUse
struct AChar_SpaceRabbit_C_OnUse_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ExecuteUbergraph_Char_SpaceRabbit
struct AChar_SpaceRabbit_C_ExecuteUbergraph_Char_SpaceRabbit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnWalkBackStopped__DelegateSignature
struct AChar_SpaceRabbit_C_OnWalkBackStopped__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
