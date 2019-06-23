#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Context_KnownThreatLocations_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Context_KnownThreatLocations.Context_KnownThreatLocations_C
// 0x0000 (0x0030 - 0x0030)
class UContext_KnownThreatLocations_C : public UEnvQueryContext_BlueprintBase
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Context_KnownThreatLocations.Context_KnownThreatLocations_C");
		return ptr;
	}


	void ProvideLocationsSet(class UObject** QuerierObject, class AActor** QuerierActor, TArray<struct FVector>* ResultingLocationSet);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
