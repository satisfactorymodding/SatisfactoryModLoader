// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"
#include "TextProperty.h"
#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGTrain.generated.h"


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
 * Describes the static properties of a train consist.
 * I.e. the locomotives, railcars, length and tare weight.
 */
USTRUCT( BlueprintType )
struct FTrainConsist
{
GENERATED_BODY()
public:
	//@todo Add vehicles and their orientation here.
	//@todo Static information about the train, length, light weight, max gross weight
};


/**
 * The physics simulation data for the trains.
 */
USTRUCT()
struct FTrainSimulationData
{
	GENERATED_BODY()
public:
	/** Is this train simulating physics */
	bool IsSimulating = false;

	/** Cached vehicles in the direction of travel. */
	UPROPERTY()
	TArray< class AFGRailroadVehicle* > SimulatedVehicles;

	/** Cached movements in the same order as the vehicles. */
	UPROPERTY()
	TArray< class UFGRailroadVehicleMovementComponent* > SimulatedMovements;

	/** Cached master locomotive. */
	UPROPERTY()
	class UFGLocomotiveMovementComponent* MasterMovement = nullptr;

	//@todotrains These change only when the consist changes.
	float Mass = 0.f;
	float MinBrakingEffort = 0.f;

	// Real-time measurements from the simulation.
	float TractiveForce = 0.f;
	float GradientForce = 0.f;
	float ResistiveForce = 0.f;
	float BrakingForce = 0.f;

	// The resulting velocity and momentum of the train.
	float Momentum = 0.f;
	float Velocity = 0.f;
};

/**
 * A train, a grouping of locomotives and railcars.
 */
UCLASS()
class FACTORYGAME_API AFGTrain : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGTrain();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Destroyed() override;
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

	/** Get the name of this train. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	FText GetTrainName() const { return mTrainName; }

	/** Get the name of this train, must be called on server. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	void SetTrainName( const FText& name );

	/** Get the track for this train. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	int32 GetTrackGraphID() const { return TrackGraphID; }

	/** @return true if the train has the autopilot enabled. */
	bool IsSelfDrivingEnabled() const;

	/** Enable/disable the autopilot on a train, does nothing if enabled/disabled twice. */
	void SetSelfDrivingEnabled( bool isEnabled );

	/** Get the self driving error for this locomotive. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|SelfDriving" )
	ESelfDrivingLocomotiveError GetSelfDrivingError() const { return mSelfDrivingError; }

	/** @return The master locomotive in the train; nullptr if MU is disabled. */
	class AFGLocomotive* GetMultipleUnitMaster() const;

	/** @return true if we can set the multiple unit master to be the given locomotive without forcing; false if we cannot. */
	bool CanSetTrainMultipleUnitMaster( const class AFGLocomotive* locomotive ) const;

	/**
	 * Set the new master locomotive in the train.
	 * @param trainID The trains ID, if invalid this function does nothing.
	 * @param locomotive The new master or nullptr to disable MU.
	 * @param if true the new master is forced; if false the new master will only be set if MU is disabled (current master is nullptr).
	 * @return true a new master was set or forced; false if not set.
	 */
	bool SetTrainMultipleUnitMaster( class AFGLocomotive* locomotive, bool force );

	/** Get the time table for this train. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadTimeTable* GetTimeTable() const;

	/** Create a new time table for this train. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadTimeTable* NewTimeTable();

	/** Get the first vehicle in the consist. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadVehicle* GetFirstVehicle() const;

	/** Get the last vehicle in the consist. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	class AFGRailroadVehicle* GetLastVehicle() const;

	/** Set whether or not this train is docked */
	void SetIsDocked( bool isDocked );

	/** Get if this train is docked at a station */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	bool GetIsDocked() const { return mIsDocked; }

	/** Get the maximum braking power of the consist. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Train" )
	float GetMaxAirBrakeDeceleration() const { return MaxAirBrakeDeceleration; }

public:
	/** Physics simulation for the train */ //@todotrains This should be simulated on the client as well without the need for replication.
	UPROPERTY()
	FTrainSimulationData mSimulationData;

public: //@todotrains private
	//@todotrains Rename m

	/** The name of this train. */
	UPROPERTY( SaveGame, Replicated )
	FText mTrainName;

	/** The track this train is on. */
	UPROPERTY( Replicated )
	int32 TrackGraphID;

	/** Train are a doubly linked list, use TTrainIterator to iterate over a train. */
	UPROPERTY( SaveGame )
	class AFGRailroadVehicle* FirstVehicle;
	UPROPERTY( SaveGame )
	class AFGRailroadVehicle* LastVehicle;

	/** This is the master locomotives that sends its input (throttle/brake/etc) to all other locomotives in the train. */
	UPROPERTY( Replicated )
	class AFGLocomotive* MultipleUnitMaster;

	/** Is this train self driving */
	UPROPERTY( Replicated )
	bool mIsSelfDrivingEnabled;
	
	/** Error reported by the AI. */
	UPROPERTY( Replicated )
	ESelfDrivingLocomotiveError mSelfDrivingError;

	/** This trains time table. */
	UPROPERTY( SaveGame, Replicated )
	class AFGRailroadTimeTable* TimeTable;

	/** Is this train docked at a station */
	UPROPERTY( SaveGame, Replicated )
	bool mIsDocked;

	/** How much the brakes decelerate the train. [cm/s^2] */
	float MaxAirBrakeDeceleration;
};
