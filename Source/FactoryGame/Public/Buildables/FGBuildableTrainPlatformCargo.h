// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableTrainPlatform.h"
#include "FGFreightWagon.h"
#include "FGTrainDockingRules.h"
#include "FGBuildableTrainPlatformCargo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnItemTransferRateUpdated, int32, itemTransferRate );

/**
 * Train Platform with inputs and outputs that can both load and unload train freight carts. Must be attached to another platform or station
 */
UCLASS()
class FACTORYGAME_API AFGBuildableTrainPlatformCargo : public AFGBuildableTrainPlatform
{
	GENERATED_BODY()
	
public:
	AFGBuildableTrainPlatformCargo();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	virtual bool Factory_PeekOutput_Implementation( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const override;
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;

	/** Get the inventory the docked vehicle loads/unloads to  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const{ return mInventory; }

	/** Get the docked actor if any. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	FORCEINLINE class AFGRailroadVehicle* GetDockedActor() const{ return mDockedRailroadVehicle; }

	/** Dock an actor to this docking station. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|CargoPlatform" )
	virtual bool Dock( class AFGRailroadVehicle* actor );

	/** Undock the docked actor. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|CargoPlatform" )
	virtual void Undock();

	/** Set whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|CargoPlatform" )
	virtual void SetIsInLoadMode( bool isInLoadMode );

	/** Get whether this station should load or unload from vehicles */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	virtual bool GetIsInLoadMode() const;

	/** Get whether this station is currently loading or unloading from vehicles */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	virtual bool IsLoadUnloading() const;

	/** Get the docked vehicles offset from the center of the platform */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	float GetDockedVehicleOffset() const;

	/** Notify for when unload and/or load transfers are completed */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|CargoPlatform" )
	void OnTransferComplete();

	// ****** Start of Progress Events - Use to trigger animations and attachments from blueprint ******* /
	/** Called when raising the crane from the platform to send to cart */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|CargoPlatform" )
	void OnBeginLoadSequence();

	/** Called when sending the crane from the platform to the cart*/
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|CargoPlatform" )
	void OnBeginUnloadSequence();
	// ***** End of Progress Events *****//

	/** Get the smoothed Outflow rate in m^3/s. Only valid for Liquid Freight Platforms*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	float GetOutflowRate() const { return mReplicatedOutflowRate; }

	/** Get the smoothed Inflow rate in m^3/s. Only valid for Liquid Freight Platforms*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	float GetInflowRate() const { return mReplicatedInflowRate; }
	
	// Begin BuildableTrainPlatform Implementation
	virtual void NotifyTrainDocked( class AFGRailroadVehicle* railroadVehicle, class AFGBuildableRailroadStation* initiatedByStation ) override;
	virtual void UpdateDockingSequence() override;
	virtual void CancelDockingSequence() override;
	// End BuildableTrainPlatform Implementation

	/** Sets the hidden power connection from the child track assigned to this platform */
	void UpdatePowerConnectionFromTrack();

	/** Get mIsFullLoad */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	FORCEINLINE uint8 IsFullLoad() const{ return mIsFullLoad; }

	/** Get mIsFullUnload */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	FORCEINLINE uint8 IsFullUnload() const{ return mIsFullUnload; }

protected:

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_PullPipeInput_Implementation( float dt ) override;
	virtual void Factory_PushPipeOutput_Implementation( float dt ) override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

	// Begin FGBuildableTrainPlatform interface
	virtual void OnRep_UpdateDockingStatus() override;
	virtual void OnRep_DockedRailroadVehicle() override;
	// End FGBuildableTrainPlatform interface
	
private:
	/** Filter items that are not valid for this type of cargo platform */
	UFUNCTION()
	bool FilterResourceForms( TSubclassOf< UFGItemDescriptor > itemDesc, int32 idx ) const;

	/**
	* @todo: Move to InventoryComponent
	* Returns the first slot index that has any items on it
	* If nothing exists in inventory -1 is returned
	*/
	int32 GetFirstIndexWithItem( UFGInventoryComponent* inventory ) const;

	// Transfers the inventory from a source inventory to a target inventory
	void TransferInventory( UFGInventoryComponent* from, UFGInventoryComponent* to );

	/** Done loading or unloading vehicle */
	void LoadUnloadVehicleComplete();

	/** Evaluate the status of the freight inventory for use by docking rules */
	void EvaluateFreightInventoryStatus();

	/** Check if we are able to fit the contents of the frieght cart into the platforms inventory */
	void UpdateUnloadSettings();

	/** Check if we are able to fit the contents of the frieght cart into the platforms inventory */
	void UpdateLoadSettings();

	/*** Swap the visibility on the load / unload cargo container component during load / unload sequences */
	void SwapCargoContainerVisibility();

	/** Explicitly hide the cargo container for the platform (called from a next tick timer to allow the anim blueprint to catch up) */
	void HidePlatformCargoContainer();
	/** Explicitly show the cargo container for the platform (called from a next tick timer to allow the anim blueprint to catch up) */
	void ShowPlatformCargoContainer();

	/** Make sure the container we load on matches the trains color etc. */
	void MatchVisualsOfCargoContainerToTrain();

	/** Forces an update of the animation instance. Neccesary to get the anim instance to correctly transition states before going offline */
	void ForceUpdateAnimInstance();

	// Called when power state changes. Used to track and set docking progress so that it can recover when power is restored
	UFUNCTION()
	void OnCargoPowerStateChanged( bool hasPower );

	/** On each update of the docking sequence update and parse the rules set */
	void EvaluateRuleSet();

	/** Checks if the docking status can complete based on the rules set */
	bool CanCompleteDocking();

	/** Is Load or Unload blocked by ItemFilter NONE? Tex. If the train is in load mode and we have a UFGNoneDescriptor in the item filter rules, this returns true. */
	bool IsLoadUnloadBlockedByNoneFilter();

	/** Update the Incoming/Outgoing Item rates */
	void UpdateItemTransferRate( int32 numItemsTransfered );

	/** Get the transfer rate for the current load/unload mode */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|CargoPlatform" )
	float GetCurrentItemTransferRate();

	/** Can this station currently pull/push input (becomes disabled while docking anim is in progress) */
	FORCEINLINE bool ShouldLockIncomingOutgoing() const;
	
	UFUNCTION()
	void OnRep_SmoothedLoadRate();
	UFUNCTION()
	void OnRep_SmoothedUnloadRate();

public:
	/** Name of the magic box skel mesh comp added via BP */
	static FName mMagicBoxComponentName;
	/** Name of the cargo static mesh comp added via BP */
	static FName mCargoMeshComponentName;

	/** Delegate for UI to hookup to when the transfer rate is updated */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|CargoPlatform" )
	FOnItemTransferRateUpdated mOnTransferRateUpdated;

protected:
	/** The freight cargo type this platform can interface with ( conveyor vs. pipes ) */
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	EFreightCargoType mFreightCargoType;

	/** SizeX of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	int8 mStorageSizeX;

	/** SizeY of storage inventory */
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	int8 mStorageSizeY;

	/** Magic box skeletal mesh component. Plays load / unload animations during partial load / unload sequences */
	UPROPERTY()
	class USkeletalMeshComponent* mMagicBoxSkelMeshComponent;

	/** Cargo container mesh component. Shown / Hidden during full load and unload sequences */
	UPROPERTY()
	class UStaticMeshComponent* mCargoMeshComponent;

	/** Set during a dock sequence, indicating if any items can be moved from the train to the platform */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "FactoryGame|Railroad|CargoPlatform" )
	uint8 mCanUnloadAny : 1;
	
	/** Indicates that the unloading sequence will be removing the entire contents of the freight car (there is enough room in its inventory to fit the freight cars contents) */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "FactoryGame|Railroad|CargoPlatform" )
	uint8 mIsFullUnload : 1;

	/** Set during a load sequence, indicating if any items can be moved from the platform to the train */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "FactoryGame|Railroad|CargoPlatform" )
	uint8 mCanLoadAny : 1;

	/** Indicates that the loading sequence will load an entire new container onto the freight car (its inventory is empty) */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "FactoryGame|Railroad|CargoPlatform" )
	uint8 mIsFullLoad : 1;

	/** Is the freight inventory full? */
	uint8 mIsFreightFull : 1;

	/** Is the freight inventory empty? */
	uint8 mIsFreightEmpty : 1;

	/** Whether load or unload, can a transfer be done that is considered total (either fill the entire wagon or fully empty the wagon) */
	uint8 mCanDoTotalTransfer : 1;

	/** Ignore the fully load or unload rule when waiting to start. This is set when the timer is approaching its limit and we want to force a sequence to run */
	uint8 mIgnoreTotalTransferRequirement : 1;

	/** Was the transfer of any items blocked by the None rule. This is tracked so we can complete even though we may not have satisfied the other rules */
	uint8 mTransferBlockedByNoneFilter : 1;

	/** Time in seconds to complete a unload */
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	float mTimeToCompleteLoad;

	/** Time in seconds to show the cargo container and hide platform container (for full loads)*/
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	float mTimeToSwapLoadVisibility;

	/** Time in seconds to complete a load */
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	float mTimeToCompleteUnload;

	/** Time in seconds to show freight container and hide platform container (for full unloads) */
	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	float mTimeToSwapUnloadVisibility;

	UPROPERTY( EditDefaultsOnly, Category = "CargoPlatform" )
	float mWaitForConditionUpdatePeriod;

	/** All factory connections that can pull to our storage */
	UPROPERTY()
	TArray<class UFGFactoryConnectionComponent*> mStorageInputConnections;

	/** All pipe connections that can pull to our storage */
	UPROPERTY()
	TArray<class UFGPipeConnectionComponent*> mPipeInputConnections;

	/** All pipe connections that can push to pipelines from our storage */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent*> mPipeOutputConnections;

	/** The current docking rules set from a docked train */
	UPROPERTY()
	FTrainDockingRuleSet mDockingRuleSet;

	/** The current load filter (only load items of this type) */
	UPROPERTY()
	TArray< TSubclassOf< class UFGItemDescriptor > > mLoadItemFilter;
	
	/*** The Current Unload filter (only unload items of this type */
	UPROPERTY()
	TArray< TSubclassOf< class UFGItemDescriptor > > mUnloadItemFilter;

	/** Timer handle to track docking duration so that we don't need to register a tick function */
	FTimerHandle mDurationTimerHandle;

	UPROPERTY()
	bool mHasFullyLoadUnloadRule;

	UPROPERTY()
	float mDockForDuration;

	UPROPERTY()
	bool mMustDockForDuration;

	UPROPERTY()
	float mCurrentDockForDuration;

	UPROPERTY()
	bool mHasAnyRelevantStacksToMove;

	UPROPERTY()
	bool mAllowDepartureNoValidItemsToTransfer;

private:
	/** Inventory where we transfer items to when unloading from a vehicle. Never reference this pointer directly. Use mCargoInventoryHandler->GetActiveInventory(). */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInventory;

	/** If an actor is docked to this station. Used to detect actor becomes invalid due to e.g. dismantle. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true ) )
	uint8 mHasDockedActor : 1;

	/** Have the player specified that this station should either load or unload to vehicles? */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	uint8 mIsInLoadMode : 1;

	/** Are we currently in the process of loading or unloading inventory  @todoTrainPlatforms - Migrate this out and replace instances with checks against the status enum */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	uint8 mIsLoadUnloading : 1;

	/** Set when Docking sequence completes to inform Factory_TickProducing it should perform a load / unload */
	UPROPERTY( SaveGame )
	uint8 mShouldExecuteLoadOrUnload : 1;

	UPROPERTY()
	uint8 mRanCompleteBeforeNone : 1;

	UPROPERTY()
	class AFGFreightWagon* mLastDockedFreight;

	/** Set during a docking sequence update to toggle the visibility of the platform and freight cargo meshes*/
	UPROPERTY()
	FTimerHandle mSwapCargoVisibilityTimerHandle;

	/** Set during a power outtage to store how much time remains on the current timer if a docking sequence is in progress */
	float mCachedDockingTimeRemaining;

	/** Set during a power outtage to store how much time remains on the toggle platform and freight cargo meshes */
	float mCachedSwapCargoVisibilityTimeRemaining;

	//////////////////////////////////////////////////////////////////////////
	/// Begin Load/Unload Transfer rate properties

	UPROPERTY( SaveGame )
	float mTimeSinceLastLoadTransferUpdate;

	UPROPERTY( SaveGame )
	float mTimeSinceLastUnloadTransferUpdate;

	UPROPERTY( SaveGame, meta = ( FGReplicatedUsing = OnRep_SmoothedLoadRate ) )
	float mSmoothedLoadRate;

	UPROPERTY( SaveGame, meta = ( FGReplicatedUsing = OnRep_SmoothedUnloadRate ) )
	float mSmoothedUnloadRate;

	/// End Load/Unload Transfer rate properties
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/// Begin pipeflow params

	/** Last content value when updating flow rate */
	int32 mFluidPushedLastProducingTick;

	/** Last content value when updating flow rate */
	int32 mFluidPulledLastProducingTick;

	/** Current smoothed outflow rate */
	float mSmoothedOutflowRate;

	/** Current smoothed outflow rate */
	float mSmoothedInflowRate;

	/** How frequently to update flow rate ( both clients and server will use the replicated value in the UI )*/
	float mUpdateReplicatedFlowFrequency;

	/** How long since the last replicated flow assignment */
	float mTimeSinceLastFlowUpdate;

	/** Replicated smoothed outflow rate */
	UPROPERTY( meta = ( FGReplicated ) )
	float mReplicatedOutflowRate;

	/** Replicated smoothed inflow rate */
	UPROPERTY( meta = ( FGReplicated ) )
	float mReplicatedInflowRate;

	/// End pipeflow params
	//////////////////////////////////////////////////////////////////////////
};
