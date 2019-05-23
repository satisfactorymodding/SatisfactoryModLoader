// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_CheatPowerSource_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_CheatPowerSource.Build_CheatPowerSource_C.UserConstructionScript
// ()

void ABuild_CheatPowerSource_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatPowerSource.Build_CheatPowerSource_C.UserConstructionScript");

	ABuild_CheatPowerSource_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
