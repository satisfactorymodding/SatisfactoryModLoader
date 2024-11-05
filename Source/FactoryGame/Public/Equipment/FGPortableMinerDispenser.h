// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGEquipment.h"
#include "GameFramework/Actor.h"
#include "Resources/FGItemDescriptor.h"
#include "FGPortableMinerDispenser.generated.h"

/**
 * TODO: Refactor alongside FGGolfCartDispenser into an "AFGEquipment_ActorSpawner" base class.
 */
UCLASS()
class FACTORYGAME_API AFGPortableMinerDispenser : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGPortableMinerDispenser();

	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	// End AActor interface

	// Begin AFGEquipment interface
	virtual void UnEquip() override;
	// End AFGEquipment interface

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;

	bool TraceForPortableMinerPlacementLocation( FVector& out_Location ) const;
	bool IsResourceNodeValid( const AFGResourceNode* resourceNode ) const;

	/** Actually spawns the resource miner */
	UFUNCTION( Server, Reliable )
	void Server_SpawnPortableMiner( const FVector& location, AFGResourceNode* resourceNode );

	/** Updates the hologram location locally and also sends a multicast to update it for everyone else */
	void UpdateHologramLocation( const FVector& location, bool isValidPlacement, bool isVisible );
	
	UFUNCTION( Server, Unreliable )
	void Server_UpdateHologramLocation( const FVector& location, bool isValidPlacement, bool isVisible );

	UFUNCTION( NetMulticast, Unreliable )
	void Multicast_UpdateHologramLocation( const FVector& location, bool isValidPlacement, bool isVisible );

	/** Updates location of the hologram locally */
	void Local_UpdateHologramLocation( const FVector& location, bool isValidPlacement, bool isVisible ) const;
	
protected:
	/** Component used for visualizing the portable miner hologram */
	UPROPERTY( EditAnywhere, Category = "Portable Miner" )
	USkeletalMeshComponent* mHologramMeshComponent;

	/** Class of the portable miner to spawn into the world */
	UPROPERTY( EditDefaultsOnly, Category = "Portable Miner" )
	TSubclassOf<class AFGPortableMiner> mPortableMinerClass;
	
	/** What form can the overlapping resources be in. */
	UPROPERTY( EditDefaultsOnly, Category = "Portable Miner" )
	TArray< EResourceForm > mAllowedResourceForms;
};
