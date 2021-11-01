// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGSplineHologram.h"
#include "Components/SplineComponent.h"
#include "FGFactoryConnectionComponent.h"
#include "FGConveyorBeltHologram.generated.h"

/**
 * Hologram for the conveyor belts, contains all the curve bending magic.
 */
UCLASS()
class FACTORYGAME_API AFGConveyorBeltHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	AFGConveyorBeltHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual void OnInvalidHitResult() override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void AdjustForGround( FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	virtual void PreHologramPlacement() override;
	virtual void PostHologramPlacement() override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void Scroll( int32 delta ) override;
	virtual void GetSupportedScrollModes( TArray<EHologramScrollMode>* out_modes ) const override;
	virtual float GetHologramHoverHeight() const override;
	// End AFGHologram Interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void ClientPreConstructMessageSerialization() override;
	virtual void ServerPostConstructMessageDeserialization() override;
	// End FGConstructionMessageInterface

	/** Get the active connections direction, may be any. */
	EFactoryConnectionDirection GetActiveConnectionDirection() const;

	/** Returns any AFGBuildables that the ConveyorBeltHologram are currently snapping to */
	TArray<AFGBuildable*> GetAnyConnectedBuildables();

protected:
	// Begin AFGBuildableHologram Interface
	virtual void CheckValidFloor() override;
	virtual void CheckValidPlacement() override;
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

	// Begin AFGHologram interface
	virtual void CheckClearance( const FVector& locationOffset ) override;
	// End AFGHologram interface

	/** Creates the clearance detector used with conveyor belts */
	void SetupConveyorClearanceDetector();

private:
	// Begin FGSplineHologram
	virtual void UpdateSplineComponent() override;
	// End FGSplineHologram

	/** Create connection arrow component on the client. */
	UFUNCTION()
	void OnRep_ConnectionArrowComponentDirection();

	/**
	 * This routes the spline to the new location. Inserting bends and straights.
	 */
	void AutoRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

	bool ValidateIncline();
	bool ValidateMinLength();

private:
	bool mUsingCutstomPoleRotation = false;

	/**Used to redirect input and construct poles when needed*/
	UPROPERTY( Replicated )
	class AFGConveyorPoleHologram* mChildPoleHologram = nullptr;

	/** The two connection components for this conveyor. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mConnectionComponents[ 2 ];

	/** The connections we've made. */
	UPROPERTY( CustomSerialization )
	class UFGFactoryConnectionComponent* mSnappedConnectionComponents[ 2 ];


	/** If we upgrade another conveyor belt this is the belt we replaces. */
	UPROPERTY()
	class AFGBuildableConveyorBelt* mUpgradedConveyorBelt;

	/** Class of conveyor pole to place at the end. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	TSubclassOf< class UFGRecipe > mDefaultConveyorPoleRecipe;

	/** What radius will the bends have. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mBendRadius;

	/** Maximum length that can be built. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mMaxSplineLength = 5600.1f;

	/** What is the maximum incline of the conveyor belt (degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mMaxIncline;

	/** Used to replicate the direction arrow. */
	UPROPERTY( ReplicatedUsing = OnRep_ConnectionArrowComponentDirection )
	EFactoryConnectionDirection mConnectionArrowComponentDirection;

	/** Arrow to indicate the direction of the conveyor while placing it. */
	UPROPERTY()
	class UStaticMeshComponent* mConnectionArrowComponent;

	UPROPERTY( CustomSerialization )
	FVector mConstructionPoleLocations[ 2 ];

	UPROPERTY(CustomSerialization)
	FRotator mConstructionPoleRotations[ 2 ];

	/** All the generated spline meshes. */
	UPROPERTY()
	TArray< class USplineMeshComponent* > mSplineMeshes;

	/** All the generated collision meshes. */
	UPROPERTY()
	TArray< class UShapeComponent* > mCollisionMeshes;

	/** Cached from the default buildable. */
	UPROPERTY()
	class UStaticMesh* mMesh;
	float mMeshLength;
};
