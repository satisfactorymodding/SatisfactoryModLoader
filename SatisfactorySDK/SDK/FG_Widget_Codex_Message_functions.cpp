// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_Message_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Codex_Message.Widget_Codex_Message_C.ClearMessage
// ()

void UWidget_Codex_Message_C::ClearMessage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.ClearMessage");

	UWidget_Codex_Message_C_ClearMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.GenerateAudioMessage
// ()
// Parameters:
// class UClass*                  inClass                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   Text                           (Parm, OutParm)

void UWidget_Codex_Message_C::GenerateAudioMessage(class UClass* inClass, struct FText* Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.GenerateAudioMessage");

	UWidget_Codex_Message_C_GenerateAudioMessage_Params params;
	params.inClass = inClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Text != nullptr)
		*Text = params.Text;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.GetAttachedFilesVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Codex_Message_C::GetAttachedFilesVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.GetAttachedFilesVisibility");

	UWidget_Codex_Message_C_GetAttachedFilesVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.GetScrollButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Codex_Message_C::GetScrollButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.GetScrollButtonVisibility");

	UWidget_Codex_Message_C_GetScrollButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.SetupImage
// ()

void UWidget_Codex_Message_C::SetupImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.SetupImage");

	UWidget_Codex_Message_C_SetupImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.Construct
// ()

void UWidget_Codex_Message_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.Construct");

	UWidget_Codex_Message_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.AddContent
// ()
// Parameters:
// class UClass*                  contentClass                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Codex_Message_C::AddContent(class UClass* contentClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.AddContent");

	UWidget_Codex_Message_C_AddContent_Params params;
	params.contentClass = contentClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.BndEvt__mScrollButton_K2Node_ComponentBoundEvent_40_OnClicked__DelegateSignature
// ()

void UWidget_Codex_Message_C::BndEvt__mScrollButton_K2Node_ComponentBoundEvent_40_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.BndEvt__mScrollButton_K2Node_ComponentBoundEvent_40_OnClicked__DelegateSignature");

	UWidget_Codex_Message_C_BndEvt__mScrollButton_K2Node_ComponentBoundEvent_40_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Codex_Message_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_Codex_Message_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Message.Widget_Codex_Message_C.ExecuteUbergraph_Widget_Codex_Message
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Codex_Message_C::ExecuteUbergraph_Widget_Codex_Message(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Message.Widget_Codex_Message_C.ExecuteUbergraph_Widget_Codex_Message");

	UWidget_Codex_Message_C_ExecuteUbergraph_Widget_Codex_Message_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
