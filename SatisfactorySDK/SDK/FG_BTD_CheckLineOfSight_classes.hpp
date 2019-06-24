#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_CheckLineOfSight_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTD_CheckLineOfSight.BTD_CheckLineOfSight_C
// 0x0000 (0x00A0 - 0x00A0)
class UBTD_CheckLineOfSight_C : public UBTDecorator_BlueprintBase
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTD_CheckLineOfSight.BTD_CheckLineOfSight_C");
		return ptr;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
