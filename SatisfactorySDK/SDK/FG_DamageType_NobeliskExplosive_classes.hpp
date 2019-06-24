#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_DamageType_NobeliskExplosive_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass DamageType_NobeliskExplosive.DamageType_NobeliskExplosive_C
// 0x0000 (0x006B - 0x006B)
class UDamageType_NobeliskExplosive_C : public UBP_DamageType_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass DamageType_NobeliskExplosive.DamageType_NobeliskExplosive_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
