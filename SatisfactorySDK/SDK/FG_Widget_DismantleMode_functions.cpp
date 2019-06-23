// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_DismantleMode_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_DismantleMode.Widget_DismantleMode_C.GetReticleVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_DismantleMode_C::GetReticleVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.GetReticleVisibility");

	UWidget_DismantleMode_C_GetReticleVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.SetDismantleRefunds
// ()

void UWidget_DismantleMode_C::SetDismantleRefunds()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.SetDismantleRefunds");

	UWidget_DismantleMode_C_SetDismantleRefunds_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.OnEscapePressed
// ()

void UWidget_DismantleMode_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.OnEscapePressed");

	UWidget_DismantleMode_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.Init
// ()

void UWidget_DismantleMode_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.Init");

	UWidget_DismantleMode_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DismantleMode_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.Tick");

	UWidget_DismantleMode_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.Construct
// ()

void UWidget_DismantleMode_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.Construct");

	UWidget_DismantleMode_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.OnDismantleRefundChanged
// ()
// Parameters:
// class UFGBuildGunStateDismantle* dismantleGun                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DismantleMode_C::OnDismantleRefundChanged(class UFGBuildGunStateDismantle* dismantleGun)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.OnDismantleRefundChanged");

	UWidget_DismantleMode_C_OnDismantleRefundChanged_Params params;
	params.dismantleGun = dismantleGun;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DismantleMode.Widget_DismantleMode_C.ExecuteUbergraph_Widget_DismantleMode
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DismantleMode_C::ExecuteUbergraph_Widget_DismantleMode(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DismantleMode.Widget_DismantleMode_C.ExecuteUbergraph_Widget_DismantleMode");

	UWidget_DismantleMode_C_ExecuteUbergraph_Widget_DismantleMode_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
