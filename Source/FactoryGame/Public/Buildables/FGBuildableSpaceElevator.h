// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "../ItemAmount.h"
#include "FGBuildableSpaceElevator.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSpaceElevator : public AFGBuildableFactory
{
	GENERATED_BODY()

public:	
	AFGBuildableSpaceElevator();

	//replication
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const;
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInferface

	// Begin AFGBuildableFactory interface
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_Tick( float dt ) override;
	// End AFGBuildableFactory interface

	//@returns true when we are fully upgraded.
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	bool IsFullyUpgraded();

	/** Returns the cost for the next upgrade */
	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void GetNextPhaseCost( TArray< FItemAmount >& out_cost );

	/** Player has dropped items onto the pay off widget from their inventory*/
	UFUNCTION( BlueprintCallable, Category = "Space Elevator" )
	void PayOffFromInventory( UFGInventoryComponent* inventory, int32 inventorySlotIndex );

	/* *@returns True if we have eaten up all the items needed to upgrade. Returns false if not, but also if there is no current recipe available. */
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	bool IsReadyToUpgrade();

	/** Get the input inventory from this building.	*/
	UFUNCTION( BlueprintPure, Category = "Space Elevator" )
	FORCEINLINE class UFGInventoryComponent* GetInputInventory() { return mInputInventory; }

	/** Called when the player presses to send more stuff to the tow truck */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Space Elevator" )
	void UpgradeTowTruck();

	/** When the player is on the last step of the game, sending the tow truck will end the game */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Space Elevator" )
	void LaunchTowTruck();

protected:

	/** Returns the game phase manager, finds it if it isn't cached */
	class AFGGamePhaseManager* GetGamePhaseManager();

private:
	/*
	* Checks and consumes any ingredient in the input inventory if the upgrade recipe requires it.
	*/
	void ConsumeInputIngredientsIfNecessary();
	
protected:
	/** Our input inventory, shared for all input connections. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInputInventory;

	/** A cached version of the game phase manager */
	UPROPERTY()
	AFGGamePhaseManager* mGamePhaseManager;

	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray< class UFGFactoryConnectionComponent* > mInputConnections;
};
