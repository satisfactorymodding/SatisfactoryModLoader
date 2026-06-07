// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGFactoryHologram.h"
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
	virtual void PreConfigureActor(AFGBuildable* inBuildable) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
protected:
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void OnHologramTransformUpdated() override;
	// End AFGHologram interface

	/** Called by the blueprint once the main mesh has been loaded and initialized. Used to spawn factory legs */
	UFUNCTION( BlueprintCallable, Category = "Trading Post Hologram" )
	void ConfigureMainMeshComponent( UStaticMeshComponent* MainMeshComponent );
private:
	/** The generator holograms */
	UPROPERTY( Replicated )
	TObjectPtr<class AFGFactoryHologram> mGeneratorHolograms[ 2 ];

	/** The storage hologram */
	UPROPERTY( Replicated )
	TObjectPtr<class AFGBuildableHologram> mStorageHologram;

	/** The hub terminal holograms */
	UPROPERTY( Replicated )
	TObjectPtr<class AFGBuildableHologram> mHubTerminalHologram;

	/** The work bench holograms */
	UPROPERTY( Replicated )
	TObjectPtr<class AFGBuildableHologram> mWorkBenchHologram;

	/** Array of components matching the location where generators are placed */
	UPROPERTY()
	TArray< TObjectPtr<USceneComponent> > mGeneratorLocations;

	/** component matching the location where the storage is placed */
	UPROPERTY()
	TObjectPtr<USceneComponent> mStorageLocation;

	/** component matching the location where the hub terminal is placed */
	UPROPERTY()
	TObjectPtr<USceneComponent> mHubTerminalLocation;

	/** component matching the location where the work bench is placed */
	UPROPERTY()
	TObjectPtr<USceneComponent> mWorkBenchLocation;
};
