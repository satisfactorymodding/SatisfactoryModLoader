#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SaveListRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SaveListRow.Widget_SaveListRow_C.SetColorForImage
struct UWidget_SaveListRow_C_SetColorForImage_Params
{
	class UImage*                                      ImageBG;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetNewSaveGameVisibility
struct UWidget_SaveListRow_C_GetNewSaveGameVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetLoadDeleteVisibility
struct UWidget_SaveListRow_C_GetLoadDeleteVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.OnFocusReceived
struct UWidget_SaveListRow_C_OnFocusReceived_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveNameTextColor
struct UWidget_SaveListRow_C_GetSaveNameTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetTextColor
struct UWidget_SaveListRow_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetIconBGColor
struct UWidget_SaveListRow_C_GetIconBGColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetIconColor
struct UWidget_SaveListRow_C_GetIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetButtonColor
struct UWidget_SaveListRow_C_GetButtonColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetNewSaveVisibility
struct UWidget_SaveListRow_C_GetNewSaveVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSessionName
struct UWidget_SaveListRow_C_GetSessionName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveDuration
struct UWidget_SaveListRow_C_GetSaveDuration_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetDesiredFileName
struct UWidget_SaveListRow_C_GetDesiredFileName_Params
{
	class FString                                      desiredFileName;                                          // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.Clicked
struct UWidget_SaveListRow_C_Clicked_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveMap
struct UWidget_SaveListRow_C_GetSaveMap_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveVersion
struct UWidget_SaveListRow_C_GetSaveVersion_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_SaveListRow_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
struct UWidget_SaveListRow_C_BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
struct UWidget_SaveListRow_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.OnWorldSave
struct UWidget_SaveListRow_C_OnWorldSave_Params
{
	bool                                               wasSuccessful;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       errorMessage;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.ConfirmDeleteSessionPopUp
struct UWidget_SaveListRow_C_ConfirmDeleteSessionPopUp_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_SaveListRow_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.DeleteSave
struct UWidget_SaveListRow_C_DeleteSave_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
struct UWidget_SaveListRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.Construct
struct UWidget_SaveListRow_C_Construct_Params
{
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.ExecuteUbergraph_Widget_SaveListRow
struct UWidget_SaveListRow_C_ExecuteUbergraph_Widget_SaveListRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveListRow.Widget_SaveListRow_C.OnClicked__DelegateSignature
struct UWidget_SaveListRow_C_OnClicked__DelegateSignature_Params
{
	class UWidget_SaveListRow_C*                       clickedRow;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
