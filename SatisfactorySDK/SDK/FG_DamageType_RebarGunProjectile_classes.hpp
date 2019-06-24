#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_DamageType_RebarGunProjectile_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass DamageType_RebarGunProjectile.DamageType_RebarGunProjectile_C
// 0x0000 (0x0068 - 0x0068)
class UDamageType_RebarGunProjectile_C : public UFGDamageType
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass DamageType_RebarGunProjectile.DamageType_RebarGunProjectile_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
