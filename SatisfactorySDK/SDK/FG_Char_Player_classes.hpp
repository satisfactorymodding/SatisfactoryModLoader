#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Player_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Char_Player.Char_Player_C
// 0x01C8 (0x0CA8 - 0x0AE0)
class AChar_Player_C : public AFGCharacterPlayer
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0AE0(0x0008) (Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      EmoteBuildGun;                                            // 0x0AE8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        HelmetMesh;                                               // 0x0AF0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpotLightComponent*                         FlashLight3P;                                             // 0x0AF8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    Flashlight_01;                                            // 0x0B00(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FlashlightCone;                                           // 0x0B08(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpotLightComponent*                         FlashLight1P;                                             // 0x0B10(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       TestPostProcess;                                          // 0x0B18(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       PPTakeDamage;                                             // 0x0B20(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       PPSpawnScanner;                                           // 0x0B28(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    WindDustGreen_01;                                         // 0x0B30(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAIPerceptionStimuliSourceComponent*         AIPerceptionStimuliSource;                                // 0x0B38(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UTextRenderComponent*                        PlayerText;                                               // 0x0B40(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FScriptMulticastDelegate                    EventScrollDown;                                          // 0x0B48(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    EventScroll;                                              // 0x0B58(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    EventScrollUp;                                            // 0x0B68(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    EventFire;                                                // 0x0B78(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	float                                              mDeltaTime;                                               // 0x0B88(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDesiredDamageIndicator;                                  // 0x0B8C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDamageIndicatorSpeed;                                    // 0x0B90(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLowHealthIndicatorPower;                                 // 0x0B94(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCurrentDamageIndicator;                                  // 0x0B98(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxDamageIndicator;                                      // 0x0B9C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLastDamageTime;                                          // 0x0BA0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTargetCameraDistance;                                    // 0x0BA4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSavedCameraDistance;                                     // 0x0BA8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMin;                                       // 0x0BAC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMax;                                       // 0x0BB0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mTransitionDelay;                                         // 0x0BB4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mTargetCameraOffset;                                      // 0x0BB8(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector                                     mCameraOffset3P;                                          // 0x0BC4(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              mDistanceInterpolationSpeed;                              // 0x0BD0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mTargetCameraFOV;                                         // 0x0BD4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSavedCameraFOV;                                          // 0x0BD8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mIsFocusing;                                              // 0x0BDC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mMuteOnOff;                                               // 0x0BDD(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0BDE(0x0002) MISSED OFFSET
	float                                              mCameraDistanceDefault3P;                                 // 0x0BE0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceFocus3P;                                   // 0x0BE4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mFocusInterpolationSpeed;                                 // 0x0BE8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mDefaultCameraInterpolationSpeed;                         // 0x0BEC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mDefaultFOV;                                              // 0x0BF0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mFocusFOV;                                                // 0x0BF4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMin3P;                                     // 0x0BF8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMax3P;                                     // 0x0BFC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSprintNoiseInterval;                                     // 0x0C00(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeSprinting;                                           // 0x0C04(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mPickupMontageSectionName;                                // 0x0C08(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mPickupMontageSectionName3p;                              // 0x0C10(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UObject*                                     mReviveWidget;                                            // 0x0C18(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mPlayerHUDClass;                                          // 0x0C20(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mFlashlightOn;                                            // 0x0C28(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	bool                                               mWaitingForPlayerState;                                   // 0x0C29(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x0C2A(0x0006) MISSED OFFSET
	TArray<class ULevelSequence*>                      mSequences;                                               // 0x0C30(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class ABP_InteractablesMarker_C*                   mInteractableMarker;                                      // 0x0C40(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mMineSection;                                             // 0x0C48(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGCameraModifierLimitLook*                  mLookModifier;                                            // 0x0C50(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FLinearColor                                mSavedCompassColor;                                       // 0x0C58(0x0010) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidGetCompassColor;                                      // 0x0C68(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0C69(0x0003) MISSED OFFSET
	struct FDisabledInputGate                          mLandingInputGate;                                        // 0x0C6C(0x0004) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
	class USkeletalMeshComponent*                      mEmoteBuildgun;                                           // 0x0C70(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FTimerHandle                                mEmoteTimer;                                              // 0x0C78(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UWidget_EmoteMenu_C*                         mEmoteMenu;                                               // 0x0C80(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mPossessed;                                               // 0x0C88(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0C89(0x0007) MISSED OFFSET
	struct FText                                       mMapText;                                                 // 0x0C90(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Char_Player.Char_Player_C");
		return ptr;
	}


	struct FText SetActorRepresentationText(const struct FText& newText);
	bool UpdateRepresentation();
	struct FLinearColor GetActorRepresentationColor();
	struct FText GetActorRepresentationText();
	class UTexture2D* GetActorRepresentationTexture();
	ERepresentationType GetActorRepresentationType();
	bool GetActorShouldShowInCompass();
	float GetActorFogOfWarRevealRadius();
	EFogOfWarRevealType GetActorFogOfWarRevealType();
	bool RemoveAsRepresentation();
	struct FRotator GetRealActorRotation();
	bool AddAsRepresentation();
	bool GetActorShouldShowOnMap();
	struct FVector GetRealActorLocation();
	bool IsActorStatic();
	void ToggleCodex();
	void ToggleInventory();
	void ToggleFlashlight();
	void RemovePlayerHUD(class AFGPlayerController* OldController);
	void SetupPlayerHUD(class AFGPlayerController* PlayerController);
	void HandleFlashlight();
	void UpdatePlayerTextVisibility();
	void GetHealthPct(float* healthPct);
	void UpdateDamageIndicator();
	void PlayDamageVO(class UDamageType* Damage_Type);
	void PlayDamageCameraShake();
	void ApplyDamagePP();
	void PlayImpactEffectSound(class UDamageType* DamageType);
	void CalculateOnscreenEffectBlendWeight(float* BlendWeight);
	void UpdateWindParticle();
	void TickSprintNoise();
	void GetPlayerCameraManager(class APlayerCameraManager** cameraManager);
	void FadeDamageIndicator();
	void TickPlayerNameText();
	void UserConstructionScript();
	void InpActEvt_OpenCodex_K2Node_InputActionEvent_6(const struct FKey& Key);
	void InpActEvt_Flashlight_K2Node_InputActionEvent_5(const struct FKey& Key);
	void InpActEvt_PrimaryFire_K2Node_InputActionEvent_4(const struct FKey& Key);
	void InpActEvt_Inventory_K2Node_InputActionEvent_3(const struct FKey& Key);
	void InpActEvt_EmoteWheel_K2Node_InputActionEvent_2(const struct FKey& Key);
	void InpActEvt_EmoteWheel_K2Node_InputActionEvent_1(const struct FKey& Key);
	void CameraTick();
	void OnLanded(struct FHitResult* Hit);
	void SetFirstPersonMode();
	void SetThirdPersonMode();
	void StartFocusAim();
	void StopFocusAim();
	void StartFreeRotate3P();
	void StopFreeRotate3P();
	void CameraZoomOut();
	void CameraZoomIn();
	void ReceiveDied();
	void ReceivePossessed(class AController** NewController);
	void PlayPickupEffects();
	void ReceiveDestroyed();
	void TakeDamageEvent(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void SnapSpringArmToDesiredLocation();
	void OnReviveComplete();
	void ClientSetupPlayerHUD(class AController* InController);
	void ReceiveUnpossessed(class AController** OldController);
	void OnReceiveRadiationStart();
	void OnReceiveRadiationTick(float* amount, float* Duration, class UClass** DamageType);
	void OnReceiveRadiationStop();
	void ReceiveBeginPlay();
	void ReceiveTick(float* DeltaSeconds);
	void AudioTickEvent(float AudioTick);
	void Server_PlayClap();
	void Multicast_PlayClap();
	void Server_SetFlashlightOn(bool FlashlightOn);
	void OnDisabledInputGateChanged(struct FDisabledInputGate* NewValue);
	void LimitLook(bool doLimit);
	void StartCinematic();
	void EndCinematic();
	void DisableGravity();
	void Server_PlaySpinEmote();
	void Multicast_PlatSpinEmote();
	void ClearEmoteMesh();
	void OnSpawnDeathMarker();
	void ShowEmote(int EmoteIndex);
	void SkipIntro();
	void Server_playSignsEmote();
	void Multicast_PlaySignsEmote();
	void StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void ExecuteUbergraph_Char_Player(int EntryPoint);
	void EventFire__DelegateSignature();
	void EventScroll__DelegateSignature(int Index);
	void EventScrollDown__DelegateSignature();
	void EventScrollUp__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
