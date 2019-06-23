// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_CategoryButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.UpdateButtonStyle
// ()

void UWidget_BuildMenu_CategoryButton_C::UpdateButtonStyle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.UpdateButtonStyle");

	UWidget_BuildMenu_CategoryButton_C_UpdateButtonStyle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.CheckIsSelected
// ()
// Parameters:
// bool                           mIsSelected                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_CategoryButton_C::CheckIsSelected(bool* mIsSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.CheckIsSelected");

	UWidget_BuildMenu_CategoryButton_C_CheckIsSelected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (mIsSelected != nullptr)
		*mIsSelected = params.mIsSelected;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.GetBuildCategoryIcon
// ()

void UWidget_BuildMenu_CategoryButton_C::GetBuildCategoryIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.GetBuildCategoryIcon");

	UWidget_BuildMenu_CategoryButton_C_GetBuildCategoryIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.GetBuildCategoryName
// ()

void UWidget_BuildMenu_CategoryButton_C::GetBuildCategoryName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.GetBuildCategoryName");

	UWidget_BuildMenu_CategoryButton_C_GetBuildCategoryName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_BuildMenu_CategoryButton_C::BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature");

	UWidget_BuildMenu_CategoryButton_C_BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_BuildMenu_CategoryButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_BuildMenu_CategoryButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_BuildMenu_CategoryButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_BuildMenu_CategoryButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.Construct
// ()

void UWidget_BuildMenu_CategoryButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.Construct");

	UWidget_BuildMenu_CategoryButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.Destruct
// ()

void UWidget_BuildMenu_CategoryButton_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.Destruct");

	UWidget_BuildMenu_CategoryButton_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.ExecuteUbergraph_Widget_BuildMenu_CategoryButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_CategoryButton_C::ExecuteUbergraph_Widget_BuildMenu_CategoryButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_CategoryButton.Widget_BuildMenu_CategoryButton_C.ExecuteUbergraph_Widget_BuildMenu_CategoryButton");

	UWidget_BuildMenu_CategoryButton_C_ExecuteUbergraph_Widget_BuildMenu_CategoryButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
