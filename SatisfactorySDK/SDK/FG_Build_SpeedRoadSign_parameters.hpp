#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_SpeedRoadSign_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.OnRep_mSpeedRestriction
struct ABuild_SpeedRoadSign_C_OnRep_mSpeedRestriction_Params
{
};

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.UserConstructionScript
struct ABuild_SpeedRoadSign_C_UserConstructionScript_Params
{
};

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.ReceiveBeginPlay
struct ABuild_SpeedRoadSign_C_ReceiveBeginPlay_Params
{
};

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_111_ComponentBeginOverlapSignature__DelegateSignature
struct ABuild_SpeedRoadSign_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_111_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.UpdateSpeedLimit
struct ABuild_SpeedRoadSign_C_UpdateSpeedLimit_Params
{
	int                                                newSpeed;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.ExecuteUbergraph_Build_SpeedRoadSign
struct ABuild_SpeedRoadSign_C_ExecuteUbergraph_Build_SpeedRoadSign_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
