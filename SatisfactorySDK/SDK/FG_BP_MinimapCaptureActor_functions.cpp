// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MinimapCaptureActor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MinimapCaptureActor.BP_MinimapCaptureActor_C.UserConstructionScript
// ()

void ABP_MinimapCaptureActor_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MinimapCaptureActor.BP_MinimapCaptureActor_C.UserConstructionScript");

	ABP_MinimapCaptureActor_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
