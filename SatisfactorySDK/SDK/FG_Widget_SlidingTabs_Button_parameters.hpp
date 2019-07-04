#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SlidingTabs_Button_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetBackgroundVisibility
struct UWidget_SlidingTabs_Button_C_SetBackgroundVisibility_Params
{
	bool                                               Visible;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetIcon
struct UWidget_SlidingTabs_Button_C_SetIcon_Params
{
	class UTexture*                                    Texture;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetTitle
struct UWidget_SlidingTabs_Button_C_SetTitle_Params
{
	struct FText                                       mTitle;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetActive
struct UWidget_SlidingTabs_Button_C_SetActive_Params
{
	bool                                               IsActive;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_SlidingTabs_Button_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.Construct
struct UWidget_SlidingTabs_Button_C_Construct_Params
{
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.PreConstruct
struct UWidget_SlidingTabs_Button_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_SlidingTabs_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_SlidingTabs_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.StartAutoScroll
struct UWidget_SlidingTabs_Button_C_StartAutoScroll_Params
{
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.ExecuteUbergraph_Widget_SlidingTabs_Button
struct UWidget_SlidingTabs_Button_C_ExecuteUbergraph_Widget_SlidingTabs_Button_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnUnhovered__DelegateSignature
struct UWidget_SlidingTabs_Button_C_OnUnhovered__DelegateSignature_Params
{
	class UWidget_SlidingTabs_Button_C*                Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnHovered__DelegateSignature
struct UWidget_SlidingTabs_Button_C_OnHovered__DelegateSignature_Params
{
	class UWidget_SlidingTabs_Button_C*                Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnClicked__DelegateSignature
struct UWidget_SlidingTabs_Button_C_OnClicked__DelegateSignature_Params
{
	class UWidget_SlidingTabs_Button_C*                Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
