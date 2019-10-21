// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Holo_TrainPlatformEmpty_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Holo_TrainPlatformEmpty.Holo_TrainPlatformEmpty_C.UserConstructionScript
// ()

void AHolo_TrainPlatformEmpty_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_TrainPlatformEmpty.Holo_TrainPlatformEmpty_C.UserConstructionScript");

	AHolo_TrainPlatformEmpty_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
