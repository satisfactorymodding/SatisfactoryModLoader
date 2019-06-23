#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManufacturingButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.UpdateButtonStyle
struct UWidget_ManufacturingButton_C_UpdateButtonStyle_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.CheckIsSelected
struct UWidget_ManufacturingButton_C_CheckIsSelected_Params
{
	bool                                               mIsSelected;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.GetRecipeName
struct UWidget_ManufacturingButton_C_GetRecipeName_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.GetRecipeIcon
struct UWidget_ManufacturingButton_C_GetRecipeIcon_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.OnMouseButtonDown
struct UWidget_ManufacturingButton_C_OnMouseButtonDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_ManufacturingButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_ManufacturingButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_ManufacturingButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.Construct
struct UWidget_ManufacturingButton_C_Construct_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.PreConstruct
struct UWidget_ManufacturingButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.Destruct
struct UWidget_ManufacturingButton_C_Destruct_Params
{
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.ExecuteUbergraph_Widget_ManufacturingButton
struct UWidget_ManufacturingButton_C_ExecuteUbergraph_Widget_ManufacturingButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.OnStopHoveringManufacturingRecipe__DelegateSignature
struct UWidget_ManufacturingButton_C_OnStopHoveringManufacturingRecipe__DelegateSignature_Params
{
	class UClass*                                      UnhoveredRecipe;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.OnManufacturingRecipeHovered__DelegateSignature
struct UWidget_ManufacturingButton_C_OnManufacturingRecipeHovered__DelegateSignature_Params
{
	class UClass*                                      RecipeHover;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingButton.Widget_ManufacturingButton_C.OnManufacturingRecipeClicked__DelegateSignature
struct UWidget_ManufacturingButton_C_OnManufacturingRecipeClicked__DelegateSignature_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
