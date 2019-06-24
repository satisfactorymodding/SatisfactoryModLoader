#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FocusOnTarget_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_FocusOnTarget.BTT_FocusOnTarget_C
// 0x0030 (0x00D0 - 0x00A0)
class UBTT_FocusOnTarget_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      FinalGoalBBKey;                                           // 0x00A8(0x0028) (Edit, BlueprintVisible)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_FocusOnTarget.BTT_FocusOnTarget_C");
		return ptr;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_FocusOnTarget(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
