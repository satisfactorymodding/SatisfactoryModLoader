// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Truck_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Truck.Anim_Truck_C.ExecuteUbergraph_Anim_Truck
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Truck_C::ExecuteUbergraph_Anim_Truck(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Truck.Anim_Truck_C.ExecuteUbergraph_Anim_Truck");

	UAnim_Truck_C_ExecuteUbergraph_Anim_Truck_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
