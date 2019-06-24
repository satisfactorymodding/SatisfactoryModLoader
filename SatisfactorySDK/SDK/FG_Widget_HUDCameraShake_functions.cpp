// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDCameraShake_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Get Cam and View Position Difference
// ()
// Parameters:
// float                          Scale                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDCameraShake_C::Get_Cam_and_View_Position_Difference(float* Scale)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Get Cam and View Position Difference");

	UWidget_HUDCameraShake_C_Get_Cam_and_View_Position_Difference_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Scale != nullptr)
		*Scale = params.Scale;
}


// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Get Cam and View Rotation Difference
// ()
// Parameters:
// float                          X                              (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// float                          Y                              (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDCameraShake_C::Get_Cam_and_View_Rotation_Difference(float* X, float* Y)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Get Cam and View Rotation Difference");

	UWidget_HUDCameraShake_C_Get_Cam_and_View_Rotation_Difference_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (X != nullptr)
		*X = params.X;
	if (Y != nullptr)
		*Y = params.Y;
}


// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.HUD Lerp
// ()

void UWidget_HUDCameraShake_C::HUD_Lerp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.HUD Lerp");

	UWidget_HUDCameraShake_C_HUD_Lerp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDCameraShake_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Tick");

	UWidget_HUDCameraShake_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.ExecuteUbergraph_Widget_HUDCameraShake
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDCameraShake_C::ExecuteUbergraph_Widget_HUDCameraShake(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.ExecuteUbergraph_Widget_HUDCameraShake");

	UWidget_HUDCameraShake_C_ExecuteUbergraph_Widget_HUDCameraShake_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
