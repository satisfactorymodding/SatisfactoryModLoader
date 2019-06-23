// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventorySlot_DropArea_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C.OnDropInventorySlot
// ()
// Parameters:
// class UWidget_InventorySlot_C* InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_DropArea_C::OnDropInventorySlot(class UWidget_InventorySlot_C* InventorySlot, bool* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C.OnDropInventorySlot");

	UWidget_InventorySlot_DropArea_C_OnDropInventorySlot_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C.FindCorrectSlot
// ()
// Parameters:
// class UWidget_InventorySlot_C* payload                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UWidget_InventorySlot_C* InventorySlot                  (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Success                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_DropArea_C::FindCorrectSlot(class UWidget_InventorySlot_C* payload, class UWidget_InventorySlot_C** InventorySlot, bool* Success)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C.FindCorrectSlot");

	UWidget_InventorySlot_DropArea_C_FindCorrectSlot_Params params;
	params.payload = payload;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (InventorySlot != nullptr)
		*InventorySlot = params.InventorySlot;
	if (Success != nullptr)
		*Success = params.Success;
}


// Function Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_InventorySlot_DropArea_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C.OnDrop");

	UWidget_InventorySlot_DropArea_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
