#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_LandingPad_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_LandingPad.Build_LandingPad_C.UpdateAudioState
struct ABuild_LandingPad_C_UpdateAudioState_Params
{
};

// Function Build_LandingPad.Build_LandingPad_C.CanProduce
struct ABuild_LandingPad_C_CanProduce_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_LandingPad.Build_LandingPad_C.UserConstructionScript
struct ABuild_LandingPad_C_UserConstructionScript_Params
{
};

// Function Build_LandingPad.Build_LandingPad_C.ReceiveTick
struct ABuild_LandingPad_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_LandingPad.Build_LandingPad_C.BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct ABuild_LandingPad_C_BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function Build_LandingPad.Build_LandingPad_C.BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
struct ABuild_LandingPad_C_BndEvt__StaticMesh1_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_LandingPad.Build_LandingPad_C.Factory_ReceiveStartProducing
struct ABuild_LandingPad_C_Factory_ReceiveStartProducing_Params
{
};

// Function Build_LandingPad.Build_LandingPad_C.Factory_ReceiveStopProducing
struct ABuild_LandingPad_C_Factory_ReceiveStopProducing_Params
{
};

// Function Build_LandingPad.Build_LandingPad_C.OnHasPowerChanged
struct ABuild_LandingPad_C_OnHasPowerChanged_Params
{
	bool*                                              newHasPower;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_LandingPad.Build_LandingPad_C.ReceiveDestroyed
struct ABuild_LandingPad_C_ReceiveDestroyed_Params
{
};

// Function Build_LandingPad.Build_LandingPad_C.ReceiveBeginPlay
struct ABuild_LandingPad_C_ReceiveBeginPlay_Params
{
};

// Function Build_LandingPad.Build_LandingPad_C.ExecuteUbergraph_Build_LandingPad
struct ABuild_LandingPad_C_ExecuteUbergraph_Build_LandingPad_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
