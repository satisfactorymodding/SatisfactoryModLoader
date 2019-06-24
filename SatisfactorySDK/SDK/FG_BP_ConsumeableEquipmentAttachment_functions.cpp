// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ConsumeableEquipmentAttachment_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.GetHandsItem
// ()
// Parameters:
// class UClass*                  Item                           (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipmentAttachment_C::GetHandsItem(class UClass** Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.GetHandsItem");

	ABP_ConsumeableEquipmentAttachment_C_GetHandsItem_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Item != nullptr)
		*Item = params.Item;
}


// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.UserConstructionScript
// ()

void ABP_ConsumeableEquipmentAttachment_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.UserConstructionScript");

	ABP_ConsumeableEquipmentAttachment_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipmentAttachment_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.ReceiveTick");

	ABP_ConsumeableEquipmentAttachment_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.PlayUseEffect
// ()
// Parameters:
// struct FVector*                UseLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipmentAttachment_C::PlayUseEffect(struct FVector* UseLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.PlayUseEffect");

	ABP_ConsumeableEquipmentAttachment_C_PlayUseEffect_Params params;
	params.UseLocation = UseLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.OnAttach
// ()

void ABP_ConsumeableEquipmentAttachment_C::OnAttach()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.OnAttach");

	ABP_ConsumeableEquipmentAttachment_C_OnAttach_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.ExecuteUbergraph_BP_ConsumeableEquipmentAttachment
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipmentAttachment_C::ExecuteUbergraph_BP_ConsumeableEquipmentAttachment(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipmentAttachment.BP_ConsumeableEquipmentAttachment_C.ExecuteUbergraph_BP_ConsumeableEquipmentAttachment");

	ABP_ConsumeableEquipmentAttachment_C_ExecuteUbergraph_BP_ConsumeableEquipmentAttachment_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
