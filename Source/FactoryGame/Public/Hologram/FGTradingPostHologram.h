// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGTradingPostHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGTradingPostHologram : public AFGFactoryHologram
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
protected:
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;

	virtual void OnHologramTransformUpdated() override;

		// End AFGHologram interface

	// Moved GetBuildableClassFromRecipe to a static helper in AFGBuildable

private:
	/** The generator holograms */
	UPROPERTY( Replicated )
	class AFGFactoryHologram* mGeneratorHolograms[ 2 ];

	/** The storage hologram */
	UPROPERTY( Replicated )
	class AFGBuildableHologram* mStorageHologram;

	/** The hub terminal holograms */
	UPROPERTY( Replicated )
	class AFGBuildableHologram* mHubTerminalHologram;

	/** The work bench holograms */
	UPROPERTY( Replicated )
	class AFGBuildableHologram* mWorkBenchHologram;

	/** Array of components matching the location where generators are placed */
	UPROPERTY()
	TArray< USceneComponent* > mGeneratorLocations;

	/** component matching the location where the storage is placed */
	UPROPERTY()
	USceneComponent* mStorageLocation;

	/** component matching the location where the hub terminal is placed */
	UPROPERTY()
	USceneComponent* mHubTerminalLocation;

	/** component matching the location where the work bench is placed */
	UPROPERTY()
	USceneComponent* mWorkBenchLocation;
};
