#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RecipeButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RecipeButton.Widget_RecipeButton_C.ClearButtonSelection
struct UWidget_RecipeButton_C_ClearButtonSelection_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetCustomTooltip
struct UWidget_RecipeButton_C_GetCustomTooltip_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetRightClickMenuVisibility
struct UWidget_RecipeButton_C_GetRightClickMenuVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.CreateRightClickMenu
struct UWidget_RecipeButton_C_CreateRightClickMenu_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetButtonHoverColor
struct UWidget_RecipeButton_C_GetButtonHoverColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetTextHoverColor
struct UWidget_RecipeButton_C_GetTextHoverColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.IsButtonEnabled
struct UWidget_RecipeButton_C_IsButtonEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduce
struct UWidget_RecipeButton_C_GetNumCanProduce_Params
{
	int                                                Result;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduceVisibility
struct UWidget_RecipeButton_C_GetNumCanProduceVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduceText
struct UWidget_RecipeButton_C_GetNumCanProduceText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.CheckIngredients
struct UWidget_RecipeButton_C_CheckIngredients_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetRecipeIcon
struct UWidget_RecipeButton_C_GetRecipeIcon_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetIconColor
struct UWidget_RecipeButton_C_GetIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.OnMouseButtonDown
struct UWidget_RecipeButton_C_OnMouseButtonDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.GetRecipeDisplayName
struct UWidget_RecipeButton_C_GetRecipeDisplayName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.Construct
struct UWidget_RecipeButton_C_Construct_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.Tick
struct UWidget_RecipeButton_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.OnClicked
struct UWidget_RecipeButton_C_OnClicked_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.OnHovered
struct UWidget_RecipeButton_C_OnHovered_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.OnPressed
struct UWidget_RecipeButton_C_OnPressed_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.OnMouseLeave
struct UWidget_RecipeButton_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.UpdateWindowWidgetOffset_Event
struct UWidget_RecipeButton_C_UpdateWindowWidgetOffset_Event_Params
{
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_RecipeButton_C_BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.ExecuteUbergraph_Widget_RecipeButton
struct UWidget_RecipeButton_C_ExecuteUbergraph_Widget_RecipeButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.OnRecipeButtonClicked__DelegateSignature
struct UWidget_RecipeButton_C_OnRecipeButtonClicked__DelegateSignature_Params
{
	class UWidget_RecipeButton_C*                      ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_RecipeButton.Widget_RecipeButton_C.UpdateWindowWidgetOffset__DelegateSignature
struct UWidget_RecipeButton_C_UpdateWindowWidgetOffset__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
