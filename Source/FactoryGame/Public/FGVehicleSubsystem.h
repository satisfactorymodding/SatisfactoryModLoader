// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGVehicleSubsystem.generated.h"

#define DEBUG_SELF_DRIVING ( 0 && ( UE_BUILD_SHIPPING == 0 ) )

UCLASS( BlueprintType )
class FACTORYGAME_API AFGSavedWheeledVehiclePath : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGSavedWheeledVehiclePath();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	/** Replication */
	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

protected:
	friend class AFGVehicleSubsystem;

	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly )
	FString mPathName;
	
	/**
	 *  Deprecated, use mTargetList->mVehicleType instead
	 */
	UPROPERTY( SaveGame )
	TSubclassOf< class AFGWheeledVehicle > mOriginalVehicleType;

	/**
	 * The saved path.
	 */
	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly )
	class AFGDrivingTargetList* mTargetList;

	/**
	 * The number of vehicles sharing this path at the moment.
	 */
	UPROPERTY( Replicated, BlueprintReadOnly )
	int mUserCount = 0;

	/**
	 * Are there any vehicles using this path at the moment?
	 */
	UPROPERTY( Replicated, BlueprintReadOnly )
	bool mIsInUse = false;

	/**
	 * The distance from the vehicle currently occupied by the player to the closest node in the path.
	 */
	UPROPERTY( BlueprintReadOnly )
	float mDistanceFromVehicle = 0.0f;

	/**
	 * Is the path in use by the vehicle currently occupied by the player?
	 */
	UPROPERTY( BlueprintReadOnly )
	bool mIsInUseByThisVehicle = false;

	/**
	 * The amount of fuel of type mFuelType ideally consumed by a vehicle in one trip around this path.
	 */
	UPROPERTY( BlueprintReadOnly )
	float mFuelConsumptionPerTrip = 0.0f;

	/**
	 * The fuel type used to express the fuel consumption in mFuelConsumptionPerTrip.
	 */
	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< class UFGItemDescriptor > mFuelType;
};

/**
 * Subsystem for all vehicles, mainly used for wheeled vehicles.
 */
UCLASS( Blueprintable, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGVehicleSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
#if DEBUG_SELF_DRIVING
	static int GetDebugLevel();
	static void SetDebugLevel( int level );
	static int GetDebugTextLevel();
	static void SetDebugTextLevel( int level );
	static int GetVehicleDeadlocksDebug();
	static void SetVehicleDeadlocksDebug( int level );
#endif

	AFGVehicleSubsystem();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	/** Replication */
	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	/** Get the vehicle subsystem, this should always return something unless you call it really early. */
	static AFGVehicleSubsystem* Get( UWorld* world );

	/** Get the vehicle subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Vehicle", DisplayName = "Get Vehicle Subsystem", Meta = (DefaultToSelf = "worldContext") )
	static AFGVehicleSubsystem* Get( UObject* worldContext );

	bool IsInitialized() const { return mIsInitialized; }

	void TickVehicleSimulation( float dt );

	float GetEffectiveSimulationDistance( class AFGVehicle* vehicle );

	/** Find the closest player sq for a creature */
	float FindClosestPlayerSq( class AFGVehicle* actor ) const;

	/**
	 * Adds the  vehicle to the subsystem
	 */
	void AddVehicle( class AFGVehicle* vehicle );

	void AddWheeledVehicle( class AFGWheeledVehicleInfo* vehicle );

	void AddDockingStation( class AFGBuildableDockingStation* station );

	void AddTargetPoint( class AFGTargetPoint* target );

	/**
	 * Removes the  vehicle from the subsystem
	 */
	void RemoveVehicle( class AFGVehicle* vehicle );

	void RemoveWheeledVehicle( class AFGWheeledVehicleInfo* vehicle );

	void RemoveDockingStation( class AFGBuildableDockingStation* station );
	
	/** Removes the desired target from the linked list */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void RemoveTargetPoint( class AFGTargetPoint* targetToRemove, bool updateList = true );

	void InvalidateTargetList( const AFGDrivingTargetList* targetList ) const;

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsPathNameTaken( const FString& name ) const;

	void SaveWheeledVehiclePath( const FString& saveName, class AFGWheeledVehicleInfo* vehicle );

	void UnsaveWheeledVehiclePath( AFGSavedWheeledVehiclePath* path );

	void FindSavedWheeledVehiclePaths( const FString& textFilter, TSubclassOf< class AFGWheeledVehicle > typeFilter, const AFGWheeledVehicleInfo* vehicle, TArray< AFGSavedWheeledVehiclePath* >& result );

	/** Get a reference to the vehicle array */
	const TArray< class AFGVehicle* >& GetVehicles() { return mVehicles; }

	bool IsWheeledVehiclePathInUse( class AFGDrivingTargetList* targetList, const AFGWheeledVehicleInfo* byVehicle = nullptr ) const;
	void CalculateWheeledVehiclePathStatus( class AFGDrivingTargetList* targetList, bool& isSaved, int& userCount ) const;
	int CalculateWheeledVehicleUserCount( class AFGDrivingTargetList* targetList ) const;
	void FindVehiclesUsingPath( const class AFGDrivingTargetList* targetList, TArray< AFGWheeledVehicleInfo* >& result ) const;

	void AddTargetList( class AFGDrivingTargetList* targetList );
	void RemoveTargetList( class AFGDrivingTargetList* targetList );

	UFUNCTION( BlueprintCallable, BlueprintPure = False, Category = "LinkedList" )
	float CalculateStraightDistanceFromPrevious( class AFGTargetPoint* targetPoint ) const;

	void UpdateTargetLists();
	void UpdateTargetList( AFGDrivingTargetList* targetList );
	void UpdateTargetPoints();

	bool IsTheChosenWheeledVehicle( const class AFGWheeledVehicleInfo* vehicle ) const { return mTheChosenWheeledVehicle == vehicle; }
	bool TryToBeTheChosenWheeledVehicle( class AFGWheeledVehicleInfo* vehicle );
	bool TryToResolveEasyDeadlock( class AFGWheeledVehicleInfo* vehicle );
	void ResetBeingTheChosenWheeledVehicle( const class AFGWheeledVehicleInfo* oldChosenVehicle, bool moveToHardDeadlocks );
	class AFGWheeledVehicleInfo* GetTheChosenWheeledVehicle() { return mTheChosenWheeledVehicle; }

	void RemoveDeadlock( int deadlockId );

	void ResetAllDeadlocks();

	void JoinDeadlock( int deadlockId, class AFGWheeledVehicleInfo* vehicle );

	bool HasSavedPaths() const { return mSavedPaths.Num() > 0; }

	/** Called whenever the number of hard deadlocks goes from zero to some */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	void OnThereBeDeadlocks();

private:
	using WheeledVehicleDeadlock = TSet< TWeakObjectPtr< AFGWheeledVehicleInfo > >;
	void AddHardDeadlock( int deadlockId, const WheeledVehicleDeadlock& deadlock );

	void SanitizeDeadlocks();
	void DetectDeadlocks();

	void AssignVehicleTargets();

	void RescueLostVehicles();
	void TryRescueVehicle( class AFGWheeledVehicleInfo* vehicleInfo );

	/**
	 * returns true if blockedVehicle is blocked by sourceVehicle, false otherwise.
	 */
	bool IsVehicleBlockedBySource( const class AFGWheeledVehicleInfo* sourceVehicle, const class AFGWheeledVehicleInfo* blockedVehicle, TSet< const class AFGWheeledVehicleInfo* >& visitedVehicles, TSet< class AFGWheeledVehicleInfo* >& deadlockedVehicles );

public:
	int mWheeledVehicleCount = 0;
	int mLoadedTargetPointCount = 0;

private:
	/** How many vehicles can we iterate over per tick */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	int32 mMaxVehicleIterationsPerTick;

	/** Iterator for current index in the vehicle array */
	int32 mVehicleIterator;

	/** All the vehicles in the world. */
	UPROPERTY()
	TArray< class AFGVehicle* > mVehicles;

	/** All the wheeled vehicles in the world. */
	UPROPERTY( Replicated )
	TArray< class AFGWheeledVehicleInfo* > mWheeledVehicles;

	/** All the docking stations in the world. */
	UPROPERTY()
	TArray< class AFGBuildableDockingStation* > mDockingStations;

	/**
	 * All the paths that are saved by players
	 */
	UPROPERTY( SaveGame, Replicated )
	TArray< AFGSavedWheeledVehiclePath* > mSavedPaths;

	/**
	 * Is this subsystem ready to use yet?
	 */
	bool mIsInitialized = false;

	/**
	 * All the paths that exist.
	 */
	TArray< AFGDrivingTargetList* > mTargetLists;

	/**
	 * All the target points placed in the world.
	 */
	TArray< AFGTargetPoint* > mTargetPoints;

	/**
	 * This is one lucky guy who is allowed to drive with only a limited set of targets claimed.
	 * The conditions for this are
	 * A) that no other vehicles are presently blocking his immediate path section and
	 * B) that he is using this to get out of a deadlock.
	 * 
	 * TODO: if we partition all the paths into non-overlapping path groups, we may have one chosen vehicle per path group
	 */
	UPROPERTY()
	AFGWheeledVehicleInfo* mTheChosenWheeledVehicle;

	using DeadlockMap = TMap< int, WheeledVehicleDeadlock >;
	/**
	 * Map to all deadlocks that have been detected, but have not yet been checked if an automatic resolution can be found for them.
	 */
	DeadlockMap mDeadlocks;
	/**
	 * Map to all deadlocks that have been deemed not automatically resolvable.
	 */
	DeadlockMap mHardDeadlocks;

	int mDeadlockIdCounter = 0;
	int mResolvedEasyDeadlockCount = 0;

	/**
	 * Is deadlock-detection presently enabled?
	 */
	bool mMayDoDeadlockDetection = false;

	/**
	 * The index into mWheeledVehicles of the vehicle that is currently being checked if it's lost. Lost meaning hovering somewhere under the landscape.
	 */
	int mLostVehicleCandidateIndex = 0;

	/**
	 * The earliest time when the next deadlock-warning message can be displayed. To avoid message spamming.
	 */
	float mEarliestDeadlockWarningTime = -BIG_NUMBER;

#if DEBUG_SELF_DRIVING
	float mDebugSimulationDistance = 0.0f;
	bool mIncreaseDebugSimulationDistance = false;
#endif
};
