// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"

#include "GameFramework/Actor.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"
#include "TextProperty.h"
#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "RailroadNavigation.h"
#include "FGTrain.generated.h"


class UFGRailroadTrackConnectionComponent;


/**
 * Error codes for the self driving locomotives.
 */
UENUM( BlueprintType )
enum class ESelfDrivingLocomotiveError : uint8
{
	SDLE_NoError					UMETA( DisplayName = "No Error" ),
	SDLE_NoPower					UMETA( DisplayName = "No Power" ),
	SDLE_NoTimeTable				UMETA( DisplayName = "No Time Table" ),
	SDLE_InvalidNextStop			UMETA( DisplayName = "Invalid Next Stop" ),
	SDLE_InvalidLocomotivePlacement	UMETA( DisplayName = "Invalid Locomotive Placement" ),
	SDLE_NoPath						UMETA( DisplayName = "No Path" )
};

/**
 * Signal aspects used for signaling and ATC points.
 */
UENUM( BlueprintType )
enum class ERailroadSignalAspect : uint8
{
	RSA_None			UMETA( DisplayName = "None" ),
	RSA_Clear			UMETA( DisplayName = "Clear" ),
	RSA_ClearThenStop	UMETA( DisplayName = "Clear Then Stop" ),
	RSA_Stop			UMETA( DisplayName = "Stop" ),
	RSA_Dock			UMETA( DisplayName = "Dock" )
};

/**
 * Docked state.
 */
UENUM( BlueprintType )
enum class ETrainDockingState : uint8
{
	TDS_None			UMETA( DisplayName = "None" ),
	TDS_ReadyToDock		UMETA( DisplayName = "Ready To Dock" ),
	TDS_Docked			UMETA( DisplayName = "Docked" )
};

/** Global constants for trains. */
struct FACTORYGAME_API TrainConstants
{
	// At which distance can a station start catching the train. [cm]
	static float CATCH_DISTANCE;
	// At which offset should a locomotive stop at a signal or station. [cm]
	static float STOP_OFFSET;
	// At which distance a locomotive can dock to a station. [cm]
	static float DOCK_DISTANCE;
	// At which speed is docking allowed. [cm/s]
	static float DOCK_SPEED;
	// This is the speed on a restricted section, e.g. before docking. [cm/s]
	static float RESTRICTED_SPEED;

public:
	FORCEINLINE ~TrainConstants() = default;
};

/**
 * Describes the static properties of a train consist.
 * I.e. the locomotives, railcars, length and tare weight.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FTrainConsist
{
GENERATED_BODY()
public:
	/** The vehicles in this consist. */
	UPROPERTY( BlueprintReadOnly )
	TArray< TSubclassOf< AFGRailroadVehicle > > Vehicles;

	//@todotrains Orientations.
	//@todotrains Fill percentages.

	/** Length of the consist, [cm] */
	UPROPERTY( BlueprintReadOnly )
	float Length = 0.f;

	/** Mass of the consist, [kg] */
	UPROPERTY( BlueprintReadOnly )
	float Mass = 0.f;

	/** Maximum speed for the slowest vehicle in the consist. [cm/s] */
	UPROPERTY( BlueprintReadOnly )
	float MaxSpeed = 0.f;

	/** The sustained braking force the consist can apply in it's operational speed range. [N] [kg cm/s^2] */
	float MaxAirBrakingEffort = 0.f;
	float HighSpeedDynamicBrakingEffort = 0.f;
	float LimitedSpeedDynamicBrakingEffort = 0.f;
	float MaxTractiveEffort = 0.f;

public:
	FORCEINLINE ~FTrainConsist() = default;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTrainAtcPoint
{
	GENERATED_BODY()
public:
	/** The track connection. */
	UPROPERTY()
	UFGRailroadTrackConnectionComponent* TrackConnection = nullptr;

	/** How far away is this point in whole segments. */
	float LongDistance = 0.f;

	/** How far away is this point. */
	float Distance = 0.f;

	/** How high up is this. */
	float AverageGrade = 0.f;

	/** The speed the train should have when passing this point. No limit if 0. */
	float SpeedLimit = 0.f;

	/** Signal output at this point. If any. */
	ERailroadSignalAspect SignalAspect = ERailroadSignalAspect::RSA_None;

public:
	FORCEINLINE ~FTrainAtcPoint() = default;
};

/**
 * Data for the automatic train control system.
 * For the AI to make the correct decisions.
 * As a safety/guidance system for when the player is driving.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FTrainAtcData
{
	GENERATED_BODY()
public:
	/** Functions to help manage the path. */
	bool SetPath( const FRailroadPathFindingResult& result );
	void ClearPath();
	bool HasPath() const;
	
	/** Update the target points ahead from the current connection. */
	void UpdateTargetPoints( UFGRailroadTrackConnectionComponent* current );
	/** Function to update which path segment we're on based on what our current connection is up ahead. */
	bool UpdateCurrentPathSegment( UFGRailroadTrackConnectionComponent* current );

	/** If a connection is relevant for controlling the train. */
	static bool IsRelevantForATC( const UFGRailroadTrackConnectionComponent* connection );
public:
	/** The route this train should follow. */
	FRailroadPathSharedPtr Path;
	/** Index of the next point along the route. */
	int32 CurrentPathSegment = INDEX_NONE;

	/** The next connection up ahead. */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > CurrentConnection = nullptr;
	float CurrentConnectionDistance = 0.f;

	/**
	 * Connection points ahead we'll pass on our way forward and the distance to them.
	 * Does not contain a point that is only a pass-through (not relevant).
	 * Index 0 may not be the same as NextConnection.
	 */
	TArray< FTrainAtcPoint > TargetPoints;

	/** Speed and distance indicators. */
	float CurrentSpeed = 0.f;
	float TargetSpeed = 0.f;

	/**
	 * Next upcoming signal.
	 * A signal in this context is something that announces a change in speed, e.g. a station we should dock to.
	 * This is not necessarily the first signal that appears in target points but rather the most restricting for our speed.
	 */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > NextSignalConnection = nullptr;
	float NextSignalSpeed = 0.f;
	float NextSignalDistance = 0.f;
	float NextSignalGrade = 0.f; // [%]
	ERailroadSignalAspect NextSignalAspect = ERailroadSignalAspect::RSA_None;

	/** If >= 0 we want to be catched at that distance. */
	float CatchAtSignalDistance = -1.f;

public:
	FORCEINLINE ~FTrainAtcData() = default;
};


/**
 * States for self driving locomotives.
 */
UENUM()
enum class ESelfDrivingLocomotiveState : uint8
{
	SDLS_Idle,
	SDLS_FollowPath,
	SDLS_Docking,
	SDLS_DockingCompleted,
};


/**
 * Realtime data for the ai.
 */
USTRUCT()
struct FACTORYGAME_API FTrainSelfDrivingData
{
	GENERATED_BODY()
public:
	/** The state the ai is in, determines which functions to run. */
	ESelfDrivingLocomotiveState State = ESelfDrivingLocomotiveState::SDLS_Idle;

	/** Next stop we're aiming for, also look at the current stop in the time table, this is updated from there. */
	int32 NextStop = INDEX_NONE;

	// Enabled
	// Last error

	/** When did we find this path. */
	float TimeOfLastFindPath = 0.0f;

	/** If the last speed was up or down or none. */
	int8 LastSpeedControl = 0;

public:
	FORCEINLINE ~FTrainSelfDrivingData() = default;
};


/**
 * The physics simulation data for the trains.
 */
USTRUCT()
struct FACTORYGAME_API FTrainSimulationData
{
	GENERATED_BODY()
public:
	/** Is this train simulating physics and not just moving along the track. */
	bool IsSimulatingPhysics = false;

	/** Cached vehicles in the direction of travel. */
	UPROPERTY()
	TArray< class AFGRailroadVehicle* > SimulatedVehicles;

	/** Cached movements in the same order as the vehicles. */
	UPROPERTY()
	TArray< class UFGRailroadVehicleMovementComponent* > SimulatedMovements;

	/** If we're simulating the train front to back (1) or back to front (-1). */
	float SimulationDirection = 0.f;

	/** Cached master locomotive. */
	UPROPERTY()
	class UFGLocomotiveMovementComponent* MasterMovement = nullptr;

	// Real-time measurements from the simulation.
	float GravitationalForce = 0.f;
	float TractiveForce = 0.f;
	float GradientForce = 0.f;
	float ResistiveForce = 0.f;
	float BrakingForce = 0.f;
	
	// Velocity of this train [directional] [cm/s]
	UPROPERTY( SaveGame )
	float Velocity = 0.f;

public:
	FORCEINLINE ~FTrainSimulationData() = default;
};

// Delegates for blueprint
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FIsSelfDrivingDelegate, bool, enabled );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDockingStateDelegate, ETrainDockingState, state );

/**
 * The AFGTrain class is concept of multiple rolling stock that is connected in series and move together as one unit.
 * It's responsible for functionality that does not apply to the individual locomotives or rail car.
 * This functionality includes but are not limited to:
 *
 * Time tables, there can only be one time table for the train.
 * Simulation, the physics simulation is per train, the cars are just following the first vehicle.
 * ATC, the automatic train control system
 */
UCLASS( NotBlueprintable, notplaceable )
class FACTORYGAME_API AFGTrain : public AActor, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGTrain();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaSeconds );
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual bool IsLevelBoundsRelevant() const override;
	// End AActor Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	//@todotrains Put stat counters in these.
	void TickAtc( float dt );
	void TickSelfDriving( float dt );

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual float GetSignificanceRange() override;
	// Significance helpers
	FORCEINLINE bool IsSignificant() const { return mIsSignificant; }
	FVector GetSignificanceLocation() const { return mSignificanceLocation; }
	float GetSignificanceRadius() const { return mSignificanceRadius; }
	// End IFGSignificanceInterface

	/** Get the name of this train. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FORCEINLINE FText GetTrainName() const { return mTrainName; }

	/** Get the name of this train, must be called on server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	void SetTrainName( const FText& name );

	/** Get the track for this train. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FORCEINLINE int32 GetTrackGraphID() const { return mTrackGraphID; }

	/** Is this train driven by a player. */
	bool IsPlayerDriven() const;

	/** @return true if the train has the autopilot enabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|SelfDriving" )
	bool IsSelfDrivingEnabled() const;

	/** Enable/disable the autopilot on a train, does nothing if enabled/disabled twice, must be called server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|SelfDriving" )
	void SetSelfDrivingEnabled( bool isEnabled );

	/** Get the self driving error for this locomotive. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|SelfDriving" )
	FORCEINLINE ESelfDrivingLocomotiveError GetSelfDrivingError() const { return mSelfDrivingError; }

	/** @return The master locomotive in the train; nullptr if MU is disabled. */
	class AFGLocomotive* GetMultipleUnitMaster() const;

	/** @return true if we can set the multiple unit master to be the given locomotive without forcing; false if we cannot. */
	bool CanSetMultipleUnitMaster( const class AFGLocomotive* locomotive ) const;

	/**
	 * Set the new master locomotive in the train.
	 * @param trainID The trains ID, if invalid this function does nothing.
	 * @param locomotive The new master or nullptr to disable MU.
	 * @param if true the new master is forced; if false the new master will only be set if MU is disabled (current master is nullptr).
	 * @return true a new master was set or forced; false if not set.
	 */
	bool SetMultipleUnitMaster( class AFGLocomotive* locomotive, bool force );

	/** @return true if input is blocked, e.g. we're docked or self driving is enabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|SelfDriving" )
	bool IsInputDisabled() const;

	/** Get the time table for this train. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadTimeTable* GetTimeTable() const;

	/** Create a new time table for this train. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadTimeTable* NewTimeTable();

	/** If this train has a valid time table. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	bool HasTimeTable() const;

	/** Get the first vehicle in the consist. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadVehicle* GetFirstVehicle() const;

	/** Get the last vehicle in the consist. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadVehicle* GetLastVehicle() const;

	/** Dock this train to the station we're at, must be called on the server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	void Dock();

	/** Get the current status on the docking. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FORCEINLINE ETrainDockingState GetDockingState() const { return mDockingState; }

	/** If this train has docked at a station. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FORCEINLINE bool IsDocked() const { return mDockingState == ETrainDockingState::TDS_Docked; }

	/** Callbacks from the station with regards to docking. */
	void OnDocked( AFGBuildableRailroadStation* station );
	void OnDockingComplete();

	/** Called when the train consist changes so constants can be recalculated. */
	void OnConsistChanged();
private:
	void ReportSelfDrivingError( ESelfDrivingLocomotiveError error );
	void ClearSelfDrivingError();

	/** Try to find a path for this train, in any direction. */
	bool FindPath( class AFGBuildableRailroadStation* station );

	/** Called to set the current docking state. */
	void SetDockingState( ETrainDockingState state );

	/** Called to toggle state for next tick. */
	void GotoSelfDrivingState( ESelfDrivingLocomotiveState newState );

	/** Self driving state handlers. */
	void TickSelfDriving_Idle();
	void TickSelfDriving_FollowPath();
	void TickSelfDriving_Docking();
	void TickSelfDriving_DockingCompleted();

	/** Help functions for speed related calculations. */
	float CalcBrakeDistance( float currentSpeed, float targetSpeed, float deceleration ) const;
	float CalcTargetSpeed( float targetSpeed, float distance, float deceleration ) const;
	float CalcTargetAcceleration( float currentSpeed, float targetSpeed, float distance ) const;
	float CalcTargetDeceleration( float currentSpeed, float targetSpeed, float distance ) const;

	/** On reps */
	UFUNCTION()
	void OnRep_DockingState();
	UFUNCTION()
	void OnRep_IsSelfDrivingEnabled();

public:
	/** Called when the self driving is turn on or off. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Train" )
	FIsSelfDrivingDelegate mOnSelfDrivingChanged;

	/** Called when the docking state changes. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Train" )
	FDockingStateDelegate mOnDockingStateChanged;

public:
	/** Static information about the consist, it changes when rolling stock is added/removed or a container is loaded/unloaded. */
	UPROPERTY()
	FTrainConsist mConsistData;

	/** Runtime data for the automatic train control. See struct for more info. */
	UPROPERTY()
	FTrainAtcData mAtcData;

	//@todotrains This should be simulated on the client as well without the need for replication.
	/** Physics simulation for the train */
	UPROPERTY( SaveGame )
	FTrainSimulationData mSimulationData;

	/** Runtime data for the self driving AI. */
	FTrainSelfDrivingData mSelfDrivingData;

public: //@todotrains private
	/** The name of this train. */
	UPROPERTY( SaveGame, Replicated )
	FText mTrainName;

	/** The track this train is on. */
	UPROPERTY( Replicated )
	int32 mTrackGraphID;

	/** Train are a doubly linked list, use TTrainIterator to iterate over a train. */
	UPROPERTY( SaveGame )
	class AFGRailroadVehicle* FirstVehicle;
	UPROPERTY( SaveGame )
	class AFGRailroadVehicle* LastVehicle;

	/** This is the master locomotives that sends its input (throttle/brake/etc) to all other locomotives in the train. */
	UPROPERTY( Replicated )
	class AFGLocomotive* mMultipleUnitMaster;

	/** This trains time table. */
	UPROPERTY( SaveGame, Replicated )
	class AFGRailroadTimeTable* TimeTable;

	/** Is this train self driving */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsSelfDrivingEnabled )
	bool mIsSelfDrivingEnabled;
	
	/** Error reported by the AI. */
	UPROPERTY( Replicated )
	ESelfDrivingLocomotiveError mSelfDrivingError;

	/** The status for an ongoing dock, this is not saved, it's updated from the station we're docked to on load. */
	UPROPERTY( ReplicatedUsing = OnRep_DockingState )
	ETrainDockingState mDockingState;

	/** How much the brakes decelerate the train. [cm/s^2] */
	float MaxAirBrakeDeceleration;

private:
	/** Sound component controlling all the moving/idle sounds for the train */
	UPROPERTY()
	class UFGRailroadVehicleSoundComponent* mSoundComponent;

	/** Significance data */
	bool mIsSignificant;
	FVector mSignificanceLocation;
	float mSignificanceRadius;
	float mSignificanceRange;

public:
	FORCEINLINE ~AFGTrain() = default;
};
