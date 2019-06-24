// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Credits_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Credits.Widget_Credits_C.OnEscape
// ()

void UWidget_Credits_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credits.Widget_Credits_C.OnEscape");

	UWidget_Credits_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credits.Widget_Credits_C.Construct
// ()

void UWidget_Credits_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credits.Widget_Credits_C.Construct");

	UWidget_Credits_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credits.Widget_Credits_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Credits_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credits.Widget_Credits_C.OnMenuEnter");

	UWidget_Credits_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credits.Widget_Credits_C.ExecuteUbergraph_Widget_Credits
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Credits_C::ExecuteUbergraph_Widget_Credits(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credits.Widget_Credits_C.ExecuteUbergraph_Widget_Credits");

	UWidget_Credits_C_ExecuteUbergraph_Widget_Credits_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credits.Widget_Credits_C.OnBackClicked__DelegateSignature
// ()

void UWidget_Credits_C::OnBackClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credits.Widget_Credits_C.OnBackClicked__DelegateSignature");

	UWidget_Credits_C_OnBackClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
