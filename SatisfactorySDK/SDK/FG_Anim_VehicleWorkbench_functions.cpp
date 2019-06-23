// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_VehicleWorkbench_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_VehicleWorkbench.Anim_VehicleWorkbench_C.ExecuteUbergraph_Anim_VehicleWorkbench
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_VehicleWorkbench_C::ExecuteUbergraph_Anim_VehicleWorkbench(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_VehicleWorkbench.Anim_VehicleWorkbench_C.ExecuteUbergraph_Anim_VehicleWorkbench");

	UAnim_VehicleWorkbench_C_ExecuteUbergraph_Anim_VehicleWorkbench_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
