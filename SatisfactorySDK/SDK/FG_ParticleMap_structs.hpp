#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct ParticleMap.ParticleMap
// 0x0038
struct FParticleMap
{
	TSoftObjectPtr<class UClass>                       ResourceNode_16_2100B5C34EE8DF7958D78A974512F3C3;         // 0x0000(0x0028) (Edit, BlueprintVisible)
	class UParticleSystem*                             ParticleSystem1_9_F0CF81514E1E1C5007AC99B0C59C63CD;       // 0x0028(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UParticleSystem*                             ParticleSystem2_12_9CB1B6054B443457EF842EA10A375BF2;      // 0x0030(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
