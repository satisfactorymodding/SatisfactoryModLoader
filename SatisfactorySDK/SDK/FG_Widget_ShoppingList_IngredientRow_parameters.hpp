#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ShoppingList_IngredientRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetProgressBarBorderColor
struct UWidget_ShoppingList_IngredientRow_C_GetProgressBarBorderColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetTextColor
struct UWidget_ShoppingList_IngredientRow_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetIconBGColor
struct UWidget_ShoppingList_IngredientRow_C_GetIconBGColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetBorderVisibility
struct UWidget_ShoppingList_IngredientRow_C_GetBorderVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetProgressBGColor
struct UWidget_ShoppingList_IngredientRow_C_GetProgressBGColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetIconVisibility
struct UWidget_ShoppingList_IngredientRow_C_GetIconVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetCheckboxVisibility
struct UWidget_ShoppingList_IngredientRow_C_GetCheckboxVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetProgressBarColor
struct UWidget_ShoppingList_IngredientRow_C_GetProgressBarColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetToDoListProgressBarPercentage
struct UWidget_ShoppingList_IngredientRow_C_GetToDoListProgressBarPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetNumIngredientsOwned
struct UWidget_ShoppingList_IngredientRow_C_GetNumIngredientsOwned_Params
{
	int                                                NumItems;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetNumberIngredientsInInventoryText
struct UWidget_ShoppingList_IngredientRow_C_GetNumberIngredientsInInventoryText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetIngredient
struct UWidget_ShoppingList_IngredientRow_C_GetIngredient_Params
{
	struct FItemAmount                                 ingredient;                                               // (Parm, OutParm)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetIcon
struct UWidget_ShoppingList_IngredientRow_C_GetIcon_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetIngredientTitleText
struct UWidget_ShoppingList_IngredientRow_C_GetIngredientTitleText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.GetIngredientNumberText
struct UWidget_ShoppingList_IngredientRow_C_GetIngredientNumberText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.Construct
struct UWidget_ShoppingList_IngredientRow_C_Construct_Params
{
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.Tick
struct UWidget_ShoppingList_IngredientRow_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingList_IngredientRow.Widget_ShoppingList_IngredientRow_C.ExecuteUbergraph_Widget_ShoppingList_IngredientRow
struct UWidget_ShoppingList_IngredientRow_C_ExecuteUbergraph_Widget_ShoppingList_IngredientRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
