// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_PayOffGrid_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C* InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_PayOffGrid_C::DropInventorySlotStack(class UWidget_InventorySlot_C* InventorySlot, bool* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.DropInventorySlotStack");

	UWidget_TradingPost_PayOffGrid_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.SetUpPayOffSlots
// ()
// Parameters:
// class UClass*                  mSchematic                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_PayOffGrid_C::SetUpPayOffSlots(class UClass* mSchematic)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.SetUpPayOffSlots");

	UWidget_TradingPost_PayOffGrid_C_SetUpPayOffSlots_Params params;
	params.mSchematic = mSchematic;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.Construct
// ()

void UWidget_TradingPost_PayOffGrid_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.Construct");

	UWidget_TradingPost_PayOffGrid_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.ExecuteUbergraph_Widget_TradingPost_PayOffGrid
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_PayOffGrid_C::ExecuteUbergraph_Widget_TradingPost_PayOffGrid(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.ExecuteUbergraph_Widget_TradingPost_PayOffGrid");

	UWidget_TradingPost_PayOffGrid_C_ExecuteUbergraph_Widget_TradingPost_PayOffGrid_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
