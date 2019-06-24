// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_Wall_Conveyor_8x4_01_Steel_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_Wall_Conveyor_8x4_01_Steel.Build_Wall_Conveyor_8x4_01_Steel_C.UserConstructionScript
// ()

void ABuild_Wall_Conveyor_8x4_01_Steel_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_Wall_Conveyor_8x4_01_Steel.Build_Wall_Conveyor_8x4_01_Steel_C.UserConstructionScript");

	ABuild_Wall_Conveyor_8x4_01_Steel_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
