// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TabButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TabButton.Widget_TabButton_C.GetButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_TabButton_C::GetButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TabButton.Widget_TabButton_C.GetButtonEnabled");

	UWidget_TabButton_C_GetButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TabButton.Widget_TabButton_C.Construct
// ()

void UWidget_TabButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TabButton.Widget_TabButton_C.Construct");

	UWidget_TabButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TabButton.Widget_TabButton_C.OnThisButtonClicked
// ()

void UWidget_TabButton_C::OnThisButtonClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TabButton.Widget_TabButton_C.OnThisButtonClicked");

	UWidget_TabButton_C_OnThisButtonClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TabButton.Widget_TabButton_C.ExecuteUbergraph_Widget_TabButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TabButton_C::ExecuteUbergraph_Widget_TabButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TabButton.Widget_TabButton_C.ExecuteUbergraph_Widget_TabButton");

	UWidget_TabButton_C_ExecuteUbergraph_Widget_TabButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
