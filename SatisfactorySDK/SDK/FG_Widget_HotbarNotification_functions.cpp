// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HotbarNotification_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HotbarNotification.Widget_HotbarNotification_C.GetDarkGrayColour
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_HotbarNotification_C::GetDarkGrayColour()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarNotification.Widget_HotbarNotification_C.GetDarkGrayColour");

	UWidget_HotbarNotification_C_GetDarkGrayColour_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_HotbarNotification.Widget_HotbarNotification_C.BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_0_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature
// ()

void UWidget_HotbarNotification_C::BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_0_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarNotification.Widget_HotbarNotification_C.BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_0_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature");

	UWidget_HotbarNotification_C_BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_0_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarNotification.Widget_HotbarNotification_C.BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_1_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature
// ()

void UWidget_HotbarNotification_C::BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_1_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarNotification.Widget_HotbarNotification_C.BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_1_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature");

	UWidget_HotbarNotification_C_BndEvt__HotbarPopUp_K2Node_ComponentBoundEvent_1_OnWidgetAnimationPlaybackStatusChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarNotification.Widget_HotbarNotification_C.ExecuteUbergraph_Widget_HotbarNotification
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HotbarNotification_C::ExecuteUbergraph_Widget_HotbarNotification(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarNotification.Widget_HotbarNotification_C.ExecuteUbergraph_Widget_HotbarNotification");

	UWidget_HotbarNotification_C_ExecuteUbergraph_Widget_HotbarNotification_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
