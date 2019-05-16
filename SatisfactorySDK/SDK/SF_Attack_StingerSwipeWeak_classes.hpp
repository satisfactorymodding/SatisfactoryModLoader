#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attack_StingerSwipeWeak_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attack_StingerSwipeWeak.Attack_StingerSwipeWeak_C
// 0x0000 (0x0050 - 0x0050)
class UAttack_StingerSwipeWeak_C : public UFGAttackMelee
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attack_StingerSwipeWeak.Attack_StingerSwipeWeak_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
