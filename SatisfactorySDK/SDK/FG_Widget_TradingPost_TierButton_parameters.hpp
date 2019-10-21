#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_TierButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.SetLockedText
struct UWidget_TradingPost_TierButton_C_SetLockedText_Params
{
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetTierNumVisibility
struct UWidget_TradingPost_TierButton_C_GetTierNumVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetCheckVisibility
struct UWidget_TradingPost_TierButton_C_GetCheckVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.IsSelectable
struct UWidget_TradingPost_TierButton_C_IsSelectable_Params
{
	bool                                               IsSelectable;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetWidgetClickable
struct UWidget_TradingPost_TierButton_C_GetWidgetClickable_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetTextHoverColor
struct UWidget_TradingPost_TierButton_C_GetTextHoverColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetButtonColor
struct UWidget_TradingPost_TierButton_C_GetButtonColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.UpdateTier
struct UWidget_TradingPost_TierButton_C_UpdateTier_Params
{
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.SetTierNumber
struct UWidget_TradingPost_TierButton_C_SetTierNumber_Params
{
	int                                                TierNumber;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_TradingPost_C*                       Tradingpost;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.BndEvt__Button_2_K2Node_ComponentBoundEvent_70_OnButtonClickedEvent__DelegateSignature
struct UWidget_TradingPost_TierButton_C_BndEvt__Button_2_K2Node_ComponentBoundEvent_70_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.ExecuteUbergraph_Widget_TradingPost_TierButton
struct UWidget_TradingPost_TierButton_C_ExecuteUbergraph_Widget_TradingPost_TierButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
