#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenuRecipeButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.UpdateNewItemOverlayVisibility
struct UWidget_BuildMenuRecipeButton_C_UpdateNewItemOverlayVisibility_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.OnKeyDown
struct UWidget_BuildMenuRecipeButton_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.GetRightClickMenuVisibility
struct UWidget_BuildMenuRecipeButton_C_GetRightClickMenuVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.CreateRightClickMenu
struct UWidget_BuildMenuRecipeButton_C_CreateRightClickMenu_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.OnMouseButtonDown
struct UWidget_BuildMenuRecipeButton_C_OnMouseButtonDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.GetTextHoverColor
struct UWidget_BuildMenuRecipeButton_C_GetTextHoverColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.GetGraphicsHoverColor
struct UWidget_BuildMenuRecipeButton_C_GetGraphicsHoverColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.ResolveHotkeyIndex
struct UWidget_BuildMenuRecipeButton_C_ResolveHotkeyIndex_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.CreateShoppingListButtons
struct UWidget_BuildMenuRecipeButton_C_CreateShoppingListButtons_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.GetBuildingIcon
struct UWidget_BuildMenuRecipeButton_C_GetBuildingIcon_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.OnFocusReceived
struct UWidget_BuildMenuRecipeButton_C_OnFocusReceived_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.GetRecipeName
struct UWidget_BuildMenuRecipeButton_C_GetRecipeName_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.Construct
struct UWidget_BuildMenuRecipeButton_C_Construct_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.BndEvt__mRecipeOverlay_K2Node_ComponentBoundEvent_35_OnButtonHoverEvent__DelegateSignature
struct UWidget_BuildMenuRecipeButton_C_BndEvt__mRecipeOverlay_K2Node_ComponentBoundEvent_35_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.BndEvt__mRecipeOverlay_K2Node_ComponentBoundEvent_439_OnButtonClickedEvent__DelegateSignature
struct UWidget_BuildMenuRecipeButton_C_BndEvt__mRecipeOverlay_K2Node_ComponentBoundEvent_439_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.BndEvt__mRecipeOverlay_K2Node_ComponentBoundEvent_16_OnButtonHoverEvent__DelegateSignature
struct UWidget_BuildMenuRecipeButton_C_BndEvt__mRecipeOverlay_K2Node_ComponentBoundEvent_16_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.SimulateOnHovered
struct UWidget_BuildMenuRecipeButton_C_SimulateOnHovered_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.SimulateOnUnhovered
struct UWidget_BuildMenuRecipeButton_C_SimulateOnUnhovered_Params
{
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.PreConstruct
struct UWidget_BuildMenuRecipeButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.ExecuteUbergraph_Widget_BuildMenuRecipeButton
struct UWidget_BuildMenuRecipeButton_C_ExecuteUbergraph_Widget_BuildMenuRecipeButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.OnStopHoveringRecipe__DelegateSignature
struct UWidget_BuildMenuRecipeButton_C_OnStopHoveringRecipe__DelegateSignature_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_BuildMenuRecipeButton_C*             RecipeButton;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.OnRecipeHovered__DelegateSignature
struct UWidget_BuildMenuRecipeButton_C_OnRecipeHovered__DelegateSignature_Params
{
	class UClass*                                      RecipeHover;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_BuildMenuRecipeButton_C*             RecipeButton;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BuildMenuRecipeButton.Widget_BuildMenuRecipeButton_C.OnRecipeClicked__DelegateSignature
struct UWidget_BuildMenuRecipeButton_C_OnRecipeClicked__DelegateSignature_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
