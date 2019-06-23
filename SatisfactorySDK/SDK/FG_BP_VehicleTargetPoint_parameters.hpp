#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_VehicleTargetPoint_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.GetLookAtDecription
struct ABP_VehicleTargetPoint_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.IsUseable
struct ABP_VehicleTargetPoint_C_IsUseable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.UpdateUseState
struct ABP_VehicleTargetPoint_C_UpdateUseState_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent*                         componentHit;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.ShouldSave
struct ABP_VehicleTargetPoint_C_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.NeedTransform
struct ABP_VehicleTargetPoint_C_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.GatherDependencies
struct ABP_VehicleTargetPoint_C_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.UserConstructionScript
struct ABP_VehicleTargetPoint_C_UserConstructionScript_Params
{
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.OnUseStop
struct ABP_VehicleTargetPoint_C_OnUseStop_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.RegisterInteractingPlayer
struct ABP_VehicleTargetPoint_C_RegisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.UnregisterInteractingPlayer
struct ABP_VehicleTargetPoint_C_UnregisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.ReceiveBeginPlay
struct ABP_VehicleTargetPoint_C_ReceiveBeginPlay_Params
{
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.OnUse
struct ABP_VehicleTargetPoint_C_OnUse_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.StartIsLookedAt
struct ABP_VehicleTargetPoint_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.StopIsLookedAt
struct ABP_VehicleTargetPoint_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.SetMeshRotation
struct ABP_VehicleTargetPoint_C_SetMeshRotation_Params
{
};

// Function BP_VehicleTargetPoint.BP_VehicleTargetPoint_C.ExecuteUbergraph_BP_VehicleTargetPoint
struct ABP_VehicleTargetPoint_C_ExecuteUbergraph_BP_VehicleTargetPoint_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
