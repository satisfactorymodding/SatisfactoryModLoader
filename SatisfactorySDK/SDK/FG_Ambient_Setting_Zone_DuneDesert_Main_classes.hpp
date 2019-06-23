#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Ambient_Setting_Zone_DuneDesert_Main_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Ambient_Setting_Zone_DuneDesert_Main.Ambient_Setting_Zone_DuneDesert_Main_C
// 0x0000 (0x0050 - 0x0050)
class UAmbient_Setting_Zone_DuneDesert_Main_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Ambient_Setting_Zone_DuneDesert_Main.Ambient_Setting_Zone_DuneDesert_Main_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
