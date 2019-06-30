// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Holo_TrainStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Holo_TrainStation.Holo_TrainStation_C.UserConstructionScript
// ()

void AHolo_TrainStation_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_TrainStation.Holo_TrainStation_C.UserConstructionScript");

	AHolo_TrainStation_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
