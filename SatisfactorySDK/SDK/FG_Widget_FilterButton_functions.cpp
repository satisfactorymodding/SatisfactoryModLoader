// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_FilterButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_FilterButton.Widget_FilterButton_C.SetTitle
// ()
// Parameters:
// struct FText                   mName                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_FilterButton_C::SetTitle(const struct FText& mName)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.SetTitle");

	UWidget_FilterButton_C_SetTitle_Params params;
	params.mName = mName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FilterButton_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.PreConstruct");

	UWidget_FilterButton_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__mShowOnCompassCheckbox_K2Node_ComponentBoundEvent_0_OnCheckChanged__DelegateSignature
// ()
// Parameters:
// bool                           IsChecked                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FilterButton_C::BndEvt__mShowOnCompassCheckbox_K2Node_ComponentBoundEvent_0_OnCheckChanged__DelegateSignature(bool IsChecked)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__mShowOnCompassCheckbox_K2Node_ComponentBoundEvent_0_OnCheckChanged__DelegateSignature");

	UWidget_FilterButton_C_BndEvt__mShowOnCompassCheckbox_K2Node_ComponentBoundEvent_0_OnCheckChanged__DelegateSignature_Params params;
	params.IsChecked = IsChecked;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__mShowOnMapCheckbox_K2Node_ComponentBoundEvent_1_OnCheckChanged__DelegateSignature
// ()
// Parameters:
// bool                           IsChecked                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FilterButton_C::BndEvt__mShowOnMapCheckbox_K2Node_ComponentBoundEvent_1_OnCheckChanged__DelegateSignature(bool IsChecked)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__mShowOnMapCheckbox_K2Node_ComponentBoundEvent_1_OnCheckChanged__DelegateSignature");

	UWidget_FilterButton_C_BndEvt__mShowOnMapCheckbox_K2Node_ComponentBoundEvent_1_OnCheckChanged__DelegateSignature_Params params;
	params.IsChecked = IsChecked;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_2_OnHovered__DelegateSignature
// ()

void UWidget_FilterButton_C::BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_2_OnHovered__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_2_OnHovered__DelegateSignature");

	UWidget_FilterButton_C_BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_2_OnHovered__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_3_OnUnhovered__DelegateSignature
// ()

void UWidget_FilterButton_C::BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_3_OnUnhovered__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_3_OnUnhovered__DelegateSignature");

	UWidget_FilterButton_C_BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_3_OnUnhovered__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.Construct
// ()

void UWidget_FilterButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.Construct");

	UWidget_FilterButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.ExecuteUbergraph_Widget_FilterButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FilterButton_C::ExecuteUbergraph_Widget_FilterButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.ExecuteUbergraph_Widget_FilterButton");

	UWidget_FilterButton_C_ExecuteUbergraph_Widget_FilterButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.mShowOnCompassChanged__DelegateSignature
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ShowOnCompass                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FilterButton_C::mShowOnCompassChanged__DelegateSignature(class UWidget_FilterButton_C* Instigator, bool ShowOnCompass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.mShowOnCompassChanged__DelegateSignature");

	UWidget_FilterButton_C_mShowOnCompassChanged__DelegateSignature_Params params;
	params.Instigator = Instigator;
	params.ShowOnCompass = ShowOnCompass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.mShowOnMapChanged__DelegateSignature
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ShowOnMap                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FilterButton_C::mShowOnMapChanged__DelegateSignature(class UWidget_FilterButton_C* Instigator, bool ShowOnMap)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.mShowOnMapChanged__DelegateSignature");

	UWidget_FilterButton_C_mShowOnMapChanged__DelegateSignature_Params params;
	params.Instigator = Instigator;
	params.ShowOnMap = ShowOnMap;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.OnUnhovered__DelegateSignature
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_FilterButton_C::OnUnhovered__DelegateSignature(class UWidget_FilterButton_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.OnUnhovered__DelegateSignature");

	UWidget_FilterButton_C_OnUnhovered__DelegateSignature_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FilterButton.Widget_FilterButton_C.OnHovered__DelegateSignature
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_FilterButton_C::OnHovered__DelegateSignature(class UWidget_FilterButton_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FilterButton.Widget_FilterButton_C.OnHovered__DelegateSignature");

	UWidget_FilterButton_C_OnHovered__DelegateSignature_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
