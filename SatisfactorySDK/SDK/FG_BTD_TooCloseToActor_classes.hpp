#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_TooCloseToActor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTD_TooCloseToActor.BTD_TooCloseToActor_C
// 0x0058 (0x00F8 - 0x00A0)
class UBTD_TooCloseToActor_C : public UBTDecorator_BlueprintBase
{
public:
	struct FBlackboardKeySelector                      mOtherActorBBKey;                                         // 0x00A0(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      mMinDistanceBBKey;                                        // 0x00C8(0x0028) (Edit, BlueprintVisible)
	float                                              mDistanceMultiplier;                                      // 0x00F0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mDistance;                                                // 0x00F4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTD_TooCloseToActor.BTD_TooCloseToActor_C");
		return ptr;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
