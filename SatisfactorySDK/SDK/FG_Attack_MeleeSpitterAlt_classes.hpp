#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attack_MeleeSpitterAlt_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attack_MeleeSpitterAlt.Attack_MeleeSpitterAlt_C
// 0x0000 (0x0058 - 0x0058)
class UAttack_MeleeSpitterAlt_C : public UFGAttackRanged
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attack_MeleeSpitterAlt.Attack_MeleeSpitterAlt_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
