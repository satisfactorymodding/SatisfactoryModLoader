// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CrystalStationContainer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_CrystalStationContainer_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.DropInventorySlotStack");

	UWidget_CrystalStationContainer_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Cleanup
// ()

void UWidget_CrystalStationContainer_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Cleanup");

	UWidget_CrystalStationContainer_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Destruct
// ()

void UWidget_CrystalStationContainer_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Destruct");

	UWidget_CrystalStationContainer_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Init
// ()

void UWidget_CrystalStationContainer_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Init");

	UWidget_CrystalStationContainer_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Construct
// ()

void UWidget_CrystalStationContainer_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Construct");

	UWidget_CrystalStationContainer_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.ExecuteUbergraph_Widget_CrystalStationContainer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CrystalStationContainer_C::ExecuteUbergraph_Widget_CrystalStationContainer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.ExecuteUbergraph_Widget_CrystalStationContainer");

	UWidget_CrystalStationContainer_C_ExecuteUbergraph_Widget_CrystalStationContainer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
