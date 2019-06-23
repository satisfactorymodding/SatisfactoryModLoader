// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CompassObjectBuildable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

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


// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnObjectCentered
// ()
// Parameters:
// bool*                          centered                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectBuildable_C::OnObjectCentered(bool* centered)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnObjectCentered");

	UWidget_CompassObjectBuildable_C_OnObjectCentered_Params params;
	params.centered = centered;

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
