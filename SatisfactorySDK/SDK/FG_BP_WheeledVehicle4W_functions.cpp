// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_WheeledVehicle4W_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_WheeledVehicle4W.BP_WheeledVehicle4W_C.UserConstructionScript
// ()

void ABP_WheeledVehicle4W_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle4W.BP_WheeledVehicle4W_C.UserConstructionScript");

	ABP_WheeledVehicle4W_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
