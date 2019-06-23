// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PowerPole_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PowerPole.Widget_PowerPole_C.UpdateHeaderText
// ()

void UWidget_PowerPole_C::UpdateHeaderText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.UpdateHeaderText");

	UWidget_PowerPole_C_UpdateHeaderText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerPole.Widget_PowerPole_C.GetFuseVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PowerPole_C::GetFuseVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.GetFuseVisibility");

	UWidget_PowerPole_C_GetFuseVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerPole.Widget_PowerPole_C.OnGetPowerCircuit
// ()
// Parameters:
// class UFGPowerCircuit*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UFGPowerCircuit* UWidget_PowerPole_C::OnGetPowerCircuit()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.OnGetPowerCircuit");

	UWidget_PowerPole_C_OnGetPowerCircuit_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerPole.Widget_PowerPole_C.IsConnected
// ()
// Parameters:
// bool                           IsConnected                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_PowerPole_C::IsConnected(bool* IsConnected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.IsConnected");

	UWidget_PowerPole_C_IsConnected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsConnected != nullptr)
		*IsConnected = params.IsConnected;
}


// Function Widget_PowerPole.Widget_PowerPole_C.Cleanup
// ()

void UWidget_PowerPole_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.Cleanup");

	UWidget_PowerPole_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerPole.Widget_PowerPole_C.GetPowerCircuitGraphVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PowerPole_C::GetPowerCircuitGraphVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.GetPowerCircuitGraphVisibility");

	UWidget_PowerPole_C_GetPowerCircuitGraphVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerPole.Widget_PowerPole_C.Init
// ()

void UWidget_PowerPole_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.Init");

	UWidget_PowerPole_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerPole.Widget_PowerPole_C.Construct
// ()

void UWidget_PowerPole_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.Construct");

	UWidget_PowerPole_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerPole.Widget_PowerPole_C.Destruct
// ()

void UWidget_PowerPole_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.Destruct");

	UWidget_PowerPole_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerPole.Widget_PowerPole_C.ResetFuse
// ()

void UWidget_PowerPole_C::ResetFuse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.ResetFuse");

	UWidget_PowerPole_C_ResetFuse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerPole.Widget_PowerPole_C.ExecuteUbergraph_Widget_PowerPole
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PowerPole_C::ExecuteUbergraph_Widget_PowerPole(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerPole.Widget_PowerPole_C.ExecuteUbergraph_Widget_PowerPole");

	UWidget_PowerPole_C_ExecuteUbergraph_Widget_PowerPole_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
