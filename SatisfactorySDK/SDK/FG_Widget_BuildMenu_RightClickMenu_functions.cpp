// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_RightClickMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_BuildMenu_RightClickMenu_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.OnKeyDown");

	UWidget_BuildMenu_RightClickMenu_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverBindToHotbar
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_BuildMenu_RightClickMenu_C::GetHoverBindToHotbar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverBindToHotbar");

	UWidget_BuildMenu_RightClickMenu_C_GetHoverBindToHotbar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverColorCodex
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_BuildMenu_RightClickMenu_C::GetHoverColorCodex()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverColorCodex");

	UWidget_BuildMenu_RightClickMenu_C_GetHoverColorCodex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverColorRemoveFromShoppingList
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_BuildMenu_RightClickMenu_C::GetHoverColorRemoveFromShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverColorRemoveFromShoppingList");

	UWidget_BuildMenu_RightClickMenu_C_GetHoverColorRemoveFromShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverColorAddToShoppingList
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_BuildMenu_RightClickMenu_C::GetHoverColorAddToShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetHoverColorAddToShoppingList");

	UWidget_BuildMenu_RightClickMenu_C_GetHoverColorAddToShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetRemoveItemButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_BuildMenu_RightClickMenu_C::GetRemoveItemButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetRemoveItemButtonVisibility");

	UWidget_BuildMenu_RightClickMenu_C_GetRemoveItemButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetAmount
// ()
// Parameters:
// int                            NumberRecipes                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_RightClickMenu_C::GetAmount(int* NumberRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetAmount");

	UWidget_BuildMenu_RightClickMenu_C_GetAmount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NumberRecipes != nullptr)
		*NumberRecipes = params.NumberRecipes;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetNumberRecipesInShoppingList
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_BuildMenu_RightClickMenu_C::GetNumberRecipesInShoppingList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.GetNumberRecipesInShoppingList");

	UWidget_BuildMenu_RightClickMenu_C_GetNumberRecipesInShoppingList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.Construct
// ()

void UWidget_BuildMenu_RightClickMenu_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.Construct");

	UWidget_BuildMenu_RightClickMenu_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.BndEvt__Button0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_BuildMenu_RightClickMenu_C::BndEvt__Button0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.BndEvt__Button0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_BuildMenu_RightClickMenu_C_BndEvt__Button0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.BndEvt__mRemoveToDoListButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_BuildMenu_RightClickMenu_C::BndEvt__mRemoveToDoListButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.BndEvt__mRemoveToDoListButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_BuildMenu_RightClickMenu_C_BndEvt__mRemoveToDoListButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.ExecuteUbergraph_Widget_BuildMenu_RightClickMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_RightClickMenu_C::ExecuteUbergraph_Widget_BuildMenu_RightClickMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.ExecuteUbergraph_Widget_BuildMenu_RightClickMenu");

	UWidget_BuildMenu_RightClickMenu_C_ExecuteUbergraph_Widget_BuildMenu_RightClickMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.UpdateWindowWidgetOffset__DelegateSignature
// ()

void UWidget_BuildMenu_RightClickMenu_C::UpdateWindowWidgetOffset__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_RightClickMenu.Widget_BuildMenu_RightClickMenu_C.UpdateWindowWidgetOffset__DelegateSignature");

	UWidget_BuildMenu_RightClickMenu_C_UpdateWindowWidgetOffset__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
