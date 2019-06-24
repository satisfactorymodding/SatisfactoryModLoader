#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveWithinAttackRange_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C
// 0x0048 (0x00E8 - 0x00A0)
class UBTT_MoveWithinAttackRange_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mTargetBBKey;                                             // 0x00A8(0x0028) (Edit, BlueprintVisible)
	class UClass*                                      mAttackClass;                                             // 0x00D0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class APawn*                                       mPawn;                                                    // 0x00D8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class AAIController*                               mAIController;                                            // 0x00E0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C");
		return ptr;
	}


	void OnFail_FB4697D6429DCDB2C971F1AA11DB20A1(TEnumAsByte<EPathFollowingResult> MovementResult);
	void OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1(TEnumAsByte<EPathFollowingResult> MovementResult);
	void OnFail_2F8CAD6F41C7875D308D88AD97B454B9(TEnumAsByte<EPathFollowingResult> MovementResult);
	void OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9(TEnumAsByte<EPathFollowingResult> MovementResult);
	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_MoveWithinAttackRange(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
