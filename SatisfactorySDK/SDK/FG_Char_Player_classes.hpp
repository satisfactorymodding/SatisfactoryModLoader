#pragma once

// Satisfactory SDK

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
// 0x01D8 (0x0CD8 - 0x0B00)
class AChar_Player_C : public AFGCharacterPlayer
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0B00(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UPostProcessComponent*                       PPRadiationDamage;                                        // 0x0B08(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      EmoteBuildGun;                                            // 0x0B10(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        HelmetMesh;                                               // 0x0B18(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpotLightComponent*                         FlashLight3P;                                             // 0x0B20(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    Flashlight_01;                                            // 0x0B28(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        FlashlightCone;                                           // 0x0B30(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpotLightComponent*                         FlashLight1P;                                             // 0x0B38(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       TestPostProcess;                                          // 0x0B40(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       PPTakeDamage;                                             // 0x0B48(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       PPSpawnScanner;                                           // 0x0B50(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    WindDustGreen_01;                                         // 0x0B58(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAIPerceptionStimuliSourceComponent*         AIPerceptionStimuliSource;                                // 0x0B60(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UTextRenderComponent*                        PlayerText;                                               // 0x0B68(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FScriptMulticastDelegate                    EventScrollDown;                                          // 0x0B70(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    EventScroll;                                              // 0x0B80(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    EventScrollUp;                                            // 0x0B90(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    EventFire;                                                // 0x0BA0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	float                                              mDeltaTime;                                               // 0x0BB0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDesiredDamageIndicator;                                  // 0x0BB4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDamageIndicatorSpeed;                                    // 0x0BB8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLowHealthIndicatorPower;                                 // 0x0BBC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCurrentDamageIndicator;                                  // 0x0BC0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxDamageIndicator;                                      // 0x0BC4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLastDamageTime;                                          // 0x0BC8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTargetCameraDistance;                                    // 0x0BCC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSavedCameraDistance;                                     // 0x0BD0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMin;                                       // 0x0BD4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMax;                                       // 0x0BD8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mTransitionDelay;                                         // 0x0BDC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mTargetCameraOffset;                                      // 0x0BE0(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mCameraOffset3P;                                          // 0x0BEC(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mDistanceInterpolationSpeed;                              // 0x0BF8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mTargetCameraFOV;                                         // 0x0BFC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSavedCameraFOV;                                          // 0x0C00(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mIsFocusing;                                              // 0x0C04(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mMuteOnOff;                                               // 0x0C05(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0C06(0x0002) MISSED OFFSET
	float                                              mCameraDistanceDefault3P;                                 // 0x0C08(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceFocus3P;                                   // 0x0C0C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mFocusInterpolationSpeed;                                 // 0x0C10(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mDefaultCameraInterpolationSpeed;                         // 0x0C14(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mDefaultFOV;                                              // 0x0C18(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mFocusFOV;                                                // 0x0C1C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMin3P;                                     // 0x0C20(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mCameraDistanceMax3P;                                     // 0x0C24(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mSprintNoiseInterval;                                     // 0x0C28(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeSprinting;                                           // 0x0C2C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mPickupMontageSectionName;                                // 0x0C30(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mPickupMontageSectionName3p;                              // 0x0C38(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UObject*                                     mReviveWidget;                                            // 0x0C40(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mPlayerHUDClass;                                          // 0x0C48(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mFlashlightOn;                                            // 0x0C50(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	bool                                               mWaitingForPlayerState;                                   // 0x0C51(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x0C52(0x0006) MISSED OFFSET
	TArray<class ULevelSequence*>                      mSequences;                                               // 0x0C58(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class ABP_InteractablesMarker_C*                   mInteractableMarker;                                      // 0x0C68(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mMineSection;                                             // 0x0C70(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGCameraModifierLimitLook*                  mLookModifier;                                            // 0x0C78(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FLinearColor                                mSavedCompassColor;                                       // 0x0C80(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidGetCompassColor;                                      // 0x0C90(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0C91(0x0003) MISSED OFFSET
	struct FDisabledInputGate                          mLandingInputGate;                                        // 0x0C94(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class USkeletalMeshComponent*                      mEmoteBuildgun;                                           // 0x0C98(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FTimerHandle                                mEmoteTimer;                                              // 0x0CA0(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UWidget_EmoteMenu_C*                         mEmoteMenu;                                               // 0x0CA8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mPossessed;                                               // 0x0CB0(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0CB1(0x0007) MISSED OFFSET
	struct FText                                       mMapText;                                                 // 0x0CB8(0x0028) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UMaterialInstanceDynamic*                    mRadiationNoise;                                          // 0x0CD0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

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
	void SetFirstPersonMode();
	void SetThirdPersonMode();
	void StartFocusAim();
	void StopFocusAim();
	void StartFreeRotate3P();
	void StopFreeRotate3P();
	void CameraZoomOut();
	void CameraZoomIn();
	void ReceiveDied();
	void CameraTick();
	void PlayPickupEffects();
	void SnapSpringArmToDesiredLocation();
	void OnReviveComplete();
	void OnLanded(struct FHitResult* Hit);
	void ClientSetupPlayerHUD(class AController* InController);
	void ReceiveUnpossessed(class AController** OldController);
	void OnReceiveRadiationStart();
	void OnReceiveRadiationStop();
	void ReceivePossessed(class AController** NewController);
	void ReceiveDestroyed();
	void TakeDamageEvent(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void ReceiveBeginPlay();
	void ReceiveTick(float* DeltaSeconds);
	void Server_PlayClap();
	void Multicast_PlayClap();
	void Server_SetFlashlightOn(bool FlashlightOn);
	void OnDisabledInputGateChanged(struct FDisabledInputGate* NewValue);
	void AudioTickEvent(float AudioTick);
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
	void OnRadiationIntensityUpdated(float* radiationIntensity, float* radiationImmunity);
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
