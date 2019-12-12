// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableTrainPlatform.h"
#include "../FGRailroadInterface.h"
#include "FGBuildableFactory.h"
#include "../Replication/FGReplicationDetailInventoryComponent.h"
#include "../Replication/FGReplicationDetailActor_CargoPlatform.h"
#include "FGBuildableTrainPlatformCargo.generated.h"

/**
 *	Train Platform with inputs and outputs that can both load and unload train freight carts. Must be attached to another platform or station
 */
UCLASS()
class FACTORYGAME_API AFGBuildableTrainPlatformCargo : public AFGBuildableTrainPlatform, public IFGRailroadInterface
{
	GENERATED_BODY()
	
public:
	//ctor
	AFGBuildableTrainPlatformCargo();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	/** Get the inventory the docked vehicle loads/unloads to  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trains|CargoPlatform" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const{ return mCargoInventoryHandler->GetActiveInventoryComponent(); }

	/** Get the docked actor if any. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trains|CargoPlatform" )
	FORCEINLINE class AFGRailroadVehicle* GetDockedActor() const{ return mDockedRailroadVehicle; }

	/** Dock an actor to this docking station. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Trains|CargoPlatform" )
	virtual bool Dock( class AFGRailroadVehicle* actor );

	/** Undock the docked actor. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Trains|CargoPlatform" )
	virtual void Undock();

	/** Set whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Trains|CargoPlatform" )
	virtual void SetIsInLoadMode( bool isInLoadMode );

	/** Get whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trains|CargoPlatform" )
	virtual bool GetIsInLoadMode() const;

	/** Get whether this station is currently loading or unloading from vehicles */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trains|CargoPlatform" )
	virtual bool IsLoadUnloading() const;

	/** Get the docked vehicles offset from the center of the platform */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trains|CargoPlatform" )
	float GetDockedVehicleOffset() const;

	/** Notify for when unload and/or load transfers are completed */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|CargoPlatform" )
	void OnTransferComplete();

	// ****** Start of Progress Events - Use to trigger animations and attachments from blueprint ******* /
	/** Called when raising the crane from the platform to send to cart */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|CargoPlatform" )
	void OnBeginLoadSequence();

	/** Called when sending the crane from the platform to the cart*/
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|CargoPlatform" )
	void OnBeginUnloadSequence();
	// ***** End of Progress Events *****//

	// Begin IFGRailroadInterface
	virtual void RegisteredOnTrack_Implementation( const FRailroadTrackPosition& position ) override;
	virtual void UnregisteredFromTrack_Implementation() override;
	virtual FRailroadTrackPosition GetTrackPosition_Implementation() const override;
	virtual int32 GetTrackGraphID_Implementation() const override;
	// End IFGRailroadInterface

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGReplicationDetailActor_CargoPlatform::StaticClass(); };
	// End IFGReplicationDetailActorOwnerInterface

	// Begin BuildableTrainPlatform Implementation
	virtual bool ShouldRegisterOnTrack() override;
	virtual void NotifyTrainDocked( class AFGRailroadVehicle* railroadVehicle, class AFGBuildableRailroadStation* initiatedByStation ) override;
	virtual void UpdateDockingSequence() override;
	// End BuildableTrainPlatform Implementation

	/** Sets the hidden power connection from the child track assigned to this platform */
	void UpdatePowerConnectionFromTrack();

protected:
	friend class AFGReplicationDetailActor_CargoPlatform;

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

	// Handle Inventory component replication via DetailActor
	virtual void OnRep_ReplicationDetailActor() override;

	// Handle Custom docking update behaviour for clients
	virtual void OnRep_UpdateDockingStatus() override;

private:

	/**
	* @todo: Move to InventoryComponent, make const
	* Returns the first slot index that has any items on it
	* If nothing exists in inventory -1 is returned
	*/
	int32 GetFirstIndexWithItem( UFGInventoryComponent* inventory );

	// Loads all possible inventory from the platform inventory into the freight inventory
	void Factory_TransferInventoryToTrain();

	// Transfers all possible inventory from the train cart into the platform inventory
	void Factory_TransferInventoryToPlatform();

	/** Done loading or unloading vehicle */
	void LoadUnloadVehicleComplete();

	/** Check if we are able to fit the contents of the frieght cart into the platforms inventory */
	void CheckCanPerformFullUnload();

	/** Check if we are able to fit the contents of the frieght cart into the platforms inventory */
	void CheckCanPerformFullLoad();

	/** Swap the visibility on the load / unload cargo container component during load / unload sequences */
	void SwapCargoContainerVisibility();

	/** Explicitly hide the cargo container for the platform (called from a next tick timer to allow the anim blueprint to catch up) */
	void HidePlatformCargoContainer();
	/** Explicitly show the cargo container for the platform (called from a next tick timer to allow the anim blueprint to catch up) */
	void ShowPlatformCargoContainer();

	// Called when power state changes. Used to track and set docking progress so that it can recover when power is restored
	UFUNCTION()
	void OnCargoPowerStateChanged( bool hasPower );

	class AFGReplicationDetailActor_CargoPlatform* GetCastRepDetailsActor() const { return Cast<AFGReplicationDetailActor_CargoPlatform>( mReplicationDetailActor ); };

public:
	/** Name of the magic box skel mesh comp added via BP */
	static FName mMagicBoxComponentName;
	/** Name of the cargo static mesh comp added via BP */
	static FName mCargoMeshComponentName;

protected:
	/** SizeX of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	int8 mStorageSizeX;

	/** SizeY of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	int8 mStorageSizeY;

	/** Magic box skeletal mesh component. Plays load / unload animations during partial load / unload sequences */
	UPROPERTY()
	class USkeletalMeshComponent* mMagicBoxSkelMeshComponent;

	/** Cargo container mesh component. Shown / Hidden during full load and unload sequences */
	UPROPERTY()
	class UStaticMeshComponent* mCargoMeshComponent;

	/** Maintainer of the active storage component for this actor. Use this to get the active inventory component. Never call mInventory directly. */
	class UFGReplicationDetailInventoryComponent* mCargoInventoryHandler;

	/** Indicates that the unloading sequence will be removing the entire contents of the freight car (there is enough room in its inventory to fit the freight cars contents) */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	bool mIsFullUnload;

	/** Indicates that the loading sequence will load an entire new container onto the freight car (its inventory is empty) */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	bool mIsFullLoad;

	/** Time in seconds to complete a unload */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	float mTimeToCompleteLoad;

	/** Time in seconds to show the cargo container and hide platform container (for full loads)*/
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	float mTimeToSwapLoadVisibility;

	/** Time in seconds to complete a load */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	float mTimeToCompleteUnload;

	/** Time in seconds to show freight container and hide platform container (for full unloads) */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Trains|CargoPlatform" )
	float mTimeToSwapUnloadVisibility;

	/** All connections that can pull to data to our storage, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mStorageInputConnections;

private:
	/** Inventory where we transfer items to when unloading from a vehicle. Never reference this pointer directly. Use mCargoInventoryHandler->GetActiveInventory(). */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInventory;

	/** If an actor is docked to this station. Used to detect actor becomes invalid due to e.g. dismantle. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true ) )
	uint8 mHasDockedActor : 1;

	/** Have the player specified that this station should either load or unload to vehicles? */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	bool mIsInLoadMode;

	/** Are we currently in the process of loading or unloading inventory  @todoTrainPlatforms - Migrate this out and replace instances with checks against the status enum */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	bool mIsLoadUnloading;

	/** Set when Docking sequence completes to inform Factory_TickProducing it should perform a load / unload */
	UPROPERTY( SaveGame )
	bool mShouldExecuteLoadOrUnload;

	/** Set during a docking sequence update to toggle the visibility of the platform and freight cargo meshes*/
	UPROPERTY()
	FTimerHandle mSwapCargoVisibilityTimerHandle;

	/** Set during a power outtage to store how much time remains on the current timer if a docking sequence is in progress */
	float mCachedDockingTimeRemaining;

	/** Set during a power outtage to store how much time remains on the toggle platform and freight cargo meshes */
	float mCachedSwapCargoVisibilityTimeRemaining;

	/** Where on the track is this platform is located. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true ) )
	FRailroadTrackPosition mTrackPosition;
	
};
