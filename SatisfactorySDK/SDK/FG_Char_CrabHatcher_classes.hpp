#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_CrabHatcher_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_CrabHatcher.Char_CrabHatcher_C
// 0x0030 (0x09C0 - 0x0990)
class AChar_CrabHatcher_C : public AFGCrabHatcher
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0990(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UParticleSystemComponent*                    CrabEggsHatch_01;                                         // 0x0998(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             Scene;                                                    // 0x09A0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        StaticMesh;                                               // 0x09A8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAnimSequence*                               mGrowAnimation;                                           // 0x09B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mEnemiesSpawned;                                          // 0x09B8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mEnemiesToSpawn;                                          // 0x09BC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_CrabHatcher.Char_CrabHatcher_C");
		return ptr;
	}


	void SpawnTimer();
	void PlaySpawnEffects();
	void UserConstructionScript();
	void ReceiveBeginPlay();
	void Damaged(class AActor* damagedActor, float Damage, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void SpawnCrabs();
	void StartExpanding();
	void ReceiveActorBeginOverlap(class AActor** OtherActor);
	void ExecuteUbergraph_Char_CrabHatcher(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
