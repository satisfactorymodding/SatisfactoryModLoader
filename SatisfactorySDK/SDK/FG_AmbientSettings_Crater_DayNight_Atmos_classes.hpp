#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AmbientSettings_Crater_DayNight_Atmos_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass AmbientSettings_Crater_DayNight_Atmos.AmbientSettings_Crater_DayNight_Atmos_C
// 0x0000 (0x0050 - 0x0050)
class UAmbientSettings_Crater_DayNight_Atmos_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass AmbientSettings_Crater_DayNight_Atmos.AmbientSettings_Crater_DayNight_Atmos_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
