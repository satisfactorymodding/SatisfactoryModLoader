#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MenuSwitcherContainer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.GetFirstChildOfSwitcher
struct UWidget_MenuSwitcherContainer_C_GetFirstChildOfSwitcher_Params
{
	class UPanelWidget*                                SwitcherWidget;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget*                                     Child;                                                    // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.SetSwitcherWidget
struct UWidget_MenuSwitcherContainer_C_SetSwitcherWidget_Params
{
	class UWidgetSwitcher*                             Widget_Switcher;                                          // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.SetNoneActive
struct UWidget_MenuSwitcherContainer_C_SetNoneActive_Params
{
};

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.BndEvt__HideSwitcher_K2Node_ComponentBoundEvent_0_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature
struct UWidget_MenuSwitcherContainer_C_BndEvt__HideSwitcher_K2Node_ComponentBoundEvent_0_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature_Params
{
};

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.SetActiveWidget
struct UWidget_MenuSwitcherContainer_C_SetActiveWidget_Params
{
	class UWidget*                                     Widget;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.ExecuteUbergraph_Widget_MenuSwitcherContainer
struct UWidget_MenuSwitcherContainer_C_ExecuteUbergraph_Widget_MenuSwitcherContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MenuSwitcherContainer.Widget_MenuSwitcherContainer_C.OnWidgetSet__DelegateSignature
struct UWidget_MenuSwitcherContainer_C_OnWidgetSet__DelegateSignature_Params
{
	bool                                               mHasChangedActiveWidget;                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
