#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_IsEnemyInRange_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BTS_IsEnemyInRange.BTS_IsEnemyInRange_C
// 0x0068 (0x0100 - 0x0098)
class UBTS_IsEnemyInRange_C : public UBTService_BlueprintBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0098(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FBlackboardKeySelector                      mEnemyBBKey;                                              // 0x00A0(0x0028) (Edit, BlueprintVisible)
	struct FBlackboardKeySelector                      mIsInRangeBBKey;                                          // 0x00C8(0x0028) (Edit, BlueprintVisible)
	class AFGEnemyController*                          mAIController;                                            // 0x00F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mAttackClass;                                             // 0x00F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BTS_IsEnemyInRange.BTS_IsEnemyInRange_C");
		return ptr;
	}


	void ReceiveTick(class AActor** OwnerActor, float* DeltaSeconds);
	void ReceiveActivationAI(class AAIController** OwnerController, class APawn** ControlledPawn);
	void ExecuteUbergraph_BTS_IsEnemyInRange(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
