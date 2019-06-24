// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_VehicleTrunk_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.OnPreviewKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_VehicleTrunk_C::OnPreviewKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.OnPreviewKeyDown");

	UWidget_VehicleTrunk_C_OnPreviewKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.SetTitle
// ()

void UWidget_VehicleTrunk_C::SetTitle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.SetTitle");

	UWidget_VehicleTrunk_C_SetTitle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.InitCallbacks
// ()

void UWidget_VehicleTrunk_C::InitCallbacks()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.InitCallbacks");

	UWidget_VehicleTrunk_C_InitCallbacks_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_VehicleTrunk_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.DropInventorySlotStack");

	UWidget_VehicleTrunk_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.SetWindowAlignment
// ()

void UWidget_VehicleTrunk_C::SetWindowAlignment()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.SetWindowAlignment");

	UWidget_VehicleTrunk_C_SetWindowAlignment_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.CloseVehicle
// ()

void UWidget_VehicleTrunk_C::CloseVehicle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.CloseVehicle");

	UWidget_VehicleTrunk_C_CloseVehicle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Cleanup
// ()

void UWidget_VehicleTrunk_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Cleanup");

	UWidget_VehicleTrunk_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Destruct
// ()

void UWidget_VehicleTrunk_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Destruct");

	UWidget_VehicleTrunk_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Init
// ()

void UWidget_VehicleTrunk_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Init");

	UWidget_VehicleTrunk_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Construct
// ()

void UWidget_VehicleTrunk_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Construct");

	UWidget_VehicleTrunk_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.GrabAllFromVehicleStorage
// ()

void UWidget_VehicleTrunk_C::GrabAllFromVehicleStorage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.GrabAllFromVehicleStorage");

	UWidget_VehicleTrunk_C_GrabAllFromVehicleStorage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.StoreAllInVehicleStorage
// ()

void UWidget_VehicleTrunk_C::StoreAllInVehicleStorage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.StoreAllInVehicleStorage");

	UWidget_VehicleTrunk_C_StoreAllInVehicleStorage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_VehicleTrunk_C::BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_VehicleTrunk_C_BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.ExecuteUbergraph_Widget_VehicleTrunk
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_VehicleTrunk_C::ExecuteUbergraph_Widget_VehicleTrunk(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.ExecuteUbergraph_Widget_VehicleTrunk");

	UWidget_VehicleTrunk_C_ExecuteUbergraph_Widget_VehicleTrunk_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
