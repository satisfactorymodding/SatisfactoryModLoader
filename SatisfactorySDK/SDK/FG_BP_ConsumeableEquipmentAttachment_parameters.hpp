#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ConsumeableEquipmentAttachment_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.GetHandsItem
struct ABP_ConsumeableEquipmentAttachment_C_GetHandsItem_Params
{
	class UClass*                                      Item;                                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.UserConstructionScript
struct ABP_ConsumeableEquipmentAttachment_C_UserConstructionScript_Params
{
};

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.ReceiveTick
struct ABP_ConsumeableEquipmentAttachment_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.PlayUseEffect
struct ABP_ConsumeableEquipmentAttachment_C_PlayUseEffect_Params
{
	struct FVector*                                    UseLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.OnAttach
struct ABP_ConsumeableEquipmentAttachment_C_OnAttach_Params
{
};

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.ExecuteUbergraph_BP_ConsumeableEquipmentAttachment
struct ABP_ConsumeableEquipmentAttachment_C_ExecuteUbergraph_BP_ConsumeableEquipmentAttachment_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
