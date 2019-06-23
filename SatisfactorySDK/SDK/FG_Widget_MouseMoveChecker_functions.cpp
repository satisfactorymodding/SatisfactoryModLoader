// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MouseMoveChecker_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.CheckIfMouseMove
// ()

void UWidget_MouseMoveChecker_C::CheckIfMouseMove()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.CheckIfMouseMove");

	UWidget_MouseMoveChecker_C_CheckIfMouseMove_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.StopCheckMouse
// ()

void UWidget_MouseMoveChecker_C::StopCheckMouse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.StopCheckMouse");

	UWidget_MouseMoveChecker_C_StopCheckMouse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.StartCheckMouse
// ()

void UWidget_MouseMoveChecker_C::StartCheckMouse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.StartCheckMouse");

	UWidget_MouseMoveChecker_C_StartCheckMouse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.ExecuteUbergraph_Widget_MouseMoveChecker
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MouseMoveChecker_C::ExecuteUbergraph_Widget_MouseMoveChecker(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.ExecuteUbergraph_Widget_MouseMoveChecker");

	UWidget_MouseMoveChecker_C_ExecuteUbergraph_Widget_MouseMoveChecker_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.OnMouseMoved__DelegateSignature
// ()

void UWidget_MouseMoveChecker_C::OnMouseMoved__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MouseMoveChecker.Widget_MouseMoveChecker_C.OnMouseMoved__DelegateSignature");

	UWidget_MouseMoveChecker_C_OnMouseMoved__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
