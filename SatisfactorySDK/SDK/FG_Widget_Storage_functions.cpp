// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Storage_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Storage.Widget_Storage_C.SetInventoryComp
// ()
// Parameters:
// class UFGInventoryComponent*   InventoryComp                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Storage_C::SetInventoryComp(class UFGInventoryComponent* InventoryComp)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.SetInventoryComp");

	UWidget_Storage_C_SetInventoryComp_Params params;
	params.InventoryComp = InventoryComp;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.OnSortClicked
// ()

void UWidget_Storage_C::OnSortClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.OnSortClicked");

	UWidget_Storage_C_OnSortClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.OnDumpAllClicked
// ()

void UWidget_Storage_C::OnDumpAllClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.OnDumpAllClicked");

	UWidget_Storage_C_OnDumpAllClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.OnGrabAllClicked
// ()

void UWidget_Storage_C::OnGrabAllClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.OnGrabAllClicked");

	UWidget_Storage_C_OnGrabAllClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.BindStorageButtons
// ()

void UWidget_Storage_C::BindStorageButtons()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.BindStorageButtons");

	UWidget_Storage_C_BindStorageButtons_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_Storage_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.DropInventorySlotStack");

	UWidget_Storage_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_Storage.Widget_Storage_C.Cleanup
// ()

void UWidget_Storage_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.Cleanup");

	UWidget_Storage_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.Init
// ()

void UWidget_Storage_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.Init");

	UWidget_Storage_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.Destruct
// ()

void UWidget_Storage_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.Destruct");

	UWidget_Storage_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.Construct
// ()

void UWidget_Storage_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.Construct");

	UWidget_Storage_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.DumpAllInStorage
// ()

void UWidget_Storage_C::DumpAllInStorage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.DumpAllInStorage");

	UWidget_Storage_C_DumpAllInStorage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.GrabAllFromStorage
// ()

void UWidget_Storage_C::GrabAllFromStorage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.GrabAllFromStorage");

	UWidget_Storage_C_GrabAllFromStorage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_Storage_C::BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_Storage_C_BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.OnInventoryComponentReplicated
// ()
// Parameters:
// class AActor*                  replicationDetailActorOwner    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Storage_C::OnInventoryComponentReplicated(class AActor* replicationDetailActorOwner)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.OnInventoryComponentReplicated");

	UWidget_Storage_C_OnInventoryComponentReplicated_Params params;
	params.replicationDetailActorOwner = replicationDetailActorOwner;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Storage.Widget_Storage_C.ExecuteUbergraph_Widget_Storage
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Storage_C::ExecuteUbergraph_Widget_Storage(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Storage.Widget_Storage_C.ExecuteUbergraph_Widget_Storage");

	UWidget_Storage_C_ExecuteUbergraph_Widget_Storage_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
