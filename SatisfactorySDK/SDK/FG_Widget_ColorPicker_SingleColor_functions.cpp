// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_SingleColor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.SetupStartColor
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_SingleColor_C::SetupStartColor(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.SetupStartColor");

	UWidget_ColorPicker_SingleColor_C_SetupStartColor_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_SingleColor_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.PreConstruct");

	UWidget_ColorPicker_SingleColor_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_SingleColor_C::BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_ColorPicker_SingleColor_C_BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_SingleColor_C::BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_ColorPicker_SingleColor_C_BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.ExecuteUbergraph_Widget_ColorPicker_SingleColor
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_SingleColor_C::ExecuteUbergraph_Widget_ColorPicker_SingleColor(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.ExecuteUbergraph_Widget_ColorPicker_SingleColor");

	UWidget_ColorPicker_SingleColor_C_ExecuteUbergraph_Widget_ColorPicker_SingleColor_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.OnClose__DelegateSignature
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_SingleColor_C::OnClose__DelegateSignature(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.OnClose__DelegateSignature");

	UWidget_ColorPicker_SingleColor_C_OnClose__DelegateSignature_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
