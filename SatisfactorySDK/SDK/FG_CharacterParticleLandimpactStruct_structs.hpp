#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct CharacterParticleLandimpactStruct.CharacterParticleLandimpactStruct
// 0x0010
struct FCharacterParticleLandimpactStruct
{
	TEnumAsByte<EPhysicalSurface>                      Surface_3_669507A4426EEB0ED2A1ED9E69467285;               // 0x0000(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	class UParticleSystem*                             EmitterTemplate_5_57DEDFA44FB7987EE1982E84B3640E76;       // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
