// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGInstancedSplineMeshComponent.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableJumppad.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTrajectoryData
{
	GENERATED_BODY()

	FVector ImpactLocation;
	float PeakHeight;
	TArray<FVector> TrajectoryPoints;
};

struct FACTORYGAME_API TrackedJumpPadPlayer
{
	TrackedJumpPadPlayer( class AFGCharacterPlayer* PlayerToTrack, float InitialTimeStamp )
		: pPlayer( PlayerToTrack )
		, NumChainedJumps( 0 )
		, LastJumpTimeStamp( InitialTimeStamp )
	{}
	
	class AFGCharacterPlayer* pPlayer;
	
	int32 NumChainedJumps;
	float LastJumpTimeStamp;
};

DECLARE_LOG_CATEGORY_EXTERN( LogJumpPad, Log, All );

/**
 * Base class for the jump pads.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableJumppad : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableJumppad();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Called when a launch is triggered. Highest Launch Speed is set to whichever object was launched fastest out of those in the trigger box. */
	UFUNCTION( BlueprintImplementableEvent, Category = "JumpPad" )
	void OnLaunch( float HighestLaunchSpeed );

	/** Called for every player launched. */
	UFUNCTION( BlueprintImplementableEvent, Category = "JumpPad" )
    void OnPlayerLaunched( class AFGCharacterPlayer* pPlayer, int32 NumChainedBounces );

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	float GetPowerBankCapacity() const { return mPowerBankCapacity; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	float GetLaunchPowerCost() const { return mLaunchPowerCost; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	float GetCurrentPowerLevel() const { return mCurrentPowerLevel; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	float GetChargeRateMultiplier() const { return mChargeRateMultiplier; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	float GetLaunchVelocity() const { return mLaunchVelocity; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	float GetTrajectoryGravityMultiplier() const { return mTrajectoryGravityMultiplier; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	int32 GetNumAvailableCharges() const { return FMath::FloorToInt( mCurrentPowerLevel / mLaunchPowerCost ); }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	const FTrajectoryData& GetTrajectoryData() const { return mTrajectoryData; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	bool HasPowerForLaunch() const { return mHasPowerForLaunch; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	FVector GetLaunchDirection();

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	bool ShouldDisplayTrajectory() const { return mShowTrajectoryCounter > 0; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	class UBoxComponent* GetLauncherBoxComponent() const { return mLauncherBox; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	class UStaticMeshComponent* GetLauncherMeshComponent() const { return mLauncherMeshComponent; }

	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	const FVector& GetTrajectoryMeshScale() const { return mTrajectoryMeshScale; }

	UFUNCTION( BlueprintCallable, Category = "JumpPad" )
	void SetLaunchAngle( float Angle );

	UFUNCTION( BlueprintCallable, Category = "JumpPad" )
	void SetTrajectoryVisibility( bool Visible );

	// Calculates launch velocity for an object in order to land at the designated landing location for this jumppad.
	UFUNCTION( BlueprintPure, Category = "JumpPad" )
	FVector CalculateLaunchVelocity( const FVector& StartLocation, float Gravity ) const;

	UFUNCTION( BlueprintCallable, Category = "JumpPad" )
	const FTrajectoryData& ResimulateTrajectory();

	UFUNCTION()
	static FTrajectoryData SimulateTrajectory( UWorld* pWorld, const FVector& StartLocation, const FVector& LaunchVector, float GravityMultiplier, AFGBuildableJumppad* pJumpPad = nullptr );

	UFUNCTION( BlueprintCallable, Category = "JumpPad" )
	virtual void Launch();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual float GetProductionProgress() const override;
	virtual bool CanProduce_Implementation() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

protected:
	// Begin Factory_ Interface
	virtual void Factory_TickProducing( float dt ) override;
	// End Factory_ Interface

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

private:
	UFUNCTION()
	void OnRep_LaunchAngle();

	void GenerateSplineMesh();
	void DestroySplineMesh();

	UFUNCTION()
	void DestroyVisualizer();
	
	void UpdateDestinationLocation();
	void ConstructSplineFromTrajectoryData();

protected:
	/** Power capacity of the internal battery. */
	UPROPERTY( EditDefaultsOnly, Category = "JumpPad", meta = ( ClampMin = "0.0" ) )
	float mPowerBankCapacity;

	/** How much power each launch requires / drains from the battery. */
	UPROPERTY( EditDefaultsOnly, Category = "JumpPad", meta = ( ClampMin = "0.0" ) )
	float mLaunchPowerCost;

	/** Multiplied by the building's power consumption rate to charge the battery. */
	UPROPERTY( EditDefaultsOnly, Category = "JumpPad", meta = ( ClampMin = "0.0" ) )
	float mChargeRateMultiplier;

	/** Current power level. */
	UPROPERTY( VisibleAnywhere, SaveGame, Category = "JumpPad" )
	float mCurrentPowerLevel;

	/** Desired launch velocity for objects with normal gravity. */
	UPROPERTY( EditDefaultsOnly, Category = "JumpPad", meta = ( ClampMin = "0.0" ) )
	float mLaunchVelocity;

	/** Angle at which objects are launched. This doesn't 100% represent how an object flies, since that can change depending on their gravity. */
	UPROPERTY( VisibleAnywhere, SaveGame, ReplicatedUsing = OnRep_LaunchAngle, Category = "JumpPad" )
	float mLaunchAngle;
	
	/** How much time has to pass for a players chain jump counter to be reset. */
    UPROPERTY( EditDefaultsOnly, Category = "JumpPad", meta = ( ClampMin = "0.0" ) )
    float mPlayerChainJumpResetTime;

	/** Whether or not there's enough power in the battery to launch. */
	UPROPERTY( VisibleAnywhere, Replicated, Category = "JumpPad" )
	bool mHasPowerForLaunch;

	/** Components which are inside the launcher trigger box, ready to be launched. */
	UPROPERTY()
	TArray<class UPrimitiveComponent*> ComponentsToLaunch;

	/** Characters which are inside the launcher trigger box, ready to be launched. */
	UPROPERTY()
	TArray<class AFGCharacterBase*> CharactersToLaunch;

	/** Vehicles which are inside the launcher trigger box, ready to be launched. */
	UPROPERTY()
	TArray<class AFGVehicle*> VehiclesToLaunch;

	/** Objects entering this box will be launched. */
	UPROPERTY( VisibleAnywhere, Category = "JumpPad" )
	class UBoxComponent* mLauncherBox;

	/** Data for the current trajectory, such as landing location and points along the trajectory. */
	UPROPERTY( BlueprintReadOnly, Category = "JumpPad" )
	FTrajectoryData mTrajectoryData;

	/** The part of the jump pad that angles up and down. */
	UPROPERTY( BlueprintReadOnly, Category = "Jump Pad" )
	class UStaticMeshComponent* mLauncherMeshComponent;

	/** The scale used for the instances in the spline mesh. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory|Transforms" )
	FVector mTrajectoryMeshScale;

	UPROPERTY( EditDefaultsOnly, Category = "Trajectory|Transforms" )
	FRotator mTrajectoryMeshRotation;

	/** How high above the impact location the destination mesh will be. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory|Transforms" )
	float mDestinationMeshHeightOffset;
	
	/** The mesh that shows where launched objects will land. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory|Mesh" )
	UStaticMesh* mDestinationMesh;

	/** StaticMesh used for spline visualization */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory|Mesh")
    UStaticMesh* mTrajectorySplineMesh;
	
	/* Number of arrows generated over the spline. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory")
	int32 mNumArrows;

	/* Generated on command */
	UPROPERTY()
	UFGInstancedSplineMeshComponent* mTrajectorySplineComponent;
	
	/* Generated on command */
	UPROPERTY()
    class UStaticMeshComponent* mDestinationMeshComponent;

	/* Generated on command */
	UPROPERTY( )
    class USplineComponent* mSplineComponent;

	/* Lifetime timer for the temporary components. */
	UPROPERTY()
	FTimerHandle mKillTimer;
	
	/** Gravity multiplier used when simulating trajectory to calculate landing location. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory" )
	float mTrajectoryGravityMultiplier;

	/** If this counter is greater than 0, it means something wants us to show our trajectory.
	Not using a bool because several objects could request us to show the trajectory at the same time. */
	UPROPERTY( VisibleAnywhere, Category = "Trajectory" )
	int32 mShowTrajectoryCounter;

	/** Used to track players and how many jumps theyve done. Initially intended for playing sounds in a sequence for christmas event.*/
	// TODO: This isn't very clean, as it will keep old data between sessions and only really reset once the game shuts down
	static TArray<TrackedJumpPadPlayer> mTrackedPlayers;

	private:
		friend class AFGJumpPadLauncherHologram;
};
