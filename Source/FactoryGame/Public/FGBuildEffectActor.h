// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

/*	TODO cleanup this rushed class, we most likely wanna split splines & normal buildables.
 * 
 */

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Actor.h"
#include "FGLightweightBuildableSubsystem.h"
#include "FGBuildEffectActor.generated.h"

class UMeshComponent;
struct FInstanceData;
class UFGRecipe;
struct FItemAmount;
class UFGItemDescriptor;
struct FInstanceHandle;
class USplineComponent;

class AFGBuildable;
class UAbstractInstanceDataObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FBuildEffectEnded );

struct FLightweightActorData
{
	TSubclassOf< AFGBuildable > BuildableClass;
	FRuntimeBuildableInstanceData RuntimeData;
	UAbstractInstanceDataObject* Instances;
	int32 Index;
};

/* Swap data for the build effect to function. */
UCLASS( EditInlineNew, DefaultToInstanced )
class FACTORYGAME_API UFGBuildEffectMaterialSwapAssetData : public UAssetUserData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mBuildEffect;
};

UCLASS()
class FACTORYGAME_API AFGBuildEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGBuildEffectActor();
	
	// Begin Actor interface
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End Actor interface
	
	uint64 GetSpawnedFrame() const { return mSpawnedFrame; }

	void SetDismantle(bool State);
	//void AddAbstractDataEntry(FTransform Transform, UAbstractInstanceDataObject* Data,const TArray< FInstanceHandle* >& Handles);
	void AddAbstractDataEntry( TSubclassOf< AFGBuildable > buildableClass, const FRuntimeBuildableInstanceData& runtimeData, UAbstractInstanceDataObject* InstanceData, int32 Index);
	void RemoveAbstractDataEntry(  TSubclassOf< AFGBuildable > buildableClass, int32 index );
	
	// Add actor to the build effect.
	FORCEINLINE void SetActor( AActor* InSourceActor )
	{
		mSourceActors.Add(InSourceActor);
		NumActors += 1;
	}

	// Add actor(s) to the build effect.
	FORCEINLINE void SetActors( TArray<AActor*> InSourceActors )
	{
		for (const auto actor : InSourceActors)
		{
			mSourceActors.Add(actor);
			NumActors += 1;
		}
	}
	
	// Set recipe used for spawning flying resources, NOTE buildable can be null.
	void SetRecipe( TSubclassOf<UFGRecipe> inRecipe, AFGBuildable* buildable );

	// Force traditional way of building the effect force ignoring the zoop direction assumption logic.
	void MarkAsBlueprintBuildEffect() { mIsBlueprint = true;}

	FBuildEffectEnded& GetBind( UClass* actorClass );

	// TODO these should be protected.
	void Start();
	void Stop();
	
	bool mIsMarkedDismantle = false;
	
protected:
	// TODO move this bs to CPP too.
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnCostEffectActor(const FTransform& SpawnLocation, FVector TargetLocation, float TargetExtent, TSubclassOf<UFGItemDescriptor> Item);

	// TODO move this bs to CPP too.
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateVFX( float duration );

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSplineVFX( float duration );

	UFUNCTION(BlueprintImplementableEvent)
	void PlayThumbSound();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayBuildFinishedEffect();

private:
	void CreateVisuals();
	void ResolveMaterial(UMeshComponent* Mesh, const TArray<UMaterialInterface*>& Overrides);
	void SetupThrowQueue();
	
	float GetTotalSplineLength() const;
	void TryPlayThumbSound();

	UFUNCTION( BlueprintCallable, Category = "BuildEffectActor" )
	FTransform GetTransformOnSplines( bool bWorldSpace ) const;
	
	void UpdateCostQueue();
	

	UFUNCTION(BlueprintPure)
	bool GetDidStartSplineEffect() const { return mDidStartSplineEffect; }

	UFUNCTION(BlueprintPure)
	float GetVolume() const { return mVolume; }
	
	// TODO move this bs to CPP too.
	UFUNCTION(BlueprintCallable)
	void OnCostActorReachedTarget();

	void CleanupRemovedBuildables();

	void UpdateSplineBuildables(float Dt);
	void UpdateGenericBuildables(float Dt);
	void UpdateWires();

	void CalculateBuildEffectBounds();

private:
	TArray<USplineComponent*> GetBeltSourceSplinesOrdered( const TArray<class AFGBuildableConveyorBelt*>& inBelts, TArray<AActor*>& orderedActors ) const;
	TArray<USplineComponent*> GetPipeSourceSplineOrdered( const TArray<class AFGBuildablePipeBase*>& inPipes, TArray<AActor*>& orderedActors ) const;

	TArray<FLightweightActorData> LightweightActors;
	TArray<FInstanceHandle*> AllHandles;
	
public:
	/* Called before it start fading out */
	FBuildEffectEnded OnBuildEffectFinished;

	/* Called when the fade out on the spline based components starts to happen. */
	FBuildEffectEnded OnSplineBuildEffectFinished;
	
protected:
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UMaterialInterface* mDecalMaterial;
	
	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UMaterialInterface* mDecalBuildEffectMaterial;

	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UMaterialInterface* mMaskedColorDecalMaterial;

	UPROPERTY(EditDefaultsOnly,Category="Materials")
	UMaterialInterface* mMaskedColorDecalEffectMaterial;

	UPROPERTY(EditDefaultsOnly,Category="Materials")
	TObjectPtr<UMaterialInterface> mBuildEffectFallback;
	
	UPROPERTY(BlueprintReadWrite)
	float mCurrentMaterializeAmount = 0.f;
	
	UPROPERTY(BlueprintReadOnly)
	float mMaterializeAmountPerThrow;
	
	UPROPERTY(BlueprintReadOnly)
	int32 itemsThrown = 0;
	
	/* Speed for the glow up and dissolve effect. */
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Time")
	float mEndStageSpeed = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Curves")
	FRuntimeFloatCurve mOffsetCurve;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Curves")
	FRuntimeFloatCurve mVolumeCurve;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Curves")
	FRuntimeFloatCurve mGlowCurve;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Curves")
	FRuntimeFloatCurve mFadeCurve;
	
	UPROPERTY(EditDefaultsOnly,Category = "Effect|Splines")
	bool mShouldDelayBelts = true;

	/*Build speed, meters per second.*/
	UPROPERTY(EditDefaultsOnly,Category = "Effect|Splines")
	float splineBuildEffectSpeed;
	
	/* delay time on belt*/
	UPROPERTY(EditDefaultsOnly,Category = "Effect|Splines")
	float mSplineDelayOffset = -0.2;

	UPROPERTY(EditDefaultsOnly,Category = "Effect|Sound")
	float mThumbSoundPlayTime = 1.f;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UClass*> mSplineClasses;

	/* Cached bounds of all meshes in the build effect actor. */
    UPROPERTY(BlueprintReadOnly)
    FBox mBounds;

	UPROPERTY(BlueprintReadOnly)
	FBox mActorBounds;

	/*Array of spline ordered by connectivity.*/
	UPROPERTY()
	TArray<class USplineComponent*> mOrganizedSplines;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> mSlicePlane;

private:

	/* Did the default buildables finish building? */
	bool mDidCallFinished;
	
	/* Did the spline based buildables finish building?*/
	bool mDidCallSplineFinished;
	
	/* Did the thumb sound play? */
	bool mDidPlayThumbSound;

	bool mDidStartSplineEffect;
	
	/* all default mesh components made for this build actor. */
	UPROPERTY()
	TArray<UMeshComponent*> mMeshComponents;

	/* Meshes that are displayed used to determine zoop dir.*/
	UPROPERTY()
	TArray<UMeshComponent*> mMainMeshes;

	/* all spline mesh components made for this build actor. */
	UPROPERTY()
	TArray<UMeshComponent*> mSplineBuildableComponents;
	
	/* Total cost of the buildables, used to determine the throw queue.*/
	UPROPERTY(  )
	TArray< FItemAmount > mCost;
	
	/* Actor applying build effect on, resolved at create visuals and not used after it anymore. */
	TArray< TWeakObjectPtr< AActor > > mSourceActors;

	/* Number of items spawned times 0.1 as an estimation on default. */
	float mTotalThrowDuration;
	
	/* Volume of the object */
	float mVolume;
	
	/* current percentage for default build effect sequence*/
	float mPercentage = 0;

	/* current percentage for spline build effect sequence*/
	float mSplinePercentage = 0;

	/* Max number of parts we can toss. */
	UPROPERTY( EditDefaultsOnly )
	int32 mMaxNumParts;

	/* Time stamp when the first item reached the buildable, at this point we start raising the building. */
	float mFirstItemReachedTargetTime = 0;
	
	float cachedTotalSplineLength;
	
	UPROPERTY()
	TArray<TSubclassOf<UFGItemDescriptor>> mThrowQueue;

	// TODO CB have a solution for lightweight actors.
	// TODO CB make use of this.
	/* Used to determine which mesh components need to be removed when we dismantle an entry before finishing the effect */
	TMap<AActor*,TArray<UMeshComponent*>> mActorToComponentsMap;

	TMap<uint32,TArray<UMeshComponent*>> mHashToInstanceArrayMap;
	//TMap<UClass*,TArray<int32>> mClassToIndexToComponentMap;
	//TArray<TArray<UMeshComponent*>> mLightweightInternalIdToMeshComponents;
	
	// TODO CB for spline effects.
	TMap<AActor*,TArray<UMeshComponent*>> mActorToSplineComponentMap;

	// Bounds based on zoop axis.
	FVector BuildDirectionMin;
	FVector BuildDirectionMax;

	/* Frame the actor was spawned, used as an id to figure out if we can append to an existing build effect actor or should we spawn a new one
	 * used when Requesting a build effect actor from the buildable subsystem */
	uint64 mSpawnedFrame;

	/* Used to determine build direction.*/
	int32 NumActors = 0;

	FVector mPivots[4];
	
	/* Should play as a traditional building vertical only.*/
	UPROPERTY( EditDefaultsOnly, Category="Build style", DisplayName = "ForceVerticalMode")
	bool mIsBlueprint = false;
	
	bool bCanPlaneBeVisible = true;

	bool bPendingSelfDestroy = false;
};