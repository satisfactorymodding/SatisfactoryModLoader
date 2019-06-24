#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_SpaceGiraffe_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_SpaceGiraffe.Char_SpaceGiraffe_C
// 0x0048 (0x09B8 - 0x0970)
class AChar_SpaceGiraffe_C : public AFGCreature
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0970(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UCapsuleComponent*                           Capsule;                                                  // 0x0978(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mDoPanic;                                                 // 0x0980(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0981(0x0007) MISSED OFFSET
	class UCurveFloat*                                 mRotationRateCurve;                                       // 0x0988(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsMoving;                                                // 0x0990(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0991(0x0003) MISSED OFFSET
	float                                              mRotationWhileStill;                                      // 0x0994(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRotationWhileMoving;                                     // 0x0998(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsSprinting;                                             // 0x099C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x099D(0x0003) MISSED OFFSET
	struct FRotator                                    mDefaultCameraRotation;                                   // 0x09A0(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x09AC(0x0004) MISSED OFFSET
	class ABP_CreatureSeat_C*                          mSeat;                                                    // 0x09B0(0x0008) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_SpaceGiraffe.Char_SpaceGiraffe_C");
		return ptr;
	}


	struct FText GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	bool IsUseable();
	void UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState);
	void OnRep_mDoPanic();
	void UserConstructionScript();
	void OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void RegisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void UnregisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void ReceiveTick(float* DeltaSeconds);
	void NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser);
	void StartRotationMovement(struct FRotator* TargetRotation);
	void InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1(float AxisValue);
	void InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10(float AxisValue);
	void ReceivePossessed(class AController** NewController);
	void ClientSetupHUD(class AFGPlayerController* Controller);
	void ReceiveUnpossessed(class AController** OldController);
	void OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
	void ReceiveDied();
	void ExecuteUbergraph_Char_SpaceGiraffe(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
