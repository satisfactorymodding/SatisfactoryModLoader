#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Zone_RockyDesert_Wildlife_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Zone_RockyDesert_Wildlife.Zone_RockyDesert_Wildlife_C
// 0x0000 (0x0050 - 0x0050)
class UZone_RockyDesert_Wildlife_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Zone_RockyDesert_Wildlife.Zone_RockyDesert_Wildlife_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
