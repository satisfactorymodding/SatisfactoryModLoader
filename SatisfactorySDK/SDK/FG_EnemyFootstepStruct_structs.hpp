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

// UserDefinedStruct EnemyFootstepStruct.EnemyFootstepStruct
// 0x0009
struct FEnemyFootstepStruct
{
	class UAkAudioEvent*                               FootstepEvent_2_644FC38741EB5D87C265E1973A9FCF5E;         // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPhysicalSurface>                      Surface_5_4496CB814B1E6F8199C79DB35C48EAD6;               // 0x0008(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
