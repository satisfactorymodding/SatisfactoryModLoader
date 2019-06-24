// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SocialMediaButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.GetHoverState
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SocialMediaButton_C::GetHoverState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.GetHoverState");

	UWidget_SocialMediaButton_C_GetHoverState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.GetIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_SocialMediaButton_C::GetIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.GetIcon");

	UWidget_SocialMediaButton_C_GetIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_55_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SocialMediaButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_55_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_55_OnButtonClickedEvent__DelegateSignature");

	UWidget_SocialMediaButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_55_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SocialMediaButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_SocialMediaButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SocialMediaButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_SocialMediaButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.ExecuteUbergraph_Widget_SocialMediaButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SocialMediaButton_C::ExecuteUbergraph_Widget_SocialMediaButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SocialMediaButton.Widget_SocialMediaButton_C.ExecuteUbergraph_Widget_SocialMediaButton");

	UWidget_SocialMediaButton_C_ExecuteUbergraph_Widget_SocialMediaButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
