// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardArmEquipmentSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.IsValidRewardItem
// ()
// Parameters:
// bool                           IsValid                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardArmEquipmentSlot_C::IsValidRewardItem(bool* IsValid)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.IsValidRewardItem");

	UWidget_RewardArmEquipmentSlot_C_IsValidRewardItem_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsValid != nullptr)
		*IsValid = params.IsValid;
}


// Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.UpdateVisibility
// ()

void UWidget_RewardArmEquipmentSlot_C::UpdateVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.UpdateVisibility");

	UWidget_RewardArmEquipmentSlot_C_UpdateVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardArmEquipmentSlot_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.PreConstruct");

	UWidget_RewardArmEquipmentSlot_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.Construct
// ()

void UWidget_RewardArmEquipmentSlot_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.Construct");

	UWidget_RewardArmEquipmentSlot_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.ExecuteUbergraph_Widget_RewardArmEquipmentSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardArmEquipmentSlot_C::ExecuteUbergraph_Widget_RewardArmEquipmentSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C.ExecuteUbergraph_Widget_RewardArmEquipmentSlot");

	UWidget_RewardArmEquipmentSlot_C_ExecuteUbergraph_Widget_RewardArmEquipmentSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
