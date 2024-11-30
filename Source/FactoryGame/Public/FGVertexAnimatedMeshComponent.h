// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AkComponent.h"
#include "FGColoredInstanceMeshProxy.h"
#include "FGSignificanceInterface.h"
#include "NiagaraSystem.h"
#include "Animation/AnimationAsset.h"
#include "Curves/RichCurve.h"
#include "Subsystems/WorldSubsystem.h"
#include "FGVertexAnimatedMeshComponent.generated.h"

//! TODO LIST
// TODO support multi material
// TODO maybe do this over 1-2 frames?
// TODO handle OC
// TODO contains can be pre-cached as an uint8:1 or bool
// TODO calculate offset when dealing windup / down interp.

// TODO Add non linear encoding to the textures, we need more once we are further away from 0.

class UAkAudioEvent;
struct FCompressedRichCurve;
class USkeletalMesh;

UENUM()
enum class EVTXAnimProductionStatus : uint8
{
	IS_UNKNOWN,
	IS_WINDINGUP,
	IS_PRODUCING,
	IS_WINDINGDOWN,
	IS_IDLE
};

enum class EVTXAnimOverclockState : uint8
{
	ISO_Default,
	ISO_OverClocked,
	ISO_UnderClocked
};

USTRUCT()
struct FVTXAnimationStateEntry
{
	GENERATED_BODY()

	/* Chance that this animation state is played.*/
	UPROPERTY(EditDefaultsOnly)
	float chance = 1;

	UPROPERTY(EditDefaultsOnly)
	float AnimationLength = 1;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* AnimationMaterialInstance;
	
	// Automatically copied from `mEdNotifies` cached as a direct pointer to the class to avoid re-instanced versions of the inline class.
	UPROPERTY( VisibleDefaultsOnly, Category = "Vertex animimations" )
	TArray< UFGNotifyBase* > mNotifiesCDO;

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Vertex animimations" )
	TArray< UFGNotifyBase* > mEdNotifies;
#endif
};

USTRUCT()
struct FVTXAnimationStates
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FVTXAnimationStateEntry> mStateEntries;
};

UCLASS()
class FACTORYGAME_API UVertexAnimationNotifySubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	// FTickableGameObject implementation Begin
	virtual void Tick(float DeltaTime) override;
	
	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Always;
	}
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UVTXAnimManager, STATGROUP_Tickables);
	}
	// End FTickableGameObject implementation
	
	void TickAnimationRandomization(float DeltaTime);
	
	/* Add component to system */
	static void AddRelevantComponents(UFGVertexAnimatedMeshComponent* Mesh);
	static void RemoveRelevantComponents(UFGVertexAnimatedMeshComponent* Mesh);

	static void AddManagedRandomizedAnimationEntry(UFGVertexAnimatedMeshComponent* Mesh);
	static void RemoveManagedRandomizedAnimationEntry(UFGVertexAnimatedMeshComponent* Mesh);
	
protected:
	void DequeueEntries();

	bool GetPlayerViewpointAndLocation(FVector& OutVector, FRotator& OutRotation) const;

private:
	TQueue< UFGVertexAnimatedMeshComponent*, EQueueMode::Mpsc > mNewRelevantObjects;
	TQueue< UFGVertexAnimatedMeshComponent*, EQueueMode::Mpsc > mRemovedRelevantObjects;

	/* List of current ticked notify timelines. */
	UPROPERTY( VisibleInstanceOnly, Transient )
	TArray<UFGVertexAnimatedMeshComponent*> mRelevantProxies;

	/* Queue of animations that have randomization support. */
	UPROPERTY( VisibleInstanceOnly, Transient)
	TArray<UFGVertexAnimatedMeshComponent*> mAnimationRandomizationList; 
};

/**
 * 
 */
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGVertexAnimatedMeshComponent : public UFGColoredInstanceMeshProxy, public IFGSignificanceInterface
{
public:
	GENERATED_BODY()
	
	UFGVertexAnimatedMeshComponent();

	// Begin actor interface.
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	// End IFGSignificanceInterface.
	
	virtual bool ShouldAddToSignificanceManager() const;
	FORCEINLINE void IncrementTimeSinceLastTick( float DT ) { mTimeSinceLastTick += DT; }
	FORCEINLINE float GetTimeSinceLastTick() const			{ return mTimeSinceLastTick; }
	FORCEINLINE void SetTimeSinceLastTick(float Value)		{ mTimeSinceLastTick = Value;}
	FORCEINLINE float GetCurrentAnimationDuration( float WorldTime, bool bWithTimeSpeedMultiplier = true ) const
	{
		const float Speed = bWithTimeSpeedMultiplier ? CurrentAnimationSpeed : 1.f;
		return FMath::Fmod(( ( WorldTime - StartTime ) * Speed ) + CurrentSequenceDuration, CurrentSequenceDuration);
	}
	FORCEINLINE float GetSequenceLength() const { return CurrentSequenceDuration; }
	FORCEINLINE void SetLastTickTime(float AnimationDurationLastTick ) { mTimeLastTime = AnimationDurationLastTick; }
	FORCEINLINE float GetLastTickTime() const { return mTimeLastTime; }
	void RandomizeAnimation();
	
	/* Called when parent buildable production status changed.*/
	UFUNCTION()
	void OnProductionStatusChanged( EProductionStatus NewState );

	UFUNCTION()
	void OnBuildingCurrentPotentialChanged( float NewPotential );

	UFUNCTION()
	void DelayedOverclockingChanged();

	void OnOverclockingChanged(EVTXAnimOverclockState NewState, bool IsSignificant);
	void UpdateEffectTimeline( const float LastTickTime, const float Dist, const float WorldTime );

	FORCEINLINE void SetWorldTimeLastRandomization(float WorldTime) { mWorldTimeLastRandomization = WorldTime; }
	FORCEINLINE float GetTimeSinceLastRandomization( const UWorld* World ) const { return World->TimeSince( mWorldTimeLastRandomization ); }

protected:
	virtual void OnUpdateState(EVTXAnimProductionStatus NewState);
	virtual void StartProducing(bool bFromFrozenIdle = false, int32 AnimationSequenceID = 0  );
	virtual void StartWindup();
	virtual void StartWindDown();
	virtual void StartIdle();
	
	//virtual void TransitionToIdle(float ProductionPct = 0);
	virtual void FreezeAnimation(float ProductionAnimationDuration);
	virtual void SetupWireMesh();
	virtual void KillWireMesh();

	/* Get time to revert back to zero frame on the GPU. */
	FORCEINLINE float GetZeroFrame() const { return GetWorld()->GetTimeSeconds(); }
	
	UFUNCTION()
	void UpdateStateToProducing();
	
	UFUNCTION()
	void UpdateStateToIdle();

	UFUNCTION()
	void StartRandomizedProductionAnimation();
	
	// Returns material for the new selected state, handles randomization and caches sequence time.
	TArray<UMaterialInterface*> GetMaterialsFromState(EVTXAnimProductionStatus State, int32 AnimationSequenceID = 0);
	
	void UpdateMaterial(TArray<UMaterialInterface*> Materials);

	UPROPERTY(EditDefaultsOnly)
	float mSignificanceRange = 6000;
	
	UPROPERTY(EditDefaultsOnly,Category="Animation")
	TMap<EVTXAnimProductionStatus,FVTXAnimationStates> mAnimationStateData;

	UPROPERTY(EditDefaultsOnly,Category="Animation|Wire")
	USkeletalMesh* mWireMesh;

	UPROPERTY(EditDefaultsOnly,Category="Animation|Wire")
	UAnimationAsset* mAnimationAsset;

	UPROPERTY(EditDefaultsOnly,Category="Animation|Wire")
	float mMaxDrawRangeCable = 5000;
	
	UPROPERTY(EditDefaultsOnly,Category="Animation|Wire")
	float mWireMeshTimeAdjustment;

	UPROPERTY(EditDefaultsOnly,Category="Animation|Binds")
	int8 TimePrimitiveDataBindID = -1;

	UPROPERTY(EditDefaultsOnly,Category="Animation|Binds")
	int8 TimeSpeedPrimitiveDataBindID = -1;

	UPROPERTY(EditDefaultsOnly, Category= "Animation")
	uint8 bAllowWindUpDownInterpolation:1 = false;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float mOverClockedAnimationSpeed = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float mUnderClockedAnimationSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly,Category="Animation|Wire")
	uint8 bNeedsSimulationForWires:1 = false;
	
	// Begin pre-cached states.
	/*	Cached on property changed for runtime speed.*/
	UPROPERTY()
	uint8 bHasWindDownSequence:1 = false;

	/*	Cached on property cached for runtime speed.*/
	UPROPERTY()
	uint8 bHasWindUpSequence:1 = false;

	/*	Cached on property cached for runtime speed.*/
	UPROPERTY()
	uint8 bHasWire:1 = false;

	/* Cached property on having custom animation sequences. */
	UPROPERTY(VisibleDefaultsOnly,Category="Animation|Cached")
	uint8 bHasProducingAnimationVariations:1 = false;

	uint8 bIsInRandomizationManagementSystem:1 = false;

	UPROPERTY()
	uint8 bIsSignificant:1 = false;

	int8 mCurrentSequence = 0;
	
private:
	UPROPERTY(VisibleInstanceOnly,Transient)
	USkeletalMeshComponent* mSpawnedWireMeshComponent;

	/*	Current animation state. */
	EVTXAnimProductionStatus CurrentStatus = EVTXAnimProductionStatus::IS_UNKNOWN;

	int32 mPendingProductionRandomizedEntry = INDEX_NONE;
	
	/* How many seconds were we into the animation before the switch to a new state was handled?*/
	float AnimationDurationBeforeStateSwitch = 0;

	/* What time did we start the animation? this value has some offset due to the fact that some sequences dont have an wind down animation
	 * but just freeze instead */
	float StartTime = 0.f;
	
	/*	Current sequence duration needed for idling and restarting animations */
	float CurrentSequenceDuration = 0.f;

	float mTimeSinceLastTick = 0.f;
	float mTimeLastTime = 0.f;
	
	/* Last world time we randomized the animation selection. */
	float mWorldTimeLastRandomization = -1;

public:
	/*	Animation speed assigned to the material and notifies timeline,
	 * can be 0 when idling and above one when overclocked. */
	float CurrentAnimationSpeed = 1.f;
	float PendingSpeed = 1.f;

	/* Current overclocking potential. */
	float CurrentMachinePotential = 1.f;

	friend class UFGAnimatedVFXNotify;
	friend class UFGAnimatedSFXNotify;
	friend class UFGStaticSFXNotify;
	
	UPROPERTY()
	TMap<FName, UAkComponent*> mSpawnedAkSoundComponents;
	
	UPROPERTY()
	TMap<FName, UParticleSystemComponent*> mSpawnedParticleEffects;
	
	FTimerHandle mStateSwitchTimer; 
	FTimerHandle mDelayedOverclockTimer;
	FTimerHandle mRandomizeAnimationTimerHandle;

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
	UFUNCTION(BlueprintCallable,Category="EditorOnly")
	static void SampleTimelineDataFromEntry(UAnimSequence* Sequence, TSubclassOf<AFGBuildable> Target, FName ComponentName);
#endif
};

UCLASS( EditInlineNew, Abstract )
class FACTORYGAME_API UFGNotifyBase : public UObject
{
public:
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	float MinimumDistance;

	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	float MaximumDistance;

	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	float NotifyTriggerTime;

	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	float EndTime;

	FORCEINLINE virtual bool IsOneShot() const { return true; }
	bool mIsActive;

	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	FName DebugName;

	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	bool bEnabled = true;
	
	UFGNotifyBase() :
		MinimumDistance( 0 ),
		MaximumDistance( 0 ),
		NotifyTriggerTime( 0.0 ),
		EndTime( INDEX_NONE ),
		mIsActive( false )
	{
	}

	virtual void Fire( UFGVertexAnimatedMeshComponent* Owner, float CurrentTime = 0.f, bool bForceSeek = false ) const
	{ }
	virtual void Deactivate(UFGVertexAnimatedMeshComponent* Owner) const
	{ }
	
	static void TryFireNotify( const float& Distance, const float& AnimDuration, const float& LastTickTime, UFGVertexAnimatedMeshComponent* Owner,const UFGNotifyBase* Entry, bool bForceSeek = false );
#if WITH_EDITOR
	virtual void Compress() {};
#endif
};

/*Base class for static entries SFX and VFX.*/
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGStaticNotifyBase : public UFGNotifyBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditDefaultsOnly, Category = "Base" )
	FTransform LocalTransform = FTransform::Identity;
};

/*	Simple vfx one shot notifies that auto destroy.
 *  Perfect for one shot sparks, steam, exhaust etc. */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGStaticVFXNotify : public UFGStaticNotifyBase
{
	GENERATED_BODY()
public:
	UPROPERTY( EditDefaultsOnly)
	UParticleSystem* PSSystem = nullptr;

	UPROPERTY( EditDefaultsOnly)
	UNiagaraSystem* NPSSystem = nullptr;

	virtual void Fire( UFGVertexAnimatedMeshComponent* Owner, float CurrentTime = 0.f, bool bForceSeek = false ) const override;
};

/*	Simple SFX one shot notifies that auto destroy.
 *  Perfect for one shot sparks, steam, exhaust etc. */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGStaticSFXNotify : public UFGStaticNotifyBase
{
	GENERATED_BODY()
public:
	UPROPERTY( EditDefaultsOnly)
	UAkAudioEvent* AKEvent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FString RTPCName = FString("RTPC_Factory_OverclockRate");
	
	virtual void Fire( UFGVertexAnimatedMeshComponent* Owner, float CurrentTime = 0.f, bool bForceSeek = false ) const override;
};


/*Base class for animated entries SFX and VFX.*/
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced, Abstract)
class FACTORYGAME_API UFGAnimatedNotifyBase : public UFGNotifyBase
{
	GENERATED_BODY()
public:
	FTransform GetTransformAtTime(float Time) const;

protected:
	UPROPERTY()
	FCompressedRichCurve FloatCurvesX;
	UPROPERTY()
	FCompressedRichCurve FloatCurvesY;
	UPROPERTY()
	FCompressedRichCurve FloatCurvesZ;

	UPROPERTY()
	FCompressedRichCurve RotationCurvesRoll;
	UPROPERTY()
	FCompressedRichCurve RotationCurvesYaw;
	UPROPERTY()
	FCompressedRichCurve RotationCurvesPitch;

	virtual bool IsOneShot() const override { return false; }

#if WITH_EDITOR
#if WITH_EDITORONLY_DATA
	// Uncompressed curves, populated in editor time and compress to the curves above for runtime.
	UPROPERTY(EditDefaultsOnly, Category ="Location")
	FRichCurve EDFloatCurvesX;
	UPROPERTY(EditDefaultsOnly, Category ="Location")
	FRichCurve EDFloatCurvesY;
	UPROPERTY(EditDefaultsOnly, Category ="Location")
	FRichCurve EDFloatCurvesZ;

	UPROPERTY(EditDefaultsOnly, Category ="Rotation")
	FRichCurve EDRotationCurvesRoll;
	UPROPERTY(EditDefaultsOnly, Category ="Rotation")
	FRichCurve EDRotationCurvesYaw;
	UPROPERTY(EditDefaultsOnly, Category ="Rotation")
	FRichCurve EDRotationCurvesPitch;
	
	UPROPERTY(EditDefaultsOnly,Category="Optimization")
	float CurveResampleTolerance = 0.5f;
#endif
public:
	void SetCurveInfoAtTime( float Time, FVector Location, FRotator Rotation );
	void ResampleCurve();
private:
	virtual void Compress() override;
#endif
};


/* Animated SFX notifies.*/
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGAnimatedVFXNotify : public UFGAnimatedNotifyBase
{
public:
	GENERATED_BODY()
public:
	UPROPERTY( EditDefaultsOnly)
    UParticleSystem* PSSystem = nullptr;

	virtual void Fire(UFGVertexAnimatedMeshComponent* Owner, float CurrentTime, bool bForceSeek) const override;
	virtual void Deactivate(UFGVertexAnimatedMeshComponent* Owner) const override;
};

/* Animated VFX notifies.*/
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGAnimatedSFXNotify : public UFGAnimatedNotifyBase
{
	GENERATED_BODY()
public:
	UPROPERTY( EditDefaultsOnly)
	UAkAudioEvent* AKEvent = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FString RTPCName = FString("RTPC_Factory_OverclockRate");

	virtual void Fire(UFGVertexAnimatedMeshComponent* Owner, float CurrentTime, bool bForceSeek) const override;
	virtual void Deactivate(UFGVertexAnimatedMeshComponent* Owner) const override;
	
};
