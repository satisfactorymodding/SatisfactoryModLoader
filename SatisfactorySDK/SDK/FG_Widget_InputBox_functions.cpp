// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InputBox_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InputBox.Widget_InputBox_C.CheckSearchbarLength
// ()
// Parameters:
// bool                           SearchbarContainsText          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::CheckSearchbarLength(bool* SearchbarContainsText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.CheckSearchbarLength");

	UWidget_InputBox_C_CheckSearchbarLength_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (SearchbarContainsText != nullptr)
		*SearchbarContainsText = params.SearchbarContainsText;
}


// Function Widget_InputBox.Widget_InputBox_C.SetSearchbarStyle
// ()

void UWidget_InputBox_C::SetSearchbarStyle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.SetSearchbarStyle");

	UWidget_InputBox_C_SetSearchbarStyle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.SetInputboxStyle
// ()
// Parameters:
// bool                           IsHovered                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::SetInputboxStyle(bool IsHovered)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.SetInputboxStyle");

	UWidget_InputBox_C_SetInputboxStyle_Params params;
	params.IsHovered = IsHovered;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.ShowHintText
// ()

void UWidget_InputBox_C::ShowHintText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.ShowHintText");

	UWidget_InputBox_C_ShowHintText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_InputBox_C::BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextChangedEvent__DelegateSignature");

	UWidget_InputBox_C_BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature");

	UWidget_InputBox_C_BndEvt__mInputBox_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.Construct
// ()

void UWidget_InputBox_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.Construct");

	UWidget_InputBox_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.Tick");

	UWidget_InputBox_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.BndEvt__mHover_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_InputBox_C::BndEvt__mHover_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.BndEvt__mHover_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_InputBox_C_BndEvt__mHover_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.BndEvt__mHover_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_InputBox_C::BndEvt__mHover_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.BndEvt__mHover_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_InputBox_C_BndEvt__mHover_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.PreConstruct");

	UWidget_InputBox_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.BndEvt__mSearchButton_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_InputBox_C::BndEvt__mSearchButton_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.BndEvt__mSearchButton_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature");

	UWidget_InputBox_C_BndEvt__mSearchButton_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.ExecuteUbergraph_Widget_InputBox
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::ExecuteUbergraph_Widget_InputBox(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.ExecuteUbergraph_Widget_InputBox");

	UWidget_InputBox_C_ExecuteUbergraph_Widget_InputBox_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.OnClearTextClicked__DelegateSignature
// ()

void UWidget_InputBox_C::OnClearTextClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.OnClearTextClicked__DelegateSignature");

	UWidget_InputBox_C_OnClearTextClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.OnTextComitted__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InputBox_C::OnTextComitted__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.OnTextComitted__DelegateSignature");

	UWidget_InputBox_C_OnTextComitted__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InputBox.Widget_InputBox_C.OnTextChanged__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_InputBox_C::OnTextChanged__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InputBox.Widget_InputBox_C.OnTextChanged__DelegateSignature");

	UWidget_InputBox_C_OnTextChanged__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
