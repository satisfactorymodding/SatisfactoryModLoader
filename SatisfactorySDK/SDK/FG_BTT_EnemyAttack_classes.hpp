#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_EnemyAttack_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTT_EnemyAttack.BTT_EnemyAttack_C
// 0x0018 (0x00B8 - 0x00A0)
class UBTT_EnemyAttack_C : public UBTTask_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x00A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UClass*                                      mAttackClass;                                             // 0x00A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UGameplayTask*                               mGameplayTask;                                            // 0x00B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTT_EnemyAttack.BTT_EnemyAttack_C");
		return ptr;
	}


	void mOnAttackFailed_8426540B4FC18260A20A279426BD39C8();
	void mOnAttackFinished_8426540B4FC18260A20A279426BD39C8();
	void ReceiveAbort(class AActor** OwnerActor);
	void ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTT_EnemyAttack(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
