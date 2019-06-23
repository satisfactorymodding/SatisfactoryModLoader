// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_LakeWater_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_LakeWater.BP_LakeWater_C.UserConstructionScript
// ()

void ABP_LakeWater_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LakeWater.BP_LakeWater_C.UserConstructionScript");

	ABP_LakeWater_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
