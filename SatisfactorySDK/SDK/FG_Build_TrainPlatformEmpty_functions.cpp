// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TrainPlatformEmpty_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_TrainPlatformEmpty.Build_TrainPlatformEmpty_C.UserConstructionScript
// ()

void ABuild_TrainPlatformEmpty_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TrainPlatformEmpty.Build_TrainPlatformEmpty_C.UserConstructionScript");

	ABuild_TrainPlatformEmpty_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
