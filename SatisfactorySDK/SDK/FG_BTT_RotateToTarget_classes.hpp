#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_RotateToTarget_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_RotateToTarget.BTT_RotateToTarget_C
// 0x0041 (0x00E1 - 0x00A0)
class UBTT_RotateToTarget_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mTargetLocationBBKey;                                     // 0x00A8(0x0028) (Edit, BlueprintVisible)
	float                                              mTargetRotation;                                          // 0x00D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mTargetLocation;                                          // 0x00D4(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsFacingRotation;                                        // 0x00E0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_RotateToTarget.BTT_RotateToTarget_C");
		return ptr;
	}


	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void RotationComplete(class APawn* PawnRotated);
	void ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_RotateToTarget(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
