#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AS_Beach_DistantCrashingWaves_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass AS_Beach_DistantCrashingWaves.AS_Beach_DistantCrashingWaves_C
// 0x0000 (0x0050 - 0x0050)
class UAS_Beach_DistantCrashingWaves_C : public UFGAmbientSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass AS_Beach_DistantCrashingWaves.AS_Beach_DistantCrashingWaves_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
