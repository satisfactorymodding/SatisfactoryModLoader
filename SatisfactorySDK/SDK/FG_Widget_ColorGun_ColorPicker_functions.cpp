// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorGun_ColorPicker_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.CompressValue
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          MinValue                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Out_Value                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::CompressValue(float Value, float MinValue, float* Out_Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.CompressValue");

	UWidget_ColorGun_ColorPicker_C_CompressValue_Params params;
	params.Value = Value;
	params.MinValue = MinValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Out_Value != nullptr)
		*Out_Value = params.Out_Value;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.ConvertColorToPreviewColor
// ()
// Parameters:
// struct FLinearColor            InputColor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          MinValue                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            OutputColor                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::ConvertColorToPreviewColor(const struct FLinearColor& InputColor, float MinValue, struct FLinearColor* OutputColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.ConvertColorToPreviewColor");

	UWidget_ColorGun_ColorPicker_C_ConvertColorToPreviewColor_Params params;
	params.InputColor = InputColor;
	params.MinValue = MinValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutputColor != nullptr)
		*OutputColor = params.OutputColor;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.UpdatePreview
// ()

void UWidget_ColorGun_ColorPicker_C::UpdatePreview()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.UpdatePreview");

	UWidget_ColorGun_ColorPicker_C_UpdatePreview_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.SetupSlots
// ()

void UWidget_ColorGun_ColorPicker_C::SetupSlots()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.SetupSlots");

	UWidget_ColorGun_ColorPicker_C_SetupSlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.Construct
// ()

void UWidget_ColorGun_ColorPicker_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.Construct");

	UWidget_ColorGun_ColorPicker_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotClicked
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::OnSlotClicked(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotClicked");

	UWidget_ColorGun_ColorPicker_C_OnSlotClicked_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotHovered
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::OnSlotHovered(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotHovered");

	UWidget_ColorGun_ColorPicker_C_OnSlotHovered_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotUnhovered
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::OnSlotUnhovered(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotUnhovered");

	UWidget_ColorGun_ColorPicker_C_OnSlotUnhovered_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_ColorGun_ColorPicker_C::BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_ColorGun_ColorPicker_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_ColorGun_ColorPicker_C::BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_ColorGun_ColorPicker_C_BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotEditClicked
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::OnSlotEditClicked(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotEditClicked");

	UWidget_ColorGun_ColorPicker_C_OnSlotEditClicked_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnUpdatePreset
// ()
// Parameters:
// struct FLinearColor            PrimaryColor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            SecondaryColor                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::OnUpdatePreset(const struct FLinearColor& PrimaryColor, const struct FLinearColor& SecondaryColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnUpdatePreset");

	UWidget_ColorGun_ColorPicker_C_OnUpdatePreset_Params params;
	params.PrimaryColor = PrimaryColor;
	params.SecondaryColor = SecondaryColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.ExecuteUbergraph_Widget_ColorGun_ColorPicker
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGun_ColorPicker_C::ExecuteUbergraph_Widget_ColorGun_ColorPicker(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.ExecuteUbergraph_Widget_ColorGun_ColorPicker");

	UWidget_ColorGun_ColorPicker_C_ExecuteUbergraph_Widget_ColorGun_ColorPicker_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnCancel__DelegateSignature
// ()

void UWidget_ColorGun_ColorPicker_C::OnCancel__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnCancel__DelegateSignature");

	UWidget_ColorGun_ColorPicker_C_OnCancel__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnAccept__DelegateSignature
// ()

void UWidget_ColorGun_ColorPicker_C::OnAccept__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnAccept__DelegateSignature");

	UWidget_ColorGun_ColorPicker_C_OnAccept__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
