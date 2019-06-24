// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ConsumeableEquipment_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.UserConstructionScript
// ()

void ABP_ConsumeableEquipment_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.UserConstructionScript");

	ABP_ConsumeableEquipment_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.PlayConsumeEffects
// ()
// Parameters:
// class UFGConsumableDescriptor** consumable                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipment_C::PlayConsumeEffects(class UFGConsumableDescriptor** consumable)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.PlayConsumeEffects");

	ABP_ConsumeableEquipment_C_PlayConsumeEffects_Params params;
	params.consumable = consumable;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.WasEquipped
// ()

void ABP_ConsumeableEquipment_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.WasEquipped");

	ABP_ConsumeableEquipment_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipment_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.ReceiveTick");

	ABP_ConsumeableEquipment_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.ExecuteUbergraph_BP_ConsumeableEquipment
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ConsumeableEquipment_C::ExecuteUbergraph_BP_ConsumeableEquipment(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.ExecuteUbergraph_BP_ConsumeableEquipment");

	ABP_ConsumeableEquipment_C_ExecuteUbergraph_BP_ConsumeableEquipment_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
