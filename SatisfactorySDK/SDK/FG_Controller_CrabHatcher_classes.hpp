#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_CrabHatcher_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Controller_CrabHatcher.Controller_CrabHatcher_C
// 0x0018 (0x0528 - 0x0510)
class AController_CrabHatcher_C : public ABP_EnemyController_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0510(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	TArray<class AFGCharacterPlayer*>                  mPlayersNearby;                                           // 0x0518(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Controller_CrabHatcher.Controller_CrabHatcher_C");
		return ptr;
	}


	void UpdateThreatNearby();
	void UserConstructionScript();
	void BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus);
	void TryRemovePlayer(class AFGCharacterPlayer* inPlayer);
	void TryAddPlayer(class AFGCharacterPlayer* inPlayer);
	void ExecuteUbergraph_Controller_CrabHatcher(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
