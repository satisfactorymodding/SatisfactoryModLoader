// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayMenu_Alpha_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.SetStartButtonEnable
// ()
// Parameters:
// bool                           Enabled                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayMenu_Alpha_C::SetStartButtonEnable(bool Enabled)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.SetStartButtonEnable");

	UWidget_PlayMenu_Alpha_C_SetStartButtonEnable_Params params;
	params.Enabled = Enabled;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.CheckSessionNameForError
// ()

void UWidget_PlayMenu_Alpha_C::CheckSessionNameForError()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.CheckSessionNameForError");

	UWidget_PlayMenu_Alpha_C_CheckSessionNameForError_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.SetPlayButtonError
// ()
// Parameters:
// bool                           Error                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   errorMessage                   (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_PlayMenu_Alpha_C::SetPlayButtonError(bool Error, const struct FText& errorMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.SetPlayButtonError");

	UWidget_PlayMenu_Alpha_C_SetPlayButtonError_Params params;
	params.Error = Error;
	params.errorMessage = errorMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.Init
// ()

void UWidget_PlayMenu_Alpha_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.Init");

	UWidget_PlayMenu_Alpha_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnEscape
// ()

void UWidget_PlayMenu_Alpha_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnEscape");

	UWidget_PlayMenu_Alpha_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.Construct
// ()

void UWidget_PlayMenu_Alpha_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.Construct");

	UWidget_PlayMenu_Alpha_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_2_onSelectionChanged__DelegateSignature
// ()
// Parameters:
// class FString                  SelectedOption                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UWidget_PlayMenu_Alpha_C::BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_2_onSelectionChanged__DelegateSignature(const class FString& SelectedOption)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_2_onSelectionChanged__DelegateSignature");

	UWidget_PlayMenu_Alpha_C_BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_2_onSelectionChanged__DelegateSignature_Params params;
	params.SelectedOption = SelectedOption;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnStartLocClicked
// ()
// Parameters:
// TEnumAsByte<EStartingLocations> mStartingLocs                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayMenu_Alpha_C::OnStartLocClicked(TEnumAsByte<EStartingLocations> mStartingLocs)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnStartLocClicked");

	UWidget_PlayMenu_Alpha_C_OnStartLocClicked_Params params;
	params.mStartingLocs = mStartingLocs;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayMenu_Alpha_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.PreConstruct");

	UWidget_PlayMenu_Alpha_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PlayMenu_Alpha_C::BndEvt__mStartGame_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature");

	UWidget_PlayMenu_Alpha_C_BndEvt__mStartGame_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PlayMenu_Alpha_C::BndEvt__mStartGame_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature");

	UWidget_PlayMenu_Alpha_C_BndEvt__mStartGame_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__EditableTextBox_0_K2Node_ComponentBoundEvent_6_OnEditableTextBoxChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_PlayMenu_Alpha_C::BndEvt__EditableTextBox_0_K2Node_ComponentBoundEvent_6_OnEditableTextBoxChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__EditableTextBox_0_K2Node_ComponentBoundEvent_6_OnEditableTextBoxChangedEvent__DelegateSignature");

	UWidget_PlayMenu_Alpha_C_BndEvt__EditableTextBox_0_K2Node_ComponentBoundEvent_6_OnEditableTextBoxChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_PlayMenu_Alpha_C::BndEvt__mStartGame_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature");

	UWidget_PlayMenu_Alpha_C_BndEvt__mStartGame_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_PlayMenu_Alpha_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnMenuEnter");

	UWidget_PlayMenu_Alpha_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.ExecuteUbergraph_Widget_PlayMenu_Alpha
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayMenu_Alpha_C::ExecuteUbergraph_Widget_PlayMenu_Alpha(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.ExecuteUbergraph_Widget_PlayMenu_Alpha");

	UWidget_PlayMenu_Alpha_C_ExecuteUbergraph_Widget_PlayMenu_Alpha_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
