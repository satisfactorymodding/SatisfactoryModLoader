// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

/*	TODO cleanup this rushed class, we most likely wanna split splines & normal buildables.
 * 
 */

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Actor.h"
#include "FGBuildEffectActor.generated.h"

class UMeshComponent;
struct FInstanceData;
class UFGRecipe;
struct FItemAmount;
class UFGItemDescriptor;

class AFGBuildable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FBuildEffectEnded );

UCLASS()
class FACTORYGAME_API AFGBuildEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGBuildEffectActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateVisuals();
	TArray<UMeshComponent*> CreateStaticMesh( UMeshComponent* SourceComponent, const FTransform& sourceActorTransform );
	void SetupThrowQueue();
	void SetRecipe( TSubclassOf<UFGRecipe> inRecipe, AFGBuildable* buildable );
	void SetIsSpline( bool IsASpline ) { mIsSpline = IsASpline; }
	float GetTotalSplineLength() const;

	UFUNCTION( BlueprintCallable, Category = "BuildEffectActor" )
	FTransform GetTransformOnSplines( bool bWorldSpace ) const;

	FBuildEffectEnded& GetBind( UClass* actorClass );

	void UpdateCostQueue();

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

	UFUNCTION(BlueprintPure)
	bool GetDidStartSplineEffect() const { return mDidStartSplineEffect; }

	UFUNCTION(BlueprintPure)
	float GetVolume() const { return mVolume; }
	
	// TODO move this bs to CPP too.
	UFUNCTION(BlueprintCallable)
	void OnCostActorReachedTarget();

	void Start();
	void Stop();

	void UpdateSplineBuildables(float Dt);
	void UpdateGenericBuildables(float Dt);
	void UpdateWires();

	void CalculateBuildEffectBounds();

	FORCEINLINE void SetActor( AActor* InSourceActor )
	{
		mSourceActors.Add(InSourceActor);
	}
	
	FORCEINLINE void SetActors( TArray<AActor*> InSourceActors )
	{
		for (const auto actor : InSourceActors)
		{
			mSourceActors.Add(actor);
		}
	}

private:

	TArray<class USplineComponent*> GetBeltSourceSplinesOrdered( const TArray<class AFGBuildableConveyorBelt*>& inBelts, TArray<AActor*>& orderedActors ) const;
	TArray<class USplineComponent*> GetPipeSourceSplineOrdered( const TArray<class AFGBuildablePipeBase*>& inPipes, TArray<AActor*>& orderedActors ) const;

public:
	/* Called before it start fading out */
	FBuildEffectEnded OnBuildEffectFinished;

	/* Called when the fade out on the spline based components starts to happen. */
	FBuildEffectEnded OnSplineBuildEffectFinished;
	
protected:
	/* The key value is the material that needs be replaced with the value, in case of the masked material
	 * on factory buildings we want to apply the mask on those to, otherwise it looks like a slice of cheese
	 * or some butter */
	UPROPERTY(EditDefaultsOnly)
	TMap<UMaterialInterface*,UMaterialInterface*> mMaterialSwapMap;
	
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

	/*Array of spline ordered by connectivity.*/
	UPROPERTY()
	TArray<class USplineComponent*> mOrganizedSplines;
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

	/* all spline mesh components made for this build actor. */
	UPROPERTY()
	TArray<UMeshComponent*> mSplineBuildableComponents;
	
	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mBuildEffectMaterial;

	UPROPERTY( EditDefaultsOnly )
	UMaterialInterface* mBuildEffectSplineMaterial;

	// TODO can be moved into scope.
	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> mBuildEffectMaterialInstance;
	
	UPROPERTY(  )
	TArray< FItemAmount > mCost;
	
	/* Actor applying build effect on. */
	TArray< TWeakObjectPtr< AActor > > mSourceActors;

	/* Number of items spawned times 0.1 as an estimation on default. */
	float mTotalThrowDuration;
	
	/* Volume of the object */
	float mVolume;
	
	/* current percentage for default build effect sequence*/
	float mPercentage = 0;

	/* current percentage for spline build effect sequence*/
	float mSplinePercentage = 0;

	UPROPERTY( EditDefaultsOnly )
	bool mIsSpline = false;
	
	UPROPERTY( EditDefaultsOnly )
	int32 mMaxNumParts;

	/*Time stamp when the first item reached the buildable, at this point we start raising the building.*/
	float mFirstItemReachedTargetTime = 0;

	/* total number of pipe segments, used for the build effect.*/
	int32 mNumBeltSegments = 0;

	float cachedTotalSplineLength;
	
	UPROPERTY()
	TArray<TSubclassOf<UFGItemDescriptor>> mThrowQueue;

	TMap<AActor*,TArray<UMeshComponent*>> mActorToComponentsMap;
};