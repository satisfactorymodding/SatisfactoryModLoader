#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_SpaceRabbit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Controller_SpaceRabbit.Controller_SpaceRabbit_C
// 0x0058 (0x0490 - 0x0438)
class AController_SpaceRabbit_C : public AFGCreatureController
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0438(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class AFGCharacterPlayer*                          mPotentialThreat;                                         // 0x0440(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	float                                              mSneakLimit;                                              // 0x0448(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x044C(0x0004) MISSED OFFSET
	struct FName                                       mSneakLimitBBKeyName;                                     // 0x0450(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FName>                               mThreatTags;                                              // 0x0458(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FName                                       mIsCuriousBBKeyName;                                      // 0x0468(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mPersonalDistance;                                        // 0x0470(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0474(0x0004) MISSED OFFSET
	struct FName                                       mPersonalDistanceBBKeyName;                               // 0x0478(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mPanicBBKeyName;                                          // 0x0480(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mFriendBBKeyName;                                         // 0x0488(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Controller_SpaceRabbit.Controller_SpaceRabbit_C");
		return ptr;
	}


	void isThreat(const struct FName& inTag, bool* isThreat);
	void ReactToSound(class AActor* inActor, const struct FVector& soundLocation, const struct FName& Tag, bool* didReact);
	void SetNewThreat(class AFGCharacterPlayer* newThreat);
	void GetCurrentThreat(class AFGCharacterPlayer** outThreat);
	void UserConstructionScript();
	void OnPossess(class APawn** PossessedPawn);
	void BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus);
	void StartPanic();
	void ExecuteUbergraph_Controller_SpaceRabbit(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
