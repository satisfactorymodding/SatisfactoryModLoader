// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ListButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ListButton.Widget_ListButton_C.GetIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ListButton_C::GetIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.GetIconColor");

	UWidget_ListButton_C_GetIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ListButton.Widget_ListButton_C.ClearListSelection
// ()

void UWidget_ListButton_C::ClearListSelection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.ClearListSelection");

	UWidget_ListButton_C_ClearListSelection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.GetIndexInList
// ()
// Parameters:
// int                            Index                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ListButton_C::GetIndexInList(int* Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.GetIndexInList");

	UWidget_ListButton_C_GetIndexInList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Index != nullptr)
		*Index = params.Index;
}


// Function Widget_ListButton.Widget_ListButton_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_ListButton_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.GetTextColor");

	UWidget_ListButton_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ListButton.Widget_ListButton_C.GetButtonBackground
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ListButton_C::GetButtonBackground()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.GetButtonBackground");

	UWidget_ListButton_C_GetButtonBackground_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ListButton.Widget_ListButton_C.UpdateButton
// ()
// Parameters:
// class UTexture*                Icon                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   Description                    (BlueprintVisible, BlueprintReadOnly, Parm)
// ESlateVisibility               descVisibility                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// ESlateVisibility               iconVisibility                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   AdditionalInfo                 (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_ListButton_C::UpdateButton(class UTexture* Icon, const struct FText& Title, const struct FText& Description, ESlateVisibility descVisibility, ESlateVisibility iconVisibility, const struct FText& AdditionalInfo)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.UpdateButton");

	UWidget_ListButton_C_UpdateButton_Params params;
	params.Icon = Icon;
	params.Title = Title;
	params.Description = Description;
	params.descVisibility = descVisibility;
	params.iconVisibility = iconVisibility;
	params.AdditionalInfo = AdditionalInfo;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ListButton_C::BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_ListButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.mSetDisabled
// ()

void UWidget_ListButton_C::mSetDisabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.mSetDisabled");

	UWidget_ListButton_C_mSetDisabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.mSetEnabled
// ()

void UWidget_ListButton_C::mSetEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.mSetEnabled");

	UWidget_ListButton_C_mSetEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_ListButton_C::BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_ListButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ListButton_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.PreConstruct");

	UWidget_ListButton_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_ListButton_C::BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_ListButton_C_BndEvt__mRecipeButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.Construct
// ()

void UWidget_ListButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.Construct");

	UWidget_ListButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.SendClick
// ()

void UWidget_ListButton_C::SendClick()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.SendClick");

	UWidget_ListButton_C_SendClick_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.ExecuteUbergraph_Widget_ListButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ListButton_C::ExecuteUbergraph_Widget_ListButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.ExecuteUbergraph_Widget_ListButton");

	UWidget_ListButton_C_ExecuteUbergraph_Widget_ListButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.OnUnhovered__DelegateSignature
// ()

void UWidget_ListButton_C::OnUnhovered__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.OnUnhovered__DelegateSignature");

	UWidget_ListButton_C_OnUnhovered__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.OnHovered__DelegateSignature
// ()

void UWidget_ListButton_C::OnHovered__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.OnHovered__DelegateSignature");

	UWidget_ListButton_C_OnHovered__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ListButton.Widget_ListButton_C.OnClicked__DelegateSignature
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_ListButton_C*    ListButton                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ListButton_C::OnClicked__DelegateSignature(int Index, class UWidget_ListButton_C* ListButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ListButton.Widget_ListButton_C.OnClicked__DelegateSignature");

	UWidget_ListButton_C_OnClicked__DelegateSignature_Params params;
	params.Index = Index;
	params.ListButton = ListButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
