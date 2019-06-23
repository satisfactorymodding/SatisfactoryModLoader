// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpeedSign_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SpeedSign.Widget_SpeedSign_C.ServerSetSpeedLimit
// ()
// Parameters:
// int                            NewSpeedLimit                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpeedSign_C::ServerSetSpeedLimit(int NewSpeedLimit)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.ServerSetSpeedLimit");

	UWidget_SpeedSign_C_ServerSetSpeedLimit_Params params;
	params.NewSpeedLimit = NewSpeedLimit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.SetInputMode
// ()

void UWidget_SpeedSign_C::SetInputMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.SetInputMode");

	UWidget_SpeedSign_C_SetInputMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.Init
// ()

void UWidget_SpeedSign_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.Init");

	UWidget_SpeedSign_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__m30_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_SpeedSign_C::BndEvt__m30_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__m30_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_SpeedSign_C_BndEvt__m30_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__m50_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_SpeedSign_C::BndEvt__m50_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__m50_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_SpeedSign_C_BndEvt__m50_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__m70_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
// ()

void UWidget_SpeedSign_C::BndEvt__m70_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__m70_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature");

	UWidget_SpeedSign_C_BndEvt__m70_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__mUnlimited_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
// ()

void UWidget_SpeedSign_C::BndEvt__mUnlimited_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.BndEvt__mUnlimited_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature");

	UWidget_SpeedSign_C_BndEvt__mUnlimited_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpeedSign.Widget_SpeedSign_C.ExecuteUbergraph_Widget_SpeedSign
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpeedSign_C::ExecuteUbergraph_Widget_SpeedSign(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpeedSign.Widget_SpeedSign_C.ExecuteUbergraph_Widget_SpeedSign");

	UWidget_SpeedSign_C_ExecuteUbergraph_Widget_SpeedSign_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
