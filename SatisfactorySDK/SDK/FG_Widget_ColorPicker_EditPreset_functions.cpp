// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_EditPreset_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_EditPreset_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.PreConstruct");

	UWidget_ColorPicker_EditPreset_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_EditPreset_C::BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_ColorPicker_EditPreset_C_BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_EditPreset_C::BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_ColorPicker_EditPreset_C_BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.OnPopupConfirm
// ()
// Parameters:
// bool                           ConfirmClicked                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_EditPreset_C::OnPopupConfirm(bool ConfirmClicked)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.OnPopupConfirm");

	UWidget_ColorPicker_EditPreset_C_OnPopupConfirm_Params params;
	params.ConfirmClicked = ConfirmClicked;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mPrimaryColorPicker_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature
// ()

void UWidget_ColorPicker_EditPreset_C::BndEvt__mPrimaryColorPicker_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mPrimaryColorPicker_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_EditPreset_C_BndEvt__mPrimaryColorPicker_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mSecondaryColorPicker_K2Node_ComponentBoundEvent_3_OnValueChanged__DelegateSignature
// ()

void UWidget_ColorPicker_EditPreset_C::BndEvt__mSecondaryColorPicker_K2Node_ComponentBoundEvent_3_OnValueChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mSecondaryColorPicker_K2Node_ComponentBoundEvent_3_OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_EditPreset_C_BndEvt__mSecondaryColorPicker_K2Node_ComponentBoundEvent_3_OnValueChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.ExecuteUbergraph_Widget_ColorPicker_EditPreset
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_EditPreset_C::ExecuteUbergraph_Widget_ColorPicker_EditPreset(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.ExecuteUbergraph_Widget_ColorPicker_EditPreset");

	UWidget_ColorPicker_EditPreset_C_ExecuteUbergraph_Widget_ColorPicker_EditPreset_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.OnAccept__DelegateSignature
// ()
// Parameters:
// struct FLinearColor            PrimaryColor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            SecondaryColor                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_EditPreset_C::OnAccept__DelegateSignature(const struct FLinearColor& PrimaryColor, const struct FLinearColor& SecondaryColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.OnAccept__DelegateSignature");

	UWidget_ColorPicker_EditPreset_C_OnAccept__DelegateSignature_Params params;
	params.PrimaryColor = PrimaryColor;
	params.SecondaryColor = SecondaryColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
