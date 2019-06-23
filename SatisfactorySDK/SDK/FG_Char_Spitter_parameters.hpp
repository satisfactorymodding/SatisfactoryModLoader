#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Spitter_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_Spitter.Char_Spitter_C.GetAttackLocation
struct AChar_Spitter_C_GetAttackLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Spitter.Char_Spitter_C.UpdateStrafeDirection
struct AChar_Spitter_C_UpdateStrafeDirection_Params
{
};

// Function Char_Spitter.Char_Spitter_C.StopStrafe
struct AChar_Spitter_C_StopStrafe_Params
{
};

// Function Char_Spitter.Char_Spitter_C.DoStrafe
struct AChar_Spitter_C_DoStrafe_Params
{
};

// Function Char_Spitter.Char_Spitter_C.StartStrafe
struct AChar_Spitter_C_StartStrafe_Params
{
};

// Function Char_Spitter.Char_Spitter_C.UserConstructionScript
struct AChar_Spitter_C_UserConstructionScript_Params
{
};

// Function Char_Spitter.Char_Spitter_C.ReceiveTick
struct AChar_Spitter_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Spitter.Char_Spitter_C.OnCurrentAggroTargetReplicated
struct AChar_Spitter_C_OnCurrentAggroTargetReplicated_Params
{
};

// Function Char_Spitter.Char_Spitter_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct AChar_Spitter_C_BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function Char_Spitter.Char_Spitter_C.ExecuteUbergraph_Char_Spitter
struct AChar_Spitter_C_ExecuteUbergraph_Char_Spitter_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Spitter.Char_Spitter_C.OnStrafeEnded__DelegateSignature
struct AChar_Spitter_C_OnStrafeEnded__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
