// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CompassObjectCardinalDirection_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C.GetVisibility_1
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_CompassObjectCardinalDirection_C::GetVisibility_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C.GetVisibility_1");

	UWidget_CompassObjectCardinalDirection_C_GetVisibility_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C.OnCompassObjectAddedToPanel
// ()
// Parameters:
// class UCanvasPanelSlot**       parentSlot                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_CompassObjectCardinalDirection_C::OnCompassObjectAddedToPanel(class UCanvasPanelSlot** parentSlot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C.OnCompassObjectAddedToPanel");

	UWidget_CompassObjectCardinalDirection_C_OnCompassObjectAddedToPanel_Params params;
	params.parentSlot = parentSlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C.ExecuteUbergraph_Widget_CompassObjectCardinalDirection
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectCardinalDirection_C::ExecuteUbergraph_Widget_CompassObjectCardinalDirection(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C.ExecuteUbergraph_Widget_CompassObjectCardinalDirection");

	UWidget_CompassObjectCardinalDirection_C_ExecuteUbergraph_Widget_CompassObjectCardinalDirection_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
