// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PulsingNamedSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PulsingNamedSlot.Widget_PulsingNamedSlot_C.mPlayPulseAnim
// ()

void UWidget_PulsingNamedSlot_C::mPlayPulseAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PulsingNamedSlot.Widget_PulsingNamedSlot_C.mPlayPulseAnim");

	UWidget_PulsingNamedSlot_C_mPlayPulseAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PulsingNamedSlot.Widget_PulsingNamedSlot_C.mStopPulseAnim
// ()

void UWidget_PulsingNamedSlot_C::mStopPulseAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PulsingNamedSlot.Widget_PulsingNamedSlot_C.mStopPulseAnim");

	UWidget_PulsingNamedSlot_C_mStopPulseAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PulsingNamedSlot.Widget_PulsingNamedSlot_C.ExecuteUbergraph_Widget_PulsingNamedSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PulsingNamedSlot_C::ExecuteUbergraph_Widget_PulsingNamedSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PulsingNamedSlot.Widget_PulsingNamedSlot_C.ExecuteUbergraph_Widget_PulsingNamedSlot");

	UWidget_PulsingNamedSlot_C_ExecuteUbergraph_Widget_PulsingNamedSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
