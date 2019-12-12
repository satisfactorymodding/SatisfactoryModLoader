// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
#include "FGBuildableDockingStation.generated.h"

/**
 * Base class for docking stations in the game, this is a load/unload station depending on the conveyor connections given.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableDockingStation : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableDockingStation();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	/** @return a valid pointer to the fuel inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetFuelInventory() const{ return mFuelInventory; }

	/** Get the inventory the docked vehicle loads/unloads to  */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const{ return mInventory; }

	/** Get the docked actor if any. */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	FORCEINLINE class AActor* GetDockedActor() const{ return mDockedActor; }

	/** Dock an actor to this docking station. */
	UFUNCTION( BlueprintCallable, Category = "DockingStation" )
	virtual bool Dock( class AActor* actor );

	/** Undock the docked actor. */
	UFUNCTION( BlueprintCallable, Category = "DockingStation" )
	virtual void Undock();

	/** Set whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintCallable, Category = "DockingStation" )
	virtual void SetIsInLoadMode( bool isInLoadMode );

	/** Get whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	virtual bool GetIsInLoadMode() const;

	/** Get whether this station is currently loading or unloading from vehicles */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	virtual bool IsLoadUnloading() const;

	/** Notify for when unload and/or load transfers are completed */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	void OnTransferComplete();

	/** Called when we start unloading the vehicle */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	void OnBeginUnloadVehicle();

	/** Called when we start loading the vehicle */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	void OnBeginLoadVehicle();

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

	/** Set up the fuel inventory when replicated */
	UFUNCTION()
	void OnRep_FuelInventory();

	/**
	 * Check if a resource is valid as fuel for this station.
	 *
	 * @todo: Move this out to a BPFunctionLibrary. It's used on several places, and seems useful
	 *
	 * @param resource - Resource class to check.
	 * @return - true if resource valid as fuel; false if not valid or if generator does not run on fuel.
	 */
	bool IsValidFuel( TSubclassOf< class UFGItemDescriptor > resource ) const;

	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;
private:
	/**
	 * @todo: Move to InventoryComponent, make const
	 * Returns the first slot index that has any items on it
	 * If nothing exists in inventory -1 is returned
	 */
	int32 GetFirstIndexWithItem( UFGInventoryComponent* inventory );


	/** Loads fuel into the docked vehicles inventory.
	 * @return true if we are done refueling (i.e. vehicle fuel inventory is full or we have no fuel to transfer)
	 */
	bool Factory_LoadFuel( UFGInventoryComponent* dockedFuelInventory, float percentOfStack );

	/** Unloads one slot from the station to the docked inventory. */
	void Factory_LoadDockedInventory( UFGInventoryComponent* dockedInventory );

	/** Unloads one slot from the docked inventory to the station. */
	void Factory_UnloadDockedInventory( UFGInventoryComponent* dockedInventory );

	/** Done loading or unloading vehicle */
	void LoadUnloadVehicleComplete();

protected:
	/** All connection components tagged with this is considered fuel components */
	static FName sFuelTag;

	/** SizeX of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	int8 mStorageSizeX;

	/** SizeY of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	int8 mStorageSizeY;

	/** How long time it takes to transfer one stack of item from/to docking station ( in seconds ) */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	float mTransferSpeed;

	/** How long time it takes to transfer 1 stack of fuel from/to docking station ( in seconds ) */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	float mFuelTransferSpeed;

	/** Current progress on transfer from/to docking station ( in seconds ) */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	float mTransferProgress;

	/** Inventory where we transfer items to when unloading from a vehicle  */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInventory;

	/** Inventory for refueling the trucks. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_FuelInventory )
	class UFGInventoryComponent* mFuelInventory;

	/** All connections that can pull in fuel to the docking station, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mFuelConnections;

	/** All connections that can pull to data to our storage, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mStorageInputConnections;

	/** The actor docked to this station. */
	UPROPERTY( SaveGame )
	class AActor* mDockedActor;

	/** If an actor is docked to this station. Used to detect actor becomes invalid due to e.g. dismantle. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson = true) )
	uint8 mHasDockedActor:1;

	/** Have the player specified that this station should either load or unload to vehicles? */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	bool mIsInLoadMode;

	/** How much of a stack to transfer in each separate transfer moment */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	float mStackTransferSize;

	/** Are we currently in the process of loading or unloading inventory */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	bool mIsLoadUnloading;
};
