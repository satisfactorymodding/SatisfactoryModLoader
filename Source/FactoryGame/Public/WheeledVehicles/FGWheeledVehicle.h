// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGVehicle.h"
#include "ItemAmount.h"
#include "PhysXPublic.h"
#include "WheeledVehicles/FGSplinePathMovementComponent.h"
#include "FGVehicleSubsystem.h"
#include "FGActorRepresentationInterface.h"
#include "FGWheeledVehicle.generated.h"

// TODO: migrate from PhysX to Chaos; in the meantime, stfu
#pragma warning( disable : 4996 )


DECLARE_STATS_GROUP( TEXT( "Wheeled vehicles" ), STATGROUP_WheeledVehicles, STATCAT_Advanced );

class FDebugDisplayInfo;

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTireData
{
	GENERATED_BODY()
	
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
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTireTrackDecalDetails
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

UENUM( BlueprintType )
enum class ERecordingStatus : uint8
{
	RS_NoRecording = 0,
	RS_RecordingStarted,
	RS_CompletionPossible,
	RS_RecordingCompleted,
	RS_RecordingAborted
};

UENUM( BlueprintType )
enum class ETransferAnimationState : uint8
{
	TS_None,
	TS_Loading,
	TS_Unloading
};

UENUM( BlueprintType )
enum class EManualDockingState : uint8
{
	MDS_NoDocking,
	MDS_CanLoad,
	MDS_CanUnload
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
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Destroyed() override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug(class UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos) override;
	// End AActor interface

	// Begin ADriveablePawn interface
	virtual bool DriverEnter( class AFGCharacterPlayer* driver ) override;
	// End ADriveablePawn interface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin Customization Interface
	
	// End Customization Interface

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

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFSaveInterface

	// Begin IFGActorRepresentationInterface
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	// End IFGActorRepresentationInterface

	//~ Begin IFGUseableInterface
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	//~ End IFGUseableInterface

	/** Returns the static mesh that are attached to the skeletal mesh of some vehicles, nullptr if there is no such static mesh */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle" )
	UStaticMesh* FindAttachedStaticMesh();

	/** Returns VehicleMovement subobject **/
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	class UWheeledVehicleMovementComponent* GetVehicleMovementComponent() const;

	/** Sets the movement component to the given component. Used to initialise 4W, 6W, NW movement components. */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetMovementComponent( UWheeledVehicleMovementComponent* movementComponent );

	/** Do we have fuel? */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	bool HasFuel() const;

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

	/**Returns the simulation component */
	//UFUNCTION( BlueprintPure, Category = "Simulation" )
	//FORCEINLINE UFloatingPawnMovement* GetSimulationComponent() { return mSimulationMovementComponent; }

	/** Indicates if the vehicle is gasing or wants to move in simulated state */
	UFUNCTION( BlueprintPure, Category = "Movement" ) 
	bool ConsumesFuel();

	/** returns the ratio ( 0 to 1.0 ) for how much fuel we want to burn. Ussually a reflection of throttle value except during simulation */
	float GetFuelBurnRatio();

	/**Returns the simulation component */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	class AFGDrivingTargetList* GetTargetList( bool createIfNeeded = false );

	/** Fills the linked list with target nodes with data from an array */
	//UFUNCTION( BlueprintCallable, Category = "Path" )
	//void SetPathFromArray( TArray< class AFGTargetPoint* > targetPoints );

	/**Getter for path visibility */
	UFUNCTION( BlueprintPure, Category = "Path" )
	bool GetPathVisibility();

	/**Getter for path visibility */
	//UFUNCTION( BlueprintCallable, Category = "Path" )
	//void SetPathVisibility( bool inVisible ) { mIsPathVisible = inVisible; }

	/** Multicast from server when foliage was destroyed */
	UFUNCTION( NetMulticast, Unreliable, Category = "Character" )
	void Multicast_PlayFoliageDestroyedEffect( class UParticleSystem* destroyEffect, class UAkAudioEvent* destroyAudioEvent, FVector location );

	/** Blueprint client accessor for when foliage was destroyed */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Character" )
	void Client_PlayFoliageDestroyedEffect( class UParticleSystem* destroyEffect, class UAkAudioEvent* destroyAudioEvent, FVector location );

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );
	
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetIsDrifting( bool newDrifting ) { mIsDrifting = newDrifting; }

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE bool GetIsDrifting() const { return mIsDrifting; }

	/** Called from Movement Component's TickVehicle
	*  eg. to manage/clamp/add custom fake forces vehicle for handling purposes
	*/
	void ManageFakeForces( float DeltaTime );

	/** retrieves the world location of where the drift force should be applied. eg. use a blueprint to position it */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	FVector GetDriftForceOffset();

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Vehicle" )
	void CloseVehicleTrunk( class AFGCharacterPlayer* player );

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Vehicle" )
	void OpenVehicleTrunk( class AFGCharacterPlayer* player );

	/** Returns the cached surface material */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE UPhysicalMaterial* GetCachedSurfaceMaterial() { return mCachedSurfaceMaterial; }

	void MeasureVelocities( float deltaTime );

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	static FText GetDefaultMapName( TSubclassOf< AFGWheeledVehicle > vehicleType );

	class AFGDrivingTargetList* GetActiveTargetList() const;

	class UFGSplinePathMovementComponent* GetSimulationMovement() const { return mSimulationMovement; }

	void SyncWithSimulation();

	bool ShouldStayAtDock();

	bool HasFullTank() const;

	float GetTotalFuelEnergy() const;

	float CalculateFuelNeed() const;

	float GetMaxFuelEnergy() const;

	bool HasFuelForRoundtrip() const;

	UFUNCTION( BlueprintPure, Category = "Docking" )
	ETransferAnimationState GetTransferAnimationState( float animationLength, float& animationTime );

	void CalculateManualDockingState();

	UFUNCTION( BlueprintPure, Category = "Docking" )
	EManualDockingState GetManualDockingState() const { return mManualDockingState; }

	UFUNCTION( BlueprintPure, Category = "Docking" )
	class AFGBuildableDockingStation* GetRefuelingStation() const { return mRefuelingStation; }

	void SetRefuelingStation( class AFGBuildableDockingStation* station );

	UFUNCTION( BlueprintCallable, Category = "Docking" )
	void DockToRefuelingStation();

protected:
	// Begin AFGVehicle interface
	virtual void Died( AActor* thisActor ) override;
	virtual void SetSimulated( bool newIsSimulated ) override;
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
	UFUNCTION( Unreliable, Server, WithValidation )
	void ServerUpdateAssistedVelocitiesState( bool inDrifting, float inInputYaw, float inInputPitch );

	/** Update the clients state from the replicated state */
	UFUNCTION()
	void UseReplicatedState();

	UFUNCTION()
	void SmoothMovementReplication(float DeltaTime);

	UFUNCTION(Server, Unreliable)
	void ReplicateMovementClientToServer(FVector AuthoritativeLoc, FQuat AuthoritativeQuat, FVector AuthoritativeVelocity);

	/** Notify to allow updating of simulated vehicle colors */
	virtual void OnCustomizationDataApplied( const FFactoryCustomizationData& customizationData ) override;

private:
	/** Tick helpers */
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

	/** Clamp angular and linear velocities */
	void ClampVelocities();

	/** handles added linear velocity on throttle */
	void AddedLinearThrottleVelocity();

	/** logic for stabilising roll angular velocity in the air */
	void ApplyRollStabilisation( float deltaTime );

	/** applies assisted acceleration and drifting velocities */
	void ApplyAssistedVelocities( float deltaTime );

	void SetRecordingStatus( ERecordingStatus recordingStatus );

	UFUNCTION()
	void OnFuelAdded( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	UFUNCTION()
	void OnRep_TransferStatusChanged();

public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

	/** Workbench component */
	UPROPERTY( BlueprintReadOnly )
	class UFGWorkBench* mWorkBench;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FTransferStatusChanged );
	/** Broadcast when transfer status is updated */
	UPROPERTY( BlueprintAssignable, Category = "Docking", DisplayName = "OnTransferStatusChanged" )
	FTransferStatusChanged TransferStatusChangedDelegate;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FManualDockingStateChanged );
	/** Broadcast when the conditions for manually docking have changed */
	UPROPERTY( BlueprintAssignable, Category = "Docking", DisplayName = "OnManualDockingStateChanged" )
	FManualDockingStateChanged ManualDockingStateChangedDelegate;

protected:
	friend class AFGWheeledVehicleAIController;
	friend class UFGSplinePathMovementComponent;
	friend class UFGWheeledVehicleDetectionComponent;
	friend class AFGSimulatedWheeledVehicle;
	friend class AFGVehicleSubsystem;
	friend class AFGDrivingTargetList;

	/** This vehicles fuel consumption in MW/s */
	UPROPERTY( EditDefaultsOnly, Category = "Fuel", meta = ( AddAutoJSON = true ) )
	float mFuelConsumption;

	UPROPERTY( SaveGame )
	float mFuelConsumedWhileRecording = 0.0f;

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

	UPROPERTY(Replicated, BlueprintReadOnly, Category="Vehicle|Movement Replication")
	FVector mAuthoritativeLocation;

	UPROPERTY(Replicated, BlueprintReadOnly, Category="Vehicle|Movement Replication")
	FQuat mAuthoritativeRotation;

	UPROPERTY(Replicated, BlueprintReadOnly, Category="Vehicle|Movement Replication")
	FVector mAuthoritativeLinearVel;
	
	FDateTime mLastAccurateLocation;	
	
private:
	/** replicated state of vehicle. */
	UPROPERTY( Transient, Replicated )
	FReplicatedAddedVelocitiesState mReplicatedState;
	
	/** Used for simulated movement along path described by mTargetList */
	UPROPERTY( ReplicatedUsing = OnRep_SimulationMovement )
	class UFGSplinePathMovementComponent* mSimulationMovement;

	/** Used for simulated movement along path described by mTemporaryTargetList */
	//UPROPERTY( ReplicatedUsing = OnRep_TemporarySimulationMovement )
	//class UFGSplinePathMovementComponent* mTemporarySimulationMovement;
	
	/** Inventory for fuel */
	UPROPERTY( VisibleDefaultsOnly, SaveGame, Replicated )
	class UFGInventoryComponent* mFuelInventory;

	/** Inventory for storage */
	UPROPERTY( VisibleDefaultsOnly, SaveGame, Replicated )
	class UFGInventoryComponent* mStorageInventory;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle", meta = ( AddAutoJSON = true ) )
	int32 mInventorySize;

	UPROPERTY()
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
	UPROPERTY( SaveGame, Replicated )
	class AFGDrivingTargetList* mTargetList;

	/** Temporary path to travel, for dynamically constructed paths, for example while docking */
	//UPROPERTY()
	//class AFGDrivingTargetList* mTemporaryTargetList;

	/** Deprecated. Kept for compatibility with legacy saves */
	UPROPERTY( SaveGame )
	class UFGTargetPointLinkedList* mTargetNodeLinkedList;

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

	/** Cached surface material under the first tire */
	UPROPERTY( )
	UPhysicalMaterial* mCachedSurfaceMaterial;

	/** Do we need fuel to drive */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	bool mNeedsFuelToDrive;

	ETransferAnimationState mLastTransferAnimationState = ETransferAnimationState::TS_None;
	float mLastTransferAnimationStartTime = -BIG_NUMBER;

public:
	// Self-driving

	void StopVehicle();
	float AdjustThrottle( float throttle ) const;
	void StartRecording();
	void StopRecording( bool isValid );
	void TickRecording( float deltaTime );
	void PlaceTargetPoint();
	void ClearTargetList();
	void CacheSpeedInKMH();
	bool ShouldStopVehicle() const;
	void SetIsFollowingPath( bool isFollowingPath );
	bool IsAtStation() const { return mCurrentStation != nullptr; }
	int GetSpeedLimit() const { return mSpeedLimit; }
	void StopAllMovement();
	float GetLocalTime() const;
	
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void MoveForward( float axisValue );
	
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void MoveRight( float axisValue );

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void TurnOverVehicle();

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsRecording() const { return mRecordingStatus == ERecordingStatus::RS_RecordingStarted || mRecordingStatus == ERecordingStatus::RS_CompletionPossible; }

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsFollowingPath() const { return mIsFollowingPath; }

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetIsPossessed( bool isPossessed );

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	bool IsPossessed() const { return mIsPossessed; }

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	int GetSpeedInKMH() const { return mSpeedInKMH; }

	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void SetSpeedLimit( int speedLimit ) { mSpeedLimit = speedLimit; }
	
	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsMenuOpen() const { return mIsMenuOpen; }
	
	UFUNCTION( BlueprintCallable, Category = "Vehicle|SelfDriving" )
	void SetIsMenuOpen( bool isMenuOpen ) { mIsMenuOpen = isMenuOpen; }

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsAutopilotEnabled() const { return mIsAutopilotEnabled; }

	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool CanLoadPath() const;
	
	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool CanSavePath() const;

	/** Get the current target */
	UFUNCTION( BlueprintPure, Category = "LinkedList" )
	FORCEINLINE class AFGTargetPoint* GetCurrentTarget() { return mCurrentTarget; }

	/** Set the current target */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void SetCurrentTarget( class AFGTargetPoint* newTarget );
	void UpdateCurrentTarget();

	/** Sets target in the linked list to the next available. Will loop */
	UFUNCTION( BlueprintCallable, Category = "LinkedList" )
	void PickNextTarget();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_Leave();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_ToggleAutoPilot();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_TogglePathVisibility();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_ToggleRecording();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_ClearRecordedPath();

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_SavePath( const FString& saveName );

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_UnsavePath( AFGSavedWheeledVehiclePath* path );

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_LoadPath( class AFGDrivingTargetList* targetList );
	
	UFUNCTION( BlueprintCallable, BlueprintPure = False )
	void FindSavedPaths( const FString& textFilter, bool filterOnVehicleType, TArray< AFGSavedWheeledVehiclePath* >& result ) const;

	UFUNCTION()
	void OnRep_IsFollowingPath();

	UFUNCTION()
	void OnRep_SimulationMovement();
	
	UFUNCTION()
	void OnRep_RecordingStatus();
	
	UFUNCTION()
	void OnRep_IsGhosting();

	UFUNCTION()
	void OnRep_ManualDockingState();

	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle|SelfDriving" )
	void IsFollowingPathChanged( bool isFollowingPath );

	/** Updates the vehicles settings depending on if it should be simulated or "real" */
	virtual void OnIsSimulatedChanged();

	//void CreateTemporaryPath( AFGDrivingTargetList* temporaryTargetList, AFGTargetPoint* nextRegularTarget );

	void TryActivatePathSimulation();

	void AttachSimulatedVehicle();

	FVector GetVelocityVector() const;

	void OnSimulationTargetReached( AFGTargetPoint* newTarget );

	void PickFirstTargetAfterStation();

	AFGTargetPoint* SpawnNewTargetPoint( const FVector& location, const FRotator& rotation, AFGDrivingTargetList* targetList, int targetSpeed, AFGTargetPoint* afterTarget = nullptr );

	void OnTargetWasForceClaimed( class AFGTargetPoint* target, class AFGWheeledVehicle* claimant );

	class UFGVehicleCollisionBoxComponent* FindCollisionBox() const;

	void StartGhosting();

	void TryLeaveSimulatedMode();
	bool IsAboveSolidGround( const FTransform& transform ) const;
	bool IsLeaveSimulationFriendly( const FTransform& transform ) const;

	void GiveWayTo( const AFGWheeledVehicle* other );

	bool WasFuelAdded() const { return mWasFuelAdded; }

private:
	float CalculateAutomatedFuelToConsume( float deltaTime );

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStopRecording, bool, success );
	UPROPERTY( BlueprintAssignable, Category = "Vehicle" )
	FOnStopRecording OnStopRecordingDelegate;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnStartRecording );
	UPROPERTY( BlueprintAssignable, Category = "Vehicle" )
	FOnStartRecording OnStartRecordingDelegate;

	UPROPERTY( EditDefaultsOnly, Category = "SelfDriving" )
	TSubclassOf< AFGTargetPoint > mTargetPointClass;

	UPROPERTY( EditDefaultsOnly, Category = "SelfDriving" )
	float mGhostingTimeout = 20.0f;

	UPROPERTY( EditDefaultsOnly, Category = "SelfDriving" )
	float mMaxDistanceToSimulation = 500.0f;

	float mSquaredDistanceToClosestPlayer = 0.0f;

private:
	// Self-driving
	int mSpeedInKMH = 0;
	bool mIsMenuOpen = false;
	float mRecordCounter = 0.0f;

	FVector mLastVehiclePosition = { 0.0f, 0.0f, 0.0f };
	float mLastVehicleYaw = 0.0f;
	float mAverageSpeed = 0.0f;
	float mYawVelocity = 0.0f;
	float mAverageYawVelocity = 0.0f;
	//float mVelocity = 0.0f;
	float mSpeed = 0.0f;
	//FVector mVelocityVector = { 0.0f, 0.0f, 0.0f };
	float mAcceleration = 0.0f;
	bool mIsReversing = false;

	int mPostSimulationImpulseCount = 0;
	//int mPostSimulationImpulseCount = 0;
	//FVector mLastSimulationVelocity = { 0.0f, 0.0f, 0.0f };
	//float mLastSimulationVelocitySquared = 0.0f;

	UPROPERTY( Replicated, SaveGame )
	int mSpeedLimit = -1;

	//UPROPERTY( SaveGame )
	float mDesiredSteering = 0.0f;

	//UPROPERTY( SaveGame )
	float mDesiredThrottle = 0.0f;

	//UPROPERTY( SaveGame )
	float mDesiredBrake = 0.0f;

	//UPROPERTY( SaveGame )
	bool mDesiredHandbrake = false;

	UPROPERTY( ReplicatedUsing = OnRep_IsFollowingPath )
	bool mIsFollowingPath = false;

	UPROPERTY( Replicated, SaveGame )
	bool mIsAutopilotEnabled = false;

	UPROPERTY( Replicated )
	bool mIsPossessed = false;

	/** The station to which this vehicle is currently docked */
	UPROPERTY( Replicated )
	class AFGBuildableDockingStation* mCurrentStation = nullptr;

	/** The station at which this vehicle is currently being refueled */
	class AFGBuildableDockingStation* mRefuelingStation = nullptr;

	UPROPERTY( ReplicatedUsing = OnRep_ManualDockingState )
	EManualDockingState mManualDockingState = EManualDockingState::MDS_NoDocking;

	/** Current node */
	UPROPERTY( SaveGame, Replicated )
	class AFGTargetPoint* mCurrentTarget;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_RecordingStatus )
	ERecordingStatus mRecordingStatus = ERecordingStatus::RS_NoRecording;

	class AFGTargetPoint* mStoredTarget = nullptr;

	UPROPERTY()
	class AFGSimulatedWheeledVehicle* mSimulatedVehicle;

	FVector mBoundingBoxExtent = FVector::ZeroVector;
	FVector mBoundingBoxOffset = FVector::ZeroVector;
	float mWheelRadius = 0.0f;

	float mThrottleSampleCount = 0.0f;
	float mThrottleSampleSum = 0.0f;

	/** Was fuel transferred from station to vehicle during the current docking */
	UPROPERTY( SaveGame )
	bool mWasFuelAdded = false;

	float mTimeStationWasEntered = 0.0f;

	bool mIsLookedAt = false;

	UPROPERTY( ReplicatedUsing = OnRep_IsGhosting )
	bool mIsGhosting = false;

	bool mWantsToStopGhosting = false;

	bool mAwaitingSubsystem = false;

	UPROPERTY( SaveGame )
	bool mHasAutomatedFuelConsumption = false;

	UPROPERTY( SaveGame )
	float mActualAutomatedFuelConsumptionSinceStart = 0.0f;

	UPROPERTY( SaveGame )
	float mAutomatedFuelConsumptionStart = 0.0f;

	UPROPERTY( SaveGame )
	float mAutomatedFuelConsumptionTimeSkipped = 0.0f;

	// If > 0, the number of blocks until this vehicle reaches itself in a deadlock. If 0 there is no deadlock.
	int mDeadlockedAtDepth = 0;

	bool mCanTransitionToRealMode = true;

	const AFGWheeledVehicle* mVehicleGivenWayTo = nullptr;

	float mNextTimeToCheckForLost = 0.0f;
};
