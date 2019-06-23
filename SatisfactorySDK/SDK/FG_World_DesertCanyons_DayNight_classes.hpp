#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_World_DesertCanyons_DayNight_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass World_DesertCanyons_DayNight.World_DesertCanyons_DayNight_C
// 0x0000 (0x0050 - 0x0050)
class UWorld_DesertCanyons_DayNight_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass World_DesertCanyons_DayNight.World_DesertCanyons_DayNight_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
