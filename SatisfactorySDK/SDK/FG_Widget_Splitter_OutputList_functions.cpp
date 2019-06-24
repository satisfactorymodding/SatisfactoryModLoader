// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Splitter_OutputList_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.ShowHideAddButton
// ()
// Parameters:
// bool                           ShouldShowAddButton            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Splitter_OutputList_C::ShowHideAddButton(bool ShouldShowAddButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.ShowHideAddButton");

	UWidget_Splitter_OutputList_C_ShowHideAddButton_Params params;
	params.ShouldShowAddButton = ShouldShowAddButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.GetDescriptorsForSearch
// ()

void UWidget_Splitter_OutputList_C::GetDescriptorsForSearch()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.GetDescriptorsForSearch");

	UWidget_Splitter_OutputList_C_GetDescriptorsForSearch_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Splitter_OutputList_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.PreConstruct");

	UWidget_Splitter_OutputList_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.BndEvt__mAdd_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Splitter_OutputList_C::BndEvt__mAdd_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.BndEvt__mAdd_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature");

	UWidget_Splitter_OutputList_C_BndEvt__mAdd_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.Construct
// ()

void UWidget_Splitter_OutputList_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.Construct");

	UWidget_Splitter_OutputList_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.ExecuteUbergraph_Widget_Splitter_OutputList
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Splitter_OutputList_C::ExecuteUbergraph_Widget_Splitter_OutputList(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.ExecuteUbergraph_Widget_Splitter_OutputList");

	UWidget_Splitter_OutputList_C_ExecuteUbergraph_Widget_Splitter_OutputList_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.OnAddClicked__DelegateSignature
// ()

void UWidget_Splitter_OutputList_C::OnAddClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Splitter_OutputList.Widget_Splitter_OutputList_C.OnAddClicked__DelegateSignature");

	UWidget_Splitter_OutputList_C_OnAddClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
