// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ImageTabButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ImageTabButton.Widget_ImageTabButton_C.UpdateButtonStyle
// ()

void UWidget_ImageTabButton_C::UpdateButtonStyle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.UpdateButtonStyle");

	UWidget_ImageTabButton_C_UpdateButtonStyle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.CheckIsSelected
// ()
// Parameters:
// bool                           isSelected                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ImageTabButton_C::CheckIsSelected(bool* isSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.CheckIsSelected");

	UWidget_ImageTabButton_C_CheckIsSelected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (isSelected != nullptr)
		*isSelected = params.isSelected;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.SetIcon
// ()

void UWidget_ImageTabButton_C::SetIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.SetIcon");

	UWidget_ImageTabButton_C_SetIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.GetButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_ImageTabButton_C::GetButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.GetButtonEnabled");

	UWidget_ImageTabButton_C_GetButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.Construct
// ()

void UWidget_ImageTabButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.Construct");

	UWidget_ImageTabButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_32_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ImageTabButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_32_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_32_OnButtonClickedEvent__DelegateSignature");

	UWidget_ImageTabButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_32_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_ImageTabButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_ImageTabButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ImageTabButton_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.PreConstruct");

	UWidget_ImageTabButton_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.Destruct
// ()

void UWidget_ImageTabButton_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.Destruct");

	UWidget_ImageTabButton_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.ExecuteUbergraph_Widget_ImageTabButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ImageTabButton_C::ExecuteUbergraph_Widget_ImageTabButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.ExecuteUbergraph_Widget_ImageTabButton");

	UWidget_ImageTabButton_C_ExecuteUbergraph_Widget_ImageTabButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ImageTabButton.Widget_ImageTabButton_C.TabButtonClicked__DelegateSignature
// ()

void UWidget_ImageTabButton_C::TabButtonClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ImageTabButton.Widget_ImageTabButton_C.TabButtonClicked__DelegateSignature");

	UWidget_ImageTabButton_C_TabButtonClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
