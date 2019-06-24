#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_SpaceGiraffe_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.GetLookAtDecription
struct AChar_SpaceGiraffe_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.IsUseable
struct AChar_SpaceGiraffe_C_IsUseable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UpdateUseState
struct AChar_SpaceGiraffe_C_UpdateUseState_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent*                         componentHit;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnRep_mDoPanic
struct AChar_SpaceGiraffe_C_OnRep_mDoPanic_Params
{
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UserConstructionScript
struct AChar_SpaceGiraffe_C_UserConstructionScript_Params
{
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnUseStop
struct AChar_SpaceGiraffe_C_OnUseStop_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.RegisterInteractingPlayer
struct AChar_SpaceGiraffe_C_RegisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StartIsLookedAt
struct AChar_SpaceGiraffe_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StopIsLookedAt
struct AChar_SpaceGiraffe_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UnregisterInteractingPlayer
struct AChar_SpaceGiraffe_C_UnregisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveTick
struct AChar_SpaceGiraffe_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.NotifyOnTakeDamage
struct AChar_SpaceGiraffe_C_NotifyOnTakeDamage_Params
{
	class AActor**                                     damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             damageAmount;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType**                                DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController**                                instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor**                                     damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StartRotationMovement
struct AChar_SpaceGiraffe_C_StartRotationMovement_Params
{
	struct FRotator*                                   TargetRotation;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1
struct AChar_SpaceGiraffe_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10
struct AChar_SpaceGiraffe_C_InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceivePossessed
struct AChar_SpaceGiraffe_C_ReceivePossessed_Params
{
	class AController**                                NewController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ClientSetupHUD
struct AChar_SpaceGiraffe_C_ClientSetupHUD_Params
{
	class AFGPlayerController*                         Controller;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveUnpossessed
struct AChar_SpaceGiraffe_C_ReceiveUnpossessed_Params
{
	class AController**                                OldController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnUse
struct AChar_SpaceGiraffe_C_OnUse_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct AChar_SpaceGiraffe_C_BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveDied
struct AChar_SpaceGiraffe_C_ReceiveDied_Params
{
};

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ExecuteUbergraph_Char_SpaceGiraffe
struct AChar_SpaceGiraffe_C_ExecuteUbergraph_Char_SpaceGiraffe_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
