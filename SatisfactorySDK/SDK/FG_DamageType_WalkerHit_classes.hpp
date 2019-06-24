#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_DamageType_WalkerHit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass DamageType_WalkerHit.DamageType_WalkerHit_C
// 0x0000 (0x006B - 0x006B)
class UDamageType_WalkerHit_C : public UBP_DamageType_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass DamageType_WalkerHit.DamageType_WalkerHit_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
