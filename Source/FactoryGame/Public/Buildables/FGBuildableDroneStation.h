// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Buildables/FGBuildableFactory.h"

#include "FGDroneVehicle.h"

#include "FGDroneStationInfo.h"

#include "Replication/FGReplicationDetailActor_DroneStation.h"
#include "FGBuildableDroneStation.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogDroneStation, Log, All );

UENUM( BlueprintType )
enum class EItemTransferringStage : uint8
{
	ITS_NONE		UMETA(displayName = "None"),
	
	ITS_UNLOAD		UMETA(displayName = "Unload"),
	ITS_LOAD		UMETA(displayName = "Load")
};

UENUM( BlueprintType )
enum class EItemTransferTickResult : uint8
{
	ITTR_DONE		UMETA(displayName = "Done"),
	
    ITTR_PARTIAL	UMETA(displayName = "Partial"),
    ITTR_FAILED		UMETA(displayName = "Failed")
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableDroneStation : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	AFGBuildableDroneStation();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

	//~ Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInferface
	
	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGReplicationDetailActor_DroneStation::StaticClass(); };
	virtual void OnReplicationDetailActorRemoved() override;
	// End IFGReplicationDetailActorOwnerInterface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	virtual void StartIsLookedAtForSnapping( class AFGCharacterPlayer* byCharacter, bool IsValidSnap );
	virtual void StopIsLookedAtForSnapping( class AFGCharacterPlayer* byCharacter );

	void Undock( bool Immediate = false );

	/** If successful, returns 0 if docking is approved right away, otherwise returns position in queue. */
	UFUNCTION( BlueprintCallable, Category = "Drone Station" )
	int32 RequestDocking( class AFGDroneVehicle* DroneToDock );

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    EItemTransferringStage GetItemTransferringStage() const { return mItemTransferringStage; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    bool IsTransferringItems() const { return mItemTransferringStage != EItemTransferringStage::ITS_NONE; }

	void SetStationDrone( class AFGDroneVehicle* Drone );

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	bool HasDronesInQueue() const { return mStationHasDronesInQueue; }
	
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    class AFGDroneVehicle* GetStationDrone() const { return mStationDrone; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    class AFGDroneVehicle* GetDockedDrone() const { return mDockedDrone; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	FVector GetDroneDockingStartLocation() const;

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    FVector GetDroneDockingLocation() const;

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	float GetDroneQueueRadius() const { return mDroneQueueRadius; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    float GetDroneQueueVerticalSeparation() const { return mDroneQueueVerticalSeparation; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    float GetDroneQueueSeparationRadius() const { return mDroneQueueSeparationRadius; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    int32 GetTripInformationSampleCount() const { return mTripInformationSampleCount; }
	
	/** Get the inventory that the docked drone unloads into */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	class UFGInventoryComponent* GetInputInventory() const { return mInputInventoryHandler->GetActiveInventoryComponent(); }

	/** Get the inventory that the docked drone loads from */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	class UFGInventoryComponent* GetOutputInventory() const { return mOutputInventoryHandler->GetActiveInventoryComponent(); }

	/** Get the inventory that the docked drone loads from */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	class UFGInventoryComponent* GetBatteryInventory() const { return mBatteryInventoryHandler->GetActiveInventoryComponent(); }

	/** @returns the info that is always present on both client and server */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    AFGDroneStationInfo* GetInfo() const { return mInfo; }

	void EnsureInfoCreated();

public:
	/** Called when the drone changes docking state. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnDockingStateChanged( EDroneDockingState NewState, float TimeSinceChanged );

	/** Called when the drone changes from having no drone in the queue to having at least one, or vice versa. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnStationHasDroneQueueUpdated( bool StationHasDroneQueue );
	
	/** Called when a drone starts its docking sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
    void StartDockingSequence( class AFGDroneVehicle* Drone );

	/** Called when a drone ends its docking sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
	void EndDockingSequence( class AFGDroneVehicle* Drone, bool ShouldTransferItems );
	
	/** Called when a drone starts its takeoff sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
    void StartTakeoffSequence( class AFGDroneVehicle* Drone );

	/** Called when a drone ends its takeoff sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
	void EndTakeoffSequence( class AFGDroneVehicle* Drone );

protected:	
	virtual void OnRep_ReplicationDetailActor() override;

	class AFGReplicationDetailActor_DroneStation* GetCastRepDetailsActor() const;

	UFUNCTION()
    bool FilterBatteryClasses( TSubclassOf< UObject > object, int32 idx ) const;

	bool IsValidFuel( TSubclassOf< class UFGItemDescriptor > resource ) const;
	
private:
	UFUNCTION()
	void OnRep_ItemTransferringStage();

	UFUNCTION()
    void OnRep_StationHasDronesInQueue();

	void SetItemTransferringStage( EItemTransferringStage NewStage );
	
    void BeginItemTransfer();
	void EndItemTransfer();

	/** One tick of item transferring. Returns true when done transferring. */
	EItemTransferTickResult ItemTransferTick( class UFGInventoryComponent* FromInventory, class UFGInventoryComponent* ToInventory, bool MustTransferEverything );
	
private:
	friend class AFGReplicationDetailActor_DroneStation;
	friend class AFGDroneStationInfo;
	friend class AFGDroneSubsystem;

	/** All connection components tagged with this is considered battery components */
	static FName sBatteriesTag;
	
	/** Where the drones should fly to before starting docking procedure. Local Space. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	FVector mDroneDockingStartLocationLocal;

	/** Where the drone is positioned when docked to the station. Local Space. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	FVector mDroneDockingLocationLocal;
	
	/** Class of the drone actor to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	TSubclassOf<class AFGDroneVehicle> mDroneClass;

	/** Valid Battery item class */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	TArray<TSubclassOf<UFGItemDescriptor>> mBatteryClasses;

	/** Item class used for calculating energy costs in batteries. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	TSubclassOf<UFGItemDescriptor> mUIBatteryCostItemClass;
	
	/** Drones waiting to dock. */
	UPROPERTY( SaveGame )
	TArray<class AFGDroneVehicle*> mDroneDockingQueue;

	/** Whether or not the station has drones in queue. */
	UPROPERTY( ReplicatedUsing=OnRep_StationHasDronesInQueue )
	bool mStationHasDronesInQueue;

	UPROPERTY( SaveGame )
	/** The most recent drone to dock. Gets cleared after traveling a certain distance away. */
	class AFGDroneVehicle* mRecentlyDockedDrone;

	/** Whether we are in the process of transferring items, and what stage. */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ItemTransferringStage )
	EItemTransferringStage mItemTransferringStage;

	/** Current progress on transfer from/to docking station ( in seconds ) */
	UPROPERTY()
	float mTransferProgress;

	/** How long time it takes to transfer one stack of item from/to docking station ( in seconds ) */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mTransferSpeed;

	/** How much of a stack to transfer in each separate transfer moment */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mStackTransferSize;

	/** How far away drones circle the station when in queue. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mDroneQueueRadius;

	/** How far away drones seperate outward when in queue. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mDroneQueueSeparationRadius;
	
	/** How far away drones seperate vertically when in queue. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mDroneQueueVerticalSeparation;

	/** Base cost of a launching a drone on a trip. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mTripPowerCost;
	
	/** How much power every meter of travel costs between this station and another. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mTripPowerPerMeterCost;

	/** We store this many of the station drone's latest trip for statistics. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int32 mTripInformationSampleCount;
	
	/** The drone belonging to this station. */
	UPROPERTY( Replicated, SaveGame )
	class AFGDroneVehicle* mStationDrone;

	/** The currently docked drone. */
	UPROPERTY( Replicated, SaveGame )
	class AFGDroneVehicle* mDockedDrone;

	/** SizeX of input and output inventories */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mStorageSizeX;

	/** SizeY of input and output inventories */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mStorageSizeY;

	/** SizeX of battery inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mBatteryStorageSizeX;

	/** SizeY of battery inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mBatteryStorageSizeY;
	
	UPROPERTY()
	class UFGReplicationDetailInventoryComponent* mInputInventoryHandler;
	
	UPROPERTY()
	class UFGReplicationDetailInventoryComponent* mOutputInventoryHandler;
	
	UPROPERTY()
	class UFGReplicationDetailInventoryComponent* mBatteryInventoryHandler;

	/** Inventory where we transfer items from when loading a drone.  */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInputInventory;

	/** Inventory where we transfer items to when unloading from a drone.  */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;
	
	/** Inventory where batteries are stored. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mBatteryInventory;

	/** All connections that can pull to data to our storage, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mStorageInputConnections;
	
	UPROPERTY( SaveGame, Replicated )
	AFGDroneStationInfo* mInfo;
};
