#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ShoppingListButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetMinusVisibility
struct UWidget_ShoppingListButton_C_GetMinusVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetInputNumberTooltip
struct UWidget_ShoppingListButton_C_GetInputNumberTooltip_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetButtonTooltip
struct UWidget_ShoppingListButton_C_GetButtonTooltip_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetInputTextfieldVisibility
struct UWidget_ShoppingListButton_C_GetInputTextfieldVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.SetAmountText
struct UWidget_ShoppingListButton_C_SetAmountText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetHoverVisibility
struct UWidget_ShoppingListButton_C_GetHoverVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetAmount
struct UWidget_ShoppingListButton_C_GetAmount_Params
{
	int                                                NumberRecipes;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.GetAmountRecipesInListColor
struct UWidget_ShoppingListButton_C_GetAmountRecipesInListColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.BndEvt__Remove1_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_ShoppingListButton_C_BndEvt__Remove1_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.Construct
struct UWidget_ShoppingListButton_C_Construct_Params
{
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.BndEvt__Add1_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_ShoppingListButton_C_BndEvt__Add1_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.BndEvt__mInputNumberToAdd_K2Node_ComponentBoundEvent_0_OnEditableTextBoxCommittedEvent__DelegateSignature
struct UWidget_ShoppingListButton_C_BndEvt__mInputNumberToAdd_K2Node_ComponentBoundEvent_0_OnEditableTextBoxCommittedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.ExecuteUbergraph_Widget_ShoppingListButton
struct UWidget_ShoppingListButton_C_ExecuteUbergraph_Widget_ShoppingListButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ShoppingListButton.Widget_ShoppingListButton_C.OnShortcutRemapClicked__DelegateSignature
struct UWidget_ShoppingListButton_C_OnShortcutRemapClicked__DelegateSignature_Params
{
	int                                                shortcutIndex;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      newRecipe;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
