// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGVehicle.h"
#include "FGInventoryComponent.h"
#include "FGDroneVehicle.generated.h"

#ifdef WITH_EDITOR
#define DEBUG_DRONES
#endif

DECLARE_LOG_CATEGORY_EXTERN( LogDrones, Log, All );

DECLARE_STATS_GROUP( TEXT("Drones"), STATGROUP_Drones, STATCAT_Advanced );

UENUM( BlueprintType )
enum class EDroneActionEvent : uint8
{
	DAE_None							UMETA(displayName = "None"),
	DAE_BeginDocking					UMETA(displayName = "Begin Docking"),
	DAE_UpdateQueuePosition				UMETA(displayName = "Update Queue Position"),
	DAE_ReachedDestination				UMETA(displayName = "Reached Destination"),
	DAE_NotifyPairedStationUpdate		UMETA(displayName = "Notify Paired Station Update")
};

UENUM( BlueprintType )
enum class EDroneFlyingMode : uint8
{
	DFM_None		UMETA(displayName = "None"),
	DFM_Flying		UMETA(displayName = "Flying"),
    DFM_Travel		UMETA(displayName = "Travel")
};

UENUM( BlueprintType )
enum class EDroneDockingState : uint8
{
	DS_UNDOCKED		UMETA(displayName = "Undocked"),
    DS_DOCKING		UMETA(displayName = "Docking"),
    DS_DOCKED		UMETA(displayName = "Docked"),
    DS_TAKEOFF		UMETA(displayName = "Takeoff")
};

USTRUCT( BlueprintType )
struct FDroneDockingStateInfo
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	EDroneDockingState State;

	UPROPERTY()
	float StateStartTime;
};

USTRUCT( BlueprintType )
struct FDroneTripInformation
{
	GENERATED_BODY()

	/** How long it took for the drone to go to the other station and back again. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	float TripDuration;

	/** Number of items received from paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	int32 IncomingItemCount;
	
	/** Number of items transferred to paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	int32 OutgoingItemCount;

	/** Number of stacks received from paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	float IncomingItemStacks;

	/** Number of stacks transferred to paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	float OutgoingItemStacks;
};

/** Drone Actions */
UCLASS()
class FACTORYGAME_API UFGDroneAction : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UFGDroneAction();
	
	virtual ~UFGDroneAction() {}

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFGSaveInterface
	
	virtual void Begin() {}
	virtual void End() {}
	virtual void Tick( float dt ) {}
	
	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData = nullptr ) {}

#ifdef DEBUG_DRONES
	virtual void DisplayDebugInformation();
#endif
	
	virtual bool IsDone() const { return true; }
	virtual FString GetActionName() const { return "NULL ACTION"; }

protected:
	void PushAction( UFGDroneAction* pAction );

protected:
	UPROPERTY()
	class AFGDroneVehicle* mDrone;
};

// Timed Action
UCLASS()
class FACTORYGAME_API UFGDroneAction_Timed : public UFGDroneAction
{
	GENERATED_BODY()
public:
	UFGDroneAction_Timed();
	
	virtual void Tick( float dt ) override;
	virtual bool IsDone() const override;

	virtual float GetActionDuration() const { return 0.0f; }

#ifdef DEBUG_DRONES
	virtual void DisplayDebugInformation() override;
#endif

protected:
	float mTimer;
};

// Travel
UCLASS()
class FACTORYGAME_API UFGDroneAction_TraversePath : public UFGDroneAction
{
	GENERATED_BODY()
public:
	UFGDroneAction_TraversePath();
	
	void SetPath( const TArray<FVector>& Path, EDroneFlyingMode FlyingMode, bool StopAtDestination );
	
	virtual FString GetActionName() const override { return "Traverse Path"; }

	virtual void Begin() override;
	virtual void Tick( float dt ) override;
	
	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData ) override;

#ifdef DEBUG_DRONES
	virtual void DisplayDebugInformation() override;
#endif

	virtual bool IsDone() const override;

private:
	void GotoNextDestination();

private:
	UPROPERTY( SaveGame )
	TArray<FVector> mPath;

	UPROPERTY( SaveGame )
	bool mStopAtDestination;

	UPROPERTY( SaveGame )
	EDroneFlyingMode mFlyingMode;

	bool mHasArrived;
};

// Request Docking
UENUM()
enum class EDroneDockingRequestState : uint8
{
	STravelToQueueLocation			UMETA(displayName = "Travel to Queue Location"),
    SFlyToQueueLocation				UMETA(displayName = "Fly to Queue Location"),
    STravelToDockingAirLocation		UMETA(displayName = "Travel to Docking Air Location"),
    SFlyToDockingAirLocation		UMETA(displayName = "Fly to Docking Air Location"),
    SDescendToDockingLocation		UMETA(displayName = "Descend to Docking Location")
};

UCLASS()
class FACTORYGAME_API UFGDroneAction_RequestDocking : public UFGDroneAction
{
	GENERATED_BODY()
public:
	UFGDroneAction_RequestDocking();
	
	void SetStation( class AFGBuildableDroneStation* Station, bool ShouldTransferItems );
	
	virtual FString GetActionName() const override { return "Request Docking"; }
	
	virtual void Begin() override;
	virtual void End() override;

	void MoveToDesignatedQueuePosition( EDroneFlyingMode FlyingMode );
	
	virtual void Tick( float dt ) override;

	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData ) override;
	
	virtual bool IsDone() const override;

#ifdef DEBUG_DRONES
	virtual void DisplayDebugInformation() override;
#endif

private:	
	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mStation;

	UPROPERTY( SaveGame )
	EDroneDockingRequestState mCurrentState;
	
	UPROPERTY( SaveGame )
	bool mShouldTransferItems;

	UPROPERTY( SaveGame )
	float mTotalQueueTime;
	
	bool mIsDone;

	UPROPERTY( SaveGame )
	int mQueuePosition;
};

// Docking
UCLASS()
class FACTORYGAME_API UFGDroneAction_DockingSequence : public UFGDroneAction_Timed
{
	GENERATED_BODY()
public:
	UFGDroneAction_DockingSequence();
	
	void SetStation( class AFGBuildableDroneStation* Station, bool ShouldTransferItems );
	
	virtual FString GetActionName() const override { return "Docking"; }
	
	virtual void Begin() override;
	virtual void End() override;

	virtual float GetActionDuration() const override;
	
private:
	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mStation;

	UPROPERTY( SaveGame )
	bool mShouldTransferItems;
};

// Takeoff
UCLASS()
class FACTORYGAME_API UFGDroneAction_TakeoffSequence : public UFGDroneAction_Timed
{
	GENERATED_BODY()
public:
	UFGDroneAction_TakeoffSequence();
	
	void SetStation( class AFGBuildableDroneStation* Station );
	
	virtual FString GetActionName() const override { return "Takeoff"; }
	
	virtual void Begin() override;
	virtual void End() override;

	virtual float GetActionDuration() const override;

	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData ) override;
	
private:
	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mStation;

	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mNewTravelDestination;

	UPROPERTY( SaveGame )
	bool mHasNewPairedStation;
};

// Travel Start
UCLASS()
class FACTORYGAME_API UFGDroneAction_TravelStartSequence : public UFGDroneAction_Timed
{
	GENERATED_BODY()
public:	
	void SetDestination( const FVector& Destination );
	
	virtual FString GetActionName() const override { return "Travel Start"; }
	
	virtual void Begin() override;
	virtual void End() override;

	virtual float GetActionDuration() const override;

private:
	UPROPERTY( SaveGame )
	FVector mDestination;
};

/** Drone Vehicle */

UCLASS()
class FACTORYGAME_API AFGDroneVehicle : public AFGVehicle
{
	GENERATED_BODY()

	friend class UFGDroneAction;
	friend class UFGDroneAction_DockingSequence;
	friend class UFGDroneAction_TakeoffSequence;
	friend class UFGDroneAction_TravelStartSequence;
public:
	AFGDroneVehicle();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin IFGUseableInterface
	virtual bool IsUseable_Implementation() const override;
	// End IFGUseableInterface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInferface

	// Begin AFGVehicle interface
	virtual void OnSimulationChanged() override;
	// End AFGVehicle interface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	void NotifyPairedStationUpdated( class AFGBuildableDroneStation* NewPairedStation );
	
	void OnUndocked();

	void OnDockedStationDestroyed();

	//~ Begin IFGDockableInterface
	virtual void OnBeginLoadVehicle_Implementation() override;
	virtual void OnBeginUnloadVehicle_Implementation() override;
	virtual void OnTransferComplete_Implementation() override;
	//~ End IFGDockableInterface

	static TArray<FVector> GeneratePathToDestination( const FVector& CurrentLocation, const FVector& Destination, UWorld* World );

	void SetCurrentDestination( const FVector& NewDestination, EDroneFlyingMode FlyingMode, bool StopAtDestination = true );
	void StopMoving();

	// Action Events
	void BeginDocking( class AFGBuildableDroneStation* station );
	void UpdateDockingQueuePosition( int NewPosition );

	/** Get the storage inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
    class UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }

	/** Gets the station this drone belongs to. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
    class AFGBuildableDroneStation* GetHomeStation() const { return mHomeStation; }

	/** Gets the station this drone is docked to. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
    class AFGBuildableDroneStation* GetDockedStation() const { return mDockedStation; }

	/** Gets the station this drone is currently traveling to. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
    class AFGBuildableDroneStation* GetCurrentDestinationStation() const { return mCurrentTripDestinationStation; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetSpeedFlying() const { return mFlyingSpeed; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetDockingSequenceDuration() const { return mDockingSequenceDuration; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetTakeoffSequenceDuration() const { return mTakeoffSequenceDuration; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetTravelStartSequenceDuration() const { return mTravelStartSequenceDuration; }
    
	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetSpeedTraveling() const { return mTravelingSpeed; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetStoppingDistanceFlying() const { return mFlyingStoppingDistance; }
    
	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetStoppingDistanceTraveling() const { return mTravelingStoppingDistance; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetSpeedForFlyingMode( EDroneFlyingMode Mode ) const;

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetStoppingDistanceForFlyingMode( EDroneFlyingMode Mode ) const;

	UFUNCTION( BlueprintPure, Category = "Drone" )
	const FVector& GetCurrentDestination() const { return mCurrentDestination; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    const FVector& GetCurrentVelocity() const { return mCurrentVelocity; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
	EDroneFlyingMode GetCurrentFlyingMode() const { return mCurrentFlyingMode; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    const FDroneDockingStateInfo& GetCurrentDockingState() const { return mCurrentDockingState; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetTimeSinceDockingStateChanged() const;
	
	UFUNCTION( BlueprintPure, Category = "Drone" )
    bool GetIsBraking() const { return mIsBraking; }

	/** Gets the current power level of the drone, which is power gained from consuming batteries. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetCurrentPowerLevel() const { return mCurrentPowerLevel; }

	/** Gets the power level of all batteries in the inventory, this power isn't usable until batteries have been consumed. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetInventoryPotentialPowerLevel() const { return mInventoryPotentialPower; }

	// Intended to only be called when the drone is created, since we also set it to be docked to the station here
    void SetHomeStation( class AFGBuildableDroneStation* station );

	bool GrabRequiredBatteriesForTrip( class AFGBuildableDroneStation* FromStation, class AFGBuildableDroneStation* ToStation, bool AllowTravelWithoutCost );
	
	bool TravelToStation( class AFGBuildableDroneStation* station, bool ShouldTransferItems );

	void BeginNewTrip( class AFGBuildableDroneStation* Station );
	void EndCurrentTrip( bool Completed );

	void SetFacingDirection( const FVector& Direction );

protected:
	UFUNCTION( BlueprintImplementableEvent )
    void TickVFX();
	
	/** Called when the drone changes flying mode. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnFlyingModeChanged( EDroneFlyingMode NewMode );

	/** Called when the drone changes docking state. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnDockingStateChanged( EDroneDockingState NewState, float TimeSinceChanged );
	
	/** Called when the drone starts its docking sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
    void StartDockingSequence( class AFGBuildableDroneStation* Station );

	/** Called when the drone ends its docking sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
	void EndDockingSequence( class AFGBuildableDroneStation* Station, bool ShouldTransferItems );
	
	/** Called when the drone starts its takeoff sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
    void StartTakeoffSequence( class AFGBuildableDroneStation* Station );

	/** Called when the drone ends its takeoff sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
	void EndTakeoffSequence( class AFGBuildableDroneStation* Station );

	/** Called when the drone starts its travel start sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
    void StartTravelStartSequence();

	/** Called when the drone ends its travel start sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
    void EndTravelStartSequence();

	/** Called when the drone changes whether or not it is braking. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnBrakingStateChanged( bool IsBraking );

	UFUNCTION()
	void OnRep_IsBraking();

	UFUNCTION()
    void OnRep_FlyingMode();

	UFUNCTION()
    void OnRep_DockingState();

	UFUNCTION()
    void OnRep_DockedStation();

	void OnSignificanceUpdate();

private:
	void ClearAllActions( bool KeepCurrentAction = false );

	void SetNewFlyingMode( EDroneFlyingMode Mode );

	void SetDockingState( EDroneDockingState State );

	bool ConsumeBatteriesForPower( float PowerRequirement );

	void CalculateInventoryPotentialPower();

private:	
	/** Inventory for storage. */
	UPROPERTY( VisibleDefaultsOnly, SaveGame )
	class UFGInventoryComponent* mStorageInventory;

	/** Inventory where batteries are stored. */
	UPROPERTY( VisibleDefaultsOnly, SaveGame )
	class UFGInventoryComponent* mBatteryInventory;

	/** Size of the drone's inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone", meta = ( AddAutoJSON = true ) )
	int32 mInventorySize;

	/** Size of battery inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	int8 mBatteryStorageSize;

	/** How long the docking sequence is. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mDockingSequenceDuration;
	
	/** How long the takeoff sequence is. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mTakeoffSequenceDuration;

	/** How long the travel start sequence is. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mTravelStartSequenceDuration;

	/** How fast the drone moves when flying. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mFlyingSpeed;

	/** How fast the drone moves when traveling. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mTravelingSpeed;

	/** How far away from the destination the drone should start slowing down at when flying. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mFlyingStoppingDistance;

	/** How far away from the destination the drone should start slowing down at when traveling. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mTravelingStoppingDistance;

	/** How fast the drone is able to turn. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mTurningStrength;
	
	float mInventoryPotentialPower;
	
	UPROPERTY( SaveGame )
	float mCurrentPowerLevel;

	UPROPERTY( SaveGame )
	float mCurrentTripPowerCost;

	UPROPERTY( SaveGame )
	FDroneTripInformation mCurrentTripInformation;
	
	UPROPERTY( ReplicatedUsing=OnRep_IsBraking )
	bool mIsBraking;

	UPROPERTY( SaveGame, Replicated )
	FVector mCurrentVelocity;

	UPROPERTY( SaveGame )
	FVector mCurrentDestination;

	UPROPERTY( SaveGame, Replicated )
	FVector mDesiredFacingDirection;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_FlyingMode )
	EDroneFlyingMode mCurrentFlyingMode;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_DockingState )
	FDroneDockingStateInfo mCurrentDockingState;

	UPROPERTY( SaveGame )
	bool mStopAtDestination;
	
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_DockedStation )
	class AFGBuildableDroneStation* mDockedStation;

	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mHomeStation;

	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mCurrentTripDestinationStation;

	// Actions
	UPROPERTY( SaveGame )
	TArray<UFGDroneAction*> mActionsToExecute;

	UPROPERTY( SaveGame )
	UFGDroneAction* mCurrentAction;
};
