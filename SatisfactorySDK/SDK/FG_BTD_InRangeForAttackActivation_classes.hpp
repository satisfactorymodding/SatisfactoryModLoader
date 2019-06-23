#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_InRangeForAttackActivation_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTD_InRangeForAttackActivation.BTD_InRangeForAttackActivation_C
// 0x0030 (0x00D0 - 0x00A0)
class UBTD_InRangeForAttackActivation_C : public UBTDecorator_BlueprintBase
{
public:
	class UClass*                                      mAttack;                                                  // 0x00A0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      mEnemyBBKey;                                              // 0x00A8(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTD_InRangeForAttackActivation.BTD_InRangeForAttackActivation_C");
		return ptr;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
