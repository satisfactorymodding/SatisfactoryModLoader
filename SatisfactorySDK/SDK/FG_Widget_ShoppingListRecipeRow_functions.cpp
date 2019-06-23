// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ShoppingListRecipeRow_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetShoppingListButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ShoppingListRecipeRow_C::GetShoppingListButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetShoppingListButtonVisibility");

	UWidget_ShoppingListRecipeRow_C_GetShoppingListButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_ShoppingListRecipeRow_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetTextColor");

	UWidget_ShoppingListRecipeRow_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAddButtonIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ShoppingListRecipeRow_C::GetAddButtonIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAddButtonIconColor");

	UWidget_ShoppingListRecipeRow_C_GetAddButtonIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAddButtonColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ShoppingListRecipeRow_C::GetAddButtonColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAddButtonColor");

	UWidget_ShoppingListRecipeRow_C_GetAddButtonColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRemoveButtonIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ShoppingListRecipeRow_C::GetRemoveButtonIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRemoveButtonIconColor");

	UWidget_ShoppingListRecipeRow_C_GetRemoveButtonIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRemoveButtonColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ShoppingListRecipeRow_C::GetRemoveButtonColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRemoveButtonColor");

	UWidget_ShoppingListRecipeRow_C_GetRemoveButtonColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAmount
// ()
// Parameters:
// int                            mAmount                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ShoppingListRecipeRow_C::GetAmount(int* mAmount)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAmount");

	UWidget_ShoppingListRecipeRow_C_GetAmount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (mAmount != nullptr)
		*mAmount = params.mAmount;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRecipe
// ()
// Parameters:
// class UClass*                  Recipe                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ShoppingListRecipeRow_C::GetRecipe(class UClass** Recipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRecipe");

	UWidget_ShoppingListRecipeRow_C_GetRecipe_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Recipe != nullptr)
		*Recipe = params.Recipe;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetTitleText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ShoppingListRecipeRow_C::GetTitleText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetTitleText");

	UWidget_ShoppingListRecipeRow_C_GetTitleText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetNumberText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ShoppingListRecipeRow_C::GetNumberText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetNumberText");

	UWidget_ShoppingListRecipeRow_C_GetNumberText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ShoppingListRecipeRow_C::BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature");

	UWidget_ShoppingListRecipeRow_C_BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.BndEvt__mButtonRemove_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ShoppingListRecipeRow_C::BndEvt__mButtonRemove_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.BndEvt__mButtonRemove_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature");

	UWidget_ShoppingListRecipeRow_C_BndEvt__mButtonRemove_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.ExecuteUbergraph_Widget_ShoppingListRecipeRow
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ShoppingListRecipeRow_C::ExecuteUbergraph_Widget_ShoppingListRecipeRow(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.ExecuteUbergraph_Widget_ShoppingListRecipeRow");

	UWidget_ShoppingListRecipeRow_C_ExecuteUbergraph_Widget_ShoppingListRecipeRow_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
