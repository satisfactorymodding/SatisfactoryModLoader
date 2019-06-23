#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_StarfishSingle_01_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.IsTooClose
struct ABP_StarfishSingle_01_C_IsTooClose_Params
{
	bool                                               IsTooClose;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.Burrow
struct ABP_StarfishSingle_01_C_Burrow_Params
{
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.CanMove
struct ABP_StarfishSingle_01_C_CanMove_Params
{
	bool                                               CanMove;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.MoveStarFish
struct ABP_StarfishSingle_01_C_MoveStarFish_Params
{
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.UpdateMesh
struct ABP_StarfishSingle_01_C_UpdateMesh_Params
{
	float                                              Position;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMeshComponent*                        Mesh;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.UserConstructionScript
struct ABP_StarfishSingle_01_C_UserConstructionScript_Params
{
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ReceiveBeginPlay
struct ABP_StarfishSingle_01_C_ReceiveBeginPlay_Params
{
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct ABP_StarfishSingle_01_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
struct ABP_StarfishSingle_01_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.StartBurrow
struct ABP_StarfishSingle_01_C_StartBurrow_Params
{
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ReceiveTick
struct ABP_StarfishSingle_01_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.StopBurrow
struct ABP_StarfishSingle_01_C_StopBurrow_Params
{
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere2_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature
struct ABP_StarfishSingle_01_C_BndEvt__Sphere2_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ExecuteUbergraph_BP_StarfishSingle_01
struct ABP_StarfishSingle_01_C_ExecuteUbergraph_BP_StarfishSingle_01_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
