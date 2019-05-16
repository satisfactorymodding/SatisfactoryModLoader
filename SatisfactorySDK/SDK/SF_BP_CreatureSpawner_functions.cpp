// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_CreatureSpawner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_CreatureSpawner.BP_CreatureSpawner_C.CallCalculateSpawnLocations
// ()

void ABP_CreatureSpawner_C::CallCalculateSpawnLocations()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSpawner.BP_CreatureSpawner_C.CallCalculateSpawnLocations");

	ABP_CreatureSpawner_C_CallCalculateSpawnLocations_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSpawner.BP_CreatureSpawner_C.UserConstructionScript
// ()

void ABP_CreatureSpawner_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSpawner.BP_CreatureSpawner_C.UserConstructionScript");

	ABP_CreatureSpawner_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
