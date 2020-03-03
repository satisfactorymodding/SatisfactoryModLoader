// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGVehicle.h"
#include "FGUseableInterface.h"
#include "FGPipeBuilder.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSplineSupportPair
{
	GENERATED_BODY()

	/** What recipe to use for the spline support */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	TSubclassOf< class UFGRecipe > SplineSupportRecipeClass;

	/** What recipe to use for the spline */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	TSubclassOf< class UFGRecipe > SplineRecipeClass;

public:
	FORCEINLINE ~FSplineSupportPair() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPipeBuilder : public AFGVehicle
{
	GENERATED_BODY()
public:	
	AFGPipeBuilder();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInterface

	/** Initiate a build on aimed location */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void OnPrimaryFirePressed(); 

	/** Sets up spline and support actor so that a spline can be built from location */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void SetupSplineAndSupport();

	/** Clears spline and support hologram so we can move freely instead */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void ClearSplineAndSupport();

	/** Initiate a move to aimed location */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void OnSecondaryFirePressed();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SecondaryFire();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_UpdateHitResult( FHitResult inHitResult );

	/** Returns the trail actor associated with this pipe builder */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|PipeBuilder" )
	FORCEINLINE	class AFGPipeBuilderTrail* GetTrail() { return mTrail; }

	/** Returns the pipe support location */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|PipeBuilder" )
	FORCEINLINE USceneComponent* GetPipeSupportLocation() { return mPipeSupportLocation; }

	/** Returns the recipeIndex */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|PipeBuilder" )
	FORCEINLINE int32 GetRecipeIndex() { return mRecipeIndex; }

	/** Sets if holograms should be active */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void SetHologramsActive( bool isActive );

	/** Sets new Recipe index */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void SetRecipeFromIndex( int32 newIndex );

	/** Do we have all holograms set up and ready to build? */
	bool IsReadyToBuild();

	/** Removes old holograms and spawns new ones */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilder" )
	void SpawnHolograms();
protected:
	/** Handles movement of the pipe builder */
	void TickMove( float dt );

protected:
	/** The main skeletal mesh associated with this Vehicle */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "FactoryGame|PipeBuilder", meta = (AllowPrivateAccess = "true") )
	class UFloatingPawnMovement* mMovementComponent;

	/** The human readable name for this vehicle. */
	//UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	//FText mDisplayName;

	/** Component used to determine generators location */
	UPROPERTY( EditAnywhere )
	USceneComponent* mPipeSupportLocation;
private:
	/** The hologram to build. */
	UPROPERTY( Replicated )
	class AFGSplineHologram* mSplineHologram;

	/** Hologra of pipe support that indicates where to build the pipe to */
	UPROPERTY( Replicated )
	class AFGPipelineSupportHologram* mSupportHologram;

	/** What recipe to use for the pipe support */
	UPROPERTY(  )
	TSubclassOf< class UFGRecipe > mCurrentSplineSupportRecipeClass;

	/** What recipe to use for the spline */
	UPROPERTY(  )
	TSubclassOf< class UFGRecipe > mCurrentSplineRecipeClass;

	/** The pipe support that the pipe is built from */
	UPROPERTY( Replicated )
	class AFGBuildablePipelineSupport* mInternalSplineSupport;

	/** Result of the latest trace. */
	UPROPERTY()
	FHitResult mHitResult;

	/** Do we want to perform movement */
	bool mDoMovement;

	/** Start point for movement of the pipe builder */
	FVector mStartLocation; 

	/** End point for movement of the pipe builder */
	FVector mEndLocation;

	/** Alpha value used when interpolating between start and end point for movement */
	float mLocationAlpha;

	/** How long time the movement should take in seconds */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	float mMoveTime;

	/** Curve used for height offset when moving */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	UCurveFloat* mHeightCurve;

	/** Class of what trail to use */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	TSubclassOf< class AFGPipeBuilderTrail > mTrailClass;

	/** Cached reference to the trail actor */
	UPROPERTY( Replicated )
	class AFGPipeBuilderTrail* mTrail;

	/** Array with what spline based recipes can be built and their corresponding supports */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	TArray< FSplineSupportPair > mSplineAndSupportData;

	/** Current index indicating what recipe is selected */
	int32 mRecipeIndex;

	/** Are spline and support holograms set up correctly */
	bool mIsSplineAndSupportSetup;
public:
	/** What distance to keep between trail and pipe builder */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "FactoryGame|PipeBuilder" )
	float mTrailDistance;


public:
	FORCEINLINE ~AFGPipeBuilder() = default;
};
