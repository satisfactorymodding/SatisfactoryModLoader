#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FollowTrackPath_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_FollowTrackPath.BTT_FollowTrackPath_C
// 0x0058 (0x00F8 - 0x00A0)
class UBTT_FollowTrackPath_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mIsDestinationReachedKey;                                 // 0x00A8(0x0028) (Edit, BlueprintVisible)
	class AFGLocomotive*                               mLocomotive;                                              // 0x00D0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class UFGLocomotiveMovementComponent*              mMovement;                                                // 0x00D8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	float                                              mApproachSpeed;                                           // 0x00E0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mApproachDistance;                                        // 0x00E4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mApproachBrakeMargin;                                     // 0x00E8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSpeed;                                                   // 0x00EC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDistance;                                                // 0x00F0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTargetSpeed;                                             // 0x00F4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_FollowTrackPath.BTT_FollowTrackPath_C");
		return ptr;
	}


	void CalcBrakeCurve(float Distance, float New_Speed, float Deceleration, bool Is_Stopping, float* Target_Speed);
	void CalcBrakeDistance(float Speed, float New_Speed, float Deceleration, float* Distance);
	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds);
	void ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void FinishStopping();
	void StopAllMovement();
	void InvalidatePath();
	void ExecuteUbergraph_BTT_FollowTrackPath(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
