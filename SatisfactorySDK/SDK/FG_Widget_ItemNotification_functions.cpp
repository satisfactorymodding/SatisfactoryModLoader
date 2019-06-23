// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ItemNotification_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ItemNotification.Widget_ItemNotification_C.GetTotalNumItemsInPlayerInventory
// ()

void UWidget_ItemNotification_C::GetTotalNumItemsInPlayerInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.GetTotalNumItemsInPlayerInventory");

	UWidget_ItemNotification_C_GetTotalNumItemsInPlayerInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsPickedUp
// ()

void UWidget_ItemNotification_C::GetNumItemsPickedUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsPickedUp");

	UWidget_ItemNotification_C_GetNumItemsPickedUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.AddToNumItems
// ()
// Parameters:
// int                            NumItems                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ItemNotification_C::AddToNumItems(int NumItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.AddToNumItems");

	UWidget_ItemNotification_C_AddToNumItems_Params params;
	params.NumItems = NumItems;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.Construct
// ()

void UWidget_ItemNotification_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.Construct");

	UWidget_ItemNotification_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.Destruct
// ()

void UWidget_ItemNotification_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.Destruct");

	UWidget_ItemNotification_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.UpdatePickUpAmount
// ()

void UWidget_ItemNotification_C::UpdatePickUpAmount()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.UpdatePickUpAmount");

	UWidget_ItemNotification_C_UpdatePickUpAmount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.ExecuteUbergraph_Widget_ItemNotification
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ItemNotification_C::ExecuteUbergraph_Widget_ItemNotification(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.ExecuteUbergraph_Widget_ItemNotification");

	UWidget_ItemNotification_C_ExecuteUbergraph_Widget_ItemNotification_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
