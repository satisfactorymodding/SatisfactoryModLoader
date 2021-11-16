// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "FGUseableInterface.h"
#include "FGVehicleSubsystem.h"
#include "FGTargetPoint.generated.h"

UCLASS()
class FACTORYGAME_API AFGTargetPoint : public AActor, public IFGSaveInterface, public IFGUseableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGTargetPoint();

	/** Decide on what properties to replicate. */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override {}
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override {}
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override {}
	virtual bool IsUseable_Implementation() const override { return true; }
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override { return FText::FromString( TEXT( "" ) ); }
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {}
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {}
	//~ End IFGUseableInterface

	/** Sets visibility for this point */
	void SetVisibility( bool isVisible );

	/** Returns current wait time */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	float GetWaitTime();

	/** Increase wait time
	 * @param addedWaitTime - if not specified we add the default wait time */
	void IncreaseWaitTime( float addedWaitTime = -1.0f ); 

	/** Sets the wait time
	* @param newWaitTime - time to wait ( seconds ) */
	UFUNCTION( BlueprintCallable, Category = "Target Point" )
	void SetWaitTime( float newWaitTime );

	/** Getter for target speed */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	FORCEINLINE int32 GetTargetSpeed() const { return mTargetSpeed; }

	/** Is target speed low enough to count as still */
	UFUNCTION( BlueprintPure, Category = "Target Point" ) 
	bool IsTargetSpeedStill() const;
	
	/** Invoked when this node has had its target speed changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Target Point" )
	void TargetSpeedChanged();

	/** Sets new target speed */
	void SetTargetSpeed( int32 newSpeed );

	//float GetTargetTime() const;

	/**
	 * The speed in cm/s that was recorded at this target.
	 * Only valid if this target point is used by a vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	FORCEINLINE float GetForwardVelocity() const { return ( float( mTargetSpeed ) + 0.5f ) / 0.036f; }

	/**
	 * The distance along the spline path to this node from the next node in the list.
	 * Only valid if this target point is used by a vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	FORCEINLINE float GetCachedTargetDistance() const { return mCachedTargetDistance; }

	/**
	 * The travel time along the spline path to this node from the first node in the list.
	 * Only valid if this target point is used by a vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	FORCEINLINE float GetCachedTimeToPrevious() const { return mCachedTimeToPrevious; }

	/**
	 * The travel time along the spline path to this node from the next node in the list.
	 * Only valid if this target point is used by a vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "Target Point" )
	FORCEINLINE float GetCachedTargetTime() const { return mCachedTargetTime; }

	UFUNCTION( BlueprintCallable, Category = "Target Point" )
	void SetIsLoopTarget( bool isLoopTarget );

	UFUNCTION( BlueprintPure, Category = "Target Point" )
	bool IsLoopTarget() const { return mIsLoopTarget; }

	/** Invoked when this node is now the target of recording completion */
	UFUNCTION( BlueprintImplementableEvent, Category = "Target Point" )
	void IsLoopTargetChanged();

	UFUNCTION( BlueprintCallable, Category = "Target Point" )
	void SetIsDockingTarget( bool isDockingTarget );

	UFUNCTION( BlueprintPure, Category = "Target Point" )
	bool IsDockingTarget() const { return mIsDockingTarget; }

	/** Invoked when this node is now the target of recording completion */
	UFUNCTION( BlueprintImplementableEvent, Category = "Target Point" )
	void IsDockingTargetChanged();

	UFUNCTION( BlueprintCallable, Category = "Target Point" )
	void SetHostStation( class AFGBuildableDockingStation* hostStation );

	class AFGBuildableDockingStation* GetHostStation() const { return mHostStation.IsValid() ? mHostStation.Get() : nullptr; }

	/** Invoked when this node has had its host station changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Target Point" )
	void HostStationChanged();

	UFUNCTION( BlueprintPure, Category = "Target Point" )
	bool HasHostStation() const { return mHostStation != nullptr; }

	UFUNCTION( BlueprintPure, Category = "Target Point" )
	bool IsTemporary() const;

	void NotifyIsTemporaryChanged();

	/** Invoked when this node has had its temporary status changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Target Point" )
	void IsTemporaryChanged();

	void SetNext( AFGTargetPoint* next );
	AFGTargetPoint* GetNext() const { return mNext; }

	FVector GetDebugPointLocation( float zOffset ) const;

	void SetOwningList( class AFGDrivingTargetList* owningList );
	class AFGDrivingTargetList* GetOwningList() const { return mOwningList; }

	bool TryClaim( class AFGWheeledVehicle* vehicle, TSet< TWeakObjectPtr< class AFGWheeledVehicle > >& blockingVehicles, bool essentialsOnly = false );
	void ForceClaim( class AFGWheeledVehicle* vehicle, bool essentialsOnly = false );
	void Claim( class AFGWheeledVehicle* vehicle, bool recursive, bool essentialsOnly = false );
	void Unclaim( class AFGWheeledVehicle* vehicle );
	void ForceUnclaim();
	void Unclaim( class AFGWheeledVehicle* vehicle, bool recursive );

	bool IsLocked( const class AFGWheeledVehicle* vehicle, TSet< TWeakObjectPtr< class AFGWheeledVehicle > >& blockingVehicles ) const;
	bool IsLockedByDocking( const class AFGWheeledVehicle* vehicle ) const;

	const class AFGWheeledVehicle* GetClaimingVehicle() const { return mClaimingVehicle.IsValid() ? mClaimingVehicle.Get() : nullptr; }

	UFUNCTION( BlueprintPure, Category = "Target Point" )
	bool IsClaimed() const { return mClaimingVehicle != nullptr; }

	/** Invoked when this node is successfully claimed/unclaimed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Target Point" )
	void IsClaimedChanged();

	void DrawTargetDebug( class AFGWheeledVehicle* claimant, bool drawSearchPoints, bool drawSmall );

	UFUNCTION( BlueprintPure, Category = "Target Point" )
	int GetDebugLevel() const;

	void FindBlockingVehicles( class AFGWheeledVehicle* blockedVehicle, TSet< const class AFGWheeledVehicle* >& blockingVehicles ) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#ifdef DEBUG_SELF_DRIVING
	virtual void Tick( float DeltaSeconds );
#endif
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );

private:
	UFUNCTION()
	void OnRep_IsLoopTarget();

	UFUNCTION()
	void OnRep_IsDockingTarget();

	UFUNCTION()
	void OnRep_TargetSpeed();

	UFUNCTION()
	void OnRep_HostStation();

	void UpdateDockingTarget();

public:
	static constexpr float RecordInterval = 1.5f;

	bool mDebugDrawName = false;

	// These cached values will only be valid if this target is in use by a vehicle
	float mCachedTargetDistance = 0.0f;
	float mCachedTimeToPrevious = 0.0f;
	float mCachedTargetTime = 0.0f;
	float mCachedProgressAtPrevious = 0.0f;

private:
	friend class AFGVehicleSubsystem;
	friend class UFGSplinePathMovementComponent;

	UPROPERTY( Transient )
	class AFGDrivingTargetList* mOwningList = nullptr;

	/** Reference to the next target point ( used in linked list ) */
	UPROPERTY( SaveGame, Replicated )
	AFGTargetPoint* mNext;

	/** Accumulated wait time for this node */ 
	UPROPERTY( SaveGame, Replicated )
	float mWaitTime;

	/** Target speed at this node */ 
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_TargetSpeed )
	int32 mTargetSpeed = -1;

	/** Default wait time if this target point has no target speed */
	UPROPERTY( EditDefaultsOnly, Category = "Target Point" ) 
	float mDefaultWaitTime = 3.0f;

	UPROPERTY( ReplicatedUsing = OnRep_IsLoopTarget )
	bool mIsLoopTarget = false;

	UPROPERTY( ReplicatedUsing = OnRep_IsDockingTarget )
	bool mIsDockingTarget = false;

	UPROPERTY( ReplicatedUsing = OnRep_HostStation )
	TWeakObjectPtr< class AFGBuildableDockingStation > mHostStation = nullptr;

	TWeakObjectPtr< class AFGWheeledVehicle > mClaimingVehicle = nullptr;

	bool mIsLookedAt = false;

	// The targets whose lead-up segments are touching the lead-up segment of this target. To be claimed by vehicles moving towards this target.
	TSet< TWeakObjectPtr< AFGTargetPoint > > mCoClaimedTargets;

	// The targets whose lead-up segments are touching this target. To be claimed by vehicles stationary at this target.
	TSet< TWeakObjectPtr< AFGTargetPoint > > mCoClaimedEssentialTargets;

	TArray< FVector > mSearchPoints;

	FVector mSegmentCenter = FVector::ZeroVector;
};	
