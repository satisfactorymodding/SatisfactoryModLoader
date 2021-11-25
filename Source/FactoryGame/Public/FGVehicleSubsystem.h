// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGVehicleSubsystem.generated.h"

#if WITH_EDITOR
#define DEBUG_SELF_DRIVING
#endif

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

	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly )
	class AFGDrivingTargetList* mTargetList;

	UPROPERTY( Replicated, BlueprintReadOnly )
	int mUserCount = 0;

	UPROPERTY( Replicated, BlueprintReadOnly )
	bool mIsInUse = false;

	UPROPERTY( BlueprintReadOnly )
	float mDistanceFromVehicle = 0.0f;

	UPROPERTY( BlueprintReadOnly )
	bool mIsInUseByThisVehicle = false;

	UPROPERTY( BlueprintReadOnly )
	float mFuelConsumptionPerTrip = 0.0f;

	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< class UFGItemDescriptor > mFuelType;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGVehicleSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
#ifdef DEBUG_SELF_DRIVING
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

	void AddWheeledVehicle( class AFGWheeledVehicle* vehicle );

	void AddDockingStation( class AFGBuildableDockingStation* station );

	void AddTargetPoint( class AFGTargetPoint* target );

	/**
	 * Removes the  vehicle from the subsystem
	 */
	void RemoveVehicle( class AFGVehicle* vehicle );

	void RemoveWheeledVehicle( class AFGWheeledVehicle* vehicle );

	void RemoveDockingStation( class AFGBuildableDockingStation* station );
	
	/** Removes the desired target from the linked list */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void RemoveTargetPoint( class AFGTargetPoint* targetToRemove, bool updateList = true );

	void InvalidateTargetList( const AFGDrivingTargetList* targetList ) const;

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsPathNameTaken( const FString& name ) const;

	void SaveWheeledVehiclePath( const FString& saveName, class AFGWheeledVehicle* vehicle );

	void UnsaveWheeledVehiclePath( AFGSavedWheeledVehiclePath* path );

	void FindSavedWheeledVehiclePaths( const FString& textFilter, TSubclassOf< class AFGWheeledVehicle > typeFilter, const AFGWheeledVehicle* vehicle, TArray< AFGSavedWheeledVehiclePath* >& result );

	/** Get a reference to the vehicle array */
	const TArray< class AFGVehicle* >& GetVehicles() { return mVehicles; }

	bool IsWheeledVehiclePathInUse( class AFGDrivingTargetList* targetList, const AFGWheeledVehicle* byVehicle = nullptr ) const;
	void CalculateWheeledVehiclePathStatus( class AFGDrivingTargetList* targetList, bool& isSaved, int& userCount ) const;
	int CalculateWheeledVehicleUserCount( class AFGDrivingTargetList* targetList ) const;
	void FindVehiclesUsingPath( const class AFGDrivingTargetList* targetList, TArray< AFGWheeledVehicle* >& result ) const;

	void AddTargetList( class AFGDrivingTargetList* targetList );
	void RemoveTargetList( class AFGDrivingTargetList* targetList );

	UFUNCTION( BlueprintCallable, BlueprintPure = False, Category = "LinkedList" )
	float CalculateStraightDistanceFromPrevious( class AFGTargetPoint* targetPoint ) const;

	void UpdateTargetLists();
	void UpdateTargetList( AFGDrivingTargetList* targetList );
	void UpdateTargetPoints();

	//void OnArrivedAtTarget( class AFGTargetPoint* target, class AFGWheeledVehicle* vehicle, const FVector& location );

	void FindTouchedTargets( const class USplineComponent* path, float segmentLength, float progresStart, float collisionAvoidanceDistance, TSet< TWeakObjectPtr< class AFGTargetPoint > >& claimTargets, TSet< TWeakObjectPtr< class AFGTargetPoint > >& essentialClaimTargets, TArray< FVector >& searchPoints, FVector& segmentCenter, class AFGWheeledVehicle* claimingVehicle );

	bool IsTheChosenWheeledVehicle( const class AFGWheeledVehicle* vehicle ) const { return mTheChosenWheeledVehicle == vehicle; }
	bool TryToBeTheChosenWheeledVehicle( class AFGWheeledVehicle* vehicle, const TArray< FVector >& searchPoints, FVector& segmentCenter, TSet< TWeakObjectPtr< class AFGWheeledVehicle > >& blockingVehicles );
	void ResetTheChosenWheeledVehicle( const class AFGWheeledVehicle* oldChosenVehicle );
	class AFGWheeledVehicle* GetTheChosenWheeledVehicle() { return mTheChosenWheeledVehicle; }

	void OnResetIsDeadlocked( const class AFGWheeledVehicle* vehicle );

	void ResetAllDeadlocks();

private:
	void AssignVehicleTargets();
	void DetectDeadlocks();

	void RescueLostVehicles();
	void TryRescueVehicle( class AFGWheeledVehicle* vehicle );

	/**
	 * if the vehicle is indirectly blocking itself, returns the number of indirections involved in that blocking
	 */
	int IsVehicleBlockingItself( const class AFGWheeledVehicle* sourceVehicle, const class AFGWheeledVehicle* blockedVehicle, TSet< const class AFGWheeledVehicle* >& visitedVehicles );

public:
	int mWheeledVehicleCount = 0;
	int mLoadedTargetPointCount = 0;

	bool mGiveClaimPriorityToTheChosenOne = false;

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
	UPROPERTY()
	TArray< class AFGWheeledVehicle* > mWheeledVehicles;

	/** All the docking stations in the world. */
	UPROPERTY()
	TArray< class AFGBuildableDockingStation* > mDockingStations;

	UPROPERTY( SaveGame, Replicated )
	TArray< AFGSavedWheeledVehiclePath* > mSavedPaths;

	bool mIsInitialized = false;

	TArray< class AFGDrivingTargetList* > mTargetLists;

	TArray< class AFGTargetPoint* > mTargetPoints;

	/**
	 * This is one lucky guy who is allowed to drive with only a limited set of targets claimed.
	 * The conditions for this are
	 * A) that no other vehicles are presently blocking his immediate path section and
	 * B) that he is using this to get out of a deadlock.
	 * 
	 * TODO: if we partition all the paths into non-overlapping path groups, we may have one chosen vehicle per path group
	 */
	class AFGWheeledVehicle* mTheChosenWheeledVehicle;

	TSet< class AFGWheeledVehicle* > mDeadlockedEasyCandidates;
	TSet< class AFGWheeledVehicle* > mDeadlockedHardOnes;
	int mResolvedEasyDeadlockCount = 0;

	bool mMayDoDeadlockDetection = false;

	int mLostVehicleCandidateIndex = 0;

#ifdef DEBUG_SELF_DRIVING
	float mDebugSimulationDistance = 0.0f;
	bool mIncreaseDebugSimulationDistance = false;
#endif
};
