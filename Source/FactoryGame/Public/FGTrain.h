// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGRailroadSubsystem.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "RailroadNavigation.h"
#include "FGTrainDockingRules.h"
#include "FGTrain.generated.h"


class UFGRailroadTrackConnectionComponent;


/**
 * Error codes for the self driving locomotives.
 */
UENUM( BlueprintType )
enum class ESelfDrivingLocomotiveError : uint8
{
	SDLE_NoError							UMETA( DisplayName = "No Error" ),
	SDLE_NoPower							UMETA( DisplayName = "No Power" ),
	SDLE_NoTimeTable						UMETA( DisplayName = "No Time Table" ),
	SDLE_InvalidNextStop					UMETA( DisplayName = "Invalid Next Stop" ),
	SDLE_InvalidLocomotivePlacement			UMETA( DisplayName = "Invalid Locomotive Placement" ),
	SDLE_NoPath								UMETA( DisplayName = "No Path" ),
	SDLE_StationUnreachable					UMETA( DisplayName = "Station Unreachable" ),
	SDLE_StationUnreachableWithSignals		UMETA( DisplayName = "Station Unreachable With Signals" ),
	SDLE_LongWaitAtSignal					UMETA( DisplayName = "Long Wait At Signal" ),
};

/**
 * Signal aspects used for signaling and ATC points.
 */
UENUM( BlueprintType )
enum class ERailroadSignalAspect : uint8
{
	RSA_None			UMETA( DisplayName = "None" ),
	RSA_Clear			UMETA( DisplayName = "Clear" ),
	RSA_Stop			UMETA( DisplayName = "Stop" ),
	RSA_Dock			UMETA( DisplayName = "Dock" )
	//RSA_Reserved		UMETA( DisplayName = "Reserved" )
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

/**
 * Error codes for the extended path finding diagnostics.
 */
UENUM( BlueprintType )
enum class EPathDiagnosticsError : uint8
{
	PDE_NoError							UMETA( DisplayName = "No Error" ),
	PDE_StationUnreachable				UMETA( DisplayName = "Station Unreachable" ),
	PDE_StationUnreachableWithSignals	UMETA( DisplayName = "Station Unreachable With Signals" )
};

/**
 * Status of this train, used by the UI and map.
 */
UENUM( BlueprintType )
enum class ETrainStatus : uint8
{
	TS_Parked							UMETA( DisplayName = "Parked" ),
	TS_ManualDriving					UMETA( DisplayName = "Manual Driving" ),
	TS_SelfDriving						UMETA( DisplayName = "Self Driving" ),
	TS_Derailed							UMETA( DisplayName = "Derailed" )
};

/** Global constants for trains. */
struct FACTORYGAME_API TrainConstants
{
	// At which distance can a station start catching the train. [cm]
	static float CATCH_DISTANCE;
	// At which offset should a locomotive stop at a station. [cm]
	static float DOCK_STOP_OFFSET;
	// At which offset should a locomotive stop at a signal. [cm]
	static float SIGNAL_STOP_OFFSET;
	// At which distance a locomotive can dock to a station. [cm]
	static float DOCK_DISTANCE;
	// At which speed is docking allowed. [cm/s]
	static float DOCK_SPEED;
	// This is the speed on a restricted section, e.g. before docking. [cm/s]
	static float RESTRICTED_SPEED;
	// This is the distance before a restricted section we should apply the restricted speed. [cm]
	static float RESTRICTED_SPEED_DISTANCE;
	// This is the distance rolling stock needs to be to a switch to de considered occupied.
	static float SWITCH_FACING_OCCUPY_DISTANCE;
	static float SWITCH_TRAILING_OCCUPY_DISTANCE;
	// This is the distance that we can toggle a switch from, both player and self driver.
	static float SWITCH_INTERACTION_DISTANCE;
	// What is the minimum speed for a train to derail during a collision.
	static float MIN_SPEED_FOR_DERAILMENT;
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
	float MaxTractiveEffort = 0.f;
	float MaxAirBrakingEffort = 0.f;
	float MaxDynamicBrakingEffort = 0.f;
	float MaxBrakeDeceleration = 0.f;
	float MaxBrakeDistance = 0.f;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTrainAtcPoint
{
	GENERATED_BODY()
public:
	/** The track connection. */
	UPROPERTY()
	UFGRailroadTrackConnectionComponent* TrackConnection = nullptr;

	/** Path segment for this point, if none, we do not have a path. */
	int32 PathSegment = INDEX_NONE;
	
	/** How far away is this point in whole segments. */
	float LongDistance = 0.f;

	/** How far away is this point. */
	float Distance = 0.f;

	/** How high up is this. */
	float AverageGrade = 0.f;

	/** The speed the train should have when passing this point. No limit if 0. */
	float SpeedLimit = 0.f;

	/** Is this connection our goal. */
	bool IsGoal = false;

	/** Signal output at this point. If any. */
	ERailroadSignalAspect SignalAspect = ERailroadSignalAspect::RSA_None;
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
	
	/**
	 * Update the target points ahead from the current connection.
	 * @return true on success; false if the target points failed to update, in which case the result is not valid.
	 */
	bool AdvanceTargetPoints( UFGRailroadTrackConnectionComponent* current );

	/**
	 * Function to update which path segment we're on based on what our current connection is up ahead.
	 * @return true on success; false if we could not find where along the path we are.
	 */
	bool AdvanceCurrentPathSegment( UFGRailroadTrackConnectionComponent* current );
	
	/**
	 * Function to poll the latest data into the target points, from signals, stations etc.
	 * @param currentPathSegmentOffset - How far have we travelled on the current segment.
	 * @return true on success; false if an invalid target point was found and the polling was cancelled.
	 */
	bool RefreshTargetPointsDistanceAndAspect( float currentPathSegmentOffset );

	/** Updates the next signal with the next red signal within the search distance. */
	void UpdateNextSwitch( float searchDistance );

	/** Updates the next restrictive signal with the closest signal within the search distance that shows a restrictive aspect. */
	void UpdateNextRestrictiveSignal( float searchDistance );

	/** Updates the next signal with the closest signal within the search distance. */
	void UpdateNextSignal( float searchDistance );
	
	/** If a connection is relevant for controlling the train. */
	static bool IsRelevantForATC( const UFGRailroadTrackConnectionComponent* connection );
public:
	/** The route this train should follow. */
	FRailroadPathSharedPtr Path;
	/** Index of the next point along the route. */
	int32 CurrentPathSegment = INDEX_NONE;
	/** Last error for the pat diagnostic run, this is reset on a successful path find. */
	EPathDiagnosticsError PathDiagnosticsError = EPathDiagnosticsError::PDE_NoError;
	
	/** The next connection up ahead. */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > CurrentConnection = nullptr;
	float CurrentConnectionDistance = 0.f;

	/**
	 * Connection points ahead we'll pass on our way forward and the distance to them.
	 * Does not contain a point that is only a pass-through (not relevant).
	 */
	UPROPERTY()
	TArray< FTrainAtcPoint > TargetPoints;

	//@todo-trains Are these kept up to date when the player is driving?
	/** Speed and distance indicators. */
	float CurrentSpeed = 0.f;
	float TargetSpeed = 0.f;
	float BrakeDistance = 0.f;

	/**
	 * Next upcoming signal that restricts our speed, e.g. a station we should dock to or a red signal.
	 * This is not necessarily the first signal that appears in target points but rather the closest one restricting our speed.
	 */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > NextRestrictiveSignalConnection = nullptr;
	//int32 NextRestrictiveSignalPathSegment = INDEX_NONE;
	float NextRestrictiveSignalSpeed = 0.f;
	float NextRestrictiveSignalDistance = 0.f;
	float NextRestrictiveSignalGrade = 0.f; // [%]
	ERailroadSignalAspect NextRestrictiveSignalAspect = ERailroadSignalAspect::RSA_None;
	
	/**
	 * Next upcoming signal, this is the closest signal up ahead.
	 */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > NextSignalConnection = nullptr;
	int32 NextSignalPathSegment = INDEX_NONE;
	float NextSignalDistance = 0.f;
	ERailroadSignalAspect NextSignalAspect = ERailroadSignalAspect::RSA_None;
	
	/**
	 * Next upcoming switch.
	 */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > NextSwitchConnection = nullptr;
	float NextSwitchDistance = 0.f;
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

	/** When did we find this path. */
	float TimeOfLastFindPath = 0.0f;

	/** If the last speed was up or down or none. */
	int8 LastSpeedControl = 0;

	/** How much time have we spend waiting on the current signal. */
	float TimeWaitingAtSignal = 0.f;
};


/**
 * The physics simulation data for the trains.
 */
USTRUCT()
struct FACTORYGAME_API FTrainSimulationData
{
	GENERATED_BODY()
public:
	/**
	 * Server: Cached vehicles in the direction of travel.
	 * Client: Cached relevant vehicles, unordered.
	 */
	UPROPERTY()
	TArray< class AFGRailroadVehicle* > SimulatedVehicles;

	/**
	 * Server: Cached movements in the same order as the vehicles.
	 * Client: Empty.
	 */
	UPROPERTY()
	TArray< class UFGRailroadVehicleMovementComponent* > SimulatedMovements;

	/** The approximated location and bounds for the vehicles combined. (Server and Client) */
	FVector TrainLocation = FVector::ZeroVector;
	float TrainBound = 0.f;

	/** Cached master locomotive. (Server and Client) */
	UPROPERTY()
	class UFGLocomotiveMovementComponent* MasterMovement = nullptr;

	// Real-time measurements from the simulation. (Server Only)
	float GravitationalForce = 0.f;
	float TractiveForce = 0.f;
	float GradientForce = 0.f;
	float ResistiveForce = 0.f;
	float AirBrakingForce = 0.f;
	float DynamicBrakingForce = 0.f;
	
	// Velocity of this train [directional] [cm/s] (Server Only)
	UPROPERTY( SaveGame )
	float Velocity = 0.f;
	
	/** If >= 0 we want to be caught at that distance from the next connection. (Server Only) */
	float CatchAtConnectionDistance = -1.f;
};

/**
 * Struct containing quantized train stats for the client.
 */
USTRUCT()
struct FClientTrainData
{
	GENERATED_BODY()
public:
	/** The train speed [cm/s], valid input range is [0,4000], values outside this range will be clamped. */
	void SetForwardSpeed( float speed );
	float GetForwardSpeed();

	/** The traction in percent. [0,1] */
	void SetTractionPct( float pct );
	float GetTractionPct();

	/** The air brake in percent. [0,1] */
	void SetAirBrakePct( float pct );
	float GetAirBrakePct();

	/** The dynamic brake in percent. [0,1] */
	void SetDynamicBrakePct( float pct );
	float GetDynamicBrakePct();

private:
	UPROPERTY()
	uint32 PackedData = 0;
};

// Delegates for blueprint
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FIsSelfDrivingDelegate, bool, enabled );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDockingStateDelegate, ETrainDockingState, state );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSelfDrivingErrorDelegate, ESelfDrivingLocomotiveError, error );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FTrainStatusDelegate, ETrainStatus, status );


/**
 * The AFGTrain class is concept of multiple rolling stock that is connected in series and move together as one unit.
 * It's responsible for functionality that does not apply to the individual locomotives or rail car.
 * This functionality includes but are not limited to:
 *
 * Time tables, there can only be one time table for the train.
 * Simulation, the physics simulation is per train, the cars are just following the first vehicle.
 * ATC, the automatic train control system
 */
UCLASS( notplaceable )
class FACTORYGAME_API AFGTrain : public AActor, public IFGSaveInterface, public IFGSignificanceInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGTrain();

	/**
	 * Use this to initialize the train or reinitialize the train on decoupling.
	 * @param firstVehicle, lastVehicle Vehicles in the train, both must be valid.
	 */
	void Initialize( class AFGRailroadVehicle* firstVehicle, class AFGRailroadVehicle* lastVehicle );

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( float dt ) override;
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
	
	void TickAtc( float dt );
	void TickSelfDriving( float dt );
	void TickPlayerDriving( float dt );

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

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText( const FText& newText ) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	// End IFGActorRepresentationInterface

	/** Get the name of this train. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FText GetTrainName() const { return mTrainName; }

	/** Get the name of this train, must be called on server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	void SetTrainName( const FText& name );

	/** Get the track graph this train is operating on. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	int32 GetTrackGraphID() const { return mTrackGraphID; }

	/** Set this train on a new track graph and update data related to that. */
	void SetTrackGraphID( int32 newID );

	/** Is this train driven by a player. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	bool IsPlayerDriven() const;

	/** @return true if the train has the autopilot enabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|SelfDriving" )
	bool IsSelfDrivingEnabled() const;

	/** Enable/disable the autopilot on a train, does nothing if enabled/disabled twice, must be called server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|SelfDriving" )
	void SetSelfDrivingEnabled( bool isEnabled );

	/** Get the self driving error for this locomotive. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|SelfDriving" )
	ESelfDrivingLocomotiveError GetSelfDrivingError() const { return mSelfDrivingError; }

	/** @return The master locomotive in the train; nullptr if MU is disabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
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
	ETrainDockingState GetDockingState() const { return mDockingState; }

	/** If this train has docked at a station. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	bool IsDocked() const { return mDockingState == ETrainDockingState::TDS_Docked; }

	/**
	 * Cancels a docking sequence. This will not immediately cancel if a load/unload animation is running
	 * This will clear any wait requirements
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	void CancelDockingSequence();

	/** True if the player has requested a docking sequence to cancel */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	bool IsDockingCancelRequested();

	/** Callbacks from the station with regards to docking. */
	void OnDocked( AFGBuildableRailroadStation* station );
	void OnDockingComplete();

	/** Connect this train to the third rail given. */
	void ConnectToThirdRail( class UFGPowerConnectionComponent* thirdRail );
	
	/** Called when the vehicles in the train are changed so it can reconnect to the third rail etc. */
	void OnVehiclesChanged();

	/** Called when the train consist changes so constants can be recalculated. */
	void OnConsistChanged();

	/** Gets the rules for docking from this trains time table for its current stop */
	void GetDockingRuleSetForCurrentStop( FTrainDockingRuleSet& out_ruleSet ) const;

	/** Called when we collide with some other train. */
	void OnCollided( AFGRailroadVehicle* ourVehicle, float ourVelocity, AFGRailroadVehicle* otherVehicle, float otherVelocity, bool shouldDerail );
	
	/** Called when this train is derailed as a consequence of a collision. */
	void OnDerail( float velocity );
	
	/** @return true if the train is derailed and cannot move, otherwise false. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FORCEINLINE bool IsDerailed() const { return mIsDerailed; }

	/** @return true if the train has a pending collision. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	bool HasPendingCollision() const { return mHasPendingCollision; }

	/** Put the train back on track, if the train is not derailed, this does nothing. */
	void Rerail();

	/** Called by a locomotive when someone enters exits a locomotive. This is called even if someone is entering a self driving locomotive. */
	void OnDriverEntered();
	void OnDriverLeft();

	/** @return status for this train. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FORCEINLINE ETrainStatus GetTrainStatus() const { return mTrainStatus; }

	/** Add or remove a vehicle locally, used on client to know about the vehicles in the train. */
	void AddLocalVehicle( class AFGRailroadVehicle* vehicle );
	void RemoveLocalVehicle( class AFGRailroadVehicle* vehicle );

protected:
	/** Get the icon to show for this train on the map and compass. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Train" )
	class UTexture2D* GetActorRepresentationTextureInternal() const;

	/** Get the color to show for this train on the map and compass. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Train" )
	FLinearColor GetActorRepresentationColorInternal() const;
	
private:
	/** Updates the train status by consolidating the rest of the trains state. */
	void UpdateTrainStatus();
	
	/** Functions to handle the self driving errors. */
	void ReportSelfDrivingError( ESelfDrivingLocomotiveError error );
	void ClearSelfDrivingError();

	/** Try to find a path for this train, in any direction. */
	bool FindPath( class AFGBuildableRailroadStation* station, bool runDiagnosticsOnFailure );

	/** Update the ready to dock state. ATC must be updated prior to calling this. */
	void UpdateReadyToDock();
	/** Called to set the current docking state. */
	void SetDockingState( ETrainDockingState state );

	/** Called to toggle state for next tick. */
	void GotoSelfDrivingState( ESelfDrivingLocomotiveState newState );

	/** Self driving state handlers. */
	void TickSelfDriving_Idle( ESelfDrivingLocomotiveError& out_error );
	void TickSelfDriving_FollowPath( ESelfDrivingLocomotiveError& out_error );
	void TickSelfDriving_Docking( ESelfDrivingLocomotiveError& out_error );
	void TickSelfDriving_DockingCompleted( ESelfDrivingLocomotiveError& out_error );

	/** Atc tick handlers. */
	void TickAtc_BlockReservations();

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
	UFUNCTION()
	void OnRep_SelfDrivingError();
	UFUNCTION()
	void OnRep_IsDerailed();
	UFUNCTION()
	void OnRep_TrainStatus();
	
#if WITH_CHEATS
	void Cheat_Teleport( class AFGBuildableRailroadStation* station );
#endif

public:
	/** Called when the self driving is turn on or off. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Train" )
	FIsSelfDrivingDelegate mOnSelfDrivingChanged;

	/** Called when the docking state changes. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Train" )
	FDockingStateDelegate mOnDockingStateChanged;

	/** Called when the self driver encounters and error. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Train" )
	FSelfDrivingErrorDelegate mOnSelfDrivingErrorChanged;
	
	/**
	 * Called when the state of the train changes
	 * This is also called when a sub event is triggered, such as self driving errors.
	 */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Railroad|Train" )
	FTrainStatusDelegate mOnTrainStatusChanged;

public:
	/** This is component used to play sounds on the train. */
	UPROPERTY( EditDefaultsOnly, Category = "Train|Sound" )
	TSubclassOf< class UFGTrainSoundComponent > mSoundComponentClass;
	
	/** Static information about the consist, it changes when rolling stock is added/removed or a container is loaded/unloaded. */
	UPROPERTY()
	FTrainConsist mConsistData;

	/** Runtime data for the automatic train control. See struct for more info. */
	UPROPERTY()
	FTrainAtcData mAtcData;
	
	/** Physics simulation for the train */
	UPROPERTY( SaveGame )
	FTrainSimulationData mSimulationData;

	/** Runtime data for the self driving AI. */
	FTrainSelfDrivingData mSelfDrivingData;

	/** Train data that is available on the client. */
	UPROPERTY( Replicated )
	FClientTrainData mClientTrainData;

public: //@todo-trains private
	/** The name of this train. */
	UPROPERTY( SaveGame, Replicated, VisibleAnywhere, Category = "Train" )
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
	UPROPERTY( SaveGame, Replicated, VisibleAnywhere, Category = "Train" )
	class AFGRailroadTimeTable* TimeTable;

	/** This is the trains current status. */
	UPROPERTY( ReplicatedUsing = OnRep_TrainStatus, VisibleAnywhere, Category = "Train" )
	ETrainStatus mTrainStatus;

	/** Is this train self driving */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsSelfDrivingEnabled, VisibleAnywhere, Category = "Train" )
	bool mIsSelfDrivingEnabled;
	
	/** Error reported by the self driver. */
	UPROPERTY( ReplicatedUsing = OnRep_SelfDrivingError, VisibleAnywhere, Category = "Train" )
	ESelfDrivingLocomotiveError mSelfDrivingError;

	/** How long do the train need to wait at a signal before "Long Wait At Signal" is raised. [seconds] */
	UPROPERTY( EditDefaultsOnly, Category = "Train" )
	float mLongWaitAtSignalThreshold;

	/** The status for an ongoing dock, this is not saved, it's updated from the station we're docked to on load. */
	UPROPERTY( ReplicatedUsing = OnRep_DockingState, VisibleAnywhere, Category = "Train" )
	ETrainDockingState mDockingState;

	/** The station this train is docked at. This is now cached when docked as we needed a means to Cancel a dock sequence from the UI Train menu */
	UPROPERTY( VisibleAnywhere, Category = "Train" )
	class AFGBuildableRailroadStation* mDockedAtStation;

	/** True if this train is derailed and needs player attention. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsDerailed, VisibleAnywhere, Category = "Train" )
	bool mIsDerailed;

	//@todo-trains Apply from pending collisions in subsystem on load.
	bool mHasPendingCollision;

private:
	/** Sound component controlling all the moving/idle sounds for the train */
	UPROPERTY()
	class UFGTrainSoundComponent* mSoundComponent;

	/** Significance data */
	bool mIsSignificant;
	FVector mSignificanceLocation;
	float mSignificanceRadius;
	float mSignificanceRange;
};
