// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableWire.h"
#include "FGBuildableHologram.h"
#include "FGCircuitConnectionComponent.h"
#include "FGPowerConnectionComponent.h"
#include "FGWireHologram.generated.h"

/**
 * Hologram for placing wires between circuit connections.
 */
UCLASS()
class FACTORYGAME_API AFGWireHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGWireHologram();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram Interface
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void OnInvalidHitResult() override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual void CheckBlueprintCommingling() override;
	virtual float GetBuildGunRangeOverride_Implementation() const override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	virtual bool CanNudgeHologram() const override;
	virtual AFGHologram* GetNudgeHologramTarget() override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const override;
	// End AFGBuildableHologram Interface

	void SetConnection( int32 ix, UFGCircuitConnectionComponent* connection );
	UFGCircuitConnectionComponent* GetConnection( int32 ix ) const;

	UFUNCTION(BlueprintPure, Category = "Power Pole")
	class AFGBuildableHologram* GetActiveAutomaticPoleHologram() const { return mActivePoleHologram; }

	// Whether or not the wire is connected to two power towers
	UFUNCTION( BlueprintPure, Category = "Power Pole")
	bool IsPowerTowerWire() const;

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void OnAutomaticPoleDisableToggle( bool disabled );

	virtual void Destroyed() override;

	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	virtual void CheckClearance( const FVector& locationOffset ) override;
	virtual uint8 GetStencilForHologramMaterialState( EHologramMaterialState state ) const override;
	// End AFGHologram Interface

private:
	void CheckValidSnap();
	void CheckLength();

	void SetActiveAutomaticPoleHologram( class AFGBuildableHologram* poleHologram );

	UStaticMeshComponent* CreateNewWireMesh();

	void UpdateWireMeshes();

	/**
	 * Check for connections near a point on a given actor.
	 *
	 * @param location                     Location to search nearby.
	 * @param actor                        Actor to search for connections on.
	 * @param ignoredConnectionComponent   Connection to ignore when searching.
	 * @param compatibleCircuitType        Circuit type to look for, null is not compatible with anything.
	 * @param powerConnectionType          In case of power connections, what power connection type to look for.
	 *
	 * @return Closest connection, with or without free connections left.
	 */
	class UFGCircuitConnectionComponent* FindOverlappingCircuitConnectionComponent(
		const FVector& location,
		class AActor* actor,
		class UFGCircuitConnectionComponent* ignoredConnectionComponent,
		TSubclassOf< class UFGCircuit > compatibleCircuitType,
		EPowerConnectionType powerConnectionType );

	void StartLookAtBuilding( UFGCircuitConnectionComponent* overlappingComponent );
	void StopLookAtBuilding();

	void StartLookAtTooManyConnectionsBuilding( UFGCircuitConnectionComponent* overlappingConnection );

	float GetLength() const;

	void SetUpgradeTarget( AFGBuildableWire* target );

private:
	float mMaxLength;
	float mMaxPowerTowerLength;
	float mLengthPerCost;

	/** The two connection components we connect. */
	UPROPERTY( Replicated, CustomSerialization )
	class UFGCircuitConnectionComponent* mConnections[ 2 ];

	/** Automatically spawned child pole, can be null. */
	UPROPERTY( Replicated )
	class AFGPowerPoleHologram* mPowerPole;

	UPROPERTY( Replicated )
	class AFGPowerPoleWallHologram* mPowerPoleWall;

	UPROPERTY()
	class AFGBuildableHologram* mActivePoleHologram;

	UPROPERTY()
	class UFGCircuitConnectionComponent* mActiveSnapConnection;

	/** Recipe to use for the automatically spawned child pole, can be null. */
	UPROPERTY( EditDefaultsOnly, Category = "Power pole" )
	TSubclassOf< class UFGRecipe > mDefaultPowerPoleRecipe;

	/** Circuit types this wire can connect. */
	UPROPERTY()
	TSubclassOf< class UFGCircuit > mCircuitType;

	UPROPERTY( EditDefaultsOnly, Category = "Power pole" )
	TSubclassOf<class UFGRecipe> mDefaultPowerPoleWallRecipe;

	/** Whether or not it's possible to place automatic power poles on the wall. */
	bool mAutomaticWallPoleEnabled;

	/** Whenever we have completed the tutorial and have poles unlocked */
	bool mAutomaticPoleAvailable;

	/** The start location of this wire */
	UPROPERTY( Replicated )
	FVector mStartLocation;

	/** Keeps track of what connection we are working with */
	UPROPERTY( Replicated, CustomSerialization )
	int32 mCurrentConnection;

	UPROPERTY()
	TArray< FWireInstance > mWireInstances;

	UPROPERTY()
	class AFGBuildableWire* mUpgradeTarget;
};
