// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGVehicle.h"
#include "FGInventoryComponent.h"
#include "FGDroneMovementComponent.h"
#include "FGDroneVehicle.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogDrones, Log, All );

DECLARE_STATS_GROUP( TEXT("Drones"), STATGROUP_Drones, STATCAT_Advanced );

extern TAutoConsoleVariable< int32 > CVarDronesDebug;

UENUM( BlueprintType )
enum class EDroneActionEvent : uint8
{
	DAE_None							UMETA(displayName = "None"),
	DAE_BeginDocking					UMETA(displayName = "Begin Docking"),
	DAE_UpdateQueuePosition				UMETA(displayName = "Update Queue Position"),
	DAE_NotifyPairedStationUpdate		UMETA(displayName = "Notify Paired Station Update")
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
	float TripDuration = 0.f;

	/** Number of items received from paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	int32 IncomingItemCount = 0;
	
	/** Number of items transferred to paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	int32 OutgoingItemCount = 0;

	/** Number of stacks received from paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	float IncomingItemStacks = 0.f;

	/** Number of stacks transferred to paired station. */
	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, SaveGame )
	float OutgoingItemStacks = 0.f;
};

USTRUCT( BlueprintType )
struct FFGDroneFuelType
{
	GENERATED_BODY()

	FName GetFuelName() const { return Item ? Item->GetFName() : FName(); }
	
	/** What type of item is used as fuel. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf< UFGItemDescriptor > Item = nullptr;

	/** What color the thruster should have when using this fuel type. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FColor ThrusterColor = FColor::White;
	
	/** What color the thruster should have when using this fuel type. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FColor ThrusterEndColor = FColor::White;

	/** Flight speed of the drone while using this fuel. Will use Default Drone Speed if <= 0. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float FlightSpeed = 1000.0f;

	/** Traveling speed of the drone while using this fuel. Will use Default Drone Speed if <= 0. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float TravelSpeed = 7000.0f;
};

USTRUCT( BlueprintType )
struct FFGDroneFuelRuntimeData
{
	GENERATED_BODY()

	/** Name of the fuel type this runtime data belongs to. */
	UPROPERTY( SaveGame, BlueprintReadOnly )
	FName FuelTypeName;

	/** Current energy level of this fuel type. */
	UPROPERTY( SaveGame, BlueprintReadOnly )
	float EnergyLevel;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnDroneActiveFuelTypeChanged, const FFGDroneFuelType&, newFuelType );

/** Drone Vehicle */

UCLASS()
class FACTORYGAME_API AFGDroneVehicle : public AFGVehicle, public IFGActorRepresentationInterface
{
	GENERATED_BODY()

	friend struct FDroneAction;
	friend struct FDroneAction_DockingSequence;
	friend struct FDroneAction_TakeoffSequence;
	friend struct FDroneAction_TravelStartSequence;
public:
	AFGDroneVehicle();

	virtual void Serialize( FArchive& Ar ) override;
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void PostNetReceiveLocationAndRotation() override;
	// End AActor interface

	// Begin IFGUseableInterface
	virtual bool IsUseable_Implementation() const override;
	// End IFGUseableInterface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInferface

	// Begin AFGVehicle interface
	virtual void OnIsSimulatedChanged() override;
	// End AFGVehicle interface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	// Begin IFGActorRepresentationInterface
	UFUNCTION() virtual bool AddAsRepresentation() override;
	UFUNCTION() virtual bool UpdateRepresentation() override;
	UFUNCTION() virtual bool RemoveAsRepresentation() override;
	UFUNCTION() virtual bool IsActorStatic() override;
	UFUNCTION() virtual FVector GetRealActorLocation() override;
	UFUNCTION() virtual FRotator GetRealActorRotation() override;
	UFUNCTION() virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION() virtual FText GetActorRepresentationText() override;
	UFUNCTION() virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION() virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION() virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION() virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION() virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION() virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION() virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION() virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION() virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION() virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	UFUNCTION() virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface

	void NotifyPairedStationUpdated( class AFGBuildableDroneStation* NewPairedStation );
	
	void OnUndocked();

	void OnDockedStationDestroyed();

	//~ Begin IFGDockableInterface
	virtual void OnBeginLoadVehicle_Implementation() override;
	virtual void OnBeginUnloadVehicle_Implementation() override;
	virtual void OnTransferComplete_Implementation() override;
	//~ End IFGDockableInterface

	static TArray<FVector> GeneratePathToDestination( const FVector& CurrentLocation, const FVector& Destination, UWorld* World );

	// Action Events
	void BeginDocking( class AFGBuildableDroneStation* station );
	void UpdateDockingQueuePosition( int NewPosition );

	/** Gets the action the drone is currently executing. */
	FORCEINLINE struct FDroneAction* GetActiveAction() const { return mActiveAction; }

	/** Whether or not this drone is currently idle. Meaning it has no Active Action and no pending actions in queue. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
	FORCEINLINE bool IsDroneIdle() const { return !mActiveAction && mActionQueue.Num() == 0; }

	/** Returns the drone movement component. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
	FORCEINLINE class UFGDroneMovementComponent* GetDroneMovementComponent() const { return mMovementComponent; }

	/** Returns the drone movement component. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
	FORCEINLINE int32 GetDroneInventorySize() const { return mInventorySize; }

	/** Fuel types the drone can use. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE TArray< FFGDroneFuelType > const& GetDroneFuelTypes() const { return mFuelTypes; }

	/** Gets the active fuel type. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FFGDroneFuelType const& GetActiveFuelType() const;

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
    class AFGBuildableDroneStation* GetCurrentDestinationStation() const { return mCurrentDestinationStation; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetSpeedFlying() const;

	UFUNCTION( BlueprintPure, Category = "Drone" )
	float GetSpeedTraveling() const;

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetDockingSequenceDuration() const { return mDockingSequenceDuration; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetTakeoffSequenceDuration() const { return mTakeoffSequenceDuration; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetTravelStartSequenceDuration() const { return mTravelStartSequenceDuration; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    const FDroneDockingStateInfo& GetCurrentDockingState() const { return mCurrentDockingState; }

	UFUNCTION( BlueprintPure, Category = "Drone" )
    float GetTimeSinceDockingStateChanged() const;

	/** Whether or not the specified item class is a valid fuel item for this drone. */
	UFUNCTION( BlueprintPure, Category = "Drone" )
	bool IsValidFuelItem( TSubclassOf< class UFGItemDescriptor > item ) const;

	// Intended to only be called when the drone is created, since we also set it to be docked to the station here
    void SetHomeStation( class AFGBuildableDroneStation* station );

	bool PrepareTripFromDockedStation( const class AFGBuildableDroneStation* ToStation );
	void RefuelFromDockedStation( float amount );
	
	bool TravelToStation( class AFGBuildableDroneStation* station, bool ShouldTransferItems );
	bool TravelToLocation( const FVector& Location );

	void BeginNewTrip( class AFGBuildableDroneStation* Station );
	void EndCurrentTrip( bool Completed );

#if !UE_BUILD_SHIPPING
	virtual void ShowDebug();
#endif

protected:
	UFUNCTION( BlueprintImplementableEvent )
    void TickVFX();

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

	/** Called when the drone selects a new fuel type. Called on both Server and Client. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone" )
	void OnActiveFuelTypeChanged( const FFGDroneFuelType& FuelType );

	/** Called when the drone changes flying mode. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
	void OnFlyingModeChanged( EDroneFlyingMode NewFlyingMode );

	/** Called when the drone starts / stops braking. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
	void OnBrakingStateChanged( bool IsBraking );

	UFUNCTION()
    void OnRep_DockingState();

	UFUNCTION()
    void OnRep_DockedStation();

	UFUNCTION()
	void OnRep_ActiveFuel();

	void OnSignificanceUpdate();

	/** Finds a fuel type by name. Fuel name is tied to Item Descriptor FName. */
	const FFGDroneFuelType* GetFuelTypeFromName( FName fuelName ) const;

	/** Finds a fuel runtime data by name. Fuel name is tied to Item Descriptor FName.*/
	const FFGDroneFuelRuntimeData* GetFuelDataFromName( FName fuelName ) const;
	FFGDroneFuelRuntimeData* GetFuelDataFromName( FName fuelName );

private:
	void ClearAllActions( bool KeepCurrentAction = false );

	void SetDockingState( EDroneDockingState State );

	/** Helper function to consume fuel from any type available. Returns true if successfully selected and consumed a fuel type. */
	bool SelectAndConsumeAnyFuel( float fuelAmount );

	/** Helper function to consume fuel from any type available.  Returns true if successfully selected and consumed a fuel type. */
	bool SelectAndConsumeFastestFuel( float fuelAmount );
	
	void SwitchToFuelType( const FFGDroneFuelType& fuelType );

	/** Function used to setup the fuel data array. Will clear out invalid entries and create new entries so it matches Fuel Type array. */
	void SetupFuelData();

	// Helper function to migrate from old legacy action to the refactored non-uobject system
	FDroneAction* MigrateLegacyAction( class UFGDroneAction* action );

	UFUNCTION()
	void OnMovementFlyingModeChanged( EDroneFlyingMode NewFlyingMode );
	
	UFUNCTION()
	void OnMovementBrakingStateChanged( bool IsBraking );

public:
	/** Invoked when the active fuel type of the drone changes */
	UPROPERTY( BlueprintAssignable, Category = "Drone" )
	FOnDroneActiveFuelTypeChanged DroneFuelTypeChangedDelegate;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* mCompassMaterialInstance;

private:
	/** The drone's movement component. */
	UPROPERTY( Replicated )
	class UFGDroneMovementComponent* mMovementComponent;
	
	/** Default fuel type of the drone. Backup for when no fuel exists. The item property is not used. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	FFGDroneFuelType mDefaultFuelType;
	
	/** Fuel types that the drone can use. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	TArray< FFGDroneFuelType > mFuelTypes;
	
	/** Inventory for storage. */
	UPROPERTY( VisibleDefaultsOnly, SaveGame )
	class UFGInventoryComponent* mStorageInventory;

	/** Size of the drone's inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone", meta = ( AddAutoJSON = true ) )
	int32 mInventorySize;

	/** How long the docking sequence is. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mDockingSequenceDuration;
	
	/** How long the takeoff sequence is. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mTakeoffSequenceDuration;

	/** How long the travel start sequence is. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone" )
	float mTravelStartSequenceDuration;
	
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_ActiveFuel )
	FName mActiveFuelName;

	UPROPERTY( SaveGame )
	TArray< FFGDroneFuelRuntimeData > mFuelData;

	UPROPERTY( SaveGame )
	float mCurrentTripPowerCost;

	UPROPERTY( SaveGame )
	FDroneTripInformation mCurrentTripInformation;

	UPROPERTY( SaveGame )
	bool mHasBegunTrip;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_DockingState )
	FDroneDockingStateInfo mCurrentDockingState;
	
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_DockedStation )
	class AFGBuildableDroneStation* mDockedStation;

	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mHomeStation;
	
	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mCurrentDestinationStation;

	// Actions (Legacy, only here for backwards compatibility with saves)
	UPROPERTY( SaveGame )
	TArray< UFGDroneAction* > mActionsToExecute;

	UPROPERTY( SaveGame )
	UFGDroneAction* mCurrentAction;

	// Actions
	TArray< FDroneAction* > mActionQueue;

	FDroneAction* mActiveAction;
};

UENUM()
enum class EDroneDockingRequestState : uint8
{
	STravelToQueueLocation			UMETA(displayName = "Travel to Queue Location"),
	SFlyToQueueLocation				UMETA(displayName = "Fly to Queue Location"),
	STravelToDockingAirLocation		UMETA(displayName = "Travel to Docking Air Location"),
	SFlyToDockingAirLocation		UMETA(displayName = "Fly to Docking Air Location"),
	SDescendToDockingLocation		UMETA(displayName = "Descend to Docking Location")
};

/** Legacy Drone Actions (Only here for backwards compatibility with saves) */
UCLASS()
class FACTORYGAME_API UFGDroneAction : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
};

// Timed Action
UCLASS()
class FACTORYGAME_API UFGDroneAction_Timed : public UFGDroneAction
{
	GENERATED_BODY()
};

// Travel
UCLASS()
class FACTORYGAME_API UFGDroneAction_TraversePath : public UFGDroneAction
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame )
	TArray< FVector > mPath;

	UPROPERTY( SaveGame )
	EDroneFlyingMode mFlyingMode;
	
	UPROPERTY( SaveGame )
	bool mStopAtDestination;

	bool mHasArrived;
};

// Request Docking
UCLASS()
class FACTORYGAME_API UFGDroneAction_RequestDocking : public UFGDroneAction
{
	GENERATED_BODY()
public:	
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
	UPROPERTY( SaveGame )
	FVector mDestination;
};

/** Drone Actions */
class FGDroneActionFactory
{
public:
	explicit FGDroneActionFactory( AFGDroneVehicle* drone );

	struct FDroneAction* CreateDroneActionFromName( const FName& name ) const;

private:
	AFGDroneVehicle* mDrone;
};

// There's no virtual getter for the static struct so we need our own virtual function which grabs the static struct on each class. :)
#define ACTION_STATIC_STRUCT_IMPL virtual UScriptStruct* GetActionStaticStruct() const override { return StaticStruct(); }

USTRUCT()
struct FACTORYGAME_API FDroneAction
{
	GENERATED_BODY()

	friend class FGDroneActionFactory;
public:
	FDroneAction();
	FDroneAction( AFGDroneVehicle* drone );
	
	virtual ~FDroneAction() {}
	
	virtual void Begin();
	virtual void End() {}
	virtual void Tick( float dt ) {}

	/** Virtual getter for the action's static struct. Needs to be implemented for each action struct. */
	virtual UScriptStruct* GetActionStaticStruct() const;
	
	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData = nullptr ) {}

	/** Can be used to migrate or sanitize data for each individual drone action */
	virtual void PostLoadGame( int32 saveVersion ) {}

#if !UE_BUILD_SHIPPING
	virtual void ShowDebug( FString& out_concatDebugString );
#endif
	
	virtual bool IsDone() const { return true; }
	virtual FString GetActionName() const { return "NULL ACTION"; }

protected:
	void PushAction( FDroneAction* action );

protected:
	TWeakObjectPtr< AFGDroneVehicle > mDrone;
	TWeakObjectPtr< UFGDroneMovementComponent > mDroneMovement;
};

// Timed Action
USTRUCT()
struct FACTORYGAME_API FDroneAction_Timed : public FDroneAction
{
	GENERATED_BODY()
public:
	FDroneAction_Timed();
	FDroneAction_Timed( AFGDroneVehicle* drone );

	ACTION_STATIC_STRUCT_IMPL
	
	virtual void Tick( float dt ) override;
	virtual bool IsDone() const override;

	virtual float GetActionDuration() const { return 0.0f; }

#if !UE_BUILD_SHIPPING
	virtual void ShowDebug( FString& out_concatDebugString ) override;
#endif

protected:
	float mTimer;
};

// Travel
USTRUCT()
struct FACTORYGAME_API FDroneAction_TraversePath : public FDroneAction
{
	GENERATED_BODY()
public:
	FDroneAction_TraversePath();
	FDroneAction_TraversePath( AFGDroneVehicle* drone, const TArray< FVector >& path, EDroneFlyingMode flyingMode, bool stopAtDestination );
	FDroneAction_TraversePath( AFGDroneVehicle* drone, const UFGDroneAction_TraversePath* legacyAction );

	ACTION_STATIC_STRUCT_IMPL
	
	virtual FString GetActionName() const override { return "Traverse Path"; }

	virtual void Begin() override;
	virtual void End() override;
	
	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData ) override;

	virtual bool IsDone() const override;
	virtual void PostLoadGame(int32 saveVersion) override;

private:
	void OnDestinationReached();

private:
	UPROPERTY( SaveGame )
	TArray< FVector > mPath;

	UPROPERTY( SaveGame )
	EDroneFlyingMode mFlyingMode;

	UPROPERTY( SaveGame )
	bool mStopAtDestination;

	bool mHasArrived;
};

// Move to location
USTRUCT()
struct FACTORYGAME_API FDroneAction_MoveToLocation : public FDroneAction
{
	GENERATED_BODY()
public:
	FDroneAction_MoveToLocation();
	FDroneAction_MoveToLocation( AFGDroneVehicle* drone, const FVector& location, EDroneFlyingMode flyingMode, const FVector& directionToFace = FVector::ZeroVector, EDroneDirectionFacingIstruction directionFacingInstruction = EDroneDirectionFacingIstruction::DFI_None );

	ACTION_STATIC_STRUCT_IMPL
	
	virtual FString GetActionName() const override { return "Move to Location"; }

	virtual void Begin() override;
	virtual void End() override;
	
	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData ) override;

	virtual bool IsDone() const override;
	virtual void PostLoadGame(int32 saveVersion) override;

private:
	void OnDestinationReached();

private:
	UPROPERTY( SaveGame )
	FVector mLocation;

	UPROPERTY( SaveGame )
	EDroneFlyingMode mFlyingMode;
	
	UPROPERTY( SaveGame )
	FVector mDirectionToFace;

	UPROPERTY( SaveGame )
	EDroneDirectionFacingIstruction mDirectionFacingInstruction;

	bool mHasArrived;
};

// Request Docking
USTRUCT()
struct FACTORYGAME_API FDroneAction_RequestDocking : public FDroneAction
{
	GENERATED_BODY()
public:
	FDroneAction_RequestDocking();
	FDroneAction_RequestDocking( AFGDroneVehicle* drone, class AFGBuildableDroneStation* station, bool shouldTransferItems );
	FDroneAction_RequestDocking( AFGDroneVehicle* drone, const UFGDroneAction_RequestDocking* legacyAction );

	ACTION_STATIC_STRUCT_IMPL
	
	virtual FString GetActionName() const override { return "Request Docking"; }
	
	virtual void Begin() override;
	virtual void End() override;

	void MoveToDesignatedQueuePosition( EDroneFlyingMode FlyingMode );
	
	virtual void Tick( float dt ) override;

	virtual void ReceiveActionEvent( EDroneActionEvent ActionEvent, void* EventData ) override;
	
	virtual bool IsDone() const override;

#if !UE_BUILD_SHIPPING
	virtual void ShowDebug( FString& out_concatDebugString ) override;
#endif
	
private:
	void OnDestinationReached();

	void MoveToStationAirLocation( EDroneFlyingMode flyingMode );

private:
	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mStation;

	UPROPERTY( SaveGame )
	bool mShouldTransferItems;

	UPROPERTY( SaveGame )
	EDroneDockingRequestState mCurrentState;
	
	UPROPERTY( SaveGame )
	float mTotalQueueTime;

	UPROPERTY( SaveGame )
	int mQueuePosition;

	bool mIsDone;
};

// Docking
USTRUCT()
struct FACTORYGAME_API FDroneAction_DockingSequence : public FDroneAction_Timed
{
	GENERATED_BODY()
public:
	FDroneAction_DockingSequence();
	FDroneAction_DockingSequence( AFGDroneVehicle* drone, class AFGBuildableDroneStation* station, bool shouldTransferItems );
	FDroneAction_DockingSequence( AFGDroneVehicle* drone, const UFGDroneAction_DockingSequence* legacyAction );

	ACTION_STATIC_STRUCT_IMPL
	
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
USTRUCT()
struct FACTORYGAME_API FDroneAction_TakeoffSequence : public FDroneAction_Timed
{
	GENERATED_BODY()
public:
	FDroneAction_TakeoffSequence();
	FDroneAction_TakeoffSequence( AFGDroneVehicle* drone, class AFGBuildableDroneStation* station );
	FDroneAction_TakeoffSequence( AFGDroneVehicle* drone, const UFGDroneAction_TakeoffSequence* legacyAction );

	ACTION_STATIC_STRUCT_IMPL
	
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
USTRUCT()
struct FACTORYGAME_API FDroneAction_TravelStartSequence : public FDroneAction_Timed
{
	GENERATED_BODY()
public:
	FDroneAction_TravelStartSequence();
	FDroneAction_TravelStartSequence( AFGDroneVehicle* drone, const FVector& destination );
	FDroneAction_TravelStartSequence( AFGDroneVehicle* drone, const UFGDroneAction_TravelStartSequence* legacyAction );

	ACTION_STATIC_STRUCT_IMPL
	
	virtual FString GetActionName() const override { return "Travel Start"; }
	
	virtual void Begin() override;
	virtual void End() override;

	virtual float GetActionDuration() const override;
	virtual void PostLoadGame(int32 saveVersion) override;

private:
	UPROPERTY( SaveGame )
	FVector mDestination;
};

#undef ACTION_STATIC_STRUCT_IMPL