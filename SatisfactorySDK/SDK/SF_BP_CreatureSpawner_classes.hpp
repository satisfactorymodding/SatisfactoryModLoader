#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_CreatureSpawner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_CreatureSpawner.BP_CreatureSpawner_C
// 0x0000 (0x0390 - 0x0390)
class ABP_CreatureSpawner_C : public AFGCreatureSpawner
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CreatureSpawner.BP_CreatureSpawner_C");
		return ptr;
	}


	void CallCalculateSpawnLocations();
	void UserConstructionScript();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
