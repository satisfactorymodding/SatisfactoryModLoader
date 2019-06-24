#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SwitchingImage_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SwitchingImage.Widget_SwitchingImage_C.PreConstruct
struct UWidget_SwitchingImage_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchingImage.Widget_SwitchingImage_C.EventImageSwitch
struct UWidget_SwitchingImage_C_EventImageSwitch_Params
{
};

// Function Widget_SwitchingImage.Widget_SwitchingImage_C.SwitchImage
struct UWidget_SwitchingImage_C_SwitchImage_Params
{
	class UTexture*                                    newTexture;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchingImage.Widget_SwitchingImage_C.BndEvt__mSwitchImageAnim_K2Node_ComponentBoundEvent_2_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature
struct UWidget_SwitchingImage_C_BndEvt__mSwitchImageAnim_K2Node_ComponentBoundEvent_2_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature_Params
{
};

// Function Widget_SwitchingImage.Widget_SwitchingImage_C.ExecuteUbergraph_Widget_SwitchingImage
struct UWidget_SwitchingImage_C_ExecuteUbergraph_Widget_SwitchingImage_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchingImage.Widget_SwitchingImage_C.OnSwitchAnimationFinished__DelegateSignature
struct UWidget_SwitchingImage_C_OnSwitchAnimationFinished__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
