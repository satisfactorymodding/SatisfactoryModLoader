// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AreaSelection_Button_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.IsMediaPlayerValid
// ()
// Parameters:
// bool                           IsValid                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_AreaSelection_Button_C::IsMediaPlayerValid(bool* IsValid)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.IsMediaPlayerValid");

	UWidget_AreaSelection_Button_C_IsMediaPlayerValid_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsValid != nullptr)
		*IsValid = params.IsValid;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SetBorderTint
// ()
// Parameters:
// struct FSlateColor             Color                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_AreaSelection_Button_C::SetBorderTint(const struct FSlateColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SetBorderTint");

	UWidget_AreaSelection_Button_C_SetBorderTint_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.DeselectAnim
// ()

void UWidget_AreaSelection_Button_C::DeselectAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.DeselectAnim");

	UWidget_AreaSelection_Button_C_DeselectAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SelectAnim
// ()

void UWidget_AreaSelection_Button_C::SelectAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SelectAnim");

	UWidget_AreaSelection_Button_C_SelectAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SetSelected
// ()
// Parameters:
// bool                           isSelected                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AreaSelection_Button_C::SetSelected(bool isSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SetSelected");

	UWidget_AreaSelection_Button_C_SetSelected_Params params;
	params.isSelected = isSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AreaSelection_Button_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.PreConstruct");

	UWidget_AreaSelection_Button_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.Construct
// ()

void UWidget_AreaSelection_Button_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.Construct");

	UWidget_AreaSelection_Button_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_AreaSelection_Button_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_AreaSelection_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_AreaSelection_Button_C::BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_AreaSelection_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_AreaSelection_Button_C::BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_AreaSelection_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.ExecuteUbergraph_Widget_AreaSelection_Button
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AreaSelection_Button_C::ExecuteUbergraph_Widget_AreaSelection_Button(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.ExecuteUbergraph_Widget_AreaSelection_Button");

	UWidget_AreaSelection_Button_C_ExecuteUbergraph_Widget_AreaSelection_Button_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.OnClicked__DelegateSignature
// ()
// Parameters:
// TEnumAsByte<EStartingLocations> StartingLoc                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AreaSelection_Button_C::OnClicked__DelegateSignature(TEnumAsByte<EStartingLocations> StartingLoc)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.OnClicked__DelegateSignature");

	UWidget_AreaSelection_Button_C_OnClicked__DelegateSignature_Params params;
	params.StartingLoc = StartingLoc;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
