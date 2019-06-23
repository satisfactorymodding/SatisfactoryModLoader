// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DragNDropInventory_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_DragNDropInventory.BP_DragNDropInventory_C.Dragged
// ()
// Parameters:
// struct FPointerEvent*          PointerEvent                   (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UBP_DragNDropInventory_C::Dragged(struct FPointerEvent* PointerEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DragNDropInventory.BP_DragNDropInventory_C.Dragged");

	UBP_DragNDropInventory_C_Dragged_Params params;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DragNDropInventory.BP_DragNDropInventory_C.DragCancelled
// ()
// Parameters:
// struct FPointerEvent*          PointerEvent                   (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UBP_DragNDropInventory_C::DragCancelled(struct FPointerEvent* PointerEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DragNDropInventory.BP_DragNDropInventory_C.DragCancelled");

	UBP_DragNDropInventory_C_DragCancelled_Params params;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DragNDropInventory.BP_DragNDropInventory_C.Drop
// ()
// Parameters:
// struct FPointerEvent*          PointerEvent                   (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UBP_DragNDropInventory_C::Drop(struct FPointerEvent* PointerEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DragNDropInventory.BP_DragNDropInventory_C.Drop");

	UBP_DragNDropInventory_C_Drop_Params params;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DragNDropInventory.BP_DragNDropInventory_C.ExecuteUbergraph_BP_DragNDropInventory
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_DragNDropInventory_C::ExecuteUbergraph_BP_DragNDropInventory(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DragNDropInventory.BP_DragNDropInventory_C.ExecuteUbergraph_BP_DragNDropInventory");

	UBP_DragNDropInventory_C_ExecuteUbergraph_BP_DragNDropInventory_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
