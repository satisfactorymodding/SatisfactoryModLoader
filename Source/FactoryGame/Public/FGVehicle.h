// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGUseableInterface.h"
#include "FGSignificanceInterface.h"
#include "FGSaveInterface.h"
#include "AI/FGAggroTargetInterface.h"
#include "FGDriveablePawn.h"
#include "FGDismantleInterface.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGDockableInterface.h"
#include "FGColorInterface.h"
#include "FGBuildableSubsystem.h"
#include "FGVehicle.generated.h"

class FDebugDisplayInfo;

/** Physics data we want to be able to restore, we store the bone name to be able to change the bone structure in updates */
USTRUCT()
struct FACTORYGAME_API FVehiclePhysicsData
{
	GENERATED_BODY()

	/** Default ctor */
	FVehiclePhysicsData() {}

	// Bone that have this information
	FName BoneName;
	// Linear velocity of the bone
	FRigidBodyState BodyState;

	friend FArchive& operator << ( FArchive& ar, FVehiclePhysicsData& physics );

public:
	FORCEINLINE ~FVehiclePhysicsData() = default;
};

/**
 * Vehicle has a driver but has empty passenger seats                                                                    
 */
UCLASS()
class FACTORYGAME_API UFGUseState_VehicleHasDriver : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_VehicleHasDriver() : Super() { mIsUsableState = true; }

public:
	FORCEINLINE ~UFGUseState_VehicleHasDriver() = default;
};

/**
 * Vehicle is in water, can't enter
 */
UCLASS()
class FACTORYGAME_API UFGUseState_VehicleInWater : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_VehicleInWater() : Super() { mIsUsableState = false; }

public:
	FORCEINLINE ~UFGUseState_VehicleInWater() = default;
};

/**
 * Vehicle is fully occupied                                                                    
 */
UCLASS()
class FACTORYGAME_API UFGUseState_VehicleOccupied : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_VehicleOccupied() : Super() { mIsUsableState = false; }

public:
	FORCEINLINE ~UFGUseState_VehicleOccupied() = default;
};

USTRUCT()
struct FACTORYGAME_API FVehicleSeat
{
	GENERATED_BODY()

	FVehicleSeat();

	/** Seat class to spawn. */
	UPROPERTY( EditDefaultsOnly, NotReplicated )
	TSubclassOf< class AFGPassengerSeat > SeatClass;

	/** Socket to attach character to. */
	UPROPERTY( EditDefaultsOnly, NotReplicated )
	FName SitSocket;

	/** Is seat and characters in this seat visible. */
	UPROPERTY( EditDefaultsOnly, NotReplicated )
	bool IsVisible;

	/** Animation to play on characters in this seat. */
	UPROPERTY( EditDefaultsOnly, NotReplicated )
	UAnimSequence* SitAnimation;

	/** How much damage do we take in this seat. */
	UPROPERTY( EditDefaultsOnly, NotReplicated )
	float DamageMultiplier;

	/** Pawn we possess when entering this seat. */
	UPROPERTY()
	class AFGDriveablePawn* mSeatPawn;

	/** Info about the character in this seat. */
	UPROPERTY()
	class AFGCharacterPlayer* mCharacter;
	UPROPERTY()
	class AController* mController;

public:
	FORCEINLINE ~FVehicleSeat() = default;
};

/**
 * Base class for all vehicles in the game, cars, train etc.
 */
UCLASS()
class FACTORYGAME_API AFGVehicle : public AFGDriveablePawn, public IFGUseableInterface, public IFGDismantleInterface, public IFGAggroTargetInterface, public IFGDockableInterface, public IFGColorInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual bool IsRelevancyOwnerFor( const AActor* Actor, const AActor* Owner, const AActor* ConnectionActor ) const override;

	AFGVehicle();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Destroyed() override;
	virtual void Tick( float dt ) override;
	virtual float TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor interface

	// Begin APawn interface
	virtual class UPawnMovementComponent* GetMovementComponent() const override;
	// End APawn interface

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFSaveInterface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual	float GetSignificanceBias() override;
	virtual float GetSignificanceRange() override;
	//End IFGSignificanceInterface

	//~ Begin IFGColorInterface
	FLinearColor GetPrimaryColor_Implementation();
	FLinearColor GetSecondaryColor_Implementation();
	bool GetCanBeColored_Implementation(){ return true; }
	void StartIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter );
	void StopIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter );
	//~ End IFGColorInterface

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

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation( AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( AFGCharacterPlayer* byCharacter ) override;
	//~ End IFGDismantleInferface

	// Begin IFGAggroTargetInterface
	virtual void RegisterIncomingAttacker_Implementation( class AFGEnemyController* forController ) override;
	virtual void UnregisterAttacker_Implementation( class AFGEnemyController* forController ) override;
	virtual AActor* GetActor_Implementation() override;
	virtual float GetEnemyTargetDesirability_Implementation( class AFGEnemyController* forController ) override;
	virtual bool ShouldAutoregisterAsTargetable_Implementation() const override;
	virtual class UPrimitiveComponent* GetTargetComponent_Implementation() override;
	virtual bool IsAlive_Implementation() const override;
	virtual FVector GetAttackLocation_Implementation() const override;
	// End IFGAggroTargetInterface

	/** Getter for simulation distance */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Vehicle" )
	FORCEINLINE float GetSimulationDistance() { return mSimulationDistance; }

	/** Getter for significance */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Vehicle|Significance" )
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }

	/** Called in Construct from the hologram. */
	void SetBuiltWithRecipe( TSubclassOf< class UFGRecipe > recipe ) { mBuiltWithRecipe = recipe; }
	/** Getter for the built with recipe. */
	FORCEINLINE TSubclassOf< class UFGRecipe > GetBuiltWithRecipe() const { return mBuiltWithRecipe; }

	/** Skel mesh for this vehicle **/
	class USkeletalMeshComponent* GetMesh() const;

	/** Health component for this vehicle */
	UFUNCTION( BlueprintPure, Category = "Damage" )
	class UFGHealthComponent* GetHealthComponent();

	/** Is this vehicle destructible */
	UFUNCTION( BlueprintPure, Category = "Damage" )
	FORCEINLINE bool IsDestructible() { return mIsDestructible; }
	
	// Begin ADriveablePawn interface

	/** Overridden to reset self driving status */
	virtual bool DriverEnter( class AFGCharacterPlayer* driver ) override;
	virtual bool DriverLeave( bool keepDriving = false ) override;
	// End ADriveablePawn interface

	/** @return true if an ai can start driving this vehicle; false otherwise. (server only) */
	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	virtual bool CanSelfDriverEnter( class AAIController* ai ) const;

	/** Let an ai enter the vehicle. Will not succeed if there is a human driver in the vehicle already. */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Vehicle|SelfDriving" )
	virtual bool SelfDriverEnter( class AAIController* ai );

	/** @return true if there's an ai controlling this vehicle; false otherwise. */
	UFUNCTION( BlueprintPure, Category = "Vehicle|SelfDriving" )
	bool IsSelfDriving() const { return mIsSelfDriving; }

	/** Check if any passenger seats are available */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	bool HasAnyPassengerSeatAvailable() const { return false; }

	/**
	 * Kicks out all players in the vehicle including its passengers
	 * Can be called on both client and server.
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Vehicle" )
	void KickAllPlayers();

	/** Adds the pushed character to the mPushedCharacters array */
	FORCEINLINE void AddPushedCharacter( class AFGCharacterBase* character ) { mPushedCharacters.Add( character ); }
	/** returns true if this vehicle has already pushed this character */
	FORCEINLINE bool HasPushedCharacter( class AFGCharacterBase* character ) { return mPushedCharacters.Contains( character ); }

	// Begin FFactoryStatHelpers Functions
	void Stat_Cost( TArray< FItemAmount >& out_amount ) const;
	void Stat_StockInventory( TArray< FItemAmount >& out_amount ) const;
	// End FFactoryStatHelpers Functions

	/** Getter and setter for the construction ID issued by server used to identify buildables when constructed on client */
	FORCEINLINE void SetNetConstructionID( FNetConstructionID netConstructionID ) { mNetConstructionID = netConstructionID; }
	FNetConstructionID GetNetConstructionID() const { return mNetConstructionID; }

	/** Is this vehicle forced to be in real mode */
	FORCEINLINE bool GetForceRealMode() {return mForceRealMode; }

	/** Is this vehicle forced to be in simulation mode */
	FORCEINLINE bool GetForceSimulationMode() { return mForceSimulationMode; }

	/** Toggles what movement mode we are using */
	void SetSimulation( bool newIsSimulating );

	/** Is the movement being simulated? */
	UFUNCTION( BlueprintPure, Category = "Simulation" )
	FORCEINLINE bool IsSimulated() { return mIsSimulated; }
private:
	/** Rep notifies */
	UFUNCTION()
	void OnRep_IsSimulated();
protected:
	/** Updates the vehicles settings depending on if it should be simulated or "real" */
	virtual void OnSimulationChanged(){}
	/** Notifies from our health component */
	UFUNCTION()
	virtual void OnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );
	UFUNCTION()
	virtual void Died( AActor* thisActor );

	/** We have taken damage */
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage", meta = ( DisplayName = "OnTakeDamage" ) )
	void NotifyOnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );
	/** We have died */
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage", meta = ( DisplayName = "Died" ) )
	void ReceiveDied( AActor* thisActor );

	// Begin AFGDriveablePawn interface
	virtual void OnDrivingStatusChanged() override;
	// End AFGDriveablePawn interface

	/** Called when the vehicle (engine) is started. */
	UFUNCTION( BlueprintImplementableEvent, Meta = ( DisplayName = "OnVehicleStartup" ) )
	void ReceiveOnVehicleStartup();
	/** Called when the vehicle (engine) is shut down. */
	UFUNCTION( BlueprintImplementableEvent, Meta = ( DisplayName = "OnVehicleShutDown" ) )
	void ReceiveOnVehicleShutDown();

	/** Update if we are submerged in water, SERVER ONLY */
	void UpdateSubmergedInWater( float deltaTime );
	/** Our status of being submerged in water has updated */
	void SubmergedInWaterUpdated( bool newIsSubmerged );
	/** Returns true if we are submerged in water */
	bool IsSubmergedInWater() const;

	/** How much do we get back when selling this vehicle. Not consolidated. */
	void GetDismantleRefundReturns( TArray< FInventoryStack >& out_returns ) const;
	/** How much do we get from the inventories when selling this vehicle. Not consolidated. */
	virtual void GetDismantleInventoryReturns( TArray< FInventoryStack >& out_returns ) const;
	/** If blueprint has anything to return when this vehicle is dismantled. Not consolidated. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Dismantle" )
	void GetDismantleBlueprintReturns( TArray< FInventoryStack >& out_returns ) const;

	/** Destroy this vehicle. Used by dismantle. */
	virtual void DestroyVehicle();

	/** Show the outline for the vehicle. */
	void ShowOutline( EOutlineColor color ) const;
	/** Hide the outline for the vehicle. */
	void HideOutline();
private:
	/** Helpers */
	void SetSelfDriving( bool newSelfDriving );

	/** Notifies from out mesh */
	UFUNCTION()
	void UpdatePhysicsVolume( APhysicsVolume* physicsVolume );

public:
	/** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName VehicleMeshComponentName;

	/** The human readable name for this vehicle. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Vehicle" )
	FText mDisplayName;

	/** The human readable description for this vehicle. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Vehicle", meta = ( MultiLine = true ) )
	FText mDescription;

	/** Hologram to build this class with. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TSubclassOf< class AFGHologram > mHologramClass;

protected:
	/** The main skeletal mesh associated with this Vehicle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Vehicle", meta = ( AllowPrivateAccess = "true" ) )
	class USkeletalMeshComponent* mMesh;

	/** Keeps track of our current health */
	UPROPERTY( SaveGame, Replicated, VisibleAnywhere, Category = "Health" )
	class UFGHealthComponent* mHealthComponent;

	/** If any of these locations enters water, then we are unusable */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TArray< FVector > mDisabledByWaterLocations;

	/** Flag for whether this vehicle is being dismantled */
	uint8 mIsDismantled : 1;

	/** Flag to indicate whether the dismantle material should be active */
	uint8 mPendingDismantleHighlighted : 1;

	/** ID given from server when constructed. Has not been assigned a value by server if 0. */
	UPROPERTY( transient, replicated )
	FNetConstructionID mNetConstructionID;

private:
	/** Recipe this vehicle was built with, e.g. used for refunds and stats. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< class UFGRecipe > mBuiltWithRecipe;

	/** The primary color of this buildable */
	UPROPERTY( SaveGame )
	FLinearColor mPrimaryColor;

	/** The primary color of this buildable */
	UPROPERTY( SaveGame )
	FLinearColor mSecondaryColor;

	/** If this vehicle is self driving. */
	UPROPERTY( Replicated )
	bool mIsSelfDriving;

	/** The AI that controls this vehicle when self-driving is activated. */
	UPROPERTY()
	class AAIController* mSelfDrivingController;

	/** Saved like this, as we can't store it in serialize, as it will be killed  */
	UPROPERTY()
	TArray<FVehiclePhysicsData> mStoredPhysicsData;

	/** Characters we pushed this frame. Reset every frame.  */
	TArray< AFGCharacterBase* > mPushedCharacters;

	/** Sound played when this vehicle is created */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle|Sound" )
	class UAkAudioEvent* mConstructSound;

	/** Can this vehicle be destroyed by damage? */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	uint8 mIsDestructible : 1;

	/** If true, then we are touching a water volume */
	uint8 mTouchingWater:1;

	/** If true, then we are submerged in water */
	UPROPERTY( Replicated )
	uint8 mIsSubmergedInWater:1;

	/** base damping forces to revert to in case a vehicle is no longer submerged */
	float mBaseAngularDamping;
	float mBaseLinearDamping;

	/** increased angular damping when vehicle is under water */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mSubmergedAngularDamping;
	/** increased linear damping when vehicle is under water */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mSubmergedLinearDamping;
	/** upwards force applied to vehicles when underwater */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mSubmergedBouyantForce;

	/** Gas damage typ that should be redirected to the driver*/
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TSubclassOf< class UFGDamageType > mGasDamageType; 

	/** Indicates if the vehicle is within significance distance */
	uint8 mIsSignificant : 1;

	/** A bias to the significance value */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceBias;

	/* Forces vehicle to be in simulation mode */
	bool mForceSimulationMode;

	/* Forces vehicle to be in real mode */
	bool mForceRealMode;

	/** Is the movement being simulated? */
	UPROPERTY( ReplicatedUsing = OnRep_IsSimulated, SaveGame )
	bool mIsSimulated;
protected:
	/** Indicates if the vehicle should be handled by significance manager */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	uint8 mAddToSignificanceManager : 1;

	/** Range that this vehicle should be significant within */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;

	/** Range after we disable simulation (remove collision) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mSimulationDistance;

public:
	FORCEINLINE ~AFGVehicle() = default;
};
