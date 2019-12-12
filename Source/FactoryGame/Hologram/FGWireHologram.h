// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGBuildableHologram.h"
#include "../FGCircuitConnectionComponent.h"
#include "Components/MeshComponent.h"
#include "FGWireHologram.generated.h"

#define NUM_CONNECTIONS 2

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
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin AFGHologram Interface
	virtual AActor* Construct( TArray< AActor* >& out_children ) override;
	virtual TArray< FItemAmount > GetCost( bool includeChildren ) const override;
	virtual bool MultiStepPlacement() override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void OnInvalidHitResult() override;
	virtual void SpawnChildren( class UFGBuildGunStateBuild* state ) override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void OnAutomaticPoleDisableToggle( bool disabled );

	virtual void Destroyed() override;

	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	virtual void SetupDepthMeshComponent( USceneComponent* attachParent, UMeshComponent* componentTemplate ) override;
	virtual void CheckClearance() override;
	// End AFGHologram Interface

private:
	void CheckValidSnap();
	void CheckLength();

	/**
	 * Check for nearby connectors.
	 * @return Closest connection, with or without free connections left.
	 */
	class UFGCircuitConnectionComponent* FindOverlappingCircuitConnectionComponent( const FVector& location, class AActor* actor, class UFGCircuitConnectionComponent* ignoredConnectionComponent );

	void StartLookAtBuilding( UFGCircuitConnectionComponent* overlappingComponent );
	void StopLookAtBuilding();

	void StartLookAtTooManyConnectionsBuilding( UFGCircuitConnectionComponent* overlappingConnection );

	float GetLength() const;

private:
	float mMaxLength;
	float mLengthPerCost;

	/** The two connection components we connect. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mConnections[ NUM_CONNECTIONS ];

	UPROPERTY( Replicated )
	class AFGPowerPoleHologram* mPowerPole;

	UPROPERTY( EditDefaultsOnly, Category = "Power pole" )
	TSubclassOf<class UFGRecipe> mDefaultPowerPoleRecipe;

	/** The start location of this wire */
	UPROPERTY( Replicated )
	FVector mStartLocation;

	/** Keeps track of what connection we are working with */
	UPROPERTY()
	int32 mCurrentConnection;

	/** The mesh we should stretch */
	UPROPERTY()
	UStaticMeshComponent* mWireMesh;
};
