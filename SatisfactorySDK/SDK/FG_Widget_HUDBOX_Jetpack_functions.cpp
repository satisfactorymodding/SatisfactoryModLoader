// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBOX_Jetpack_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.StopPulse
// ()

void UWidget_HUDBox_Jetpack_C::StopPulse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.StopPulse");

	UWidget_HUDBox_Jetpack_C_StopPulse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.StartPulse
// ()

void UWidget_HUDBox_Jetpack_C::StartPulse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.StartPulse");

	UWidget_HUDBox_Jetpack_C_StartPulse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.Construct
// ()

void UWidget_HUDBox_Jetpack_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.Construct");

	UWidget_HUDBox_Jetpack_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Jetpack_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.Tick");

	UWidget_HUDBox_Jetpack_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.BarPulse
// ()

void UWidget_HUDBox_Jetpack_C::BarPulse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.BarPulse");

	UWidget_HUDBox_Jetpack_C_BarPulse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.ExecuteUbergraph_Widget_HUDBox_Jetpack
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Jetpack_C::ExecuteUbergraph_Widget_HUDBox_Jetpack(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.ExecuteUbergraph_Widget_HUDBox_Jetpack");

	UWidget_HUDBox_Jetpack_C_ExecuteUbergraph_Widget_HUDBox_Jetpack_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
