// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGBuildableDockingStation.generated.h"

USTRUCT( BlueprintType )
struct FDockingVehicleStatistics
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	float mTimeSinceLastDocking = 0.0f;

	/**
	 * The weighted average of time between station docks.
	 * The weights are (beginning with latest): 1/2, 1/4, 1/8, 1/16...
	 */
	UPROPERTY( SaveGame )
	float mWeightedAverageTimeBetweenDocks = 0.0f;

	/**
	 * The weighted average of number of items per station dock.
	 * The weights are (beginning with latest): 1/2, 1/4, 1/8, 1/16...
	 */
	UPROPERTY( SaveGame )
	float mWeightedAverageItemsTransferred = 0.0f;
};

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
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFSaveInterface
	
	//Begin IFGSignificanceInterface
	virtual float GetSignificanceRange() override;
	//End IFGSignificanceInterface

	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	class AFGDockingStationInfo* GetInfo() const { return mInfo; }

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
	virtual bool DockActor( class AActor* actor );

	/** Undock the docked actor. */
	UFUNCTION( BlueprintCallable, Category = "DockingStation" )
	virtual void Undock( bool notifyDockedActor );

	/** Set whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintCallable, Category = "DockingStation" )
	virtual void SetIsInLoadMode( bool isInLoadMode );

	/** Get whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	virtual bool GetIsInLoadMode() const;

	/** Get whether this station is currently loading or unloading from vehicles */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	virtual bool IsLoadUnloading() const;

	void SetVehicleFuelConsumptionRate( float vehicleFuelConsumptionRate );

	/** Get the combined fuel per second for all vehicles that dock to this station, in the fuel type last supplied by the station */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	float GetVehicleFuelConsumptionRate() const { return mVehicleFuelConsumptionRate; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FVehicleFuelConsumptionRateChanged );
	/** Broadcast when the fuel-consumption rate (per second) of the vehicles has changed */
	UPROPERTY( BlueprintAssignable, Category = "DockingStation", DisplayName = "OnVehicleFuelConsumptionRateChanged" )
	FVehicleFuelConsumptionRateChanged VehicleFuelConsumptionRateChangedDelegate;

	void SetItemTransferRate( float itemTransferRate );

	/** Get the combined average items per second for all vehicles that dock to this station */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	float GetItemTransferRate() const { return mItemTransferRate; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FItemTransferRateChanged );
	/** Broadcast when the average item-transfer rate (per second) of the vehicles has changed */
	UPROPERTY( BlueprintAssignable, Category = "DockingStation", DisplayName = "OnItemTransferRateChanged" )
	FItemTransferRateChanged ItemTransferRateChangedDelegate;

	void SetMaximumStackTransferRate( float maximumItemTransferRate );

	/** Get the combined max stacks per second for all vehicles that dock to this station */
	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	float GetMaximumStackTransferRate() const { return mMaximumStackTransferRate; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FMaximumStackTransferRateChanged );
	/** Broadcast when the maximum item-transfer rate (per second) of the vehicles has changed */
	UPROPERTY( BlueprintAssignable, Category = "DockingStation", DisplayName = "OnMaximumStackTransferRateChanged" )
	FMaximumStackTransferRateChanged MaximumStackTransferRateChangedDelegate;

	/** Returns the zone in which a vehicle is considered docked */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	UBoxComponent* FindDockArea();

	/** Notify for when unload and/or load transfers are completed */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	void OnTransferComplete();

	/** Called when we start unloading the vehicle */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	void OnBeginUnloadVehicle();

	/** Called when we start loading the vehicle */
	UFUNCTION( BlueprintImplementableEvent, Category = "DockingStation" )
	void OnBeginLoadVehicle();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	UMaterialInterface* GetDefaultCompassMaterial();

	FVector GetWorldDockPosition() const;

	void FindStationTargets( TArray< class AFGTargetPoint* >& targets );
	void UpdateVehicleTargets( bool lifecycleStart );
	void CleanUpStationVehicleTargets();
	void AddDockingVehicle( class AFGWheeledVehicle* vehicle );
	void RemoveDockingVehicle( class AFGWheeledVehicle* vehicle );
	void UpdateVehicleFuelConsumptionRate();
	void UpdateMaximumStackTransferRate();
	void UpdateItemTransferRate();

	UFUNCTION( BlueprintPure, Category = "DockingStation" )
	int GetDockingVehicleCount() const { return mDockingVehicles.Num(); }

	bool CanBeRefuelingVehicle( AFGWheeledVehicle* vehicle ) const;
	void SetRefuelingVehicle( AFGWheeledVehicle* vehicle );

	bool HasSufficientFuelType() const;

	virtual void PreSerializedToBlueprint() override;
	virtual void PostSerializedToBlueprint() override;
	virtual void PostSerializedFromBlueprint( bool isBlueprintWorld ) override;
	
protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

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
	void EnsureInfoCreated();

	/** Loads fuel into the docked vehicles inventory.
	 * @return true if we are done refueling (i.e. vehicle fuel inventory is full or we have no fuel to transfer)
	 */
	bool Factory_LoadFuel( AFGWheeledVehicle* vehicle, float percentOfStack, bool conserveFuel );

	/** Unloads one slot from the station to the docked inventory. */
	void Factory_LoadDockedInventory( UFGInventoryComponent* dockedInventory );

	/** Unloads one slot from the docked inventory to the station. */
	void Factory_UnloadDockedInventory( UFGInventoryComponent* dockedInventory );

	/** Done loading or unloading vehicle */
	void LoadUnloadVehicleComplete();

	UFUNCTION()
	void OnDockingAreaBeginOverlap( UPrimitiveComponent* thisComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool isFromSweep, const FHitResult& sweepResult );

	UFUNCTION()
	void OnDockingAreaEndOverlap( UPrimitiveComponent* thisComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex );

	UFUNCTION()
	void OnRep_VehicleFuelConsumptionRate();

	UFUNCTION()
	void OnRep_ItemTransferRate();

	UFUNCTION()
	void OnRep_MaximumStackTransferRate();

public:
	/** Where the vehicle should place itself, the extended position of the crane */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	FVector2D mDockPosition;
	
	/**
	 * The minimum time from when the vehicle enters a station until it leaves that station
	 * Should match the docking animation time
	 */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	float mMinimumDockingTime = 10.0f;

	/** The zone in which a vehicle is considered docked */
	UPROPERTY( Transient )
	UBoxComponent* mDockArea;

	float mMaxTargetPointZ = -BIG_NUMBER;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;
	
protected:
	/** All connection components tagged with this is considered fuel components */
	static FName sFuelTag;

	/** SizeX of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	int8 mStorageSizeX;

	/** SizeY of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	int8 mStorageSizeY;

	/** SizeX of fuel inventory */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	int8 mFuelInventorySizeX;

	/** SizeY of fuel inventory */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	int8 mFuelInventorySizeY;
	
	/** How long time it takes to transfer one stack of item from/to docking station ( in seconds ) */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	float mTransferSpeed;

	/** How long time it takes to transfer 1 stack of fuel from/to docking station ( in seconds ) */
	UPROPERTY( EditDefaultsOnly, Category = "DockingStation" )
	float mFuelTransferSpeed;

	/** Current progress on transfer from/to docking station ( in seconds ) */
	UPROPERTY( Meta = ( NoAutoJson = true, FGReplicated ) )
	float mTransferProgress;
	
	/** All connections that can pull in fuel to the docking station, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mFuelConnections;

	/** All connections that can pull to data to our storage, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mStorageInputConnections;

	/** The actor docked to this station. */
	UPROPERTY( SaveGame )
	class AActor* mDockedActor;

	/** A non-automated vehicle currently receiving fuel from the station. */
	TWeakObjectPtr< class AFGWheeledVehicle > mRefuelingVehicle;

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

private:
	UPROPERTY( Replicated, SaveGame )
	class AFGDockingStationInfo* mInfo;

	/** Used to hold a reference to the mInfo during blueprint serialization. Holds a reference to mInfo which is nulled during blueprint serialization */
	UPROPERTY()
	class AFGDockingStationInfo* mTempInfo;

	/** Inventory where we transfer items to when unloading from a vehicle  */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInventory;

	/** Inventory for refueling the trucks. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mFuelInventory;

	UPROPERTY( Replicated )
	bool mForceSignificance = false;

	UPROPERTY( ReplicatedUsing = OnRep_VehicleFuelConsumptionRate )
	float mVehicleFuelConsumptionRate = 0.0;

	UPROPERTY( ReplicatedUsing = OnRep_ItemTransferRate )
	float mItemTransferRate = 0.0f;

	UPROPERTY( ReplicatedUsing = OnRep_MaximumStackTransferRate )
	float mMaximumStackTransferRate = 0;

	UPROPERTY( SaveGame )
	TMap< class AFGWheeledVehicle*, FDockingVehicleStatistics > mDockingVehicleStatistics;

	/**
	 * A list of all vehicle that may be docking to this station while self driving
	 */
	TSet< class AFGWheeledVehicle* > mDockingVehicles;

	TSubclassOf< class UFGItemDescriptor > mCurrentFuelType;

	float mLastTransferItemCount = 0.0f;
};
