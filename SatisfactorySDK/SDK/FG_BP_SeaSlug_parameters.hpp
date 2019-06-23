#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SeaSlug_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SeaSlug.BP_SeaSlug_C.UpdateMesh
struct ABP_SeaSlug_C_UpdateMesh_Params
{
	float                                              Position;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class USkeletalMeshComponent*                      Mesh;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_SeaSlug.BP_SeaSlug_C.UserConstructionScript
struct ABP_SeaSlug_C_UserConstructionScript_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_1__FinishedFunc
struct ABP_SeaSlug_C_Timeline_1__FinishedFunc_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_1__UpdateFunc
struct ABP_SeaSlug_C_Timeline_1__UpdateFunc_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_0__FinishedFunc
struct ABP_SeaSlug_C_Timeline_0__FinishedFunc_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_0__UpdateFunc
struct ABP_SeaSlug_C_Timeline_0__UpdateFunc_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.ReceiveBeginPlay
struct ABP_SeaSlug_C_ReceiveBeginPlay_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct ABP_SeaSlug_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_SeaSlug.BP_SeaSlug_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
struct ABP_SeaSlug_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SeaSlug.BP_SeaSlug_C.Reset
struct ABP_SeaSlug_C_Reset_Params
{
};

// Function BP_SeaSlug.BP_SeaSlug_C.ExecuteUbergraph_BP_SeaSlug
struct ABP_SeaSlug_C_ExecuteUbergraph_BP_SeaSlug_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
