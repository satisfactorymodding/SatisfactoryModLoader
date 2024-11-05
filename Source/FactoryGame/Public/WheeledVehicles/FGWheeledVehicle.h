// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGVehicle.h"
#include "FGSplinePathMovementComponent.h"
#include "FGVehicleSubsystem.h"
#include "FGWheeledVehicleMovementComponent.h"
#include "FGWheeledVehicle.generated.h"

DECLARE_STATS_GROUP( TEXT( "Wheeled vehicles" ), STATGROUP_WheeledVehicles, STATCAT_Advanced );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAutopilotEnabledChanged, bool, autopilotEnabled );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnVehiclePathVisibilityChanged, bool, pathVisibility );

extern TAutoConsoleVariable< int32 > CVarVehicleDebug;

class FDebugDisplayInfo;

UENUM( BlueprintType )
enum class ERecordingStatus : uint8
{
	RS_NoRecording = 0,
	RS_RecordingStarted,
	RS_CompletionPossible,
	RS_RecordingCompleted,
	RS_RecordingAborted
};

UENUM( BlueprintType )
enum class ETransferAnimationState : uint8
{
	TS_None,
	TS_Loading,
	TS_Unloading
};

UENUM( BlueprintType )
enum class EManualDockingState : uint8
{
	MDS_NoDocking,
	MDS_CanLoad,
	MDS_CanUnload
};

/**
 * This is our implementation of a wheeled vehicle, we want a base class FGVehicle that can be shared by wheeled vehicles, trains etc.
 * @see AWheeledVehicle
 */
UCLASS( abstract, config = Game, BlueprintType )
class FACTORYGAME_API AFGWheeledVehicle : public AFGVehicle
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	AFGWheeledVehicle();

	// Begin AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Destroyed() override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos) override;
	// End AActor interface

	// Begin ADriveablePawn interface
	virtual bool DriverEnter( AFGCharacterPlayer* driver ) override;
	virtual bool DriverLeave(bool keepDriving) override;
	virtual void Server_DriverLeave_Implementation() override;
	virtual void LeavesVehicle() override;
	virtual void SubmergedInWaterUpdated(bool newIsSubmerged) override;
	// End ADriveablePawn interface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin Customization Interface
	
	// End Customization Interface

	//~ Begin IFGDockableInterface
	virtual bool CanDock_Implementation( EDockStationType atStation ) const override;
	virtual UFGInventoryComponent* GetDockInventory_Implementation() const override;
	virtual UFGInventoryComponent* GetDockFuelInventory_Implementation() const override;
	virtual void WasDocked_Implementation( AFGBuildableDockingStation* atStation ) override;
	virtual void WasUndocked_Implementation() override;
	virtual void OnBeginLoadVehicle_Implementation() override;
	virtual void OnBeginUnloadVehicle_Implementation() override;
	virtual void OnTransferComplete_Implementation() override;
	//~ End IFGDockableInterface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFSaveInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	//~ End IFGUseableInterface

	UFUNCTION()
	void OnVehicleLanded();

	/** Add the bindings to vehicle and child-classes. */
	virtual void AddInputBindings( UInputComponent* enhancedInput ) override;

	UFUNCTION( Reliable, NetMulticast )
	virtual void Multicast_OnVehicleEntered( AFGCharacterPlayer* driver );

	/** Input Actions */
	UFUNCTION()
	void Input_ThrottleSteer( const FInputActionValue& actionValue );

// <FL> [ZimmermannA] Gamepad Related vehicle controlling
	UFUNCTION()
	void Input_GamepadThrottle( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_GamepadBrake( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_GamepadSteer( const FInputActionValue& actionValue );
// </FL>
	
	UFUNCTION()
	void Input_LookAxis( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_Handbrake( const FInputActionValue& actionValue );
	
	UFUNCTION()
    void Input_Honk( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_ToggleCamera( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_ToggleLights( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_OpenRecorder( const FInputActionValue& actionValue );
	
	virtual FVector GetVehicleRealActorLocation() const override;

	/** Returns the static mesh that is attached to the skeletal mesh of some vehicles, nullptr if there is no such static mesh */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle" )
	UStaticMeshComponent* FindAttachedStaticMesh();

	/** Returns VehicleMovement subobject **/
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	UFGWheeledVehicleMovementComponent* GetVehicleMovementComponent() const;

	/** Do we have fuel? */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	bool HasFuel() const;

	/** Get the fuel inventory. */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

	/** Get the storage inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }

	FORCEINLINE UBoxComponent* GetFoliageCollideBox() const { return mFoliageCollideBox; } 

	/** Use this function instead of the one in movement component because we have multiple components that move the vehicle */
	UFUNCTION( BlueprintPure, Category = "Velocity" )
	float GetForwardSpeed() const;

	/**
	 * Check if a resource is valid as fuel for this station.
	 * @param resource - Resource class to check.
	 * @return - true if resource valid as fuel; false if not valid or if generator does not run on fuel.
	 */
	UFUNCTION()
	bool IsValidFuel( TSubclassOf< UFGItemDescriptor > resource ) const;
	
	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

	/** Indicates if the vehicle is gasing or wants to move in simulated state */
	UFUNCTION( BlueprintPure, Category = "Movement" ) 
	bool ShouldConsumeFuel() const;

	/** returns the ratio ( 0 to 1.0 ) for how much fuel we want to burn. Ussually a reflection of throttle value except during simulation */
	float GetFuelBurnRatio();

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	AFGWheeledVehicleInfo* GetInfo() const { return mInfo; }

	/**Returns the simulation component */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	AFGDrivingTargetList* GetTargetList( bool createIfNeeded = false );

	/**Getter for path visibility */
	UFUNCTION( BlueprintPure, Category = "Path" )
	bool GetPathVisibility() const;

	/** Blueprint client accessor for when foliage was destroyed */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Character" )
	void Client_PlayFoliageDestroyedEffect( UParticleSystem* destroyEffect, UAkAudioEvent* destroyAudioEvent, FVector location );
	
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Vehicle" )
	void CloseVehicleTrunk();

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Vehicle" )
	void OpenVehicleTrunk( AFGCharacterPlayer* player );

	void MeasureVelocities( float deltaTime );

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	static FText GetDefaultMapName( TSubclassOf< AFGWheeledVehicle > vehicleType );

	void SyncWithSimulation();

	bool HasFullTank() const;

	float GetTotalFuelEnergy() const;

	float CalculateFuelNeed() const;

	static float GetMaxFuelEnergy( TSubclassOf< UFGItemDescriptor > fuelClass );

	float GetMaxFuelEnergy() const;

	bool HasFuelForRoundtrip() const;

	bool IsSufficientFuelType( TSubclassOf< UFGItemDescriptor > fuelType ) const;

	UFUNCTION( BlueprintPure, Category = "Docking" )
	ETransferAnimationState GetTransferAnimationState( float animationLength, float& animationTime ) const;

	void CalculateManualDockingState();

	UFUNCTION( BlueprintPure, Category = "Docking" )
	EManualDockingState GetManualDockingState() const { return mManualDockingState; }

	UFUNCTION( BlueprintPure, Category = "Docking" )
	AFGBuildableDockingStation* GetRefuelingStation() const { return mRefuelingStation; }

	void SetRefuelingStation( AFGBuildableDockingStation* station );

	UFUNCTION( BlueprintCallable, Category = "Docking" )
	void DockToRefuelingStation();

	virtual void UpdatePlayerStatus() override;

protected:
	// Begin AFGVehicle interface
	virtual void Died( AActor* thisActor ) override;
	virtual void SetSimulated( bool newIsSimulated ) override;
	// End AFGVehicle interface

	/** Create item drops for our inventory ( used when vehicle has killed/destroyed */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle" )
	void CreateInventoryItemDrops();

	UFUNCTION()
	void SmoothMovementReplication(float DeltaTime);

	UFUNCTION(Server, Unreliable)
	void ReplicateMovementClientToServer(FVector AuthoritativeLoc, FQuat AuthoritativeQuat, FVector AuthoritativeVelocity);

	/** Notify to allow updating of simulated vehicle colors */
	virtual void OnCustomizationDataApplied( const FFactoryCustomizationData& customizationData ) override;

	/** Ticks foliage removal and character ragdoll */
	virtual void TickPendingVehicleCollisions( float dt );

	UFUNCTION( BlueprintCallable, BlueprintPure )
	float ImpactForceForCollisionSFX( const UPrimitiveComponent* hitComponent, const AActor* otherActor, const UPrimitiveComponent* otherComponent );

	UFUNCTION()
	void OnRepTrunkUser();

	/** Updates current status of the vehicle, such as whenever it has fuel, whenever it is a part of a deadlock, etc */
	void UpdateVehicleStatus();
private:
	void EnsureInfoCreated();

	/** Tick helpers */
	void BurnFuel( const float dt );

	void SetRecordingStatus( ERecordingStatus recordingStatus );

	UFUNCTION()
	void OnFuelAdded( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* sourceInventory = nullptr );

	UFUNCTION()
	void OnRep_TransferStatusChanged();

public:
	// Self-driving

	void StopVehicle();

	float AdjustThrottle( float throttle ) const;

	void StartRecording();

	void StopRecording( bool isValid );

	void TickRecording( float deltaTime );

	void PlaceTargetPoint();

	void ClearTargetList();

	void CacheSpeedInKMH();

	bool ShouldStopVehicle() const;

	int GetSpeedLimit() const { return mSpeedLimit; }

	void StopAllMovement();

	float GetLocalTime() const;
	
	UFUNCTION()
	void MoveForward( float throttle, float brake );
	
	UFUNCTION()
	void MoveRight( float axisValue );

	UFUNCTION(Server, Reliable)
	void Server_SetVehicleLightsOn( bool active );
	
	UFUNCTION(BlueprintNativeEvent, Category="Vehicle")
	void OnVehicleLightStatusChanged();

	UFUNCTION(Server, Reliable)
	void Server_SetHonkStatus(bool active);

	UFUNCTION(BlueprintNativeEvent, Category="Vehicle")
	void OnHonkStatusChanged();

	UFUNCTION(BlueprintNativeEvent, Category="Vehicle")
	void OnOpenRecorderMenu();

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void TurnOverVehicle();

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsRecording() const { return mRecordingStatus == ERecordingStatus::RS_RecordingStarted || mRecordingStatus == ERecordingStatus::RS_CompletionPossible; }

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsFollowingPath() const;

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetIsPossessed( bool isPossessed );

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	int GetSpeedInKMH() const { return mSpeedInKMH; }

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetSpeedLimit( int speedLimit ) { mSpeedLimit = speedLimit; }
	
	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsMenuOpen() const { return mIsMenuOpen; }
	
	UFUNCTION( BlueprintCallable, Category = "Vehicle|SelfDriving" )
	void SetIsMenuOpen( bool isMenuOpen ) { mIsMenuOpen = isMenuOpen; }

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsAutopilotEnabled() const { return mIsAutopilotEnabled; }

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool CanLoadPath() const;
	
	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool CanSavePath() const;

	/** Sets target in the linked list to the next available. Will loop */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void PickNextTarget();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_ToggleAutoPilot();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_TogglePathVisibility();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_ToggleRecording();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_ClearRecordedPath();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_SavePath( const FString& saveName );

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_UnsavePath( AFGSavedWheeledVehiclePath* path );

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_LoadPath( class AFGDrivingTargetList* targetList );
	
	UFUNCTION( BlueprintCallable, BlueprintPure = False )
	void FindSavedPaths( const FString& textFilter, bool filterOnVehicleType, TArray< AFGSavedWheeledVehiclePath* >& result ) const;
	
	UFUNCTION()
	void OnRep_RecordingStatus();

	UFUNCTION()
	void OnRep_ManualDockingState();

	UFUNCTION()
	void OnRep_IsAutopilotEnabled();

	UFUNCTION()
	void OnRep_Info();

	UFUNCTION()
	void OnRep_TargetList( AFGDrivingTargetList* oldList );

	/** Updates the vehicles settings depending on if it should be simulated or "real" */
	virtual void OnIsSimulatedChanged() override;

	FVector GetVelocityVector() const;

	void OnSimulationTargetReached( AFGTargetPoint* newTarget );

	AFGTargetPoint* SpawnNewTargetPoint( const FVector& location, const FRotator& rotation, AFGDrivingTargetList* targetList, int targetSpeed, AFGTargetPoint* afterTarget = nullptr );

	void StartGhosting();

	void TryLeaveSimulatedMode();
	bool IsAboveSolidGround( const FTransform& transform ) const;
	AActor* IsOverlappingOther( const FTransform& transform ) const;

	bool WasFuelAdded() const { return mWasFuelAdded; }

	float GetTargetWaitTime() const { return mTargetWaitTime; }
	bool IsWaitingAtTarget() const { return mTargetWaitTime > 0.0f; }
	
	UFUNCTION()
	void OnPathVisibilityChanged( bool pathVisibility );

	UFUNCTION()
	void OnRep_EngineAudioChanged( const bool oldEngineState );
	
private:
	float CalculateAutomatedFuelToConsume( float deltaTime );

	// Used so we can know when target list changed and listen for path visibility updates from the targetlist. 
	void SetTargetList( AFGDrivingTargetList* targetList );

	/** Updates the visibility of the vehicle mesh, but does not touch the driver's pawn to not mess with it's visibility settings */
	void UpdateVehicleMeshVisibility(bool bNewVisibility);
public:
	/** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName VehicleMeshComponentName;
	
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

	/** Workbench component */
	UPROPERTY( BlueprintReadOnly )
	class UFGWorkBench* mWorkBench;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FTransferStatusChanged );
	/** Broadcast when transfer status is updated */
	UPROPERTY( BlueprintAssignable, Category = "Docking", DisplayName = "OnTransferStatusChanged" )
	FTransferStatusChanged TransferStatusChangedDelegate;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FManualDockingStateChanged );
	/** Broadcast when the conditions for manually docking have changed */
	UPROPERTY( BlueprintAssignable, Category = "Docking", DisplayName = "OnManualDockingStateChanged" )
	FManualDockingStateChanged ManualDockingStateChangedDelegate;

	UPROPERTY( BlueprintAssignable, Category = "Vehicle" )
	FOnAutopilotEnabledChanged mOnAutopilotEnabledChanged;

	UPROPERTY( BlueprintAssignable, Category = "Vehicle" )
	FOnVehiclePathVisibilityChanged mOnVehiclePathVisibilityChanged;
	
	/** Tells audio functionality if engine should be making noises. */
	UPROPERTY( ReplicatedUsing = OnRep_EngineAudioChanged )
	bool mIsEngineOn = false;
	
protected:
	friend class AFGWheeledVehicleAIController;
	friend class UFGSplinePathMovementComponent;
	friend class UFGWheeledVehicleDetectionComponent;
	friend class AFGVehicleSubsystem;
	friend class AFGDrivingTargetList;

	float mTimeDriverEntered;

	/** Angular damping strength (multiplier?) that is applied to the vehicle when in the air. Used to stabilize vehicles in the air and prever over-rotation */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Replicated, SaveGame, Category= "Vehicle" )
	float mAirDampingStrength = 2.5f;

	/** Damage class applied to characters being ran over by this vehicle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Damage" )
	TSubclassOf<UFGDamageType> mRunOverDamageTypeClass;

	/** Base Damage applied to characters that get run over this vehicle at its current speed. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Damage" )
	FRuntimeFloatCurve mDamageAtSpeed;
	
	/** Min speed required to ragdoll a character that's being ran over. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Vehicle" )
	float mRagdollRunOverMinSpeed = 10.f;
	
	/** This vehicles fuel consumption in MW/s */
	UPROPERTY( EditDefaultsOnly, Category = "Fuel", meta = ( AddAutoJSON = true ) )
	float mFuelConsumption;

	UPROPERTY( SaveGame )
	float mFuelConsumedWhileRecording = 0.0f;

	/** Amount left of the currently burned piece of fuel. In megawatt seconds (MWs). */
	UPROPERTY( SaveGame, Replicated )
	float mCurrentFuelAmount;

	/** Are we currently in the process of loading inventory */
	UPROPERTY( BlueprintReadOnly, SaveGame, ReplicatedUsing = OnRep_TransferStatusChanged, Meta = ( NoAutoJson = true ) )
	bool mIsLoadingVehicle;

	/** Are we currently in the process of unloading inventory */
	UPROPERTY( BlueprintReadOnly, SaveGame, ReplicatedUsing = OnRep_TransferStatusChanged, Meta = ( NoAutoJson = true ) )
	bool mIsUnloadingVehicle;

	/** vehicle simulation component */
    UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
    TObjectPtr<UFGWheeledVehicleMovementComponent> mVehicleMovement;

	/** Collision box for detecting overlaps with foliage only. Shape modified in BP */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TObjectPtr<UBoxComponent> mFoliageCollideBox;

	/** Last time we had a position sort of matching server position on the client */
	FDateTime mLastAccurateLocation;

	/** List of head lights this vehicle has */
	UPROPERTY( BlueprintReadOnly, Category = "Vehicle")
	TArray<TObjectPtr<ULightComponent> > mVehicleHeadlights;

	/** List of tail lights this vehicle has */
	UPROPERTY( BlueprintReadOnly, Category = "Vehicle")
	TArray<TObjectPtr<ULightComponent> > mVehicleTailLights;

	/** Are lights on? */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing=OnVehicleLightStatusChanged )
	bool mVehicleLightsOn;

	/** Is Vehicle honking? */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing=OnHonkStatusChanged )
	bool mVehicleHonkOn;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	FRotator mDefaultLockedSprintArmRotation;

	bool mCameraLocked;

	UPROPERTY( BlueprintReadWrite, ReplicatedUsing=OnRepTrunkUser )
	TObjectPtr<AFGCharacterPlayer> mTrunkUser;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FGameplayTag mEnteredVehicleTag;

	UPROPERTY( BlueprintReadWrite, Replicated )
	bool mIsTrunkOpen;
	
private:
	bool mIsServer = false;
	
	/** Inventory for fuel */
	UPROPERTY( VisibleDefaultsOnly, SaveGame )
	TObjectPtr<UFGInventoryComponent> mFuelInventory;

	/** Inventory for storage */
	UPROPERTY( VisibleDefaultsOnly, SaveGame )
	TObjectPtr<UFGInventoryComponent> mStorageInventory;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle", meta = ( AddAutoJSON = true ) )
	int32 mInventorySize;

	/** Deprecated. Kept for compatibility with legacy saves */
	UPROPERTY( SaveGame )
	class UFGTargetPointLinkedList* mTargetNodeLinkedList;
	
	/** Do we need fuel to drive */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	bool mNeedsFuelToDrive;

	ETransferAnimationState mLastTransferAnimationState = ETransferAnimationState::TS_None;
	float mLastTransferAnimationStartTime = -BIG_NUMBER;
	
public:
	// self-driving

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStopRecording, bool, success );
	UPROPERTY( BlueprintAssignable, Category = "Vehicle" )
	FOnStopRecording OnStopRecordingDelegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnStartRecording );
	UPROPERTY( BlueprintAssignable, Category = "Vehicle" )
	FOnStartRecording OnStartRecordingDelegate;

	UPROPERTY( EditDefaultsOnly, Category = "SelfDriving" )
	TSubclassOf< AFGTargetPoint > mTargetPointClass;

	UPROPERTY( EditDefaultsOnly, Category = "SelfDriving" )
	float mGhostingTimeout = 20.0f;

	UPROPERTY( EditDefaultsOnly, Category = "SelfDriving" )
	float mMaxDistanceToSimulation = 500.0f;

	float mSquaredDistanceToClosestPlayer = 0.0f;

	int mPostSimulationImpulseCount = 0;

	float mTimeStationWasEntered = 0.0f;

	/** Was fuel transferred from station to vehicle during the current docking */
	UPROPERTY( SaveGame )
	bool mWasFuelAdded = false;

	bool mIsLookedAt = false;

private:
	// Self-driving

	UPROPERTY( ReplicatedUsing = OnRep_Info, SaveGame )
	TObjectPtr<AFGWheeledVehicleInfo> mInfo;
	
	/** Linked list with target nodes that make up our path to travel */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_TargetList )
	TObjectPtr<AFGDrivingTargetList> mTargetList;

	int mSpeedInKMH = 0;
	bool mIsMenuOpen = false;
	float mRecordCounter = 0.0f;

	FVector mLastVehiclePosition = { 0.0f, 0.0f, 0.0f };
	float mLastVehicleYaw = 0.0f;
	float mAverageSpeed = 0.0f;
	float mYawVelocity = 0.0f;
	float mAverageYawVelocity = 0.0f;
	float mSpeed = 0.0f;
	float mAcceleration = 0.0f;
	bool mIsReversing = false;

	UPROPERTY( Replicated, SaveGame )
	int mSpeedLimit = -1;

	bool mDesiredBrakeAsReverse = true;
	
	float mDesiredSteering = 0.0f;

	float mDesiredThrottle = 0.0f;

	float mDesiredBrake = 0.0f;

	bool mDesiredHandbrake = false;

	UPROPERTY( ReplicatedUsing = OnRep_IsAutopilotEnabled, SaveGame )
	bool mIsAutopilotEnabled = false;
	
	/** The station at which this vehicle is currently being refueled */
	UPROPERTY()
	TObjectPtr<AFGBuildableDockingStation> mRefuelingStation = nullptr;

	UPROPERTY( ReplicatedUsing = OnRep_ManualDockingState )
	EManualDockingState mManualDockingState = EManualDockingState::MDS_NoDocking;

	/** Deprecated. Use mInfo->mTarget. */
	UPROPERTY( SaveGame )
	TObjectPtr<AFGTargetPoint> mCurrentTarget;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_RecordingStatus )
	ERecordingStatus mRecordingStatus = ERecordingStatus::RS_NoRecording;

	UPROPERTY()
	TObjectPtr<AFGTargetPoint> mStoredTarget = nullptr;

	float mThrottleSampleCount = 0.0f;
	float mThrottleSampleSum = 0.0f;

	bool mWantsToStopGhosting = false;

	bool mAwaitingSubsystem = false;

	UPROPERTY( SaveGame )
	bool mHasAutomatedFuelConsumption = false;

	UPROPERTY( SaveGame )
	float mActualAutomatedFuelConsumptionSinceStart = 0.0f;

	UPROPERTY( SaveGame )
	float mAutomatedFuelConsumptionStart = 0.0f;

	UPROPERTY( SaveGame )
	float mAutomatedFuelConsumptionTimeSkipped = 0.0f;

	UPROPERTY( SaveGame )
	float mTargetWaitTime = 0.0f;

	TWeakObjectPtr< AActor > mOverlappingActor;

	float mNextTimeToCheckForLost = 0.0f;
};
