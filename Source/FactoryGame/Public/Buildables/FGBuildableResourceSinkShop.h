// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableResourceSinkShop.generated.h"

/**
 * Building where you can buy schematics with coupons
 */
UCLASS()
class FACTORYGAME_API AFGBuildableResourceSinkShop : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	AFGBuildableResourceSinkShop();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Rep detail actor interface. At present this building doesn't utilize its detail actor and thus needs to override the locking behaviour on its inv comp
	virtual void OnReplicationDetailActorCreated() override;
	virtual void OnReplicationDetailActorRemoved() override;

	/** Get the inventory that holds the purchases we made in the resource sink shop */
	UFUNCTION( BlueprintPure, Category = "Resource Sink Shop" )
	FORCEINLINE class UFGInventoryComponent* GetShopInventory() const { return mShopInventory; }

	/** Can the inventory fit the items that are received when purchasing the given schematics */
	UFUNCTION( BlueprintPure, Category = "Resource Sink Shop" )
	bool CanInventoryFitPlannedPurchase( TArray< TSubclassOf< class UFGSchematic > > schematics ) const;

	/** Purchase the given schematics. If any of the schematics give items they are placed in the shop inventory 
	*	return true if we could afford all given schematics and non of them are already purchased
	*/
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Resource Sink Shop" )
	bool PurchaseResourceSinkSchematics( class UFGInventoryComponent* playerInventory, TArray< TSubclassOf< class UFGSchematic > > schematics );

private:
	/** The inventory that holds the purchases we made in the resource sink shop */
	UPROPERTY( VisibleDefaultsOnly, SaveGame, Replicated, Category = "Resource Sink Shop" )
	class UFGInventoryComponent* mShopInventory;

	/** The size of the inventory that holds the purchases we made in the resource sink shop */
	UPROPERTY( EditDefaultsOnly, Category = "Resource Sink Shop" )
	int32 mShopInventoryDefaultSize;

	/** Cached resource sink subsystem */
	UPROPERTY( Transient )
	class AFGResourceSinkSubsystem* mResourceSinkSubsystem;

};
