#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_SpaceRabbit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_SpaceRabbit.Char_SpaceRabbit_C
// 0x00B8 (0x0A28 - 0x0970)
class AChar_SpaceRabbit_C : public AFGCreature
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0970(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UFGInventoryComponent*                       mInventory;                                               // 0x0978(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       mFriendBBKeyName;                                         // 0x0980(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FText                                       mPetText;                                                 // 0x0988(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	class AFGCharacterPlayer*                          mPotentialThreat;                                         // 0x09A0(0x0008) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FTimerHandle                                mWalkBackTimerHandle;                                     // 0x09A8(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	bool                                               mIsWalkingBackwards;                                      // 0x09B0(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x09B1(0x0003) MISSED OFFSET
	struct FVector                                     mWalkBackDirection;                                       // 0x09B4(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnWalkBackStopped;                                        // 0x09C0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	float                                              mWalkBackDistance;                                        // 0x09D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x09D4(0x0004) MISSED OFFSET
	class AActor*                                      mFriendActor;                                             // 0x09D8(0x0008) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, SaveGame, IsPlainOldData)
	int                                                mLootTableIndex;                                          // 0x09E0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x09E4(0x0004) MISSED OFFSET
	class UClass*                                      mLootSettings;                                            // 0x09E8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FTimerHandle                                mLootTimerHandle;                                         // 0x09F0(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance, SaveGame)
	float                                              mLotMinTime;                                              // 0x09F8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLotMaxTime;                                              // 0x09FC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsAlive;                                                 // 0x0A00(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0A01(0x0007) MISSED OFFSET
	struct FName                                       mGotBerryBBKeyName;                                       // 0x0A08(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FText                                       mFriendText;                                              // 0x0A10(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_SpaceRabbit.Char_SpaceRabbit_C");
		return ptr;
	}


	struct FText GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	bool IsUseable();
	void UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState);
	void SetupLootTimer();
	void OnRep_mLootTableIndex();
	void RollLoot();
	void SetNewFriend(class AActor* newFriend);
	void StopBackwardWalk();
	void UpdateWalkBackMovement();
	void UpdateWalkBackDirection();
	void StartWalkBack();
	void UserConstructionScript();
	void OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void RegisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void UnregisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void ReceiveTick(float* DeltaSeconds);
	void NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser);
	void ReceiveDied();
	void NotifyOnTakePointDamage(class AActor** damagedActor, float* Damage, class AController** instigatedBy, struct FVector* HitLocation, class UPrimitiveComponent** HitComponent, struct FName* BoneName, struct FVector* ShotFromDirection, class UDamageType** DamageType, class AActor** damageCauser);
	void NotifyOnTakeRadialDamage(class AActor** damagedActor, float* Damage, class AController** instigatedBy, class UDamageType** DamageType, class AActor** damageCauser);
	void ReceiveBeginPlay();
	void PlayConsumeItemEffect(class UClass** itemDescriptor, int* amount);
	void OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void ExecuteUbergraph_Char_SpaceRabbit(int EntryPoint);
	void OnWalkBackStopped__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
