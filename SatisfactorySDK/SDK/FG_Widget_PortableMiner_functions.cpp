// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PortableMiner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PortableMiner.Widget_PortableMiner_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_PortableMiner_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.DropInventorySlotStack");

	UWidget_PortableMiner_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.InitCallbacks
// ()

void UWidget_PortableMiner_C::InitCallbacks()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.InitCallbacks");

	UWidget_PortableMiner_C_InitCallbacks_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.UpdateMinerInfo
// ()

void UWidget_PortableMiner_C::UpdateMinerInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.UpdateMinerInfo");

	UWidget_PortableMiner_C_UpdateMinerInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.UpdateMinerProgress
// ()

void UWidget_PortableMiner_C::UpdateMinerProgress()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.UpdateMinerProgress");

	UWidget_PortableMiner_C_UpdateMinerProgress_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.Init
// ()

void UWidget_PortableMiner_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.Init");

	UWidget_PortableMiner_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PortableMiner_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.Tick");

	UWidget_PortableMiner_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.Construct
// ()

void UWidget_PortableMiner_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.Construct");

	UWidget_PortableMiner_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.BndEvt__mButtonTakeAllItems_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_PortableMiner_C::BndEvt__mButtonTakeAllItems_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.BndEvt__mButtonTakeAllItems_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_PortableMiner_C_BndEvt__mButtonTakeAllItems_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.BndEvt__mButtonPickUpMiner_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_PortableMiner_C::BndEvt__mButtonPickUpMiner_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.BndEvt__mButtonPickUpMiner_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_PortableMiner_C_BndEvt__mButtonPickUpMiner_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PortableMiner.Widget_PortableMiner_C.ExecuteUbergraph_Widget_PortableMiner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PortableMiner_C::ExecuteUbergraph_Widget_PortableMiner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PortableMiner.Widget_PortableMiner_C.ExecuteUbergraph_Widget_PortableMiner");

	UWidget_PortableMiner_C_ExecuteUbergraph_Widget_PortableMiner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
