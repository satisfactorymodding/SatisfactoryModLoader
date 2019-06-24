// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Beacon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Beacon.Anim_Beacon_C.ExecuteUbergraph_Anim_Beacon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Beacon_C::ExecuteUbergraph_Anim_Beacon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Beacon.Anim_Beacon_C.ExecuteUbergraph_Anim_Beacon");

	UAnim_Beacon_C_ExecuteUbergraph_Anim_Beacon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
