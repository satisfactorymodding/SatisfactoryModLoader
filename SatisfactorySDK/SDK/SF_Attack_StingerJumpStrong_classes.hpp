#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attack_StingerJumpStrong_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Attack_StingerJumpStrong.Attack_StingerJumpStrong_C
// 0x0000 (0x0068 - 0x0068)
class UAttack_StingerJumpStrong_C : public UFGAttackMeleeJump
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Attack_StingerJumpStrong.Attack_StingerJumpStrong_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
