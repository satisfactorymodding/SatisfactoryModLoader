#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_FactoryGame_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class FactoryGame.FGActorRepresentation
// 0x0078 (0x00A0 - 0x0028)
class UFGActorRepresentation : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	class AActor*                                      mRealActor;                                               // 0x0030(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	struct FVector_NetQuantize                         mActorLocation;                                           // 0x0038(0x000C) (Net)
	struct FRotator                                    mActorRotation;                                           // 0x0044(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mIsStatic;                                                // 0x0050(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0051(0x0007) MISSED OFFSET
	class UTexture2D*                                  mRepresentationTexture;                                   // 0x0058(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	struct FText                                       mRepresentationText;                                      // 0x0060(0x0028) (Net)
	struct FLinearColor                                mRepresentationColor;                                     // 0x0078(0x0010) (Net, ZeroConstructor, IsPlainOldData)
	ERepresentationType                                mRepresentationType;                                      // 0x0088(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	EFogOfWarRevealType                                mFogOfWarRevealType;                                      // 0x0089(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x008A(0x0002) MISSED OFFSET
	float                                              mFogOfWarRevealRadius;                                    // 0x008C(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x0090(0x0008) MISSED OFFSET
	bool                                               mShouldShowInCompass;                                     // 0x0098(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mShouldShowOnMap;                                         // 0x0099(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x6];                                       // 0x009A(0x0006) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGActorRepresentation");
		return ptr;
	}


	void OnRep_ShouldShowOnMap();
	void OnRep_ShouldShowInCompass();
	void OnRep_RepresentationTexture();
	void OnRep_RepresentationText();
	void OnRep_RepresentationColor();
	void OnRep_FogOfWarRevealType();
	void OnRep_FogOfWarRevealRadius();
	bool IsActorStatic();
	bool GetShouldShowOnMap();
	bool GetShouldShowInCompass();
	ERepresentationType GetRepresentationType();
	class UTexture2D* GetRepresentationTexture();
	struct FText GetRepresentationText();
	struct FLinearColor GetRepresentationColor();
	class AActor* GetRealActor();
	bool GetIsTemporary();
	EFogOfWarRevealType GetFogOfWarRevealType();
	float GetFogOfWarRevealRadius();
	struct FRotator GetActorRotation();
	struct FVector GetActorLocation();
};


// Class FactoryGame.FGActorRepresentationInterface
// 0x0000 (0x0028 - 0x0028)
class UFGActorRepresentationInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGActorRepresentationInterface");
		return ptr;
	}


	bool UpdateRepresentation();
	struct FText SetActorRepresentationText(const struct FText& newText);
	bool RemoveAsRepresentation();
	bool IsActorStatic();
	struct FRotator GetRealActorRotation();
	struct FVector GetRealActorLocation();
	bool GetActorShouldShowOnMap();
	bool GetActorShouldShowInCompass();
	ERepresentationType GetActorRepresentationType();
	class UTexture2D* GetActorRepresentationTexture();
	struct FText GetActorRepresentationText();
	struct FLinearColor GetActorRepresentationColor();
	EFogOfWarRevealType GetActorFogOfWarRevealType();
	float GetActorFogOfWarRevealRadius();
	bool AddAsRepresentation();
};


// Class FactoryGame.FGSubsystem
// 0x0000 (0x0328 - 0x0328)
class AFGSubsystem : public AInfo
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSubsystem");
		return ptr;
	}

};


// Class FactoryGame.FGActorRepresentationManager
// 0x0080 (0x03A8 - 0x0328)
class AFGActorRepresentationManager : public AFGSubsystem
{
public:
	struct FScriptMulticastDelegate                    mOnActorRepresentationAdded;                              // 0x0328(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnActorRepresentationRemoved;                            // 0x0338(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnActorRepresentationUpdated;                            // 0x0348(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnActorRepresentationUpdatedCompassShow;                 // 0x0358(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnActorRepresentationUpdatedMapShow;                     // 0x0368(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<class UFGActorRepresentation*>              mReplicatedRepresentations;                               // 0x0378(0x0010) (Net, ZeroConstructor)
	TArray<class UFGActorRepresentation*>              mClientReplicatedRepresentations;                         // 0x0388(0x0010) (ZeroConstructor)
	TArray<class UFGActorRepresentation*>              mLocalRepresentations;                                    // 0x0398(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGActorRepresentationManager");
		return ptr;
	}


	bool UpdateRepresentation(class AActor* realActor, bool isLocal);
	bool RemoveRepresentationOfActor(class AActor* realActor);
	void OnRep_ReplicatedRepresentations();
	void GetAllActorRepresentations(TArray<class UFGActorRepresentation*>* out_AllRepresentations);
	class AFGActorRepresentationManager* Get(class UObject* WorldContext);
	bool CreateAndAddNewRepresentationNoActor(const struct FVector& Location, class UTexture2D* compassTexture, const struct FLinearColor& compassColor, float LifeTime, bool shouldShowInCompass, bool shouldShowOnMap, ERepresentationType representationType, bool isLocal);
	bool CreateAndAddNewRepresentation(class AActor* realActor, bool isLocal);
};


// Class FactoryGame.FGAggroTargetInterface
// 0x0000 (0x0028 - 0x0028)
class UFGAggroTargetInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAggroTargetInterface");
		return ptr;
	}


	void UnregisterAttacker(class AFGEnemyController* forController);
	bool ShouldAutoregisterAsTargetable();
	void RegisterIncomingAttacker(class AFGEnemyController* forController);
	bool IsAlive();
	class UPrimitiveComponent* GetTargetComponent();
	float GetEnemyTargetDesirability(class AFGEnemyController* forController);
	struct FVector GetAttackLocation();
	class AActor* GetActor();
};


// Class FactoryGame.FGAISystem
// 0x00A0 (0x01D0 - 0x0130)
class UFGAISystem : public UAISystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0130(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnAggroTargetAdded;                                      // 0x0138(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnAggroTargetRemoved;                                    // 0x0148(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mDisableAIDistance;                                       // 0x0158(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNavWalkingDistance;                                      // 0x015C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMeshTickEnableDistance;                                  // 0x0160(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMeshUpdateDistance;                                      // 0x0164(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mActivateSpawnerDistance;                                 // 0x0168(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDisablePawnMovement;                                     // 0x016C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x5B];                                      // 0x016D(0x005B) MISSED OFFSET
	int                                                mMaxCreatureIterationsPerTick;                            // 0x01C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMaxSpawnerIterationsPerTick;                             // 0x01CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAISystem");
		return ptr;
	}


	void UnpardonActor(class AActor* inActor);
	void RemoveFromTargetableList(const TScriptInterface<class UFGAggroTargetInterface>& aggroTarget);
	void PlayerDestroyed(class AActor* destroyedPlayer);
	void PardonActor(class AActor* inActor);
	bool IsActorPardoned(class AActor* inActor);
	TArray<TScriptInterface<class UFGAggroTargetInterface>> GetAggroTargetList();
	void CreatureDestroyed(class AActor* destroyedEnemy);
	void ClearAllPardonedActors();
	void AggroTargetDestroyed(class AActor* DestroyedActor);
	void AddToTargetableList(const TScriptInterface<class UFGAggroTargetInterface>& aggroTarget);
};


// Class FactoryGame.FGAmbientSettings
// 0x0028 (0x0050 - 0x0028)
class UFGAmbientSettings : public UObject
{
public:
	class UAkAudioEvent*                               mOnEnterOuterVolumeEvent;                                 // 0x0028(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mOnExitOuterVolumeEvent;                                  // 0x0030(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mOnEnterInnerVolumeEvent;                                 // 0x0038(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mOnExitInnerVolumeEvent;                                  // 0x0040(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      mIgnoreListenerRotation : 1;                              // 0x0048(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0049(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAmbientSettings");
		return ptr;
	}


	bool ShouldIgnoreListenerRotation();
	void OnExitOuterVolume(class UAkComponent* ambientComponent);
	void OnExitInnerVolume(class UAkComponent* ambientComponent);
	void OnEnterOuterVolume(class UAkComponent* ambientComponent);
	void OnEnterInnerVolume(class UAkComponent* ambientComponent);
	class UAkAudioEvent* GetEnterOuterVolumeEvent();
	class UAkAudioEvent* GetEnterInnerVolumeEvent();
};


// Class FactoryGame.FGAmbientSoundSpline
// 0x0020 (0x0348 - 0x0328)
class AFGAmbientSoundSpline : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class USplineComponent*                            mSpline;                                                  // 0x0330(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGSoundSplineComponent*                     mSoundSpline;                                             // 0x0338(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mSignificanceRange;                                       // 0x0340(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0344(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAmbientSoundSpline");
		return ptr;
	}


	class USplineComponent* GetSplineComponent();
};


// Class FactoryGame.FGAmbientVolume
// 0x0040 (0x03A0 - 0x0360)
class AFGAmbientVolume : public AVolume
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0360(0x0008) MISSED OFFSET
	class UClass*                                      mAmbientSettings;                                         // 0x0368(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class UAkComponent*                                mAudioComponent;                                          // 0x0370(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnTemplate, EditConst, InstancedReference, IsPlainOldData)
	float                                              mAdditionalAttenuationDistance;                           // 0x0378(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x037C(0x0020) MISSED OFFSET
	float                                              mSignificanceRange;                                       // 0x039C(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAmbientVolume");
		return ptr;
	}

};


// Class FactoryGame.FGAnimNotify_Attack
// 0x0000 (0x0038 - 0x0038)
class UFGAnimNotify_Attack : public UAnimNotify
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAnimNotify_Attack");
		return ptr;
	}

};


// Class FactoryGame.FGAnimNotify_FootDown
// 0x0008 (0x0040 - 0x0038)
class UFGAnimNotify_FootDown : public UAnimNotify
{
public:
	int                                                mFootIndex;                                               // 0x0038(0x0004) (Edit, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mPlaySound;                                               // 0x003C(0x0001) (Edit, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x003D(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAnimNotify_FootDown");
		return ptr;
	}

};


// Class FactoryGame.FGAnimNotify_Landed
// 0x0000 (0x0038 - 0x0038)
class UFGAnimNotify_Landed : public UAnimNotify
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAnimNotify_Landed");
		return ptr;
	}

};


// Class FactoryGame.FGCharacterAnimInstance
// 0x0120 (0x0480 - 0x0360)
class UFGCharacterAnimInstance : public UAnimInstance
{
public:
	struct FVector                                     mVelocity;                                                // 0x0360(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mVelocityLocalNormalized;                                 // 0x036C(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mAccelerationLocalNormalized;                             // 0x0378(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0384(0x000C) MISSED OFFSET
	struct FTransform                                  mActorTransform;                                          // 0x0390(0x0030) (BlueprintVisible, BlueprintReadOnly, IsPlainOldData)
	class AFGCharacterBase*                            mCachedCharacter;                                         // 0x03C0(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EMovementMode>                         mCachedMovementMode;                                      // 0x03C8(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EMovementMode>                         mCachedDefaultWalkMode;                                   // 0x03C9(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x03CA(0x0002) MISSED OFFSET
	float                                              mSpeed;                                                   // 0x03CC(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mSpeedLastFrame;                                          // 0x03D0(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mSpeedZ;                                                  // 0x03D4(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mWalkRotation;                                            // 0x03D8(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mIsStandingStill;                                         // 0x03DC(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mIsAccelerating;                                          // 0x03DD(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x03DE(0x0002) MISSED OFFSET
	float                                              mYawDelta;                                                // 0x03E0(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mAimYaw;                                                  // 0x03E4(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mAimYawInterpSpeed;                                       // 0x03E8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mRootRotation;                                            // 0x03EC(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mTurnInPlaceLeft;                                         // 0x03F8(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mTurnInPlaceRight;                                        // 0x03F9(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mTurnInPlaceComplete;                                     // 0x03FA(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x5];                                       // 0x03FB(0x0005) MISSED OFFSET
	class UCurveFloat*                                 mTurnLeftCurve;                                           // 0x0400(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UCurveFloat*                                 mTurnRightCurve;                                          // 0x0408(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mActorRotationForwardVector;                              // 0x0410(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mActorRotationForwardVectorReference;                     // 0x041C(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mAimYawReductionStartTime;                                // 0x0428(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mAimYawReductionCurrentTime;                              // 0x042C(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    mActorRotationLastTick;                                   // 0x0430(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mYawRotationStrength;                                     // 0x043C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mYawRotationInterpSpeed;                                  // 0x0440(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRootRotationInterpSpeed;                                 // 0x0444(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAllowedToTurn;                                           // 0x0448(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x0449(0x0007) MISSED OFFSET
	float                                              mTurnInPlaceDefaultTime;                                  // 0x0450(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUseTurnInPlace;                                          // 0x0454(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mCanUpdateActorRotationReference;                         // 0x0455(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData05[0x2];                                       // 0x0456(0x0002) MISSED OFFSET
	float                                              mYawAimMaxValue;                                          // 0x0458(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mYawAimMinValue;                                          // 0x045C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAimPitch;                                                // 0x0460(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              mAimPitchInterpSpeed;                                     // 0x0464(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mGetDeltaPitchRotation;                                   // 0x0468(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUsePreLand;                                              // 0x0469(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mPreLand;                                                 // 0x046A(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData06[0x1];                                       // 0x046B(0x0001) MISSED OFFSET
	float                                              mPreLandVelocityMultiplier;                               // 0x046C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<TEnumAsByte<ECollisionChannel>>             mPreLandCollisionChannels;                                // 0x0470(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCharacterAnimInstance");
		return ptr;
	}


	void OnRadialDamageTaken();
	void OnPointDamageTaken(const struct FVector& shootDIrection);
	void OnAnyDamageTaken();
	float GetVelocityDirection();
	struct FVector GetVelocity();
	struct FRotator GetDesiredWalkRotation();
	struct FRotator GetDesiredRunLeanRotation();
	class AFGCharacterBase* GetCachedCharacter();
	float GetAccelerationVectorLength();
};


// Class FactoryGame.FGAnimPlayer
// 0x0010 (0x0490 - 0x0480)
class UFGAnimPlayer : public UFGCharacterAnimInstance
{
public:
	bool                                               mIsFirstPerson;                                           // 0x0480(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EArmEquipment                                      mArmSlotType;                                             // 0x0481(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	EBackEquipment                                     mBacklotType;                                             // 0x0482(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x5];                                       // 0x0483(0x0005) MISSED OFFSET
	class AFGCharacterPlayer*                          mCharacter;                                               // 0x0488(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAnimPlayer");
		return ptr;
	}

};


// Class FactoryGame.FGAssetManager
// 0x0000 (0x03D8 - 0x03D8)
class UFGAssetManager : public UAssetManager
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAssetManager");
		return ptr;
	}

};


// Class FactoryGame.FGHologram
// 0x0088 (0x03B0 - 0x0328)
class AFGHologram : public AActor
{
public:
	TArray<class UClass*>                              mValidHitClasses;                                         // 0x0328(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, EditConst)
	class UClass*                                      mRecipe;                                                  // 0x0338(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                mLoopSound;                                               // 0x0340(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               mClearanceDetector;                                       // 0x0348(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0350(0x000C) MISSED OFFSET
	bool                                               mPlacementMaterial;                                       // 0x035C(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x035D(0x0003) MISSED OFFSET
	class UMaterialInstance*                           mValidPlacementMaterial;                                  // 0x0360(0x0008) (ZeroConstructor, IsPlainOldData)
	class UMaterialInstance*                           mInvalidPlacementMaterial;                                // 0x0368(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class AFGHologram*>                         mChildren;                                                // 0x0370(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0380(0x0008) MISSED OFFSET
	class APawn*                                       mConstructionInstigator;                                  // 0x0388(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mIsDisabled;                                              // 0x0390(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsChanged;                                               // 0x0391(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x16];                                      // 0x0392(0x0016) MISSED OFFSET
	int                                                mInitialScrollModeValue;                                  // 0x03A8(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x4];                                       // 0x03AC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHologram");
		return ptr;
	}


	void Server_SetSnapToGuideLines(bool IsEnabled);
	void OnRep_PlacementMaterial();
	void OnRep_InitialScrollModeValue();
	bool IsChanged();
	bool GetNoSnapMode();
	void GetConstructDisqualifiers(TArray<class UClass*>* out_constructResults);
	void Client_PlaySnapSound();
	bool CanConstruct();
	void AddValidHitClass(class UClass* hitClass);
};


// Class FactoryGame.FGBuildableHologram
// 0x0030 (0x03E0 - 0x03B0)
class AFGBuildableHologram : public AFGHologram
{
public:
	class UClass*                                      mBuildableClass;                                          // 0x03B0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mMaxPlacementFloorAngle;                                  // 0x03B8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x03BC(0x0004) MISSED OFFSET
	class UFGFactoryLegsComponent*                     mLegs;                                                    // 0x03C0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x03C8(0x0008) MISSED OFFSET
	class UBoxComponent*                               mClearanceBox;                                            // 0x03D0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x03D8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableHologram");
		return ptr;
	}


	void ReceiveConfigureComponents(class AFGBuildable* inBuildable);
	void ReceiveConfigureActor(class AFGBuildable* inBuildable);
};


// Class FactoryGame.FGFactoryHologram
// 0x0068 (0x0448 - 0x03E0)
class AFGFactoryHologram : public AFGBuildableHologram
{
public:
	class UStaticMeshComponent*                        mClearanceMeshComponent;                                  // 0x03E0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMesh*                                 mClearanceMesh;                                           // 0x03E8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          mClearanceMaterial;                                       // 0x03F0(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x50];                                      // 0x03F8(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFactoryHologram");
		return ptr;
	}

};


// Class FactoryGame.FGConveyorAttachmentHologram
// 0x0018 (0x0460 - 0x0448)
class AFGConveyorAttachmentHologram : public AFGFactoryHologram
{
public:
	float                                              mMaxValidTurnOffset;                                      // 0x0448(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxValidTurnAngle;                                       // 0x044C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGBuildableConveyorBelt*                    mSnappedConveyor;                                         // 0x0450(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0458(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorAttachmentHologram");
		return ptr;
	}

};


// Class FactoryGame.FGAttachmentSplitterHologram
// 0x0018 (0x0478 - 0x0460)
class AFGAttachmentSplitterHologram : public AFGConveyorAttachmentHologram
{
public:
	class AFGBuildableAttachmentSplitter*              mUpgradedSplitter;                                        // 0x0460(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UFGFactoryConnectionComponent*>       mSnappedConnectionComponents;                             // 0x0468(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttachmentSplitterHologram");
		return ptr;
	}

};


// Class FactoryGame.FGAttack
// 0x0028 (0x0050 - 0x0028)
class UFGAttack : public UObject
{
public:
	class UAnimMontage*                                mAttackMontage;                                           // 0x0028(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mStopsMovement;                                           // 0x0030(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0031(0x0003) MISSED OFFSET
	float                                              mAttackRange;                                             // 0x0034(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAttackActivationDistance;                                // 0x0038(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mDamage;                                                  // 0x003C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDamageType;                                              // 0x0040(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAttackAngle;                                             // 0x0048(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x004C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttack");
		return ptr;
	}


	bool GetStopsMovement(class UClass* inClass);
	class UClass* GetDamageType(class UClass* inClass);
	int GetDamage(class UClass* inClass);
	float GetAttackRange(class UClass* inClass);
	class UAnimMontage* GetAttackMontage(class UClass* inClass);
	float GetAttackAngle(class UClass* inClass);
	float GetAttackActivationDistance(class UClass* inClass);
};


// Class FactoryGame.FGAttackCustomRadial
// 0x0000 (0x0050 - 0x0050)
class UFGAttackCustomRadial : public UFGAttack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttackCustomRadial");
		return ptr;
	}

};


// Class FactoryGame.FGAttackMelee
// 0x0000 (0x0050 - 0x0050)
class UFGAttackMelee : public UFGAttack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttackMelee");
		return ptr;
	}

};


// Class FactoryGame.FGAttackMeleeJump
// 0x0018 (0x0068 - 0x0050)
class UFGAttackMeleeJump : public UFGAttackMelee
{
public:
	float                                              mJumpRange;                                               // 0x0050(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mJumpVelocity;                                            // 0x0054(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAnimMontage*                                mPreJumpMontage;                                          // 0x0060(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttackMeleeJump");
		return ptr;
	}


	class UAnimMontage* GetPreJumpMontage(class UClass* inClass);
	struct FVector GetJumpVelocity(class UClass* inClass);
	float GetJumpRange(class UClass* inClass);
};


// Class FactoryGame.FGAttackRanged
// 0x0008 (0x0058 - 0x0050)
class UFGAttackRanged : public UFGAttack
{
public:
	class UClass*                                      mProjectileClass;                                         // 0x0050(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttackRanged");
		return ptr;
	}


	void SpawnProjectile(class AActor* targetActor, class AFGEnemy* sourceActor);
};


// Class FactoryGame.FGAttentionPingActor
// 0x0008 (0x0330 - 0x0328)
class AFGAttentionPingActor : public AActor
{
public:
	int                                                mPlayerSlotIdx;                                           // 0x0328(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x032C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAttentionPingActor");
		return ptr;
	}


	void SpawnAttentionPingEffects();
	void OnRep_PlayerSlotIdx();
	int GetPlayerSlotIdx();
};


// Class FactoryGame.FGMessageBase
// 0x0058 (0x0260 - 0x0208)
class UFGMessageBase : public UUserWidget
{
public:
	struct FText                                       mTitle;                                                   // 0x0208(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	struct FText                                       mPreviewText;                                             // 0x0220(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	bool                                               mIsPopup;                                                 // 0x0238(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0239(0x0007) MISSED OFFSET
	class UClass*                                      mSenderClass;                                             // 0x0240(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EMessageType                                       mType;                                                    // 0x0248(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0249(0x0007) MISSED OFFSET
	TArray<class UTexture2D*>                          mImages;                                                  // 0x0250(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMessageBase");
		return ptr;
	}


	class UObject* GetMessageDefaultObject(class UClass* inClass);
};


// Class FactoryGame.FGAudioMessage
// 0x0068 (0x02C8 - 0x0260)
class UFGAudioMessage : public UFGMessageBase
{
public:
	class UAkComponent*                                mAkAudioComponent;                                        // 0x0260(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FAudioSubtitlePair>                  mAudioEvents;                                             // 0x0268(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0278(0x0008) MISSED OFFSET
	struct FAudioSubtitlePair                          mCurrentDialogue;                                         // 0x0280(0x0028)
	float                                              mSubtitleTimeMultiplier;                                  // 0x02A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x02AC(0x0004) MISSED OFFSET
	struct FScriptDelegate                             mAudioMessageConcluded;                                   // 0x02B0(0x0014) (ZeroConstructor, InstancedReference)
	class UInputComponent*                             mAudioMessageInputComponent;                              // 0x02C0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAudioMessage");
		return ptr;
	}


	void StartPlayback();
	void PlayNextDialogue();
	struct FAudioSubtitlePair GetCurrentDialogue();
	void ContinuePlayback();
	void CancelPlayback();
	void AssignOnConcludedDelegate(const struct FScriptDelegate& concludedDelegate);
};


// Class FactoryGame.FGAudioVolumeSubsystem
// 0x0000 (0x0328 - 0x0328)
class AFGAudioVolumeSubsystem : public AFGSubsystem
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGAudioVolumeSubsystem");
		return ptr;
	}

};


// Class FactoryGame.FGBaseUI
// 0x0020 (0x0228 - 0x0208)
class UFGBaseUI : public UUserWidget
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0208(0x0008) MISSED OFFSET
	class UFGPopupWidget*                              mActivePopup;                                             // 0x0210(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0218(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBaseUI");
		return ptr;
	}


	void SetPopup(class UFGPopupWidget* inPopup);
	void PopPopupQueue();
	class UFGPopupWidget* GetPopup();
	class UFGPopupWidget* CreatePopupWidget(const struct FPopupData& PopupData);
	void ClosePopup();
	void AddPopup(const struct FText& Title, const struct FText& Body, const struct FScriptDelegate& ConfirmClickDelegate, TEnumAsByte<EPopupId> PopupID, class UClass* PopupClass);
};


// Class FactoryGame.FGBeacon
// 0x0000 (0x0328 - 0x0328)
class AFGBeacon : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBeacon");
		return ptr;
	}

};


// Class FactoryGame.FGBlueprintFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBlueprintFunctionLibrary");
		return ptr;
	}


	void UpdateUseState(class UClass* newState, struct FUseState* State);
	void TravelToMainMenu(class APlayerController* PlayerController);
	void ShowOutline(class UPrimitiveComponent* comp, EOutlineColor Color);
	void RemoveGenericTickObjectFromSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void RemoveGainSignificanceObjectFromSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void RemoveFactoryObjectFromSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void RemoveConveyorBeltFromSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void RemoveAudioVolumeFromSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void RemoveAmbientSoundSplineFromSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	float LogX(float Base, float Value);
	class FString LinearColorToHex(const struct FLinearColor& inColor);
	bool IsLocationNearABase(class UObject* WorldContext, const struct FVector& InLocation, float closeDistance);
	bool IsLocallyHumanControlled(class APawn* Pawn);
	bool IsInAlwaysLoadedLevel(class AActor* Actor);
	bool IsGameWorld(class UObject* WorldContext);
	bool IsEditorWorld(class UObject* WorldContext);
	bool IsAlphaBuild();
	bool ImpactEffectIsWithinDistance(class UObject* WorldContext, class APawn* Instigator, const struct FVector& SpawnLocation, float visibleCullDistance);
	bool ImpactEffectIsRelevant(class UObject* WorldContext, class APawn* Instigator, const struct FVector& SpawnLocation, float visibleCullDistance, float alwaysSuccessDistance, bool skipLOSCheck);
	void HideOutline(class UPrimitiveComponent* comp);
	class FString GetVersionString();
	class AActor* GetOuterActor(class UObject* Obj);
	class FString GetLanguage();
	struct FName GetComponentFlagSoftLanding();
	void GetAvailableSubCategoriesForCategory(class UObject* WorldContext, class UClass* buildCategory, TArray<class UClass*>* out_subCategories);
	void GetAvailableRecipesInSubCategory(class UObject* WorldContext, class UClass* subCategory, TArray<class UClass*>* out_recipes);
	void GetAvailableRecipesInCategory(class UObject* WorldContext, class UClass* buildCategory, TArray<class UClass*>* out_recipes);
	void GetAllWidgetsOfClassInHierarchy(class UWidget* hierarchyContext, class UClass* WidgetClass, TArray<class UWidget*>* FoundWidgets);
	void GetAllDescriptorsSorted(class UObject* WorldContext, TArray<class UClass*>* out_descriptors);
	void GetAllBuildCategories(class UObject* WorldContext, TArray<class UClass*>* out_buildCategories);
	void CreateSessionAndTravelToMap(class APlayerController* Player, const class FString& mapName, const class FString& options, const class FString& SessionName, TEnumAsByte<ESessionVisibility> sessionVisibility);
	float CmS2KmH(float CmS);
	void ClosePopup(class APlayerController* Controller);
	void Cheat_GetAllDescriptors(TArray<class UClass*>* out_descriptors);
	void ChangeLanguage(const class FString& Target);
	bool CanBeOnConveyor(class UClass* inClass);
	void AddPopupWithCloseDelegate(class APlayerController* Controller, const struct FText& Title, const struct FText& Body, const struct FScriptDelegate& CloseDelegate, TEnumAsByte<EPopupId> PopupID, class UClass* PopupClass, class UObject* popupInstigator);
	void AddPopup(class APlayerController* Controller, const struct FText& Title, const struct FText& Body, const struct FScriptDelegate& ConfirmClickDelegate, TEnumAsByte<EPopupId> PopupID, class UClass* PopupClass, class UObject* popupInstigator);
	void AddGenericTickObjectToSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void AddGainSignificanceObjectToSignificanceManager(class UObject* WorldContextObject, class UObject* Obj, float desiredGainDistance);
	void AddFactoryObjectToSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void AddConveyorBeltToSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void AddAudioVolumeToSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
	void AddAmbientSoundSplineToSignificanceManager(class UObject* WorldContextObject, class UObject* Obj);
};


// Class FactoryGame.FGBoundedTextRenderComponent
// 0x0000 (0x05B0 - 0x05B0)
class UFGBoundedTextRenderComponent : public UTextRenderComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBoundedTextRenderComponent");
		return ptr;
	}


	void AssignBoundingBox(class UBoxComponent* BoxComponent);
};


// Class FactoryGame.FGBuildable
// 0x0240 (0x0568 - 0x0328)
class AFGBuildable : public AActor
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x0328(0x0020) MISSED OFFSET
	class UClass*                                      mHologramClass;                                           // 0x0348(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FText                                       mDisplayName;                                             // 0x0350(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	struct FText                                       mDescription;                                             // 0x0368(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	struct FFactoryTickFunction                        mFactoryTickFunction;                                     // 0x0380(0x0058) (Edit, DisableEditOnInstance)
	struct FLinearColor                                mPrimaryColor;                                            // 0x03D8(0x0010) (ZeroConstructor, SaveGame, IsPlainOldData)
	struct FLinearColor                                mSecondaryColor;                                          // 0x03E8(0x0010) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      mColorSlot;                                               // 0x03F8(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x03F9(0x0007) MISSED OFFSET
	class UClass*                                      mBuildEffectTemplate;                                     // 0x0400(0x0008) (ZeroConstructor, IsPlainOldData)
	class UClass*                                      mDismantleEffectTemplate;                                 // 0x0408(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0410(0x0008) MISSED OFFSET
	class AActor*                                      mBuildEffectInstignator;                                  // 0x0418(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	struct FSoftClassPath                              mDismantleEffectClassName;                                // 0x0420(0x0018) (ZeroConstructor, Config, NoClear)
	struct FSoftClassPath                              mBuildEffectClassName;                                    // 0x0438(0x0018) (ZeroConstructor, Config, NoClear)
	float                                              mBuildEffectSpeed;                                        // 0x0450(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mForceNetUpdateOnRegisterPlayer;                          // 0x0454(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x0455(0x0003) MISSED OFFSET
	struct FSoftClassPath                              mHighlightParticleClassName;                              // 0x0458(0x0018) (ZeroConstructor, Config, NoClear)
	class UParticleSystem*                             mHighlightParticleSystemTemplate;                         // 0x0470(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystemComponent*                    mHighlightParticleSystemComponent;                        // 0x0478(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mDidFirstTimeUse;                                         // 0x0480(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mShouldShowHighlight;                                     // 0x0481(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x1E];                                      // 0x0482(0x001E) MISSED OFFSET
	float                                              mCameraDistanceSq;                                        // 0x04A0(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                mBuildingID;                                              // 0x04A4(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	TArray<struct FItemAmount>                         mDismantleRefund;                                         // 0x04A8(0x0010) (ZeroConstructor, SaveGame)
	unsigned char                                      UnknownData05[0x10];                                      // 0x04B8(0x0010) MISSED OFFSET
	bool                                               mIsUseable;                                               // 0x04C8(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData06[0x7];                                       // 0x04C9(0x0007) MISSED OFFSET
	class UClass*                                      mInteractWidgetClass;                                     // 0x04D0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData07[0x8];                                       // 0x04D8(0x0008) MISSED OFFSET
	TArray<class AFGCharacterPlayer*>                  mInteractingPlayers;                                      // 0x04E0(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData08[0x8];                                       // 0x04F0(0x0008) MISSED OFFSET
	class UClass*                                      mBuiltWithRecipe;                                         // 0x04F8(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mBuildTimeStamp;                                          // 0x0500(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData09[0x4];                                       // 0x0504(0x0004) MISSED OFFSET
	class UShapeComponent*                             mCachedShapeComponent;                                    // 0x0508(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mHighlightLocation;                                       // 0x0510(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData10[0x50];                                      // 0x0518(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildable");
		return ptr;
	}


	void ShowHighlightEffect();
	void RemoveHighlightEffect();
	void ReapplyColorSlot();
	void PlayDismantleSound();
	void PlayDismantleEffects();
	void PlayConstructSound();
	void PlayBuildEffects(class AActor* inInstigator);
	void OnRep_SecondaryColor();
	void OnRep_PrimaryColor();
	void OnRep_DidFirstTimeUse();
	void OnRep_ColorSlot();
	unsigned char GetNumPowerConnections();
	TArray<class UMeshComponent*> GetMainMeshes();
	class UClass* GetInteractWidgetClass();
	void GetDismantleBlueprintReturns(TArray<struct FInventoryStack>* out_returns);
	class UShapeComponent* GetClearanceComponent();
	void Factory_ReceiveTick(float DeltaTime);
	bool Factory_PeekOutput(class UFGFactoryConnectionComponent* Connection, class UClass* Type, TArray<struct FInventoryItem>* out_items);
	bool Factory_GrabOutput(class UFGFactoryConnectionComponent* Connection, class UClass* Type, struct FInventoryItem* out_item, float* out_OffsetBeyond);
};


// Class FactoryGame.FGBuildableFactory
// 0x00E8 (0x0650 - 0x0568)
class AFGBuildableFactory : public AFGBuildable
{
public:
	unsigned char                                      UnknownData00[0x28];                                      // 0x0568(0x0028) MISSED OFFSET
	float                                              mPowerConsumption;                                        // 0x0590(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mPowerConsumptionExponent;                                // 0x0594(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mPowerInfoClass;                                          // 0x0598(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGPowerInfoComponent*                       mPowerInfo;                                               // 0x05A0(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	struct FScriptMulticastDelegate                    mOnHasPowerChanged;                                       // 0x05A8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnHasProductionChanged;                                  // 0x05B8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x4];                                       // 0x05C8(0x0004) MISSED OFFSET
	float                                              mMinimumProducingTime;                                    // 0x05CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMinimumStoppedTime;                                      // 0x05D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeSinceStartStopProducing;                             // 0x05D4(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                mNumCyclesForProductivity;                                // 0x05D8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x19];                                      // 0x05DC(0x0019) MISSED OFFSET
	bool                                               mCanChangePotential;                                      // 0x05F5(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x2];                                       // 0x05F6(0x0002) MISSED OFFSET
	float                                              mCurrentPotential;                                        // 0x05F8(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mPendingPotential;                                        // 0x05FC(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mMinPotential;                                            // 0x0600(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxPotential;                                            // 0x0604(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxPotentialIncreasePerCrystal;                          // 0x0608(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsProductionPaused;                                      // 0x060C(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData04[0x3];                                       // 0x060D(0x0003) MISSED OFFSET
	class AFGReplicationDetailActor*                   mReplicationDetailActor;                                  // 0x0610(0x0008) (Net, ZeroConstructor, Transient, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnReplicationDetailActorCreatedEvent;                     // 0x0618(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	class UFGInventoryComponent*                       mInventoryPotential;                                      // 0x0628(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData05[0x8];                                       // 0x0630(0x0008) MISSED OFFSET
	unsigned char                                      mCurrentProductivity;                                     // 0x0638(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      mIsProducing : 1;                                         // 0x0639(0x0001) (Net, SaveGame)
	unsigned char                                      UnknownData06 : 1;                                        // 0x0639(0x0001)
	unsigned char                                      mHasPower : 1;                                            // 0x0639(0x0001) (Net)
	unsigned char                                      UnknownData07[0x2];                                       // 0x063A(0x0002) MISSED OFFSET
	float                                              mSignificanceBias;                                        // 0x063C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mEffectUpdateInterval;                                    // 0x0640(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData08[0x4];                                       // 0x0644(0x0004) MISSED OFFSET
	bool                                               mAddToSignificanceManager;                                // 0x0648(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData09[0x7];                                       // 0x0649(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableFactory");
		return ptr;
	}


	void StopProductionLoopEffects();
	void StopIdlingLoopEffects();
	void StartProductionLoopEffects();
	void StartIdlingLoopEffects();
	void SetPendingPotential(float newPendingPotential);
	void SetIsProductionPaused(bool IsPaused);
	bool RunsOnPower();
	void ReceiveUpdateEffects(float DeltaSeconds);
	void OnRep_ReplicationDetailActor();
	void OnRep_IsProducing();
	void OnPotentialInventoryItemRemoved(class UClass* ItemClass, int numRemoved);
	void OnIsProducingChanged(bool newIsProducing);
	void OnHasPowerChanged(bool newHasPower);
	bool IsProductionPaused();
	bool IsProducing();
	bool IsConfigured();
	bool HasPower();
	float GetProductivity();
	float GetProductionProgress();
	EProductionStatus GetProductionIndicatorStatus();
	float GetProductionCycleTimeForRecipe(class UClass* Recipe);
	float GetProductionCycleTime();
	float GetProducingPowerConsumption();
	class UFGPowerInfoComponent* GetPowerInfo();
	class UFGInventoryComponent* GetPotentialInventory();
	float GetPendingPotential();
	float GetMinPotential();
	float GetMaxPossiblePotential();
	bool GetIsSignificant();
	float GetDefaultProductionCycleTime();
	float GetDefaultProducingPowerConsumption();
	float GetCurrentPotential();
	float GetCurrentMaxPotential();
	TArray<class UFGFactoryConnectionComponent*> GetConnectionComponents();
	bool GetCanChangePotential();
	void Factory_ReceiveTickProducing(float DeltaTime);
	void Factory_ReceiveStopProducing();
	void Factory_ReceiveStartProducing();
	void Factory_CollectInput();
	bool CanProduce();
	float CalcProductionCycleTimeForPotential(float potential);
	float CalcProducingPowerConsumptionForPotential(float potential);
};


// Class FactoryGame.FGBuildableConveyorAttachment
// 0x0000 (0x0650 - 0x0650)
class AFGBuildableConveyorAttachment : public AFGBuildableFactory
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableConveyorAttachment");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableAttachmentMerger
// 0x0028 (0x0678 - 0x0650)
class AFGBuildableAttachmentMerger : public AFGBuildableConveyorAttachment
{
public:
	int                                                mCurrentInputIndex;                                       // 0x0650(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x24];                                      // 0x0654(0x0024) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableAttachmentMerger");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableAttachmentSplitter
// 0x0038 (0x0688 - 0x0650)
class AFGBuildableAttachmentSplitter : public AFGBuildableConveyorAttachment
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x0650(0x0020) MISSED OFFSET
	int                                                mCurrentOutputIndex;                                      // 0x0670(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0674(0x0004) MISSED OFFSET
	TArray<struct FConnectionItemStruct>               mDistributionTable;                                       // 0x0678(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableAttachmentSplitter");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableManufacturer
// 0x0058 (0x06A8 - 0x0650)
class AFGBuildableManufacturer : public AFGBuildableFactory
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0650(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    mCurrentRecipeChanged;                                    // 0x0658(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mManufacturingSpeed;                                      // 0x0668(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCurrentManufacturingProgress;                            // 0x066C(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	class UFGInventoryComponent*                       mInputInventory;                                          // 0x0670(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0678(0x0010) MISSED OFFSET
	class UFGInventoryComponent*                       mOutputInventory;                                         // 0x0688(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x10];                                      // 0x0690(0x0010) MISSED OFFSET
	class UClass*                                      mCurrentRecipe;                                           // 0x06A0(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableManufacturer");
		return ptr;
	}


	void SetRecipe(class UClass* Recipe);
	void OnRep_CurrentRecipe();
	bool MoveOrDropOutputInventory(class AFGCharacterPlayer* Pawn);
	bool MoveOrDropInputInventory(class AFGCharacterPlayer* Pawn);
	class UFGInventoryComponent* GetOutputInventory();
	float GetManufacturingSpeed();
	class UFGInventoryComponent* GetInputInventory();
	class UClass* GetCurrentRecipe();
	void GetAvailableRecipes(TArray<class UClass*>* out_recipes);
};


// Class FactoryGame.FGBuildableAutomatedWorkBench
// 0x0008 (0x06B0 - 0x06A8)
class AFGBuildableAutomatedWorkBench : public AFGBuildableManufacturer
{
public:
	int                                                mInputInventorySize;                                      // 0x06A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x06AC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableAutomatedWorkBench");
		return ptr;
	}


	void SetManufacturingSpeed(float newManufacturingSpeed);
};


// Class FactoryGame.FGBuildableConverter
// 0x0008 (0x06B0 - 0x06A8)
class AFGBuildableConverter : public AFGBuildableManufacturer
{
public:
	int                                                mNumberOfIngredientsNeeded;                               // 0x06A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x06AC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableConverter");
		return ptr;
	}


	void SetupItemFilter();
	int GetNumberOfInputs();
	bool FilterIngredientClasses(class UClass* Object, int idx);
};


// Class FactoryGame.FGRemoteCallObject
// 0x0000 (0x0028 - 0x0028)
class UFGRemoteCallObject : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRemoteCallObject");
		return ptr;
	}


	class AFGGameState* GetGameState();
};


// Class FactoryGame.FGConveyorRemoteCallObject
// 0x0008 (0x0030 - 0x0028)
class UFGConveyorRemoteCallObject : public UFGRemoteCallObject
{
public:
	bool                                               mForceNetField_UFGConveyorRemoteCallObject;               // 0x0028(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0029(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorRemoteCallObject");
		return ptr;
	}


	void Server_OnUse(class AFGBuildableConveyorBelt* Target, class AFGCharacterPlayer* byCharacter, int ItemIndex, int8_t repVersion);
};


// Class FactoryGame.FGBuildableConveyorBase
// 0x0190 (0x06F8 - 0x0568)
class AFGBuildableConveyorBase : public AFGBuildable
{
public:
	float                                              mSpeed;                                                   // 0x0568(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x056C(0x0004) MISSED OFFSET
	struct FConveyorBeltItems                          mItems;                                                   // 0x0570(0x0170) (Net)
	class UFGFactoryConnectionComponent*               mConnection0;                                             // 0x06E0(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               mConnection1;                                             // 0x06E8(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x06F0(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableConveyorBase");
		return ptr;
	}

};


// Class FactoryGame.FGUseState
// 0x0008 (0x0030 - 0x0028)
class UFGUseState : public UObject
{
public:
	bool                                               mWantAdditonalData;                                       // 0x0028(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsUsableState;                                           // 0x0029(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x002A(0x0006) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_ConveyorBeltValid
// 0x0008 (0x0038 - 0x0030)
class UFGUseState_ConveyorBeltValid : public UFGUseState
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0030(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_ConveyorBeltValid");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_ConveyorBeltFullInventory
// 0x0008 (0x0038 - 0x0030)
class UFGUseState_ConveyorBeltFullInventory : public UFGUseState
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0030(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_ConveyorBeltFullInventory");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_ConveyorBeltEmpty
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_ConveyorBeltEmpty : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_ConveyorBeltEmpty");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableConveyorBelt
// 0x0088 (0x0780 - 0x06F8)
class AFGBuildableConveyorBelt : public AFGBuildableConveyorBase
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x06F8(0x0008) MISSED OFFSET
	TMap<struct FName, class UInstancedStaticMeshComponent*> mItemMeshMap;                                             // 0x0700(0x0050) (ExportObject, ZeroConstructor)
	TArray<struct FSplinePointData>                    mSplineData;                                              // 0x0750(0x0010) (Net, ZeroConstructor, SaveGame)
	class UFGSplineComponent*                          mSplineComponent;                                         // 0x0760(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGSoundSplineComponent*                     mSoundSplineComponent;                                    // 0x0768(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UAkAudioEvent*                               mSplineAudioEvent;                                        // 0x0770(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0778(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableConveyorBelt");
		return ptr;
	}


	void OnRep_SplineData();
	class UStaticMesh* GetSplineMesh();
	TArray<struct FSplinePointData> GetSplineData();
	class UFGSplineComponent* GetSplineComponent();
	bool GetIsSignificant();
};


// Class FactoryGame.FGBuildableConveyorLift
// 0x00C8 (0x07C0 - 0x06F8)
class AFGBuildableConveyorLift : public AFGBuildableConveyorBase
{
public:
	float                                              mMeshHeight;                                              // 0x06F8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x06FC(0x0004) MISSED OFFSET
	class UStaticMesh*                                 mBottomMesh;                                              // 0x0700(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mMidMesh;                                                 // 0x0708(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mTopMesh;                                                 // 0x0710(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mBellowMesh;                                              // 0x0718(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mJointMesh;                                               // 0x0720(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mShelfMesh;                                               // 0x0728(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FTransform                                  mTopTransform;                                            // 0x0730(0x0030) (Net, SaveGame, IsPlainOldData)
	bool                                               mIsReversed;                                              // 0x0760(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0761(0x0007) MISSED OFFSET
	TMap<struct FName, class UInstancedStaticMeshComponent*> mItemMeshMap;                                             // 0x0768(0x0050) (ExportObject, ZeroConstructor)
	unsigned char                                      UnknownData02[0x8];                                       // 0x07B8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableConveyorLift");
		return ptr;
	}


	void OnRep_TopTransform();
};


// Class FactoryGame.FGBuildableDecor
// 0x0008 (0x0570 - 0x0568)
class AFGBuildableDecor : public AFGBuildable
{
public:
	class UStaticMesh*                                 mDecorMesh;                                               // 0x0568(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableDecor");
		return ptr;
	}


	void SetDecorMesh(class UStaticMesh* Mesh);
	class UStaticMesh* GetDecorMesh();
};


// Class FactoryGame.FGBuildableDockingStation
// 0x0058 (0x06A8 - 0x0650)
class AFGBuildableDockingStation : public AFGBuildableFactory
{
public:
	int8_t                                             mStorageSizeX;                                            // 0x0650(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int8_t                                             mStorageSizeY;                                            // 0x0651(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0652(0x0002) MISSED OFFSET
	float                                              mTransferSpeed;                                           // 0x0654(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFuelTransferSpeed;                                       // 0x0658(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTransferProgress;                                        // 0x065C(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       mInventory;                                               // 0x0660(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	class UFGInventoryComponent*                       mFuelInventory;                                           // 0x0668(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x0670(0x0020) MISSED OFFSET
	class AActor*                                      mDockedActor;                                             // 0x0690(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      mHasDockedActor : 1;                                      // 0x0698(0x0001) (SaveGame)
	bool                                               mIsInLoadMode;                                            // 0x0699(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x069A(0x0002) MISSED OFFSET
	float                                              mStackTransferSize;                                       // 0x069C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsLoadUnloading;                                         // 0x06A0(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x06A1(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableDockingStation");
		return ptr;
	}


	void Undock();
	void SetIsInLoadMode(bool isInLoadMode);
	void OnTransferComplete();
	void OnRep_FuelInventory();
	void OnBeginUnloadVehicle();
	void OnBeginLoadVehicle();
	bool IsLoadUnloading();
	bool GetIsInLoadMode();
	class UFGInventoryComponent* GetInventory();
	class UFGInventoryComponent* GetFuelInventory();
	class AActor* GetDockedActor();
	bool FilterFuelClasses(class UClass* Object, int idx);
	bool Dock(class AActor* Actor);
};


// Class FactoryGame.FGBuildableFactoryBuilding
// 0x0008 (0x0570 - 0x0568)
class AFGBuildableFactoryBuilding : public AFGBuildable
{
public:
	class UFGColoredInstanceMeshProxy*                 mMeshComponentProxy;                                      // 0x0568(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableFactoryBuilding");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableFloor
// 0x0008 (0x0578 - 0x0570)
class AFGBuildableFloor : public AFGBuildableFactoryBuilding
{
public:
	float                                              mSize;                                                    // 0x0570(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0574(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableFloor");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableFoundation
// 0x0010 (0x0580 - 0x0570)
class AFGBuildableFoundation : public AFGBuildableFactoryBuilding
{
public:
	float                                              mSize;                                                    // 0x0570(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHeight;                                                  // 0x0574(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FFoundationSideSelectionFlags               mDisableSnapOn;                                           // 0x0578(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0579(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableFoundation");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableGenerator
// 0x0010 (0x0660 - 0x0650)
class AFGBuildableGenerator : public AFGBuildableFactory
{
public:
	float                                              mPowerProduction;                                         // 0x0650(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mPowerProductionExponent;                                 // 0x0654(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLoadPercentage;                                          // 0x0658(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mIsFuseTriggered;                                         // 0x065C(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x065D(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableGenerator");
		return ptr;
	}


	float IsFuseTriggered();
	float GetPowerProductionCapacity();
	float GetLoadPercentage();
	float GetDefaultPowerProductionCapacity();
	void Factory_TickPowerProduction(float dt);
	void Factory_StopPowerProduction();
	void Factory_StartPowerProduction();
	bool CanStartPowerProduction();
	float CalcPowerProductionCapacityForPotential(float potential);
};


// Class FactoryGame.FGBuildableGeneratorFuel
// 0x0060 (0x06C0 - 0x0660)
class AFGBuildableGeneratorFuel : public AFGBuildableGenerator
{
public:
	class UFGReplicationDetailInventoryComponent*      mFuelInventoryHandler;                                    // 0x0660(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<class UClass*>                              mFuelClasses;                                             // 0x0668(0x0010) (ZeroConstructor, Deprecated)
	TArray<TSoftObjectPtr<class UClass>>               mDefaultFuelClasses;                                      // 0x0678(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UClass*>                              mAvailableFuelClasses;                                    // 0x0688(0x0010) (Net, ZeroConstructor)
	class UFGInventoryComponent*                       mFuelInventory;                                           // 0x0698(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x06A0(0x0010) MISSED OFFSET
	float                                              mCurrentFuelAmount;                                       // 0x06B0(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mHasFuleCached;                                           // 0x06B4(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x06B5(0x0003) MISSED OFFSET
	class UClass*                                      mCurrentFuelClass;                                        // 0x06B8(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableGeneratorFuel");
		return ptr;
	}


	void OnRep_FuelInventory();
	bool IsValidFuel(class UClass* Resource);
	bool HasFuel();
	class UFGInventoryComponent* GetFuelInventory();
	float GetFuelAmount();
	bool FilterFuelClasses(class UClass* Object, int idx);
};


// Class FactoryGame.FGBuildableGeneratorGeoThermal
// 0x0008 (0x0668 - 0x0660)
class AFGBuildableGeneratorGeoThermal : public AFGBuildableGenerator
{
public:
	class AFGResourceNode*                             mExtractResourceNode;                                     // 0x0660(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableGeneratorGeoThermal");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableGeneratorNuclear
// 0x0008 (0x06C8 - 0x06C0)
class AFGBuildableGeneratorNuclear : public AFGBuildableGeneratorFuel
{
public:
	class UFGInventoryComponent*                       mOutputInventory;                                         // 0x06C0(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableGeneratorNuclear");
		return ptr;
	}


	class UFGInventoryComponent* GetWasteInventory();
};


// Class FactoryGame.FGBuildableHubTerminal
// 0x0008 (0x0570 - 0x0568)
class AFGBuildableHubTerminal : public AFGBuildable
{
public:
	class AFGBuildableTradingPost*                     mTradingPost;                                             // 0x0568(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableHubTerminal");
		return ptr;
	}


	class AFGBuildableTradingPost* GetTradingPost();
};


// Class FactoryGame.FGBuildablePole
// 0x0030 (0x0598 - 0x0568)
class AFGBuildablePole : public AFGBuildable
{
public:
	float                                              mHeight;                                                  // 0x0568(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mCanStack;                                                // 0x056C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x056D(0x0003) MISSED OFFSET
	float                                              mStackHeight;                                             // 0x0570(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0574(0x0004) MISSED OFFSET
	class UFGColoredInstanceMeshProxy*                 mPoleComponentProxy;                                      // 0x0578(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               mSnapOnly0;                                               // 0x0580(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UStaticMesh*                                 mPoleMesh;                                                // 0x0588(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mUseStaticHeight;                                         // 0x0590(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0591(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildablePole");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableWall
// 0x0008 (0x0578 - 0x0570)
class AFGBuildableWall : public AFGBuildableFactoryBuilding
{
public:
	float                                              mWidth;                                                   // 0x0570(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHeight;                                                  // 0x0574(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableWall");
		return ptr;
	}

};


// Class FactoryGame.FGBuildablePoweredWall
// 0x0000 (0x0578 - 0x0578)
class AFGBuildablePoweredWall : public AFGBuildableWall
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildablePoweredWall");
		return ptr;
	}


	class UFGPowerConnectionComponent* GetFoundationConnection();
};


// Class FactoryGame.FGBuildablePowerPole
// 0x0020 (0x0588 - 0x0568)
class AFGBuildablePowerPole : public AFGBuildable
{
public:
	class UWidgetComponent*                            mConnectionsWidget;                                       // 0x0568(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGPowerConnectionComponent*                 mPowerConnection;                                         // 0x0570(0x0008) (Edit, ExportObject, Net, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGColoredInstanceMeshProxy*                 mMeshComponentProxy;                                      // 0x0578(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	int                                                mCachedNumConnectionsToPole;                              // 0x0580(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0584(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildablePowerPole");
		return ptr;
	}


	class UFGPowerConnectionComponent* GetPowerConnection();
	class UFGPowerCircuit* GetPowerCircuit();
	int GetCachedNumConnections();
};


// Class FactoryGame.FGBuildableRadarTower
// 0x0038 (0x0688 - 0x0650)
class AFGBuildableRadarTower : public AFGBuildableFactory
{
public:
	struct FScriptMulticastDelegate                    OnRadarTowerRadiusExpanded;                               // 0x0650(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mMinRevealRadius;                                         // 0x0660(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxRevealRadius;                                         // 0x0664(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mNumRadarExpansionSteps;                                  // 0x0668(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRadarExpansionInterval;                                  // 0x066C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mCurrentExpansionStep;                                    // 0x0670(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0674(0x000C) MISSED OFFSET
	float                                              mTimeToNextExpansion;                                     // 0x0680(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0684(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRadarTower");
		return ptr;
	}


	void Multicast_ExpandRadarRadius();
	float GetTimeToNextExpansion();
	int GetNumRadarExpansionSteps();
	float GetMinRevealRadius();
	float GetMaxRevealRadius();
	float GetCurrentRevealRadius();
	int GetCurrentExpansionStep();
};


// Class FactoryGame.FGBuildableRailroadBridge
// 0x0018 (0x0580 - 0x0568)
class AFGBuildableRailroadBridge : public AFGBuildable
{
public:
	class UFGSplineComponent*                          mSplineComponent;                                         // 0x0568(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	TArray<struct FSplinePointData>                    mSplineData;                                              // 0x0570(0x0010) (Net, ZeroConstructor, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRailroadBridge");
		return ptr;
	}


	float GetLength();
};


// Class FactoryGame.FGBuildableRailroadSignal
// 0x0000 (0x0650 - 0x0650)
class AFGBuildableRailroadSignal : public AFGBuildableFactory
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRailroadSignal");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableTrainPlatform
// 0x0048 (0x0698 - 0x0650)
class AFGBuildableTrainPlatform : public AFGBuildableFactory
{
public:
	class AFGBuildableRailroadTrack*                   mRailroadTrack;                                           // 0x0650(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0658(0x0010) MISSED OFFSET
	class UFGTrainPlatformConnection*                  mPlatformConnection0;                                     // 0x0668(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGTrainPlatformConnection*                  mPlatformConnection1;                                     // 0x0670(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AFGRailroadVehicle*                          mDockedRailroadVehicle;                                   // 0x0678(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGBuildableRailroadStation*                 mStationDockingMaster;                                    // 0x0680(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsOrientationReversed;                                   // 0x0688(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	ETrainPlatformDockingStatus                        mPlatformDockingStatus;                                   // 0x0689(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	ETrainPlatformDockingStatus                        mSavedDockingStatus;                                      // 0x068A(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x5];                                       // 0x068B(0x0005) MISSED OFFSET
	struct FTimerHandle                                mDockingSequenceTimerHandle;                              // 0x0690(0x0008)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableTrainPlatform");
		return ptr;
	}


	void OnRep_UpdateDockingStatus();
	ETrainPlatformDockingStatus GetDockingStatus();
};


// Class FactoryGame.FGBuildableRailroadStation
// 0x0070 (0x0708 - 0x0698)
class AFGBuildableRailroadStation : public AFGBuildableTrainPlatform
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0698(0x0008) MISSED OFFSET
	class AFGTrainStationIdentifier*                   mStationIdentifier;                                       // 0x06A0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	EStationDockingStatus                              mStationDockingStatus;                                    // 0x06A8(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x06A8(0x0003) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
	unsigned char                                      UnknownData02[0x4];                                       // 0x06AC(0x0004) MISSED OFFSET
	TArray<class AFGBuildableTrainPlatform*>           mDockedPlatformList;                                      // 0x06B0(0x0010) (ZeroConstructor, SaveGame)
	unsigned char                                      UnknownData03[0x8];                                       // 0x06C0(0x0008) MISSED OFFSET
	TArray<TWeakObjectPtr<class AFGRailroadVehicle>>   mRelevantDockedVehicles;                                  // 0x06C8(0x0010) (ZeroConstructor)
	class UBoxComponent*                               mStationDockCollider;                                     // 0x06D8(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FTimerHandle                                mUpdateDockingStatusTimer;                                // 0x06E0(0x0008)
	class AFGLocomotive*                               mDockingLocomotive;                                       // 0x06E8(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mMaxDockSpeed;                                            // 0x06F0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxDockDistanceFromCenter;                               // 0x06F4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRailroadTrackPosition                      mTrackPosition;                                           // 0x06F8(0x0010) (SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRailroadStation");
		return ptr;
	}


	void PerformIsDockedCheck();
	void OnNameChanged();
	void OnLocomotiveDocked();
	void OnDockingColliderEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	void OnDockingColliderBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
	class AFGTrainStationIdentifier* GetStationIdentifier();
};


// Class FactoryGame.FGBuildableRailroadSwitchControl
// 0x0010 (0x0660 - 0x0650)
class AFGBuildableRailroadSwitchControl : public AFGBuildableFactory
{
public:
	class UFGRailroadTrackConnectionComponent*         mControlledConnection;                                    // 0x0650(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	int                                                mSwitchPosition;                                          // 0x0658(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x065C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRailroadSwitchControl");
		return ptr;
	}


	int GetSwitchPosition();
};


// Class FactoryGame.FGBuildableRailroadTrack
// 0x0058 (0x05C0 - 0x0568)
class AFGBuildableRailroadTrack : public AFGBuildable
{
public:
	class UStaticMesh*                                 mMesh;                                                    // 0x0568(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMeshLength;                                              // 0x0570(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0574(0x0004) MISSED OFFSET
	class USplineComponent*                            mSplineComponent;                                         // 0x0578(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGInstancedSplineMeshComponent*             mInstancedSplineComponent;                                // 0x0580(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	TArray<struct FSplinePointData>                    mSplineData;                                              // 0x0588(0x0010) (Net, ZeroConstructor, SaveGame)
	class UFGRailroadTrackConnectionComponent*         mConnections[0x2];                                        // 0x0598(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	bool                                               mIsOwnedByPlatform;                                       // 0x05A8(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x05A9(0x0007) MISSED OFFSET
	TArray<class UObject*>                             mRailroadInterfaces;                                      // 0x05B0(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRailroadTrack");
		return ptr;
	}


	class USplineComponent* GetSplineComponent();
	float GetLength();
};


// Class FactoryGame.FGBuildableRamp
// 0x0000 (0x0580 - 0x0580)
class AFGBuildableRamp : public AFGBuildableFoundation
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRamp");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableResourceExtractor
// 0x0040 (0x0690 - 0x0650)
class AFGBuildableResourceExtractor : public AFGBuildableFactory
{
public:
	float                                              mExtractStartupTime;                                      // 0x0650(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mExtractCycleTime;                                        // 0x0654(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<EResourceForm>                              mAllowedResourceForms;                                    // 0x0658(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	struct FVector                                     mExtractionOffset;                                        // 0x0668(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0674(0x0004) MISSED OFFSET
	class AFGResourceNode*                             mExtractResourceNode;                                     // 0x0678(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mCurrentExtractProgress;                                  // 0x0680(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0684(0x0004) MISSED OFFSET
	class UFGInventoryComponent*                       mOutputInventory;                                         // 0x0688(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableResourceExtractor");
		return ptr;
	}


	bool IsStartupComplete();
	class AFGResourceNode* GetResourceNode();
	class UFGInventoryComponent* GetOutputInventory();
	class UParticleSystem* GetMiningParticle();
};


// Class FactoryGame.FGBuildableRoad
// 0x0028 (0x0590 - 0x0568)
class AFGBuildableRoad : public AFGBuildable
{
public:
	class UFGRoadConnectionComponent*                  mConnection0;                                             // 0x0568(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGRoadConnectionComponent*                  mConnection1;                                             // 0x0570(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGSplineComponent*                          mSplineComponent;                                         // 0x0578(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	TArray<struct FSplinePointData>                    mSplineData;                                              // 0x0580(0x0010) (Net, ZeroConstructor, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableRoad");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableSignWall
// 0x0030 (0x05A8 - 0x0578)
class AFGBuildableSignWall : public AFGBuildableWall
{
public:
	class USceneComponent*                             mSignDisplayRoot;                                         // 0x0578(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mTextDisplayRoot;                                         // 0x0580(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UTextRenderComponent*                        mTextRenderComponent;                                     // 0x0588(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	struct FSignWallData                               mSignData;                                                // 0x0590(0x0018) (Net, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableSignWall");
		return ptr;
	}


	void SetSignData(const struct FSignWallData& SignData, bool bUpdate);
	void OnRep_SignData();
	struct FSignWallData GetSignData();
};


// Class FactoryGame.FGBuildableSpaceElevator
// 0x0020 (0x0670 - 0x0650)
class AFGBuildableSpaceElevator : public AFGBuildableFactory
{
public:
	class UFGInventoryComponent*                       mInputInventory;                                          // 0x0650(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	class AFGGamePhaseManager*                         mGamePhaseManager;                                        // 0x0658(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0660(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableSpaceElevator");
		return ptr;
	}


	void UpgradeTowTruck();
	void PayOffFromInventory(class UFGInventoryComponent* inventory, int inventorySlotIndex);
	void LaunchTowTruck();
	bool IsReadyToUpgrade();
	bool IsFullyUpgraded();
	void GetNextPhaseCost(TArray<struct FItemAmount>* out_cost);
	class UFGInventoryComponent* GetInputInventory();
};


// Class FactoryGame.FGBuildableSpeedSign
// 0x0000 (0x0568 - 0x0568)
class AFGBuildableSpeedSign : public AFGBuildable
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableSpeedSign");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableSplitterSmart
// 0x0028 (0x06B0 - 0x0688)
class AFGBuildableSplitterSmart : public AFGBuildableAttachmentSplitter
{
public:
	struct FScriptMulticastDelegate                    OnSortRulesChangedDelegate;                               // 0x0688(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<struct FSplitterSortRule>                   mSortRules;                                               // 0x0698(0x0010) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame)
	int                                                mMaxNumSortRules;                                         // 0x06A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x06AC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableSplitterSmart");
		return ptr;
	}


	void SetSortRuleAt(int Index, const struct FSplitterSortRule& Rule);
	void RemoveSortRuleAt(int Index);
	void OnRep_SortRules();
	bool IsValidSortRuleAt(int Index);
	struct FSplitterSortRule GetSortRuleAt(int Index);
	int GetNumSortRules();
	int GetMaxNumSortRules();
	void AddSortRule(const struct FSplitterSortRule& Rule);
};


// Class FactoryGame.FGBuildableStair
// 0x0000 (0x0580 - 0x0580)
class AFGBuildableStair : public AFGBuildableFoundation
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableStair");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableStandaloneSign
// 0x00C8 (0x0630 - 0x0568)
class AFGBuildableStandaloneSign : public AFGBuildable
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0568(0x0010) MISSED OFFSET
	TMap<int, class USceneComponent*>                  mDataToComponentMap;                                      // 0x0578(0x0050) (ExportObject, ZeroConstructor)
	class USceneComponent*                             mSignDisplayRoot;                                         // 0x05C8(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mTextDisplayRoot;                                         // 0x05D0(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UFGColoredInstanceMeshProxy*                 mMeshComponentProxy;                                      // 0x05D8(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               mBoundingBox;                                             // 0x05E0(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mHologramParticleComponent;                               // 0x05E8(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	float                                              mGainSignificanceDistance;                                // 0x05F0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x05F4(0x0004) MISSED OFFSET
	struct FSignData                                   mSignData;                                                // 0x05F8(0x0018) (Net, SaveGame)
	struct FSignElementConstraints                     mSignConstraints;                                         // 0x0610(0x0018) (Edit, DisableEditOnInstance)
	class UFont*                                       mSignFont;                                                // 0x0628(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableStandaloneSign");
		return ptr;
	}


	void OnRep_SignData();
	float GetTextScaleFromNormalizedValue(float Value);
	struct FSignElementConstraints GetSignConstraints();
	float GetCurrentNormalizedTextScale();
	float GetCurrentNormalizedTextOffsetZ();
};


// Class FactoryGame.FGBuildableStorage
// 0x0040 (0x0690 - 0x0650)
class AFGBuildableStorage : public AFGBuildableFactory
{
public:
	float                                              mStackingHeight;                                          // 0x0650(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0654(0x0004) MISSED OFFSET
	TArray<struct FItemAmount>                         mDefaultResources;                                        // 0x0658(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	int                                                mInventorySizeX;                                          // 0x0668(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mInventorySizeY;                                          // 0x066C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGInventoryComponent*                       mStorageInventory;                                        // 0x0670(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x18];                                      // 0x0678(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableStorage");
		return ptr;
	}


	class UFGInventoryComponent* GetStorageInventory();
};


// Class FactoryGame.FGBuildableSubsystem
// 0x0240 (0x0568 - 0x0328)
class AFGBuildableSubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	float                                              mDistanceConsideredClose;                                 // 0x0330(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mNumFactoriesNeededForCloseCheck;                         // 0x0334(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FScriptMulticastDelegate                    BuildableConstructedGlobalDelegate;                       // 0x0338(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<class AFGBuildable*>                        mBuildables;                                              // 0x0348(0x0010) (ZeroConstructor)
	TArray<struct FBuildableBucket>                    mBuildableBuckets;                                        // 0x0358(0x0010) (ZeroConstructor)
	class AActor*                                      mBuildableInstancesActor;                                 // 0x0368(0x0008) (ZeroConstructor, IsPlainOldData)
	TMap<class UStaticMesh*, class UProxyHierarchicalInstancedStaticMeshComponent*> mBuildableMeshInstances;                                  // 0x0370(0x0050) (ExportObject, ZeroConstructor)
	class UFGProductionIndicatorInstanceManager*       mProductionIndicatorInstanceManager;                      // 0x03C0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TMap<class UStaticMesh*, class UFGColoredInstanceManager*> mColoredInstances;                                        // 0x03C8(0x0050) (ExportObject, ZeroConstructor)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0418(0x0004) MISSED OFFSET
	struct FColor                                      mColorSlotsPrimary[0x10];                                 // 0x041C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	struct FColor                                      mColorSlotsSecondary[0x10];                               // 0x045C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1C];                                      // 0x049C(0x001C) MISSED OFFSET
	TArray<struct FDistanceBasedTickRate>              mDistanceBasedTickRate;                                   // 0x04B8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	bool                                               mFactoryOptimizationEnabled;                              // 0x04C8(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x04C9(0x0003) MISSED OFFSET
	float                                              mReplayEffecTimeDilation;                                 // 0x04CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mReplayEffectTimerDefault;                                // 0x04D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x14];                                      // 0x04D4(0x0014) MISSED OFFSET
	class UMaterial*                                   mDefaultFactoryMaterial;                                  // 0x04E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData05[0x20];                                      // 0x04F0(0x0020) MISSED OFFSET
	struct FFactoryTickFunction                        mFactoryTickFunction;                                     // 0x0510(0x0058) (Edit, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableSubsystem");
		return ptr;
	}


	void setColorSlotSecondary(unsigned char Index, const struct FColor& Color);
	void setColorSlotPrimary(unsigned char Index, const struct FColor& Color);
	void ReplayBuildingEffects();
	void GetTypedBuildable(class UClass* inClass, TArray<class AFGBuildable*>* out_buildables);
	struct FLinearColor getColorSlotSecondaryLinear(unsigned char Index);
	struct FColor getColorSlotSecondary(unsigned char Index);
	struct FLinearColor getColorSlotPrimaryLinear(unsigned char Index);
	struct FColor getColorSlotPrimary(unsigned char Index);
	class AFGBuildableSubsystem* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGBuildableTradingPost
// 0x00E0 (0x0730 - 0x0650)
class AFGBuildableTradingPost : public AFGBuildableFactory
{
public:
	class UClass*                                      mDefaultGeneratorRecipe;                                  // 0x0650(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class AFGBuildableGenerator*>               mGenerators;                                              // 0x0658(0x0010) (Net, ZeroConstructor, SaveGame)
	class UClass*                                      mDefaultStorageRecipe;                                    // 0x0668(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDefaultMAMRecipe;                                        // 0x0670(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDefaultHubTerminalRecipe;                                // 0x0678(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDefaultWorkBenchRecipe;                                  // 0x0680(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGBuildable*                                mStorage;                                                 // 0x0688(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGBuildable*                                mMAM;                                                     // 0x0690(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGBuildableHubTerminal*                     mHubTerminal;                                             // 0x0698(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGBuildable*                                mWorkBench;                                               // 0x06A0(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	TArray<int>                                        mGeneratorVisibilityLevels;                               // 0x06A8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	int                                                mStorageInventorySize;                                    // 0x06B8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mStorageVisibilityLevel;                                  // 0x06BC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMAMVisibilityLevel;                                      // 0x06C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x06C4(0x0004) MISSED OFFSET
	class UFGInventoryComponent*                       mInputInventory;                                          // 0x06C8(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	float                                              mSpawningGroundZOffset;                                   // 0x06D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mGroundSearchZDistance;                                   // 0x06D4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGSchematicManager*                         mSchematicManager;                                        // 0x06D8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UFGInventoryComponent*                       mStorageInventory;                                        // 0x06E0(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	TArray<struct FItemAmount>                         mDefaultResources;                                        // 0x06E8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class USceneComponent*                             mGenerator1Location;                                      // 0x06F8(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mGenerator2Location;                                      // 0x0700(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mStorageLocation;                                         // 0x0708(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mMAMLocation;                                             // 0x0710(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mHubTerminalLocation;                                     // 0x0718(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mWorkBenchLocation;                                       // 0x0720(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mNeedPlayingBuildEffectNotification;                      // 0x0728(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0729(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableTradingPost");
		return ptr;
	}


	void UpdateStorageVisibility();
	void UpdateMAMVisibility();
	void UpdateGeneratorVisibility();
	void OnTradingPostUpgraded(int Level, bool suppressBuildEffects);
	void OnRep_NeedPlayingBuildEffect();
	int GetTradingPostLevel();
	class UFGInventoryComponent* GetStorageInventory();
	bool AreChildBuildingsLoaded();
};


// Class FactoryGame.FGBuildableTrainPlatformCargo
// 0x0080 (0x0718 - 0x0698)
class AFGBuildableTrainPlatformCargo : public AFGBuildableTrainPlatform
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0698(0x0008) MISSED OFFSET
	int8_t                                             mStorageSizeX;                                            // 0x06A0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int8_t                                             mStorageSizeY;                                            // 0x06A1(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x06A2(0x0006) MISSED OFFSET
	class USkeletalMeshComponent*                      mMagicBoxSkelMeshComponent;                               // 0x06A8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        mCargoMeshComponent;                                      // 0x06B0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x06B8(0x0008) MISSED OFFSET
	bool                                               mIsFullUnload;                                            // 0x06C0(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData)
	bool                                               mIsFullLoad;                                              // 0x06C1(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x2];                                       // 0x06C2(0x0002) MISSED OFFSET
	float                                              mTimeToCompleteLoad;                                      // 0x06C4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeToSwapLoadVisibility;                                // 0x06C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeToCompleteUnload;                                    // 0x06CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeToSwapUnloadVisibility;                              // 0x06D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x14];                                      // 0x06D4(0x0014) MISSED OFFSET
	class UFGInventoryComponent*                       mInventory;                                               // 0x06E8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      mHasDockedActor : 1;                                      // 0x06F0(0x0001) (SaveGame)
	bool                                               mIsInLoadMode;                                            // 0x06F1(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsLoadUnloading;                                         // 0x06F2(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mShouldExecuteLoadOrUnload;                               // 0x06F3(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData05[0x4];                                       // 0x06F4(0x0004) MISSED OFFSET
	struct FTimerHandle                                mSwapCargoVisibilityTimerHandle;                          // 0x06F8(0x0008)
	unsigned char                                      UnknownData06[0x8];                                       // 0x0700(0x0008) MISSED OFFSET
	struct FRailroadTrackPosition                      mTrackPosition;                                           // 0x0708(0x0010) (SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableTrainPlatformCargo");
		return ptr;
	}


	void Undock();
	void SetIsInLoadMode(bool isInLoadMode);
	void OnTransferComplete();
	void OnCargoPowerStateChanged(bool HasPower);
	void OnBeginUnloadSequence();
	void OnBeginLoadSequence();
	bool IsLoadUnloading();
	bool GetIsInLoadMode();
	class UFGInventoryComponent* GetInventory();
	float GetDockedVehicleOffset();
	class AFGRailroadVehicle* GetDockedActor();
	bool Dock(class AFGRailroadVehicle* Actor);
};


// Class FactoryGame.FGBuildableTrainPlatformEmpty
// 0x0000 (0x0698 - 0x0698)
class AFGBuildableTrainPlatformEmpty : public AFGBuildableTrainPlatform
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableTrainPlatformEmpty");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableWalkway
// 0x0010 (0x0580 - 0x0570)
class AFGBuildableWalkway : public AFGBuildableFactoryBuilding
{
public:
	float                                              mSize;                                                    // 0x0570(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mElevation;                                               // 0x0574(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FFoundationSideSelectionFlags               mDisableSnapOn;                                           // 0x0578(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0579(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableWalkway");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableWindTurbine
// 0x0000 (0x0650 - 0x0650)
class AFGBuildableWindTurbine : public AFGBuildableFactory
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableWindTurbine");
		return ptr;
	}

};


// Class FactoryGame.FGBuildableWire
// 0x0038 (0x05A0 - 0x0568)
class AFGBuildableWire : public AFGBuildable
{
public:
	float                                              mMaxLength;                                               // 0x0568(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLengthPerCost;                                           // 0x056C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMeshComponent*                        mWireMesh;                                                // 0x0570(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	TWeakObjectPtr<class UFGCircuitConnectionComponent> mConnections[0x2];                                        // 0x0578(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     mLocations[0x2];                                          // 0x0588(0x000C) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildableWire");
		return ptr;
	}


	float GetLength();
	class UFGCircuitConnectionComponent* GetConnection(int Index);
};


// Class FactoryGame.FGBuildCategory
// 0x00A0 (0x00C8 - 0x0028)
class UFGBuildCategory : public UObject
{
public:
	struct FText                                       mDisplayName;                                             // 0x0028(0x0028) (Edit, DisableEditOnInstance)
	struct FSlateBrush                                 mCategoryIcon;                                            // 0x0040(0x0088) (Edit, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildCategory");
		return ptr;
	}


	struct FText GetCategoryName(class UClass* inClass);
	struct FSlateBrush GetCategoryIcon(class UClass* inClass);
};


// Class FactoryGame.FGItemDescriptor
// 0x0100 (0x0128 - 0x0028)
class UFGItemDescriptor : public UObject
{
public:
	bool                                               mUseDisplayNameAndDescription;                            // 0x0028(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0029(0x0007) MISSED OFFSET
	struct FText                                       mDisplayName;                                             // 0x0030(0x0028) (Edit, DisableEditOnInstance)
	struct FText                                       mDescription;                                             // 0x0048(0x0028) (Edit, DisableEditOnInstance)
	EStackSize                                         mStackSize;                                               // 0x0060(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mCanBeDiscarded;                                          // 0x0061(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0062(0x0002) MISSED OFFSET
	float                                              mEnergyValue;                                             // 0x0064(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRadioactiveDecay;                                        // 0x0068(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EResourceForm                                      mForm;                                                    // 0x006C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x006D(0x0003) MISSED OFFSET
	struct FSlateBrush                                 mInventoryIcon;                                           // 0x0070(0x0088)
	class UTexture2D*                                  mSmallIcon;                                               // 0x00F8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mPersistentBigIcon;                                       // 0x0100(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mConveyorMesh;                                            // 0x0108(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FItemView                                   mPreviewView;                                             // 0x0110(0x0014) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData03[0x4];                                       // 0x0124(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGItemDescriptor");
		return ptr;
	}


	int GetStackSize(class UClass* inClass);
	class UTexture2D* GetSmallIcon(class UClass* inClass);
	float GetRadioactiveDecay(class UClass* inClass);
	void GetPreviewView(class UClass* inClass, struct FItemView* out_previewView);
	struct FText GetItemName(class UClass* inClass);
	class UStaticMesh* GetItemMesh(class UClass* inClass);
	struct FSlateBrush GetItemIcon(class UClass* inClass);
	struct FText GetItemDescription(class UClass* inClass);
	void GetIconView(class UClass* inClass, struct FItemView* out_itemView);
	EResourceForm GetForm(class UClass* inClass);
	float GetEnergyValue(class UClass* inClass);
	class UTexture2D* GetBigIcon(class UClass* inClass);
	bool CanBeDiscarded(class UClass* inClass);
};


// Class FactoryGame.FGBuildDescriptor
// 0x0020 (0x0148 - 0x0128)
class UFGBuildDescriptor : public UFGItemDescriptor
{
public:
	class UClass*                                      mBuildCategory;                                           // 0x0128(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UClass*>                              mSubCategories;                                           // 0x0130(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mBuildMenuPriority;                                       // 0x0140(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0144(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildDescriptor");
		return ptr;
	}


	void GetSubCategories(class UClass* inClass, TArray<class UClass*>* out_subCategories);
	float GetBuildMenuPriority(class UClass* inClass);
	class UClass* GetBuildCategory(class UClass* inClass);
};


// Class FactoryGame.FGBuildGuide
// 0x0018 (0x0340 - 0x0328)
class AFGBuildGuide : public AActor
{
public:
	EGuideLineType                                     mGuideLineType;                                           // 0x0328(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x17];                                      // 0x0329(0x0017) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildGuide");
		return ptr;
	}


	void SetBuildGuideStartEnd(const struct FVector& startPoint, const struct FVector& endPoint, float meshSize);
};


// Class FactoryGame.FGBuildGunState
// 0x0028 (0x0050 - 0x0028)
class UFGBuildGunState : public UObject
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0028(0x0004) MISSED OFFSET
	float                                              mActionDelay;                                             // 0x002C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0030(0x0008) MISSED OFFSET
	struct FText                                       mActionMessage;                                           // 0x0038(0x0028) (Edit, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildGunState");
		return ptr;
	}


	void TickState(float DeltaTime);
	void SecondaryFire();
	void ScrollUp();
	void ScrollDown();
	void ResetBuildGunDelay();
	void PrimaryFire();
	bool IsActive();
	bool HasBuildGunDelay();
	bool HasAuthority();
	float GetBuildGunDelayPercentage();
	struct FText GetBuildGunDelayMessage();
	class AFGBuildGun* GetBuildGun();
	void EndState();
	void ChangeScrollMode();
	void ChangeNoSnapMode();
	void ChangeGuideLinesSnapMode(bool Enabled);
	bool BuildGunDelayIsComplete();
	void BeginState();
	void BeginBuildGunDelay();
};


// Class FactoryGame.FGEquipment
// 0x0098 (0x03C0 - 0x0328)
class AFGEquipment : public AActor
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
	class UClass*                                      mAttachmentClass;                                         // 0x0338(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mSecondaryAttachmentClass;                                // 0x0340(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EEquipmentSlot                                     mEquipmentSlot;                                           // 0x0348(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0349(0x0007) MISSED OFFSET
	class UClass*                                      mSprintHeadBobShake;                                      // 0x0350(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mEquipSound;                                              // 0x0358(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mUnequipSound;                                            // 0x0360(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mEquipmentWidget;                                         // 0x0368(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGEquipmentChild*                           mChildEquipment;                                          // 0x0370(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class UClass*                                      m1PAnimClass;                                             // 0x0378(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mAttachSocket;                                            // 0x0380(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mChildEquipmentClass;                                     // 0x0388(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FItemAmount>                         mCostToUse;                                               // 0x0390(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	EArmEquipment                                      mArmAnimation;                                            // 0x03A0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EBackEquipment                                     mBackAnimation;                                           // 0x03A1(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasPersistentOwner;                                      // 0x03A2(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x5];                                       // 0x03A3(0x0005) MISSED OFFSET
	class AFGEquipmentAttachment*                      mAttachment;                                              // 0x03A8(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGEquipmentAttachment*                      mSecondaryAttachment;                                     // 0x03B0(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x03B8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEquipment");
		return ptr;
	}


	void WasUnEquipped();
	void WasEquipped();
	void UnEquip();
	bool ShouldShowStinger();
	void Server_UpdateAttachmentUseState(int newUseState);
	void Server_ChargeForUse();
	bool IsLocalInstigator();
	bool IsEquipped();
	class AFGEquipmentAttachment* GetSecondaryAttachment();
	class AFGCharacterPlayer* GetInstigatorCharacter();
	EEquipmentSlot GetEquipmentSlot(class UClass* inClass);
	class AFGEquipmentAttachment* GetAttachment();
	void Equip(class AFGCharacterPlayer* Character);
	void DidNotAffordUse();
	void ChargeForUse();
	bool CanAffordUse();
	float AdjustDamage(float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
};


// Class FactoryGame.FGBuildGun
// 0x0110 (0x04D0 - 0x03C0)
class AFGBuildGun : public AFGEquipment
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x03C0(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnStateChanged;                                          // 0x03C8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnRecipeChanged;                                         // 0x03D8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mBuildDistanceMax;                                        // 0x03E8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03EC(0x0004) MISSED OFFSET
	class UClass*                                      mMenuStateClass;                                          // 0x03F0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mBuildStateClass;                                         // 0x03F8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDismantleStateClass;                                     // 0x0400(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGBuildGunState*                            mStates[0x4];                                             // 0x0408(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0428(0x0008) MISSED OFFSET
	struct FHitResult                                  mHitResult;                                               // 0x0430(0x0088) (IsPlainOldData)
	EBuildGunState                                     mCurrentStateEnum;                                        // 0x04B8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x04B9(0x0007) MISSED OFFSET
	class UFGBuildGunState*                            mCurrentState;                                            // 0x04C0(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x8];                                       // 0x04C8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildGun");
		return ptr;
	}


	void Server_SecondaryFire();
	void Server_ScrollUp();
	void Server_ScrollMode();
	void Server_ScrollDown();
	void Server_PrimaryFire();
	void Server_NoSnapMode();
	void Server_GotoState(EBuildGunState State);
	void Server_GotoBuildState(class UClass* Recipe);
	bool IsInState(EBuildGunState inState);
	void GotoMenuState();
	void GotoDismantleState();
	void GotoBuildState(class UClass* Recipe);
	class UFGInventoryComponent* GetInventory();
	float GetCurrentBuildGunDelayPercentage();
	struct FText GetCurrentBuildGunDelayMessage();
	TArray<struct FItemAmount> GetCostForRecipe(class UClass* Recipe);
	class UFGBuildGunState* GetBuildGunStateFor(EBuildGunState gunState);
	void GetAvailableRecipes(TArray<class UClass*>* out_recipes);
	bool CompareActiveRecipeTo(class UClass* Recipe);
};


// Class FactoryGame.FGEquipmentAttachment
// 0x0038 (0x0360 - 0x0328)
class AFGEquipmentAttachment : public AActor
{
public:
	class UClass*                                      mEquipmentClass;                                          // 0x0328(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mUseLocation;                                             // 0x0330(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
	struct FName                                       mAttachSocket;                                            // 0x0340(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EArmEquipment                                      mArmAnimation;                                            // 0x0348(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EBackEquipment                                     mBackAnimation;                                           // 0x0349(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x034A(0x0006) MISSED OFFSET
	class AFGCharacterPlayer*                          mAttachedTo;                                              // 0x0350(0x0008) (ZeroConstructor, IsPlainOldData)
	EEquipmentSlot                                     mEquipmentSlot;                                           // 0x0358(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0359(0x0003) MISSED OFFSET
	int                                                mAnimationState;                                          // 0x035C(0x0004) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEquipmentAttachment");
		return ptr;
	}


	void PlayUseEffect(const struct FVector& UseLocation);
	void PlayDetachEffects3P();
	void PlayAttachEffects3P();
	void OnRep_UseLocationUpdated();
	void OnRep_OnAnimationStateUpdated();
	void OnDetach();
	void OnAttachmentUseStateUpdated(int newUseState);
	void OnAttach();
	bool IsAttached();
	EEquipmentSlot GetEquippedSlot();
	struct FName GetAttachSocket();
	class AFGCharacterPlayer* GetAttachedTo();
};


// Class FactoryGame.FGBuildGunAttachment
// 0x0000 (0x0360 - 0x0360)
class AFGBuildGunAttachment : public AFGEquipmentAttachment
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildGunAttachment");
		return ptr;
	}

};


// Class FactoryGame.FGBuildGunStateBuild
// 0x0058 (0x00A8 - 0x0050)
class UFGBuildGunStateBuild : public UFGBuildGunState
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0050(0x0018) MISSED OFFSET
	class UClass*                                      mPendingRecipe;                                           // 0x0068(0x0008) (ZeroConstructor, IsPlainOldData)
	class UClass*                                      mActiveRecipe;                                            // 0x0070(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0078(0x0008) MISSED OFFSET
	class AFGHologram*                                 mHologram;                                                // 0x0080(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AActor*                                      mUpgradedActor;                                           // 0x0088(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	TArray<struct FFactoryClearanceData>               mProximateClearances;                                     // 0x0090(0x0010) (ZeroConstructor)
	class UBoxComponent*                               mClearanceDetector;                                       // 0x00A0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildGunStateBuild");
		return ptr;
	}


	void ResetHologram();
	void OnResetHologram();
	void OnRep_Hologram();
	void OnMultiStepPlacement(bool isFinalStep);
	void OnActiveDescriptorChanged();
	TArray<struct FItemAmount> GetHologramCost();
	class AFGHologram* GetHologram();
	class UClass* GetDescriptor();
	void EndClearanceOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	void Client_OnResetHologram();
	void Client_OnBuildableConstructed(class UClass* Desc);
	void BeginClearanceOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
};


// Class FactoryGame.FGBuildGunStateDismantle
// 0x0030 (0x0080 - 0x0050)
class UFGBuildGunStateDismantle : public UFGBuildGunState
{
public:
	struct FScriptMulticastDelegate                    OnPeekRefundsChanged;                                     // 0x0050(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	class AActor*                                      mSelectedActor;                                           // 0x0060(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FDismantleRefunds                           mPeekDismantleRefund;                                     // 0x0068(0x0018) (Net, Transient)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildGunStateDismantle");
		return ptr;
	}


	void Server_PeekAtDismantleRefund(class AActor* selected);
	void Server_DismantleActor(class AActor* actorToDismantle);
	void OnStopDismantle();
	void OnStartDismantle();
	void OnRep_PeekDismantleRefund();
	class AActor* GetSelectedActor();
	TArray<struct FInventoryStack> GetPeekDismantleRefund();
	TArray<struct FInventoryStack> GetDismantleRefund();
	bool CanDismantle();
};


// Class FactoryGame.FGBuildingDescriptor
// 0x0008 (0x0150 - 0x0148)
class UFGBuildingDescriptor : public UFGBuildDescriptor
{
public:
	class UClass*                                      mBuildableClass;                                          // 0x0148(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildingDescriptor");
		return ptr;
	}


	float GetPowerProduction(class UClass* inClass);
	float GetPowerConsumption(class UClass* inClass);
	class UClass* GetBuildableClass(class UClass* inClass);
};


// Class FactoryGame.FGBuildSubCategory
// 0x0000 (0x00C8 - 0x00C8)
class UFGBuildSubCategory : public UFGBuildCategory
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGBuildSubCategory");
		return ptr;
	}

};


// Class FactoryGame.FGButtonWidget
// 0x0008 (0x0210 - 0x0208)
class UFGButtonWidget : public UUserWidget
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0208(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGButtonWidget");
		return ptr;
	}


	void SetButton(class UButton* inButton);
};


// Class FactoryGame.FGWeapon
// 0x0050 (0x0410 - 0x03C0)
class AFGWeapon : public AFGEquipment
{
public:
	class AFGHUD*                                      mAssosiatedHud;                                           // 0x03C0(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x03C8(0x0010) MISSED OFFSET
	int                                                mMagSize;                                                 // 0x03D8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mCurrentAmmo;                                             // 0x03DC(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class UClass*                                      mAmmunitionClass;                                         // 0x03E0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDamageTypeClass;                                         // 0x03E8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mReloadTime;                                              // 0x03F0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFireRate;                                                // 0x03F4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsFiring;                                                // 0x03F8(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mIsPendingFire;                                           // 0x03F9(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mIsReloading;                                             // 0x03FA(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x5];                                       // 0x03FB(0x0005) MISSED OFFSET
	class UAkAudioEvent*                               mReloadSound;                                             // 0x0400(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0408(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWeapon");
		return ptr;
	}


	void Server_StartPrimaryFire();
	void Server_Reload();
	void Server_EndPrimaryFire();
	void PlayReloadEffects();
	void PlayFireReleasedEffects();
	void PlayFireEffect();
	void PlayFailedToFireEffects();
	bool HasAmmunition();
	int GetSpareAmmunition();
	float GetReloadTimeLeft();
	int GetMagSize();
	bool GetIsReloading();
	bool GetIsFiring();
	int GetCurrentAmmo();
	class AFGHUD* GetAssosiatedHud();
	void FireAmmunition();
	bool CanReload();
	void ActualReload();
};


// Class FactoryGame.FGC4Dispenser
// 0x0038 (0x0448 - 0x0410)
class AFGC4Dispenser : public AFGWeapon
{
public:
	class UClass*                                      mC4ExplosiveClass;                                        // 0x0410(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class AFGC4Explosive*>                      mDispensedExplosives;                                     // 0x0418(0x0010) (ZeroConstructor, SaveGame)
	float                                              mMaxChargeTime;                                           // 0x0428(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMaxThrowForce;                                           // 0x042C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDelayBetweenExplosions;                                  // 0x0430(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x14];                                      // 0x0434(0x0014) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGC4Dispenser");
		return ptr;
	}


	void Server_SpawnC4(int throwForce);
	void Server_DetonatePressed();
	float GetChargePct();
};


// Class FactoryGame.FGC4Explosive
// 0x0018 (0x0340 - 0x0328)
class AFGC4Explosive : public AActor
{
public:
	float                                              mBaseDamage;                                              // 0x0328(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDamageRadius;                                            // 0x032C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDamageType;                                              // 0x0330(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsDetonated;                                             // 0x0338(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0339(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGC4Explosive");
		return ptr;
	}


	void PlayExplosionEffects();
	void OnRep_IsDetonated();
};


// Class FactoryGame.FGCameraModifierLimitLook
// 0x0018 (0x0060 - 0x0048)
class UFGCameraModifierLimitLook : public UCameraModifier
{
public:
	unsigned char                                      UnknownData00[0xC];                                       // 0x0048(0x000C) MISSED OFFSET
	float                                              mMaxPitch;                                                // 0x0054(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxYaw;                                                  // 0x0058(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x005C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCameraModifierLimitLook");
		return ptr;
	}


	void SetDefaultLookRotator(const struct FRotator& inRotator);
	struct FRotator GetDefaultLookRotator();
};


// Class FactoryGame.FGCentralStorageContainer
// 0x0000 (0x0690 - 0x0690)
class AFGCentralStorageContainer : public AFGBuildableStorage
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCentralStorageContainer");
		return ptr;
	}


	void AddToCentralStorageSubsystem();
};


// Class FactoryGame.FGCentralStorageSubsystem
// 0x0020 (0x0348 - 0x0328)
class AFGCentralStorageSubsystem : public AFGSubsystem
{
public:
	struct FScriptMulticastDelegate                    CentralStorageAddedOrRemoved;                             // 0x0328(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<class AFGCentralStorageContainer*>          mCentralStorages;                                         // 0x0338(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCentralStorageSubsystem");
		return ptr;
	}


	void RemoveItemsFromCentralStorage(class UClass* ItemClass, int Num);
	bool IsCentralStorageBuilt();
	int GetNumItemsFromCentralStorage(class UClass* ItemClass);
	TArray<class AFGCentralStorageContainer*> GetCentralStorageContainers();
	class AFGCentralStorageSubsystem* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGChainsaw
// 0x0038 (0x03F8 - 0x03C0)
class AFGChainsaw : public AFGEquipment
{
public:
	class UClass*                                      mFuelClass;                                               // 0x03C0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mEnergyConsumption;                                       // 0x03C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSawDownTreeTime;                                         // 0x03CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCollateralPickupRadius;                                  // 0x03D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mExcludeChainsawableFoliage;                              // 0x03D4(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x03D5(0x0003) MISSED OFFSET
	float                                              mEnergyStored;                                            // 0x03D8(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1C];                                      // 0x03DC(0x001C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGChainsaw");
		return ptr;
	}


	void Server_StopSawing();
	void Server_StartSawing();
	void Server_RemoveChainsawedObject(class USceneComponent* sawingComponent, const struct FTransform& foliageToRemoveTransform, const struct FVector& effectLocation);
	float SawProgress();
	bool IsSawing();
	bool IsSawEngaged();
	bool HasAnyFuel();
	class UClass* GetFuelClass();
	bool CanStartSawing();
	void BroadcastPickup(TArray<struct FPickedUpInstance> pickups, class AFGFoliagePickup* instigatorPlayer);
};


// Class FactoryGame.FGChainsawableInterface
// 0x0000 (0x0028 - 0x0028)
class UFGChainsawableInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGChainsawableInterface");
		return ptr;
	}


	bool IsChainsawable();
	class UStaticMeshComponent* GetMeshComponent();
};


// Class FactoryGame.FGCharacterBase
// 0x0180 (0x08C0 - 0x0740)
class AFGCharacterBase : public ACharacter
{
public:
	TArray<struct FName>                               mFeetNames;                                               // 0x0740(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	struct FFootstepEffect                             mDefaultFootstepEffect;                                   // 0x0750(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FFootstepEffectSurface>              mFootstepEffect;                                          // 0x0760(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UAkAudioEvent*>                       mFootstepAudioEvents;                                     // 0x0770(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mMaxFootstepParticleSpawnDistance;                        // 0x0780(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxFootstepDecalSpawnDistance;                           // 0x0784(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mFootstepDecalSize;                                       // 0x0788(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFootstepDecalLifetime;                                   // 0x0794(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGHealthComponent*                          mHealthComponent;                                         // 0x0798(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, Net, ZeroConstructor, EditConst, InstancedReference, SaveGame, IsPlainOldData)
	class UCurveFloat*                                 mFallDamageCurve;                                         // 0x07A0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UCurveFloat*                                 mFallDamageCurveOverride;                                 // 0x07A8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UClass*                                      mFallDamageDamageType;                                    // 0x07B0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x07B8(0x0008) MISSED OFFSET
	float                                              mMaxDeathStayTime;                                        // 0x07C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDeathRemoveCheckTime;                                    // 0x07C4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mEnemyTargetDesirability;                                 // 0x07C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x07CC(0x0004) MISSED OFFSET
	class UAkAudioEvent*                               mTakeDamageSound;                                         // 0x07D0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mDeathSound;                                              // 0x07D8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mLandEvent;                                               // 0x07E0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mTakeDamageParticle;                                      // 0x07E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMinVehiclePushVelocityForRagdoll;                        // 0x07F0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeToGetUpFromRagdoll;                                  // 0x07F4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxDistanceMovedToGetUp;                                 // 0x07F8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0xC];                                       // 0x07FC(0x000C) MISSED OFFSET
	bool                                               mIsRagdolled;                                             // 0x0808(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0xF];                                       // 0x0809(0x000F) MISSED OFFSET
	struct FVector                                     mRagdollMeshLoc;                                          // 0x0818(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mRagdollMeshVelocity;                                     // 0x0824(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	struct FName                                       mRagdollMeshLocBoneName;                                  // 0x0830(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mRagdollMeshPhysicsBoneName;                              // 0x0838(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSyncBodyMaxDistance;                                     // 0x0840(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x42];                                      // 0x0844(0x0042) MISSED OFFSET
	bool                                               mApplyDamageMomentum;                                     // 0x0886(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData05[0x1];                                       // 0x0887(0x0001) MISSED OFFSET
	TArray<class UClass*>                              mIgnoredDamageTypes;                                      // 0x0888(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mWeakspotMultiplier;                                      // 0x0898(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData06[0x4];                                       // 0x089C(0x0004) MISSED OFFSET
	TArray<struct FName>                               mWeakspotBoneNames;                                       // 0x08A0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mNormalDamageMultiplier;                                  // 0x08B0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData07[0xC];                                       // 0x08B4(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCharacterBase");
		return ptr;
	}


	bool TraceForGround(const struct FVector& TraceStart, const struct FVector& TraceEnd, struct FHitResult* out_hitResult, float* out_waterDepth);
	void SetFallDamageOverride(class UCurveFloat* fallDamageCurveOverride);
	void ReceiveDied();
	int ReceivedAdjustDamage(float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void RagdollCharacter(bool newRagdoll);
	void PushedByVehicle(class AFGVehicle* Vehicle, const struct FVector& pushVelocity);
	void PlayFootstepEffect(int footDown, bool PlaySound);
	void OnTakeRadialDamage(class AActor* damagedActor, float Damage, class UDamageType* DamageType, const struct FVector& HitLocation, const struct FHitResult& HitInfo, class AController* instigatedBy, class AActor* damageCauser);
	void OnTakePointDamage(class AActor* damagedActor, float Damage, class AController* instigatedBy, const struct FVector& HitLocation, class UPrimitiveComponent* HitComponent, const struct FName& BoneName, const struct FVector& ShotFromDirection, class UDamageType* DamageType, class AActor* damageCauser);
	void OnTakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void OnRep_IsRagdolled();
	void NotifyOnWeakspotHit();
	void NotifyOnTakeRadialDamage(class AActor* damagedActor, float Damage, class AController* instigatedBy, class UDamageType* DamageType, class AActor* damageCauser);
	void NotifyOnTakePointDamage(class AActor* damagedActor, float Damage, class AController* instigatedBy, const struct FVector& HitLocation, class UPrimitiveComponent* HitComponent, const struct FName& BoneName, const struct FVector& ShotFromDirection, class UDamageType* DamageType, class AActor* damageCauser);
	void NotifyOnTakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	bool IsRagdolled();
	bool IsAliveAndWell();
	class UAkAudioEvent* GetTakeDamageSound();
	class UParticleSystem* GetTakeDamageParticle();
	class USkeletalMeshComponent* GetMesh3P();
	class UFGHealthComponent* GetHealthComponent();
	class UClass* GetFallDamageDamageType();
	class UAkAudioEvent* GetDeathSound();
	void Died(class AActor* thisActor);
	void CheckIfShouldDestroy();
	int CalculateFallDamage(float zSpeed);
	float AdjustDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
};


// Class FactoryGame.FGCharacterMovementComponent
// 0x0060 (0x0790 - 0x0730)
class UFGCharacterMovementComponent : public UCharacterMovementComponent
{
public:
	float                                              mLastJumpTimeStamp;                                       // 0x0730(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      mIsParachuting : 1;                                       // 0x0734(0x0001) (BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0735(0x0003) MISSED OFFSET
	float                                              mClimbSpeed;                                              // 0x0738(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxSprintSpeed;                                          // 0x073C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0740(0x0004) MISSED OFFSET
	float                                              mSprintMinDotResult;                                      // 0x0744(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mJumpOffLadderVelocity;                                   // 0x0748(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x074C(0x0004) MISSED OFFSET
	class AFGJetPack*                                  mCachedJetPack;                                           // 0x0750(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGParachute*                                mCachedParachute;                                         // 0x0758(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGHookshot*                                 mCachedHookshot;                                          // 0x0760(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGJumpingStilts*                            mCachedJumpingStilts;                                     // 0x0768(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x10];                                      // 0x0770(0x0010) MISSED OFFSET
	class UFGLadderComponent*                          mOnLadder;                                                // 0x0780(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData04[0x8];                                       // 0x0788(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCharacterMovementComponent");
		return ptr;
	}


	void ServerSetHookLocation(const struct FVector& hookLocation);
	bool GetWantsToSprint();
	class UFGLadderComponent* GetOnLadder();
	bool GetIsSprinting();
};


// Class FactoryGame.FGUseState_ReviveInvalid_PlayerNotDead
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_ReviveInvalid_PlayerNotDead : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_ReviveInvalid_PlayerNotDead");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_ReviveValid
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_ReviveValid : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_ReviveValid");
		return ptr;
	}

};


// Class FactoryGame.FGCharacterPlayer
// 0x0240 (0x0B00 - 0x08C0)
class AFGCharacterPlayer : public AFGCharacterBase
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x08C0(0x0010) MISSED OFFSET
	float                                              mBaseTurnRate;                                            // 0x08D0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	float                                              mBaseLookUpRate;                                          // 0x08D4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	class USkeletalMeshComponent*                      mMesh3P;                                                  // 0x08D8(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UClass*                                      mMesh1PAnimClass;                                         // 0x08E0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mFoliagePickupProxyClass;                                 // 0x08E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGFoliagePickup*                            mFoliagePickupProxy;                                      // 0x08F0(0x0008) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData)
	class AFGBuildGun*                                 mBuildGun;                                                // 0x08F8(0x0008) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGResourceScanner*                          mResourceScanner;                                         // 0x0900(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGResourceMiner*                            mResourceMiner;                                           // 0x0908(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AActor*                                      mBestUsableActor;                                         // 0x0910(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FUseState                                   mCachedUseState;                                          // 0x0918(0x0028) (BlueprintVisible, BlueprintReadOnly)
	class UClass*                                      mAnimInstanceClass;                                       // 0x0940(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mAnimInstanceClass1P;                                     // 0x0948(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mReviveDuration;                                          // 0x0950(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0954(0x0004) MISSED OFFSET
	TArray<struct FItemAmount>                         mStartingResources;                                       // 0x0958(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FItemAmount>                         mStartingResourceForTesting;                              // 0x0968(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UClass*                                      mDrownDamageDamageType;                                   // 0x0978(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDrownDamage;                                             // 0x0980(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDrownDamageInterval;                                     // 0x0984(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGCharacterPlayer*                          mPlayerToRevive;                                          // 0x0988(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class AFGItemPickup*                               mPickupToCollect;                                         // 0x0990(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FFootstepEffect                             m1PDefaultFootstepEffect;                                 // 0x0998(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FFootstepEffectSurface>              m1PFootstepEffect;                                        // 0x09A8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UAkAudioEvent*>                       m1PFootstepEvent;                                         // 0x09B8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData02[0x4];                                       // 0x09C8(0x0004) MISSED OFFSET
	struct FVector                                     mLastSafeGroundPositions[0x3];                            // 0x09CC(0x000C) (ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                mLastSafeGroundPositionLoopHead;                          // 0x09F0(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x09F4(0x0004) MISSED OFFSET
	class UCameraComponent*                            mCameraComponent;                                         // 0x09F8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpringArmComponent*                         mSpringArmComponent;                                      // 0x0A00(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<class AFGEquipment*>                        mActiveEquipments;                                        // 0x0A08(0x0010) (Net, ZeroConstructor)
	TArray<class AFGEquipment*>                        mClientActiveEquipments;                                  // 0x0A18(0x0010) (ZeroConstructor)
	TArray<class AFGEquipmentAttachment*>              mAllAttachments;                                          // 0x0A28(0x0010) (Net, ZeroConstructor)
	TArray<class AFGEquipmentAttachment*>              mActiveAttachments;                                       // 0x0A38(0x0010) (Net, ZeroConstructor)
	ECameraMode                                        mCurrentCameraMode;                                       // 0x0A48(0x0001) (ZeroConstructor, IsPlainOldData)
	ECameraMode                                        mPlayerPreferredCameraMode;                               // 0x0A49(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x6];                                       // 0x0A4A(0x0006) MISSED OFFSET
	class UFGInventoryComponent*                       mInventory;                                               // 0x0A50(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	class UFGInventoryComponentBeltSlot*               mBeltSlot;                                                // 0x0A58(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	class UFGInventoryComponent*                       mTrashSlot;                                               // 0x0A60(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mAllowCameraToggling;                                     // 0x0A68(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData05[0x3];                                       // 0x0A69(0x0003) MISSED OFFSET
	float                                              mUseDistance;                                             // 0x0A6C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData06[0x4];                                       // 0x0A70(0x0004) MISSED OFFSET
	int8_t                                             mPickupCounter;                                           // 0x0A74(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x3];                                       // 0x0A75(0x0003) MISSED OFFSET
	class AFGCharacterPlayer*                          mReviver;                                                 // 0x0A78(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData08[0x18];                                      // 0x0A80(0x0018) MISSED OFFSET
	class UClass*                                      mDefaultWalkHeadBobShake;                                 // 0x0A98(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDefaultSprintHeadBobShake;                               // 0x0AA0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGDriveablePawn*                            mDrivenVehicle;                                           // 0x0AA8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGDriveablePawn*                            mSavedDrivenVehicle;                                      // 0x0AB0(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class UFGOutlineComponent*                         mOutlineComponent;                                        // 0x0AB8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mHealthGenerationThreshold;                               // 0x0AC0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHealthGenerationAmount;                                  // 0x0AC4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHealthGenerationInterval;                                // 0x0AC8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHealthGenerationWaitTime;                                // 0x0ACC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData09[0x20];                                      // 0x0AD0(0x0020) MISSED OFFSET
	float                                              mRadiationIntensity;                                      // 0x0AF0(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mRadiationDamageAngle;                                    // 0x0AF4(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mRadiationImmunity;                                       // 0x0AF8(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mInRadioactiveZone;                                       // 0x0AFC(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData10[0x3];                                       // 0x0AFD(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCharacterPlayer");
		return ptr;
	}


	void UsePreferredCameraMode();
	void UnequipEquipment(class AFGEquipment* equipment);
	void ToggleCameraMode();
	void ToggleBuildGun();
	void StopReceivingRadiation();
	void StopFreeRotate3P();
	void StopFocusAim();
	void StartReceivingRadiation();
	void StartFreeRotate3P();
	void StartFocusAim();
	void SpawnInitialGear();
	void SnapSpringArmToDesiredLocation();
	void SetWantSprintBobbing(bool wantBobbing);
	void SetThirdPersonMode();
	void SetRadiationImmunity(float newImmunity);
	void SetMeshVisibility(bool IsFirstPerson);
	void SetFirstPersonMode();
	void SetCameraMode(ECameraMode newCameraMode);
	void Server_UnequipEquipment(class AFGEquipment* newEquipment);
	void Server_ToggleSwitchControl(class AFGBuildableRailroadSwitchControl* switchControl);
	void Server_RevivePlayer(class AFGCharacterPlayer* playerToRevive);
	void Server_PickUpItem(class AFGItemPickup* itemPickup);
	void Server_OnUseReleased();
	void Server_OnUse();
	void Server_EquipEquipment(class AFGEquipment* newEquipment);
	void Server_CycleHandEquipmentPressed(int dir);
	void PlayPickupEffects();
	void OnSpawnDeathMarker();
	void OnReviveComplete();
	void OnRep_RadiationIntensity();
	void OnRep_PickupCounter();
	void OnRep_InRadioactiveZone();
	void OnRep_DrivenVehicle();
	void OnRep_ActiveEquipments();
	void OnRep_ActiveAttachments();
	void OnReceiveRadiationStop();
	void OnReceiveRadiationStart();
	void OnRadiationIntensityUpdated(float radiationIntensity, float radiationImmunity);
	void OnItemAddedToInventory(class UClass* ItemClass, int numAdded);
	void OnInventorySlotsUnlocked(int newUnlockedSlots);
	void OnDisabledInputGateChanged(const struct FDisabledInputGate& NewValue);
	void OnArmsSlotsUnlocked(int newUnlockedSlots);
	bool IsFirstPerson();
	bool IsDrivingVehicle();
	bool IsBuildGunEquipped();
	void HotKeyRecipe(class UClass* Recipe);
	void HotKeyDismantle();
	bool GetWantSprintBobbing();
	float GetUseDistance();
	class UFGInventoryComponent* GetTrashSlot();
	class USpringArmComponent* GetSpringArmComponent();
	float GetReviveProgress();
	class AFGResourceScanner* GetResourceScanner();
	class AFGResourceMiner* GetResourceMiner();
	float GetRadiationIntensity();
	float GetRadiationImmunity();
	float GetRadiationDamageAngle();
	float GetPickupProgress();
	class UFGOutlineComponent* GetOutline();
	class USkeletalMeshComponent* GetMesh1P();
	struct FVector GetInventoryDropLocation(class UFGInventoryComponent* component, const struct FInventoryStack& stack);
	class UFGInventoryComponent* GetInventory();
	class UFGInventoryComponentEquipment* GetEquipmentSlot(EEquipmentSlot Slot);
	class AFGEquipment* GetEquipmentInSlot(EEquipmentSlot Slot);
	class AFGDriveablePawn* GetDrivenVehicle();
	class UClass* GetDesiredWalkHeadBobShake();
	class UClass* GetDesiredSprintHeadBobShake();
	class UFGLadderComponent* GetCurrentLadderComponent();
	ECameraMode GetCameraMode();
	class UCameraComponent* GetCameraComponent();
	class AFGBuildGun* GetBuildGun();
	class AActor* GetBestUsableActor();
	class UFGInventoryComponentBeltSlot* GetBeltSlot();
	TArray<class AFGEquipment*> GetActiveEquipments();
	struct FInventoryItem GetActiveEquipmentItem(EEquipmentSlot Slot);
	ECrosshairState GetActiveCrosshairState();
	TArray<class AFGEquipmentAttachment*> GetActiveAttachments();
	void EquipEquipment(class AFGEquipment* equipment);
	void Client_Revived();
	void CameraZoomOut();
	void CameraZoomIn();
	void AddRadiationImmunity(float toAdd);
};


// Class FactoryGame.FGChatManager
// 0x0028 (0x0350 - 0x0328)
class AFGChatManager : public AFGSubsystem
{
public:
	struct FScriptMulticastDelegate                    OnChatMessageAdded;                                       // 0x0328(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	int                                                mMaxNumMessagesInHistory;                                 // 0x0338(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMessageVisibleDuration;                                  // 0x033C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FChatMessageStruct>                  mReceivedMessages;                                        // 0x0340(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGChatManager");
		return ptr;
	}


	void Multicast_BroadcastChatMessage(const struct FChatMessageStruct& newMessage);
	void GetReceivedChatMessages(TArray<struct FChatMessageStruct>* out_messages);
	float GetMessageVisibleDuration();
	int GetMaxNumMessagesInHistory();
	class FString GetChatMessageName(const struct FChatMessageStruct& inMessage);
	struct FLinearColor GetChatMessageColor(const struct FChatMessageStruct& inMessage);
	class AFGChatManager* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGCheatManager
// 0x0010 (0x0088 - 0x0078)
class UFGCheatManager : public UCheatManager
{
public:
	TArray<class UClass*>                              mPopularUClassChoices;                                    // 0x0078(0x0010) (ZeroConstructor, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCheatManager");
		return ptr;
	}


	void VisitAllMapAreas();
	void UpdateSessionToOSS();
	void TurboMode(bool Enabled);
	void TriggerPresenceUpdate();
	void ToggleCameraMode();
	void ToggleAudioLandingDebug();
	void ToggleAudioDebug();
	void TestSharedInventoryPtr();
	void SplitAllConveyors();
	void ShowSequenceList();
	void ShowFactoryOnly(bool environmentHidden);
	void SetTradingPostLevel(int inLevel);
	void SetTimeSpeedMultiplier(float Speed);
	void SetTimeOfDay(int hour, int minute);
	void SetSlomo(float Slomo);
	void SetRandomDebugStartingPoint();
	void SetGamePhase(TEnumAsByte<EGamePhase> phase);
	void SetFactoryDetailReplication(bool enable);
	void SetDebugStartingPoint(const struct FName& startingPoint);
	void SetAITickDistance(float Distance);
	void SendInviteToFriend(const class FString& friendName);
	void SaveWithNewSessionName(const class FString& saveName, const class FString& SessionName);
	void RunDebugMetric();
	void ResetSchematics();
	void ResetHubTutorial();
	void ResetFuses();
	void ReplayBuildingEffects();
	void RemoveAllFoliage(int maxNumInstances);
	void RebuildPowerCircuits();
	void RandomizeBuildingsColorSlot(unsigned char SlotIndex);
	void PurgeInactiveClientsFromSave(bool fetchInventories);
	void PurgeAllTrainState();
	void PurgeAllBeaconsFromSave();
	void PumpiMode(bool enable);
	void PrintStatichMeshesHirarchy();
	void PardonAllPlayers();
	void OpenModMap();
	void NoPower(bool Enabled);
	void NoCost(bool Enabled);
	void MergeAllConveyors();
	void MCP_UpdatePresenceString(const class FString& String);
	void MCP_UpdatePresence(const class FString& Key, const class FString& Value);
	void MCP_LogPresence();
	void MCP_Logout();
	void MCP_Login(const class FString& UserName, const class FString& password);
	void MCP_GetOnlineStatus(int localPlayerNum);
	void MCP_GetFriends();
	void ListUnlockedRecipesAndSchematics();
	void ListItemPickups();
	void ListDebugStartingPoint();
	void HideFactoryOnly(bool factoryHidden);
	void HideAllBuildings(bool InVisibility);
	void GiveItem(class UClass* Resource, int amount);
	void GiefStorySchematics();
	void GiefStartingResearch();
	void GiefSchematicsOfTier(int tier);
	void GiefCheatSchematics();
	void GiefAvailableSchematics();
	void GiefAllSchematicsAndPhases();
	void GiefALLSchematics();
	void GetVehicleInfo();
	void ForceSpawnCreatures();
	void FlipVehicle();
	void FixupBuiltByRecipeInOldSave(bool reapplyRecipeIfBetterMatchFound);
	void EnablePlayerFOV(bool enable);
	void EnableInstancingOnFactory(bool Enabled);
	void EnableBuildableTick(bool enable);
	void DumpTicking(bool detailed);
	void DumpSchematics();
	void DumpPlayerStates();
	void DumpNonDormantActors();
	void DumpFactoryStatsToLog();
	void DumpAttachedToSkelMesh(bool detailed);
	void DumpAllAvailableRecipes();
	void DumpActorRepresentations();
	void DumpActiveGPUParticles();
	void DestroyPawn();
	void DebugCrash();
	void CompleteResearch();
	void ClearPardon();
	void ClearGiveItemPopularList();
};


// Class FactoryGame.FGCircuit
// 0x0038 (0x0060 - 0x0028)
class UFGCircuit : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	int                                                mCircuitID;                                               // 0x0030(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0034(0x0004) MISSED OFFSET
	TArray<class UFGCircuitConnectionComponent*>       mComponents;                                              // 0x0038(0x0010) (ExportObject, ZeroConstructor, SaveGame)
	unsigned char                                      mNeedFullRebuild : 1;                                     // 0x0048(0x0001)
	unsigned char                                      mHasChanged : 1;                                          // 0x0048(0x0001)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0049(0x0007) MISSED OFFSET
	TArray<class AFGCharacterPlayer*>                  mInteractingPlayers;                                      // 0x0050(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCircuit");
		return ptr;
	}


	int GetCircuitID();
};


// Class FactoryGame.FGConnectionComponent
// 0x0000 (0x0240 - 0x0240)
class UFGConnectionComponent : public USceneComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConnectionComponent");
		return ptr;
	}

};


// Class FactoryGame.FGCircuitConnectionComponent
// 0x0050 (0x0290 - 0x0240)
class UFGCircuitConnectionComponent : public UFGConnectionComponent
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0240(0x0018) MISSED OFFSET
	int                                                mMaxNumConnectionLinks;                                   // 0x0258(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsHiddenConnection;                                      // 0x025C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x025D(0x0003) MISSED OFFSET
	TArray<class AFGBuildableWire*>                    mWires;                                                   // 0x0260(0x0010) (Edit, Net, ZeroConstructor, EditConst, SaveGame)
	unsigned char                                      mNbWiresConnected;                                        // 0x0270(0x0001) (Edit, Net, ZeroConstructor, EditConst, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0271(0x0007) MISSED OFFSET
	TArray<class UFGCircuitConnectionComponent*>       mHiddenConnections;                                       // 0x0278(0x0010) (Edit, ExportObject, ZeroConstructor, EditConst, SaveGame)
	int                                                mCircuitID;                                               // 0x0288(0x0004) (Edit, Net, ZeroConstructor, EditConst, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x028C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCircuitConnectionComponent");
		return ptr;
	}


	void ReceiveOnCircuitIDChanged();
	bool IsHidden();
	int IsConnected();
	int GetNumHiddenConnections();
	int GetNumFreeConnections();
	int GetNumConnections();
	int GetMaxNumConnections();
	int GetCircuitID();
};


// Class FactoryGame.FGCircuitSubsystem
// 0x0070 (0x0398 - 0x0328)
class AFGCircuitSubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	TMap<int, class UFGCircuit*>                       mCircuits;                                                // 0x0330(0x0050) (ZeroConstructor)
	TArray<class UFGCircuit*>                          mReplicatedCircuits;                                      // 0x0380(0x0010) (Net, ZeroConstructor)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0390(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCircuitSubsystem");
		return ptr;
	}


	void PowerCircuit_OnFuseSet();
	void PowerCircuit_OnFuseReset();
	void OnRep_ReplicatedCircuits();
	class AFGCircuitSubsystem* GetCircuitSubsystem(class UObject* WorldContext);
	class UFGCircuit* FindCircuit(int circuitID);
};


// Class FactoryGame.FGColoredInstanceManager
// 0x0190 (0x03D0 - 0x0240)
class UFGColoredInstanceManager : public USceneComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0240(0x0008) MISSED OFFSET
	class UHierarchicalInstancedStaticMeshComponent*   mInstanceComponents[0x10];                                // 0x0248(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x108];                                     // 0x02C8(0x0108) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGColoredInstanceManager");
		return ptr;
	}

};


// Class FactoryGame.FGColoredInstanceMeshProxy
// 0x0010 (0x0600 - 0x05F0)
class UFGColoredInstanceMeshProxy : public UStaticMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x05F0(0x0008) MISSED OFFSET
	bool                                               mCanBecolored;                                            // 0x05F8(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mBlockInstancing;                                         // 0x05F9(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x05FA(0x0006) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGColoredInstanceMeshProxy");
		return ptr;
	}

};


// Class FactoryGame.FGWeaponInstantFire
// 0x0010 (0x0420 - 0x0410)
class AFGWeaponInstantFire : public AFGWeapon
{
public:
	float                                              mInstantHitDamage;                                        // 0x0410(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mWeaponTraceLength;                                       // 0x0414(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mHitParticleEffect;                                       // 0x0418(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWeaponInstantFire");
		return ptr;
	}


	void Server_NotifyMiss();
	void Server_NotifyHit(const struct FHitResult& HitResult);
};


// Class FactoryGame.FGColorGun
// 0x0098 (0x04B8 - 0x0420)
class AFGColorGun : public AFGWeaponInstantFire
{
public:
	struct FLinearColor                                mPrimaryColor;                                            // 0x0420(0x0010) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FLinearColor                                mSecondaryColor;                                          // 0x0430(0x0010) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FLinearColor                                mRedundantTargetCrosshairColor;                           // 0x0440(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mRedundantTargetCrosshairTexture;                         // 0x0450(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FLinearColor                                mNoTargetCrosshairColor;                                  // 0x0458(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mNoTargetCrosshairTexture;                                // 0x0468(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FLinearColor                                mNonColorableTargetCrosshairColor;                        // 0x0470(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mNonColorableTargetCrosshairTexture;                      // 0x0480(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mValidTargetCrosshairTexture;                             // 0x0488(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      mColorSlot;                                               // 0x0490(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0491(0x0007) MISSED OFFSET
	class AActor*                                      mCurrentColorTarget;                                      // 0x0498(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x18];                                      // 0x04A0(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGColorGun");
		return ptr;
	}


	void ToggleColorPickerUI();
	void Sever_SetSecondaryColorForSlot(unsigned char SlotIndex, const struct FLinearColor& NewColor);
	void Sever_SetSecondaryColor(const struct FLinearColor& NewColor);
	void Sever_SetPrimaryColorForSlot(unsigned char SlotIndex, const struct FLinearColor& NewColor);
	void Sever_SetPrimaryColor(const struct FLinearColor& NewColor);
	void Sever_SetColorSlot(unsigned char SlotIndex);
	void SetSecondaryColorForSlot(unsigned char SlotIndex, const struct FLinearColor& NewColor);
	void SetSecondaryColor(const struct FLinearColor& NewColor);
	void SetPrimaryColorForSlot(unsigned char SlotIndex, const struct FLinearColor& NewColor);
	void SetPrimaryColor(const struct FLinearColor& NewColor);
	void SetColorSlot(unsigned char SlotIndex);
	void OnTargetStateChanged(EFGColorGunTargetType targetType);
	void OnSecondaryFirePressed();
	struct FLinearColor GetSecondaryColorForSlot(unsigned char Index);
	struct FLinearColor GetSecondaryColor();
	struct FLinearColor GetPrimaryColorForSlot(unsigned char Index);
	struct FLinearColor GetPrimaryColor();
	unsigned char GetMaxNumColorSlots();
	unsigned char GetColorSlotIndex();
};


// Class FactoryGame.FGColorInterface
// 0x0000 (0x0028 - 0x0028)
class UFGColorInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGColorInterface");
		return ptr;
	}


	void StopIsAimedAtForColor(class AFGCharacterPlayer* byCharacter);
	void StartIsAimedAtForColor(class AFGCharacterPlayer* byCharacter);
	void SetSecondaryColor(const struct FLinearColor& NewColor);
	void SetPrimaryColor(const struct FLinearColor& NewColor);
	void SetColorSlot(unsigned char Index);
	struct FLinearColor GetSecondaryColor();
	struct FLinearColor GetPrimaryColor();
	unsigned char GetColorSlot();
	bool GetCanBeColored();
};


// Class FactoryGame.FGCombatFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCombatFunctionLibrary");
		return ptr;
	}


	class AFGCharacterBase* TryGetCharacterFromDamageCauser(class AActor* damageCauser);
	bool IsWithinRange(class APawn* attacker, const TScriptInterface<class UFGAggroTargetInterface>& victim, float range);
	bool IsWithinAttackRange(class APawn* attacker, const TScriptInterface<class UFGAggroTargetInterface>& victim, class UClass* attackClass);
	void DoRadialDamageWithinCollision(class AController* Controller, class UShapeComponent* collisionShape, const struct FVector& centerLocation, class UClass* DamageType, float Damage, float Radius);
};


// Class FactoryGame.FGCompassObjectWidget
// 0x0070 (0x0278 - 0x0208)
class UFGCompassObjectWidget : public UUserWidget
{
public:
	class UTexture2D*                                  mTexture;                                                 // 0x0208(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FText                                       mText;                                                    // 0x0210(0x0028) (BlueprintVisible)
	struct FVector2D                                   mPositionOffset;                                          // 0x0228(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mClampPosition;                                           // 0x0230(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mShouldFadeInEdges;                                       // 0x0231(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0232(0x0006) MISSED OFFSET
	class UImage*                                      mImage;                                                   // 0x0238(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mCheckForBlockingInCompass;                               // 0x0240(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0241(0x0007) MISSED OFFSET
	class UFGActorRepresentation*                      mActorRepresentation;                                     // 0x0248(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     mStaticDirection;                                         // 0x0250(0x000C) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mIsBlocking;                                              // 0x025C(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1B];                                      // 0x025D(0x001B) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCompassObjectWidget");
		return ptr;
	}


	void SetAsStaticDirection(const struct FVector& Direction);
	void SetActorRepresentation(class UFGActorRepresentation* actorRepresentation);
	void OnObjectCentered(bool centered);
	void OnCompassObjectUpdated();
	void OnCompassObjectAddedToPanel(class UCanvasPanelSlot* parentSlot);
	ERepresentationType GetRepresentationType();
	struct FVector GetDirectionFromLocation(const struct FVector& Location);
	float GetBlockingAmount();
	float GetAngleFromDirection(const struct FVector& Direction);
	float GetAlphaAmount();
	class UFGActorRepresentation* GetActorRepresentation();
};


// Class FactoryGame.FGCompassWidget
// 0x0070 (0x0278 - 0x0208)
class UFGCompassWidget : public UUserWidget
{
public:
	class UCanvasPanel*                                mCompassPanel;                                            // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UCanvasPanel*                                mContentPanel;                                            // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UImage*                                      mCompassLine;                                             // 0x0218(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<class UFGCompassObjectWidget*>              mCompassObjects;                                          // 0x0220(0x0010) (ExportObject, ZeroConstructor, Transient)
	TArray<class UFGCompassObjectWidget*>              mCenterableCompassObjects;                                // 0x0230(0x0010) (ExportObject, ZeroConstructor, Transient)
	TArray<class UFGCompassObjectWidget*>              mCenterableResourceCompassObjects;                        // 0x0240(0x0010) (ExportObject, ZeroConstructor, Transient)
	class AFGActorRepresentationManager*               mActorRepresentationManager;                              // 0x0250(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	TArray<class UFGCompassObjectWidget*>              mCurrentCenteredResourceObjects;                          // 0x0258(0x0010) (ExportObject, ZeroConstructor, Transient)
	class UFGCompassObjectWidget*                      mCurrentCenteredObject;                                   // 0x0268(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	float                                              mThresholdForCenteredObjects;                             // 0x0270(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mThresholdForCenteredResourceObjects;                     // 0x0274(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCompassWidget");
		return ptr;
	}


	void RemoveCompassObjectForRepresentation(class UFGActorRepresentation* actorRepresentation);
	void RemoveAllCompassRepresentations();
	void OnActorRepresentationUpdated(class UFGActorRepresentation* actorRepresentation);
	void OnActorRepresentationRemoved(class UFGActorRepresentation* actorRepresentation);
	void OnActorRepresentationAdded(class UFGActorRepresentation* actorRepresentation);
	class UClass* GetCompassObjectWidgetClass(class UFGActorRepresentation* actorRepresentation);
	struct FVector2D GetCompassLineOffset();
	class UFGCompassObjectWidget* CreatePrimitiveCompassObject(class UClass* compassObjectTemplate, class UTexture2D* Texture);
	class UFGCompassObjectWidget* CreateCompassObject(class UClass* compassObjectTemplate, class UFGActorRepresentation* actorRepresentation);
	void BindActorRepresentationManager(class AFGActorRepresentationManager* representationManager);
	class UFGCompassObjectWidget* AddCompassObjectForRepresentation(class UClass* compassObjectTemplate, class UFGActorRepresentation* actorRepresentation);
	void AddAllCompassRepresentations(class AFGActorRepresentationManager* representationManager);
	void AddAllCardinalDirections(class UClass* compassObjectTemplate, class UTexture2D* northTex, class UTexture2D* eastTex, class UTexture2D* southTex, class UTexture2D* westTex, class UTexture2D* northWestTex, class UTexture2D* southEastTex, class UTexture2D* southWestText, class UTexture2D* northEastTex);
};


// Class FactoryGame.FGConstructDisqualifier
// 0x0018 (0x0040 - 0x0028)
class UFGConstructDisqualifier : public UObject
{
public:
	struct FText                                       mDisqfualifyingText;                                      // 0x0028(0x0028) (Edit, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConstructDisqualifier");
		return ptr;
	}


	struct FText GetDisqualifyingText(class UClass* inClass);
};


// Class FactoryGame.FGCDInitializing
// 0x0000 (0x0040 - 0x0040)
class UFGCDInitializing : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDInitializing");
		return ptr;
	}

};


// Class FactoryGame.FGCDInvalidAimLocation
// 0x0000 (0x0040 - 0x0040)
class UFGCDInvalidAimLocation : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDInvalidAimLocation");
		return ptr;
	}

};


// Class FactoryGame.FGCDUnaffordable
// 0x0000 (0x0040 - 0x0040)
class UFGCDUnaffordable : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDUnaffordable");
		return ptr;
	}

};


// Class FactoryGame.FGCDInvalidPlacement
// 0x0000 (0x0040 - 0x0040)
class UFGCDInvalidPlacement : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDInvalidPlacement");
		return ptr;
	}

};


// Class FactoryGame.FGCDEncroachingClearance
// 0x0000 (0x0040 - 0x0040)
class UFGCDEncroachingClearance : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDEncroachingClearance");
		return ptr;
	}

};


// Class FactoryGame.FGCDEncroachingPlayer
// 0x0000 (0x0040 - 0x0040)
class UFGCDEncroachingPlayer : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDEncroachingPlayer");
		return ptr;
	}

};


// Class FactoryGame.FGCDInvalidFloor
// 0x0000 (0x0040 - 0x0040)
class UFGCDInvalidFloor : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDInvalidFloor");
		return ptr;
	}

};


// Class FactoryGame.FGCDUniqueBuilding
// 0x0000 (0x0040 - 0x0040)
class UFGCDUniqueBuilding : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDUniqueBuilding");
		return ptr;
	}

};


// Class FactoryGame.FGCDMustSnap
// 0x0000 (0x0040 - 0x0040)
class UFGCDMustSnap : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDMustSnap");
		return ptr;
	}

};


// Class FactoryGame.FGCDShouldntSnap
// 0x0000 (0x0040 - 0x0040)
class UFGCDShouldntSnap : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDShouldntSnap");
		return ptr;
	}

};


// Class FactoryGame.FGCDNeedsResourceNode
// 0x0000 (0x0040 - 0x0040)
class UFGCDNeedsResourceNode : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDNeedsResourceNode");
		return ptr;
	}

};


// Class FactoryGame.FGCDResourceNodeIsOccuped
// 0x0000 (0x0040 - 0x0040)
class UFGCDResourceNodeIsOccuped : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDResourceNodeIsOccuped");
		return ptr;
	}

};


// Class FactoryGame.FGCDResourceDeposit
// 0x0000 (0x0040 - 0x0040)
class UFGCDResourceDeposit : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDResourceDeposit");
		return ptr;
	}

};


// Class FactoryGame.FGCDWireSnap
// 0x0000 (0x0040 - 0x0040)
class UFGCDWireSnap : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDWireSnap");
		return ptr;
	}

};


// Class FactoryGame.FGCDWireTooLong
// 0x0000 (0x0040 - 0x0040)
class UFGCDWireTooLong : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDWireTooLong");
		return ptr;
	}

};


// Class FactoryGame.FGCDWireTooManyConnections
// 0x0000 (0x0040 - 0x0040)
class UFGCDWireTooManyConnections : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDWireTooManyConnections");
		return ptr;
	}

};


// Class FactoryGame.FGCDBeltMustSnap
// 0x0000 (0x0040 - 0x0040)
class UFGCDBeltMustSnap : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDBeltMustSnap");
		return ptr;
	}

};


// Class FactoryGame.FGCDConveyorTooLong
// 0x0000 (0x0040 - 0x0040)
class UFGCDConveyorTooLong : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDConveyorTooLong");
		return ptr;
	}

};


// Class FactoryGame.FGCDConveyorTooShort
// 0x0000 (0x0040 - 0x0040)
class UFGCDConveyorTooShort : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDConveyorTooShort");
		return ptr;
	}

};


// Class FactoryGame.FGCDConveyorTooSteep
// 0x0000 (0x0040 - 0x0040)
class UFGCDConveyorTooSteep : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDConveyorTooSteep");
		return ptr;
	}

};


// Class FactoryGame.FGCDConveyorInvalidShape
// 0x0000 (0x0040 - 0x0040)
class UFGCDConveyorInvalidShape : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDConveyorInvalidShape");
		return ptr;
	}

};


// Class FactoryGame.FGCDConveyorAttachmentTooSharpTurn
// 0x0000 (0x0040 - 0x0040)
class UFGCDConveyorAttachmentTooSharpTurn : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDConveyorAttachmentTooSharpTurn");
		return ptr;
	}

};


// Class FactoryGame.FGCDMustHaveRailRoadTrack
// 0x0000 (0x0040 - 0x0040)
class UFGCDMustHaveRailRoadTrack : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDMustHaveRailRoadTrack");
		return ptr;
	}

};


// Class FactoryGame.FGCDMustAttachToTrainPlatform
// 0x0000 (0x0040 - 0x0040)
class UFGCDMustAttachToTrainPlatform : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDMustAttachToTrainPlatform");
		return ptr;
	}

};


// Class FactoryGame.FGCDTrackTooLong
// 0x0000 (0x0040 - 0x0040)
class UFGCDTrackTooLong : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDTrackTooLong");
		return ptr;
	}

};


// Class FactoryGame.FGCDTrackTooShort
// 0x0000 (0x0040 - 0x0040)
class UFGCDTrackTooShort : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDTrackTooShort");
		return ptr;
	}

};


// Class FactoryGame.FGCDTrackTooSteep
// 0x0000 (0x0040 - 0x0040)
class UFGCDTrackTooSteep : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDTrackTooSteep");
		return ptr;
	}

};


// Class FactoryGame.FGCDTrackTrunToSharp
// 0x0000 (0x0040 - 0x0040)
class UFGCDTrackTrunToSharp : public UFGConstructDisqualifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCDTrackTrunToSharp");
		return ptr;
	}

};


// Class FactoryGame.FGEquipmentDescriptor
// 0x0008 (0x0130 - 0x0128)
class UFGEquipmentDescriptor : public UFGItemDescriptor
{
public:
	class UClass*                                      mEquipmentClass;                                          // 0x0128(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEquipmentDescriptor");
		return ptr;
	}


	class UClass* GetEquipmentClass(class UClass* inClass);
};


// Class FactoryGame.FGConsumableDescriptor
// 0x0038 (0x0168 - 0x0130)
class UFGConsumableDescriptor : public UFGEquipmentDescriptor
{
public:
	class UAkAudioEvent*                               mConsumeEvent;                                            // 0x0130(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCustomHandsMeshScale;                                    // 0x0138(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRotator                                    mCustomRotation;                                          // 0x013C(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mCustomLocation;                                          // 0x0148(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0154(0x0004) MISSED OFFSET
	class USkeletalMesh*                               mFPOverrideMesh;                                          // 0x0158(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mTPOverrideMesh;                                          // 0x0160(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConsumableDescriptor");
		return ptr;
	}


	class UStaticMesh* GetTPOverrideMesh(class UClass* inClass);
	class USkeletalMesh* GetFPOverrideMesh(class UClass* inClass);
	void ConsumedBy(class AFGCharacterPlayer* Player);
};


// Class FactoryGame.FGConsumableEquipment
// 0x0000 (0x03C0 - 0x03C0)
class AFGConsumableEquipment : public AFGEquipment
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConsumableEquipment");
		return ptr;
	}


	void Server_PrimaryFire();
	void PlayConsumeEffects(class UFGConsumableDescriptor* consumable);
	void GetConsumeable(class UClass** out_consumeable, int* out_numConsumeable);
};


// Class FactoryGame.FGConveyorBeltHologram
// 0x0078 (0x0458 - 0x03E0)
class AFGConveyorBeltHologram : public AFGBuildableHologram
{
public:
	class UFGSplineComponent*                          mSplineComponent;                                         // 0x03E0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FSplinePointData>                    mSplineData;                                              // 0x03E8(0x0010) (Net, ZeroConstructor)
	unsigned char                                      UnknownData00[0x8];                                       // 0x03F8(0x0008) MISSED OFFSET
	class UFGFactoryConnectionComponent*               mConnectionComponents[0x2];                               // 0x0400(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               mSnappedConnectionComponents[0x2];                        // 0x0410(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AFGConveyorPoleHologram*                     mConveyorPoles[0x2];                                      // 0x0420(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGBuildableConveyorBelt*                    mUpgradedConveyorBelt;                                    // 0x0430(0x0008) (ZeroConstructor, IsPlainOldData)
	class UClass*                                      mDefaultConveyorPoleRecipe;                               // 0x0438(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mBendRadius;                                              // 0x0440(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMaxLength;                                               // 0x0444(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxIncline;                                              // 0x0448(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EFactoryConnectionDirection                        mConnectionArrowComponentDirection;                       // 0x044C(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x044D(0x0003) MISSED OFFSET
	class UStaticMeshComponent*                        mConnectionArrowComponent;                                // 0x0450(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorBeltHologram");
		return ptr;
	}


	void OnRep_SplineData();
	void OnRep_ConnectionArrowComponentDirection();
};


// Class FactoryGame.FGSplineHologram
// 0x0018 (0x03F8 - 0x03E0)
class AFGSplineHologram : public AFGBuildableHologram
{
public:
	class USplineComponent*                            mSplineComponent;                                         // 0x03E0(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	TArray<struct FSplinePointData>                    mSplineData;                                              // 0x03E8(0x0010) (Net, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSplineHologram");
		return ptr;
	}


	void OnRep_SplineData();
};


// Class FactoryGame.FGConveyorLiftHologram
// 0x0108 (0x0500 - 0x03F8)
class AFGConveyorLiftHologram : public AFGSplineHologram
{
public:
	unsigned char                                      UnknownData00[0x58];                                      // 0x03F8(0x0058) MISSED OFFSET
	class UFGFactoryConnectionComponent*               mConnectionComponents[0x2];                               // 0x0450(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGFactoryConnectionComponent*               mSnappedConnectionComponents[0x2];                        // 0x0460(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AFGBuildableConveyorLift*                    mUpgradedConveyorLift;                                    // 0x0470(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0478(0x0008) MISSED OFFSET
	struct FTransform                                  mTopTransform;                                            // 0x0480(0x0030) (Net, IsPlainOldData)
	unsigned char                                      UnknownData02[0x10];                                      // 0x04B0(0x0010) MISSED OFFSET
	class UStaticMesh*                                 mBottomMesh;                                              // 0x04C0(0x0008) (ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 mMidMesh;                                                 // 0x04C8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 mTopMesh;                                                 // 0x04D0(0x0008) (ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 mJointMesh;                                               // 0x04D8(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x10];                                      // 0x04E0(0x0010) MISSED OFFSET
	EFactoryConnectionDirection                        mArrowDirection;                                          // 0x04F0(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x04F1(0x0007) MISSED OFFSET
	class UStaticMeshComponent*                        mArrowComponent;                                          // 0x04F8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorLiftHologram");
		return ptr;
	}


	void OnRep_TopTransform();
	void OnRep_ArrowDirection();
};


// Class FactoryGame.FGConveyorMultiPoleHologram
// 0x0000 (0x03E0 - 0x03E0)
class AFGConveyorMultiPoleHologram : public AFGBuildableHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorMultiPoleHologram");
		return ptr;
	}

};


// Class FactoryGame.FGPoleHologram
// 0x0030 (0x0478 - 0x0448)
class AFGPoleHologram : public AFGFactoryHologram
{
public:
	struct FPoleHeightMesh                             mPoleMesh;                                                // 0x0448(0x0010) (Net)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0458(0x0010) MISSED OFFSET
	class UStaticMeshComponent*                        mPoleMeshComponent;                                       // 0x0468(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mPoleHeightComponent;                                     // 0x0470(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPoleHologram");
		return ptr;
	}


	void OnRep_PoleMesh();
};


// Class FactoryGame.FGConveyorPoleHologram
// 0x0008 (0x0480 - 0x0478)
class AFGConveyorPoleHologram : public AFGPoleHologram
{
public:
	class UFGFactoryConnectionComponent*               mSnapConnection;                                          // 0x0478(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorPoleHologram");
		return ptr;
	}

};


// Class FactoryGame.FGConveyorPoleStackable
// 0x0000 (0x0598 - 0x0598)
class AFGConveyorPoleStackable : public AFGBuildablePole
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGConveyorPoleStackable");
		return ptr;
	}

};


// Class FactoryGame.FGCreature
// 0x00B0 (0x0970 - 0x08C0)
class AFGCreature : public AFGCharacterBase
{
public:
	TArray<class UMaterialInstance*>                   mArachnophobiaModeMaterials;                              // 0x08C0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	bool                                               mIsArachnid;                                              // 0x08D0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EEnabled>                              mIsEnabled;                                               // 0x08D1(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x08D2(0x0006) MISSED OFFSET
	class UClass*                                      mItemToDrop;                                              // 0x08D8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGSplinePath*                               mSpline;                                                  // 0x08E0(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, SaveGame, IsPlainOldData)
	struct FScriptMulticastDelegate                    mRotationDoneDelegate;                                    // 0x08E8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<struct FMoveSpeedPair>                      mMoveSpeedData;                                           // 0x08F8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	bool                                               mShouldOptimizeMeshWhenVisible;                           // 0x0908(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsPersistent;                                            // 0x0909(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x090A(0x0006) MISSED OFFSET
	class UClass*                                      mActualAIControllerClass;                                 // 0x0910(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FTimerHandle                                mRotationTimerHandle;                                     // 0x0918(0x0008)
	struct FRotator                                    mTargetRotation;                                          // 0x0920(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0xC];                                       // 0x092C(0x000C) MISSED OFFSET
	bool                                               mCanSpawnDuringDay;                                       // 0x0938(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mCanSpawnDuringNight;                                     // 0x0939(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mMoveDuringRotation;                                      // 0x093A(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x1];                                       // 0x093B(0x0001) MISSED OFFSET
	float                                              mRotationSpeedMultiplier;                                 // 0x093C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class USceneComponent*                             mEyeLocationComponent;                                    // 0x0940(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBillboardComponent*                         mArachnophobia_Sprite;                                    // 0x0948(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UMaterialBillboardComponent*                 mArachnophobia_Material;                                  // 0x0950(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UParticleSystemComponent*                    mArachnophobia_Particle;                                  // 0x0958(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mDayTimePctCountAsNight;                                  // 0x0960(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0xC];                                       // 0x0964(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCreature");
		return ptr;
	}


	void StartRotationMovement(const struct FRotator& TargetRotation);
	void SpawnDeathItem();
	void SetPersistent(bool persist);
	void SetMoveSpeed(EMoveSpeed newMoveSpeedType);
	void PlayConsumeItemEffect(class UClass* itemDescriptor, int amount);
	void OnRep_TargetRotation();
	void OnRep_IsEnabled();
	void OnArachnophobiaModeChanged(bool isArachnophobiaMode);
	void Multicast_ConsumeItem(class UClass* itemDescriptor, int amount);
	bool IsPersistent();
	struct FRotator GetTargetRotation();
	class AFGSplinePath* GetSplinePath();
	bool GetIsEnabled();
	bool GetIsArachnid();
	float GetDayTimePctAsNight();
	TArray<class UMaterialInstance*> GetArachnophobiaModeMaterials();
	void ConfigureArachnophobiaMode(bool isArachnophobiaMode);
	void CheckRotationMovement();
	void CancelRotationMovement();
	void AiCalculateLeadTrajectory(const struct FVector& targetPos, const struct FVector& targetVelocity, const struct FVector& fromPos, float interceptorSpeed, float leadScaling, bool* isPosibleToLead, struct FVector* interceptPoint);
};


// Class FactoryGame.FGEnemy
// 0x0010 (0x0980 - 0x0970)
class AFGEnemy : public AFGCreature
{
public:
	class AActor*                                      mCurrentAggroTarget;                                      // 0x0970(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0978(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEnemy");
		return ptr;
	}


	void PerformCustomRadialAttack();
	void OnRep_CurrentAggroTarget();
	void OnCurrentAggroTargetReplicated();
	class UFGGameplayTask_Attack* GetCurrentAttackTask();
	class AActor* GetCurrentAggroTarget();
	struct FVector GetAttackLocation();
};


// Class FactoryGame.FGCrabHatcher
// 0x0010 (0x0990 - 0x0980)
class AFGCrabHatcher : public AFGEnemy
{
public:
	float                                              mThreatTimerMax;                                          // 0x0980(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0984(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCrabHatcher");
		return ptr;
	}


	void StartExpanding();
	void SpawnCrabs();
	void SetThreatNearby(bool inNearby);
	void SetDidSpawnCrabs(bool inDidSPawn);
	void SetAnimationLength(float animLength);
	void OnRep_DidSpawnCrabs();
	bool GetThreatNearby();
	bool GetDidSpawnCrabs();
};


// Class FactoryGame.FGCrashSiteDebris
// 0x0000 (0x0328 - 0x0328)
class AFGCrashSiteDebris : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCrashSiteDebris");
		return ptr;
	}

};


// Class FactoryGame.FGCrashSiteDebrisActor
// 0x0010 (0x0338 - 0x0328)
class AFGCrashSiteDebrisActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class UStaticMeshComponent*                        mMesh;                                                    // 0x0330(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCrashSiteDebrisActor");
		return ptr;
	}

};


// Class FactoryGame.FGInteractActor
// 0x0008 (0x0330 - 0x0328)
class AFGInteractActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInteractActor");
		return ptr;
	}


	void OnInteract(class AFGCharacterPlayer* byCharacter);
};


// Class FactoryGame.FGCrate
// 0x0018 (0x0348 - 0x0330)
class AFGCrate : public AFGInteractActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0330(0x0008) MISSED OFFSET
	class UFGInventoryComponent*                       mInventory;                                               // 0x0338(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	EFGCrateIconType                                   mIconType;                                                // 0x0340(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0341(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCrate");
		return ptr;
	}


	void OnRequestReprecentMarker();
	class UFGInventoryComponent* GetInventory();
	bool FilterInventoryClasses(class UClass* Object, int idx);
};


// Class FactoryGame.FGCreatureController
// 0x0000 (0x0438 - 0x0438)
class AFGCreatureController : public AAIController
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCreatureController");
		return ptr;
	}


	void StopPanic();
	void StartPanic();
	void SetEnabled(bool Enabled);
	void OnTargetPerceptionUpdated(class AActor* inActor, const struct FAIStimulus& Stimulus);
};


// Class FactoryGame.FGDriveablePawn
// 0x0040 (0x03C8 - 0x0388)
class AFGDriveablePawn : public APawn
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0388(0x0008) MISSED OFFSET
	bool                                               mShouldAttachDriver;                                      // 0x0390(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsDriverVisible;                                         // 0x0391(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x0392(0x0006) MISSED OFFSET
	struct FName                                       mDriverSeatSocket;                                        // 0x0398(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAnimSequence*                               mDriverSeatAnimation;                                     // 0x03A0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mDriverExitOffset;                                        // 0x03A8(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x03B4(0x0004) MISSED OFFSET
	class AFGCharacterPlayer*                          mDriver;                                                  // 0x03B8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mIsDriving;                                               // 0x03C0(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x03C1(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDriveablePawn");
		return ptr;
	}


	bool ShouldAttachDriver();
	void ReceiveOnDriverLeave();
	void ReceiveOnDriverEnter();
	void PlaceExitingDriver();
	void OnRep_IsDriving();
	bool IsDriving();
	bool IsDriverVisible();
	bool HasPendingDriver();
	struct FName GetDriverSeatSocket();
	class UAnimSequence* GetDriverSeatAnimation();
	struct FVector GetDriverExitOffset();
	class AFGCharacterPlayer* GetDriver();
	bool DriverLeave(bool keepDriving);
	bool DriverEnter(class AFGCharacterPlayer* Driver);
	bool CanDriverEnter(class AFGCharacterPlayer* Character);
};


// Class FactoryGame.FGCreatureSeat
// 0x0008 (0x03D0 - 0x03C8)
class AFGCreatureSeat : public AFGDriveablePawn
{
public:
	class AFGCreature*                                 mMountedCreature;                                         // 0x03C8(0x0008) (BlueprintVisible, Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCreatureSeat");
		return ptr;
	}


	class AFGCreature* GetMountedCreature();
};


// Class FactoryGame.FGCreatureSpawner
// 0x0068 (0x0390 - 0x0328)
class AFGCreatureSpawner : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class UFGCreatureSpawnerDebugComponent*            mDebugComponent;                                          // 0x0330(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBillboardComponent*                         mEditorSprite;                                            // 0x0338(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UCapsuleComponent*                           mCapsuleComponent;                                        // 0x0340(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      mCreatureClass;                                           // 0x0348(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInt32Interval                              mNumberOfCreatures;                                       // 0x0350(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mSpawnRadius;                                             // 0x0358(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mSpawnHalfHeight;                                         // 0x035C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               mIsActive;                                                // 0x0360(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0361(0x0007) MISSED OFFSET
	TArray<struct FSpawnData>                          mSpawnData;                                               // 0x0368(0x0010) (ZeroConstructor, SaveGame)
	TArray<class AFGSplinePath*>                       mSplines;                                                 // 0x0378(0x0010) (Edit, ZeroConstructor)
	int                                                mRandomSeed;                                              // 0x0388(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                mRespawnTimeIndays;                                       // 0x038C(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCreatureSpawner");
		return ptr;
	}


	void SpawnCreatures();
	bool IsSpawnerActive();
	TArray<class AFGSplinePath*> GetSplines();
	void DestroyCreatures();
	void CreatureDied(class AActor* thisActor);
	bool CalculateSpawningLocations();
};


// Class FactoryGame.FGCreatureSpawnerDebugComponent
// 0x0000 (0x00F0 - 0x00F0)
class UFGCreatureSpawnerDebugComponent : public UActorComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGCreatureSpawnerDebugComponent");
		return ptr;
	}

};


// Class FactoryGame.FGDamageOverTime
// 0x0020 (0x0048 - 0x0028)
class UFGDamageOverTime : public UObject
{
public:
	float                                              mDamageInterval;                                          // 0x0028(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDamageAmount;                                            // 0x002C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDamageClass;                                             // 0x0030(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UClass*>                              mActorFilter;                                             // 0x0038(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDamageOverTime");
		return ptr;
	}


	bool ShouldBeAppliedToActor(class UClass* dotClass, class AActor* Actor);
	float GetDamageInterval(class UClass* dotClass);
	class UClass* GetDamageClass(class UClass* dotClass);
	float GetDamageAmount(class UClass* dotClass);
};


// Class FactoryGame.FGDamageOverTimeVolume
// 0x0018 (0x0378 - 0x0360)
class AFGDamageOverTimeVolume : public AVolume
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0360(0x0008) MISSED OFFSET
	class UClass*                                      mPostProcessSettings;                                     // 0x0368(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class UFGDotComponent*                             mDotComponent;                                            // 0x0370(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnTemplate, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDamageOverTimeVolume");
		return ptr;
	}

};


// Class FactoryGame.FGDamageType
// 0x0028 (0x0068 - 0x0040)
class UFGDamageType : public UDamageType
{
public:
	class UAkAudioEvent*                               mImpactAudioEvent;                                        // 0x0040(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPlayOnDamageEvent>                    mPlayImpactAudioOn;                                       // 0x0048(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EOverrideSetting>                      mImpactAudioSetting;                                      // 0x0049(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x004A(0x0006) MISSED OFFSET
	class UParticleSystem*                             mImpactParticle;                                          // 0x0050(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPlayOnDamageEvent>                    mPlayImpactParticleOn;                                    // 0x0058(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EOverrideSetting>                      mImpactParticleSetting;                                   // 0x0059(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mShouldDamageDestructible;                                // 0x005A(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1];                                       // 0x005B(0x0001) MISSED OFFSET
	float                                              mDamageImpulseZ;                                          // 0x005C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mShouldShockEnemy;                                        // 0x0060(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0061(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDamageType");
		return ptr;
	}

};


// Class FactoryGame.FGDecorDescriptor
// 0x0008 (0x0158 - 0x0150)
class UFGDecorDescriptor : public UFGBuildingDescriptor
{
public:
	class UStaticMesh*                                 mDecorMesh;                                               // 0x0150(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDecorDescriptor");
		return ptr;
	}


	class UStaticMesh* GetDecorMesh(class UClass* inClass);
};


// Class FactoryGame.FGDecorHologram
// 0x0008 (0x03E8 - 0x03E0)
class AFGDecorHologram : public AFGBuildableHologram
{
public:
	class UStaticMesh*                                 mDecorMesh;                                               // 0x03E0(0x0008) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDecorHologram");
		return ptr;
	}

};


// Class FactoryGame.FGDestructibleActor
// 0x0028 (0x0370 - 0x0348)
class AFGDestructibleActor : public ADestructibleActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0348(0x0008) MISSED OFFSET
	class UStaticMeshComponent*                        mStaticMeshProxy;                                         // 0x0350(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	bool                                               mHasBeenFractured;                                        // 0x0358(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x17];                                      // 0x0359(0x0017) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDestructibleActor");
		return ptr;
	}


	void PlayDestructEffects();
	void OnDestructibleFractured(const struct FVector& HitPoint, const struct FVector& HitDirection);
	void Multicast_OnDestructibleFractured(const struct FVector& HitPoint, const struct FVector& HitDirection);
};


// Class FactoryGame.FGProjectile
// 0x0080 (0x03A8 - 0x0328)
class AFGProjectile : public AActor
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
	struct FProjectileData                             mProjectileData;                                          // 0x0338(0x0030) (Edit, DisableEditOnInstance, SaveGame)
	bool                                               mHasExploded;                                             // 0x0368(0x0001) (Net, ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0369(0x0003) MISSED OFFSET
	struct FVector                                     mInitialVelocity;                                         // 0x036C(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	class USphereComponent*                            mCollisionComp;                                           // 0x0378(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UProjectileMovementComponent*                mProjectileMovement;                                      // 0x0380(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	struct FVector                                     mTargetLocation;                                          // 0x0388(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mCanTriggerExplodeBySameClass;                            // 0x0394(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mExplodeAtEndOfLife;                                      // 0x0395(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x0396(0x0002) MISSED OFFSET
	class AFGPlayerController*                         mCachedPC;                                                // 0x0398(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x03A0(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGProjectile");
		return ptr;
	}


	void SetTargetLocation(const struct FVector& TargetLocation);
	void SetInitialVelocity(const struct FVector& inVelocity);
	void PlayExplosionEffects();
	void PlayAttachEffect();
	void OnRep_InitialVelocity();
	void OnRep_Exploded();
	void OnImpact(const struct FHitResult& HitResult);
	void OnBounce(const struct FHitResult& HitResult, const struct FVector& hitVelocity);
	struct FVector GetProjectileTargetLocation();
	class USphereComponent* GetCollisionSphere();
};


// Class FactoryGame.FGDestructiveProjectile
// 0x0030 (0x03D8 - 0x03A8)
class AFGDestructiveProjectile : public AFGProjectile
{
public:
	class USphereComponent*                            mDestructionCollisionComp;                                // 0x03A8(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mDestroysRelevantActors;                                  // 0x03B0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDestroysFoliage;                                         // 0x03B1(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x03B2(0x0002) MISSED OFFSET
	int                                                mMaxParticleSpawnsPerDetonation;                          // 0x03B4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x03B8(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDestructiveProjectile");
		return ptr;
	}

};


// Class FactoryGame.FGDeveloperSettings
// 0x0098 (0x00D0 - 0x0038)
class UFGDeveloperSettings : public UDeveloperSettings
{
public:
	bool                                               mGreedyFocusInPIE;                                        // 0x0038(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0039(0x0003) MISSED OFFSET
	float                                              mLowestWorldLocation;                                     // 0x003C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mHighestWorldLocation;                                    // 0x0040(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mFogOfWarUpperRangeMin;                                   // 0x0044(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mFogOfWarUpperRangeMax;                                   // 0x0048(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mFogOfWarGradientExpandValue;                             // 0x004C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	bool                                               mEnableFogOfWarRevealCalculations;                        // 0x0050(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	bool                                               mEnableFogOfWarTextureUpdates;                            // 0x0051(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	bool                                               mForceSingleThreadedCalculations;                         // 0x0052(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData01[0x5];                                       // 0x0053(0x0005) MISSED OFFSET
	struct FRuntimeFloatCurve                          mFogOfWarGradientCurve;                                   // 0x0058(0x0078) (Edit, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDeveloperSettings");
		return ptr;
	}

};


// Class FactoryGame.FGDismantleInterface
// 0x0000 (0x0028 - 0x0028)
class UFGDismantleInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDismantleInterface");
		return ptr;
	}


	void Upgrade(class AActor* newActor);
	void StopIsLookedAtForDismantle(class AFGCharacterPlayer* byCharacter);
	void StartIsLookedAtForDismantle(class AFGCharacterPlayer* byCharacter);
	void PreUpgrade();
	struct FVector GetRefundSpawnLocationAndArea(const struct FVector& aimHitLocation, float* out_radius);
	void GetDismantleRefund(TArray<struct FInventoryStack>* out_refund);
	void Dismantle();
	bool CanDismantle();
};


// Class FactoryGame.FGHotbarShortcut
// 0x0008 (0x0030 - 0x0028)
class UFGHotbarShortcut : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHotbarShortcut");
		return ptr;
	}


	bool IsValidShortcut(class AFGPlayerController* Owner);
	bool IsActive(class AFGPlayerController* Owner);
	class UTexture2D* GetDisplayImage();
	void Execute(class AFGPlayerController* Owner);
};


// Class FactoryGame.FGDismantleShortcut
// 0x0000 (0x0030 - 0x0030)
class UFGDismantleShortcut : public UFGHotbarShortcut
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDismantleShortcut");
		return ptr;
	}

};


// Class FactoryGame.FGDockableInterface
// 0x0000 (0x0028 - 0x0028)
class UFGDockableInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDockableInterface");
		return ptr;
	}


	void WasUndocked();
	void WasDocked(class AFGBuildableDockingStation* atStation);
	void OnTransferComplete();
	void OnBeginUnloadVehicle();
	void OnBeginLoadVehicle();
	class UFGInventoryComponent* GetDockInventory();
	class UFGInventoryComponent* GetDockFuelInventory();
	bool CanDock(EDockStationType atStation);
};


// Class FactoryGame.FGDotComponent
// 0x0020 (0x0260 - 0x0240)
class UFGDotComponent : public USceneComponent
{
public:
	TArray<class AActor*>                              mActorsToDamage;                                          // 0x0240(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0250(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDotComponent");
		return ptr;
	}


	void OnPrimitiveComponentExited(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	void OnPrimitiveComponentEntered(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool fromSweep, const struct FHitResult& SweepResult);
	void DamageContainingActors();
};


// Class FactoryGame.FGDropPod
// 0x0028 (0x0350 - 0x0328)
class AFGDropPod : public AActor
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0328(0x0018) MISSED OFFSET
	int                                                mAmountOfInventorySlots;                                  // 0x0340(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasBeenOpened;                                           // 0x0344(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0345(0x0003) MISSED OFFSET
	class UFGInventoryComponent*                       mInventory;                                               // 0x0348(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDropPod");
		return ptr;
	}


	void RollLoot();
	struct FDropPackage RollDropPackage(TArray<class UClass*> includedItems);
	void Open();
	void OnRep_HasBeenOpened();
	void OnOpened();
	bool HasBeenOpened();
	class UFGInventoryComponent* GetLootInventory();
	void GenerateDropPodInventory(TArray<class UClass*> includedItems, int numItemsCreated);
};


// Class FactoryGame.FGSettings
// 0x0000 (0x0028 - 0x0028)
class UFGSettings : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSettings");
		return ptr;
	}

};


// Class FactoryGame.FGDropPodSettings
// 0x0010 (0x0038 - 0x0028)
class UFGDropPodSettings : public UFGSettings
{
public:
	TArray<struct FDropPackage>                        mDropTable;                                               // 0x0028(0x0010) (Edit, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDropPodSettings");
		return ptr;
	}


	struct FDropPackage GetRandomDropPackage(class UWorld* World);
};


// Class FactoryGame.FGDynamicHeightFogUpdater
// 0x0010 (0x0038 - 0x0028)
class UFGDynamicHeightFogUpdater : public UObject
{
public:
	TArray<class UWorld*>                              mActiveWorlds;                                            // 0x0028(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDynamicHeightFogUpdater");
		return ptr;
	}

};


// Class FactoryGame.FGEnemyController
// 0x00B8 (0x04F0 - 0x0438)
class AFGEnemyController : public AFGCreatureController
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0438(0x0008) MISSED OFFSET
	float                                              mUpdateAggroInterval;                                     // 0x0440(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mTimeToLoseAllAggro;                                      // 0x0444(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAggroTargetsAggroMax;                                    // 0x0448(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mAggroBaseWeight;                                         // 0x044C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAggroAggroWeight;                                        // 0x0450(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAggroDistanceWeight;                                     // 0x0454(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FAggroEntry>                         mAggroEntries;                                            // 0x0458(0x0010) (BlueprintVisible, ZeroConstructor)
	TArray<struct FAggroEntry>                         mSortedAggroEntries;                                      // 0x0468(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
	float                                              mTargetSwitchFactor;                                      // 0x0478(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDefaultIgnoreCooldown;                                   // 0x047C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mStaticIgnoreCooldown;                                    // 0x0480(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0484(0x0004) MISSED OFFSET
	class UCurveFloat*                                 mAggroDistanceCurve;                                      // 0x0488(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mGainAggroThreshold;                                      // 0x0490(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLoseAggroThreshold;                                      // 0x0494(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TScriptInterface<class UFGAggroTargetInterface>    mCurrentAggroTarget;                                      // 0x0498(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x10];                                      // 0x04A8(0x0010) MISSED OFFSET
	TArray<class UClass*>                              mAttackPattern;                                           // 0x04B8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData03[0x8];                                       // 0x04C8(0x0008) MISSED OFFSET
	TArray<TSoftObjectPtr<class UClass>>               mIgnoredAggroTargetClasses;                               // 0x04D0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData04[0xC];                                       // 0x04E0(0x000C) MISSED OFFSET
	float                                              mPanicIgnoreTime;                                         // 0x04EC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEnemyController");
		return ptr;
	}


	void UpdateAttackPattern();
	void UpdateAggroTargets(float dt, bool fullCheck);
	void UpdateAggroAndFindAndAssignTarget();
	bool ShouldAddAggroTarget(const TScriptInterface<class UFGAggroTargetInterface>& aggroTargetInterface);
	void SetCurrentAggroTarget(const TScriptInterface<class UFGAggroTargetInterface>& newAggroTargetInterface);
	void ResetLastValidTargetLocation();
	void RemoveInvalidAggroTargets();
	void OnPawnTakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void OnAggroTargetUpdated();
	void OnAggroTargetLost(class AActor* lostActor);
	bool IsOnIgnoreList(const TScriptInterface<class UFGAggroTargetInterface>& aggroTargetInterface);
	struct FVector GetTargetLastValidLocation();
	float GetTargetingDesireFromAggroEntry(const struct FAggroEntry& outTarget);
	float GetTargetingDesire(const TScriptInterface<class UFGAggroTargetInterface>& aggroTarget);
	TScriptInterface<class UFGAggroTargetInterface> GetMostDesirableAggroTarget();
	class UClass* GetCurrentAttackFromPattern();
	int GetAttackPatternIndex();
	float GetAggroThreshold();
	void GatherAggroTargets();
	void FindAndAssignTarget();
	void ClearAllAggroTargetsAndUpdate();
	bool CanSeeActor(class AActor* Target);
	void AggroTargetRemoved(const TScriptInterface<class UFGAggroTargetInterface>& aggroTarget);
	void AggroTargetAdded(const TScriptInterface<class UFGAggroTargetInterface>& aggroTarget);
	void AddToAggroByTarget(const TScriptInterface<class UFGAggroTargetInterface>& Target, float Damage);
};


// Class FactoryGame.FGEnvironmentSettings
// 0x0008 (0x0030 - 0x0028)
class UFGEnvironmentSettings : public UFGSettings
{
public:
	class UMaterialParameterCollection*                mWorldBoundsParameters;                                   // 0x0028(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEnvironmentSettings");
		return ptr;
	}

};


// Class FactoryGame.FGEnvQueryGenerator_ForAngle
// 0x00C8 (0x0148 - 0x0080)
class UFGEnvQueryGenerator_ForAngle : public UEnvQueryGenerator_ProjectedPoints
{
public:
	struct FAIDataProviderFloatValue                   mDistance;                                                // 0x0080(0x0030) (Edit, DisableEditOnInstance)
	struct FAIDataProviderFloatValue                   mAngle;                                                   // 0x00B0(0x0030) (Edit, DisableEditOnInstance)
	struct FAIDataProviderFloatValue                   mStepSize;                                                // 0x00E0(0x0030) (Edit, DisableEditOnInstance)
	struct FAIDataProviderBoolValue                    mGenerateMirroredPoints;                                  // 0x0110(0x0030) (Edit, DisableEditOnInstance)
	class UClass*                                      mCenterActor;                                             // 0x0140(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEnvQueryGenerator_ForAngle");
		return ptr;
	}

};


// Class FactoryGame.FGEnvQueryTest_ItemDescription
// 0x0008 (0x01C8 - 0x01C0)
class UFGEnvQueryTest_ItemDescription : public UEnvQueryTest
{
public:
	class UClass*                                      mItemDescriptorClass;                                     // 0x01C0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEnvQueryTest_ItemDescription");
		return ptr;
	}

};


// Class FactoryGame.FGEquipmentChild
// 0x0010 (0x0338 - 0x0328)
class AFGEquipmentChild : public AActor
{
public:
	class AFGEquipment*                                mParentEquipment;                                         // 0x0328(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	struct FName                                       mAttachSocket;                                            // 0x0330(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEquipmentChild");
		return ptr;
	}


	void OnUnEquip();
	void OnEquip(class AFGCharacterPlayer* Character);
	struct FTransform GetAttachSocketTransform();
};


// Class FactoryGame.FGEquipmentStunSpear
// 0x0030 (0x03F0 - 0x03C0)
class AFGEquipmentStunSpear : public AFGEquipment
{
public:
	class USphereComponent*                            mCollisionComp;                                           // 0x03C0(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UClass*                                      mDamageTypeClass;                                         // 0x03C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x03D0(0x0004) MISSED OFFSET
	float                                              mSecondSwingMaxTime;                                      // 0x03D4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x03D8(0x0008) MISSED OFFSET
	float                                              mSecondSwingCooldDownTime;                                // 0x03E0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mDamage;                                                  // 0x03E4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAttackDistance;                                          // 0x03E8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x03EC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEquipmentStunSpear");
		return ptr;
	}


	void Server_ShockEnemy();
	void PlayStunEffects();
	void OnHitTarget();
	bool GetShouldPlaySecondSwing();
	void DoAttack();
};


// Class FactoryGame.FGErrorMessage
// 0x0020 (0x0048 - 0x0028)
class UFGErrorMessage : public UObject
{
public:
	struct FText                                       mErrorMessage;                                            // 0x0028(0x0028) (Edit, DisableEditOnInstance)
	TEnumAsByte<EErrorResponse>                        mErrorResponse;                                           // 0x0040(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0041(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGErrorMessage");
		return ptr;
	}


	TEnumAsByte<EErrorResponse> GetErrorResponse();
	struct FText GetErrorMessage();
};


// Class FactoryGame.FGExplosiveDestroyableInterface
// 0x0000 (0x0028 - 0x0028)
class UFGExplosiveDestroyableInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGExplosiveDestroyableInterface");
		return ptr;
	}


	bool NotifyExploded();
	class UParticleSystem* GetDestroyEffect();
};


// Class FactoryGame.FGDynamicExponentialFogVolume
// 0x18A0 (0x1C00 - 0x0360)
class AFGDynamicExponentialFogVolume : public AVolume
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0360(0x0010) MISSED OFFSET
	float                                              mPriority;                                                // 0x0370(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	float                                              mBlendDistance;                                           // 0x0374(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	struct FRuntimeFloatCurve                          mFogHeight;                                               // 0x0378(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mFogDensity;                                              // 0x03F0(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mFogInscatteringColor;                                    // 0x0468(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mFullyDirectionalInscatteringColorDistance;               // 0x0630(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mNonDirectionalInscatteringColorDistance;                 // 0x06A8(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mDirectionalInscatteringExponent;                         // 0x0720(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mDirectionalInscatteringStartDistance;                    // 0x0798(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mDirectionalInscatteringColor;                            // 0x0810(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mFogHeightFalloff;                                        // 0x09D8(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mFogMaxOpacity;                                           // 0x0A50(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mStartDistance;                                           // 0x0AC8(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mFogCutoffDistance;                                       // 0x0B40(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	bool                                               mOverrideHorizonColor;                                    // 0x0BB8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0BB9(0x0007) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mHorizonColorCurve;                                       // 0x0BC0(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	bool                                               mOverrideZenithColor;                                     // 0x0D88(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0D89(0x0007) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mZenithColorCurve;                                        // 0x0D90(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	bool                                               mOverrideCloudColor;                                      // 0x0F58(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0F59(0x0007) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mCloudColorCurve;                                         // 0x0F60(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	bool                                               mOverrideCloudOpacity;                                    // 0x1128(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x1129(0x0007) MISSED OFFSET
	struct FRuntimeFloatCurve                          mCloudOpacity;                                            // 0x1130(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	float                                              mBlendWeight;                                             // 0x11A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      mEnableSaturation : 1;                                    // 0x11AC(0x0001) (Edit)
	unsigned char                                      UnknownData05[0x3];                                       // 0x11AD(0x0003) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mSaturation;                                              // 0x11B0(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      mEnableContrast : 1;                                      // 0x1378(0x0001) (Edit)
	unsigned char                                      UnknownData06[0x7];                                       // 0x1379(0x0007) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mContrast;                                                // 0x1380(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      mEnableGain : 1;                                          // 0x1548(0x0001) (Edit)
	unsigned char                                      UnknownData07[0x7];                                       // 0x1549(0x0007) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mGain;                                                    // 0x1550(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData08[0x4E8];                                     // 0x1718(0x04E8) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGDynamicExponentialFogVolume");
		return ptr;
	}

};


// Class FactoryGame.FGFactoryBuildingHologram
// 0x0008 (0x03E8 - 0x03E0)
class AFGFactoryBuildingHologram : public AFGBuildableHologram
{
public:
	class UStaticMeshComponent*                        mBuildingMesh;                                            // 0x03E0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFactoryBuildingHologram");
		return ptr;
	}

};


// Class FactoryGame.FGFactoryConnectionComponent
// 0x0030 (0x0270 - 0x0240)
class UFGFactoryConnectionComponent : public UFGConnectionComponent
{
public:
	EFactoryConnectionConnector                        mConnector;                                               // 0x0240(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	EFactoryConnectionDirection                        mDirection;                                               // 0x0241(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0242(0x0002) MISSED OFFSET
	float                                              mConnectorClearance;                                      // 0x0244(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGFactoryConnectionComponent*               mConnectedComponent;                                      // 0x0248(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	bool                                               mHasConnectedComponent;                                   // 0x0250(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0251(0x0007) MISSED OFFSET
	class UFGInventoryComponent*                       mConnectionInventory;                                     // 0x0258(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0260(0x0008) MISSED OFFSET
	unsigned char                                      mForwardPeekAndGrabToBuildable : 1;                       // 0x0268(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0269(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFactoryConnectionComponent");
		return ptr;
	}


	bool IsConnected();
	class UFGInventoryComponent* GetInventory();
	EFactoryConnectionDirection GetDirection();
	float GetConnectorClearance();
	EFactoryConnectionConnector GetConnector();
	bool Factory_PeekOutput(class UClass* Type, TArray<struct FInventoryItem>* out_items);
	bool Factory_Internal_PeekOutputInventory(class UClass* Type, TArray<struct FInventoryItem>* out_items);
	bool Factory_Internal_GrabOutputInventory(class UClass* Type, struct FInventoryItem* out_item);
	bool Factory_GrabOutput(class UClass* Type, struct FInventoryItem* out_item, float* out_OffsetBeyond);
};


// Class FactoryGame.FGFactoryLegsComponent
// 0x0060 (0x02A0 - 0x0240)
class UFGFactoryLegsComponent : public USceneComponent
{
public:
	TArray<struct FName>                               mLegSocketNames;                                          // 0x0240(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UStaticMesh*                                 mLegMeshOverride;                                         // 0x0250(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mFootMeshOverride;                                        // 0x0258(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxLegLengthOverride;                                    // 0x0260(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0264(0x0004) MISSED OFFSET
	TArray<class UStaticMeshComponent*>                mLegMeshComponents;                                       // 0x0268(0x0010) (ExportObject, ZeroConstructor, Transient)
	TArray<class UStaticMeshComponent*>                mFootMeshComponents;                                      // 0x0278(0x0010) (ExportObject, ZeroConstructor, Transient)
	TArray<struct FFeetOffset>                         mCachedFeetOffset;                                        // 0x0288(0x0010) (Net, ZeroConstructor, SaveGame)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0298(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFactoryLegsComponent");
		return ptr;
	}


	TArray<class UStaticMeshComponent*> GetLegMeshComponents();
	TArray<class UStaticMeshComponent*> GetFootMeshComponents();
};


// Class FactoryGame.FGFactorySettings
// 0x0110 (0x0138 - 0x0028)
class UFGFactorySettings : public UFGSettings
{
public:
	class UMaterialInstance*                           mDefaultValidPlacementMaterial;                           // 0x0028(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mDefaultValidPlacementMaterialSimplified;                 // 0x0030(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mDefaultInvalidPlacementMaterial;                         // 0x0038(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mDefaultInputConnectionMaterial;                          // 0x0040(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mDefaultOutputConnectionMaterial;                         // 0x0048(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mDefaultPowerConnectionMaterial;                          // 0x0050(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mDefaultConveyorConnectionFrameMesh;                      // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mDefaultConveyorConnectionArrowMesh;                      // 0x0060(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mDefaultPowerConnectionMesh;                              // 0x0068(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mClearanceMesh;                                           // 0x0070(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mClearanceMaterial;                                       // 0x0078(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mHologramLoopSound;                                       // 0x0080(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mHologramSnapSound;                                       // 0x0088(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mBuildGuideMesh;                                          // 0x0090(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mBuildGuideMaterial;                                      // 0x0098(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mConveyorBuildGuideMaterial;                              // 0x00A0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mInventoryDropCrate;                                      // 0x00A8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UAkAudioEvent*>                       mConstructionSounds;                                      // 0x00B0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UAkAudioEvent*>                       mDismantleSounds;                                         // 0x00C0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UClass*                                      mBuildEffect;                                             // 0x00D0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDismantleEffect;                                         // 0x00D8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInterface*                          mDismantlePendingMaterial;                                // 0x00E0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mBuildGunClass;                                           // 0x00E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mResourceScannerClass;                                    // 0x00F0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mResourceMinerClass;                                      // 0x00F8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mLegMesh;                                                 // 0x0100(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mFootMesh;                                                // 0x0108(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxFeetLength;                                           // 0x0110(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0114(0x0004) MISSED OFFSET
	class UClass*                                      mDismantleShortcutClass;                                  // 0x0118(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mRecipeShortcutClass;                                     // 0x0120(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FName>                               mShortcutMap;                                             // 0x0128(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFactorySettings");
		return ptr;
	}


	class UAkAudioEvent* GetRandomDismantleSound();
	class UAkAudioEvent* GetRandomConstructionSound();
};


// Class FactoryGame.FGFAnimInstanceFactory
// 0x0650 (0x09B0 - 0x0360)
class UFGFAnimInstanceFactory : public UAnimInstance
{
public:
	struct FAnimInstanceProxyFactory                   mProxy;                                                   // 0x0360(0x0620) (BlueprintVisible, BlueprintReadOnly, Transient)
	bool                                               mUseRampUp;                                               // 0x0980(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0981(0x0003) MISSED OFFSET
	float                                              mRampUpTime;                                              // 0x0984(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRampDownTime;                                            // 0x0988(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDefaultCycleTime;                                        // 0x098C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mSoundSpeedRTPC;                                          // 0x0990(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSoundSpeedRTPCInterval;                                  // 0x0998(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSoundSpeedAccumulator;                                   // 0x099C(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsGenerator;                                             // 0x09A0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x09A1(0x0003) MISSED OFFSET
	float                                              mSoundSpeedRTPCMinValue;                                  // 0x09A4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSoundSpeedRTPCMaxValue;                                  // 0x09A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x09AC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFAnimInstanceFactory");
		return ptr;
	}

};


// Class FactoryGame.FGFloorHologram
// 0x0000 (0x03E8 - 0x03E8)
class AFGFloorHologram : public AFGFactoryBuildingHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFloorHologram");
		return ptr;
	}

};


// Class FactoryGame.FGFluffActor
// 0x0000 (0x0328 - 0x0328)
class AFGFluffActor : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFluffActor");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier_RemovableByBuildings
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier_RemovableByBuildings : public UFGFoliageIdentifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier_RemovableByBuildings");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier_Pickupable
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier_Pickupable : public UFGFoliageIdentifier_RemovableByBuildings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier_Pickupable");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier_Chainsawable
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier_Chainsawable : public UFGFoliageIdentifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier_Chainsawable");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier_ChainsawableXmasTree
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier_ChainsawableXmasTree : public UFGFoliageIdentifier_Chainsawable
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier_ChainsawableXmasTree");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier_VehicleDestroyable
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier_VehicleDestroyable : public UFGFoliageIdentifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier_VehicleDestroyable");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageIdentifier_ExplosiveDestroyable
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageIdentifier_ExplosiveDestroyable : public UFGFoliageIdentifier
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageIdentifier_ExplosiveDestroyable");
		return ptr;
	}

};


// Class FactoryGame.FGFoliageLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGFoliageLibrary : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageLibrary");
		return ptr;
	}

};


// Class FactoryGame.FGFoliagePickup
// 0x0020 (0x0348 - 0x0328)
class AFGFoliagePickup : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class UStaticMesh*                                 mPickupMesh;                                              // 0x0330(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0338(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliagePickup");
		return ptr;
	}


	void Server_PickupWithTransform(class AFGCharacterPlayer* byCharacter, class AFGFoliageRemoval* foliageRemoval, const struct FTransform& withTransform);
	void PlayPickupEffect(class UFGFoliageResourceUserData* foliageUserData, const struct FVector& atLocation);
	void BroadcastPickup(class UStaticMesh* fromStaticMesh, const struct FVector& atLocation);
};


// Class FactoryGame.FGFoliageRemoval
// 0x0118 (0x0440 - 0x0328)
class AFGFoliageRemoval : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	struct FRemovedInstanceArray                       mRemovedInstances;                                        // 0x0330(0x00C8) (Net, SaveGame)
	unsigned char                                      UnknownData01[0x10];                                      // 0x03F8(0x0010) MISSED OFFSET
	class UHierarchicalInstancedStaticMeshComponent*   mMeshComponent;                                           // 0x0408(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       mLevelName;                                               // 0x0410(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	struct FName                                       mFoliageTypeName;                                         // 0x0418(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	struct FBox                                        mLevelBounds;                                             // 0x0420(0x001C) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x043C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageRemoval");
		return ptr;
	}


	bool RemoveInstance(const struct FTransform& foliageTransform, bool localSpace, int InstanceId);
	void RegisterWithSubsystem();
};


// Class FactoryGame.FGFoliageRemovalSubsystem
// 0x0090 (0x03B8 - 0x0328)
class AFGFoliageRemovalSubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x90];                                      // 0x0328(0x0090) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageRemovalSubsystem");
		return ptr;
	}


	void OnLevelRemovedFromWorld(class ULevel* inLevel, class UWorld* inWorld);
	void OnLevelAddedToWorld(class ULevel* inLevel, class UWorld* inWorld);
	bool HasIdentifier(class UHierarchicalInstancedStaticMeshComponent* component, class UClass* foliageIdentifier);
	bool GetLookAtFoliage(const struct FVector& ViewLocation, const struct FVector& endViewLocation, class UClass* foliageIdentifier, class UHierarchicalInstancedStaticMeshComponent** out_component, int* out_instanceId, struct FVector* out_instanceLocation);
	bool GetFoliageWithinRadius(const struct FVector& Location, float Radius, bool isLocalSpace, TArray<int>* out_instanceArray, TArray<struct FVector>* out_locationArray, TArray<class UHierarchicalInstancedStaticMeshComponent*>* out_componentArray);
	class AFGFoliageRemovalSubsystem* GetFoliageRemovalSubsystem(class UObject* WorldContext);
	class AFGFoliageRemoval* GetFoliageRemovalActor(class UHierarchicalInstancedStaticMeshComponent* fromComponent);
	bool GetClosestFoliageForComponent(const struct FVector& Location, float MaxDistance, class UHierarchicalInstancedStaticMeshComponent* component, bool isLocalSpace, int* out_instanceId, struct FVector* out_instanceLocation);
	void GetClosestFoliageArrayForComponent(TArray<struct FVector> Locations, float MaxDistance, class UHierarchicalInstancedStaticMeshComponent* component, bool isLocalSpace, TArray<int>* out_instanceArray);
	bool GetClosestFoliage(const struct FVector& Location, float MaxDistance, class UClass* foliageIdentifier, bool isLocalSpace, class UHierarchicalInstancedStaticMeshComponent** out_component, int* out_instanceId, struct FVector* out_instanceLocation);
};


// Class FactoryGame.FGFoliageResourceUserData
// 0x0050 (0x0078 - 0x0028)
class UFGFoliageResourceUserData : public UAssetUserData
{
public:
	TArray<struct FItemDropWithChance>                 mPickupItems;                                             // 0x0028(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	class UAkAudioEvent*                               mPickupEvent;                                             // 0x0038(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mPickupEffect;                                            // 0x0040(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mVehicleDestroyedEvent;                                   // 0x0048(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mVehicleDestroyedEffect;                                  // 0x0050(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mExplosionDestroyedEffect;                                // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mFXPriority;                                              // 0x0060(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0064(0x0004) MISSED OFFSET
	TArray<class UClass*>                              mFoliageIdentifiers;                                      // 0x0068(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoliageResourceUserData");
		return ptr;
	}

};


// Class FactoryGame.FGFoundationHologram
// 0x0010 (0x03F8 - 0x03E8)
class AFGFoundationHologram : public AFGFactoryBuildingHologram
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x03E8(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoundationHologram");
		return ptr;
	}

};


// Class FactoryGame.FGFoundationSubsystem
// 0x0060 (0x0388 - 0x0328)
class AFGFoundationSubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
	TMap<int, struct FBuilding>                        mBuildings;                                               // 0x0338(0x0050) (ZeroConstructor, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFoundationSubsystem");
		return ptr;
	}

};


// Class FactoryGame.FGVehicle
// 0x0110 (0x04D8 - 0x03C8)
class AFGVehicle : public AFGDriveablePawn
{
public:
	unsigned char                                      UnknownData00[0x28];                                      // 0x03C8(0x0028) MISSED OFFSET
	struct FText                                       mDisplayName;                                             // 0x03F0(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	struct FText                                       mDescription;                                             // 0x0408(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	class UClass*                                      mHologramClass;                                           // 0x0420(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class USkeletalMeshComponent*                      mMesh;                                                    // 0x0428(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UFGHealthComponent*                          mHealthComponent;                                         // 0x0430(0x0008) (Edit, ExportObject, Net, ZeroConstructor, EditConst, InstancedReference, SaveGame, IsPlainOldData)
	TArray<struct FVector>                             mDisabledByWaterLocations;                                // 0x0438(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0448(0x0008) MISSED OFFSET
	TArray<struct FItemAmount>                         mDismantleRefund;                                         // 0x0450(0x0010) (ZeroConstructor, SaveGame)
	struct FLinearColor                                mPrimaryColor;                                            // 0x0460(0x0010) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	struct FLinearColor                                mSecondaryColor;                                          // 0x0470(0x0010) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsSelfDriving;                                           // 0x0480(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0481(0x0007) MISSED OFFSET
	class AAIController*                               mSelfDrivingController;                                   // 0x0488(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<struct FVehiclePhysicsData>                 mStoredPhysicsData;                                       // 0x0490(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData03[0x10];                                      // 0x04A0(0x0010) MISSED OFFSET
	class UAkAudioEvent*                               mConstructSound;                                          // 0x04B0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      mIsDestructible : 1;                                      // 0x04B8(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData04 : 1;                                        // 0x04B8(0x0001)
	unsigned char                                      mIsSubmergedInWater : 1;                                  // 0x04B8(0x0001) (Net)
	unsigned char                                      UnknownData05[0xB];                                       // 0x04B9(0x000B) MISSED OFFSET
	float                                              mSubmergedAngularDamping;                                 // 0x04C4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSubmergedLinearDamping;                                  // 0x04C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSubmergedBouyantForce;                                   // 0x04CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mGasDamageType;                                           // 0x04D0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVehicle");
		return ptr;
	}


	void UpdatePhysicsVolume(class APhysicsVolume* PhysicsVolume);
	bool SelfDriverEnter(class AAIController* AI);
	void ReceiveOnVehicleStartup();
	void ReceiveOnVehicleShutDown();
	void ReceiveDied(class AActor* thisActor);
	void OnTakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void OnRep_SecondaryColor();
	void OnRep_PrimaryColor();
	void NotifyOnTakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void KickAllPlayers();
	bool IsSelfDriving();
	bool IsDestructible();
	bool HasAnyPassengerSeatAvailable();
	class UFGHealthComponent* GetHealthComponent();
	void GetDismantleBlueprintReturns(TArray<struct FInventoryStack>* out_returns);
	void Died(class AActor* thisActor);
	bool CanSelfDriverEnter(class AAIController* AI);
};


// Class FactoryGame.FGRailroadVehicle
// 0x0040 (0x0518 - 0x04D8)
class AFGRailroadVehicle : public AFGVehicle
{
public:
	class AFGTrain*                                    mTrain;                                                   // 0x04D8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mLength;                                                  // 0x04E0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x04E4(0x0004) MISSED OFFSET
	class AFGBuildableTrainPlatform*                   mDockedAtPlatform;                                        // 0x04E8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	TWeakObjectPtr<class AFGRailroadVehicle>           mCoupledVehicles[0x2];                                    // 0x04F0(0x0008) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsOrientationReversed;                                   // 0x0500(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0501(0x0003) MISSED OFFSET
	struct FRailroadTrackPosition                      mTrackPosition;                                           // 0x0504(0x0010) (SaveGame)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0514(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadVehicle");
		return ptr;
	}


	bool IsOrientationReversed();
	bool IsCoupledAt(ERailroadVehicleCoupler coupler);
	class AFGTrain* GetTrain();
	struct FRailroadTrackPosition GetTrackPosition();
	int GetTrackGraphID();
	class UFGRailroadVehicleMovementComponent* GetRailroadVehicleMovementComponent();
	float GetLength();
	class AFGRailroadVehicle* GetCoupledVehicleAt(ERailroadVehicleCoupler coupler);
};


// Class FactoryGame.FGFreightWagon
// 0x0040 (0x0558 - 0x0518)
class AFGFreightWagon : public AFGRailroadVehicle
{
public:
	TArray<class AFGCharacterPlayer*>                  mLaunchedCharacters;                                      // 0x0518(0x0010) (ZeroConstructor)
	class UFGRailroadVehicleMovementComponent*         mVehicleMovement;                                         // 0x0528(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       mStorageInventory;                                        // 0x0530(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	int                                                mInventorySize;                                           // 0x0538(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x053C(0x0004) MISSED OFFSET
	class UStaticMeshComponent*                        mCargoMeshComponent;                                      // 0x0540(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mLaunchCharacterScalar;                                   // 0x0548(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x054C(0x0004) MISSED OFFSET
	class UBoxComponent*                               mCargoOverlapCollision;                                   // 0x0550(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFreightWagon");
		return ptr;
	}


	void OnItemRemovedFromFreight(class UClass* ItemClass, int numRemoved);
	void OnItemAddedToFreight(class UClass* ItemClass, int numAdded);
	void InitializeInventoryComponent();
	float GetFreightInventoryFilledPercent();
	class UFGInventoryComponent* GetFreightInventory();
};


// Class FactoryGame.FGGameEngine
// 0x0028 (0x0D20 - 0x0CF8)
class UFGGameEngine : public UGameEngine
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0CF8(0x0008) MISSED OFFSET
	struct FFGEngineCommon                             mEngineCommonImp;                                         // 0x0D00(0x0020)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameEngine");
		return ptr;
	}

};


// Class FactoryGame.FGGameInstance
// 0x0158 (0x01F8 - 0x00A0)
class UFGGameInstance : public UGameInstance
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x00A0(0x0008) MISSED OFFSET
	class UFGSaveSystem*                               mSaveSystem;                                              // 0x00A8(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FScriptMulticastDelegate                    mOnNewError;                                              // 0x00B0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	class UAnalyticsService*                           mAnalyticsService;                                        // 0x00C0(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UFGErrorMessage*>                     mErrorList;                                               // 0x00C8(0x0010) (ZeroConstructor)
	struct FOnJoinSessionData                          mJoinSessionData;                                         // 0x00D8(0x00C8)
	unsigned char                                      UnknownData01[0x10];                                      // 0x01A0(0x0010) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnNatTypeUpdated;                                        // 0x01B0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData02[0x10];                                      // 0x01C0(0x0010) MISSED OFFSET
	class UEOSManager*                                 mCachedEOSManager;                                        // 0x01D0(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<struct FFGModPackage>                       ModPackages;                                              // 0x01D8(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
	class UFGMusicManager*                             mMusicManager;                                            // 0x01E8(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x01F0(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameInstance");
		return ptr;
	}


	void SetSkipOnboarding(bool doSkip);
	void SetHasSeenAlphaInfoScreen(bool hasSeen);
	void PushError(class UObject* WorldContext, class UClass* errorMessage);
	class UFGErrorMessage* PeekNextError(class UObject* WorldContext);
	bool HasPlayerSeenAlphaInfoScreen();
	bool GetSkipOnboarding();
	class UFGErrorMessage* GetNextError(class UObject* WorldContext);
	class UAnalyticsService* GetGameAnalyticsService(class UObject* WorldContext);
	void GetFGUGC(class UClass* WeaponClass, class UClass* EnemyClass, class UClass* BossClass, class UClass* PlayerPawnClass);
	bool FindModPackages();
};


// Class FactoryGame.FGGameMode
// 0x00A8 (0x04B8 - 0x0410)
class AFGGameMode : public AGameMode
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0410(0x0008) MISSED OFFSET
	class UFGSaveSession*                              mSaveSession;                                             // 0x0418(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x30];                                      // 0x0420(0x0030) MISSED OFFSET
	unsigned char                                      mLastAutosaveId;                                          // 0x0450(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0451(0x0003) MISSED OFFSET
	int                                                mSessionId;                                               // 0x0454(0x0004) (ZeroConstructor, SaveGame, Deprecated, IsPlainOldData)
	class FString                                      mSessionIDString;                                         // 0x0458(0x0010) (ZeroConstructor, SaveGame, Deprecated)
	class FString                                      mSaveSessionName;                                         // 0x0468(0x0010) (ZeroConstructor, SaveGame)
	unsigned char                                      UnknownData03[0x8];                                       // 0x0478(0x0008) MISSED OFFSET
	struct FName                                       mStartingPointTagName;                                    // 0x0480(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	struct FName                                       mDebugStartingPointTagName;                               // 0x0488(0x0008) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsMainMenu;                                              // 0x0490(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x0491(0x0007) MISSED OFFSET
	TArray<struct FSoftClassPath>                      mDefaultRemoteCallObjectsClassNames;                      // 0x0498(0x0010) (ZeroConstructor, Config)
	unsigned char                                      UnknownData05[0x10];                                      // 0x04A8(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameMode");
		return ptr;
	}


	void TriggerWorldSave(const class FString& saveGameName);
	void TriggerBundledWorldSave(const class FString& saveGameName);
	bool RegisterRemoteCallObjectClass(class UClass* inClass);
	void KickPlayer(class APlayerState* ps);
};


// Class FactoryGame.FGGamePhaseManager
// 0x0040 (0x0368 - 0x0328)
class AFGGamePhaseManager : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	TEnumAsByte<EGamePhase>                            mGamePhase;                                               // 0x0330(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0331(0x0007) MISSED OFFSET
	TArray<struct FPhaseTierInfo>                      mGamePhaseTierInfo;                                       // 0x0338(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FPhaseCost>                          mGamePhaseCosts;                                          // 0x0348(0x0010) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame)
	struct FScriptMulticastDelegate                    mOnGamePhaseChanged;                                      // 0x0358(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGamePhaseManager");
		return ptr;
	}


	void SetGamePhase(TEnumAsByte<EGamePhase> newPhase);
	int PayOffOnGamePhase(const struct FItemAmount& payOff, TEnumAsByte<EGamePhase> gamePhase);
	void OnRep_GamePhase();
	struct FText GetGamePhaseName(TEnumAsByte<EGamePhase> gamePhase);
	TEnumAsByte<EGamePhase> GetGamePhaseForTechTier(int techTier);
	TEnumAsByte<EGamePhase> GetGamePhaseForSchematic(class UClass* inSchematic);
	TEnumAsByte<EGamePhase> GetGamePhase();
	void GetCostForGamePhase(TEnumAsByte<EGamePhase> gamePhase, TArray<struct FItemAmount>* out_cost);
	void GetBaseCostForGamePhase(TEnumAsByte<EGamePhase> gamePhase, TArray<struct FItemAmount>* out_cost);
	class AFGGamePhaseManager* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGameplayTaskResource_Attack
// 0x0000 (0x0038 - 0x0038)
class UFGameplayTaskResource_Attack : public UGameplayTaskResource
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGameplayTaskResource_Attack");
		return ptr;
	}

};


// Class FactoryGame.FGGameplayTask_Base
// 0x0008 (0x0070 - 0x0068)
class UFGGameplayTask_Base : public UGameplayTask
{
public:
	class AFGEnemy*                                    mCachedPawn;                                              // 0x0068(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameplayTask_Base");
		return ptr;
	}

};


// Class FactoryGame.FGGameplayTask_Attack
// 0x0008 (0x0078 - 0x0070)
class UFGGameplayTask_Attack : public UFGGameplayTask_Base
{
public:
	class UClass*                                      mAttackClass;                                             // 0x0070(0x0008) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameplayTask_Attack");
		return ptr;
	}


	class UClass* GetAttackClass();
};


// Class FactoryGame.FGGameplayTask_AttackJump
// 0x0038 (0x00B0 - 0x0078)
class UFGGameplayTask_AttackJump : public UFGGameplayTask_Attack
{
public:
	struct FScriptMulticastDelegate                    mOnJumpAttackFinished;                                    // 0x0078(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnJumpAttackFailed;                                      // 0x0088(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0098(0x0010) MISSED OFFSET
	bool                                               mDoJump;                                                  // 0x00A8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x00A9(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameplayTask_AttackJump");
		return ptr;
	}


	class UFGGameplayTask_AttackJump* StartJump(class AFGEnemy* Enemy, class UClass* attackClass, bool StartJump);
	void OnMontageEnded(class UAnimMontage* Montage, bool interrupted);
	void OnLandedCallback(const struct FHitResult& Hit);
};


// Class FactoryGame.FGGameplayTask_AttackMelee
// 0x0050 (0x00C8 - 0x0078)
class UFGGameplayTask_AttackMelee : public UFGGameplayTask_Attack
{
public:
	struct FScriptMulticastDelegate                    mOnAttackFinished;                                        // 0x0078(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnAttackFailed;                                          // 0x0088(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TScriptInterface<class UFGAggroTargetInterface>    mAttackTarget;                                            // 0x0098(0x0010) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x20];                                      // 0x00A8(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameplayTask_AttackMelee");
		return ptr;
	}


	void OnMontageEnded(class UAnimMontage* Montage, bool interrupted);
	void OnMontageBlendingOut(class UAnimMontage* Montage, bool interrupted);
	class UFGGameplayTask_AttackMelee* Attack(class AFGEnemy* Enemy, const TScriptInterface<class UFGAggroTargetInterface>& attackTarget, class UClass* attackClass);
};


// Class FactoryGame.FGGameSession
// 0x0018 (0x0358 - 0x0340)
class AFGGameSession : public AGameSession
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0340(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameSession");
		return ptr;
	}


	void ListenForIntroSequenceUpdated();
	void IntroSequenceUpdated();
};


// Class FactoryGame.FGGameState
// 0x01E8 (0x0570 - 0x0388)
class AFGGameState : public AGameState
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0388(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    MapAreaVisistedDelegate;                                  // 0x0390(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnUnlockedMoreInventorySlots;                            // 0x03A0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnUnlockedMoreArmsSlots;                                 // 0x03B0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mTurboModeMultiplier;                                     // 0x03C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03C4(0x0004) MISSED OFFSET
	class UClass*                                      mPowerCircuitFuseTriggeredMessage;                        // 0x03C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UClass*>                              mAvailableRecipes;                                        // 0x03D0(0x0010) (ZeroConstructor, SaveGame)
	class UClass*                                      mMapUnlockedMessage;                                      // 0x03E0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mInventorySlotUnlockedMessage;                            // 0x03E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mBuildingEfficiencyUnlockedMessage;                       // 0x03F0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mBuildingOverclockUnlockedMessage;                        // 0x03F8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mArmEquipmentSlotUnlockedMessage;                         // 0x0400(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGTimeOfDaySubsystem*                       mTimeSubsystem;                                           // 0x0408(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGStorySubsystem*                           mStorySubsystem;                                          // 0x0410(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGRailroadSubsystem*                        mRailroadSubsystem;                                       // 0x0418(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGCircuitSubsystem*                         mCircuitSubsystem;                                        // 0x0420(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGRecipeManager*                            mRecipeManager;                                           // 0x0428(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGSchematicManager*                         mSchematicManager;                                        // 0x0430(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGGamePhaseManager*                         mGamePhaseManager;                                        // 0x0438(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGResearchManager*                          mResearchManager;                                         // 0x0440(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGTutorialIntroManager*                     mTutorialIntroManager;                                    // 0x0448(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGActorRepresentationManager*               mActorRepresentationManager;                              // 0x0450(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGMapManager*                               mMapManager;                                              // 0x0458(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGRadioactivitySubsystem*                   mRadioactivitySubsystem;                                  // 0x0460(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGChatManager*                              mChatManager;                                             // 0x0468(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGCentralStorageSubsystem*                  mCentralStorageSubsystem;                                 // 0x0470(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              mScannableResources;                                      // 0x0478(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<class UClass*>                              mVisitedMapAreas;                                         // 0x0488(0x0010) (Net, ZeroConstructor, SaveGame)
	bool                                               mCheatNoCost;                                             // 0x0498(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mCheatNoPower;                                            // 0x0499(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsMapUnlocked;                                           // 0x049A(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1];                                       // 0x049B(0x0001) MISSED OFFSET
	int                                                mNumAdditionalInventorySlots;                             // 0x049C(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsBuildingEfficiencyUnlocked;                            // 0x04A0(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsBuildingOverclockUnlocked;                             // 0x04A1(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsTradingPostBuilt;                                      // 0x04A2(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mHasInitalTradingPostLandAnimPlayed;                      // 0x04A3(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsSpaceElevatorBuilt;                                    // 0x04A4(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x04A5(0x0003) MISSED OFFSET
	int                                                mDefaultPlayerInventorySlots;                             // 0x04A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x4];                                       // 0x04AC(0x0004) MISSED OFFSET
	class UClass*                                      mHubPartClass;                                            // 0x04B0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mPlayDurationWhenLoaded;                                  // 0x04B8(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData05[0x4];                                       // 0x04BC(0x0004) MISSED OFFSET
	class FString                                      mReplicatedSessionName;                                   // 0x04C0(0x0010) (Net, ZeroConstructor, SaveGame)
	bool                                               mForceAddHubPartOnSpawn;                                  // 0x04D0(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData06[0x3];                                       // 0x04D1(0x0003) MISSED OFFSET
	struct FFGBuildingColorSlotStruct                  mBuildingColorSlots[0x10];                                // 0x04D4(0x0008) (Edit, Net, DisableEditOnInstance)
	unsigned char                                      UnknownData07[0x4];                                       // 0x0554(0x0004) MISSED OFFSET
	TArray<class UClass*>                              mResourcesScannedFor;                                     // 0x0558(0x0010) (ZeroConstructor)
	int                                                mNumAdditionalArmEquipmentSlots;                          // 0x0568(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData08[0x4];                                       // 0x056C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameState");
		return ptr;
	}


	void SetIsSpaceElevatorBuilt(bool IsSpaceElevatorBuilt);
	void SetHasInitalTradingPostLandAnimPlayed();
	void SetCheatNoPower(bool NoPower);
	void SetCheatNoCost(bool NoCost);
	void SetAndReplicateBuildingColorInSlot(unsigned char Slot, const struct FColor& pColor, const struct FColor& sColor);
	void SendMessageToPlayer(class UClass* inMessage, class APlayerController* Controller);
	void SendMessageToAllPlayers(class UClass* inMessage);
	void RemoveAllScannableResources();
	void OnSchematicPurchased(class UClass* newSchematic);
	void OnRep_MapAreaVisited();
	void OnRep_BuildingColorSlot();
	void NotifyPlayerAdded(class AFGCharacterPlayer* inPlayer);
	bool IsTradingPostBuilt();
	bool IsSpaceElevatorBuilt();
	bool IsMapAreaVisisted(class UClass* inArea);
	bool HasInitalTradingPostLandAnimPlayed();
	void GetVisitedMapAreas(TArray<class UClass*>* out_VisitedAreas);
	class AFGTutorialIntroManager* GetTutorialIntroManager();
	int GetTotalPlayerInventorySlots();
	int GetTotalPlayerArmEquipmentSlots();
	int GetTotalPlayDuration();
	class FString GetSessionName();
	class AFGSchematicManager* GetSchematicManager();
	class AFGResearchManager* GetResearchManager();
	int GetNumInventorySlotsUnlocked();
	int GetNumArmEquipmentSlotsUnlocked();
	bool GetIsMapUnlocked();
	class AFGGamePhaseManager* GetGamePhaseManager();
	bool GetCheatNoPower();
	bool GetCheatNoCost();
	bool GetBuildingOverclockUnlocked();
	bool GetBuildingEfficiencyUnlocked();
	class AFGActorRepresentationManager* GetActorRepresentationManager();
};


// Class FactoryGame.FGGameUI
// 0x0038 (0x0260 - 0x0228)
class UFGGameUI : public UFGBaseUI
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0228(0x0018) MISSED OFFSET
	TArray<class UFGInteractWidget*>                   mInteractWidgetStack;                                     // 0x0240(0x0010) (ExportObject, ZeroConstructor)
	class UFGAudioMessage*                             mCurrentAudioMessage;                                     // 0x0250(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mMinTimeBetweenAudioMessage;                              // 0x0258(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x025C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameUI");
		return ptr;
	}


	void SetWindowWantsInventoryAddon(bool doWantAddon);
	void SetShowInventory(bool doShow);
	void SetCurrentAudioMessage(class UFGAudioMessage* newMessage);
	void RemovePawnHUD();
	void RemoveInteractWidget(class UFGInteractWidget* widgetToRemove);
	void RemoveAudioMessage();
	void ReceivedMessage(class UClass* inMessage);
	void PopAllWidgets();
	void OnReceiveRadiationStop();
	void OnReceiveRadiationStart();
	void OnRadiationIntensityUpdated(float radiationIntensity, float radiationImmunity);
	void HandlePendingMessages();
	void HandleFocusLost();
	bool GetWindowWantsInventoryAddon();
	bool GetShowInventory();
	TArray<class UClass*> GetPendingMessages();
	TArray<class UFGInteractWidget*> GetInteractWidgetStack();
	class UFGAudioMessage* GetCurrentAudioMessage();
	void ClearHintOnTutorialStepCompleted();
	bool CanReceiveMessage(class UClass* inMessage);
	void CancelPressed();
	void AddPendingMessage(class UClass* newMessage);
	void AddPawnHUD(class UUserWidget* newContent);
	void AddIntroTutorialInfo(const struct FTutorialHintData& TutorialHintData);
	void AddInteractWidget(class UFGInteractWidget* widgetToAdd);
	class UFGPopupWidget* AddCheatWidget(const struct FPopupData& PopupData);
};


// Class FactoryGame.FGGameUserSettings
// 0x0048 (0x0160 - 0x0118)
class UFGGameUserSettings : public UGameUserSettings
{
public:
	struct FScriptMulticastDelegate                    OnArachnophobiaModeChangedDelegate;                       // 0x0118(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<struct FAudioVolumeMap>                     mAudioVolumes;                                            // 0x0128(0x0010) (ZeroConstructor, Config)
	int                                                mFOV;                                                     // 0x0138(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	int                                                mMotionBlurQuality;                                       // 0x013C(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	TArray<struct FFGKeyMapping>                       mCustomKeyMappings;                                       // 0x0140(0x0010) (Edit, ZeroConstructor, Config)
	int                                                mNetworkQuality;                                          // 0x0150(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0154(0x0004) MISSED OFFSET
	float                                              mHeadBobScale;                                            // 0x0158(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      mIsArachnophobiaMode : 1;                                 // 0x015C(0x0001) (Config)
	unsigned char                                      mInvertY : 1;                                             // 0x015C(0x0001) (Config)
	unsigned char                                      mHoldToSprint : 1;                                        // 0x015C(0x0001) (Config)
	unsigned char                                      mAutoSortInventory : 1;                                   // 0x015C(0x0001) (Config)
	unsigned char                                      mAnalyticsDisabled : 1;                                   // 0x015C(0x0001) (Config)
	unsigned char                                      UnknownData01[0x3];                                       // 0x015D(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameUserSettings");
		return ptr;
	}


	void UpdatePostProcessSettings();
	void SetNeworkQuality(int newNetworkQuality);
	void SetMotionBlurEnabled(bool enable);
	void SetInvertedLook(bool newInvertLook);
	void SetHoldToSprint(bool newHoldToSprint);
	void SetHeadBobScale(float newHeadBobScale);
	void SetFOV(int NewFOV);
	void SetAutoSortInventory(bool shouldAutoSort);
	void SetAudioVolume(const class FString& Name, float Value);
	void SetAudioToDefaults();
	void SetArachnophobiaMode(bool newArachnophobiaMode);
	void SetAnalyticsDisabled(bool IsDisabled, class UAnalyticsService* AnalyticsService);
	void ResetAudioToCurrentSettings();
	bool IsUsingCustomQualitySetting(const class FString& SettingName);
	bool IsPostProcessUsingCustomSettings();
	bool IsMotionBlurEnabled();
	bool IsMotionBlurDirty();
	bool GetRequireRestart();
	int GetNeworkQuality();
	TArray<struct FFGKeyMapping> GetKeyMappings();
	bool GetInvertedLook();
	bool GetHoldToSprint();
	float GetHeadBobScale();
	int GetFOV();
	class UFGGameUserSettings* GetFGGameUserSettings();
	int GetDefaultQualitySetting(const class FString& SettingName);
	bool GetAutoSortInventory();
	float GetAudioVolume(const class FString& Name);
	bool GetArachnophobiaMode();
	bool GetAnalyticsDisabled();
	void ClearRequireRestart();
};


// Class FactoryGame.FGGameViewportClient
// 0x0000 (0x02E8 - 0x02E8)
class UFGGameViewportClient : public UGameViewportClient
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGameViewportClient");
		return ptr;
	}

};


// Class FactoryGame.FGGasMask
// 0x0000 (0x03C0 - 0x03C0)
class AFGGasMask : public AFGEquipment
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGasMask");
		return ptr;
	}

};


// Class FactoryGame.FGGasMaskAttachment
// 0x0000 (0x0360 - 0x0360)
class AFGGasMaskAttachment : public AFGEquipmentAttachment
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGasMaskAttachment");
		return ptr;
	}

};


// Class FactoryGame.FGResourceExtractorHologram
// 0x0018 (0x0460 - 0x0448)
class AFGResourceExtractorHologram : public AFGFactoryHologram
{
public:
	TArray<EResourceForm>                              mAllowedResourceForms;                                    // 0x0448(0x0010) (ZeroConstructor)
	class AFGResourceNode*                             mSnappedResourceNode;                                     // 0x0458(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceExtractorHologram");
		return ptr;
	}

};


// Class FactoryGame.FGGeoThermalGeneratorHologram
// 0x0000 (0x0460 - 0x0460)
class AFGGeoThermalGeneratorHologram : public AFGResourceExtractorHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGeoThermalGeneratorHologram");
		return ptr;
	}

};


// Class FactoryGame.FGGlobalSettings
// 0x0050 (0x0078 - 0x0028)
class UFGGlobalSettings : public UObject
{
public:
	class UClass*                                      mResourceSettings;                                        // 0x0028(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mFactorySettings;                                         // 0x0030(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mDropPodSettings;                                         // 0x0038(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mHardDriveSettings;                                       // 0x0040(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mEnvironmentSettings;                                     // 0x0048(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mSubsystemClasses;                                        // 0x0050(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mSignSettings;                                            // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FSoftClassPath                              mGlobalSettingsClassName;                                 // 0x0060(0x0018) (ZeroConstructor, Config, NoClear)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGGlobalSettings");
		return ptr;
	}


	class UFGSubsystemClasses* GetSubsystemClassesCDO();
	class UFGSignSettings* GetSignSettingsCDO();
	class UFGResourceSettings* GetResourceSettingsCDO();
	class UFGHardDriveSettings* GetHardDriveSettingsCDO();
	class UFGGlobalSettings* GetGlobalSettingsClassCDO();
	class UFGFactorySettings* GetFactorySettingsCDO();
	class UFGEnvironmentSettings* GetEnvironmentSettingsCDO();
	class UFGDropPodSettings* GetDropPodSettingsCDO();
};


// Class FactoryGame.FGHardDriveSettings
// 0x0028 (0x0050 - 0x0028)
class UFGHardDriveSettings : public UFGSettings
{
public:
	int                                                mUniqueItemCount;                                         // 0x0028(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x002C(0x0004) MISSED OFFSET
	TArray<struct FHardDriveSchematicDrop>             mPotentialSchematicDrops;                                 // 0x0030(0x0010) (Edit, ZeroConstructor)
	struct FItemAmount                                 mFallbackReturnItem;                                      // 0x0040(0x0010) (Edit)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHardDriveSettings");
		return ptr;
	}


	TArray<struct FResearchRecipeReward> GetResearchRewardPackages(class UWorld* World, class UClass* calledByResearch);
};


// Class FactoryGame.FGHealthComponent
// 0x0078 (0x0168 - 0x00F0)
class UFGHealthComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x00F0(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnTakeAnyDamageDelegate;                                  // 0x00F8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnTakePointDamageDelegate;                                // 0x0108(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnTakeRadialDamageDelegate;                               // 0x0118(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    DeathDelegate;                                            // 0x0128(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    HealDelegate;                                             // 0x0138(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<struct FScriptDelegate>                     mOnAdjustDamage;                                          // 0x0148(0x0010) (ZeroConstructor)
	float                                              mMaxHealth;                                               // 0x0158(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	float                                              mCurrentHealth;                                           // 0x015C(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mRespawnHealthFactor;                                     // 0x0160(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      mIsDead : 1;                                              // 0x0164(0x0001) (Net, SaveGame)
	unsigned char                                      mReplicateDamageEvents : 1;                               // 0x0164(0x0001)
	unsigned char                                      mReplicateDeathEvents : 1;                                // 0x0164(0x0001)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0165(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHealthComponent");
		return ptr;
	}


	void TakeRadialDamage(class AActor* damagedActor, float Damage, class UDamageType* DamageType, const struct FVector& HitLocation, const struct FHitResult& HitInfo, class AController* instigatedBy, class AActor* damageCauser);
	void TakePointDamage(class AActor* damagedActor, float Damage, class AController* instigatedBy, const struct FVector& HitLocation, class UPrimitiveComponent* HitComponent, const struct FName& BoneName, const struct FVector& ShotFromDirection, class UDamageType* DamageType, class AActor* damageCauser);
	void TakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void ReviveResetHealth();
	void ResetHealthFromDeath();
	void ResetHealth();
	void RemoveAdjustDamageListener(const struct FScriptDelegate& AdjustDamage);
	void Kill();
	bool IsDead();
	void Heal(float healAmount);
	float GetMaxHealth();
	float GetCurrentHealth();
	void Client_TakeRadialDamage(class AActor* damagedActor, float Damage, class UDamageType* DamageType, const struct FVector& HitLocation, const struct FHitResult& HitInfo, class AController* instigatedBy, class AActor* damageCauser);
	void Client_TakePointDamage(class AActor* damagedActor, float Damage, class AController* instigatedBy, const struct FVector& HitLocation, class UPrimitiveComponent* HitComponent, const struct FName& BoneName, const struct FVector& ShotFromDirection, class UDamageType* DamageType, class AActor* damageCauser);
	void Client_TakeDamage(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser);
	void Client_Heal(float amount);
	void Client_Died(class AActor* DeadActor);
	void AddAdjustDamageListener(const struct FScriptDelegate& AdjustDamage);
};


// Class FactoryGame.FGHookshot
// 0x0028 (0x03E8 - 0x03C0)
class AFGHookshot : public AFGEquipment
{
public:
	float                                              mMaxHookDistance;                                         // 0x03C0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAccelRate;                                               // 0x03C4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mBrakeAccelRate;                                          // 0x03C8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x03CC(0x000C) MISSED OFFSET
	class UAkComponent*                                mHookshotAudio;                                           // 0x03D8(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x03E0(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHookshot");
		return ptr;
	}


	void RestoreAudioSourceToOriginalLocation();
	void OwnerLanded(const struct FHitResult& Hit);
	void OnWireDetach();
	void OnFire(bool attachedToSomething, const struct FHitResult& HitResult);
	void MoveAudioSourceInFrontOfPlayer();
};


// Class FactoryGame.FGHUDBase
// 0x0008 (0x0420 - 0x0418)
class AFGHUDBase : public AHUD
{
public:
	class UFGBaseUI*                                   mBaseUI;                                                  // 0x0418(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHUDBase");
		return ptr;
	}


	class UFGBaseUI* GetBaseUI();
};


// Class FactoryGame.FGHUD
// 0x00C0 (0x04E0 - 0x0420)
class AFGHUD : public AFGHUDBase
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0420(0x0010) MISSED OFFSET
	class UClass*                                      mGameUIClass;                                             // 0x0430(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mRespawnUIClass;                                          // 0x0438(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mDefaultCrosshair;                                        // 0x0440(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mPickupCrosshair;                                         // 0x0448(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mVehicleCrosshair;                                        // 0x0450(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mWeaponCrosshair;                                         // 0x0458(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mWorkbenchCrosshair;                                      // 0x0460(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mBuildCrosshair;                                          // 0x0468(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mDismantleCrosshair;                                      // 0x0470(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mCustomCrosshair;                                         // 0x0478(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  mGeneralCrosshair;                                        // 0x0480(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x0488(0x0020) MISSED OFFSET
	class UUserWidget*                                 mRespawnUI;                                               // 0x04A8(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	class UFGGameUI*                                   mGameUI;                                                  // 0x04B0(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	class UWorld*                                      mPreviewBuildingWorld;                                    // 0x04B8(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UClass*                                      mPreviewStageClass;                                       // 0x04C0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x04C8(0x0008) MISSED OFFSET
	class UClass*                                      mPreviewActorClass;                                       // 0x04D0(0x0008) (ZeroConstructor, IsPlainOldData)
	class UUserWidget*                                 mPawnHUD;                                                 // 0x04D8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHUD");
		return ptr;
	}


	void UpdateCrosshairState(class AFGCharacterPlayer* Player);
	void UpdateCrosshairColorState(const struct FLinearColor& NewColor);
	void ShowRespawnUI();
	void SetShowCrossHair(bool showCrosshair);
	void SetPumpiMode(bool hideHUD);
	void SetPreviewView(const struct FItemView& View);
	void SetPreviewDistance(float previewDistance);
	void SetPreviewActorClass(class UClass* ActorClass);
	void SetPartialPumpiMode(bool hideHUD);
	void SetHUDVisibility(bool hudVisibility);
	void SetForceHideCrossHair(bool forceHide);
	void SetCrustomCrosshairTexture(class UTexture2D* newTexture);
	void SetCrosshairState(ECrosshairState crosshairState);
	void RemoveEquipmentHUD(EEquipmentSlot Slot);
	void OpenInteractUI(class UClass* WidgetClass, class UObject* interactObject);
	bool GetShowCrosshair();
	bool GetPumpiMode();
	class UTextureRenderTarget2D* GetPreviewTexture();
	class UUserWidget* GetPawnHUD();
	bool GetPartialPumpiMode();
	bool GetHUDVisibility();
	class UFGGameUI* GetGameUI();
	ECrosshairState GetCrosshairState();
	void EndPreviewActor();
	void CloseRespawnUI();
	void BeginPreviewActor();
	void AddPawnHUD(class UClass* WidgetClass, class APawn* Pawn);
	void AddEquipmentHUD(class UClass* WidgetClass, EEquipmentSlot Slot);
};


// Class FactoryGame.FGInputLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGInputLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInputLibrary");
		return ptr;
	}


	void UpdateInputMappings(class APlayerController* PlayerController);
	bool RebindKey(class APlayerController* PlayerController, const struct FFGKeyMapping& newKeyMapping);
	void NullKeyMappingWithSameKeyCombo(class APlayerController* PlayerController, const struct FFGKeyMapping& keyMapping);
	bool IsKeyMappingRelevant(const struct FName& keyMappingName);
	bool IsFGKeyMappingAvailable(class APlayerController* PlayerController, const struct FFGKeyMapping& keyMapping);
	bool IsAxisMappingUsingSameKeys(const struct FInputAxisKeyMapping& mappingA, const struct FInputAxisKeyMapping& mappingB);
	bool IsAxisKeyMappingAvailable(class APlayerController* PlayerController, const struct FFGKeyMapping& keyMapping);
	bool IsActionMappingUsingSameKeys(const struct FInputActionKeyMapping& mappingA, const struct FInputActionKeyMapping& mappingB);
	bool IsActionKeyMappingAvailable(class APlayerController* PlayerController, const struct FFGKeyMapping& keyMapping);
	bool IsActionAndAxisMappingUsingSameKeys(const struct FInputActionKeyMapping& actionMapping, const struct FInputAxisKeyMapping& axisMapping);
	struct FFGKeyMapping GetOverlappingKeyMapping(class APlayerController* PlayerController, const struct FFGKeyMapping& keyMapping);
	struct FText GetKeyNameForAxis(class APlayerController* PlayerController, const struct FName& AxisName, bool positiveAxisScale, bool getGamepadKey);
	struct FText GetKeyNameForAction(class APlayerController* PlayerController, const struct FName& ActionName, bool getGamepadKey, bool abbreviateKeyName);
	struct FInputActionKeyMapping GetKeyMappingForAction(class APlayerController* PlayerController, const struct FName& inAction, bool getGamepadKey);
	struct FKey GetKeyForAxis(class APlayerController* PlayerController, const struct FName& AxisName, bool positiveAxisScale, bool getGamepadKey);
	struct FText GetAbbreviatedKeyName(const struct FKey& Key);
	struct FText FormatStringWithKeyNames(class APlayerController* PlayerController, const struct FText& textToFormat, bool abbreviateKeyNames);
	struct FFGKeyMapping CreateFGKeyMappingStruct(const struct FName& ActionName, bool IsAxisMapping, bool positiveAxisScale, const struct FInputEvent& InputEvent, const struct FKey& keyPressed);
};


// Class FactoryGame.FGInteractableMarker
// 0x0028 (0x0350 - 0x0328)
class AFGInteractableMarker : public AActor
{
public:
	class UWidgetComponent*                            mIconWidget;                                              // 0x0328(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class USplineMeshComponent*                        mSplineMesh;                                              // 0x0330(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	float                                              mDesiredScreenRadius;                                     // 0x0338(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
	class AActor*                                      mTrackedActor;                                            // 0x0340(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGPlayerController*                         mCachePlayerController;                                   // 0x0348(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInteractableMarker");
		return ptr;
	}


	void SetTrackedActor(class AActor* trackedActor);
	void OnSetActorTracked();
	class AActor* GetTrackedActor();
};


// Class FactoryGame.FGInteractWidget
// 0x0050 (0x0258 - 0x0208)
class UFGInteractWidget : public UUserWidget
{
public:
	bool                                               mUseKeyboard;                                             // 0x0208(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUseMouse;                                                // 0x0209(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mCaptureInput;                                            // 0x020A(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mRestoreFocusWhenLost;                                    // 0x020B(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x020C(0x0004) MISSED OFFSET
	TArray<struct FName>                               mInputToPassThrough;                                      // 0x0210(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	TEnumAsByte<EHorizontalAlignment>                  mDesiredHorizontalAlignment;                              // 0x0220(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EVerticalAlignment>                    mDesiredVerticalAlignment;                                // 0x0221(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0222(0x0002) MISSED OFFSET
	struct FSlateChildSize                             mDesiredAlignmentSize;                                    // 0x0224(0x0008) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData02[0x4];                                       // 0x022C(0x0004) MISSED OFFSET
	class UObject*                                     mInteractObject;                                          // 0x0230(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UClass*                                      mDefaultFocusWidgetClass;                                 // 0x0238(0x0008) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUseGamepadCursor;                                        // 0x0240(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0241(0x0007) MISSED OFFSET
	class UWidget*                                     mDefaultFocusWidget;                                      // 0x0248(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mSupportsStacking;                                        // 0x0250(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x0251(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInteractWidget");
		return ptr;
	}


	void UpdateIgnoreMoveInput();
	void UpdateIgnoreLookInput();
	void SetupDefaultFocus();
	void SetInputMode();
	void SetDesiredVerticalAlignment(TEnumAsByte<EVerticalAlignment> newAlignment);
	void SetDesiredHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> newAlignment);
	void SetDesiredAlignmentSize(const struct FSlateChildSize& newSize);
	void SetDefaultFocusWidget(class UWidget* FocusWidget);
	void OnEscapePressed();
	void OnConsume();
	void Init();
	bool GetUseGamepadCursor();
	bool GetSupportsStacking();
	TEnumAsByte<EVerticalAlignment> GetDesiredVerticalAlignment();
	TEnumAsByte<EHorizontalAlignment> GetDesiredHorizontalAlignment();
	struct FSlateChildSize GetDesiredAlignmentSize();
	class UWidget* GetDefaultFocusWidget();
};


// Class FactoryGame.FGInventoryComponent
// 0x0098 (0x0188 - 0x00F0)
class UFGInventoryComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x00F0(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    ResizeInventoryDelegate;                                  // 0x00F8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnItemAddedDelegate;                                      // 0x0108(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnItemRemovedDelegate;                                    // 0x0118(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0128(0x0010) MISSED OFFSET
	int                                                mDefaultInventorySize;                                    // 0x0138(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mAdjustedSizeDiff;                                        // 0x013C(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	TArray<struct FInventoryStack>                     mInventoryStacks;                                         // 0x0140(0x0010) (Net, ZeroConstructor, SaveGame)
	unsigned char                                      UnknownData02[0x10];                                      // 0x0150(0x0010) MISSED OFFSET
	TArray<int>                                        mArbitrarySlotSizes;                                      // 0x0160(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<class UClass*>                              mAllowedItemDescriptors;                                  // 0x0170(0x0010) (Net, ZeroConstructor, SaveGame)
	bool                                               mCanBeRearrange;                                          // 0x0180(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0181(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInventoryComponent");
		return ptr;
	}


	void SplitStackAtIdx(int idx, int numItemsToMove);
	void SortInventory();
	void SetCanBeRearranged(bool canBeRearranged);
	void SetAllowedItemOnIndex(int idx, class UClass* allowedItemClass);
	void Server_SortInventory();
	void Resize(int newSize);
	void RemoveFromIndex(int idx, int Num);
	void RemoveAllFromIndex(int idx);
	void Remove(class UClass* ItemClass, int Num);
	void OnRep_InventoryStacks();
	bool IsValidIndex(int idx);
	bool IsSomethingOnIndex(int idx);
	bool IsItemAllowed(class UClass* Item, int idx);
	bool IsIndexEmpty(int idx);
	bool IsEmpty();
	bool HasItems(class UClass* ItemClass, int Num);
	bool HasEnoughSpaceForStacks(TArray<struct FInventoryStack> stacks);
	bool HasEnoughSpaceForStack(const struct FInventoryStack& stack);
	bool HasEnoughSpaceForItem(const struct FInventoryItem& stack);
	bool HasAuthority();
	bool GetStackFromIndex(int idx, struct FInventoryStack* out_stack);
	int GetSlotSize(int Index, class UClass* itemDesc);
	int GetSizeLinear();
	int GetNumItems(class UClass* ItemClass);
	void GetInventoryStacks(TArray<struct FInventoryStack>* out_stacks);
	int GetFullestStackIndex();
	bool GetCanBeRearranged();
	class UClass* GetAllowedItemOnIndex(int idx);
	int FindEmptyIndex();
	void Empty();
	bool CanSplitStackAtIdx(int idx);
	int AddStackToIndex(int idx, const struct FInventoryStack& stack, bool allowPartial);
	void AddStacks(TArray<struct FInventoryStack> stacks);
	int AddStack(const struct FInventoryStack& stack, bool allowPartialAdd);
	void AddArbitrarySlotSize(int Index, int arbitrarySlotSize);
};


// Class FactoryGame.FGInventoryComponentBeltSlot
// 0x0000 (0x0188 - 0x0188)
class UFGInventoryComponentBeltSlot : public UFGInventoryComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInventoryComponentBeltSlot");
		return ptr;
	}

};


// Class FactoryGame.FGInventoryComponentEquipment
// 0x0018 (0x01A0 - 0x0188)
class UFGInventoryComponentEquipment : public UFGInventoryComponent
{
public:
	class AFGEquipment*                                mOverrideEquipmentInSlot;                                 // 0x0188(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGEquipment*                                mEquipmentInSlot;                                         // 0x0190(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	EEquipmentSlot                                     mEquipmentInventorySlot;                                  // 0x0198(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0199(0x0003) MISSED OFFSET
	int                                                mActiveEquipmentIndex;                                    // 0x019C(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInventoryComponentEquipment");
		return ptr;
	}


	EEquipmentSlot GetEquipmentSlotEnum();
	int GetActiveIndex();
};


// Class FactoryGame.FGInventoryComponentTrash
// 0x0000 (0x0188 - 0x0188)
class UFGInventoryComponentTrash : public UFGInventoryComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInventoryComponentTrash");
		return ptr;
	}


	bool IsValidItem(class UClass* Resource);
};


// Class FactoryGame.FGInventoryLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGInventoryLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInventoryLibrary");
		return ptr;
	}


	bool MoveInventoryItem(class UFGInventoryComponent* SourceComponent, int sourceIdx, class UFGInventoryComponent* destinationComponent, int destinationIdx);
	void MergeInventoryItem(const struct FInventoryStack& Item, TArray<struct FInventoryStack>* Items);
	struct FInventoryStack MakeInventoryStack(int NumItems, const struct FInventoryItem& Item);
	struct FInventoryItem MakeInventoryItem(class UClass* ItemClass);
	bool IsValidItem(const struct FInventoryItem& Item);
	bool HasState(const struct FInventoryItem& Item);
	bool HasItems(const struct FInventoryStack& stack);
	bool GrabAllItemsFromInventory(class UFGInventoryComponent* SourceComponent, class UFGInventoryComponent* destinationComponent, class UClass* onlyGrabOfDesc);
	int GetMinNumSlotsForItems(TArray<struct FInventoryStack>* Items);
	class UFGInventoryComponent* CreateInventoryComponentOfClass(class AActor* Owner, class UClass* inClass, const struct FName& Name);
	class UFGInventoryComponent* CreateInventoryComponent(class AActor* Owner, const struct FName& Name);
	void ConsolidateItemsAmount(TArray<struct FItemAmount>* Items);
	void ConsolidateInventoryItems(TArray<struct FInventoryStack>* Items);
	void BreakInventoryStack(const struct FInventoryStack& stack, int* out_numItems, struct FInventoryItem* out_item);
	void BreakInventoryItem(const struct FInventoryItem& Item, class UClass** out_itemClass, class AActor** out_itemState);
};


// Class FactoryGame.FGItemDescriptorBiomass
// 0x0000 (0x0128 - 0x0128)
class UFGItemDescriptorBiomass : public UFGItemDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGItemDescriptorBiomass");
		return ptr;
	}

};


// Class FactoryGame.FGItemDescriptorNuclearFuel
// 0x0010 (0x0138 - 0x0128)
class UFGItemDescriptorNuclearFuel : public UFGItemDescriptor
{
public:
	class UClass*                                      mSpentFuelClass;                                          // 0x0128(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mAmountOfWaste;                                           // 0x0130(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0134(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGItemDescriptorNuclearFuel");
		return ptr;
	}


	class UClass* GetSpentFuelClass(class UClass* inClass);
	int GetAmountWasteCreated(class UClass* inClass);
};


// Class FactoryGame.FGUseState_FullInventory
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_FullInventory : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_FullInventory");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_Collecting
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_Collecting : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_Collecting");
		return ptr;
	}

};


// Class FactoryGame.FGItemPickup
// 0x0068 (0x0390 - 0x0328)
class AFGItemPickup : public AActor
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0328(0x0018) MISSED OFFSET
	float                                              mTimeToPickUp;                                            // 0x0340(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0344(0x0004) MISSED OFFSET
	class AFGCharacterPlayer*                          mCollector;                                               // 0x0348(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	struct FTimerHandle                                mCollectingTimerHandle;                                   // 0x0350(0x0008)
	struct FInventoryStack                             mPickupItems;                                             // 0x0358(0x0020) (Edit, Net, SaveGame)
	bool                                               mDestroyOnPickup;                                         // 0x0378(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0379(0x0007) MISSED OFFSET
	class UAkComponent*                                mSoundComponent;                                          // 0x0380(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UAkAudioEvent*                               mAudioEvent;                                              // 0x0388(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGItemPickup");
		return ptr;
	}


	void SetNumItems(int NumItems);
	void PlayPickupEffect();
	void PickUpByCharacter(class AFGCharacterPlayer* byCharacter);
	bool PickupByAmount(int amount);
	void OnRep_PickedUp();
	void OnPickup(class AFGCharacterPlayer* byCharacter);
	bool IsPickedUp();
	struct FInventoryStack GetPickupItems();
	int GetNumItems();
	float GetNormalizedCollectionProgress();
};


// Class FactoryGame.FGItemPickup_Spawnable
// 0x0010 (0x03A0 - 0x0390)
class AFGItemPickup_Spawnable : public AFGItemPickup
{
public:
	class UStaticMeshComponent*                        mMeshComponent;                                           // 0x0390(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mPlaySpawnEffect;                                         // 0x0398(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0399(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGItemPickup_Spawnable");
		return ptr;
	}


	void PlaySpawnEffect();
	void FindGroundLocationInfrontOfActor(class AActor* sourceActor, float offsetLength, const struct FInventoryStack& Item, struct FVector* out_location, struct FRotator* out_rotation);
	void FindGroundLocationAndRotation(class UObject* WorldContext, const struct FVector& fromLocation, TArray<class AActor*> ActorsToIgnore, struct FVector* out_location, struct FRotator* out_rotation);
	void CreateItemDropsInCylinder(class UObject* WorldContext, TArray<struct FInventoryStack> Items, const struct FVector& aroundLocation, float SphereRadius, TArray<class AActor*> ActorsToIgnore, class UClass* itemDropClass, TArray<class AFGItemPickup_Spawnable*>* out_itemDrops);
	class AFGItemPickup_Spawnable* CreateItemDrop(class UObject* WorldContext, const struct FInventoryStack& Item, const struct FVector& SpawnLocation, const struct FRotator& spawnRotation, class UClass* itemDropClass);
	class AFGItemPickup_Spawnable* AddItemToWorldStackAtLocation(class UObject* WorldContext, const struct FInventoryStack& Item, const struct FVector& SpawnLocation, const struct FRotator& spawnRotation, class UClass* itemDropClass);
};


// Class FactoryGame.FGJetPack
// 0x0010 (0x03D0 - 0x03C0)
class AFGJetPack : public AFGEquipment
{
public:
	float                                              mJumpTimeStamp;                                           // 0x03C0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData)
	bool                                               mIsThrusting;                                             // 0x03C4(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData00[0xB];                                       // 0x03C5(0x000B) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGJetPack");
		return ptr;
	}


	void OnStopThrusting();
	void OnStartThrusting();
	struct FVector GetNewVelocityWhenThrusting(float Delta);
	float GetMaxFuel();
	float GetCurrentFuel();
	bool CanThrust();
};


// Class FactoryGame.FGJetPackAttachment
// 0x0008 (0x0368 - 0x0360)
class AFGJetPackAttachment : public AFGEquipmentAttachment
{
public:
	bool                                               mIsThrusting;                                             // 0x0360(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0361(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGJetPackAttachment");
		return ptr;
	}


	void OnStopThrusting();
	void OnStartThrusting();
	void OnRep_IsThrusting();
};


// Class FactoryGame.FGJumpingStilts
// 0x0020 (0x03E0 - 0x03C0)
class AFGJumpingStilts : public AFGEquipment
{
public:
	class UCurveFloat*                                 mFallDamageCurveOverride;                                 // 0x03C0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSprintSpeedFactor;                                       // 0x03C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mJumpSpeedFactor;                                         // 0x03CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x03D0(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGJumpingStilts");
		return ptr;
	}


	float GetNormalizedFallSpeedUntilDamaged();
	float GetMaxFallSpeedBeforeDamage();
	float GetCurrentFallSpeed();
	float GetAdjustedZJumpSpeed(float defaultJumpZ);
	float GetAdjustedMaxSpeed(float defaultMaxSpeed);
};


// Class FactoryGame.FGJumpingStiltsAttachment
// 0x0000 (0x0360 - 0x0360)
class AFGJumpingStiltsAttachment : public AFGEquipmentAttachment
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGJumpingStiltsAttachment");
		return ptr;
	}

};


// Class FactoryGame.FGLadderComponent
// 0x0030 (0x05B0 - 0x0580)
class UFGLadderComponent : public UBoxComponent
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0580(0x0018) MISSED OFFSET
	float                                              mClimbableLookAngle;                                      // 0x0598(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mEndClimbingLookAngle;                                    // 0x059C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class AFGCharacterPlayer*>                  mPotentialClimbers;                                       // 0x05A0(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGLadderComponent");
		return ptr;
	}


	void EndPotentialClimberOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	void BeginPotentialClimberOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool isFromSweep, const struct FHitResult& SweepResult);
};


// Class FactoryGame.FGListView
// 0x00E8 (0x0200 - 0x0118)
class UFGListView : public UPanelWidget
{
public:
	struct FScriptDelegate                             mOnGenerateRowEvent;                                      // 0x0118(0x0014) (Edit, ZeroConstructor, InstancedReference)
	struct FScriptDelegate                             mGetNumRowsEvent;                                         // 0x0128(0x0014) (Edit, ZeroConstructor, InstancedReference)
	unsigned char                                      UnknownData00[0x70];                                      // 0x0138(0x0070) MISSED OFFSET
	TEnumAsByte<ESelectionMode>                        mSelectionMode;                                           // 0x01A8(0x0001) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData01[0x57];                                      // 0x01A9(0x0057) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGListView");
		return ptr;
	}


	void Refresh();
	class UWidget* OnGenerateRow__DelegateSignature(int Item);
	int GetNumRows__DelegateSignature();
};


// Class FactoryGame.FGListViewSlot
// 0x0008 (0x0040 - 0x0038)
class UFGListViewSlot : public UPanelSlot
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGListViewSlot");
		return ptr;
	}

};


// Class FactoryGame.FGEM_LoggedOutFromOnlineService
// 0x0000 (0x0048 - 0x0048)
class UFGEM_LoggedOutFromOnlineService : public UFGErrorMessage
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEM_LoggedOutFromOnlineService");
		return ptr;
	}

};


// Class FactoryGame.FGEM_LostConnectionWithOnlineService
// 0x0000 (0x0048 - 0x0048)
class UFGEM_LostConnectionWithOnlineService : public UFGErrorMessage
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEM_LostConnectionWithOnlineService");
		return ptr;
	}

};


// Class FactoryGame.FGEM_FailedToLoginToOnlineService
// 0x0000 (0x0048 - 0x0048)
class UFGEM_FailedToLoginToOnlineService : public UFGErrorMessage
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGEM_FailedToLoginToOnlineService");
		return ptr;
	}

};


// Class FactoryGame.FGLocalPlayer
// 0x00F0 (0x02B8 - 0x01C8)
class UFGLocalPlayer : public ULocalPlayer
{
public:
	unsigned char                                      UnknownData00[0x58];                                      // 0x01C8(0x0058) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnLoginStateChanged;                                     // 0x0220(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnFriendsListUpdated;                                    // 0x0230(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnFriendsPresenceUpdated;                                // 0x0240(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnInviteReceived;                                        // 0x0250(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x58];                                      // 0x0260(0x0058) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGLocalPlayer");
		return ptr;
	}


	void UpdatePresence();
	void OpenMap_SetupServer();
	class FString GetUsername();
	TEnumAsByte<ELoginState> GetLoginState();
	bool GetFriendList(TArray<struct FFGOnlineFriend>* out_friends);
	void CreateOfflineSession_SetupServer(bool startOffline);
	void AutoLogin();
};


// Class FactoryGame.FGLocomotive
// 0x0078 (0x0590 - 0x0518)
class AFGLocomotive : public AFGRailroadVehicle
{
public:
	struct FFloatInterval                              mPowerConsumption;                                        // 0x0518(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGPowerConnectionComponent*                 mSlidingShoe;                                             // 0x0520(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGPowerInfoComponent*                       mPowerInfo;                                               // 0x0528(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FTransform                                  mReplicatedMovementTransform;                             // 0x0530(0x0030) (Net, IsPlainOldData)
	class UFGLocomotiveMovementComponent*              mVehicleMovement;                                         // 0x0560(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x28];                                      // 0x0568(0x0028) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGLocomotive");
		return ptr;
	}


	void UpdateTargetPoints(float MaxDistance);
	bool UpdatePathSegment();
	void SetSelfDrivingEnabled(bool IsEnabled);
	bool SetPath(const struct FRailroadPathFindingResult& Result);
	bool SetMultipleUnitControlMaster(bool Force);
	void ReportSelfDrivingError(ESelfDrivingLocomotiveError Error);
	void OnRep_ReplicatedMovementTransform();
	bool IsSelfDrivingEnabled();
	bool HasPath();
	void GetTargetPoints(TArray<struct FRailroadPathPoint>* out_points);
	ESelfDrivingLocomotiveError GetSelfDrivingError();
	class UFGPowerInfoComponent* GetPowerInfo();
	void GetPath(TArray<struct FRailroadPathPoint>* out_points);
	EMultipleUnitControl GetMultipleUnitRole();
	class UFGLocomotiveMovementComponent* GetLocomotiveMovementComponent();
	void ClearSelfDrivingError();
	void ClearPath();
	void ClearMultipleUnitControlMaster();
	bool CanSetTrainMultipleUnitMaster();
};


// Class FactoryGame.FGRailroadVehicleMovementComponent
// 0x00C0 (0x0240 - 0x0180)
class UFGRailroadVehicleMovementComponent : public UPawnMovementComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0180(0x0008) MISSED OFFSET
	TArray<struct FWheelsetSetup>                      mWheelsetSetups;                                          // 0x0188(0x0010) (Edit, ZeroConstructor)
	float                                              mWheelRadius;                                             // 0x0198(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x019C(0x0004) MISSED OFFSET
	TArray<struct FCouplerSetup>                       mCouplerSetups;                                           // 0x01A0(0x0010) (Edit, ZeroConstructor)
	unsigned char                                      UnknownData02[0x34];                                      // 0x01B0(0x0034) MISSED OFFSET
	float                                              mMass;                                                    // 0x01E4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mMaxVelocity;                                             // 0x01E8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mPayloadMass;                                             // 0x01EC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mDragCoefficient;                                         // 0x01F0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mChassisWidth;                                            // 0x01F4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mChassisHeight;                                           // 0x01F8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mRollingResistanceCoefficient;                            // 0x01FC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mCurvatureResistanceCoefficient;                          // 0x0200(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mMaxAirBrakingEffort;                                     // 0x0204(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x38];                                      // 0x0208(0x0038) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadVehicleMovementComponent");
		return ptr;
	}


	void SetPayloadMass(float payload);
	bool IsMoving();
	struct FVector GetWheelsetRotation(int Index);
	float GetWheelsetOffset(int Index);
	float GetWheelsetAngle();
	float GetWheelRotation();
	float GetTractiveForce();
	float GetTrackGrade();
	float GetTrackCurvature();
	float GetRelativeForwardSpeed();
	float GetPayloadMass();
	int GetNumWheelsets();
	float GetMaxForwardSpeed();
	float GetMaxAirBrakingEffort();
	float GetMass();
	float GetForwardSpeed();
	float GetDynamicBrakingForce();
	struct FVector GetCouplerRotationAndExtention(int Index, float* out_extention);
	float GetBrakingForce();
	float GetAirBrakingForce();
};


// Class FactoryGame.FGLocomotiveMovementComponent
// 0x0158 (0x0398 - 0x0240)
class UFGLocomotiveMovementComponent : public UFGRailroadVehicleMovementComponent
{
public:
	struct FReplicatedRailroadVehicleState             mReplicatedState;                                         // 0x0240(0x0014) (Net, ZeroConstructor, Transient, IsPlainOldData)
	int                                                mRawReverserInput;                                        // 0x0254(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mRawSteeringInput;                                        // 0x0258(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mRawThrottleInput;                                        // 0x025C(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mRawDynamicBrakeInput;                                    // 0x0260(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mRawAirBrakeInput;                                        // 0x0264(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	struct FRailroadVehicleInputRate                   mThrottleInputRate;                                       // 0x0268(0x0008) (Edit)
	struct FRailroadVehicleInputRate                   mDynamicBrakeInputRate;                                   // 0x0270(0x0008) (Edit)
	float                                              mDynamicBrakeVelocityThreshold;                           // 0x0278(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FRailroadVehicleInputRate                   mAirBrakeInputRate;                                       // 0x027C(0x0008) (Edit)
	int                                                mReverserInput;                                           // 0x0284(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mSteeringInput;                                           // 0x0288(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mThrottleInput;                                           // 0x028C(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mAirBrakeInput;                                           // 0x0290(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              mDynamicBrakeInput;                                       // 0x0294(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	struct FRuntimeFloatCurve                          mTractiveEffortCurve;                                     // 0x0298(0x0078) (Edit)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0310(0x0008) MISSED OFFSET
	struct FRuntimeFloatCurve                          mDynamicBrakingEffortCurve;                               // 0x0318(0x0078) (Edit)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0390(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGLocomotiveMovementComponent");
		return ptr;
	}


	void UseReplicatedState();
	void SetThrottleInput(float Throttle);
	void SetSteeringInput(float Steering);
	void SetReverserInput(int reverser);
	void SetEmergencyBrake();
	void SetAirBrakeInput(float Brake);
	void ServerUpdateState(int inReverserInput, float InSteeringInput, float InThrottleInput, float inDynamicBrakeInput, float inAirBrakeInput);
	float GetThrottle();
	int GetReverser();
	float GetMaxTractiveEffort();
	float GetMaxDynamicBrakingEffort();
	float GetDynamicBrake();
	float GetAirBrake();
};


// Class FactoryGame.FGLootSettings
// 0x0000 (0x0028 - 0x0028)
class UFGLootSettings : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGLootSettings");
		return ptr;
	}


	class UObject* GetLootSettingsDefaultObject(class UClass* inClass);
};


// Class FactoryGame.FGManta
// 0x0040 (0x0368 - 0x0328)
class AFGManta : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class USplineComponent*                            mCachedSpline;                                            // 0x0330(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AFGSplinePath*                               mSplinePath;                                              // 0x0338(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class USkeletalMeshComponent*                      mCachedMesh;                                              // 0x0340(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0348(0x0004) MISSED OFFSET
	float                                              mCurrentTime;                                             // 0x034C(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mOffsetMagnitude;                                         // 0x0350(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSecondsPerLoop;                                          // 0x0354(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0358(0x0004) MISSED OFFSET
	float                                              mSignificanceRange;                                       // 0x035C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mTickTransform;                                           // 0x0360(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsClosedSplineLoop;                                      // 0x0361(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x6];                                       // 0x0362(0x0006) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGManta");
		return ptr;
	}


	class USplineComponent* GetSpline();
	float GetCurrentTime();
};


// Class FactoryGame.FGManufacturingButton
// 0x0030 (0x0238 - 0x0208)
class UFGManufacturingButton : public UUserWidget
{
public:
	struct FScriptMulticastDelegate                    OnManufacturePressed;                                     // 0x0208(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mMinTimeBetweenPress;                                     // 0x0218(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x021C(0x0008) MISSED OFFSET
	float                                              mHoldTimeMax;                                             // 0x0224(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHoldProduceSpeed;                                        // 0x0228(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0xC];                                       // 0x022C(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGManufacturingButton");
		return ptr;
	}


	void SetButton(class UButton* inButton);
	void OnReleasedButton();
	void OnPressedButton();
};


// Class FactoryGame.FGMapArea
// 0x0038 (0x0060 - 0x0028)
class UFGMapArea : public UObject
{
public:
	struct FText                                       mDisplayName;                                             // 0x0028(0x0028) (Edit, DisableEditOnInstance)
	class UClass*                                      mZoneType;                                                // 0x0040(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FText                                       mUserSetDisplayName;                                      // 0x0048(0x0028)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapArea");
		return ptr;
	}


	class UClass* GetZoneType(class UClass* inClass);
	struct FText GetUserSetAreaDisplayName(class UClass* inClass);
	struct FText GetAreaDisplayName(class UClass* inClass);
};


// Class FactoryGame.FGMapAreaTexture
// 0x0058 (0x0080 - 0x0028)
class UFGMapAreaTexture : public UObject
{
public:
	class UTexture2D*                                  mFogOfWarTexture;                                         // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<unsigned char>                              mAreaData;                                                // 0x0030(0x0010) (ZeroConstructor)
	TArray<struct FColor>                              mColorPalette;                                            // 0x0040(0x0010) (ZeroConstructor)
	TArray<struct FColorMapAreaPair>                   mColorToArea;                                             // 0x0050(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class AFGMinimapCaptureActor*                      mCaptureActor;                                            // 0x0060(0x0008) (ZeroConstructor, IsPlainOldData)
	int                                                mDataWidth;                                               // 0x0068(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x006C(0x000C) MISSED OFFSET
	class AFGGameState*                                mCachedGameState;                                         // 0x0078(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapAreaTexture");
		return ptr;
	}


	void OnNewMapAreaVisisted(class UClass* newMapArea);
	class UTexture2D* GetFogOfWarTexture();
};


// Class FactoryGame.FGMapAreaZoneDescriptor
// 0x0010 (0x0038 - 0x0028)
class UFGMapAreaZoneDescriptor : public UObject
{
public:
	class FString                                      mZoneType;                                                // 0x0028(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapAreaZoneDescriptor");
		return ptr;
	}


	void GetZoneType(class FString* out_zoneType);
};


// Class FactoryGame.FGMapFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGMapFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapFunctionLibrary");
		return ptr;
	}


	void GetWorldBounds(class UObject* WorldContext, struct FVector2D* Min, struct FVector2D* Max);
	struct FVector2D GetNormalizedPosition(class AFGMinimapCaptureActor* minimapCaptureActor, const struct FVector& WorldLocation);
	class AFGMinimapCaptureActor* GetMinimapCaptureActor(class UObject* WorldContext);
	struct FVector2D GetMapPosition(class AFGMinimapCaptureActor* minimapCaptureActor, const struct FVector& WorldLocation, float mapResolution);
	float GetMapDistance(class AFGMinimapCaptureActor* minimapCaptureActor, float worldDistance, float mapResolution);
};


// Class FactoryGame.FGMapManager
// 0x0098 (0x03C0 - 0x0328)
class AFGMapManager : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	TArray<unsigned char>                              mFogOfWarRawData;                                         // 0x0330(0x0010) (ZeroConstructor, SaveGame)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0340(0x0010) MISSED OFFSET
	class UTexture2D*                                  mFogOfWarTexture;                                         // 0x0350(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x18];                                      // 0x0358(0x0018) MISSED OFFSET
	class AFGMinimapCaptureActor*                      mCachedMinimapCaptureActor;                               // 0x0370(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x18];                                      // 0x0378(0x0018) MISSED OFFSET
	TArray<struct FFogOfWarQueuePair>                  mFogOfWarTransferQueue;                                   // 0x0390(0x0010) (ZeroConstructor)
	class AFGActorRepresentationManager*               mActorRepresentationManager;                              // 0x03A0(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	TArray<class UFGActorRepresentation*>              mDynamicFogOfWarRevealActors;                             // 0x03A8(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData04[0x8];                                       // 0x03B8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapManager");
		return ptr;
	}


	void OnActorRepresentationUpdated(class UFGActorRepresentation* actorRepresentation);
	void OnActorRepresentationRemoved(class UFGActorRepresentation* actorRepresentation);
	void OnActorRepresentationAdded(class UFGActorRepresentation* actorRepresentation);
	class UTexture2D* GetFogOfWarTexture();
	class AFGMapManager* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGMapObjectWidget
// 0x0020 (0x0228 - 0x0208)
class UFGMapObjectWidget : public UUserWidget
{
public:
	class UFGActorRepresentation*                      mActorRepresentation;                                     // 0x0208(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class UFGMapWidget*                                mMapWidget;                                               // 0x0210(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0218(0x0008) MISSED OFFSET
	class AFGMinimapCaptureActor*                      mMinimapCaptureActor;                                     // 0x0220(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapObjectWidget");
		return ptr;
	}


	void OnObjectMoved(const struct FVector2D& normalizedLocation);
	void OnObjectFiltered(bool FilteredIn);
	void OnActorRepresentationUpdated();
};


// Class FactoryGame.FGMapWidget
// 0x0020 (0x0228 - 0x0208)
class UFGMapWidget : public UUserWidget
{
public:
	class UTexture2D*                                  mFogOfWarTexture;                                         // 0x0208(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UFGActorRepresentation*>              mMapActors;                                               // 0x0210(0x0010) (ZeroConstructor)
	class AFGActorRepresentationManager*               mActorRepresentationManager;                              // 0x0220(0x0008) (ZeroConstructor, Transient, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMapWidget");
		return ptr;
	}


	void OnObjectUpdatedOnMap(class UFGActorRepresentation* actorRepresentation);
	void OnObjectRemovedFromMap(class UFGActorRepresentation* actorRepresentation);
	void OnObjectAddedToMap(class UFGActorRepresentation* actorRepresentation);
	void OnMapCentered(const struct FVector2D& normalizedWorldLocation);
	void OnActorRepresentationUpdated(class UFGActorRepresentation* actorRepresentation);
	void OnActorRepresentationRemoved(class UFGActorRepresentation* actorRepresentation);
	void OnActorRepresentationAdded(class UFGActorRepresentation* actorRepresentation);
	class UTexture2D* GetFogOfWarTexture();
};


// Class FactoryGame.FGMaterialEffectComponent
// 0x0050 (0x0140 - 0x00F0)
class UFGMaterialEffectComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x00F0(0x0020) MISSED OFFSET
	TArray<class UMeshComponent*>                      mMeshes;                                                  // 0x0110(0x0010) (ExportObject, ZeroConstructor)
	class UMaterialInterface*                          mMaterial;                                                // 0x0120(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x0128(0x0006) MISSED OFFSET
	bool                                               mAutoDestroy;                                             // 0x012E(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1];                                       // 0x012F(0x0001) MISSED OFFSET
	TArray<class UMaterialInstanceDynamic*>            mMids;                                                    // 0x0130(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMaterialEffectComponent");
		return ptr;
	}


	void SetMeshes(TArray<class UMeshComponent*> meshes);
	void SetMaterialScalarParameterValue(const struct FName& Name, float Value);
	void SetDuration(float Duration);
	void PreStarted();
	void OnUpdate(float DeltaTime);
	void OnStarted();
	void OnEnded();
	void GetMeshesBounds(bool onlyVisible, bool onlyColliding, struct FVector* out_origin, struct FVector* out_boxExtent);
	TArray<class UMeshComponent*> GetMeshes();
	float GetDuration();
};


// Class FactoryGame.FGMaterialEffect_Build
// 0x0020 (0x0160 - 0x0140)
class UFGMaterialEffect_Build : public UFGMaterialEffectComponent
{
public:
	class AActor*                                      mInstigator;                                              // 0x0140(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<struct FItemAmount>                         mCost;                                                    // 0x0148(0x0010) (ZeroConstructor)
	float                                              mSpeed;                                                   // 0x0158(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x015C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMaterialEffect_Build");
		return ptr;
	}


	float GetSpeed();
	class AActor* GetInstigator();
	TArray<struct FItemAmount> GetCost();
};


// Class FactoryGame.FGMaterialFlowAnalysisFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGMaterialFlowAnalysisFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMaterialFlowAnalysisFunctionLibrary");
		return ptr;
	}


	struct FMaterialFlowGraph PerformMaterialFlowAnalysis(TArray<class UClass*> recipes, class AFGRecipeManager* recipeManager);
	TArray<struct FMaterialFlowNode> GetGraphNodes(const struct FMaterialFlowGraph& graph, int Depth);
	int GetGraphDepth(const struct FMaterialFlowGraph& graph);
};


// Class FactoryGame.FGMenuBase
// 0x0008 (0x0210 - 0x0208)
class UFGMenuBase : public UUserWidget
{
public:
	class UFGWidgetSwitcher*                           mCachedOwner;                                             // 0x0208(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMenuBase");
		return ptr;
	}


	void OnMenuExitDone();
	void OnMenuExit(class UWidget* prevMenu, bool noAnimation);
	void OnMenuEnterDone();
	void OnMenuEnter(class UWidget* prevMenu);
};


// Class FactoryGame.FGMessageSender
// 0x0038 (0x0060 - 0x0028)
class UFGMessageSender : public UObject
{
public:
	struct FText                                       mSenderName;                                              // 0x0028(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	struct FText                                       mSenderMail;                                              // 0x0040(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	class UTexture2D*                                  mTexture;                                                 // 0x0058(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMessageSender");
		return ptr;
	}


	class UObject* GetSenderDefaultObject(class UClass* inClass);
};


// Class FactoryGame.FGHeightWaterUserData
// 0x0000 (0x0028 - 0x0028)
class UFGHeightWaterUserData : public UAssetUserData
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHeightWaterUserData");
		return ptr;
	}

};


// Class FactoryGame.FGHeightFoliageUserData
// 0x0000 (0x0028 - 0x0028)
class UFGHeightFoliageUserData : public UAssetUserData
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHeightFoliageUserData");
		return ptr;
	}

};


// Class FactoryGame.FGHeightHideUserData
// 0x0000 (0x0028 - 0x0028)
class UFGHeightHideUserData : public UAssetUserData
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGHeightHideUserData");
		return ptr;
	}

};


// Class FactoryGame.FGMinimapCaptureActor
// 0x0008 (0x0340 - 0x0338)
class AFGMinimapCaptureActor : public ASceneCapture2D
{
public:
	class UFGMapAreaTexture*                           mMapAreaTexture;                                          // 0x0338(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMinimapCaptureActor");
		return ptr;
	}


	class UFGMapAreaTexture* GetMapAreaTexture();
};


// Class FactoryGame.FGMultiplayerVerticalBox
// 0x0000 (0x0128 - 0x0128)
class UFGMultiplayerVerticalBox : public UVerticalBox
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMultiplayerVerticalBox");
		return ptr;
	}


	void Sort();
};


// Class FactoryGame.FGMusicManager
// 0x0038 (0x0060 - 0x0028)
class UFGMusicManager : public UObject
{
public:
	float                                              mUpdateInterval;                                          // 0x0028(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFactoryCloseDistance;                                    // 0x002C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkObject*                                   mAkObject;                                                // 0x0030(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData)
	struct FSoftClassPath                              mMusicManagerClassName;                                   // 0x0038(0x0018) (ZeroConstructor, Config, GlobalConfig)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0050(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGMusicManager");
		return ptr;
	}


	void Stop();
	void Play();
	void Pause();
	void OnPlayerNearBaseChanged(bool isNear);
	void OnPlayerEnteredArea(class UClass* mapArea);
	void NotifyPostLoadMap(class UWorld* loadedWorld, class AWorldSettings* WorldSettings);
	class UFGMusicManager* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGNavArea_Water
// 0x0000 (0x0048 - 0x0048)
class UFGNavArea_Water : public UNavArea
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNavArea_Water");
		return ptr;
	}

};


// Class FactoryGame.FGPresenceLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGPresenceLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPresenceLibrary");
		return ptr;
	}


	bool NetIdHasValidPresence(class UObject* WorldContext, const struct FUniqueNetIdRepl& netId);
	bool IsValid_OnlinePresence(const struct FOnlinePresence& A);
	bool IsPlayingThisGame(const struct FOnlinePresence& presence);
	bool IsPlayingOtherGame(const struct FOnlinePresence& presence);
	bool IsOnline(const struct FOnlinePresence& presence);
	struct FBlueprintSessionResult GetSessionFromPresence(const struct FOnlinePresence& presence);
	class FString GetPresenceString(const struct FOnlinePresence& presence);
	struct FOnlinePresence GetPresenceFromNetId(class UObject* WorldContext, const struct FUniqueNetIdRepl& netId);
};


// Class FactoryGame.FGFriendsLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGFriendsLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGFriendsLibrary");
		return ptr;
	}


	bool IsWaitingForData(class ULocalPlayer* friendOf, const struct FFGOnlineFriend& onlineFriend);
	bool IsValid_Friend(const struct FFGOnlineFriend& A);
	TEnumAsByte<ECantJoinReason> IsFriendJoinable(class ULocalPlayer* friendOf, const struct FFGOnlineFriend& onlineFriend);
	struct FUniqueNetIdRepl GetFriendUniqueNetId(const struct FFGOnlineFriend& onlineFriend);
	bool GetFriendName(class ULocalPlayer* friendOf, const struct FFGOnlineFriend& onlineFriend, class FString* out_displayName);
	struct FFGOnlineFriend GetFriendFromNetId(class ULocalPlayer* friendOf, const struct FUniqueNetIdRepl& netId);
	bool EqualEqual_FriendFriend(const struct FFGOnlineFriend& A, const struct FFGOnlineFriend& B);
};


// Class FactoryGame.FGSessionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGSessionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSessionLibrary");
		return ptr;
	}


	void SetSessionVisibility(class UObject* WorldContext, TEnumAsByte<ESessionVisibility> Visibility);
	void JoinSession(class UObject* WorldContext, const struct FBlueprintSessionResult& session);
	bool IsSessionValid(const struct FBlueprintSessionResult& session);
	bool IsInGameSession(class ULocalPlayer* LocalPlayer);
	bool InOnlineSession(class UObject* WorldContext, const struct FUniqueNetIdRepl& PlayerId);
	TEnumAsByte<ESessionVisibility> GetSessionVisibility(const struct FBlueprintSessionResult& session);
	struct FFGOnlineSessionSettings GetSessionSettings(const struct FBlueprintSessionResult& session);
	struct FBlueprintSessionResult GetMySession(class ULocalPlayer* LocalPlayer);
	int GetMaxNumberOfPlayers(const struct FBlueprintSessionResult& session);
};


// Class FactoryGame.FGInviteLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGInviteLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGInviteLibrary");
		return ptr;
	}


	void SendInviteToFriend(class ULocalPlayer* fromPlayer, const struct FFGOnlineFriend& toFriend);
	void JoinInvite(class UObject* WorldContext, const struct FPendingInvite& invite);
	void GetPendingInvites(class UObject* WorldContext, TArray<struct FPendingInvite>* out_invites);
	struct FUniqueNetIdRepl GetInviteSenderUniqueNetId(const struct FPendingInvite& invite);
	struct FPendingInvite GetInviteFromSender(class UObject* WorldContext, const struct FUniqueNetIdRepl& Sender);
	void DiscardInvite(class UObject* WorldContext, const struct FPendingInvite& invite);
};


// Class FactoryGame.FGNetworkLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGNetworkLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNetworkLibrary");
		return ptr;
	}


	bool SubmitFeedback(const struct FUserFeedbackFrontEndData& frontEndFeedbackData, class APlayerController* PlayerController);
	void QueryNATType(class UObject* WorldContext);
	bool OpenWebURL(const class FString& URL);
	struct FText NATTypeToText(ECachedNATType natType);
	bool IsValid_UniqueNetId(const struct FUniqueNetIdRepl& A);
	bool IsServer(class UObject* WorldContext);
	bool GetNameFromUniqueNetId(class ULocalPlayer* querier, const struct FUniqueNetIdRepl& netId, class FString* out_name);
	ECachedNATType GetCachedNATType(class UObject* WorldContext);
	bool EqualEqual_NetIdNetId(const struct FUniqueNetIdRepl& A, const struct FUniqueNetIdRepl& B);
};


// Class FactoryGame.FGNewsFeedActor
// 0x0050 (0x0378 - 0x0328)
class AFGNewsFeedActor : public AActor
{
public:
	struct FScriptMulticastDelegate                    mOnNewsReceived;                                          // 0x0328(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FText                                       mNewFeedText;                                             // 0x0338(0x0028) (BlueprintVisible, BlueprintReadOnly)
	struct FText                                       mNewsFeedRequestFailedText;                               // 0x0350(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	TArray<struct FNewsFeedMap>                        mNewsFeedURLs;                                            // 0x0368(0x0010) (ZeroConstructor, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNewsFeedActor");
		return ptr;
	}

};


// Class FactoryGame.FGNobeliskDetonator
// 0x0070 (0x0480 - 0x0410)
class AFGNobeliskDetonator : public AFGWeapon
{
public:
	struct FProjectileData                             mExplosiveData;                                           // 0x0410(0x0030) (Edit, DisableEditOnInstance)
	class UClass*                                      mExplosiveClass;                                          // 0x0440(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class AFGNobeliskExplosive*>                mDispensedExplosives;                                     // 0x0448(0x0010) (ZeroConstructor, SaveGame)
	bool                                               mIsPendingExecuteFire;                                    // 0x0458(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0459(0x0003) MISSED OFFSET
	float                                              mMaxChargeTime;                                           // 0x045C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMaxThrowForce;                                           // 0x0460(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMinThrowForce;                                           // 0x0464(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDelayBetweenExplosions;                                  // 0x0468(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x14];                                      // 0x046C(0x0014) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNobeliskDetonator");
		return ptr;
	}


	void Server_StartDetonations();
	void Server_SpawnExplosive(const struct FTransform& SpawnTransform, int throwForce);
	void Server_ExecuteSecondaryFire();
	void Server_ExecutePrimaryFire();
	void OnViewportFocusChanged(bool IsOpen, class UClass* interactionClass);
	void OnSecondaryFirePressed();
	float GetChargePct();
	void ExecuteSecondaryFire();
	void ExecutePrimaryFire();
};


// Class FactoryGame.FGWeaponAttachment
// 0x0010 (0x0370 - 0x0360)
class AFGWeaponAttachment : public AFGEquipmentAttachment
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0360(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWeaponAttachment");
		return ptr;
	}


	void PlayFireEffect(const struct FVector& flashLocation);
	void Multicast_SetFlashLocation(const struct FVector& newFlashLocation);
	void Multicast_PlayReloadEffectMulticast();
	void ClientPlayReloadEffect();
};


// Class FactoryGame.FGNobeliskDetonatorAttachment
// 0x0008 (0x0378 - 0x0370)
class AFGNobeliskDetonatorAttachment : public AFGWeaponAttachment
{
public:
	bool                                               mIsLoaded;                                                // 0x0370(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0371(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNobeliskDetonatorAttachment");
		return ptr;
	}


	void OnIsLoadedSet();
	void Multicast_SetIsLoaded(bool isLoaded);
};


// Class FactoryGame.FGNobeliskExplosive
// 0x0028 (0x0400 - 0x03D8)
class AFGNobeliskExplosive : public AFGDestructiveProjectile
{
public:
	class URotatingMovementComponent*                  mRotatingMovementComp;                                    // 0x03D8(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	float                                              mDetonateIn;                                              // 0x03E0(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x03E4(0x0004) MISSED OFFSET
	class USphereComponent*                            mEnvironmentDestructionSphere;                            // 0x03E8(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FRotator                                    mThrowRotation;                                           // 0x03F0(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03FC(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNobeliskExplosive");
		return ptr;
	}


	void OnRep_DetonateIn();
};


// Class FactoryGame.FGNobeliskExplosiveAttachment
// 0x0008 (0x0378 - 0x0370)
class AFGNobeliskExplosiveAttachment : public AFGWeaponAttachment
{
public:
	bool                                               mIsLoaded;                                                // 0x0370(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0371(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNobeliskExplosiveAttachment");
		return ptr;
	}


	void OnIsLoadedSet();
	void OnBeginFireEffect(const struct FVector& Location);
	void Multicast_SetIsLoaded(bool isLoaded);
	void Multicast_PlayBeginFireEffect(const struct FVector& Location);
};


// Class FactoryGame.FGNoneDescriptor
// 0x0000 (0x0128 - 0x0128)
class UFGNoneDescriptor : public UFGItemDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGNoneDescriptor");
		return ptr;
	}

};


// Class FactoryGame.FGObjectScanner
// 0x00B8 (0x0478 - 0x03C0)
class AFGObjectScanner : public AFGEquipment
{
public:
	float                                              mBeepDelayMax;                                            // 0x03C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mBeepDelayMin;                                            // 0x03C4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDetectionRange;                                          // 0x03C8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mUpdateClosestObjectTime;                                 // 0x03CC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FScannableDetails>                   mObjectDetails;                                           // 0x03D0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class AActor*                                      mClosestObject;                                           // 0x03E0(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mShouldBeepEvenIfNoObject;                                // 0x03E8(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8F];                                      // 0x03E9(0x008F) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGObjectScanner");
		return ptr;
	}


	void UpdateScannerVisuals(bool wasChange);
	void SetScannableEntry(class UClass* ScannableClass);
	void PlayBeep(bool isObjectInRange);
	bool IsBeeping();
	struct FScannableDetails GetCurrentDetails();
	TArray<struct FScannableDetails> GetAvailableObjectDetails();
	bool CycleForward();
	bool CycleBackward();
};


// Class FactoryGame.FGObjectScannerAttachment
// 0x0008 (0x0368 - 0x0360)
class AFGObjectScannerAttachment : public AFGEquipmentAttachment
{
public:
	bool                                               mIsBeeping;                                               // 0x0360(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0361(0x0003) MISSED OFFSET
	struct FColor                                      mScannerLightColor;                                       // 0x0364(0x0004) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGObjectScannerAttachment");
		return ptr;
	}


	void UpdateScannerVisuals();
	void OnRep_ScannerLightColor();
	void OnRep_IsBeeping();
	bool IsBeeping();
	struct FColor GetScannerLightColor();
};


// Class FactoryGame.FGOnlineSessionClient
// 0x0030 (0x01C0 - 0x0190)
class UFGOnlineSessionClient : public UOnlineSessionClient
{
public:
	unsigned char                                      UnknownData00[0x30];                                      // 0x0190(0x0030) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGOnlineSessionClient");
		return ptr;
	}

};


// Class FactoryGame.FGOutlineComponent
// 0x0110 (0x0350 - 0x0240)
class UFGOutlineComponent : public USceneComponent
{
public:
	class AActor*                                      mActiveOutlineActor;                                      // 0x0240(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class AActor*>                              mActiveMultiOutlineActors;                                // 0x0248(0x0010) (ZeroConstructor)
	TMap<class AActor*, struct FCachedMeshToMaterialObject> mCachedActorMaterials;                                    // 0x0258(0x0050) (ZeroConstructor)
	TMap<class UFGSplineComponent*, struct FCachedSplineMeshToMaterialObject> mCachedSplineComponentMaterials;                          // 0x02A8(0x0050) (ZeroConstructor)
	TMap<class UProxyInstancedStaticMeshComponent*, struct FCachedMaterialInterfaceArray> mCachedProxyMeshMaterials;                                // 0x02F8(0x0050) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0348(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGOutlineComponent");
		return ptr;
	}


	void UpdateProxyOutlineMesh(class UStaticMesh* newOutlineMesh);
	void UpdateProxyOutlineLocationAndRotation(const struct FVector& NewLocation, const struct FRotator& NewRotation);
	void ShowProxyOutline(class UStaticMesh* outlineMesh, const struct FTransform& Transform, EOutlineColor Color);
	void ShowOutline(class AActor* actorToOutline, EOutlineColor Color);
	void ShowMultiActorOutline(TArray<class AActor*> actorsToOutline, EOutlineColor Color);
	bool IsOutlineVisible();
	void HideOutline();
	EOutlineColor GetOutlineColor();
};


// Class FactoryGame.FGParachuteCameraShake
// 0x0000 (0x0160 - 0x0160)
class UFGParachuteCameraShake : public UCameraShake
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGParachuteCameraShake");
		return ptr;
	}

};


// Class FactoryGame.FGParachute
// 0x0010 (0x03D0 - 0x03C0)
class AFGParachute : public AFGEquipment
{
public:
	float                                              mTerminalVelocityZ;                                       // 0x03C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x03C4(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGParachute");
		return ptr;
	}


	void OnDeployStop();
	void OnDeployed();
	struct FVector ModifyVelocity(float DeltaTime, const struct FVector& OldVelocity);
	bool IsDeployed();
};


// Class FactoryGame.FGParachuteAttachment
// 0x0008 (0x0368 - 0x0360)
class AFGParachuteAttachment : public AFGEquipmentAttachment
{
public:
	bool                                               mIsDeployed;                                              // 0x0360(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0361(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGParachuteAttachment");
		return ptr;
	}


	void OnRep_IsDeployed();
	void OnDeployStop();
	void OnDeployed();
};


// Class FactoryGame.FGPassengerSeat
// 0x0008 (0x03D0 - 0x03C8)
class AFGPassengerSeat : public AFGDriveablePawn
{
public:
	class AFGVehicle*                                  mOuterVehicle;                                            // 0x03C8(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPassengerSeat");
		return ptr;
	}


	void UpdateCamera();
	class AFGVehicle* GetOuterVehicle();
};


// Class FactoryGame.FGPlanet
// 0x0000 (0x0328 - 0x0328)
class AFGPlanet : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPlanet");
		return ptr;
	}


	void UpdatePreview();
};


// Class FactoryGame.FGPlayerControllerBase
// 0x0038 (0x06B0 - 0x0678)
class AFGPlayerControllerBase : public APlayerController
{
public:
	struct FScriptMulticastDelegate                    OnInputChanged;                                           // 0x0678(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	class UInputComponent*                             mDisableInputComponent;                                   // 0x0688(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UInputComponent*                             mEnableInputComponent;                                    // 0x0690(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FName>                               mAllowedInputWhenDead;                                    // 0x0698(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData00[0x8];                                       // 0x06A8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPlayerControllerBase");
		return ptr;
	}


	void SetMouseSensitivity(float newSense);
	void SetIsUsingGamepad(bool newIsUsingGamepad);
	void Server_UpdateCappedBandwidth(int Cap);
	void ResetInputBindings();
	bool RebindActionKey(const struct FFGKeyMapping& newKeyMapping);
	class FString GetPresenceString();
	float GetMouseSensitivityY();
	float GetMouseSensitivityX();
	float GetMouseSensitivity();
	struct FText GetKeyNameForAction(const struct FName& inAction, bool getGamepadKey);
	bool GetIsUsingGamepad();
	float GetDefaultMouseSensitivityY();
	float GetDefaultMouseSensitivityX();
	float GetDefaultMouseSensitivity();
	void FlushPressedKeys();
	void DiscardInput();
	void Client_UpdateCappedBandwidth(int Cap);
};


// Class FactoryGame.FGPlayerController
// 0x00F8 (0x07A8 - 0x06B0)
class AFGPlayerController : public AFGPlayerControllerBase
{
public:
	struct FScriptMulticastDelegate                    OnShortcutsLayoutChanged;                                 // 0x06B0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnShortcutChanged;                                        // 0x06C0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnToggleInventory;                                        // 0x06D0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnToggleInteractionUI;                                    // 0x06E0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    MapAreaEntered;                                           // 0x06F0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mDisabledInputGateChanged;                                // 0x0700(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	bool                                               mCanAffectAudioVolumes;                                   // 0x0710(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0711(0x0007) MISSED OFFSET
	TArray<class UFGRemoteCallObject*>                 mRemoteCallObjects;                                       // 0x0718(0x0010) (Net, ZeroConstructor)
	class UInputComponent*                             mInputComponentChords;                                    // 0x0728(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      mAttentionPingActorClass;                                 // 0x0730(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMapAreaCheckInterval;                                    // 0x0738(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x073C(0x0004) MISSED OFFSET
	class UClass*                                      mCurrentMapArea;                                          // 0x0740(0x0008) (ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                mMovementWindComp;                                        // 0x0748(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData02[0x18];                                      // 0x0750(0x0018) MISSED OFFSET
	bool                                               mIsRespawning;                                            // 0x0768(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0xF];                                       // 0x0769(0x000F) MISSED OFFSET
	class UFGMapAreaTexture*                           mCachedMapAreaTexture;                                    // 0x0778(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x1];                                       // 0x0780(0x0001) MISSED OFFSET
	bool                                               mRespawnFromDeath;                                        // 0x0781(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               mRespawnFromJoin;                                         // 0x0782(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData05[0x11];                                      // 0x0783(0x0011) MISSED OFFSET
	int                                                mMinPhotoModeFOV;                                         // 0x0794(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMaxPhotoModeFOV;                                         // 0x0798(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData06[0x4];                                       // 0x079C(0x0004) MISSED OFFSET
	class UInputComponent*                             mPhotomodeInputComponent;                                 // 0x07A0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPlayerController");
		return ptr;
	}


	void TrackAkMemoryPools();
	void TrackAkComponentsWithNoPositionOrOwner();
	void TrackAkComponents(bool byClass);
	void TogglePhotoModeInstructionsWidget();
	void TogglePhotoMode();
	void ToggleHiResPhotoMode();
	void TakePhoto();
	void Suicide();
	void StartRespawn();
	void SetSessionName(const class FString& newSessionName);
	void SetRecipeShortcutOnIndex(class UClass* Recipe, int onIndex);
	void SetDismantleShortcutOnIndex(int onIndex);
	void SetDisabledInputGate(const struct FDisabledInputGate& newDisabledInputGate);
	void Server_Suicide();
	void Server_StartRespawn();
	void Server_SpawnAttentionPingActor(const struct FVector& pingLocation, const struct FVector& pingNormal);
	void Server_SetRecipeShortcutOnIndex(class UClass* Recipe, int onIndex);
	void Server_SetDismantleShortcutOnIndex(int onIndex);
	void Server_SendChatMessage(const struct FChatMessageStruct& newMessage);
	void Server_Respawn();
	void Server_RequestFogOfWarData();
	void Server_FinishRespawn();
	void Server_DealRadialDamage(const struct FHitResult& impact, float Damage, float Radius, class UClass* DamageType, class AActor* inInstigator);
	void Server_DealImpactDamage(const struct FHitResult& impact, const struct FVector& forwardVector, float Damage, class UClass* DamageType, class AActor* inInstigator);
	class UFGRemoteCallObject* RegisterRemoteCallObjectClass(class UClass* inClass);
	void OnStartRespawn(bool isJoining);
	class UAkComponent* OnSetupMovementWind();
	void OnRep_IsRespawning();
	void OnPrimaryFire();
	void OnFinishRespawn();
	void OnDisabledInputGateChanged();
	bool NeedRespawn();
	void MaterialLookup(const class FString& ItemName);
	void MaterialFlowAnalysis(const class FString& recipeName);
	bool IsRespawning();
	bool IsInTutorialMode();
	void IncrementPhotoModeFOV();
	void GetValidShortcuts(TArray<class UFGHotbarShortcut*>* out_shortcuts);
	int GetShortcutIndexFromKey(const struct FKeyEvent& Key);
	class FString GetScreenshotPath(bool isHighRes);
	float GetScreenBasedObjectRadius(class AActor* Actor, float screenRadius);
	class UFGRemoteCallObject* GetRemoteCallObjectOfClass(class UClass* inClass);
	int GetRecipeShortcutIndex(class UClass* Recipe);
	bool GetPlayerHasMessage(class UClass* newMessage);
	int GetPhotoModeFOV();
	float GetObjectScreenRadius(class AActor* Actor, float boundingRadius);
	bool GetIsPhotoMode();
	bool GetHiResPhotoModeEnabled();
	int GetDismantleShortcutIndex();
	struct FDisabledInputGate GetDisabledInputGate();
	class UClass* GetCurrentMapArea();
	void GetAllShortcuts(TArray<class UFGHotbarShortcut*>* out_shortcuts);
	void ExecuteShortcut(int shortcutIndex);
	void EnterChatMessage(const class FString& inMessage);
	void EnablePhotoMode(bool IsEnabled);
	void DecrementPhotoModeFOV();
	void CreateSequenceList();
	void Client_WaitForLevelStreaming();
	void Client_TransferFogOfWarData(TArray<unsigned char> fogOfWarRawData, int Index);
	void Client_AddMessage(class UClass* newMessage);
	void CheckPawnMapArea();
};


// Class FactoryGame.FGPlayerStartTradingPost
// 0x0000 (0x0358 - 0x0358)
class AFGPlayerStartTradingPost : public APlayerStart
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPlayerStartTradingPost");
		return ptr;
	}

};


// Class FactoryGame.FGPlayerState
// 0x00B8 (0x04A8 - 0x03F0)
class AFGPlayerState : public APlayerState
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x03F0(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    BuildableConstructedDelegate;                             // 0x03F8(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0408(0x0010) MISSED OFFSET
	TArray<class UFGHotbarShortcut*>                   mHotbarShortcuts;                                         // 0x0418(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<class UClass*>                              mDefaultRecipeShortcuts;                                  // 0x0428(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UClass*>                              mNewRecipes;                                              // 0x0438(0x0010) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, SaveGame)
	int                                                mSlotNum;                                                 // 0x0448(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x044C(0x0004) MISSED OFFSET
	TArray<struct FSlotData>                           mSlotData;                                                // 0x0450(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	class APawn*                                       mOwnedPawn;                                               // 0x0460(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      mHasReceivedInitialItems : 1;                             // 0x0468(0x0001) (SaveGame)
	unsigned char                                      mHasSetupDefaultShortcuts : 1;                            // 0x0468(0x0001) (SaveGame)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0469(0x0007) MISSED OFFSET
	class UFGTutorialSubsystem*                        mTutorialSubsystem;                                       // 0x0470(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class UClass*                                      mTutorialSubsystemClass;                                  // 0x0478(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FMessageData>                        mMessageData;                                             // 0x0480(0x0010) (ZeroConstructor, SaveGame)
	TArray<class UClass*>                              mRememberedFirstTimeEquipmentClasses;                     // 0x0490(0x0010) (Net, ZeroConstructor, SaveGame)
	int                                                mNumArmSlots;                                             // 0x04A0(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData04[0x4];                                       // 0x04A4(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPlayerState");
		return ptr;
	}


	void Server_RemoveRecipe(class UClass* Recipe);
	void RemoveRecipe(class UClass* Recipe);
	void RemoveMessage(class UClass* inMessage);
	void ReadMessage(class UClass* inMessage);
	void OnRep_HotbarShortcuts();
	class FString GetUsername();
	class FString GetUserID();
	struct FUniqueNetIdRepl GetUniqeNetId();
	class UFGTutorialSubsystem* GetTutorialSubsystem();
	class FString GetSteamID();
	int GetSlotNum();
	TArray<struct FSlotData> GetSlotData();
	int GetNumArmSlots();
	TArray<class UClass*> GetAllMessages(EMessageType MessageType);
	TArray<struct FMessageData> GetAllMessageData();
	class UFGHotbarShortcut* CreateShortcut(class UClass* shortcutClass);
	void AddMessage(class UClass* inMessage);
	void AddArmSlots(int slotsToAdd);
};


// Class FactoryGame.FGPoleDescriptor
// 0x0010 (0x0160 - 0x0150)
class UFGPoleDescriptor : public UFGBuildingDescriptor
{
public:
	TArray<struct FPoleHeightMesh>                     mHeightMeshes;                                            // 0x0150(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPoleDescriptor");
		return ptr;
	}


	void GetHeightMeshes(class UClass* inClass, TArray<struct FPoleHeightMesh>* out_heightMeshes);
};


// Class FactoryGame.FGPopupInstigatorInterface
// 0x0000 (0x0028 - 0x0028)
class UFGPopupInstigatorInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPopupInstigatorInterface");
		return ptr;
	}


	void WidgetFactory(class UClass* PopupClass, TArray<class UUserWidget*>* out_widgets);
	void NotifyPopupClosed(class UClass* PopupClass, int exitCode);
};


// Class FactoryGame.FGPopupWidget
// 0x0030 (0x0288 - 0x0258)
class UFGPopupWidget : public UFGInteractWidget
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0258(0x0008) MISSED OFFSET
	struct FScriptDelegate                             mPopupConfirmClickedDelegate;                             // 0x0260(0x0014) (ZeroConstructor, InstancedReference, Deprecated)
	struct FScriptDelegate                             mPopupClosedDelegate;                                     // 0x0270(0x0014) (ZeroConstructor, InstancedReference)
	class UObject*                                     mInstigator;                                              // 0x0280(0x0008) (Edit, BlueprintVisible, ZeroConstructor, EditConst, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPopupWidget");
		return ptr;
	}


	void CallPopupConfirmClicked();
	void CallPopupClosedClicked(bool confirm);
};


// Class FactoryGame.FGPopupWidgetContent
// 0x0010 (0x0218 - 0x0208)
class UFGPopupWidgetContent : public UUserWidget
{
public:
	class UObject*                                     mInstigator;                                              // 0x0208(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UFGPopupWidget*                              mPopupWidget;                                             // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPopupWidgetContent");
		return ptr;
	}


	void SetOptionalTextElements(const struct FText& Title, const struct FText& Desc);
	void SetInstigatorAndInitialize(class UObject* Instigator);
	void NotifyPopupConfirmed();
	void NotifyPopupCanceled();
	bool GetShouldOkayBeEnabled();
};


// Class FactoryGame.FGPortableMiner
// 0x0040 (0x0368 - 0x0328)
class AFGPortableMiner : public AActor
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
	float                                              mExtractCycleTime;                                        // 0x0338(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
	class AFGResourceNode*                             mExtractResourceNode;                                     // 0x0340(0x0008) (BlueprintVisible, Net, ZeroConstructor, SaveGame, IsPlainOldData)
	class UFGInventoryComponent*                       mOutputInventory;                                         // 0x0348(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	float                                              mCurrentExtractProgress;                                  // 0x0350(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0354(0x0004) MISSED OFFSET
	class UClass*                                      mInteractWidgetClass;                                     // 0x0358(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mInventorySize;                                           // 0x0360(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsProducing;                                             // 0x0364(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x0365(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPortableMiner");
		return ptr;
	}


	void OnRep_IsProducing();
	bool IsProducing();
	class UFGInventoryComponent* GetOutputInventory();
	float GetExtractionProgress();
	TArray<struct FInventoryStack> GetDismantleInventoryReturns();
	bool CanProduce();
};


// Class FactoryGame.FGPortableMinerDispenser
// 0x0028 (0x03E8 - 0x03C0)
class AFGPortableMinerDispenser : public AFGEquipment
{
public:
	TArray<EResourceForm>                              mAllowedResourceForms;                                    // 0x03C0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mPlaceDistanceMax;                                        // 0x03D0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x03D4(0x0004) MISSED OFFSET
	class UMaterialInstance*                           mValidPlacementMaterial;                                  // 0x03D8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UMaterialInstance*                           mInvalidPlacementMaterial;                                // 0x03E0(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPortableMinerDispenser");
		return ptr;
	}


	void SpawnPortableMiner(class AFGResourceNode* resourceNode);
	void Server_PrimaryFire();
};


// Class FactoryGame.FGPowerCircuit
// 0x0068 (0x00C8 - 0x0060)
class UFGPowerCircuit : public UFGCircuit
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0060(0x0010) MISSED OFFSET
	float                                              mPowerProductionCapacity;                                 // 0x0070(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              mPowerProduced;                                           // 0x0074(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              mPowerConsumed;                                           // 0x0078(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsFuseTriggered;                                         // 0x007C(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x007D(0x0003) MISSED OFFSET
	struct FPowerCircuitStats                          mPowerStats;                                              // 0x0080(0x0048) (Net)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPowerCircuit");
		return ptr;
	}


	void ResetFuse();
	bool IsFuseTriggered();
	void GetStats(struct FPowerCircuitStats* out_stats);
	int GetNumGraphPoint(const struct FPowerCircuitStats& stats);
	bool GetGraphPointAtIndex(const struct FPowerCircuitStats& stats, int idx, struct FPowerGraphPoint* out_item);
};


// Class FactoryGame.FGPowerCircuitWidget
// 0x0018 (0x0220 - 0x0208)
class UFGPowerCircuitWidget : public UUserWidget
{
public:
	struct FScriptDelegate                             mGetPowerCircuitEvent;                                    // 0x0208(0x0014) (Edit, ZeroConstructor, InstancedReference)
	class UFGPowerCircuit*                             mPowerCircuit;                                            // 0x0218(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPowerCircuitWidget");
		return ptr;
	}


	class UFGPowerCircuit* GetPowerCircuit__DelegateSignature();
	class UFGPowerCircuit* GetPowerCircuit();
};


// Class FactoryGame.FGPowerConnectionComponent
// 0x0010 (0x02A0 - 0x0290)
class UFGPowerConnectionComponent : public UFGCircuitConnectionComponent
{
public:
	class UFGPowerInfoComponent*                       mPowerInfo;                                               // 0x0290(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0298(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPowerConnectionComponent");
		return ptr;
	}


	void SetPowerInfo(class UFGPowerInfoComponent* powerInfo);
	class UFGPowerInfoComponent* GetPowerInfo();
	class UFGPowerCircuit* GetPowerCircuit();
};


// Class FactoryGame.FGWallHologram
// 0x0008 (0x03F0 - 0x03E8)
class AFGWallHologram : public AFGFactoryBuildingHologram
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x03E8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWallHologram");
		return ptr;
	}

};


// Class FactoryGame.FGPoweredWallHologram
// 0x0000 (0x03F0 - 0x03F0)
class AFGPoweredWallHologram : public AFGWallHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPoweredWallHologram");
		return ptr;
	}

};


// Class FactoryGame.FGPowerInfoComponent
// 0x0028 (0x0118 - 0x00F0)
class UFGPowerInfoComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0xC];                                       // 0x00F0(0x000C) MISSED OFFSET
	int                                                mCircuitID;                                               // 0x00FC(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mTargetConsumption;                                       // 0x0100(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mActualConsumption;                                       // 0x0104(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mBaseProduction;                                          // 0x0108(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mDynamicProductionCapacity;                               // 0x010C(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mDynamicProductionDemandFactor;                           // 0x0110(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01 : 1;                                        // 0x0114(0x0001)
	unsigned char                                      mIsFuseTriggered : 1;                                     // 0x0114(0x0001) (Net)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0115(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPowerInfoComponent");
		return ptr;
	}


	void SetTargetConsumption(float newConsumption);
	void SetDynamicProductionCapacity(float newProduction);
	void SetBaseProduction(float newProduction);
	bool IsFuseTriggered();
	bool IsConnected();
	bool HasPower();
	float GetTargetConsumption();
	float GetRegulatedDynamicProduction();
	class UFGPowerCircuit* GetPowerCircuit();
	float GetDynamicProductionDemandFactor();
	float GetDynamicProductionCapacity();
	float GetBaseProduction();
	float GetActualConsumption();
};


// Class FactoryGame.FGPowerPoleHologram
// 0x0008 (0x03E8 - 0x03E0)
class AFGPowerPoleHologram : public AFGBuildableHologram
{
public:
	class UFGCircuitConnectionComponent*               mSnapConnection;                                          // 0x03E0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGPowerPoleHologram");
		return ptr;
	}

};


// Class FactoryGame.FGProceduralStaticMeshActor
// 0x0000 (0x0338 - 0x0338)
class AFGProceduralStaticMeshActor : public AStaticMeshActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGProceduralStaticMeshActor");
		return ptr;
	}

};


// Class FactoryGame.FGProductionIndicatorComponent
// 0x0028 (0x0118 - 0x00F0)
class UFGProductionIndicatorComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x00F0(0x0010) MISSED OFFSET
	class UMaterialInstanceDynamic*                    mIndicatorMaterial;                                       // 0x0100(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0108(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGProductionIndicatorComponent");
		return ptr;
	}

};


// Class FactoryGame.FGProductionIndicatorInstanceComponent
// 0x0020 (0x0610 - 0x05F0)
class UFGProductionIndicatorInstanceComponent : public UStaticMeshComponent
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x05F0(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGProductionIndicatorInstanceComponent");
		return ptr;
	}

};


// Class FactoryGame.FGProductionIndicatorInstanceManager
// 0x0070 (0x02B0 - 0x0240)
class UFGProductionIndicatorInstanceManager : public USceneComponent
{
public:
	unsigned char                                      UnknownData00[0x70];                                      // 0x0240(0x0070) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGProductionIndicatorInstanceManager");
		return ptr;
	}

};


// Class FactoryGame.FGProfileSpline
// 0x0008 (0x0330 - 0x0328)
class AFGProfileSpline : public AActor
{
public:
	float                                              Duration;                                                 // 0x0328(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x032C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGProfileSpline");
		return ptr;
	}


	void StartProfile();
};


// Class FactoryGame.FGRadiationInterface
// 0x0000 (0x0028 - 0x0028)
class UFGRadiationInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRadiationInterface");
		return ptr;
	}


	void ReceiveRadiation(float amount, float Duration, const struct FVector& Direction, class UClass* DamageType);
};


// Class FactoryGame.FGRadiationSettings
// 0x0078 (0x00B0 - 0x0038)
class UFGRadiationSettings : public UDeveloperSettings
{
public:
	class UClass*                                      mRadiationDamageType;                                     // 0x0038(0x0008) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mMaxIntensity;                                            // 0x0040(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mMinDamageInterval;                                       // 0x0044(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mMaxDamageInterval;                                       // 0x0048(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mDamagePerInterval;                                       // 0x004C(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mMinDistanceToSource;                                     // 0x0050(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mMinRadiationThreshold;                                   // 0x0054(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	float                                              mRadiationFalloffByDistance;                              // 0x0058(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x005C(0x0004) MISSED OFFSET
	TMap<TEnumAsByte<EResourcePurity>, int>            mNodeRadiationPurityAmounts;                              // 0x0060(0x0050) (Edit, ZeroConstructor, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRadiationSettings");
		return ptr;
	}

};


// Class FactoryGame.FGRadioactiveActor
// 0x0008 (0x0330 - 0x0328)
class AFGRadioactiveActor : public AActor
{
public:
	float                                              mRadioactiveDecay;                                        // 0x0328(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x032C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRadioactiveActor");
		return ptr;
	}

};


// Class FactoryGame.FGRadioactivitySubsystem
// 0x00A0 (0x03C8 - 0x0328)
class AFGRadioactivitySubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0328(0x0018) MISSED OFFSET
	TMap<class UObject*, struct FRadioactiveSource>    mSources;                                                 // 0x0340(0x0050) (ZeroConstructor)
	TArray<class AActor*>                              mAffectedActors;                                          // 0x0390(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x28];                                      // 0x03A0(0x0028) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRadioactivitySubsystem");
		return ptr;
	}


	void OnActorSpawned(class AActor* SpawnedActor);
	void OnActorDestroyed(class AActor* DestroyedActor);
	class AFGRadioactivitySubsystem* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGRailroadBridgeHologram
// 0x0078 (0x0470 - 0x03F8)
class AFGRailroadBridgeHologram : public AFGSplineHologram
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x03F8(0x0008) MISSED OFFSET
	class AFGBuildableFoundation*                      mSnappedFoundation[0x2];                                  // 0x0400(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x60];                                      // 0x0410(0x0060) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadBridgeHologram");
		return ptr;
	}

};


// Class FactoryGame.FGRailroadFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGRailroadFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadFunctionLibrary");
		return ptr;
	}


	bool IsValid(const struct FRailroadTrackPosition& Position);
	void GetWorldLocationAndDirection(const struct FRailroadTrackPosition& Position, struct FVector* out_location, struct FVector* out_direction);
	class AFGBuildableRailroadTrack* GetTrack(const struct FRailroadTrackPosition& Position);
	void DrawDebugTrackPosition(const struct FRailroadTrackPosition& Position, const struct FColor& Color, bool isPersistentLines);
	void DrawDebugRailroadPathResult(const struct FRailroadTrackPosition& Start, const struct FRailroadPathFindingResult& Result, bool isPersistentLines);
};


// Class FactoryGame.FGRailroadHologram
// 0x0018 (0x0460 - 0x0448)
class AFGRailroadHologram : public AFGFactoryHologram
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x0448(0x0004) MISSED OFFSET
	struct FRailroadTrackPosition                      mSnappedTrackPosition;                                    // 0x044C(0x0010)
	unsigned char                                      UnknownData01[0x4];                                       // 0x045C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadHologram");
		return ptr;
	}

};


// Class FactoryGame.FGRailroadInterface
// 0x0000 (0x0028 - 0x0028)
class UFGRailroadInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadInterface");
		return ptr;
	}


	void UnregisteredFromTrack();
	void RegisteredOnTrack(const struct FRailroadTrackPosition& Position);
	struct FRailroadTrackPosition GetTrackPosition();
	int GetTrackGraphID();
};


// Class FactoryGame.FGRailroadSubsystem
// 0x00C0 (0x03E8 - 0x0328)
class AFGRailroadSubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	float                                              mConnectDistance;                                         // 0x0330(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0334(0x0004) MISSED OFFSET
	class UClass*                                      mSwitchControlClass;                                      // 0x0338(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mVehicleSoundComponentClass;                              // 0x0340(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x18];                                      // 0x0348(0x0018) MISSED OFFSET
	TArray<class FString>                              mStationNames;                                            // 0x0360(0x0010) (ZeroConstructor)
	TMap<int, struct FTrackGraph>                      mTrackGraphs;                                             // 0x0370(0x0050) (ZeroConstructor)
	unsigned char                                      UnknownData03[0x8];                                       // 0x03C0(0x0008) MISSED OFFSET
	TArray<class AFGTrainStationIdentifier*>           mTrainStationIdentifiers;                                 // 0x03C8(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<class AFGTrain*>                            mTrains;                                                  // 0x03D8(0x0010) (Net, ZeroConstructor, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadSubsystem");
		return ptr;
	}


	void GetTrainStations(int trackID, TArray<class AFGTrainStationIdentifier*>* out_stations);
	void GetTrains(int trackID, TArray<class AFGTrain*>* out_trains);
	void GetAllTrainStations(TArray<class AFGTrainStationIdentifier*>* out_stations);
	void GetAllTrains(TArray<class AFGTrain*>* out_trains);
	class AFGRailroadSubsystem* Get(class UObject* WorldContext);
	struct FRailroadPathFindingResult FindPathSync(class AFGLocomotive* Locomotive, class AFGTrainStationIdentifier* Station);
};


// Class FactoryGame.FGRailroadSwitchHologram
// 0x0000 (0x0460 - 0x0460)
class AFGRailroadSwitchHologram : public AFGRailroadHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadSwitchHologram");
		return ptr;
	}

};


// Class FactoryGame.FGRailroadTimeTable
// 0x0028 (0x0350 - 0x0328)
class AFGRailroadTimeTable : public AInfo
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
	TArray<struct FTimeTableStop>                      mStops;                                                   // 0x0338(0x0010) (Net, ZeroConstructor, SaveGame)
	int                                                mCurrentStop;                                             // 0x0348(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x034C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadTimeTable");
		return ptr;
	}


	bool SetStops(TArray<struct FTimeTableStop> stops);
	void SetStopDuration(int Index, float Duration);
	void SetCurrentStop(int Index);
	void RemoveStop(int Index);
	bool IsValidStop(int Index);
	void GetStops(TArray<struct FTimeTableStop>* out_stops);
	struct FTimeTableStop GetStop(int Index);
	int GetNumStops();
	int GetMaxNumStops();
	int GetCurrentStop();
	bool AddStop(int Index, const struct FTimeTableStop& Stop);
};


// Class FactoryGame.FGRailroadTrackConnectionComponent
// 0x0030 (0x0270 - 0x0240)
class UFGRailroadTrackConnectionComponent : public UFGConnectionComponent
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0240(0x0018) MISSED OFFSET
	TArray<class UFGRailroadTrackConnectionComponent*> mConnectedComponents;                                     // 0x0258(0x0010) (ExportObject, ZeroConstructor, SaveGame)
	int                                                mSwitchPosition;                                          // 0x0268(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x026C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadTrackConnectionComponent");
		return ptr;
	}


	void SetSwitchPosition(int Position);
	int GetSwitchPosition();
	int GetNumSwitchPositions();
	class UFGRailroadTrackConnectionComponent* GetConnection(int Position);
};


// Class FactoryGame.FGRailroadTrackHologram
// 0x0068 (0x0460 - 0x03F8)
class AFGRailroadTrackHologram : public AFGSplineHologram
{
public:
	float                                              mMinLength;                                               // 0x03F8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxLength;                                               // 0x03FC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMinBendRadius;                                           // 0x0400(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxGrade;                                                // 0x0404(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSnapDistance;                                            // 0x0408(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x040C(0x0004) MISSED OFFSET
	class UFGRailroadTrackConnectionComponent*         mConnectionComponents[0x2];                               // 0x0410(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGRailroadTrackConnectionComponent*         mSnappedConnectionComponents[0x2];                        // 0x0420(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<class USplineMeshComponent*>                mSplineMeshes;                                            // 0x0430(0x0010) (ExportObject, ZeroConstructor)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0440(0x0010) MISSED OFFSET
	class UStaticMesh*                                 mMesh;                                                    // 0x0450(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0458(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadTrackHologram");
		return ptr;
	}

};


// Class FactoryGame.FGVehicleHologram
// 0x0008 (0x03B8 - 0x03B0)
class AFGVehicleHologram : public AFGHologram
{
public:
	class UClass*                                      mVehicleClass;                                            // 0x03B0(0x0008) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVehicleHologram");
		return ptr;
	}

};


// Class FactoryGame.FGRailroadVehicleHologram
// 0x0020 (0x03D8 - 0x03B8)
class AFGRailroadVehicleHologram : public AFGVehicleHologram
{
public:
	unsigned char                                      UnknownData00[0x4];                                       // 0x03B8(0x0004) MISSED OFFSET
	float                                              mLength;                                                  // 0x03BC(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FRailroadTrackPosition                      mTrackPosition;                                           // 0x03C0(0x0010)
	class AFGRailroadVehicle*                          mSnappedVehicle;                                          // 0x03D0(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadVehicleHologram");
		return ptr;
	}

};


// Class FactoryGame.FGRailroadVehicleSoundComponent
// 0x0030 (0x0270 - 0x0240)
class UFGRailroadVehicleSoundComponent : public USceneComponent
{
public:
	class UFGLocomotiveMovementComponent*              mLocomotiveMovementComponent;                             // 0x0240(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAkComponent*                                mWheelsetsAkComponent;                                    // 0x0248(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAkComponent*                                mEnginesAkComponent;                                      // 0x0250(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAkComponent*                                mAllVehicleCentersAkComponent;                            // 0x0258(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0260(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRailroadVehicleSoundComponent");
		return ptr;
	}


	void UpdateRTPCs();
	void OnThrottleReleased();
	void OnThrottleApplied();
	void OnStoppedMoving();
	void OnStartedMoving();
	void OnDynamicBrakesReleased();
	void OnDynamicBrakesApplied();
	void OnAirBrakesReleased();
	void OnAirBrakesApplied();
};


// Class FactoryGame.FGRecipe
// 0x0058 (0x0080 - 0x0028)
class UFGRecipe : public UObject
{
public:
	bool                                               mDisplayNameOverride;                                     // 0x0028(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0029(0x0007) MISSED OFFSET
	struct FText                                       mDisplayName;                                             // 0x0030(0x0028) (Edit, DisableEditOnInstance)
	TArray<struct FItemAmount>                         mIngredients;                                             // 0x0048(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FItemAmount>                         mProduct;                                                 // 0x0058(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mManufactoringDuration;                                   // 0x0068(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x006C(0x0004) MISSED OFFSET
	TArray<TSoftObjectPtr<class UClass>>               mProducedIn;                                              // 0x0070(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRecipe");
		return ptr;
	}


	void SortByName(TArray<class UClass*>* recipes);
	TArray<class UClass*> GetRewardedRecipes(class UClass* inClass);
	struct FText GetRecipeName(class UClass* inClass);
	TArray<struct FItemAmount> GetProducts(class UClass* inClass, bool allowChildRecipes);
	TArray<class UClass*> GetProducedIn(class UClass* inClass);
	float GetManufacturingDuration(class UClass* inClass);
	TArray<struct FItemAmount> GetIngredients(class UClass* inClass);
};


// Class FactoryGame.FGRecipeManager
// 0x0018 (0x0340 - 0x0328)
class AFGRecipeManager : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	TArray<class UClass*>                              mAvailableRecipes;                                        // 0x0330(0x0010) (Net, ZeroConstructor, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRecipeManager");
		return ptr;
	}


	bool IsRecipeAvailable(class UClass* recipeClass);
	void GetAvailableRecipesForProducer(class UClass* forProducer, TArray<class UClass*>* out_recipes);
	void GetAllAvailableRecipes(TArray<class UClass*>* out_recipes);
	class AFGRecipeManager* Get(class UObject* WorldContext);
	TArray<class UClass*> FindRecipesByProduct(class UClass* product);
	TArray<class UClass*> FindRecipesByIngredient(class UClass* ingredient);
};


// Class FactoryGame.FGRecipeProducerInterface
// 0x0000 (0x0028 - 0x0028)
class UFGRecipeProducerInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRecipeProducerInterface");
		return ptr;
	}

};


// Class FactoryGame.FGRecipeShortcut
// 0x0008 (0x0038 - 0x0030)
class UFGRecipeShortcut : public UFGHotbarShortcut
{
public:
	class UClass*                                      mRecipeToActivate;                                        // 0x0030(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRecipeShortcut");
		return ptr;
	}


	void SetRecipe(class UClass* Recipe);
	void OnRep_Recipe();
	class UClass* GetRecipe();
};


// Class FactoryGame.FGRenderTargetStage
// 0x0028 (0x0350 - 0x0328)
class AFGRenderTargetStage : public AActor
{
public:
	int                                                mDynamicRenderTargetSizeX;                                // 0x0328(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mDynamicRenderTargetSizeY;                                // 0x032C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EPixelFormat>                          mDynamicPixelFormat;                                      // 0x0330(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0331(0x0007) MISSED OFFSET
	class USceneCaptureComponent2D*                    mSceneCaptureComponent;                                   // 0x0338(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mStage;                                                   // 0x0340(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      mDynamicRenderTarget : 1;                                 // 0x0348(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0349(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRenderTargetStage");
		return ptr;
	}


	void UpdateRenderedComponents();
	void SetView(const struct FItemView& View);
	void SetPreviewDistance(float Distance);
	class USceneComponent* GetStage();
	class UTextureRenderTarget2D* GetRenderTarget();
	void EndCapture();
	void CaptureOnce();
	void BeginCapture();
};


// Class FactoryGame.FGReplicationDependencyActorInterface
// 0x0000 (0x0028 - 0x0028)
class UFGReplicationDependencyActorInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDependencyActorInterface");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActor
// 0x0010 (0x0338 - 0x0328)
class AFGReplicationDetailActor : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class AFGBuildable*                                mOwningBuildable;                                         // 0x0330(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActor");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActor_BuildableFactory
// 0x0008 (0x0340 - 0x0338)
class AFGReplicationDetailActor_BuildableFactory : public AFGReplicationDetailActor
{
public:
	class UFGInventoryComponent*                       mInventoryPotential;                                      // 0x0338(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActor_BuildableFactory");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActor_CargoPlatform
// 0x0008 (0x0348 - 0x0340)
class AFGReplicationDetailActor_CargoPlatform : public AFGReplicationDetailActor_BuildableFactory
{
public:
	class UFGInventoryComponent*                       mCargoInventory;                                          // 0x0340(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActor_CargoPlatform");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActor_GeneratorFuel
// 0x0008 (0x0348 - 0x0340)
class AFGReplicationDetailActor_GeneratorFuel : public AFGReplicationDetailActor_BuildableFactory
{
public:
	class UFGInventoryComponent*                       mFuelInventory;                                           // 0x0340(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActor_GeneratorFuel");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActor_Manufacturing
// 0x0018 (0x0358 - 0x0340)
class AFGReplicationDetailActor_Manufacturing : public AFGReplicationDetailActor_BuildableFactory
{
public:
	class UFGInventoryComponent*                       mInputInventory;                                          // 0x0340(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       mOutputInventory;                                         // 0x0348(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mCurrentManufacturingProgress;                            // 0x0350(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0354(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActor_Manufacturing");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActor_Storage
// 0x0008 (0x0348 - 0x0340)
class AFGReplicationDetailActor_Storage : public AFGReplicationDetailActor_BuildableFactory
{
public:
	class UFGInventoryComponent*                       mStorageInventory;                                        // 0x0340(0x0008) (ExportObject, Net, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActor_Storage");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailActorOwnerInterface
// 0x0000 (0x0028 - 0x0028)
class UFGReplicationDetailActorOwnerInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailActorOwnerInterface");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationDetailInventoryComponent
// 0x0020 (0x0110 - 0x00F0)
class UFGReplicationDetailInventoryComponent : public UActorComponent
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x00F0(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationDetailInventoryComponent");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationGraph
// 0x0168 (0x0458 - 0x02F0)
class UFGReplicationGraph : public UReplicationGraph
{
public:
	TArray<class UClass*>                              mSpatializedClasses;                                      // 0x02F0(0x0010) (ZeroConstructor)
	TArray<class UClass*>                              mNonSpatializedClasses;                                   // 0x0300(0x0010) (ZeroConstructor)
	TArray<class UClass*>                              mAlwaysRelevantClasses;                                   // 0x0310(0x0010) (ZeroConstructor)
	class UReplicationGraphNode_GridSpatialization2D*  mGridNode;                                                // 0x0320(0x0008) (ZeroConstructor, IsPlainOldData)
	class UReplicationGraphNode_ActorList*             mAlwaysRelevantNode;                                      // 0x0328(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<struct FConnectionAlwaysRelevant_NodePair>  mAlwaysRelevantForConnectionList;                         // 0x0330(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x50];                                      // 0x0340(0x0050) MISSED OFFSET
	unsigned char                                      UnknownData01[0x50];                                      // 0x0340(0x0050) UNKNOWN PROPERTY: SetProperty FactoryGame.FGReplicationGraph.mPersistentDependencyClasses
	unsigned char                                      UnknownData02[0x68];                                      // 0x03E0(0x0068) MISSED OFFSET
	TArray<class AActor*>                              mActorsWithoutNetConnection;                              // 0x0448(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationGraph");
		return ptr;
	}

};


// Class FactoryGame.FGReplicationGraphNode_AlwaysRelevant_ForConnection
// 0x0218 (0x0338 - 0x0120)
class UFGReplicationGraphNode_AlwaysRelevant_ForConnection : public UReplicationGraphNode_AlwaysRelevant_ForConnection
{
public:
	unsigned char                                      UnknownData00[0x218];                                     // 0x0120(0x0218) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGReplicationGraphNode_AlwaysRelevant_ForConnection");
		return ptr;
	}

};


// Class FactoryGame.FGResearchMachine
// 0x0030 (0x0270 - 0x0240)
class UFGResearchMachine : public USceneComponent
{
public:
	class UClass*                                      mCurrentResearchRecipe;                                   // 0x0240(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGCharacterPlayer*                          mPlayerUsingMachine;                                      // 0x0248(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class UStaticMeshComponent*                        mResearchingMeshComponent;                                // 0x0250(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMesh*                                 mResearchingMesh;                                         // 0x0258(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class UCurveFloat*                                 mItemScaleCurve;                                          // 0x0260(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0268(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResearchMachine");
		return ptr;
	}


	void SetResearchRecipe(class UClass* researchRecipe);
	void SetResearchMeshCurveScale(class UCurveFloat* curveScale);
	void SetResearchMeshComponent(class UStaticMeshComponent* StaticMeshComponent);
	void SetMachineUser(class AFGCharacterPlayer* Player);
	void OnResearchStarted(class UClass* researchRecipe);
	void OnResearchConcluded(class UClass* researchRecipe);
	void OnRep_ResearchMesh();
	bool IsResearchBeingConducted();
	class UStaticMeshComponent* GetResearchMeshComponent();
	class AFGCharacterPlayer* GetMachineUser();
};


// Class FactoryGame.FGResearchManager
// 0x0118 (0x0440 - 0x0328)
class AFGResearchManager : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    ResearchStartedDelegate;                                  // 0x0330(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    PaidOffResearchDelegate;                                  // 0x0340(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    ResearchCompletedDelegate;                                // 0x0350(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    ResearchResultsClaimedDelegate;                           // 0x0360(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    ResearchNewAvailableDelegate;                             // 0x0370(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	bool                                               mCanConductMultipleResearch;                              // 0x0380(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0381(0x0007) MISSED OFFSET
	TArray<class UClass*>                              mDefaultStartingResearch;                                 // 0x0388(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UClass*>                              mAllResearchRecipes;                                      // 0x0398(0x0010) (ZeroConstructor)
	TArray<struct FResearchCost>                       mResearchCosts;                                           // 0x03A8(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<struct FCompletedResearch>                  mCompletedResearch;                                       // 0x03B8(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<struct FResearchTime>                       mOngoingResearch;                                         // 0x03C8(0x0010) (Net, ZeroConstructor)
	TArray<struct FResearchTime>                       mSavedOngoingResearch;                                    // 0x03D8(0x0010) (ZeroConstructor, SaveGame)
	int                                                mDecorPoints;                                             // 0x03E8(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                mStructurePoints;                                         // 0x03EC(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x50];                                      // 0x03F0(0x0050) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResearchManager");
		return ptr;
	}


	void UnlockResearchWithItem(class UClass* ItemClass);
	void SetSelectedRewardIndexByRecipe(class UClass* CompletedResearch, int selectedIndex);
	int PayOffOnResearch(const struct FItemAmount& payOff, class UClass* researchRecipe);
	int PayOffFromInventory(class UClass* researchRecipe, class UFGInventoryComponent* inventory, int inventorySlotIndex);
	void OnResearchTimerComplete(class UClass* researchRecipe);
	bool IsResearchRecipeAccessible(class UClass* researchRecipe);
	bool IsResearchComplete(class UClass* researchRecipe);
	bool IsResearchBeingConducted(class UClass* researchRecipe);
	bool IsResearchAccessibleAndPaidOff(class UClass* researchRecipe);
	bool IsCompletedResearchResultSelectable(class UClass* researchRecipe);
	bool IsAnyResearchBeingConducted();
	bool InitiateResearch(class UClass* researchRecipe);
	void GiveAccessToResearch(class UClass* researchRecipeClass, bool accessedViaCheats);
	int GetStructurePoints();
	TArray<struct FResearchRecipeReward> GetRewardsFromCompletedResearch(const struct FCompletedResearch& CompletedResearch);
	float GetResearchDuration(class UClass* researchRecipe);
	class UClass* GetResearchBeingConducted();
	void GetPayOffBalanceForResearch(class UClass* researchRecipe, TArray<struct FItemAmount>* out_cost);
	float GetOngoingResearchTimeLeft(class UClass* researchRecipe);
	int GetDecorPoints();
	struct FCompletedResearch GetCompletedResearchRewardByRecipe(class UClass* CompletedResearch);
	void GetAllResearchRecipes(TArray<class UClass*>* out_ResearchRecipes);
	void GetAllCompletedAndClaimedResearch(TArray<class UClass*>* out_ResearchRecipes);
	void GetAllAccessibleResearch(TArray<class UClass*>* out_ResearchRecipes);
	class AFGResearchManager* Get(class UObject* WorldContext);
	bool ContainsAnyCompletedButUnclaimedResearch();
	int ConsumeStructurePoints(int amount);
	int ConsumeDecorPoints(int amount);
	bool ClaimResearchResults(class AFGCharacterPlayer* instigatorPlayer, class UClass* CompletedResearch, int selectedRewardIndex);
	bool CanResearchRewardBeClaimed(class UClass* researchRecipe);
	bool CanResearchBeInitiated(class UClass* researchRecipe);
	bool CanConsumeStructurePoints(int amount);
	bool CanConsumeDecorPoints(int amount);
	void AddStructurePoints(int amount);
	void AddDecorPoints(int amount);
};


// Class FactoryGame.FGResearchRecipe
// 0x0058 (0x00D8 - 0x0080)
class UFGResearchRecipe : public UFGRecipe
{
public:
	TArray<class UClass*>                              mTriggerItems;                                            // 0x0080(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	bool                                               mIsRepeatable;                                            // 0x0090(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mRewardUsesDropPackage;                                   // 0x0091(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0092(0x0006) MISSED OFFSET
	TArray<TSoftObjectPtr<class UClass>>               mUnlockedResearch;                                        // 0x0098(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<TSoftObjectPtr<class UClass>>               mUnlockedSchematics;                                      // 0x00A8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	int                                                mDecorPoints;                                             // 0x00B8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mStructurePoints;                                         // 0x00BC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mExcludeFromBuild;                                        // 0x00C0(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x00C1(0x0007) MISSED OFFSET
	struct FAssetBundleData                            mAssetBundleData;                                         // 0x00C8(0x0010)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResearchRecipe");
		return ptr;
	}


	bool IsValidResearchRecipeReward(const struct FResearchRecipeReward& recipeReward);
	bool IsResearchRepeatable(class UClass* inClass);
	struct FResearchRecipeReward GetResearcResults(class UClass* inClass);
	TArray<class UClass*> GetResearchTriggerItems(class UClass* inClass);
	float GetResearchTime(class UClass* inClass);
};


// Class FactoryGame.FGResourceNode
// 0x0098 (0x03C0 - 0x0328)
class AFGResourceNode : public AActor
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0328(0x0018) MISSED OFFSET
	class UClass*                                      mResourceClass;                                           // 0x0340(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EResourcePurity>                       mPurity;                                                  // 0x0348(0x0001) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	TEnumAsByte<EResourceAmount>                       mAmount;                                                  // 0x0349(0x0001) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x034A(0x0006) MISSED OFFSET
	class UStaticMeshComponent*                        mStaticMeshComponent;                                     // 0x0350(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UDecalComponent*                             mDecalComponent;                                          // 0x0358(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	class UBoxComponent*                               mBoxComponent;                                            // 0x0360(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	int                                                mResourcesLeft;                                           // 0x0368(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, DisableEditOnTemplate, SaveGame, IsPlainOldData)
	bool                                               mIsOccupied;                                              // 0x036C(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x036D(0x0003) MISSED OFFSET
	TArray<class UObject*>                             mRevealedOnMapBy;                                         // 0x0370(0x0010) (Net, ZeroConstructor, SaveGame)
	bool                                               mIsLonerNode;                                             // 0x0380(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               mCanPlaceResourceExtractor;                               // 0x0381(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x2];                                       // 0x0382(0x0002) MISSED OFFSET
	int                                                mExtractMultiplier;                                       // 0x0384(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUseDefaultMesh;                                          // 0x0388(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x0389(0x0007) MISSED OFFSET
	TArray<struct FPurityTextPair>                     mPurityTextArray;                                         // 0x0390(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	unsigned char                                      UnknownData05[0x8];                                       // 0x03A0(0x0008) MISSED OFFSET
	class UParticleSystem*                             mHighlightParticleSystemTemplate;                         // 0x03A8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UParticleSystemComponent*                    mHighlightParticleSystemComponent;                        // 0x03B0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mDoSpawnParticle;                                         // 0x03B8(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData06[0x7];                                       // 0x03B9(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceNode");
		return ptr;
	}


	void ToggleResourcePickUI(class AFGCharacterPlayer* Player);
	void SetIsOccupied(bool occupied);
	void OnRep_IsOccupied();
	void OnIsOccupiedChanged(bool newIsOccupied);
	bool IsOccupied();
	void InitResource(class UClass* ResourceClass, TEnumAsByte<EResourceAmount> amount, TEnumAsByte<EResourcePurity> Purity);
	bool HasAnyResources();
	struct FText GetResourceName();
	class UClass* GetResourceClass();
	TEnumAsByte<EResourceAmount> GetResourceAmount();
	struct FText GetResoucesLeftText();
	struct FText GetResoucePurityText();
	TEnumAsByte<EResourcePurity> GetResoucePurity();
	bool GetIsLonerNode();
	int GetExtractMultiplier();
	float GetExtractionSpeedMultiplier();
	void ExtractResourceAndGiveToPlayer(class AFGCharacterPlayer* toPlayer, int amount);
	void ClearWidget();
	bool CanPlaceResourceExtractor();
};


// Class FactoryGame.FGResourceDeposit
// 0x0040 (0x0400 - 0x03C0)
class AFGResourceDeposit : public AFGResourceNode
{
public:
	struct FResourceDepositPackage                     mResourceDepositPackage;                                  // 0x03C0(0x0020)
	int                                                mResourceDepositTableIndex;                               // 0x03E0(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsEmptied;                                               // 0x03E4(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x03E5(0x0003) MISSED OFFSET
	int                                                mMineAmount;                                              // 0x03E8(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03EC(0x0004) MISSED OFFSET
	class UStaticMeshComponent*                        mDepositMeshComponent;                                    // 0x03F0(0x0008) (Edit, BlueprintVisible, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	class UClass*                                      mOverrideResourceClass;                                   // 0x03F8(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceDeposit");
		return ptr;
	}


	void PlayDepletedEffect(class UClass* Descriptor);
	void OnRep_ResourceDepositEmptied();
	bool IsDepositEmpty();
	int GetMineAmount();
};


// Class FactoryGame.FGResourceDescriptor
// 0x0068 (0x0190 - 0x0128)
class UFGResourceDescriptor : public UFGItemDescriptor
{
public:
	class UStaticMesh*                                 mGroundMesh;                                              // 0x0128(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UStaticMesh*                                 mDepositMesh;                                             // 0x0130(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mDepositMaterial;                                         // 0x0138(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterialInstance*                           mGroundMeshMaterialOverride;                              // 0x0140(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterial*                                   mDecalMaterial;                                           // 0x0148(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDecalSize;                                               // 0x0150(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FLinearColor                                mPingColor;                                               // 0x0154(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCollectSpeedMultiplier;                                  // 0x0164(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UTexture2D*                                  mCompassTexture;                                          // 0x0168(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mManualMiningParticle;                                    // 0x0170(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mFactoryMiningParticle;                                   // 0x0178(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UParticleSystem*                             mDestroyedParticle;                                       // 0x0180(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mManualMiningAudioName;                                   // 0x0188(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceDescriptor");
		return ptr;
	}


	struct FLinearColor GetPingColor(class UClass* inClass);
	class UMaterialInstance* GetMeshOverrideMaterial(class UClass* inClass);
	class UParticleSystem* GetManualMiningParticle(class UClass* inClass);
	struct FName GetManualMiningAudioName(class UClass* inClass);
	class UStaticMesh* GetGroundMesh(class UClass* inClass);
	class UParticleSystem* GetFactoryMiningParticle(class UClass* inClass);
	class UParticleSystem* GetDestroyedParticle(class UClass* inClass);
	class UStaticMesh* GetDepositMesh(class UClass* inClass);
	class UMaterialInstance* GetDepositMaterial(class UClass* inClass);
	float GetDecalSize(class UClass* inClass);
	class UMaterial* GetDecalMaterial(class UClass* inClass);
	class UTexture2D* GetCompasTexture(class UClass* inClass);
	float GetCollectSpeedMultiplier(class UClass* inClass);
	bool CanBeHandMined(class UClass* inClass);
};


// Class FactoryGame.FGResourceDescriptorGeyser
// 0x0000 (0x0190 - 0x0190)
class UFGResourceDescriptorGeyser : public UFGResourceDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceDescriptorGeyser");
		return ptr;
	}

};


// Class FactoryGame.FGResourceMiner
// 0x0018 (0x03D8 - 0x03C0)
class AFGResourceMiner : public AFGEquipment
{
public:
	class UParticleSystem*                             mPickParticleSystem;                                      // 0x03C0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAnimationAsset*                             mPickArmsAnim;                                            // 0x03C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGResourceNode*                             mCachedResouceNode;                                       // 0x03D0(0x0008) (Net, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceMiner");
		return ptr;
	}


	void StopMining();
	void StartMining();
	void SetResourceNode(class AFGResourceNode* inNode);
	void Server_ExtractResources();
	void RemoveEquipment();
	class AFGResourceNode* GetResourceNode();
	void DoMine();
};


// Class FactoryGame.FGUseState_NodeFullInventory
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_NodeFullInventory : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_NodeFullInventory");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_NonConveyorResource
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_NonConveyorResource : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_NonConveyorResource");
		return ptr;
	}

};


// Class FactoryGame.FGResourceNodeGeyser
// 0x0000 (0x03C0 - 0x03C0)
class AFGResourceNodeGeyser : public AFGResourceNode
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceNodeGeyser");
		return ptr;
	}

};


// Class FactoryGame.FGResourceScanner
// 0x0030 (0x03F0 - 0x03C0)
class AFGResourceScanner : public AFGEquipment
{
public:
	class UClass*                                      mResourceDescriptorToScanFor;                             // 0x03C0(0x0008) (ZeroConstructor, IsPlainOldData)
	int                                                mNrOfClosestClustersToMark;                               // 0x03C8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mLastPressedTimeStamp;                                    // 0x03CC(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              mHoldDownDurationForUI;                                   // 0x03D0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mIsPressingScan;                                          // 0x03D4(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsWaitingForSelectionUI;                                 // 0x03D5(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x03D6(0x0002) MISSED OFFSET
	float                                              mDistBetweenNodesInCluster;                               // 0x03D8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03DC(0x0004) MISSED OFFSET
	TArray<struct FNodeClusterData>                    mNodeClusters;                                            // 0x03E0(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceScanner");
		return ptr;
	}


	void ShowResourceDescriptorSelectUI();
	void SetResourceDescriptorToScanFor(class UClass* inClass);
	void SetPressingScan(bool isPressingScan);
	void Server_ScanReleased();
	void PlayClusterEffects(TArray<struct FNodeClusterData> clusters);
	TArray<class UClass*> GetScannableResources();
	class UClass* GetResourceDescriptorToScanFor();
	void CloseResourceDescriptorSelectUI();
};


// Class FactoryGame.FGResourceSettings
// 0x0090 (0x00B8 - 0x0028)
class UFGResourceSettings : public UFGSettings
{
public:
	TArray<struct FResourceDepositPackage>             mResourceDepositTable;                                    // 0x0028(0x0010) (Edit, ZeroConstructor)
	TArray<struct FInt32Interval>                      mResourceAmount;                                          // 0x0038(0x0010) (Edit, EditFixedSize, ZeroConstructor, DisableEditOnInstance)
	TArray<float>                                      mPurityMultiplier;                                        // 0x0048(0x0010) (Edit, EditFixedSize, ZeroConstructor, DisableEditOnInstance)
	class UStaticMesh*                                 mDefaultItemMesh;                                         // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TMap<int, EStackSize>                              mStackSizes;                                              // 0x0060(0x0050) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UClass*                                      mItemDropClass;                                           // 0x00B0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGResourceSettings");
		return ptr;
	}


	struct FResourceDepositPackage GetResourceDepositDataFromClass(class UClass* desiredResourceClass, class AActor* WorldContext, int* out_resourceDepositPackageIdx);
	struct FResourceDepositPackage GetRandomResourceDepositData(class AActor* WorldContext, int* out_resourceDepositPackageIdx);
};


// Class FactoryGame.FGRiverSpline
// 0x0020 (0x0348 - 0x0328)
class AFGRiverSpline : public AActor
{
public:
	class UAkAudioEvent*                               mAudioEvent;                                              // 0x0328(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	float                                              mEmitterInterval;                                         // 0x0330(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0334(0x0004) MISSED OFFSET
	class UFGSoundSplineComponent*                     mSoundSplineComponent;                                    // 0x0338(0x0008) (ExportObject, ZeroConstructor, InstancedReference, Deprecated, IsPlainOldData)
	bool                                               mShouldHaveAudio;                                         // 0x0340(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0341(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRiverSpline");
		return ptr;
	}

};


// Class FactoryGame.FGRoadConnectionComponent
// 0x0000 (0x0240 - 0x0240)
class UFGRoadConnectionComponent : public UFGConnectionComponent
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRoadConnectionComponent");
		return ptr;
	}

};


// Class FactoryGame.FGRoadHologram
// 0x0038 (0x0430 - 0x03F8)
class AFGRoadHologram : public AFGSplineHologram
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x03F8(0x0018) MISSED OFFSET
	class UFGRoadConnectionComponent*                  mConnectionComponents[0x2];                               // 0x0410(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGRoadConnectionComponent*                  mSnappedConnectionComponents[0x2];                        // 0x0420(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGRoadHologram");
		return ptr;
	}

};


// Class FactoryGame.FGSaveInterface
// 0x0000 (0x0028 - 0x0028)
class UFGSaveInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSaveInterface");
		return ptr;
	}


	bool ShouldSave();
	void PreSaveGame(int SaveVersion, int GameVersion);
	void PreLoadGame(int SaveVersion, int GameVersion);
	void PostSaveGame(int SaveVersion, int GameVersion);
	void PostLoadGame(int SaveVersion, int GameVersion);
	bool NeedTransform();
	void GatherDependencies(TArray<class UObject*>* out_dependentObjects);
};


// Class FactoryGame.FGSaveSession
// 0x00A0 (0x00C8 - 0x0028)
class UFGSaveSession : public UObject
{
public:
	struct FScriptMulticastDelegate                    mOnSaveWorld;                                             // 0x0028(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData00[0x88];                                      // 0x0038(0x0088) MISSED OFFSET
	float                                              mAutosaveInterval;                                        // 0x00C0(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	int                                                mNumRotatingAutosaves;                                    // 0x00C4(0x0004) (ZeroConstructor, Config, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSaveSession");
		return ptr;
	}


	bool SaveGame(const class FString& Filename);
	void OnActorDestroyed(class AActor* DestroyedActor);
	bool LoadGame(const class FString& saveName);
	int GetVersion(struct FSaveHeader* Header);
	class FString GetSessionName(struct FSaveHeader* Header);
	class FString GetSessionID(struct FSaveHeader* Header);
	TEnumAsByte<ESessionVisibility> GetSaveSessionVisibility(struct FSaveHeader* Header);
	class FString GetSaveSessionName(struct FSessionSaveStruct* session);
	class FString GetSaveSessionID(struct FSessionSaveStruct* session);
	struct FDateTime GetSaveDateTime(struct FSaveHeader* Header);
	int GetPlayDurationSeconds(struct FSaveHeader* Header);
	class FString GetName(struct FSaveHeader* Header);
	class FString GetMapOptions(struct FSaveHeader* Header);
	class FString GetMapName(struct FSaveHeader* Header);
	int GetBuildVersion(struct FSaveHeader* Header);
	class UFGSaveSession* Get(class UObject* WorldContext);
	void Autosave();
};


// Class FactoryGame.FGSaveSystem
// 0x0020 (0x0048 - 0x0028)
class UFGSaveSystem : public UObject
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0028(0x0010) MISSED OFFSET
	TArray<struct FMapRedirector>                      mMapRedirectors;                                          // 0x0038(0x0010) (ZeroConstructor, Config, GlobalConfig)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSaveSystem");
		return ptr;
	}


	bool IsValidSaveName(const class FString& saveName);
	bool IsSessionNameUsed(const class FString& SessionName);
	ESaveExists GetSaveExists(const class FString& saveName, const class FString& currentSessionName);
	void GetAllSavesPerSession(TArray<struct FSessionSaveStruct>* out_sessions);
	class UFGSaveSystem* Get(class UObject* WorldContext);
	void FindSaveGames(bool newestFirst, TArray<struct FSaveHeader>* out_saveGames);
	bool DeleteSave(const class FString& saveName);
};


// Class FactoryGame.FGSchematic
// 0x0120 (0x0148 - 0x0028)
class UFGSchematic : public UObject
{
public:
	ESchematicType                                     mType;                                                    // 0x0028(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0029(0x0007) MISSED OFFSET
	struct FText                                       mDisplayName;                                             // 0x0030(0x0028) (Edit, DisableEditOnInstance)
	ESchematicCategory                                 mSchematicCategory;                                       // 0x0048(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0049(0x0003) MISSED OFFSET
	int                                                mTechTier;                                                // 0x004C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FItemAmount>                         mCost;                                                    // 0x0050(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mShipTravelTimeAfterPurchase;                             // 0x0060(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0064(0x0004) MISSED OFFSET
	TArray<class UClass*>                              mRecipes;                                                 // 0x0068(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class UClass*>                              mResourcesToAddToScanner;                                 // 0x0078(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	bool                                               mUnlocksMap;                                              // 0x0088(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUnlocksBuildEfficiency;                                  // 0x0089(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mUnlocksBuildOverclock;                                   // 0x008A(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x1];                                       // 0x008B(0x0001) MISSED OFFSET
	int                                                mNumInventorySlotsToUnlock;                               // 0x008C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mNumArmEquipmentSlotsToUnlock;                            // 0x0090(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData04[0x4];                                       // 0x0094(0x0004) MISSED OFFSET
	struct FSlateBrush                                 mSchematicIcon;                                           // 0x0098(0x0088) (Edit, DisableEditOnInstance)
	class UClass*                                      mDependsOnSchematic;                                      // 0x0120(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<class UClass*>                              mAdditionalSchematicDependencies;                         // 0x0128(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	struct FAssetBundleData                            mAssetBundleData;                                         // 0x0138(0x0010)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSchematic");
		return ptr;
	}


	bool IsIncludedInBuild(class UClass* inClass);
	bool GetUnlocksMap(class UClass* inClass);
	bool GetUnlocksInventorySlots(class UClass* inClass);
	bool GetUnlocksBuildOverclock(class UClass* inClass);
	bool GetUnlocksBuildEfficiencyDisplay(class UClass* inClass);
	bool GetUnlocksArmEquipmentSlots(class UClass* inClass);
	ESchematicType GetType(class UClass* inClass);
	int GetTechTier(class UClass* inClass);
	float GetShipTravelTimeAfterPurchase(class UClass* inClass);
	struct FText GetSchematicDisplayName(class UClass* inClass);
	ESchematicCategory GetSchematicCategory(class UClass* inClass);
	TArray<class UClass*> GetResourceToAddToScanner(class UClass* inClass);
	TArray<class UClass*> GetRecipes(class UClass* inClass);
	int GetNumInventorySlotsUnlocked(class UClass* inClass);
	int GetNumArmEquipmentSlotsUnlocked(class UClass* inClass);
	struct FSlateBrush GetItemIcon(class UClass* inClass);
	class UClass* GetDependentOnSchematic(class UClass* inClass);
	TArray<struct FItemAmount> GetCost(class UClass* inClass);
	TArray<class UClass*> GetAdditionalSchematicDependencies(class UClass* inClass);
};


// Class FactoryGame.FGSchematicManager
// 0x00A0 (0x03C8 - 0x0328)
class AFGSchematicManager : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    PurchasedSchematicDelegate;                               // 0x0330(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    PaidOffOnSchematicDelegate;                               // 0x0340(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	TArray<class UClass*>                              mAllSchematics;                                           // 0x0350(0x0010) (ZeroConstructor)
	TArray<class UClass*>                              mAvailableSchematics;                                     // 0x0360(0x0010) (Net, ZeroConstructor, SaveGame)
	TArray<class UClass*>                              mPurchasedSchematics;                                     // 0x0370(0x0010) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame)
	TArray<struct FSchematicCost>                      mPaidOffSchematic;                                        // 0x0380(0x0010) (Net, ZeroConstructor, SaveGame)
	class UClass*                                      mActiveSchematic;                                         // 0x0390(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	struct FScriptMulticastDelegate                    mOnActiveSchematicChanged;                                // 0x0398(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	float                                              mShipLandTimeStamp;                                       // 0x03A8(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mShipLandTimeStampSave;                                   // 0x03AC(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mHasTechTierLimit;                                        // 0x03B0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x03B1(0x0003) MISSED OFFSET
	int                                                mMaxAllowedTechTier;                                      // 0x03B4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x03B8(0x0008) MISSED OFFSET
	class UClass*                                      mShipReturnedMessage;                                     // 0x03C0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSchematicManager");
		return ptr;
	}


	bool SetActiveSchematic(class UClass* newActiveSchematic);
	bool PayOffOnSchematic(class UClass* Schematic, TArray<struct FItemAmount>* amount);
	void OnRep_PurchasedSchematic();
	void OnRep_PaidOffOnSchematic();
	void OnRep_ActiveSchematic();
	void LaunchShip();
	bool IsShipAtTradingPost();
	bool IsSchematicPurchased(class UClass* SchematicClass);
	bool IsSchematicPaidOff(class UClass* Schematic);
	void GiveAccessToSchematic(class UClass* SchematicClass, bool accessedViaCheats);
	float GetTimeUntilShipReturn();
	TArray<struct FItemAmount> GetRemainingCostFor(class UClass* Schematic);
	void GetPurchasedSchematics(TArray<class UClass*>* out_schematics);
	TArray<struct FItemAmount> GetPaidOffCostFor(class UClass* Schematic);
	int GetMaxAllowedTechTier();
	int GetHighestAvailableTechTier();
	TArray<struct FItemAmount> GetCostFor(class UClass* Schematic);
	void GetAvailableSchematics(TArray<class UClass*>* out_schematics);
	void GetAllSchematicsOfType(ESchematicType Type, TArray<class UClass*>* out_schematics);
	void GetAllSchematics(TArray<class UClass*>* out_schematics);
	class UClass* GetActiveSchematic();
	class AFGSchematicManager* Get(class UObject* WorldContext);
	bool CanSetAsActiveSchematic(class UClass* inSchematic);
	void AddAvailableSchematic(class UClass* schematicClassToAdd);
};


// Class FactoryGame.FGSharedPostProcessSettings
// 0x04F8 (0x0520 - 0x0028)
class UFGSharedPostProcessSettings : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	struct FPostProcessSettings                        mPostProcessSettings;                                     // 0x0030(0x04E0) (Edit, DisableEditOnInstance)
	float                                              mBlendRadius;                                             // 0x0510(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mBlendWeight;                                             // 0x0514(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mPriority;                                                // 0x0518(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x051C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSharedPostProcessSettings");
		return ptr;
	}

};


// Class FactoryGame.FGSignCanvasWidget
// 0x00E0 (0x02E8 - 0x0208)
class UFGSignCanvasWidget : public UUserWidget
{
public:
	class USizeBox*                                    mCanvasSizeBox;                                           // 0x0208(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UCanvasPanel*                                mCanvasPanel;                                             // 0x0210(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FSlateBrush                                 mSelectionBrushTemplate;                                  // 0x0218(0x0088) (Edit, DisableEditOnInstance)
	class UClass*                                      mDefaultElementClass;                                     // 0x02A0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mTextElementClass;                                        // 0x02A8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mIconElementClass;                                        // 0x02B0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGSignElementDragDrop*                      mDragAndDrop;                                             // 0x02B8(0x0008) (ZeroConstructor, IsPlainOldData)
	class UFGSignElementDragWidget*                    mDragElement;                                             // 0x02C0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<class UFGSignElementWidget*>                mElementWidgets;                                          // 0x02C8(0x0010) (ExportObject, ZeroConstructor)
	class UFGSignElementWidget*                        mSelectedElement;                                         // 0x02D8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGSignInteractWidget*                       mInteractWidget;                                          // 0x02E0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignCanvasWidget");
		return ptr;
	}


	void OnElementSelected(class UFGSignElementData* elementData);
	struct FVector2D GetComponentToCanvasLocation(const struct FVector2D& locationInComponent);
	struct FVector2D GetCanvasToComponentLocation(const struct FVector2D& locationInCanvas);
	void AddSignCanvasElement(class UFGSignElementData* elementData);
};


// Class FactoryGame.FGSignElementDragDrop
// 0x0000 (0x0088 - 0x0088)
class UFGSignElementDragDrop : public UDragDropOperation
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignElementDragDrop");
		return ptr;
	}

};


// Class FactoryGame.FGSignElementDragWidget
// 0x0018 (0x0220 - 0x0208)
class UFGSignElementDragWidget : public UUserWidget
{
public:
	class UFGSignElementWidget*                        mElementReference;                                        // 0x0208(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USizeBox*                                    mSizeBox;                                                 // 0x0210(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UImage*                                      mBackground;                                              // 0x0218(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignElementDragWidget");
		return ptr;
	}


	void OnExitCanavasBounds();
	void OnEnterCanvasBounds();
	void Init(class UFGSignElementData* elementData);
};


// Class FactoryGame.FGSignElementListWidget
// 0x0020 (0x0228 - 0x0208)
class UFGSignElementListWidget : public UUserWidget
{
public:
	class UButton*                                     mAddTextElementButton;                                    // 0x0208(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UButton*                                     mAddIconElementButton;                                    // 0x0210(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UVerticalBox*                                mElementListBox;                                          // 0x0218(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0220(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignElementListWidget");
		return ptr;
	}

};


// Class FactoryGame.FGSignElementSettingsWidget
// 0x0008 (0x0210 - 0x0208)
class UFGSignElementSettingsWidget : public UUserWidget
{
public:
	class UFGSignElementWidget*                        mElementWidget;                                           // 0x0208(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignElementSettingsWidget");
		return ptr;
	}


	void OnElementDataChanged();
	void OnColorIndexSelected(int Index);
	void Init();
};


// Class FactoryGame.FGSignElementWidget
// 0x0040 (0x0248 - 0x0208)
class UFGSignElementWidget : public UUserWidget
{
public:
	class UBorder*                                     mSelectionBorder;                                         // 0x0208(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      mDragWidgetClass;                                         // 0x0210(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mSignElementSettingsWidget;                               // 0x0218(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFGSignElementDragWidget*                    mDragElement;                                             // 0x0220(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGSignCanvasWidget*                         mCanvasParent;                                            // 0x0228(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGSignElementData*                          mElementData;                                             // 0x0230(0x0008) (ZeroConstructor, IsPlainOldData)
	class UCanvasPanelSlot*                            mPanelSlot;                                               // 0x0238(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0240(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignElementWidget");
		return ptr;
	}


	void RefreshElement(bool isInitialization);
	void OnElementSelected();
	void OnElementDeselected();
	class UFGSignElementData* GetElementData();
};


// Class FactoryGame.FGSignificanceInterface
// 0x0000 (0x0028 - 0x0028)
class UFGSignificanceInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignificanceInterface");
		return ptr;
	}


	void LostSignificance();
	float GetSignificanceRange();
	float GetSignificanceBias();
	void GainedSignificance();
};


// Class FactoryGame.FGSignificanceManager
// 0x0040 (0x0170 - 0x0130)
class UFGSignificanceManager : public USignificanceManager
{
public:
	bool                                               mIsEnabled;                                               // 0x0130(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x17];                                      // 0x0131(0x0017) MISSED OFFSET
	TArray<class AFGBuildableFactory*>                 mPreviousSignificantFactories;                            // 0x0148(0x0010) (ZeroConstructor)
	TArray<class AFGBuildableConveyorBelt*>            mPreviousSignificantConveyorBelts;                        // 0x0158(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0168(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignificanceManager");
		return ptr;
	}

};


// Class FactoryGame.FGSignInteractWidget
// 0x0078 (0x02D0 - 0x0258)
class UFGSignInteractWidget : public UFGInteractWidget
{
public:
	class UFGSignElementListWidget*                    mElementListWidget;                                       // 0x0258(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UOverlay*                                    mElementSettingsContainer;                                // 0x0260(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USizeBox*                                    mCanvasSizeBox;                                           // 0x0268(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UCanvasPanel*                                mCanvasContainer;                                         // 0x0270(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGSignCanvasWidget*                         mSignCanvasWidget;                                        // 0x0278(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGSignElementSettingsWidget*                mElementSettingsWidget;                                   // 0x0280(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0288(0x0008) MISSED OFFSET
	struct FSignData                                   mSignData;                                                // 0x0290(0x0018) (BlueprintVisible)
	unsigned char                                      UnknownData01[0x28];                                      // 0x02A8(0x0028) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignInteractWidget");
		return ptr;
	}


	void ApplySignData();
	void AddNewTextElement();
	void AddNewSignElement(class UFGSignElementData* elementData);
	void AddNewIconElement();
};


// Class FactoryGame.FGSignElementData
// 0x0018 (0x0040 - 0x0028)
class UFGSignElementData : public UObject
{
public:
	int                                                SignElementID;                                            // 0x0028(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                ColorIndex;                                               // 0x002C(0x0004) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	struct FVector2D                                   TranslationOffset;                                        // 0x0030(0x0008) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              Rotation;                                                 // 0x0038(0x0004) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              Scale;                                                    // 0x003C(0x0004) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignElementData");
		return ptr;
	}

};


// Class FactoryGame.FGSignTextData
// 0x0018 (0x0058 - 0x0040)
class UFGSignTextData : public UFGSignElementData
{
public:
	class FString                                      SignText;                                                 // 0x0040(0x0010) (BlueprintVisible, ZeroConstructor, SaveGame)
	int                                                FontSize;                                                 // 0x0050(0x0004) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	EHorizontalSignTextAlignment                       TextAlignmentHorizontal;                                  // 0x0054(0x0001) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0055(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignTextData");
		return ptr;
	}

};


// Class FactoryGame.FGSignIconData
// 0x0008 (0x0048 - 0x0040)
class UFGSignIconData : public UFGSignElementData
{
public:
	int                                                IconIndex;                                                // 0x0040(0x0004) (BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0044(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignIconData");
		return ptr;
	}

};


// Class FactoryGame.FGSignInterface
// 0x0000 (0x0028 - 0x0028)
class UFGSignInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignInterface");
		return ptr;
	}


	void SetSignData(const struct FSignData& Data, bool bUpdate);
	struct FVector2D GetSignDimensions();
	struct FSignData GetSignData();
	int GetAvailableElementID();
};


// Class FactoryGame.FGSignSettings
// 0x0048 (0x0070 - 0x0028)
class UFGSignSettings : public UFGSettings
{
public:
	class UMaterial*                                   mTextMaterial;                                            // 0x0028(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterial*                                   mIconMaterial;                                            // 0x0030(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterial*                                   mBackgroundMaterial;                                      // 0x0038(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mBackgroundMeshMaterialIndex;                             // 0x0040(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0044(0x0004) MISSED OFFSET
	struct FName                                       mTextMaterialColorParam;                                  // 0x0048(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mIconMaterialColorParam;                                  // 0x0050(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FName                                       mBackgroundMaterialColorParam;                            // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FSignColorData>                      mSignColorData;                                           // 0x0060(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignSettings");
		return ptr;
	}


	class UMaterialInterface* GetTextMaterialInstanceFromIndex(int Index);
	TArray<struct FSignColorData> GetSignColorData();
	class UMaterialInterface* GetIconMaterialInstanceFromIndex(int Index);
	class UMaterialInterface* GetBackgroundMaterialInstanceFromIndex(int Index);
};


// Class FactoryGame.FGSignTextWidget
// 0x0008 (0x0250 - 0x0248)
class UFGSignTextWidget : public UFGSignElementWidget
{
public:
	class UTextBlock*                                  mTextBlock;                                               // 0x0248(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSignTextWidget");
		return ptr;
	}


	class UTextBlock* GetTextBlock();
};


// Class FactoryGame.FGSkySphere
// 0x1130 (0x1458 - 0x0328)
class AFGSkySphere : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	struct FRuntimeCurveLinearColor                    mSunLightColorCurve;                                      // 0x0330(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mSunIntensity;                                            // 0x04F8(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mSunRotationPitch;                                        // 0x0570(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mSunLightShaftOcclusionCurve;                             // 0x05E8(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mMoonLightColorCurve;                                     // 0x0660(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mMoonIntensity;                                           // 0x0828(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mMoonRotationPitch;                                       // 0x08A0(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mMoonLightShaftOcclusionCurve;                            // 0x0918(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mSkyLightIntensity;                                       // 0x0990(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mOcclusionTintColor;                                      // 0x0A08(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mHorizonColorCurve;                                       // 0x0BD0(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mZenithColorCurve;                                        // 0x0D98(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mCloudColorCurve;                                         // 0x0F60(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mCloudOpacity;                                            // 0x1128(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mStarBrightness;                                          // 0x11A0(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeCurveLinearColor                    mSkyLightColor;                                           // 0x1218(0x01C8) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FRuntimeFloatCurve                          mSunFogMultiplier;                                        // 0x13E0(0x0078) (Edit, BlueprintVisible, BlueprintReadOnly)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSkySphere");
		return ptr;
	}


	void UpdatePreview();
	float GetFloatCurveValue(const struct FRuntimeFloatCurve& Curve, float Time);
	struct FLinearColor GetColorCurveValue(const struct FRuntimeCurveLinearColor& Curve, float Time);
	void ApplySkySphereSettings(const struct FSkySphereSettings& Settings);
};


// Class FactoryGame.FGSoundSplineComponent
// 0x0010 (0x0460 - 0x0450)
class UFGSoundSplineComponent : public UAkComponent
{
public:
	float                                              mEmitterInterval;                                         // 0x0450(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0454(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSoundSplineComponent");
		return ptr;
	}


	void SetEmitterInterval(float newEmitterInterval);
	float GetEmitterInterval(float newEmitterInterval);
};


// Class FactoryGame.FGSpaceElevatorHologram
// 0x0000 (0x0448 - 0x0448)
class AFGSpaceElevatorHologram : public AFGFactoryHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSpaceElevatorHologram");
		return ptr;
	}

};


// Class FactoryGame.FGSplineComponent
// 0x0080 (0x06C0 - 0x0640)
class UFGSplineComponent : public USplineComponent
{
public:
	class UStaticMesh*                                 mSplineMesh;                                              // 0x0640(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSplineMeshLength;                                        // 0x0648(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mGenerateCollisions;                                      // 0x064C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x064D(0x0003) MISSED OFFSET
	float                                              mCollisionSpacing;                                        // 0x0650(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mCollisionExtent;                                         // 0x0654(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mCollisionOffset;                                         // 0x0660(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x066C(0x0004) MISSED OFFSET
	class UMaterialInterface*                          mOverrideMaterial;                                        // 0x0670(0x0008) (ZeroConstructor, IsPlainOldData)
	bool                                               mUseInstancing;                                           // 0x0678(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0679(0x0007) MISSED OFFSET
	TArray<class USplineMeshComponent*>                mSplineMeshComponents;                                    // 0x0680(0x0010) (ExportObject, ZeroConstructor)
	TArray<class USplineMeshComponent*>                mCustomDepthSplineMeshComponents;                         // 0x0690(0x0010) (ExportObject, ZeroConstructor)
	class UFGInstancedSplineMeshComponent*             mSplineMeshInstances;                                     // 0x06A0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInstancedSplineMeshComponent*             mCustomDepthSplineMeshInstances;                          // 0x06A8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<class UShapeComponent*>                     mSplineCollisionComponents;                               // 0x06B0(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSplineComponent");
		return ptr;
	}


	void UpdateSplineMeshes();
	void SetOverrideMaterial(class UMaterialInterface* Material);
	void DrawDebugSpline(const struct FColor& color1, const struct FColor& color2, float Thickness);
};


// Class FactoryGame.FGSplinePath
// 0x0008 (0x0330 - 0x0328)
class AFGSplinePath : public AActor
{
public:
	class USplineComponent*                            mSpline;                                                  // 0x0328(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSplinePath");
		return ptr;
	}

};


// Class FactoryGame.FGSporeFlower
// 0x0038 (0x0360 - 0x0328)
class AFGSporeFlower : public AActor
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0328(0x0018) MISSED OFFSET
	TArray<class UClass*>                              mTriggerActorClasses;                                     // 0x0340(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<class AActor*>                              mTriggerActors;                                           // 0x0350(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSporeFlower");
		return ptr;
	}


	bool ActorShouldTriggerFlower(class AActor* Actor);
};


// Class FactoryGame.FGStackableStorageHologram
// 0x0008 (0x0450 - 0x0448)
class AFGStackableStorageHologram : public AFGFactoryHologram
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0448(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGStackableStorageHologram");
		return ptr;
	}

};


// Class FactoryGame.FGStairHologram
// 0x0000 (0x03F8 - 0x03F8)
class AFGStairHologram : public AFGFoundationHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGStairHologram");
		return ptr;
	}

};


// Class FactoryGame.FGStandaloneSignHologram
// 0x0000 (0x03E0 - 0x03E0)
class AFGStandaloneSignHologram : public AFGBuildableHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGStandaloneSignHologram");
		return ptr;
	}

};


// Class FactoryGame.FGStartingPod
// 0x0030 (0x0358 - 0x0328)
class AFGStartingPod : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class AFGCharacterPlayer*                          mCachedPlayer;                                            // 0x0330(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	TArray<struct FInventoryStack>                     mDismantleStacks;                                         // 0x0338(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	class USkeletalMeshComponent*                      mDropPodMesh;                                             // 0x0348(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0350(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGStartingPod");
		return ptr;
	}


	void StartSequence();
	void OnPlayerSkipIntroSequence();
	class AFGCharacterPlayer* GetCachedPlayer();
};


// Class FactoryGame.FGStatHat
// 0x0008 (0x0030 - 0x0028)
class UFGStatHat : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGStatHat");
		return ptr;
	}

};


// Class FactoryGame.FGStorySubsystem
// 0x0058 (0x0380 - 0x0328)
class AFGStorySubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	TArray<class AFGCharacterPlayer*>                  mActivePlayers;                                           // 0x0330(0x0010) (ZeroConstructor)
	TArray<struct FSchematicMessagePair>               mSchematicMessageData;                                    // 0x0340(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FItemFoundData>                      mItemFoundData;                                           // 0x0350(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, SaveGame)
	TArray<struct FResearchMessageData>                mResearchMessageData;                                     // 0x0360(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UClass*                                      mResearchTimerCompleteMessage;                            // 0x0370(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mNewResearchAvailableMessage;                             // 0x0378(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGStorySubsystem");
		return ptr;
	}


	void SetupDelegates();
	void OnSchematicPurchased(class UClass* newSchematic);
	void OnResearchRewardClaimed(class UClass* researchRecipe);
	void OnResearchRecipeTimerComplete(class UClass* researchRecipe);
	void OnPlayerAddedItemToInventory(class UClass* ItemClass, int numAdded);
	void OnNewResearchRecipeAvailable(class UClass* researchRecipe);
	void OnMapAreaVisited(class UClass* mapArea);
	void AddPlayer(class AFGCharacterPlayer* inPlayer);
};


// Class FactoryGame.FGSubsystemClasses
// 0x0070 (0x0098 - 0x0028)
class UFGSubsystemClasses : public UFGSettings
{
public:
	class UClass*                                      mStorySubsystemClass;                                     // 0x0028(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mTimeSubsystemClass;                                      // 0x0030(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mRailroadSubsystemClass;                                  // 0x0038(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mCircuitSubsystemClass;                                   // 0x0040(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mSchematicManagerClass;                                   // 0x0048(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mGamePhaseManagerClass;                                   // 0x0050(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mResearchManagerClass;                                    // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mTutorialIntroManagerClass;                               // 0x0060(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mRadioactivitySubsystemClass;                             // 0x0068(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mChatManagerClass;                                        // 0x0070(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mCentralStorageSubsystemClass;                            // 0x0078(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mMapManagerClass;                                         // 0x0080(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mBuildableSubsystemClass;                                 // 0x0088(0x0008) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mFoliageRemovalSubsystemClass;                            // 0x0090(0x0008) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSubsystemClasses");
		return ptr;
	}

};


// Class FactoryGame.FGSuitBase
// 0x0010 (0x03D0 - 0x03C0)
class AFGSuitBase : public AFGEquipment
{
public:
	TArray<struct FMaterialAndSlotName>                mSuit1PMeshMaterials;                                     // 0x03C0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSuitBase");
		return ptr;
	}

};


// Class FactoryGame.FGSuitBaseAttachment
// 0x0010 (0x0370 - 0x0360)
class AFGSuitBaseAttachment : public AFGEquipmentAttachment
{
public:
	TArray<struct FMaterialAndSlotName>                mSuit3PMeshMaterials;                                     // 0x0360(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGSuitBaseAttachment");
		return ptr;
	}

};


// Class FactoryGame.FGTargetPoint
// 0x0028 (0x0350 - 0x0328)
class AFGTargetPoint : public AActor
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class AFGTargetPoint*                              mNext;                                                    // 0x0330(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGWheeledVehicle*                           mOwningVehicle;                                           // 0x0338(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsVisible;                                               // 0x0340(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0341(0x0003) MISSED OFFSET
	float                                              mWaitTime;                                                // 0x0344(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mDefaultWaitTime;                                         // 0x0348(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mTargetSpeed;                                             // 0x034C(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTargetPoint");
		return ptr;
	}


	void SetWaitTime(float newWaitTime);
	void SetVisibility(bool inVisible);
	void SetTargetSpeed(int newSpeed);
	void SetOwningVehicle(class AFGWheeledVehicle* newVehicle);
	void OnRep_Visibility();
	bool IsTargetSpeedStill();
	void IncreaseWaitTime(float addedWaitTime);
	float GetWaitTime();
	int GetTargetSpeed();
	class AFGWheeledVehicle* GetOwningVehicle();
};


// Class FactoryGame.FGTargetPointLinkedList
// 0x0028 (0x0050 - 0x0028)
class UFGTargetPointLinkedList : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	class AFGTargetPoint*                              mFirst;                                                   // 0x0030(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGTargetPoint*                              mLast;                                                    // 0x0038(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGTargetPoint*                              mCurrentTarget;                                           // 0x0040(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                mMaxLength;                                               // 0x0048(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x004C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTargetPointLinkedList");
		return ptr;
	}


	void SetPathVisibility(bool inVisible);
	void SetNextTarget();
	void SetCurrentTarget(class AFGTargetPoint* newTarget);
	void SetClosestPointAsTarget();
	void RemoveItem(class AFGTargetPoint* targetToRemove);
	void InsertItem(class AFGTargetPoint* newTarget);
	class AFGTargetPoint* GetLastTarget();
	class AFGTargetPoint* GetFirstTarget();
	class AFGTargetPoint* GetCurrentTarget();
	void ClearRecording();
};


// Class FactoryGame.FGTimeOfDaySubsystem
// 0x0050 (0x0378 - 0x0328)
class AFGTimeOfDaySubsystem : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	float                                              mSyncronizeTimeOfDayInterval;                             // 0x0330(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDayLengthMinutes;                                        // 0x0334(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNightLengthMinutes;                                      // 0x0338(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDayStartTime;                                            // 0x033C(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNightStartTime;                                          // 0x0340(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSpeedMultiplier;                                         // 0x0344(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0348(0x0004) MISSED OFFSET
	float                                              mDaySeconds;                                              // 0x034C(0x0004) (ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mReplicatedDaySeconds;                                    // 0x0350(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	int                                                mNumberOfPassedDays;                                      // 0x0354(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0358(0x0008) MISSED OFFSET
	bool                                               mUpdateTime;                                              // 0x0360(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0361(0x0007) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnNewDayDelegate;                                        // 0x0368(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTimeOfDaySubsystem");
		return ptr;
	}


	void UpdateServerDaySeconds();
	void SetTimeSpeedMultiplier(float Multiplier);
	void OnRep_ReplicatedDaySeconds();
	bool IsNight();
	bool IsDay();
	float GetTimeOfDayHours();
	float GetSeconds();
	int GetPassedDays();
	float GetNormalizedTimeOfDay();
	float GetNighttimeSeconds();
	float GetNightPct();
	int GetMinutes();
	int GetHours();
	float GetDaytimeSeconds();
	float GetDaySeconds();
	float GetDayPct();
	int GetDayMinutes();
	class AFGTimeOfDaySubsystem* Get(class UObject* WorldContext);
};


// Class FactoryGame.FGTitleButton
// 0x0000 (0x0210 - 0x0210)
class UFGTitleButton : public UFGButtonWidget
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTitleButton");
		return ptr;
	}

};


// Class FactoryGame.FGToolBelt
// 0x0008 (0x03C8 - 0x03C0)
class AFGToolBelt : public AFGEquipment
{
public:
	int                                                mNumArmSlotsToUnlock;                                     // 0x03C0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x03C4(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGToolBelt");
		return ptr;
	}

};


// Class FactoryGame.FGTradingPostHologram
// 0x0060 (0x04A8 - 0x0448)
class AFGTradingPostHologram : public AFGFactoryHologram
{
public:
	class AFGFactoryHologram*                          mGeneratorHolograms[0x2];                                 // 0x0448(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGBuildableHologram*                        mStorageHologram;                                         // 0x0458(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGBuildableHologram*                        mMAMHologram;                                             // 0x0460(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGBuildableHologram*                        mHubTerminalHologram;                                     // 0x0468(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class AFGBuildableHologram*                        mWorkBenchHologram;                                       // 0x0470(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	TArray<class USceneComponent*>                     mGeneratorLocations;                                      // 0x0478(0x0010) (ExportObject, ZeroConstructor)
	class USceneComponent*                             mStorageLocation;                                         // 0x0488(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mMAMLocation;                                             // 0x0490(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mHubTerminalLocation;                                     // 0x0498(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             mWorkBenchLocation;                                       // 0x04A0(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTradingPostHologram");
		return ptr;
	}

};


// Class FactoryGame.FGTrain
// 0x00A8 (0x03D0 - 0x0328)
class AFGTrain : public AInfo
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	struct FTrainSimulationData                        mSimulationData;                                          // 0x0330(0x0050)
	struct FText                                       mTrainName;                                               // 0x0380(0x0028) (Net)
	int                                                TrackGraphID;                                             // 0x0398(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x039C(0x0004) MISSED OFFSET
	class AFGRailroadVehicle*                          FirstVehicle;                                             // 0x03A0(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGRailroadVehicle*                          LastVehicle;                                              // 0x03A8(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGLocomotive*                               MultipleUnitMaster;                                       // 0x03B0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mIsSelfDrivingEnabled;                                    // 0x03B8(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	ESelfDrivingLocomotiveError                        mSelfDrivingError;                                        // 0x03B9(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x6];                                       // 0x03BA(0x0006) MISSED OFFSET
	class AFGRailroadTimeTable*                        TimeTable;                                                // 0x03C0(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsDocked;                                                // 0x03C8(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x03C9(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTrain");
		return ptr;
	}


	void SetTrainName(const struct FText& Name);
	class AFGRailroadTimeTable* NewTimeTable();
	struct FText GetTrainName();
	int GetTrackGraphID();
	class AFGRailroadTimeTable* GetTimeTable();
	ESelfDrivingLocomotiveError GetSelfDrivingError();
	float GetMaxAirBrakeDeceleration();
	class AFGRailroadVehicle* GetLastVehicle();
	bool GetIsDocked();
	class AFGRailroadVehicle* GetFirstVehicle();
};


// Class FactoryGame.FGTrainPlatformConnection
// 0x0030 (0x0270 - 0x0240)
class UFGTrainPlatformConnection : public UFGConnectionComponent
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0240(0x0008) MISSED OFFSET
	unsigned char                                      mComponentDirection : 1;                                  // 0x0248(0x0001) (SaveGame)
	ETrainPlatformConnectionType                       mPlatformConnectionStatus;                                // 0x0249(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x024A(0x0006) MISSED OFFSET
	class AFGBuildableTrainPlatform*                   platformOwner;                                            // 0x0250(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class UFGRailroadTrackConnectionComponent*         mRailroadTrackConnection;                                 // 0x0258(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	class UFGTrainPlatformConnection*                  mConnectedTo;                                             // 0x0260(0x0008) (ExportObject, ZeroConstructor, InstancedReference, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0268(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTrainPlatformConnection");
		return ptr;
	}

};


// Class FactoryGame.FGTrainPlatformHologram
// 0x0058 (0x04A0 - 0x0448)
class AFGTrainPlatformHologram : public AFGFactoryHologram
{
public:
	bool                                               mRequireSnapToPlatform;                                   // 0x0448(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0449(0x0007) MISSED OFFSET
	class UClass*                                      mRailroadTrackRecipe;                                     // 0x0450(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGRailroadTrackHologram*                    mRailroadTrackHologram;                                   // 0x0458(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class UFGTrainPlatformConnection*                  mPlatformConnectionComponents[0x2];                       // 0x0460(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGTrainPlatformConnection*                  mConnectedPlatformComponents[0x2];                        // 0x0470(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x0480(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTrainPlatformHologram");
		return ptr;
	}

};


// Class FactoryGame.FGTrainStationHologram
// 0x0000 (0x04A0 - 0x04A0)
class AFGTrainStationHologram : public AFGTrainPlatformHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTrainStationHologram");
		return ptr;
	}

};


// Class FactoryGame.FGTrainStationIdentifier
// 0x0030 (0x0358 - 0x0328)
class AFGTrainStationIdentifier : public AInfo
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	class AFGBuildableRailroadStation*                 mStation;                                                 // 0x0330(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	int                                                mTrackGraphID;                                            // 0x0338(0x0004) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x033C(0x0004) MISSED OFFSET
	struct FText                                       mStationName;                                             // 0x0340(0x0028) (Net, SaveGame)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTrainStationIdentifier");
		return ptr;
	}


	void SetStationName(const struct FText& Text);
	void OnRep_StationName();
	int GetTrackGraphID();
	struct FText GetStationName();
	class AFGBuildableRailroadStation* GetStation();
};


// Class FactoryGame.FGTutorialIntroManager
// 0x00F8 (0x0420 - 0x0328)
class AFGTutorialIntroManager : public AFGSubsystem
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0328(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnIntroSequenceStateUpdated;                             // 0x0330(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	bool                                               mTradingPostBuilt;                                        // 0x0340(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0341(0x0002) MISSED OFFSET
	EIntroTutorialSteps                                mPendingTutorial;                                         // 0x0343(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1];                                       // 0x0344(0x0001) MISSED OFFSET
	bool                                               mHasCompletedIntroTutorial;                               // 0x0345(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)
	bool                                               mHasCompletedIntroSequence;                               // 0x0346(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData03[0x1];                                       // 0x0347(0x0001) MISSED OFFSET
	class UClass*                                      mTradingPostDescriptor;                                   // 0x0348(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGBuildableTradingPost*                     mTradingPost;                                             // 0x0350(0x0008) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	TArray<struct FTutorialHintData>                   mIntroTutorialData;                                       // 0x0358(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UClass*                                      mIronOreDescriptor;                                       // 0x0368(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidPickUpIronOre;                                        // 0x0370(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData04[0x7];                                       // 0x0371(0x0007) MISSED OFFSET
	class UClass*                                      mDropPodItemClass;                                        // 0x0378(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidDismantleDropPod;                                     // 0x0380(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData05[0x7];                                       // 0x0381(0x0007) MISSED OFFSET
	class UClass*                                      mStunSpearItemClass;                                      // 0x0388(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidEquipStunSpear;                                       // 0x0390(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData06[0x7];                                       // 0x0391(0x0007) MISSED OFFSET
	class UClass*                                      mStep1UpgradeSchematic;                                   // 0x0398(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidStep1Upgrade;                                         // 0x03A0(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData07[0x7];                                       // 0x03A1(0x0007) MISSED OFFSET
	class UClass*                                      mStep2UpgradeSchematic;                                   // 0x03A8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidStep2Upgrade;                                         // 0x03B0(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData08[0x7];                                       // 0x03B1(0x0007) MISSED OFFSET
	class UClass*                                      mStep3UpgradeSchematic;                                   // 0x03B8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidStep3Upgrade;                                         // 0x03C0(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData09[0x7];                                       // 0x03C1(0x0007) MISSED OFFSET
	class UClass*                                      mStep4UpgradeSchematic;                                   // 0x03C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidStep4Upgrade;                                         // 0x03D0(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData10[0x7];                                       // 0x03D1(0x0007) MISSED OFFSET
	class UClass*                                      mStep5UpgradeSchematic;                                   // 0x03D8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDidStep5Upgrade;                                         // 0x03E0(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData11[0x7];                                       // 0x03E1(0x0007) MISSED OFFSET
	class UClass*                                      mStartingPodClass;                                        // 0x03E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGStartingPod*                              mStartingPod;                                             // 0x03F0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	bool                                               mSkipTutorialInPIE;                                       // 0x03F8(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData12[0x3];                                       // 0x03F9(0x0003) MISSED OFFSET
	int                                                mTradingPostLevel;                                        // 0x03FC(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              mWaitTimeAfterCompletingMinorStep;                        // 0x0400(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mWaitTimeAfterCompletingHubStep;                          // 0x0404(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mHoldTimeToSkipIntro;                                     // 0x0408(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData13[0x4];                                       // 0x040C(0x0004) MISSED OFFSET
	struct FTimerHandle                                mHoldToSkipTimerHandle;                                   // 0x0410(0x0008)
	unsigned char                                      UnknownData14[0x8];                                       // 0x0418(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTutorialIntroManager");
		return ptr;
	}


	void UpdateTutorial(EIntroTutorialSteps nextTutorialStep);
	void StartSkipIntroSequence();
	void SetInputGatesFromTutorialLevel(class AFGPlayerController* PlayerController);
	void SetCanSkipTutorialIntro(bool canSkip);
	void OnSchematicPurchased(class UClass* newSchematic);
	void OnRep_TradingPostLevel();
	void OnPlayerAddedItemToInventory(class UClass* ItemClass, int numAdded);
	void OnPlayerAddedItemToArmSlot(class UClass* ItemClass, int numAdded);
	void OnBuildingBuiltGlobal(class AFGBuildable* buildable);
	void IntroDone();
	bool HasTradingpostBeenBuilt();
	int GetTradingPostLevel();
	float GetNormalizedProgressToSkip();
	bool GetIsTutorialCompleted();
	bool GetIsIntroSequenceDone();
	EIntroTutorialSteps GetCurrentTutorialStep();
	bool GetCanSkipTutorial();
	class AFGTutorialIntroManager* Get(class UObject* WorldContext);
	void EndSkipIntroSequence();
	void CompleteTutorial();
	void CancelSkipIntroSequence();
};


// Class FactoryGame.FGTutorialSubsystem
// 0x0048 (0x0070 - 0x0028)
class UFGTutorialSubsystem : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	TArray<class UClass*>                              mBuildingsBuilt;                                          // 0x0030(0x0010) (ZeroConstructor, SaveGame)
	bool                                               mHasSeenIntroTutorial;                                    // 0x0040(0x0001) (ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0041(0x0007) MISSED OFFSET
	TArray<class UClass*>                              mIntroTutorialMessages;                                   // 0x0048(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FTutorialData>                       mTutorialData;                                            // 0x0058(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class AFGPlayerState*                              mOwningPlayerState;                                       // 0x0068(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGTutorialSubsystem");
		return ptr;
	}


	void OnBuildingBuilt(class UClass* itemDesc);
	void ClearBuiltData();
	void AddToBuiltClasses(class UClass* inClass);
};


// Class FactoryGame.FGUseState_Valid
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_Valid : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_Valid");
		return ptr;
	}

};


// Class FactoryGame.FGUseableInterface
// 0x0000 (0x0028 - 0x0028)
class UFGUseableInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseableInterface");
		return ptr;
	}


	void UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState);
	void UnregisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void RegisterInteractingPlayer(class AFGCharacterPlayer* Player);
	void OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	void OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
	bool IsUseable();
	struct FText GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State);
};


// Class FactoryGame.FGUseState_VehicleHasDriver
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_VehicleHasDriver : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_VehicleHasDriver");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_VehicleInWater
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_VehicleInWater : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_VehicleInWater");
		return ptr;
	}

};


// Class FactoryGame.FGUseState_VehicleOccupied
// 0x0000 (0x0030 - 0x0030)
class UFGUseState_VehicleOccupied : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGUseState_VehicleOccupied");
		return ptr;
	}

};


// Class FactoryGame.FGVehicleCollisionBoxComponent
// 0x0020 (0x05A0 - 0x0580)
class UFGVehicleCollisionBoxComponent : public UBoxComponent
{
public:
	float                                              mFudgeFactor;                                             // 0x0580(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAddedZVelocityFactor;                                    // 0x0584(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxAddedZVelocity;                                       // 0x0588(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxCollisionVelocity;                                    // 0x058C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMinVelocityForAddedZ;                                    // 0x0590(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0594(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVehicleCollisionBoxComponent");
		return ptr;
	}


	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
};


// Class FactoryGame.FGVehicleDescriptor
// 0x0008 (0x0150 - 0x0148)
class UFGVehicleDescriptor : public UFGBuildDescriptor
{
public:
	class UClass*                                      mVehicleClass;                                            // 0x0148(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVehicleDescriptor");
		return ptr;
	}


	class UClass* GetVehicleClass(class UClass* inClass);
};


// Class FactoryGame.FGVehicleDestroyableInterface
// 0x0000 (0x0028 - 0x0028)
class UFGVehicleDestroyableInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVehicleDestroyableInterface");
		return ptr;
	}


	float GetForceThreshold();
	class UParticleSystem* GetDestroyEffect();
	class UAkAudioEvent* GetDestroyAudioEvent();
};


// Class FactoryGame.FGVehicleWheel
// 0x0038 (0x0128 - 0x00F0)
class UFGVehicleWheel : public UVehicleWheel
{
public:
	bool                                               mInvertSteering;                                          // 0x00F0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mAutoGenerateCollisionCylinder;                           // 0x00F1(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x26];                                      // 0x00F2(0x0026) MISSED OFFSET
	float                                              mCamberAtRest;                                            // 0x0118(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCamberAtMaxCompression;                                  // 0x011C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCamberAtMaxDroop;                                        // 0x0120(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCamberStiffness;                                         // 0x0124(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVehicleWheel");
		return ptr;
	}

};


// Class FactoryGame.FGVersionFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGVersionFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVersionFunctionLibrary");
		return ptr;
	}


	bool IsPublicBuild();
	class FString GetVersionString();
	EGameVersion GetGameVersion();
};


// Class FactoryGame.FGVirtualCursorFunctionLibrary
// 0x0000 (0x0028 - 0x0028)
class UFGVirtualCursorFunctionLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVirtualCursorFunctionLibrary");
		return ptr;
	}


	void EnableVirtualCursor(class APlayerController* PC);
	void DisableVirtualCursor(class APlayerController* PC);
};


// Class FactoryGame.FGVolumeMapArea
// 0x0010 (0x0370 - 0x0360)
class AFGVolumeMapArea : public AVolume
{
public:
	class UClass*                                      mMapArea;                                                 // 0x0360(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0368(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGVolumeMapArea");
		return ptr;
	}


	void OnPrimitiveComponentEntered(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool fromSweep, const struct FHitResult& SweepResult);
	class UClass* GetMapArea();
};


// Class FactoryGame.FGWalkwayHologram
// 0x0010 (0x03F8 - 0x03E8)
class AFGWalkwayHologram : public AFGFactoryBuildingHologram
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x03E8(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWalkwayHologram");
		return ptr;
	}

};


// Class FactoryGame.FGWaterAudio
// 0x0010 (0x0038 - 0x0028)
class UFGWaterAudio : public UObject
{
public:
	TArray<struct FPawnImpactAudio>                    mImpactAudioMap;                                          // 0x0028(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWaterAudio");
		return ptr;
	}


	void OnPawnHitSurface(class AFGWaterVolume* waterVolume, class APawn* Pawn, const struct FVector& surfaceLocation);
	void OnCameraExitedWater(class AFGWaterVolume* waterVolume, const struct FVector& exitLocation, class AFGPlayerController* PC);
	void OnCameraEnteredWater(class AFGWaterVolume* waterVolume, const struct FVector& enterLocation, class AFGPlayerController* PC);
	class UAkAudioEvent* GetImpactEvent(class APawn* Pawn);
};


// Class FactoryGame.FGWaterVolume
// 0x0038 (0x03A8 - 0x0370)
class AFGWaterVolume : public APhysicsVolume
{
public:
	unsigned char                                      UnknownData00[0x18];                                      // 0x0370(0x0018) MISSED OFFSET
	class UClass*                                      mAreaClass;                                               // 0x0388(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mWaterAudio;                                              // 0x0390(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class UClass*                                      mPostProcessSettings;                                     // 0x0398(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x03A0(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWaterVolume");
		return ptr;
	}


	void OnPrimitiveComponentExited(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	void OnPrimitiveComponentEntered(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool fromSweep, const struct FHitResult& SweepResult);
};


// Class FactoryGame.FGWeaponAttachmentProjectile
// 0x0000 (0x0370 - 0x0370)
class AFGWeaponAttachmentProjectile : public AFGWeaponAttachment
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWeaponAttachmentProjectile");
		return ptr;
	}

};


// Class FactoryGame.FGWeaponChild
// 0x0008 (0x0340 - 0x0338)
class AFGWeaponChild : public AFGEquipmentChild
{
public:
	bool                                               mIsLoaded;                                                // 0x0338(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0339(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWeaponChild");
		return ptr;
	}


	void NotifyReloading();
	void NotifyReloadComplete();
	void NotifyPrimaryFireExecuted();
	void NotifyFailedToFire();
	void NotifyEndSecondaryFire();
	void NotifyEndPrimaryFire();
	void NotifyBeginSecondaryFire();
	void NotifyBeginPrimaryFire();
};


// Class FactoryGame.FGWeaponProjectileFire
// 0x0030 (0x0440 - 0x0410)
class AFGWeaponProjectileFire : public AFGWeapon
{
public:
	struct FProjectileData                             mProjectileData;                                          // 0x0410(0x0030) (Edit, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWeaponProjectileFire");
		return ptr;
	}

};


// Class FactoryGame.FGWheeledVehicle
// 0x01C8 (0x06A0 - 0x04D8)
class AFGWheeledVehicle : public AFGVehicle
{
public:
	class UFGWorkBench*                                mWorkBench;                                               // 0x04D8(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FTimerHandle                                mUpdateMovementHandle;                                    // 0x04E0(0x0008) (BlueprintVisible)
	bool                                               mForceSimulationMode;                                     // 0x04E8(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mForceRealMode;                                           // 0x04E9(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x04EA(0x0006) MISSED OFFSET
	struct FScriptMulticastDelegate                    TranferStatusChangedDelegate;                             // 0x04F0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FReplicatedAddedVelocitiesState             mReplicatedState;                                         // 0x0500(0x000C) (Net, ZeroConstructor, Transient, IsPlainOldData)
	float                                              mFuelConsumption;                                         // 0x050C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mCurrentFuelAmount;                                       // 0x0510(0x0004) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsLoadingVehicle;                                        // 0x0514(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsUnloadingVehicle;                                      // 0x0515(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x0516(0x0002) MISSED OFFSET
	class UClass*                                      mCurrentFuelClass;                                        // 0x0518(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsInAir;                                                 // 0x0520(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0521(0x0003) MISSED OFFSET
	int                                                mNumWheelsOnGround;                                       // 0x0524(0x0004) (ZeroConstructor, IsPlainOldData)
	class UWheeledVehicleMovementComponent*            mVehicleMovement;                                         // 0x0528(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
	float                                              mDistBetweenDecals;                                       // 0x0530(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDecalLifespan;                                           // 0x0534(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UMaterial*                                   mDefaultTireTrackDecal;                                   // 0x0538(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FTireTrackDecalDetails>              mTireTrackDecals;                                         // 0x0540(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	struct FVector                                     mDecalSize;                                               // 0x0550(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mFoliageDestroyRadius;                                    // 0x055C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAddedGroundAngularVelocityStrengthYaw;                   // 0x0560(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAddedGroundAngularVelocityStrengthPitch;                 // 0x0564(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAddedAirControlAngularVelocityStrengthYaw;               // 0x0568(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAddedAirControlAngularVelocityStrengthPitch;             // 0x056C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNaturalAngularVelocityStrengthYaw;                       // 0x0570(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNaturalAngularVelocityStrengthPitch;                     // 0x0574(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNaturalAirAngularVelocityStrengthYaw;                    // 0x0578(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mNaturalAirAngularVelocityStrengthPitch;                  // 0x057C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAddedAngularVelocityInputSmoothingSpeed;                 // 0x0580(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x0584(0x0004) MISSED OFFSET
	class UBoxComponent*                               mFoliageCollideBox;                                       // 0x0588(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mIsSimulated;                                             // 0x0590(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData04[0x3];                                       // 0x0591(0x0003) MISSED OFFSET
	float                                              mSimulationDistance;                                      // 0x0594(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UFloatingPawnMovement*                       mSimulationMovementComponent;                             // 0x0598(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       mFuelInventory;                                           // 0x05A0(0x0008) (Edit, ExportObject, Net, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, SaveGame, IsPlainOldData)
	class UFGInventoryComponent*                       mStorageInventory;                                        // 0x05A8(0x0008) (Edit, ExportObject, Net, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, SaveGame, IsPlainOldData)
	int                                                mInventorySize;                                           // 0x05B0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData05[0x14];                                      // 0x05B4(0x0014) MISSED OFFSET
	TArray<struct FSurfaceParticlePair>                mVehicleParticeMap;                                       // 0x05C8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	TArray<struct FParticleTemplatePair>               mActiveParticleAndTemplate;                               // 0x05D8(0x0010) (ZeroConstructor)
	class FString                                      mTireEffectSocketName;                                    // 0x05E8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	class UFGTargetPointLinkedList*                    mTargetNodeLinkedList;                                    // 0x05F8(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	bool                                               mIsPathVisible;                                           // 0x0600(0x0001) (Net, ZeroConstructor, SaveGame, IsPlainOldData)
	unsigned char                                      UnknownData06[0x7];                                       // 0x0601(0x0007) MISSED OFFSET
	TArray<struct FVector>                             mLastDecalLocations;                                      // 0x0608(0x0010) (ZeroConstructor)
	TArray<class UHierarchicalInstancedStaticMeshComponent*> mOverlappedHISMComponents;                                // 0x0618(0x0010) (ExportObject, ZeroConstructor)
	float                                              mAddedAngularVelocityInputPitch;                          // 0x0628(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              mAddedAngularVelocityInputYaw;                            // 0x062C(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x4];                                       // 0x0630(0x0004) MISSED OFFSET
	float                                              mReverseAddedAngularVelocityYawMultiplier;                // 0x0634(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasAirControl;                                           // 0x0638(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData08[0x3];                                       // 0x0639(0x0003) MISSED OFFSET
	float                                              mGroundTraceLength;                                       // 0x063C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData09[0x4];                                       // 0x0640(0x0004) MISSED OFFSET
	float                                              mMaxDeltaLinearVelocity;                                  // 0x0644(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData10[0x4];                                       // 0x0648(0x0004) MISSED OFFSET
	float                                              mMaxDeltaAngularVelocity;                                 // 0x064C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mRollStabilisationStrength;                               // 0x0650(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxRollAngleForUpsideDown;                               // 0x0654(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxFlatOnGroundRollAngleLimit;                           // 0x0658(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxRollForActivationOfAssistedVelocities;                // 0x065C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mMaxSpeedForAddedAcceleration;                            // 0x0660(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaxAssistedAcceleration;                                 // 0x0664(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasAssistedVelocities;                                   // 0x0668(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasRollStabilisation;                                    // 0x0669(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData11[0x2];                                       // 0x066A(0x0002) MISSED OFFSET
	float                                              mDriftingLateralForce;                                    // 0x066C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDriftingUpwardForce;                                     // 0x0670(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData12[0x4];                                       // 0x0674(0x0004) MISSED OFFSET
	class UCurveFloat*                                 mDriftForwardForceStrengthCurve;                          // 0x0678(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<struct FName>                               mDriftForceBones;                                         // 0x0680(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	float                                              mMinAngleForDrift;                                        // 0x0690(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData13[0xC];                                       // 0x0694(0x000C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWheeledVehicle");
		return ptr;
	}


	bool WantsToMove();
	void UseReplicatedState();
	void SetPathVisibility(bool inVisible);
	void SetPathFromArray(TArray<class AFGTargetPoint*> targetPoints);
	void SetMovementComponent(class UWheeledVehicleMovementComponent* MovementComponent);
	void SetIsDrifting(bool newDrifting);
	void SetAddedAngularVelocityYaw(float yawToAdd);
	void SetAddedAngularVelocityPitch(float pitchToAdd);
	void ServerUpdateAssistedVelocitiesState(bool inDrifting, float inInputYaw, float inInputPitch);
	void ResetAddedAngularVelocityValues();
	void RemoveTargetPoint(class AFGTargetPoint* targetToRemove);
	void PlayFoliageDestroyedEffect(class UParticleSystem* destroyEffect, class UAkAudioEvent* destroyAudioEvent, const struct FVector& Location);
	void OnRep_TransferStatusChanged();
	void OnRep_IsSimulated();
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult);
	int NumWheelsOnGround();
	bool IsValidFuel(class UClass* Resource);
	bool IsSimulated();
	bool HasFuel();
	class UWheeledVehicleMovementComponent* GetVehicleMovementComponent();
	void GetTireData(TArray<struct FTireData>* out_tireData);
	class UFGTargetPointLinkedList* GetTargetNodeLinkedList();
	class UFGInventoryComponent* GetStorageInventory();
	class UFloatingPawnMovement* GetSimulationComponent();
	bool GetPathVisibility();
	bool GetIsInAir();
	bool GetIsGrounded();
	bool GetIsDrifting();
	class UFGInventoryComponent* GetFuelInventory();
	float GetForwardSpeed();
	struct FVector GetDriftForceOffset();
	bool FilterFuelClasses(class UClass* Object, int idx);
	void CreateInventoryItemDrops();
};


// Class FactoryGame.FGWheeledVehicleHologram
// 0x0000 (0x03B8 - 0x03B8)
class AFGWheeledVehicleHologram : public AFGVehicleHologram
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWheeledVehicleHologram");
		return ptr;
	}

};


// Class FactoryGame.FGWheeledVehicleMovementComponent4W
// 0x0048 (0x0478 - 0x0430)
class UFGWheeledVehicleMovementComponent4W : public UWheeledVehicleMovementComponent4W
{
public:
	bool                                               mUseDSOLGearbox;                                          // 0x0430(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0431(0x0003) MISSED OFFSET
	float                                              mDSOLMaxSlopeAngleLimit;                                  // 0x0434(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mSlopeShiftRatio;                                         // 0x0438(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mDownShiftLatency;                                        // 0x043C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x38];                                      // 0x0440(0x0038) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWheeledVehicleMovementComponent4W");
		return ptr;
	}


	float GetLargestTireLoadValue();
	float GetLargestLongitudinalSlip();
	float GetLargestLateralSlip();
};


// Class FactoryGame.FGWheeledVehicleMovementComponent6W
// 0x01B0 (0x0488 - 0x02D8)
class UFGWheeledVehicleMovementComponent6W : public UWheeledVehicleMovementComponent
{
public:
	struct FVehicleEngineData6W                        EngineSetup;                                              // 0x02D8(0x0090) (Edit)
	struct FVehicleDifferential6WData                  DifferentialSetup;                                        // 0x0368(0x0003) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               mUseDSOLGearbox;                                          // 0x036B(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mDSOLMaxSlopeAngleLimit;                                  // 0x036C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              mSlopeShiftRatio;                                         // 0x0370(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0374(0x0004) MISSED OFFSET
	struct FVehicleTransmissionData6W                  TransmissionSetup;                                        // 0x0378(0x0030) (Edit)
	float                                              mDownShiftLatency;                                        // 0x03A8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x03AC(0x0004) MISSED OFFSET
	struct FRuntimeFloatCurve                          SteeringCurve;                                            // 0x03B0(0x0078) (Edit)
	float                                              AckermannAccuracy;                                        // 0x0428(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x5C];                                      // 0x042C(0x005C) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWheeledVehicleMovementComponent6W");
		return ptr;
	}


	float GetLargestTireLoadValue();
	float GetLargestLongitudinalSlip();
	float GetLargestLateralSlip();
};


// Class FactoryGame.FGWidgetMultiplayer
// 0x0018 (0x0220 - 0x0208)
class UFGWidgetMultiplayer : public UUserWidget
{
public:
	bool                                               mIsOnline;                                                // 0x0208(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               mIsPlayingSatisfactory;                                   // 0x0209(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x020A(0x0006) MISSED OFFSET
	class FString                                      mTitle;                                                   // 0x0210(0x0010) (BlueprintVisible, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWidgetMultiplayer");
		return ptr;
	}

};


// Class FactoryGame.FGWidgetSwitcher
// 0x0058 (0x0188 - 0x0130)
class UFGWidgetSwitcher : public UWidgetSwitcher
{
public:
	float                                              mFadeOutTime;                                             // 0x0130(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0134(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate                    mOnWidgetSet;                                             // 0x0138(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    mOnFadoutDone;                                            // 0x0148(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x18];                                      // 0x0158(0x0018) MISSED OFFSET
	class UWidget*                                     mPendingNewWidget;                                        // 0x0170(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGMenuBase*                                 mEnteringWidget;                                          // 0x0178(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGMenuBase*                                 mExitingWidget;                                           // 0x0180(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWidgetSwitcher");
		return ptr;
	}


	void FadeOut();
	void ExitAnimationTookToLong();
	void EnterAnimationTookToLong();
};


// Class FactoryGame.FGWildCardDescriptor
// 0x0000 (0x0128 - 0x0128)
class UFGWildCardDescriptor : public UFGItemDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWildCardDescriptor");
		return ptr;
	}

};


// Class FactoryGame.FGWindow
// 0x0000 (0x0208 - 0x0208)
class UFGWindow : public UUserWidget
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWindow");
		return ptr;
	}


	class UUserWidget* GetCloseButton();
};


// Class FactoryGame.FGWireHologram
// 0x0040 (0x0420 - 0x03E0)
class AFGWireHologram : public AFGBuildableHologram
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x03E0(0x0008) MISSED OFFSET
	class UFGCircuitConnectionComponent*               mConnections[0x2];                                        // 0x03E8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AFGPowerPoleHologram*                        mPowerPole;                                               // 0x03F8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class UClass*                                      mDefaultPowerPoleRecipe;                                  // 0x0400(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mStartLocation;                                           // 0x0408(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	int                                                mCurrentConnection;                                       // 0x0414(0x0004) (ZeroConstructor, IsPlainOldData)
	class UStaticMeshComponent*                        mWireMesh;                                                // 0x0418(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWireHologram");
		return ptr;
	}


	void OnAutomaticPoleDisableToggle(bool Disabled);
};


// Class FactoryGame.FGWorkBench
// 0x0030 (0x0270 - 0x0240)
class UFGWorkBench : public USceneComponent
{
public:
	class UClass*                                      mCurrentRecipe;                                           // 0x0240(0x0008) (ZeroConstructor, IsPlainOldData)
	float                                              mCurrentManufacturingProgress;                            // 0x0248(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              mManufacturingSpeed;                                      // 0x024C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGCharacterPlayer*                          mPlayerWorkingAtBench;                                    // 0x0250(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	float                                              mRecipeRate;                                              // 0x0258(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               mIsProducing;                                             // 0x025C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x025D(0x0003) MISSED OFFSET
	class UFGInventoryComponent*                       mInventory;                                               // 0x0260(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mProduceClickSpeed;                                       // 0x0268(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHoldToProduce;                                           // 0x026C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x026D(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWorkBench");
		return ptr;
	}


	void SetWorkBenchUser(class AFGCharacterPlayer* newUser);
	void SetRecipe(class UClass* Recipe);
	void SetIsPressingProduce(bool isPressingProduce);
	void SetInventory(class UFGInventoryComponent* newInventory);
	void SetHoldToProduce(bool newHold);
	void RemoveIngredientsAndAwardRewards(class UFGInventoryComponent* inventory, class UClass* Recipe);
	void Produce(float produceSpeed);
	bool IsProducing();
	class AFGCharacterPlayer* GetWorkBenchUser();
	float GetProduceClickSpeed();
	class AFGCharacterPlayer* GetPlayerWorkingAtBench();
	float GetManufacturingSpeed();
	float GetManufacturingProgress();
	class UFGInventoryComponent* GetInventory();
	bool GetHoldToProduce();
	class UClass* GetCurrentRecipe();
	void CraftComplete();
	bool CanProduce(class UClass* Recipe, class UFGInventoryComponent* inventory);
};


// Class FactoryGame.FGWorldCreationInterface
// 0x0000 (0x0028 - 0x0028)
class UFGWorldCreationInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWorldCreationInterface");
		return ptr;
	}

};


// Class FactoryGame.FGWorldSettings
// 0x00D8 (0x0628 - 0x0550)
class AFGWorldSettings : public AWorldSettings
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0550(0x0008) MISSED OFFSET
	TArray<class AFGDynamicExponentialFogVolume*>      mFogVolumes;                                              // 0x0558(0x0010) (ZeroConstructor, Transient)
	TArray<class AFGAmbientVolume*>                    mAmbientVolumes;                                          // 0x0568(0x0010) (ZeroConstructor, Transient)
	TArray<class AFGWaterVolume*>                      mWaterVolumes;                                            // 0x0578(0x0010) (ZeroConstructor, Transient)
	struct FExponentialFogSettings                     mDefaultHeightFogSettings;                                // 0x0588(0x0048) (Edit, DisableEditOnTemplate)
	class AExponentialHeightFog*                       mExponentialHeightFog;                                    // 0x05D0(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class AFGSkySphere*                                mSkySphere;                                               // 0x05D8(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class AFGMinimapCaptureActor*                      mMinimapCaptureActor;                                     // 0x05E0(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class UAkAudioEvent*                               mLevelStartedEvent;                                       // 0x05E8(0x0008) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class FString                                      mDefaultLoadSave;                                         // 0x05F0(0x0010) (Edit, ZeroConstructor, DisableEditOnTemplate)
	float                                              mStartTimeOfDay;                                          // 0x0600(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0604(0x0004) MISSED OFFSET
	class AFGBuildableSubsystem*                       mBuildableSubsystem;                                      // 0x0608(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGFoundationSubsystem*                      mFoundationSubsystem;                                     // 0x0610(0x0008) (ZeroConstructor, SaveGame, IsPlainOldData)
	class AFGAudioVolumeSubsystem*                     mAudioVolumeSubsystem;                                    // 0x0618(0x0008) (ZeroConstructor, IsPlainOldData)
	class AFGFoliageRemovalSubsystem*                  mFoliageRemovalSubsystem;                                 // 0x0620(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class FactoryGame.FGWorldSettings");
		return ptr;
	}


	void UpdateWorldBounds();
	class UAkAudioEvent* GetLevelStartedAkEvent();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
