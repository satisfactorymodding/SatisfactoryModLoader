// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupContentResolutionTimer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.GetShouldOkayBeEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_PopupContentResolutionTimer_C::GetShouldOkayBeEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.GetShouldOkayBeEnabled");

	UWidget_PopupContentResolutionTimer_C_GetShouldOkayBeEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Get_TimerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PopupContentResolutionTimer_C::Get_TimerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Get_TimerText");

	UWidget_PopupContentResolutionTimer_C_Get_TimerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Construct
// ()

void UWidget_PopupContentResolutionTimer_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Construct");

	UWidget_PopupContentResolutionTimer_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.TriggerCancel
// ()

void UWidget_PopupContentResolutionTimer_C::TriggerCancel()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.TriggerCancel");

	UWidget_PopupContentResolutionTimer_C_TriggerCancel_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.SetOptionalTextElements
// ()
// Parameters:
// struct FText*                  Title                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText*                  Desc                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_PopupContentResolutionTimer_C::SetOptionalTextElements(struct FText* Title, struct FText* Desc)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.SetOptionalTextElements");

	UWidget_PopupContentResolutionTimer_C_SetOptionalTextElements_Params params;
	params.Title = Title;
	params.Desc = Desc;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Destruct
// ()

void UWidget_PopupContentResolutionTimer_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Destruct");

	UWidget_PopupContentResolutionTimer_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.ExecuteUbergraph_Widget_PopupContentResolutionTimer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupContentResolutionTimer_C::ExecuteUbergraph_Widget_PopupContentResolutionTimer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.ExecuteUbergraph_Widget_PopupContentResolutionTimer");

	UWidget_PopupContentResolutionTimer_C_ExecuteUbergraph_Widget_PopupContentResolutionTimer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
