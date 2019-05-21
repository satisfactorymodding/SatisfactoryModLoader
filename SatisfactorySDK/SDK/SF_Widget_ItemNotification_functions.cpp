// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_ItemNotification_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsPickedUp
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ItemNotification_C::GetNumItemsPickedUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsPickedUp");

	UWidget_ItemNotification_C_GetNumItemsPickedUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.GetItemName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ItemNotification_C::GetItemName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.GetItemName");

	UWidget_ItemNotification_C_GetItemName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsInInventory
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ItemNotification_C::GetNumItemsInInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsInInventory");

	UWidget_ItemNotification_C_GetNumItemsInInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
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


// Function Widget_ItemNotification.Widget_ItemNotification_C.GetAddText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ItemNotification_C::GetAddText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ItemNotification.Widget_ItemNotification_C.GetAddText");

	UWidget_ItemNotification_C_GetAddText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
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
