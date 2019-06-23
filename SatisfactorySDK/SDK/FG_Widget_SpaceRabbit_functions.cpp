// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpaceRabbit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceRabbit_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.DropInventorySlotStack");

	UWidget_SpaceRabbit_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Cleanup
// ()

void UWidget_SpaceRabbit_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Cleanup");

	UWidget_SpaceRabbit_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Init
// ()

void UWidget_SpaceRabbit_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Init");

	UWidget_SpaceRabbit_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Construct
// ()

void UWidget_SpaceRabbit_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Construct");

	UWidget_SpaceRabbit_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Destruct
// ()

void UWidget_SpaceRabbit_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Destruct");

	UWidget_SpaceRabbit_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.ExecuteUbergraph_Widget_SpaceRabbit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceRabbit_C::ExecuteUbergraph_Widget_SpaceRabbit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.ExecuteUbergraph_Widget_SpaceRabbit");

	UWidget_SpaceRabbit_C_ExecuteUbergraph_Widget_SpaceRabbit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
