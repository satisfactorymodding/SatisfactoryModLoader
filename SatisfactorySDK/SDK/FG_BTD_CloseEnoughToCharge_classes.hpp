#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_CloseEnoughToCharge_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTD_CloseEnoughToCharge.BTD_CloseEnoughToCharge_C
// 0x0028 (0x00C8 - 0x00A0)
class UBTD_CloseEnoughToCharge_C : public UBTDecorator_BlueprintBase
{
public:
	struct FBlackboardKeySelector                      mFinalGoalBBKey;                                          // 0x00A0(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTD_CloseEnoughToCharge.BTD_CloseEnoughToCharge_C");
		return ptr;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
