// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_MedKit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_MedKit.Equip_MedKit_C.UserConstructionScript
// ()

void AEquip_MedKit_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_MedKit.Equip_MedKit_C.UserConstructionScript");

	AEquip_MedKit_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_MedKit.Equip_MedKit_C.WasEquipped
// ()

void AEquip_MedKit_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_MedKit.Equip_MedKit_C.WasEquipped");

	AEquip_MedKit_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_MedKit.Equip_MedKit_C.PlayConsumeEffects
// ()
// Parameters:
// class UFGConsumableDescriptor** consumable                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_MedKit_C::PlayConsumeEffects(class UFGConsumableDescriptor** consumable)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_MedKit.Equip_MedKit_C.PlayConsumeEffects");

	AEquip_MedKit_C_PlayConsumeEffects_Params params;
	params.consumable = consumable;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_MedKit.Equip_MedKit_C.WasUnEquipped
// ()

void AEquip_MedKit_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_MedKit.Equip_MedKit_C.WasUnEquipped");

	AEquip_MedKit_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_MedKit.Equip_MedKit_C.ExecuteUbergraph_Equip_MedKit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_MedKit_C::ExecuteUbergraph_Equip_MedKit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_MedKit.Equip_MedKit_C.ExecuteUbergraph_Equip_MedKit");

	AEquip_MedKit_C_ExecuteUbergraph_Equip_MedKit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
