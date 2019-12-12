// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGVehicle.h"
#include "ItemAmount.h"
#include "PhysicsPublic.h"
#include "PhysXPublic.h"
#include "WheeledVehicle.h"
#include "FGWheeledVehicle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FTranferStatusChanged );

class FDebugDisplayInfo;

USTRUCT( BlueprintType )
struct FTireData
{
	GENERATED_BODY()

	//bool IsInAir;
	UPROPERTY( BlueprintReadOnly, Category = "Vehicle" )
	UPhysicalMaterial* SurfaceMaterial;

	UPROPERTY( BlueprintReadOnly, Category = "Vehicle" )
	FVector WheelLocation;

	UPROPERTY( BlueprintReadOnly, Category = "Vehicle" )
	float WheelRadius;

	UPROPERTY( BlueprintReadOnly, Category = "Vehicle" )
	float WheelWidth;

	UPROPERTY( BlueprintReadOnly, Category = "Vehicle" )
	int32 WheelIndex;

	UPROPERTY( BlueprintReadOnly, Category = "Vehicle" )
	bool IsInAir;
	//float TireFriction;
};

USTRUCT( BlueprintType )
struct FTireTrackDecalDetails
{
	GENERATED_BODY()

	/** Surface material to override for */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	UPhysicalMaterial* SurfacePhysicsMaterial;

	/** Material to use as an override */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	class UMaterial* DecalMaterialOverride;

};

USTRUCT( BlueprintType )
struct FSurfaceParticlePair
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "SurfaceParticlePair" )
	UParticleSystem* EmitterTemplate;

	UPROPERTY( EditDefaultsOnly, Category = "SurfaceParticlePair" )
	TEnumAsByte< EPhysicalSurface > Surface;
};

USTRUCT()
struct FParticleTemplatePair
{
	GENERATED_BODY()

	FParticleTemplatePair() : Template( nullptr ), Particle( nullptr ) {}

	UPROPERTY()
	UParticleSystem* Template;

	UPROPERTY()
	UParticleSystemComponent* Particle;

};

USTRUCT()
struct FTireParticleCollection
{
	GENERATED_BODY()

	UPROPERTY()
	TArray< FParticleTemplatePair > Collection;
};

/* DSOL (Don't shift on (wheel) load) dynamic gearbox data */
struct DSOLDynGearboxData
{
	bool mWasShiftingUp;
	bool mWasShiftingDown;
	int32 mTargetGear = 1;
	float mGearSwitchTime;
	float mSlopeShiftRatio; //Multiplier to affect shifting gears up and down on a slope
};

/* DSOL (Don't shift on (wheel) load) dynamic gearbox data */
struct DSOLSetupData
{
	int mNumberOfGears;
	float mDownShiftLatency;
};

/**
* Some replicated state for this vehicle.
* Done here instead of movement component
* because this is the only shared place
* between the 4W & 6W movement components
*/
USTRUCT()
struct FReplicatedAddedVelocitiesState
{
	GENERATED_USTRUCT_BODY()

	// input replication: steering
	UPROPERTY()
	bool IsDrifting;

	// input replication: angular velocity pitch
	UPROPERTY()
	float AddedAngularVelocityInputPitch;

	// input replication: angular velocity yaw
	UPROPERTY()
	float AddedAngularVelocityInputYaw;
};

/**
 * This is our implementation of a wheeled vehicle, we want a base class FGVehicle that can be shared by wheeled vehicles, trains etc.
 * @see AWheeledVehicle
 */
UCLASS( abstract, config = Game, BlueprintType )
class FACTORYGAME_API AFGWheeledVehicle : public AFGVehicle
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	AFGWheeledVehicle();

	// Begin AActor interface
	//MODDING EDIT PostInitialize crashed  when creating a blueprint child
	//virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug(class UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos) override;
	// End AActor interface

	//~ Begin IFGDockableInterface
	virtual bool CanDock_Implementation( EDockStationType atStation ) const override;
	virtual class UFGInventoryComponent* GetDockInventory_Implementation() const override;
	virtual class UFGInventoryComponent* GetDockFuelInventory_Implementation() const override;
	virtual void WasDocked_Implementation( class AFGBuildableDockingStation* atStation ) override;
	virtual void WasUndocked_Implementation() override;
	virtual void OnBeginLoadVehicle_Implementation() override;
	virtual void OnBeginUnloadVehicle_Implementation() override;
	virtual void OnTransferComplete_Implementation() override;
	//~ End IFGDockableInterface

	/** Returns VehicleMovement subobject **/
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	class UWheeledVehicleMovementComponent* GetVehicleMovementComponent() const;

	/** Sets the movement component to the given component. Used to initialise 4W, 6W, NW movement components. */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetMovementComponent( UWheeledVehicleMovementComponent* movementComponent );

	/** Do we have fuel? */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	bool HasFuel();

	/** Gets information about tires ( such as IsInAir etc ) */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void GetTireData( TArray< FTireData >& out_tireData );

	/** Gets the particle system that corresponds to physmat */
	UParticleSystem* GetSurfaceParticleSystem( UPhysicalMaterial* physMat);

	/** Gets air status */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	bool GetIsInAir() { return mIsInAir; }

	/** Is any wheel on the ground*/
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	int32 NumWheelsOnGround() { return mNumWheelsOnGround; }	

	/** Get the fuel inventory. */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE class UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

	/** Get the storage inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }

	/** Use this function instead of the one in movement component because we have multiple components that move the vehicle */
	UFUNCTION( BlueprintPure, Category = "Velocity" )
	float GetForwardSpeed();

	/**
	 * Check if a resource is valid as fuel for this station.
	 * @param resource - Resource class to check.
	 * @return - true if resource valid as fuel; false if not valid or if generator does not run on fuel.
	 */
	UFUNCTION()
	bool IsValidFuel( TSubclassOf< class UFGItemDescriptor > resource ) const;

	/**
	 * If an object can be destroyed by a vehicle collision (foliage that are static meshes) this function destroys it IF the required force is met.
	 * Some objects only need an overlap, in which case force is irrelevant and forceOfCollision will be -1.0f.
	 * @param actor - collided actor
	 * @param forceOfCollision - the force of the collision, or 0.0f if an overlap
	 */
	void HandleDestroyStaticMesh( AActor* actor, float forceOfCollision = 0.0f );

	/**
	* If an object can be destroyed by a vehicle running over it (eg. foliage) this function destroys it IF the required force is met.
	*/
	void HandleDestroyFoliage();

	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

	///////////////////////DSOL Gearbox Stuff////////////////////////////////
	// "Don't Shift On Load" gearbox. Doesn't shift up if there is load on 
	// the tires. Useful for climbing uphill.
	// I'm putting this functionality here because it is a common object 
	// for movement components to access without modifying the engine.
	// The flag to enable/disable this, however, will be in the 
	// movement components. This mean we must manually also 
	// call this from movement components.
	/////////////////////////////////////////////////////////////////////////

	/** Simulates an automatic gearbox that does not shift up when there is load on the tires (useful when driving uphill) */
	static void SimulateDSOLGearBox( float DeltaTime,
									 float RawThrottleInput,
									 DSOLSetupData& setupData,
									 DSOLDynGearboxData& gearboxData, 
									 PxVehicleWheelsSimData& wheelsSimData, 
									 PxVehicleDriveDynData& driveDynData, 
									 PxVehicleDriveSimData& driveSimData );

	/** Is the movement being simulated? */
	UFUNCTION( BlueprintPure, Category = "Simulation" )
	FORCEINLINE bool IsSimulated() { return mIsSimulated; }

	/**Returns the simulation component */
	UFUNCTION( BlueprintPure, Category = "Simulation" )
	FORCEINLINE UFloatingPawnMovement* GetSimulationComponent() { return mSimulationMovementComponent; }

	/** Toggles what movement mode we are using */
	void SetSimulation( bool newIsSimulating );

	/** Indicates if the vehicle is gasing or wants to move in simulated state */
	UFUNCTION( BlueprintPure, Category = "Movement" ) 
	bool WantsToMove();

	/** returns the ratio ( 0 to 1.0 ) for how much fuel we want to burn. Ussually a reflection of throttle value except during simulation */
	float GetFuelBurnRatio();

	/**Returns the simulation component */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	class UFGTargetPointLinkedList* GetTargetNodeLinkedList();

	/** Removes the desired target from the linked list */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void RemoveTargetPoint( class AFGTargetPoint* targetToRemove );

	/** Fills the linked list with target nodes with data from an array */
	UFUNCTION( BlueprintCallable, Category = "Path" )
	void SetPathFromArray( TArray< class AFGTargetPoint* > targetPoints );

	/**Getter for path visibility */
	UFUNCTION( BlueprintPure, Category = "Path" )
	FORCEINLINE bool GetPathVisibility() { return mIsPathVisible; }

	/**Getter for path visibility */
	UFUNCTION( BlueprintCallable, Category = "Path" )
	void SetPathVisibility( bool inVisible ) { mIsPathVisible = inVisible; }

	/** Blueprint accessor for when foliage was destroyed */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Character" )
	void PlayFoliageDestroyedEffect( class UParticleSystem* destroyEffect, class UAkAudioEvent* destroyAudioEvent, FVector location );

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );
	
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetIsDrifting( bool newDrifting ) { mIsDrifting = newDrifting; }

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE bool GetIsDrifting() { return mIsDrifting; }

	/** Called from Movement Component's TickVehicle
	*  eg. to manage/clamp/add custom fake forces vehicle for handling purposes
	*/
	void ManageFakeForces( float DeltaTime );

	/** retrieves the world location of where the drift force should be applied. eg. use a blueprint to position it */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	FVector GetDriftForceOffset();

protected:
	// Begin AFGVehicle interface
	virtual void Died( AActor* thisActor ) override;
	// End AFGVehicle interface

	/** Create item drops for our inventory ( used when vehicle has killed/destroyed */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle" )
	void CreateInventoryItemDrops();

	/** sets mAddedAngularVelocityInputPitch and lerps it using mAddedAngularVelocityInputSmoothingSpeed */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetAddedAngularVelocityPitch( float pitchToAdd );

	/** sets mAddedAngularVelocityInputYaw and lerps it using mAddedAngularVelocityInputSmoothingSpeed */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetAddedAngularVelocityYaw( float yawToAdd );

	//@todo Deprecated REMOVE ME
	UFUNCTION( BlueprintPure, Category = "Vehicle", meta = ( DeprecatedFunction, DeprecationMessage = "Duplicate, use GetIsInAir instead" ) )
	FORCEINLINE bool GetIsGrounded() { return !GetIsInAir(); }

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void ResetAddedAngularVelocityValues();

	/** Read current state for simulation */
	void UpdateAssistedVelocitiesState();

	/** Pass current state to server */
	UFUNCTION( Reliable, Server, WithValidation )
	void ServerUpdateAssistedVelocitiesState( bool inDrifting, float inInputYaw, float inInputPitch );

	/** Update the clients state from the replicated state */
	UFUNCTION()
	void UseReplicatedState();

private:
	/** Tick helpers */
	void UpdateSimulationState();
	void UpdateAirStatus();
	void UpdateTireEffects();
	void UpdateTireParticle( FTireData tireData );
	void BurnFuel( float dt );

	/** Applies added angular velocity to the vehicle to assist sliding and air control */
	void ApplyAddedAngularVelocityModifiers( float deltaTime );

	/** Activates/deactivates tire particles so that it's only the one matching the template that is active */
	void SwitchParticle( int32 tireIndex, UParticleSystem* particleTemplate );

	/** Draws a tire track decal if necessary */
	void DrawTireTrack( FTireData tireData, FVector decalLocation );

	/** Updates the vehicles settings depending on if it should be simulated or "real" */
	void OnSimulationChanged();

	/** Clamp angular and linear velocities */
	void ClampVelocities();

	/** handles added linear velocity on throttle */
	void AddedLinearThrottleVelocity();

	/** logic for stabilising roll angular velocity in the air */
	void ApplyRollStabilisation( float deltaTime );

	/** applies assisted acceleration and drifting velocities */
	void ApplyAssistedVelocities( float deltaTime );

	/** Rep notifies */
	UFUNCTION()
	void OnRep_IsSimulated();

	UFUNCTION()
	void OnRep_TransferStatusChanged();

public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

	/** Workbench component */
	UPROPERTY( BlueprintReadOnly )
	class UFGWorkBench* mWorkBench;

	UPROPERTY( BlueprintReadWrite, Category = "Vehicle" )
	FTimerHandle mUpdateMovementHandle;

	/* Forces vehicle to be in simulation mode */
	UPROPERTY( BlueprintReadWrite, Category = "Debug" )
	bool mForceSimulationMode; 

	/* Forces vehicle to be in real mode */
	UPROPERTY( BlueprintReadWrite, Category = "Debug" )
	bool mForceRealMode;

	/** Broadcast when transfer status is updated */
	UPROPERTY( BlueprintAssignable, Category = "Docking", DisplayName = "OnTransferStatusChanged" )
	FTranferStatusChanged TranferStatusChangedDelegate;

protected:

	// replicated state of vehicle 
	UPROPERTY( Transient, Replicated )
	FReplicatedAddedVelocitiesState mReplicatedState;

	/** This vehicles fuel consumption in MW/s */
	UPROPERTY( EditDefaultsOnly, Category = "Fuel" )
	float mFuelConsumption;

	/** Amount left of the currently burned piece of fuel. In megawatt seconds (MWs). */
	UPROPERTY( SaveGame, Replicated )
	float mCurrentFuelAmount;

	/** Are we currently in the process of loading inventory */
	UPROPERTY( BlueprintReadOnly, SaveGame, ReplicatedUsing = OnRep_TransferStatusChanged, Meta = ( NoAutoJson = true ) )
	bool mIsLoadingVehicle;

	/** Are we currently in the process of unloading inventory */
	UPROPERTY( BlueprintReadOnly, SaveGame, ReplicatedUsing = OnRep_TransferStatusChanged, Meta = ( NoAutoJson = true ) )
	bool mIsUnloadingVehicle;

	/** Type of the currently burned piece of fuel. */
	UPROPERTY( SaveGame )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;

	/** Is vehicle in air */
	UPROPERTY()
	bool mIsInAir;

	/** Is there at least 1 wheel on the ground */
	UPROPERTY()
	int32 mNumWheelsOnGround;

	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, Category = Vehicle )
	class UWheeledVehicleMovementComponent* mVehicleMovement;

	/** Distance between tire track decals */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mDistBetweenDecals;

	/** Time, in seconds, for the tire track decal to live */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mDecalLifespan;

	/** default tire track decal. Can be empty for no default. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	class UMaterial* mDefaultTireTrackDecal;

	/** tire track decal  settings */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TArray< FTireTrackDecalDetails > mTireTrackDecals;

	/** The scale for the decal. This will probably need to be uniquely set for every vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	FVector mDecalSize;

	/** When foliage is run over by this vehicle, this is the radius of foliage that should be cleared */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mFoliageDestroyRadius;

	/** Strength of the angular velocity yaw modifier when on the ground and holding "drift" */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mAddedGroundAngularVelocityStrengthYaw;

	/** Strength of the angular velocity pitch modifier when on the ground and holding "drift" */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mAddedGroundAngularVelocityStrengthPitch;

	/** Strength of the added air control angular yaw velocity */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mAddedAirControlAngularVelocityStrengthYaw;

	/** Strength of the added air control angular pitch velocity */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mAddedAirControlAngularVelocityStrengthPitch;

	/**
	* Strength of the natural added angular yaw velocity when turning.
	* Used to generate natural sliding when not in the air and turning without handbrake.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mNaturalAngularVelocityStrengthYaw;

	/** 
	 * Strength of the natural added angular pitch velocity when turning.
	 * Used to generate natural sliding when not in the air and turning without handbrake.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mNaturalAngularVelocityStrengthPitch;

	/**
	* Strength of the natural added angular yaw velocity during air control.
	* Used to generate natural sliding when not in the air and turning without handbrake.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mNaturalAirAngularVelocityStrengthYaw;

	/**
	* Strength of the natural added angular pitch velocity during air control.
	* Used to generate natural sliding when not in the air and turning without handbrake.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mNaturalAirAngularVelocityStrengthPitch;

	/** 
	 * Speed at which the added angular velocity input smooths from previous input to the next
	 * Should be between 0.1 to 1.0
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle", meta = (ClampMin = 0.1, ClampMax = 1.0) )
	float mAddedAngularVelocityInputSmoothingSpeed;

	/** Collision box for detecting overlaps with foliage only. Shape modified in BP */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	UBoxComponent* mFoliageCollideBox;
private:
	/** Is the movement being simulated? */
	UPROPERTY( ReplicatedUsing = OnRep_IsSimulated, SaveGame )
	bool mIsSimulated;

	/** Distance from player at which simulation begins */
	UPROPERTY( EditDefaultsOnly, Category = "Simulation" )
	float mSimulationDistance;

	/** Our component used for simulated movement */
	UPROPERTY()
	class UFloatingPawnMovement* mSimulationMovementComponent;
	
	/** Inventory for fuel */
	UPROPERTY( VisibleDefaultsOnly, SaveGame, Replicated )
	class UFGInventoryComponent* mFuelInventory;

	/** Inventory for storage */
	UPROPERTY( VisibleDefaultsOnly, SaveGame, Replicated )
	class UFGInventoryComponent* mStorageInventory;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	int32 mInventorySize;

	/** A complete collection of all tire particles gathered per tire */
	TArray< FTireParticleCollection > mTireParticleCollection;

	/** Map that lists which templates corresponds to what surface type */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TArray< FSurfaceParticlePair > mVehicleParticeMap;

	/** Contains references to all current active partice systems on the tires */
	UPROPERTY()
	TArray< FParticleTemplatePair > mActiveParticleAndTemplate;

	/** Base name of socket use for tire particles */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	FString mTireEffectSocketName;

	/** Linked list with target nodes that make up our path to travel */
	UPROPERTY( SaveGame )
	class UFGTargetPointLinkedList* mTargetNodeLinkedList;

	/** Should targets nodes be visible */
	UPROPERTY( SaveGame, Replicated )
	bool mIsPathVisible;

	/** location of the last placed decals for each wheel */
	UPROPERTY()
	TArray< FVector > mLastDecalLocations;

	/** If we have overlapped foliage go nuts and destroy them */
	UPROPERTY()
	TArray< class UHierarchicalInstancedStaticMeshComponent* > mOverlappedHISMComponents;

	/**
	* input for added angular Pitch velocity modifier. Between -1.0 and 1.0.
	* This is to be updated via blueprint.
	*/
	UPROPERTY()
	float mAddedAngularVelocityInputPitch;

	/** 
	 * input for added angular yaw velocity modifier. Between -1.0 and 1.0. 
	 * This is to be updated via blueprint.
	 */
	UPROPERTY()
	float mAddedAngularVelocityInputYaw;

	// Set from blueprint. True if drift button is down.
	bool mIsDrifting;

	/** 
	 * it may be a good idea to make the added velocity stronger when reversing.
	 * eg. with the explorer, it will make it easier to drift 180 when reversing.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle", meta = (ClampMin = 0.1, ClampMax = 5.0) )
	float mReverseAddedAngularVelocityYawMultiplier;

	/** if true, can control vehicle in air */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	bool mHasAirControl;

	/** length to trace to check for ground */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mGroundTraceLength;

	/** change in linear velocity since last frame */
	float mDeltaLinearVelocity;

	/** max change in linear velocity since last frame */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMaxDeltaLinearVelocity;

	/** change in angular velocity since last frame */
	float mDeltaAngularVelocity;

	/** max change in angular velocity since last frame */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMaxDeltaAngularVelocity;

	/** Amount of damping to add to roll */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mRollStabilisationStrength;

	/** The min roll angle to consider the vehicle upside down - only as far as roll goes. Other factors are also taken into account. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMaxRollAngleForUpsideDown;

	/** The max roll angle to consider the vehicle flat on ground - only as far as roll goes. Other factors are also taken into account. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMaxFlatOnGroundRollAngleLimit;

	/** If roll angle is over this value then assisted velocities will not be applied. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMaxRollForActivationOfAssistedVelocities;

	/** 
	 * There can be added acceleration when at low speeds. This max speed is when no more acceleration is added. 
	 * Added acceleration is interpolated between mMaxAssistedAcceleration -> Zero
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	int32 mMaxSpeedForAddedAcceleration;

	/** Maximum amount of force that can be added to assist acceleration */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMaxAssistedAcceleration;

	/** If true, Assisted Acceleration & drifting is be in effect */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	bool mHasAssistedVelocities;

	/** If true, roll stabilisation is be in effect */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	bool mHasRollStabilisation;

	/** the lateral force we add for drifting */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mDriftingLateralForce;

	/** the upward force we add for drifting (this is to reduce friction & encourage oversteer) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mDriftingUpwardForce;

	/** 
	 * the curve representing the force we add to the drift angle relevant to the current angle.
	 * Y-axis is abs( degrees ) between forward vector and current velocity direction
	 * Should be 0 at slight angles to prevent basic speed up when holding drift
	 * should peak at 90 degrees or so.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	UCurveFloat* mDriftForwardForceStrengthCurve;

	/** 
	 * List of bones to apply drift force to when drifting
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TArray< FName > mDriftForceBones;

	/**
	* min angle for drift (degrees)
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mMinAngleForDrift;

	/** Indicates that we have found ground from previously being airborn */
	bool mWantsToLand;

	/* Saved velocity while no wheels are touching the ground */
	float mLandVelocityZ;
};
