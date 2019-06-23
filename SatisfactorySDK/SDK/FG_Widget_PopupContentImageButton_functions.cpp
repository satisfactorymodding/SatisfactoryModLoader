// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupContentImageButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.CacheDataFromReward
// ()

void UWidget_PopupContentImageButton_C::CacheDataFromReward()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.CacheDataFromReward");

	UWidget_PopupContentImageButton_C_CacheDataFromReward_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetIsSmeltable
// ()
// Parameters:
// class UClass*                  inClass                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsSmeltable                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupContentImageButton_C::GetIsSmeltable(class UClass* inClass, bool* IsSmeltable)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetIsSmeltable");

	UWidget_PopupContentImageButton_C_GetIsSmeltable_Params params;
	params.inClass = inClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsSmeltable != nullptr)
		*IsSmeltable = params.IsSmeltable;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.ClearSelectionList
// ()

void UWidget_PopupContentImageButton_C::ClearSelectionList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.ClearSelectionList");

	UWidget_PopupContentImageButton_C_ClearSelectionList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetIndexInList
// ()
// Parameters:
// int                            Index                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupContentImageButton_C::GetIndexInList(int* Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetIndexInList");

	UWidget_PopupContentImageButton_C_GetIndexInList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Index != nullptr)
		*Index = params.Index;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_PopupContentImageButton_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetTextColor");

	UWidget_PopupContentImageButton_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetBackgroundColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_PopupContentImageButton_C::GetBackgroundColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.GetBackgroundColor");

	UWidget_PopupContentImageButton_C_GetBackgroundColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupContentImageButton_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.PreConstruct");

	UWidget_PopupContentImageButton_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.Construct
// ()

void UWidget_PopupContentImageButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.Construct");

	UWidget_PopupContentImageButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.UpdateButton
// ()
// Parameters:
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FSlateBrush             ImageBrush                     (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_PopupContentImageButton_C::UpdateButton(const struct FText& Title, const struct FSlateBrush& ImageBrush)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.UpdateButton");

	UWidget_PopupContentImageButton_C_UpdateButton_Params params;
	params.Title = Title;
	params.ImageBrush = ImageBrush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_PopupContentImageButton_C::BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_PopupContentImageButton_C_BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PopupContentImageButton_C::BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_PopupContentImageButton_C_BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PopupContentImageButton_C::BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_PopupContentImageButton_C_BndEvt__mPopupContentButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.ExecuteUbergraph_Widget_PopupContentImageButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupContentImageButton_C::ExecuteUbergraph_Widget_PopupContentImageButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.ExecuteUbergraph_Widget_PopupContentImageButton");

	UWidget_PopupContentImageButton_C_ExecuteUbergraph_Widget_PopupContentImageButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.NotifyPopupContentIndexSelect__DelegateSignature
// ()
// Parameters:
// int                            ChildIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupContentImageButton_C::NotifyPopupContentIndexSelect__DelegateSignature(int ChildIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentImageButton.Widget_PopupContentImageButton_C.NotifyPopupContentIndexSelect__DelegateSignature");

	UWidget_PopupContentImageButton_C_NotifyPopupContentIndexSelect__DelegateSignature_Params params;
	params.ChildIndex = ChildIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
