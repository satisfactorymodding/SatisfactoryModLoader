#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ListButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ListButton.Widget_ListButton_C.GetIconColor
struct UWidget_ListButton_C_GetIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ListButton.Widget_ListButton_C.ClearListSelection
struct UWidget_ListButton_C_ClearListSelection_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.GetIndexInList
struct UWidget_ListButton_C_GetIndexInList_Params
{
	int                                                Index;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ListButton.Widget_ListButton_C.GetTextColor
struct UWidget_ListButton_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ListButton.Widget_ListButton_C.GetButtonBackground
struct UWidget_ListButton_C_GetButtonBackground_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ListButton.Widget_ListButton_C.UpdateButton
struct UWidget_ListButton_C_UpdateButton_Params
{
	class UTexture*                                    Icon;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       Description;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
	ESlateVisibility                                   descVisibility;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ESlateVisibility                                   iconVisibility;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       AdditionalInfo;                                           // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_ListButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.mSetDisabled
struct UWidget_ListButton_C_mSetDisabled_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.mSetEnabled
struct UWidget_ListButton_C_mSetEnabled_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_ListButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.PreConstruct
struct UWidget_ListButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_ListButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.Construct
struct UWidget_ListButton_C_Construct_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.SendClick
struct UWidget_ListButton_C_SendClick_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.ExecuteUbergraph_Widget_ListButton
struct UWidget_ListButton_C_ExecuteUbergraph_Widget_ListButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ListButton.Widget_ListButton_C.OnUnhovered__DelegateSignature
struct UWidget_ListButton_C_OnUnhovered__DelegateSignature_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.OnHovered__DelegateSignature
struct UWidget_ListButton_C_OnHovered__DelegateSignature_Params
{
};

// Function Widget_ListButton.Widget_ListButton_C.OnClicked__DelegateSignature
struct UWidget_ListButton_C_OnClicked__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
