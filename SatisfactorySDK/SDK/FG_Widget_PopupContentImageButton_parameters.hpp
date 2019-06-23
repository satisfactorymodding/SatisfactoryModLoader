#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupContentImageButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.CacheDataFromReward
struct UWidget_PopupContentImageButton_C_CacheDataFromReward_Params
{
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetIsSmeltable
struct UWidget_PopupContentImageButton_C_GetIsSmeltable_Params
{
	class UClass*                                      inClass;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsSmeltable;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.ClearSelectionList
struct UWidget_PopupContentImageButton_C_ClearSelectionList_Params
{
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetIndexInList
struct UWidget_PopupContentImageButton_C_GetIndexInList_Params
{
	int                                                Index;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetTextColor
struct UWidget_PopupContentImageButton_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetBackgroundColor
struct UWidget_PopupContentImageButton_C_GetBackgroundColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.PreConstruct
struct UWidget_PopupContentImageButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.Construct
struct UWidget_PopupContentImageButton_C_Construct_Params
{
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.UpdateButton
struct UWidget_PopupContentImageButton_C_UpdateButton_Params
{
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FSlateBrush                                 ImageBrush;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_PopupContentImageButton_C_BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_PopupContentImageButton_C_BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_PopupContentImageButton_C_BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.ExecuteUbergraph_Widget_PopupContentImageButton
struct UWidget_PopupContentImageButton_C_ExecuteUbergraph_Widget_PopupContentImageButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.NotifyPopupContentIndexSelect__DelegateSignature
struct UWidget_PopupContentImageButton_C_NotifyPopupContentIndexSelect__DelegateSignature_Params
{
	int                                                ChildIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
