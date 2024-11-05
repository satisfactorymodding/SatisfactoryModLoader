// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGTrainPlatformHologram.generated.h"

/**
 *	Base Hologram class for constructing train platform buildings (Stations, Cargo, Empty etc.) as they all require a child RailroadTrack hologram
 */
UCLASS()
class FACTORYGAME_API AFGTrainPlatformHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	AFGTrainPlatformHologram();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin Actor Interface
	virtual void BeginPlay() override;
	// End Actor Interface

	// Begin AFGHologram interface
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual void PreConfigureActor( class AFGBuildable* inBuildable ) override;
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual int32 GetRotationStep() const override;
	virtual void OnHologramTransformUpdated() override;
	// End AFGHologram interface

	void SnapToConnection( class UFGTrainPlatformConnection* connection );
	
	/** Check for platform connections to snap to */
	class UFGTrainPlatformConnection* FindOverlappingConnectionComponent( const FVector& location, float actorOverlapRadius, float toleranceRadius, bool ignoreSelf, bool ignoreIsConnected ) const;

protected:
	/** Overrides floor snapping and forces platforms to only snap to other platforms (not true for stations, true for other platforms) */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mRequireSnapToPlatform;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	TSubclassOf< class UFGRecipe > mRailroadTrackRecipe;

	/** The Railroad hologram */
	UPROPERTY( Replicated )
	class AFGRailroadTrackHologram* mRailroadTrackHologram;

	/** The components of this hologram used for detecting platform snapping */
	UPROPERTY()
	class UFGTrainPlatformConnection* mPlatformConnectionComponents[ 2 ]; 

	/** Stores a reference to the other platforms this hologram is connecting to */
	UPROPERTY( CustomSerialization )
	class UFGTrainPlatformConnection* mConnectedPlatformComponents[ 2 ];

private:
	/** radius to allow snapping to occur*/
	float mSnapDistance;

	/** radius to check for potential actors (platforms) containing connection components */
	float mActorOverlapCheckRadius;

	/** Track whether this platform is flipped, is only assigned to snapped buildings */
	bool mIsOrientationReversed;
};
