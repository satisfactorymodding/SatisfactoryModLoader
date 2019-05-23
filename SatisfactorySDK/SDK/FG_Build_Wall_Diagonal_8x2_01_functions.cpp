// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_Wall_Diagonal_8x2_01_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_Wall_Diagonal_8x2_01.Build_Wall_Diagonal_8x2_01_C.UserConstructionScript
// ()

void ABuild_Wall_Diagonal_8x2_01_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_Wall_Diagonal_8x2_01.Build_Wall_Diagonal_8x2_01_C.UserConstructionScript");

	ABuild_Wall_Diagonal_8x2_01_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
