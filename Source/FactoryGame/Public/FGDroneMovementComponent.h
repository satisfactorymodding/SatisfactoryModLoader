// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "Components/ActorComponent.h"
#include "Components/SplineComponent.h"
#include "FGDroneMovementComponent.generated.h"

UENUM( BlueprintType )
enum class EDroneFlyingMode : uint8
{
	DFM_None		UMETA(displayName = "None"),
	DFM_Flying		UMETA(displayName = "Flying"),
	DFM_Travel		UMETA(displayName = "Travel")
};

UENUM()
enum class EDroneMovementInstruction : uint8
{
	DMI_None,
	DMI_MoveToLocation,
	DMI_FollowPath
};

UENUM()
enum class EDroneDirectionFacingIstruction : uint8
{
	DFI_None,
	
	// Drone will face the specified direction when arriving at the destination
	DFI_AtDestination,

	// Drone will face the specified direction immediately at the start of the movement instruction
	DFI_AtStart
};

DECLARE_MULTICAST_DELEGATE( FDroneMovementEvent );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDroneMovementBrakingEvent, bool, IsBraking );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDroneMovementFlyingModeEvent, EDroneFlyingMode, NewFlyingMode );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGDroneMovementComponent : public UActorComponent, public IFGSaveInterface
{
	GENERATED_BODY()

public:	
	UFGDroneMovementComponent();

	// Begin UActorComponent Interface
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End UActorComponent Interface
	
	// Begin UObject Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End UObject Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	void PostDroneReceiveLocationAndRotation( const FVector& newLocation, const FRotator& newRotation );

	/** Called from the Drone Subsystem to tick this movement, returns true if movement was applied. */
	void TickDroneMovement( float deltaSeconds, FVector& out_newLocation, FRotator& out_newRotation );

	/** Gets the current velocity of the drone. */
	UFUNCTION( BlueprintPure, Category = "DroneMovement" )
	FORCEINLINE FVector const& GetVelocity() const { return mVelocity; }
	
	/** Whether or not the drone is currently braking. */
	UFUNCTION( BlueprintPure, Category = "DroneMovement" )
	FORCEINLINE bool IsBraking() const { return mIsBraking; }

	/** Gets the current flying mode of the drone. */
	UFUNCTION( BlueprintPure, Category = "DroneMovement" )
	FORCEINLINE EDroneFlyingMode GetFlyingMode() const { return mFlyingMode; }

	/** Gets the current movement instruction of the drone. */
	UFUNCTION( BlueprintPure, Category = "DroneMovement" )
	FORCEINLINE EDroneMovementInstruction GetCurrentMovementInstruction() const { return mCurrentMovementInstruction; }

	/** Gets the current max speed of the drone. */
	UFUNCTION( BlueprintPure, Category = "DroneMovement" )
	float GetMaxSpeed() const;

	/** Used to move the drone to the specified location. */
	UFUNCTION( BlueprintCallable, Category = "DroneMovement" )
	void MoveToLocation( const FVector& Location, EDroneFlyingMode flyingMode, const FVector& directionToFace = FVector::ZeroVector, EDroneDirectionFacingIstruction facingDirectionInstruction = EDroneDirectionFacingIstruction::DFI_None );

	/** Used to make the drone follow a path. */
    UFUNCTION( BlueprintCallable, Category = "DroneMovement" )
    void FollowPath( const TArray< FVector >& Path, EDroneFlyingMode flyingMode, bool brakeWhenApproaching = true );

private:
	UFUNCTION()
	void OnRep_MovementInstruction( EDroneMovementInstruction previousInstruction );

	UFUNCTION()
	void OnRep_FlyingMode();
	
	/** Sets the current flying mode of the drone. */
	void SetFlyingMode( EDroneFlyingMode newFlyingMode );

	/** Sets the current movement instruction of the drone. */
	void SetMovementInstruction( EDroneMovementInstruction movementInstruction );

	/** Interrupts whatever movement the drone is doing right now. */
	void CancelCurrentMovement();

	void TickMovement_MoveTo( float deltaSeconds, FVector& out_newLocation, FRotator& out_newRotation );
	void TickMovement_FollowPath( float deltaSeconds, FVector& out_newLocation, FRotator& out_newRotation );
	void TickMovement_None( float deltaSeconds, FVector& out_newLocation, FRotator& out_newRotation );

	/** Helper function to move towards a location, returns true if we arrived at the location. */
	bool MoveTowardsLocation( const FVector& location, float deltaSeconds, FVector& out_newLocation, FRotator& out_newRotation, bool brakeWhenApproaching = false );

	bool HasAuthority() const;

	void SetRegistered( bool registered, bool updateTransformWhenUnregistered = true );

public:
	/** Called whenever the drone finishes its movement instruction. */
	FDroneMovementEvent OnMovementInstructionFinished;

	/** Called whenever the drone reaches its destination. */
	FDroneMovementEvent OnDestinationReached;

	/** Called whenever the drone changes its flying mode. */
	UPROPERTY( BlueprintAssignable, Category = "DroneMovement" )
	FDroneMovementFlyingModeEvent OnFlyingModeChanged;
	
	/** Called whenever the drone changes its braking state. */
	UPROPERTY( BlueprintAssignable, Category = "DroneMovement" )
	FDroneMovementBrakingEvent OnBrakingStateChanged;

private:
	/** The drone this movement component belongs to. */
	UPROPERTY()
	class AFGDroneVehicle* mDrone;

	/** The current flying mode of the drone. Used to determine how the flying should behave. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_FlyingMode )
	EDroneFlyingMode mFlyingMode;

	/** What the drone movement is currently instructed to do. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_MovementInstruction )
	EDroneMovementInstruction mCurrentMovementInstruction;

	/** The path the drone is currently following. */
	UPROPERTY( SaveGame, Replicated )
	TArray< FVector > mCurrentPath;

	/** Whether or not the drone should brake when approaching the end of the path it's following. */
	UPROPERTY( SaveGame, Replicated )
	bool mBrakeWhenApproachingDestination;

	/** Instruction describing when the drone should face the specified facing direction. */
	UPROPERTY( SaveGame, Replicated )
	EDroneDirectionFacingIstruction mFacingDirectionInstruction;

	/** Index representing what location we're at in the path. */
	UPROPERTY( SaveGame, Replicated )
	int32 mCurrentPathIndex;

	/** If the drone is told to move to a location, this is the location. */
	UPROPERTY( SaveGame, Replicated )
	FVector mCurrentDestination;

	/** Will turn to face the specified direction once destination is reached. */
	UPROPERTY( SaveGame, Replicated )
	FVector mDirectionToFaceAtDestination;

	/** The desired facing direction of the drone. It will rotate to face this direction. */
	UPROPERTY( SaveGame, Replicated )
	FVector mDesiredFacingDirection;

	/** Velocity of the drone on the server. */
	UPROPERTY( Replicated )
	FVector mServerVelocity;

	/** Location of the drone on the server. */
	FVector mServerLocation;

	/** Rotation of the drone on the server. */
	FRotator mServerRotation;

	/** Current velocity of the drone. */
	UPROPERTY( SaveGame )
	FVector mVelocity;

	/** Whether or not drone is currently braking. */
	UPROPERTY()
	bool mIsBraking;
};
