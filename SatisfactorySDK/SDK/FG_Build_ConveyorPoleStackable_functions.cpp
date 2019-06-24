// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorPoleStackable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorPoleStackable.Build_ConveyorPoleStackable_C.UserConstructionScript
// ()

void ABuild_ConveyorPoleStackable_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorPoleStackable.Build_ConveyorPoleStackable_C.UserConstructionScript");

	ABuild_ConveyorPoleStackable_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
