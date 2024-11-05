// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGUseableInterface.h"
#include "FGSignificanceInterface.h"
#include "FGActorRepresentationInterface.h"
#include "FGSaveInterface.h"
#include "FGDriveablePawn.h"
#include "FGDismantleInterface.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGDockableInterface.h"
#include "FGColorInterface.h"
#include "FGBuildableSubsystem.h"
#include "FGClearanceInterface.h"
#include "FGVehicle.generated.h"

class UFGDamageType;
class FDebugDisplayInfo;

/** Physics data we want to be able to restore, we store the bone name to be able to change the bone structure in updates */
USTRUCT()
struct FVehiclePhysicsData
{
	GENERATED_BODY()
	
	FVehiclePhysicsData() {}

	// Bone that have this information
	FName BoneName;
	// Linear velocity of the bone
	FRigidBodyState BodyState;

	friend FArchive& operator << ( FArchive& ar, FVehiclePhysicsData& physics );
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
};

/**
 * UseState representing the WorkBench.
 */
UCLASS()
class FACTORYGAME_API UFGUseState_WorkBench : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_WorkBench() : Super() { mIsUsableState = true; }
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
};

/**
 * Base class for all vehicles in the game, cars, train etc.
 */
UCLASS()
class FACTORYGAME_API AFGVehicle : public AFGDriveablePawn, public IFGUseableInterface, public IFGDismantleInterface, public IFGDockableInterface, public IFGColorInterface, public IFGSignificanceInterface, public IFGClearanceInterface
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
	virtual float GetSignificanceRange() override;
	//End IFGSignificanceInterface

	// Begin IFGClearanceInterface
    virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
    // End IFGClearanceInterface

	float GetJumpPadForceMultiplier() const { return mJumpPadForceMultiplier; }
	
	virtual void OnBuildEffectFinished();
	virtual void OnDismantleEffectFinished();
	virtual void ExecuteBuildEffect();
	void TurnOffAndDestroy();
	void PlayDismantleEffects();
	
	//~ Begin IFGColorInterface
	void SetCustomizationData_Native( const FFactoryCustomizationData& customizationData, bool skipCombine = false );
	void SetCustomizationData_Implementation( const FFactoryCustomizationData& colorData );
	void ApplyCustomizationData_Native( const FFactoryCustomizationData& customizationData );
	FFactoryCustomizationData& GetCustomizationData_Native() { return mCustomizationData; }
	FFactoryCustomizationData GetCustomizationData_Implementation() { return mCustomizationData; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Implementation() { return mFactorySkinClass; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Native() { return mFactorySkinClass; }
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Native();
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Implementation();
	bool GetCanBeColored_Implementation(){ return true; }
	virtual bool IsColorApplicationDeferred() { return false; }
	virtual bool CanApplyDeferredColorToBuildable( FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ){ return false; }
	virtual void ApplyDeferredColorToBuildable( FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController ){};
	void StartIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter, bool isValid = true );
	void StopIsAimedAtForColor_Implementation( class AFGCharacterPlayer* byCharacter );
	//~ End IFGColorInterface

	//~ Begin IFGDockableInterface
	virtual bool CanDock_Implementation( EDockStationType atStation ) const override { return false; }
	virtual class UFGInventoryComponent* GetDockInventory_Implementation() const override { return nullptr; }
	virtual class UFGInventoryComponent* GetDockFuelInventory_Implementation() const override { return nullptr; }
	virtual void WasDocked_Implementation( class AFGBuildableDockingStation* atStation ) override {}
	virtual void WasUndocked_Implementation() override {}
	virtual void OnBeginLoadVehicle_Implementation() override {}
	virtual void OnBeginUnloadVehicle_Implementation() override {}
	virtual void OnTransferComplete_Implementation() override {}
	//~ End IFGDockableInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	//~ End IFGUseableInterface

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void PreUpgrade_Implementation() override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	virtual void StartIsLookedAtForDismantle_Implementation( AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	virtual FText GetDismantleDisplayName_Implementation(AFGCharacterPlayer* byCharacter) const override;
	virtual bool SupportsDismantleDisqualifiers_Implementation() const override { return true; }
	virtual void GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const override;
	//~ End IFGDismantleInferface

	void SetBuildEffectInstigator(AActor* Actor) { mBuildEffectInstigator = Actor; }
	
	UFUNCTION( Reliable, NetMulticast )
	virtual void NetMulticast_Dismantle();
	
	/** Getter for simulation distance */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Vehicle" )
	FORCEINLINE float GetSimulationDistance() const { return mSimulationDistance; }

	/** Getter for significance */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Vehicle|Significance" )
	FORCEINLINE bool GetIsSignificant() const { return mIsSignificant; }

	/** Called in Construct from the hologram. */
	void SetBuiltWithRecipe( TSubclassOf< class UFGRecipe > recipe ) { mBuiltWithRecipe = recipe; }
	
	/** Getter for the built with recipe. */
	FORCEINLINE TSubclassOf< class UFGRecipe > GetBuiltWithRecipe() const { return mBuiltWithRecipe; }
	TSubclassOf< class UFGItemDescriptor > GetBuiltWithDescriptor() const;
	template< class C > TSubclassOf< C > GetBuiltWithDescriptor() const { return *GetBuiltWithDescriptor(); }

	/** Can this vehicle be sampled for the build gun */
	virtual bool CanBeSampled();

	/** Skel mesh for this vehicle **/
	class USkeletalMeshComponent* GetMesh() const;

	/** Health component for this vehicle */
	UFUNCTION( BlueprintPure, Category = "Damage" )
	class UFGHealthComponent* GetHealthComponent() const { return mHealthComponent; }

	/** Is this vehicle destructible */
	UFUNCTION( BlueprintPure, Category = "Damage" )
	FORCEINLINE bool IsDestructible() const { return mIsDestructible; }
	
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

	void SetForceRealMode( bool forceRealMode );

	void SetForceSimulationMode( bool forceSimulationMode );

	/** Is this vehicle forced to be in real mode */
	FORCEINLINE bool GetForceRealMode() const { return mForceRealMode; }

	/** Is this vehicle forced to be in simulation mode */
	FORCEINLINE bool GetForceSimulationMode() const { return mForceSimulationMode; }

	/** Toggles what movement mode we are using */
	virtual void SetSimulated( bool newIsSimulated );

	/** Is the movement being simulated? */
	UFUNCTION( BlueprintPure, Category = "Simulation" )
	FORCEINLINE bool IsSimulated() const { return mIsSimulated; }

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	/** Call to update colors on mesh primative data */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );

	/** Update skins on all meshes */
	UFUNCTION( BlueprintCallable, Category = "Buildable|Customization" )
	void ApplySkinData( TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc );

	UFUNCTION()
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > GetDefaultSwatchCustomizationOverride( UObject* worldContext );

	UFUNCTION( BlueprintNativeEvent, Category = "Buildable|Customization" )
	void OnSkinCustomizationApplied( TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > skin );

	virtual FVector GetVehicleRealActorLocation() const;

	/** Returns true if we are submerged in water */
	UFUNCTION( BlueprintPure )
	bool IsSubmergedInWater() const;

	void SetOwningPlayerState( class AFGPlayerState* playerState );

	void SetMatchCustomizationWithPlayerState( bool shouldMatch );
	
protected:
	/** Called when customization data is applied. Allows child vehicles to update their simulated vehicles to keep colors synced */
	virtual void OnCustomizationDataApplied( const FFactoryCustomizationData& customizationData );

	/** Called when customization data gets set. */
	virtual void OnCustomizationDataSet( const FFactoryCustomizationData& previousData );

private:
	/** Rep notifies */
	UFUNCTION()
	void OnRep_IsSimulated();

	void ToggleEntireVehicleOutline( const bool isOutlined, const EOutlineColor& outlineColor );
	
protected:
	/** Updates the vehicles settings depending on if it should be simulated or "real" */
	virtual void OnIsSimulatedChanged() {}

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
	virtual void SubmergedInWaterUpdated( bool newIsSubmerged );

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

	/** Called to update the camera when this vehicle is possessed by a player. */
	UFUNCTION( BlueprintImplementableEvent )
	void UpdateCamera( float DeltaTime );

private:
	/** Helpers */
	void SetSelfDriving( bool newSelfDriving );

	/** Notifies from out mesh */
	UFUNCTION()
	void UpdatePhysicsVolume( APhysicsVolume* physicsVolume );
	
	/** Let the client know custom color / material information has been applied to the vehicle */
	UFUNCTION()
	void OnRep_CustomColorData();

	UFUNCTION()
	void OnRep_OwningPlayerState( class AFGPlayerState* previousPlayerState );

	UFUNCTION()
	void OnPlayerCustomizationDataChanged( const struct FPlayerCustomizationData& newCustomizationData );

	void UpdateCustomizationDataFromPlayerState();

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

	/** Keeps track of active DOT effects applied to us. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	class UFGDotReceiverComponent* mDOTReceiverComponent;

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

	/** Custom Color/Mat data. Stored in a TArray so it can be variable (or 0 size) to reduce save footprint since many buildings will only utilize the slot index */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CustomColorData )
	FFactoryCustomizationData mCustomizationData;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TSubclassOf< class UFGFactorySkinActorData > mFactorySkinClass;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle" )
	TSubclassOf< class UFGSwatchGroup > mSwatchGroup;
	
	UPROPERTY( BlueprintReadWrite )
	USkeletalMeshComponent* mOptionalWorkBenchComponent = nullptr;

	UPROPERTY( BlueprintReadWrite )
	class UBoxComponent* mOptionalWorkBenchBox = nullptr;

	/** Recipe this vehicle was built with, e.g. used for refunds and stats. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< class UFGRecipe > mBuiltWithRecipe;

	UPROPERTY( Replicated, meta = ( NoAutoJson = true ) )
	AActor* mBuildEffectInstigator;

	/** The player state that "owns" this vehicle. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_OwningPlayerState )
	class AFGPlayerState* mOwningPlayerState;

	/** Whether or not to match customization data with the player that "owns" the vehicle.  */
	UPROPERTY( EditDefaultsOnly, SaveGame, Replicated, Category = "Vehicle" )
	bool mMatchCustomizationDataWithPlayerState;

private:
	/** Clearance data of this vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TArray< FFGClearanceData > mClearanceData;

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

	/** Amount of time in seconds that have passed since this vehicle has been last submerged */
	float timeBeforeCanStopBeingSubmerged = 0.0f;

	/** base damping forces to revert to in case a vehicle is no longer submerged */
	float mBaseAngularDamping;
	float mBaseLinearDamping;

	/** increased angular damping when vehicle is under water */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mSubmergedAngularDamping;
	/** increased linear damping when vehicle is under water */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mSubmergedLinearDamping;

	/** Damage types that should be redirected to the driver. Damages here act as damage multipliers (i.e setting it to gas damage with 0.5 damage will x0.5 the incoming damages */
	UPROPERTY( EditDefaultsOnly, Category= "Vehicle" )
	TArray< TSubclassOf< UFGDamageType > > mDamageTypesRedirectedToDriver;
	
	/** How much to to multiply the jump pad force with. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mJumpPadForceMultiplier;

	/** Indicates if the vehicle is within significance distance */
	uint8 mIsSignificant : 1;

	/* Forces vehicle to be in simulation mode */
	bool mForceSimulationMode;

	/* Forces vehicle to be in real mode */
	bool mForceRealMode;
	
	UPROPERTY()
	class UFGMaterialEffect_Build* mActiveBuildEffect;
	
	/** Flag for whether the build effect is active */
	uint8 mBuildEffectIsPlaying : 1;
	
protected:
	/** Is the movement being simulated? */
	UPROPERTY( ReplicatedUsing = OnRep_IsSimulated, SaveGame )
	bool mIsSimulated;

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
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UMaterialInterface* mActorRepresentationCompassMaterial;

	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Representation" )
	FText mMapText;

	bool IsPlayingBuildEffect() const { return mBuildEffectIsPlaying; }
};
