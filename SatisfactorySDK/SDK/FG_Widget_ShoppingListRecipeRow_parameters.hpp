#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ShoppingListRecipeRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetShoppingListButtonVisibility
struct UWidget_ShoppingListRecipeRow_C_GetShoppingListButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetTextColor
struct UWidget_ShoppingListRecipeRow_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAddButtonIconColor
struct UWidget_ShoppingListRecipeRow_C_GetAddButtonIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAddButtonColor
struct UWidget_ShoppingListRecipeRow_C_GetAddButtonColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRemoveButtonIconColor
struct UWidget_ShoppingListRecipeRow_C_GetRemoveButtonIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRemoveButtonColor
struct UWidget_ShoppingListRecipeRow_C_GetRemoveButtonColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetAmount
struct UWidget_ShoppingListRecipeRow_C_GetAmount_Params
{
	int                                                mAmount;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetRecipe
struct UWidget_ShoppingListRecipeRow_C_GetRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetTitleText
struct UWidget_ShoppingListRecipeRow_C_GetTitleText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.GetNumberText
struct UWidget_ShoppingListRecipeRow_C_GetNumberText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
struct UWidget_ShoppingListRecipeRow_C_BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.BndEvt__mButtonRemove_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
struct UWidget_ShoppingListRecipeRow_C_BndEvt__mButtonRemove_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ShoppingListRecipeRow.Widget_ShoppingListRecipeRow_C.ExecuteUbergraph_Widget_ShoppingListRecipeRow
struct UWidget_ShoppingListRecipeRow_C_ExecuteUbergraph_Widget_ShoppingListRecipeRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
