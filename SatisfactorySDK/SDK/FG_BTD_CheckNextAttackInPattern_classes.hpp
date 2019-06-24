#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_CheckNextAttackInPattern_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C
// 0x0010 (0x00B0 - 0x00A0)
class UBTD_CheckNextAttackInPattern_C : public UBTDecorator_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UClass*                                      mAttackToCheck;                                           // 0x00A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C");
		return ptr;
	}


	bool PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ReceiveExecutionStartAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTD_CheckNextAttackInPattern(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
