// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_Slot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.UpdateColors
// ()
// Parameters:
// struct FLinearColor            PrimaryColor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            SecondaryColor                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::UpdateColors(const struct FLinearColor& PrimaryColor, const struct FLinearColor& SecondaryColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.UpdateColors");

	UWidget_ColorPicker_Slot_C_UpdateColors_Params params;
	params.PrimaryColor = PrimaryColor;
	params.SecondaryColor = SecondaryColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.SetIsSelected
// ()
// Parameters:
// bool                           isSelected                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::SetIsSelected(bool isSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.SetIsSelected");

	UWidget_ColorPicker_Slot_C_SetIsSelected_Params params;
	params.isSelected = isSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.PreConstruct");

	UWidget_ColorPicker_Slot_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ColorPicker_Slot_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_ColorPicker_Slot_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_ColorPicker_Slot_C::BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_ColorPicker_Slot_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_ColorPicker_Slot_C::BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature");

	UWidget_ColorPicker_Slot_C_BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mEditButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ColorPicker_Slot_C::BndEvt__mEditButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mEditButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature");

	UWidget_ColorPicker_Slot_C_BndEvt__mEditButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.ExecuteUbergraph_Widget_ColorPicker_Slot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::ExecuteUbergraph_Widget_ColorPicker_Slot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.ExecuteUbergraph_Widget_ColorPicker_Slot");

	UWidget_ColorPicker_Slot_C_ExecuteUbergraph_Widget_ColorPicker_Slot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnEditClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::OnEditClicked__DelegateSignature(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnEditClicked__DelegateSignature");

	UWidget_ColorPicker_Slot_C_OnEditClicked__DelegateSignature_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnUnhovered__DelegateSignature
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::OnUnhovered__DelegateSignature(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnUnhovered__DelegateSignature");

	UWidget_ColorPicker_Slot_C_OnUnhovered__DelegateSignature_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnHovered__DelegateSignature
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::OnHovered__DelegateSignature(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnHovered__DelegateSignature");

	UWidget_ColorPicker_Slot_C_OnHovered__DelegateSignature_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_ColorPicker_Slot_C* Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ColorPicker_Slot_C::OnClicked__DelegateSignature(class UWidget_ColorPicker_Slot_C* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnClicked__DelegateSignature");

	UWidget_ColorPicker_Slot_C_OnClicked__DelegateSignature_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
