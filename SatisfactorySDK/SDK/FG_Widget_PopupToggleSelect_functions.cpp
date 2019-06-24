// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupToggleSelect_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.SetOptionalTextElements
// ()
// Parameters:
// struct FText*                  Title                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText*                  Desc                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_PopupToggleSelect_C::SetOptionalTextElements(struct FText* Title, struct FText* Desc)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.SetOptionalTextElements");

	UWidget_PopupToggleSelect_C_SetOptionalTextElements_Params params;
	params.Title = Title;
	params.Desc = Desc;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.GetShouldOkayBeEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_PopupToggleSelect_C::GetShouldOkayBeEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.GetShouldOkayBeEnabled");

	UWidget_PopupToggleSelect_C_GetShouldOkayBeEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.SetInstigatorAndInitialize
// ()
// Parameters:
// class UObject**                Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupToggleSelect_C::SetInstigatorAndInitialize(class UObject** Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.SetInstigatorAndInitialize");

	UWidget_PopupToggleSelect_C_SetInstigatorAndInitialize_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.OnChildSelected
// ()
// Parameters:
// int                            ChildIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupToggleSelect_C::OnChildSelected(int ChildIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.OnChildSelected");

	UWidget_PopupToggleSelect_C_OnChildSelected_Params params;
	params.ChildIndex = ChildIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.NotifyPopupConfirmed
// ()

void UWidget_PopupToggleSelect_C::NotifyPopupConfirmed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.NotifyPopupConfirmed");

	UWidget_PopupToggleSelect_C_NotifyPopupConfirmed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.NotifyPopupCanceled
// ()

void UWidget_PopupToggleSelect_C::NotifyPopupCanceled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.NotifyPopupCanceled");

	UWidget_PopupToggleSelect_C_NotifyPopupCanceled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.ExecuteUbergraph_Widget_PopupToggleSelect
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupToggleSelect_C::ExecuteUbergraph_Widget_PopupToggleSelect(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.ExecuteUbergraph_Widget_PopupToggleSelect");

	UWidget_PopupToggleSelect_C_ExecuteUbergraph_Widget_PopupToggleSelect_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
