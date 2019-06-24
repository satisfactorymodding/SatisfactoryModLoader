// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerEquipmentInventory_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.SetActiveSlot
// ()
// Parameters:
// int                            mActiveSlotIndex               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerEquipmentInventory_C::SetActiveSlot(int mActiveSlotIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.SetActiveSlot");

	UWidget_PlayerEquipmentInventory_C_SetActiveSlot_Params params;
	params.mActiveSlotIndex = mActiveSlotIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.ArmSelectionVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PlayerEquipmentInventory_C::ArmSelectionVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.ArmSelectionVisibility");

	UWidget_PlayerEquipmentInventory_C_ArmSelectionVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Construct
// ()

void UWidget_PlayerEquipmentInventory_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Construct");

	UWidget_PlayerEquipmentInventory_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerEquipmentInventory_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Tick");

	UWidget_PlayerEquipmentInventory_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Destruct
// ()

void UWidget_PlayerEquipmentInventory_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Destruct");

	UWidget_PlayerEquipmentInventory_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.ExecuteUbergraph_Widget_PlayerEquipmentInventory
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerEquipmentInventory_C::ExecuteUbergraph_Widget_PlayerEquipmentInventory(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.ExecuteUbergraph_Widget_PlayerEquipmentInventory");

	UWidget_PlayerEquipmentInventory_C_ExecuteUbergraph_Widget_PlayerEquipmentInventory_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
