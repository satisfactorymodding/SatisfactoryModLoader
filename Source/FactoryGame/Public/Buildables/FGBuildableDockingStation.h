// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildableFactory.h"
#include "FGBuildableDockingStation.generated.h"

class UBoxComponent;
class AFGDockingStationIdentifier;
class AFGVehiclePathNode;
class UFGPipeConnectionComponent;

USTRUCT()
struct FDockingStationVehicleTracking
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	TWeakObjectPtr<AActor> OwnerVehicle;

	UPROPERTY(SaveGame)
	int32 VehicleInventorySizeLinear{0};

	UPROPERTY(SaveGame)
	int32 VehicleFluidSlotCapacity{0};

	UPROPERTY(SaveGame)
	float TimeSinceLastDocking{0.0f};

	UPROPERTY(SaveGame)
	float AverageTimeBetweenDocks{0.0f};

	UPROPERTY(SaveGame)
	float AverageItemsTransferredPerDock{0.0f};

	UPROPERTY(SaveGame)
	bool bHasEverTransferredAnyItems{false};

	UPROPERTY(SaveGame)
	float AverageFuelConsumptionPerDock{0.0f};

	UPROPERTY(SaveGame)
	bool bHasEverBeenRefueled{false};
};

USTRUCT( BlueprintType )
struct FDockingStationTaggedFluidConnection
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "Docking Station Tagged Fluid Connection" )
	TObjectPtr<UFGPipeConnectionComponent> Connection;

	UPROPERTY( BlueprintReadWrite, Category = "Docking Station Tagged Fluid Connection" )
	int32 SlotIndex{0};
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

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_StopProducing() override;
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_PullPipeInput_Implementation(float dt) override;
	virtual void Factory_PushPipeOutput_Implementation(float dt) override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End AFGBuildableFactory interface

	// Begin IFGDismantleInterface
	virtual void GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const override;
	// End IFGDismantleInterface

	/** Returns the docking station identifier actor for this docking station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE AFGDockingStationIdentifier* GetStationIdentifier() const { return mStationIdentifier; }

	/** Returns the docking target node owned by this docking station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE AFGVehiclePathNode* GetDockingPathNode() const { return mDockingPathNode; }

	/** @return a valid pointer to the fuel inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const{ return mFuelInventory; }

	/** Get the inventory the docked vehicle loads/unloads to  */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE UFGInventoryComponent* GetInventory() const{ return mInventory; }

	/** Get the docked actor if any. */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE AActor* GetDockedActor() const{ return mDockedActor; }

	/** Returns the resource form of this docking station. This determines whenever it is a fluid docking station or solid docking station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	EResourceForm GetDockingStationResourceForm() const;

	/** Dock an actor to this docking station. */
	UFUNCTION( BlueprintCallable, Category = "Docking Station" )
	virtual bool DockActor( class AActor* actor );

	/** Forcibly undocks the currently docked actor. This happens automatically once the docking sequence is complete */
	UFUNCTION( BlueprintCallable, Category = "Docking Station" )
	virtual void ForceUndockActor();

	/** Set whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintCallable, Category = "Docking Station" )
	virtual void SetIsInLoadMode( bool isInLoadMode );

	/** Get whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	virtual bool GetIsInLoadMode() const;

	/** Sets whenever vehicle fuel type should be forcefully swapped by this docking station */
	UFUNCTION( BlueprintCallable, Category = "Docking Station" )
	virtual void SetForceVehicleFuelType( bool isForceVehicleFuelType );

	/** Gets whenever vehicle fuel type is being forcefully swapped by this docking station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE bool GetIsForceVehicleFuelType() const { return mForceVehicleFuelType; }

	/** Get whether this station is currently loading or unloading from vehicles */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	virtual bool IsLoadUnloading() const;

	void SetVehicleFuelConsumptionRate( float vehicleFuelConsumptionRate );

	/** Get the combined fuel per second for all vehicles that dock to this station, in the fuel type last supplied by the station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	float GetVehicleFuelConsumptionRate() const { return mVehicleFuelConsumptionRate; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FVehicleFuelConsumptionRateChanged );
	/** Broadcast when the fuel-consumption rate (per second) of the vehicles has changed */
	UPROPERTY( BlueprintAssignable, Category = "Docking Station", DisplayName = "OnVehicleFuelConsumptionRateChanged" )
	FVehicleFuelConsumptionRateChanged VehicleFuelConsumptionRateChangedDelegate;

	void SetItemTransferRate( float itemTransferRate );

	/** Get the combined average items per second for all vehicles that dock to this station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE float GetItemTransferRate() const { return mItemTransferRate; }

	/** Returns the current progress of the load/unload cycle */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE float GetLoadUnloadCycleProgress() const { return mLoadUnloadCycleProgress; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FItemTransferRateChanged );
	/** Broadcast when the average item-transfer rate (per second) of the vehicles has changed */
	UPROPERTY( BlueprintAssignable, Category = "Docking Station", DisplayName = "OnItemTransferRateChanged" )
	FItemTransferRateChanged ItemTransferRateChangedDelegate;

	void SetMaximumStackTransferRate( float maximumItemTransferRate );

	/** Get the combined max stacks per second for all vehicles that dock to this station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	float GetMaximumStackTransferRate() const { return mMaximumStackTransferRate; }

	/** Returns the time it takes to complete a full loading/unloading cycle */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	FORCEINLINE float GetLoadUnloadCycleLength() const { return mLoadUnloadCycleLength; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FMaximumStackTransferRateChanged );

	/** Broadcast when the maximum item-transfer rate (per second) of the vehicles has changed */
	UPROPERTY( BlueprintAssignable, Category = "Docking Station", DisplayName = "OnMaximumStackTransferRateChanged" )
	FMaximumStackTransferRateChanged MaximumStackTransferRateChangedDelegate;

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	/** Returns the default compass material for the docking station representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	UMaterialInterface* GetDefaultCompassMaterial();

	virtual void PreSerializedToBlueprint() override;
	virtual void PostSerializedToBlueprint() override;
	virtual void PostSerializedFromBlueprint( bool isBlueprintWorld ) override;

	FORCEINLINE USceneComponent* GetDockingTargetNodeLocation() const { return mDockingTargetNodeLocation; }
	FORCEINLINE float GetDockingPathNodeElevationOffset() const { return mDockingPathNodeElevationOffset; }
	FORCEINLINE void SetDockingPathNodeElevationOffset( const float newElevationOffset ) { mDockingPathNodeElevationOffset = newElevationOffset; }
	void CheckCreateVehicleDockingNode();

	/** Returns the docking area box used for resolving legacy paths docking to stations */
	UFUNCTION(BlueprintImplementableEvent, Category = "Docking Station")
	UBoxComponent* FindLegacyDockArea();

	/** Returns the current fluid descriptor for the fluid truck docking station */
	UFUNCTION( BlueprintPure, Category = "Docking Station" )
	TSubclassOf<UFGItemDescriptor> GetCurrentFluidDescriptor() const { return mCurrentFluidDescriptor; }

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCurrentFluidDescriptorChanged );

	/** Broadcast when current fluid descriptor changes */
	UPROPERTY( BlueprintAssignable, Category = "Docking Station" )
	FOnCurrentFluidDescriptorChanged OnCurrentFluidDescriptorChanged;
protected:
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

	void CreateDockingStationIdentifier();
	void CreateVehicleDockingNode();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayDockingEffects( AActor* dockedActor );
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_StopDockingEffects();

	/** Called locally to start playing docking animation on the given actor. GetIsInLoadMode can be called to learn if it is loading or unloading */
	UFUNCTION( BlueprintImplementableEvent, Category = "Docking Station" )
	void PlayDockingEffects( AActor* dockedActor );
	/** Called locally to cancel an active docking animation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Docking Station" )
	void StopDockingEffects();

	/** Loads fuel into the docked vehicles inventory. */
	int32 Factory_LoadFuel( UFGInventoryComponent* fuelInventory ) const;
	/** Transfers items between source and target inventories for docking. Returns number of items transferred */
	int32 Factory_LoadUnloadDockedInventory( UFGInventoryComponent* dockedInventory ) const;
	/** Done loading or unloading vehicle */
	void Factory_LoadUnloadVehicleComplete( int32 numItemsTransferred, int32 numFuelItemsTransferred );
	/** Updates the currently used fuel type for this station from the inventory */
	void Factory_UpdateCurrentFuelType();

	// Fluid truck station related functionality
	TSubclassOf<UFGItemDescriptor> FetchCurrentFluidDescriptor() const;
	void UpdateBuildableDataOnMesh();

	/** Creates a new vehicle tracking for the given vehicle or returns an existing one */
	FDockingStationVehicleTracking* FindVehicleTracking( const AActor* dockedActor );
	/** Recalculated station statistics derived from the tracking information */
	void Factory_RecalculateDerivedStatistics();

	UFUNCTION()
	void OnRep_VehicleFuelConsumptionRate();
	UFUNCTION()
	void OnRep_ItemTransferRate();
	UFUNCTION()
	void OnRep_MaximumStackTransferRate();
	UFUNCTION()
	void OnRep_CurrentFluidType();
	UFUNCTION()
	void OnRep_DockingPathNode();
public:
	/** Actor representation texture for the docking station */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station|Representation" )
	TObjectPtr<UTexture2D> mActorRepresentationTexture;

protected:
	/** Location of the docking target node. This is the location the vehicles will park at */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station" )
	TObjectPtr<USceneComponent> mDockingTargetNodeLocation;

	/** Class for the docking target node */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station" )
	TSubclassOf<AFGVehiclePathNode> mDockingTargetNodeClass;
	
	/** Size of the storage inventory for the truck station */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station|Inventory" )
	int32 mStorageInventorySize{48};

	/** True if this is a fluid storage inventory, and as such only fluid trucks can be loaded/unloaded at this station */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station|Inventory" )
	bool mIsFluidStorageInventory{false};

	/** Size of the fuel inventory for the truck station */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station|Inventory" )
	int32 mFuelInventorySize{1};
	
	/** How long  does it take for one full cycle of loading or unloading to complete? (in seconds) */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station" )
	float mLoadUnloadCycleLength{10.0f};

	/** Current normalized progress of loading/unloading cycle */
	UPROPERTY( SaveGame, Replicated )
	float mLoadUnloadCycleProgress{0.0f};
	
	/** All connections that can pull in fuel to the docking station */
	UPROPERTY()
	TArray<TObjectPtr<UFGFactoryConnectionComponent>> mFuelConnections;

	/** All connections that can pull to data to our storage */
	UPROPERTY()
	TArray<TObjectPtr<UFGFactoryConnectionComponent>> mStorageInputConnections;

	/** Input connections for fluid docking station. Must be populated by the blueprint! */
	UPROPERTY( BlueprintReadWrite, Category = "Docking Station" )
	TArray<FDockingStationTaggedFluidConnection> mFluidInputConnections;

	/** Input connections for fluid docking station. Must be populated by the blueprint! */
	UPROPERTY( BlueprintReadWrite, Category = "Docking Station" )
	TArray<FDockingStationTaggedFluidConnection> mFluidOutputConnections;

	/** The actor docked to this station. */
	UPROPERTY( SaveGame )
	TObjectPtr<class AActor> mDockedActor;

	/** If an actor is docked to this station. Used to detect actor becomes invalid due to e.g. dismantle. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson = true) )
	uint8 mHasDockedActor:1;

	/** Have the player specified that this station should either load or unload to vehicles? */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	bool mIsInLoadMode{true};

	/** Are we currently in the process of loading or unloading inventory */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	bool mIsLoadUnloading{false};

	/** True if docking station should force the fuel type for the vehicle being docked. This will automatically discard the old fuel type */
	UPROPERTY( EditDefaultsOnly, SaveGame, Replicated, Category = "Docking Station" )
	bool mForceVehicleFuelType{true};

	/** How much individual vehicle dock weights for vehicle throughput statistics, 0.5 means that a single dock determines 50% of throughput, 0.2 means 20%, and so on */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station", meta = (UIMin = "0.1", UIMax = "1.0") )
	float mIndividualDockWeightForStatistics{0.5f};

	/** Amount of time, in seconds, after which the station will stop tracking a particular vehicle if it has not docked again in that amount of game time */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station" )
	float mStationForgetVehicleTimeout{1800.0f};

	/** Current fluid descriptor for the fluid docking station */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentFluidType )
	TSubclassOf<UFGItemDescriptor> mCurrentFluidDescriptor;

	/** Station identifier for the docking station */
	UPROPERTY( Replicated, SaveGame )
	TObjectPtr<AFGDockingStationIdentifier> mStationIdentifier;

	/** Path node used as a docking target for this docking station */
	UPROPERTY( ReplicatedUsing = OnRep_DockingPathNode, SaveGame )
	TObjectPtr<AFGVehiclePathNode> mDockingPathNode;

	UPROPERTY( SaveGame )
	float mDockingPathNodeElevationOffset{0.0f};

	/** Used to hold a reference to the mInfo during blueprint serialization. Holds a reference to mInfo which is nulled during blueprint serialization */
	UPROPERTY( Transient )
	TObjectPtr<AFGDockingStationIdentifier> mTempInfo;

	/** Inventory where we transfer items to when unloading from a vehicle  */
	UPROPERTY()
	TObjectPtr<UFGInventoryComponent> mInventory;

	/** Inventory for refueling the trucks. */
	UPROPERTY()
	TObjectPtr<UFGInventoryComponent> mFuelInventory;

	/** True if we are playing docking effects locally currently */
	bool mIsPlayingDockingEffects{false};

	UPROPERTY( ReplicatedUsing = OnRep_VehicleFuelConsumptionRate )
	float mVehicleFuelConsumptionRate = 0.0;

	UPROPERTY( ReplicatedUsing = OnRep_ItemTransferRate )
	float mItemTransferRate = 0.0f;

	UPROPERTY( ReplicatedUsing = OnRep_MaximumStackTransferRate )
	float mMaximumStackTransferRate = 0;

	TSubclassOf< class UFGItemDescriptor > mCurrentFuelType;

	UPROPERTY( SaveGame )
	TArray<FDockingStationVehicleTracking> mVehicleTracking;
};
