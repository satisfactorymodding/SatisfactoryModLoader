#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Zone_CraterLakes_DayNight_Wildlife_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Zone_CraterLakes_DayNight_Wildlife.Zone_CraterLakes_DayNight_Wildlife_C
// 0x0000 (0x0050 - 0x0050)
class UZone_CraterLakes_DayNight_Wildlife_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Zone_CraterLakes_DayNight_Wildlife.Zone_CraterLakes_DayNight_Wildlife_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
