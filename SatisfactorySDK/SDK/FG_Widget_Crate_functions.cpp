// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Crate_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Crate.Widget_Crate_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_Crate_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.DropInventorySlotStack");

	UWidget_Crate_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_Crate.Widget_Crate_C.Cleanup
// ()

void UWidget_Crate_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.Cleanup");

	UWidget_Crate_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Crate.Widget_Crate_C.Init
// ()

void UWidget_Crate_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.Init");

	UWidget_Crate_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Crate.Widget_Crate_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Crate_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.Tick");

	UWidget_Crate_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Crate.Widget_Crate_C.Construct
// ()

void UWidget_Crate_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.Construct");

	UWidget_Crate_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Crate.Widget_Crate_C.Destruct
// ()

void UWidget_Crate_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.Destruct");

	UWidget_Crate_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Crate.Widget_Crate_C.OnGrabAll
// ()

void UWidget_Crate_C::OnGrabAll()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.OnGrabAll");

	UWidget_Crate_C_OnGrabAll_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Crate.Widget_Crate_C.ExecuteUbergraph_Widget_Crate
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Crate_C::ExecuteUbergraph_Widget_Crate(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Crate.Widget_Crate_C.ExecuteUbergraph_Widget_Crate");

	UWidget_Crate_C_ExecuteUbergraph_Widget_Crate_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
