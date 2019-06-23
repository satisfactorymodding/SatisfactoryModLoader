// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ErrorMessage_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ErrorMessage.Widget_ErrorMessage_C.SetBody
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_ErrorMessage_C::SetBody(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ErrorMessage.Widget_ErrorMessage_C.SetBody");

	UWidget_ErrorMessage_C_SetBody_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ErrorMessage.Widget_ErrorMessage_C.SetButtonText
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_ErrorMessage_C::SetButtonText(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ErrorMessage.Widget_ErrorMessage_C.SetButtonText");

	UWidget_ErrorMessage_C_SetButtonText_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ErrorMessage.Widget_ErrorMessage_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_ErrorMessage_C::BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ErrorMessage.Widget_ErrorMessage_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_ErrorMessage_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ErrorMessage.Widget_ErrorMessage_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ErrorMessage_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ErrorMessage.Widget_ErrorMessage_C.PreConstruct");

	UWidget_ErrorMessage_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ErrorMessage.Widget_ErrorMessage_C.ExecuteUbergraph_Widget_ErrorMessage
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ErrorMessage_C::ExecuteUbergraph_Widget_ErrorMessage(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ErrorMessage.Widget_ErrorMessage_C.ExecuteUbergraph_Widget_ErrorMessage");

	UWidget_ErrorMessage_C_ExecuteUbergraph_Widget_ErrorMessage_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ErrorMessage.Widget_ErrorMessage_C.mOnClicked__DelegateSignature
// ()

void UWidget_ErrorMessage_C::mOnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ErrorMessage.Widget_ErrorMessage_C.mOnClicked__DelegateSignature");

	UWidget_ErrorMessage_C_mOnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
