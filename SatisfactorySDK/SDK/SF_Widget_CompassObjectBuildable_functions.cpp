// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CompassObjectBuildable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.HideDescription
// ()

void UWidget_CompassObjectBuildable_C::HideDescription()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.HideDescription");

	UWidget_CompassObjectBuildable_C_HideDescription_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.GetAngleFromCompassCenter
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_CompassObjectBuildable_C::GetAngleFromCompassCenter()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.GetAngleFromCompassCenter");

	UWidget_CompassObjectBuildable_C_GetAngleFromCompassCenter_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Construct
// ()

void UWidget_CompassObjectBuildable_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Construct");

	UWidget_CompassObjectBuildable_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectBuildable_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Tick");

	UWidget_CompassObjectBuildable_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnCompassObjectUpdated
// ()

void UWidget_CompassObjectBuildable_C::OnCompassObjectUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnCompassObjectUpdated");

	UWidget_CompassObjectBuildable_C_OnCompassObjectUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.ExecuteUbergraph_Widget_CompassObjectBuildable
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectBuildable_C::ExecuteUbergraph_Widget_CompassObjectBuildable(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.ExecuteUbergraph_Widget_CompassObjectBuildable");

	UWidget_CompassObjectBuildable_C_ExecuteUbergraph_Widget_CompassObjectBuildable_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
