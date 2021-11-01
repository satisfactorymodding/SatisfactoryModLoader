// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "ItemAmount.h"
#include "FGActorRepresentationInterface.h"
#include "FGBuildableSpaceElevator.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSpaceElevator : public AFGBuildableFactory, public IFGActorRepresentationInterface
{
	GENERATED_BODY()

public:	
	AFGBuildableSpaceElevator();

	//replication
	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const;

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText( const FText& newText ) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	// End IFGActorRepresentationInterface
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInferface

	//~ Begin AFGBuildable interface
	virtual bool CanBeSampled_Implementation() const{ return false; }
	//~ End AFGBuildable interface

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

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

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

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

};
