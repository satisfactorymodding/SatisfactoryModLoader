// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_TutorialSubsystem_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_TutorialSubsystem.BP_TutorialSubsystem_C.UserConstructionScript
// ()

void UBP_TutorialSubsystem_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_TutorialSubsystem.BP_TutorialSubsystem_C.UserConstructionScript");

	UBP_TutorialSubsystem_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
