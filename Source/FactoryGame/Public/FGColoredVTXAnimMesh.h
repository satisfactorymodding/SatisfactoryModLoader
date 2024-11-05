// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGColoredVTXAnimMeshInterface.h"
#include "FGSignificanceInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "Particles/WorldPSCPool.h"
#include "AkAudioEvent.h"
#include "Animation/AnimSequence.h"
#include "Components/TimelineComponent.h"
#include "Curves/RichCurve.h"
#include "Engine/SkeletalMesh.h"
#include "FGColoredVTXAnimMesh.generated.h"

class UFGAnimationTimeLineEntryBase;

USTRUCT(BlueprintType)
struct FACTORYGAME_API FVtxAnimEmitterTransformAtTime
{
	GENERATED_BODY()
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float Time;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FTransform Transform;

	FVtxAnimEmitterTransformAtTime() :
		Time(0.f),
		Transform( FTransform::Identity )
	{ }
};

/*Array for editor tool only.*/
USTRUCT(BlueprintType)
struct FACTORYGAME_API FVtxAnimEmitterTransformAtTimeArray
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FVtxAnimEmitterTransformAtTime> Data;

	FVtxAnimEmitterTransformAtTimeArray()
	{
	}
};

UCLASS( EditInlineNew )
class FACTORYGAME_API UFGAnimationTimeLineObject : public UObject
{
	GENERATED_BODY()
	
public:
	/* Debug name.*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName mSequenceName;
	
	/* Sequence animation length. */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 mNumFrames;

	UPROPERTY( EditDefaultsOnly, Instanced )
	TArray< UFGAnimationTimeLineEntryBase* > mTimelineData;
};

/* Base class for vfx & sfx entries. */
UCLASS(Blueprintable, EditInlineNew, abstract, DefaultToInstanced)
class FACTORYGAME_API UFGAnimationTimeLineEntryBase : public UObject
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
	
	UFGAnimationTimeLineEntryBase() :
		NotifyTriggerTime( 0.0 ),
		EndTime( INDEX_NONE ),
		mIsActive( false )
	{ }
	
	virtual void Fire( UFGColoredVTXAnimMesh* Owner, float CurrentTime = 0.f, bool bForceSeek = false ) const
	{ }
	virtual void Deactivate(UFGColoredVTXAnimMesh* Owner) const
	{ }
	static void TryFireNotify( const float& Distance, const float& AnimDuration, const float& DeltaTime, UFGColoredVTXAnimMesh* Owner,const UFGAnimationTimeLineEntryBase* Entry, bool bForceSeek = false );
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGAnimationTimeLineSFXEntry : public UFGAnimationTimeLineEntryBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditDefaultsOnly, Category = "Base|Audio" )
	UAkAudioEvent* AudioEvent;
	 
	UPROPERTY( EditDefaultsOnly, Category = "Base|Audio" )
	FTransform LocalTransform;
	
	// /* Do we allow seeking or should we just wait for the next audio event.
	// * RECOMMENDED for long audio events, avoid with short events. */
	// UPROPERTY( EditDefaultsOnly, Category = "Base|Audio" )
	// bool CanBeRecovered;
	
	virtual void Fire( UFGColoredVTXAnimMesh* Owner, float CurrentTime = 0.f, bool bForceSeek = false ) const override;
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGAnimationTimeLineVFXEntry : public UFGAnimationTimeLineEntryBase
{
	GENERATED_BODY()
public:
	UPROPERTY( EditDefaultsOnly, Category = "Base|VFX" )
	UParticleSystem* PSSystem;
	
	UPROPERTY( EditDefaultsOnly, Category = "Base|VFX" )
	FTransform LocalTransform;

	virtual void Fire( UFGColoredVTXAnimMesh* Owner, float CurrentTime = 0.f, bool bForceSeek = false ) const override;
};

// TODO look into FCompressedRichCurve for mem reduction.
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGAnimationTimeLineAnimatedEntry : public UFGAnimationTimeLineEntryBase
{
	GENERATED_BODY()
public:
	// Position X Y Z
	UPROPERTY()
	FRichCurve FloatCurvesX;
	UPROPERTY()
	FRichCurve FloatCurvesY;
	UPROPERTY()
	FRichCurve FloatCurvesZ;
	
	// Rotation
	UPROPERTY()
	FRichCurve RotationCurvesRoll;
	UPROPERTY()
	FRichCurve RotationCurvesYaw;
	UPROPERTY()
	FRichCurve RotationCurvesPitch;
	
	FTransform GetTransformAtTime(float Time) const;
	void SetCurveInfoAtTime(float Time, FVector Location, FRotator Rotation);
	void ResampleCurve();

	virtual bool IsOneShot() const override { return false; }
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class FACTORYGAME_API UFGAnimationTimeLineAnimatedVFXEntry : public UFGAnimationTimeLineAnimatedEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UParticleSystem* PSSystem;

	virtual void Fire(UFGColoredVTXAnimMesh* Owner, float CurrentTime, bool bForceSeek) const override;
	virtual void Deactivate(UFGColoredVTXAnimMesh* Owner) const override;
};

UCLASS()
class FACTORYGAME_API UVTXAnimManager : public UTickableWorldSubsystem
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
	// FTickableGameObject implementation End

	/* Add component to system */
	static void AddRelevantComponents(UFGColoredVTXAnimMesh* Mesh);
	static void RemoveRelevantComponents(UFGColoredVTXAnimMesh* Mesh);
	
protected:
	void DequeueEntries();

	bool GetPlayerViewpointAndLocation(FVector& OutVector, FRotator& OutRotation) const;
	

private:
	TQueue< UFGColoredVTXAnimMesh*, EQueueMode::Mpsc > mNewRelevantObjects;
	TQueue< UFGColoredVTXAnimMesh*, EQueueMode::Mpsc > mRemovedRelevantObjects;

	UPROPERTY( VisibleInstanceOnly, Transient )
	TArray<UFGColoredVTXAnimMesh*> mRelevantProxies;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ))
class FACTORYGAME_API UFGColoredVTXAnimMesh : public UFGColoredVTXAnimMeshInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
	UFGColoredVTXAnimMesh();

public:
	virtual float GetSignificanceRange() override { return mSignificanceRange; }

	FORCEINLINE void IncrementTimeSinceLastTick( float DT ) { mTimeSinceLastTick += DT; }
	FORCEINLINE float GetTimeSinceLastTick() const			{ return mTimeSinceLastTick; }
	FORCEINLINE void SetTimeSinceLastTick(float Value)		{ mTimeSinceLastTick = Value;}
	FORCEINLINE float GetCurrentAnimationDuration(float WorldTime) const
	{
		return FMath::Fmod(( WorldTime - mTimeOffset) + SequenceLengths[mCurrentSequence], SequenceLengths[mCurrentSequence]);
	}

	void UpdateEffectTimeline(const float Dt, const float Dist, const float WorldTime);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;

	// Begin UFGColoredVTXAnimMeshInterface interface.
	virtual void StopAnimation(float WorldTime) override;
	virtual void StartProductionAnimation(float WorldTime) override;
	virtual void BeginStopAnimation(float WorldTime) override;
	virtual void BeginStartAnimation(float WorldTime) override;
	virtual bool ShouldFireEffects() const;
	// End UFGColoredVTXAnimMeshInterface interface.

	void StopEffects();
	virtual void SpawnAndSetupWireMesh();
	void CleanupWireMesh();
	
	virtual bool ShouldSpawnWireMesh() const { return IsValid(mWireMesh); }

	UFUNCTION()
	void OnStartAnimationFinished();
	
	UFUNCTION()
	void OnShutdownAnimationFinished();
	
	UPROPERTY(EditAnywhere)
	float mSignificanceRange;
	
	UPROPERTY(EditAnywhere)
	float mMaxDrawRangeCable;
	
	/* Mesh for wires, will be spawned on significance.*/
	UPROPERTY(EditAnywhere)
	USkeletalMesh* mWireMesh = nullptr;

	UPROPERTY(EditAnywhere)
	UAnimationAsset* mAnimationAsset = nullptr;

#if WITH_EDITORONLY_DATA
	/* Array of animation sequences. */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Vertex animimations" )
	TArray< UFGAnimationTimeLineObject* > mAnimationTimelineData;
#endif
	
	UPROPERTY( VisibleDefaultsOnly, Category = "Vertex animimations" )
	TArray< UFGAnimationTimeLineObject* > mAnimationTimelineDataCDO;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 mProductionSequenceID = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 mStartupSequenceID = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 mShutdownSequenceID = 1;
	
	UPROPERTY(VisibleAnywhere)
	int32 mCurrentSequence = INDEX_NONE;

	UPROPERTY(EditDefaultsOnly,Category="Vertex Animations")
	TArray<float> SequenceLengths;

	UPROPERTY(EditDefaultsOnly,Category="Vertex Animations")
	float mMinimumRangeForStartupAnimation = 20000;

	bool mIsSignificant;
	
	float mTimeSinceLastTick;
	

	/* At what time was this animation paused. */
	float PausedAnimTime;
	/* Offset time to get the correct animation time on the gpu.*/
	float mTimeOffset;
	
	bool bIsPaused;

	UPROPERTY()
	TMap<FName, UAkComponent*> mSpawnedAkSoundComponents;

	UPROPERTY()
	TMap<FName, UParticleSystemComponent*> mSpawnedParticleEffects;

	UPROPERTY(VisibleInstanceOnly)
	USkeletalMeshComponent* mSpawnedWireMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float mWireMeshTimeAdjustment;
	
	friend class UFGAnimationTimeLineEntryBase;
	friend class UFGAnimationTimeLineSFXEntry;
	friend class UFGAnimationTimeLineAnimatedVFXEntry;
	friend class UFGAnimationTimeLineVFXEntry;
	
	FTimerHandle mStatusTimerHandle;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	UFUNCTION(BlueprintCallable,Category="EditorOnly")
	static void SampleTimelineDataFromEntry(UAnimSequence* Sequence, TSubclassOf<AFGBuildable> Target, FName ComponentName);
#endif
};
