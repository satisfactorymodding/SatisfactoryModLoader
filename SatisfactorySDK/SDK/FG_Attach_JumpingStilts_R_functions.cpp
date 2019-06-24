// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_JumpingStilts_R_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_JumpingStilts_R.Attach_JumpingStilts_R_C.UserConstructionScript
// ()

void AAttach_JumpingStilts_R_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_JumpingStilts_R.Attach_JumpingStilts_R_C.UserConstructionScript");

	AAttach_JumpingStilts_R_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
