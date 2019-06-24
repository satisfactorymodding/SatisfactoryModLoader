#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Context_FinalTarget_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Context_FinalTarget.Context_FinalTarget_C
// 0x0000 (0x0030 - 0x0030)
class UContext_FinalTarget_C : public UEnvQueryContext_BlueprintBase
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Context_FinalTarget.Context_FinalTarget_C");
		return ptr;
	}


	void ProvideSingleActor(class UObject** QuerierObject, class AActor** QuerierActor, class AActor** ResultingActor);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
