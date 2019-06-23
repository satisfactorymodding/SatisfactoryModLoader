#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EnemyController_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_EnemyController.BP_EnemyController_C
// 0x0020 (0x0510 - 0x04F0)
class ABP_EnemyController_C : public AFGEnemyController
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x04F0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UBlackboardData*                             mBlackboardAsset;                                         // 0x04F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UBehaviorTree*                               mBehaviorTree;                                            // 0x0500(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mLastKnownTargetLocationBBKeyName;                        // 0x0508(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_EnemyController.BP_EnemyController_C");
		return ptr;
	}


	void UserConstructionScript();
	void OnPossess(class APawn** PossessedPawn);
	void OnAggroTargetLost(class AActor** lostActor);
	void ExecuteUbergraph_BP_EnemyController(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
