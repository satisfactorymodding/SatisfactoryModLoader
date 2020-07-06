// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "../ItemAmount.h"
#include "../FGBuildableSubsystem.h"
#include "../FGConstructionMessageInterface.h"
#include "HologramSplinePathMode.h"
#include "Script.h"
#include "../ItemAmount.h"
#include "Components/MeshComponent.h"
#include "FGHologram.generated.h"

//For UE4 Profiler ~ Stat Group
DECLARE_STATS_GROUP( TEXT( "Hologram" ), STATGROUP_Hologram, STATCAT_Advanced );

/**
 * Enum for different scroll modes a hologram can implement.
 */
UENUM( BlueprintType )
enum class EHologramScrollMode : uint8
{
	HSM_NONE = 0					UMETA( DisplayName = "None" ),
	HSM_ROTATE = 1					UMETA( DisplayName = "Rotate" ),
	HSM_RAISE_LOWER = 2				UMETA( DisplayName = "Raise/Lower" ),
	HSM_SPLINE_PATH_MODE = 3		UMETA( DisplayName = "Spline Mode" ),
	HSM_MAX							UMETA( Hidden )
};

/**
 * The base class for all holograms.
 * It defines the interface all "buildable things" must follow.
 *
 * Note : Do not use SetActorLocation(), SetActorRotation() etc to move a hologram.
 *       Use SetHologramLocationAndRotation() instead as this handles snapping etc.
 *
 *
 */
UCLASS( hidecategories = ( "Actor", "Input", "Replication", "Rendering", "Actor Tick" ) )
class FACTORYGAME_API AFGHologram : public AActor, public IFGConstructionMessageInterface
{
	GENERATED_BODY()
public:
	AFGHologram();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual bool IsNetRelevantFor( const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation ) const override;

	/** Spawns a hologram from recipe */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Hologram" )
	static AFGHologram* SpawnHologramFromRecipe( TSubclassOf< class UFGRecipe > inRecipe, AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator = nullptr );

	/** Spawns a hologram from recipe and sets is as child to specified parent */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Hologram" )
	static AFGHologram* SpawnChildHologramFromRecipe( AFGHologram* parent, TSubclassOf< UFGRecipe > recipe, AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator = nullptr );

	/** Set the item descriptor for this hologram, called when setting up the hologram, before BeginPlay. */
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Get the item descriptor for the building being built. */
	TSubclassOf< class UFGItemDescriptor > GetItemDescriptor() const;

	/** Set who is building with this hologram. */
	void SetConstructionInstigator( APawn* instigator ) { mConstructionInstigator = instigator; }
	FORCEINLINE APawn* GetConstructionInstigator() const { return mConstructionInstigator; }

	/** Applies the hologram's net data serailization needed to send a valid constructHologramMessage */
	void SerializeOntoConstructHologramMessage( FConstructHologramMessage& message );

	/** Deserializes hologram data and applies it to the hologram. This will also run hologram validation. */
	void DeserializeFromConstructHologramMessage( FConstructHologramMessage& message, class AFGBuildGun* buildGun );

	/** Net Construction Messages */
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void ClientPreConstructMessageSerialization() override;
	virtual void ServerPostConstructMessageDeserialization() override;
	virtual void OnConstructMessagedDeserialized_Implementation() override;

	/**
	 * Do all custom initialization here.
	 */
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void SetActorHiddenInGame( bool newHidden ) override;
	// End Actor interface

	/**
	 * Let the hologram check if the hit result is valid.
	 *Indicates to build gun if the placement logic an updating should continue or not. If hit is not valid, no location updating will be set, and the hologram will be hidden.

	 * @return true if the hit result is invalid for SetLocationAndRotation, this causes the hologram to be hidden and updating to be skipped.
	 */
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const;

	/**
	 * See if the hit actor can be upgraded with this hologram and set the holograms location and rotation accordingly.
	 * @return true if an upgrade is possible; false if not.
	 */
	virtual bool TryUpgrade( const FHitResult& hitResult );

	/**
	 * Adjust the placement for the ground, this should be the last step in the placement. Usually for things such as updating legs on buildings and such.
	 */
	virtual void AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation );

	/**
	 * See if we can snap to the hit actor. Used for holograms snapping on top of ex resource nodes, other buildings like stackable poles and similar.
	   If returning true, we assume location and snapping is applied, and no further location and rotation will be updated this frame by the build gun.
	 * @return true if we can snap; false if not.
	 */
	virtual bool TrySnapToActor( const FHitResult& hitResult );

	/**
	 * Update the holograms location and rotation. Can preform it's own logics, like snapping and various other things in here. 
	 Will only be called if we have a valid hit result and did not snap.
	 *
	 * @param hitResult - the hit result from the trace preformed in BuildGun
	 */
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult );

	/**
	 * Notify that the hologram hit result is NOT valid and that the hologram is sett to hidden in game. Will usually trigger when E.g. Aiming up in the sky. 
	 (Called when the IsValidHitResult returns false.)
	 */
	virtual void OnInvalidHitResult();

	/**
	 * Checks placement and cost. Default behavior is to call functions, CheckCanAfford, consider placement if the actor is visible and not an upgrade. Also responsible for applying the valid/invalid render materials with the SetMaterial function. Will do the same on all active child holograms.
	 */
	void ValidatePlacementAndCost( class UFGInventoryComponent* inventory );
	
	/**
	 * Place parts of the hologram/performs a step in the build process for each call to this function.
	 * For every build execute input this function is called till it returns true to indicate that it's done.
	 * When it returns true, Construct can be called to construct the actor.
	 *
	 * There are two modes on the build gun. 
	 * One mode where each placement requires a primary fire execution, 
	 * but also one where a step is executed on press and release.
	 * 
	 * //[DavalliusA:Wed/20-11-2019] might not need this. We might simply block other function calls during the initial time in these cases... or we can have problem relying on "ValidatePlacementAndCost" based on input, and then executing with this variable true....
	 * @param isInputFromARelease - will be true if the hold mode is executed very quickly, as it's likely a user didn't intend to change the input. Enabling quick placement of the default settings.
	 *
	 * @return - true if placement is finished and Construct can be called; false if placement is not finished.
	 */
	virtual bool DoMultiStepPlacement(bool isInputFromARelease);

	/**
	 * Update scroll input on the hologram. Default is to branch on mScrollMode and call ScrollRotate() or change the mScrollRaiseLowerValue with the input.
	 * @param delta	The scroll direction and amount, negative is down and positive is up.
	 */
	virtual void Scroll( int32 delta );

	///**
	// * Used to update build input based on directional input from mouse/control pad right stick. Only called for holograms that returns true for "hasDirectionalInput". When it's called depends on the hold/press to continue method used.
	// //[DavalliusA:Tue/19-11-2019] we should probably do this based on input here, instead of view angle, as we would probably like it to require the same amount of input no matter the distance to the pole/perspective? Or would we actually want this to change? If so, how do we handle input when from pretty much straight above?
	// */
	//virtual void UpdateBuildDirectionInput( FVector2D delta );

	///**
	// * Use scroll on the hologram.
	// * @param delta	The scroll direction and amount, negative is down and positive is up.
	// */
	//virtual void UpdateBuildDirectionInput( int32 delta );

	//@todoscroll Cleanup or use old scroll with modes, there are some problems with how it was implemented before -G2
	virtual void ScrollRotate( int32 delta, int32 step );
	int32 GetScrollRotateValue() const { return mScrollRotation; }
	void SetScrollRotateValue(int32 rotValue)  { mScrollRotation = rotValue; }

	/**
	 * Set the initial scroll value that has been saved in the BuildGun.
	 *
	 * @param scrollMode - if this scroll mode isn't supported, no value will be set
	 * @param scrollValue - the value we want to set to the scroll mode
	 */
	void SetInitialScrollValue( EHologramScrollMode scrollMode, int32 scrollValue );

	/**
	 * Get the scroll value of the specified mode
	 *
	 * @param scrollMode - the scroll mode we want to get the scroll value of
	 * @return if scrollMode is HSM_NONE or invalid, then we return 0
	 */
	int32 GetScrollValue( EHologramScrollMode scrollMode ) const;

	/**
	 * Change the scroll mode on the hologram if many.
	 */
	void SetScrollMode( EHologramScrollMode mode );

	/**
	 * Get the currently active scroll mode.
	 */
	EHologramScrollMode GetScrollMode() const;

	/**
	 * Set the active scroll mode, changes what happens when Scroll is called.
	 */
	bool IsScrollModeSupported( EHologramScrollMode mode ) const;

	/**
	 * Change the scroll mode on the hologram if many.
	 * @param out_modes		Array with the supported modes in the preferred toggle order.
	 */
	virtual void GetSupportedScrollModes( TArray< EHologramScrollMode >* out_modes ) const;


	/**
	* Get the target spline path modes implemented for spline based holograms
	* @param out_splineModes	 Array with all supported spline pathing modes
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Hologram" )
	 void GetSupportedSplineModes( TArray< EHologramSplinePathMode >& out_splineModes ) const;

	UFUNCTION( BlueprintCallable, Category = "Hologram" )
	EHologramSplinePathMode GetSplineMode();

	UFUNCTION( BlueprintCallable, Category = "Hologram" )
	void SetSplineMode(EHologramSplinePathMode  mode);


	/** Set the no snap mode. @see mNoSnapMode */
	void SetNoSnapMode( bool isEnabled ) { mNoSnapMode = isEnabled; }

	/** Set hologram to snap to guide lines */
	virtual void SetSnapToGuideLines( bool isEnabled );

	/** Set hologram to snap to guide lines on server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SetSnapToGuideLines( bool isEnabled );

	/** @return true if no snap mode is enabled; false otherwise. */
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	FORCEINLINE bool GetNoSnapMode() const { return mNoSnapMode; }

	/**
	 * Set the placement material, this is updated when calling ValidatePlacementAndCost, so call this only if you want to override it.
	 * @param material - This is represented as a bool valid placement material (true), invalid placement material (false).
	 */
	virtual void SetPlacementMaterial( bool material );

	/**
	 * If the hologram contains changes that can be reset using the right mouse button, e.g. multi step placement and rotation.
	 * @return true if the hologram has changes; false if the hologram is in vanilla condition.
	 */
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	virtual bool IsChanged() const;

	/**
	 * @return Does this hologram upgrade/replace another building.
	 */
	FORCEINLINE bool IsUpgrade() const { return GetUpgradedActor() != nullptr; }

	/**
	 * @return The actor to replace when upgrading; if any. AKA, the target for the upgrade.
	 */
	virtual AActor* GetUpgradedActor() const;

	/**
	* @return true if the hologram can be constructed.
	*/
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	bool CanConstruct() const;


	virtual bool CanTakeNextBuildStep() const;


	/**
	 * Construct the real deal.
	 * @param out_children All children constructed, if any.
	 * @return The constructed actor; nullptr on failure.
	 */
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID constructionID );

	/** Even on if this hologram was constructed as a pending hologram */
	UFUNCTION( BlueprintNativeEvent, Category = "Hologram" )
	void OnPendingConstructionHologramCreated( class AFGHologram* fromHologram );
	void OnHologramTimeout();
	FTimerHandle mHologramTimeoutTimerHandler;

	/** The base cost for this hologram. */
	TArray< FItemAmount > GetBaseCost() const;

	/** Get the multiplier for the base cost, e.g. if this hologram cost per length unit. */
	virtual int32 GetBaseCostMultiplier() const;

	/**
	 * Returns the cost of this hologram.
	 * @param includeChildren Include child holograms cost in the cost.
	 * @note DO NOT expose this to blueprint, use the provided functions in the build guns build state.
	 */
	TArray< FItemAmount > GetCost( bool includeChildren ) const;

	/** Can be null if the building has no clearance */
	class UBoxComponent* GetClearanceDetector() const{ return mClearanceDetector; }

	TSubclassOf< class UFGRecipe > GetRecipe() const { return mRecipe; }

	/** Can be null if the building has no clearance */
	inline bool HasClearance() const{ return mClearanceDetector != nullptr; }

	/** Disable this hologram. */
	void SetDisabled( bool disabled  );

	/** @return Is this hologram disabled. */
	bool IsDisabled() const;

	/**
	 * Let the hologram spawn any children.
	 * @param state The build gun state responsible for spawning the states.
	 *              Use state->SpawnChildHologram( ... )
	 */
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator );

	/**
	 * Add a child hologram
	 */
	void AddChild( AFGHologram* child );

	/** Function to add disqualifiers */
	void AddConstructDisqualifier( TSubclassOf< class UFGConstructDisqualifier > disqualifier );

	/** @return true if the hologram can be constructed. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Hologram" )
	void GetConstructDisqualifiers( TArray< TSubclassOf< class UFGConstructDisqualifier > >& out_constructResults ) const;

	/** Empty the array of construct disqualifiers */
	void ResetConstructDisqualifiers();

	/**Returns true if this building want to snap to other buildings clearances with it's own clearance when receiving invalid placements due to overlapping clearances*/
	bool UsesBuildClearanceOverlapSnapping(){
		return mUseBuildClearanceOverlapSnapp;
	}

	//Set how the mUseBuildClearanceOverlapSnapp should be applied when enabled
	void SetUseAutomaticBuildClearanceOverlapSnapp( bool newValue )
	{
		mUseAutomaticBuildClearanceOverlapSnapp = newValue;
	}

	/** Returns whether or not this hologram is representing a construction event for client that is waiting for a server response. */
	bool GetIsPendingToBeConstructed() const { return mIsPendingToBeConstructed; }

	FORCEINLINE void SetIsPendingToBeConstructed( bool value ){ mIsPendingToBeConstructed = value; }

	/**Take the current transform and apply it to the scroll rotation value. */
	virtual void UpdateRotationValuesFromTransform();

	/** Adds a local construction ID associated with this hologram. Only used if this hologram is pending construction */
	void SetLocalPendingConstructionID( FNetConstructionID localNetConstructionId ) { mLocalNetConstructionID = localNetConstructionId; }
	FORCEINLINE FNetConstructionID GetLocalPendingConstructionID() const { return mLocalNetConstructionID; }

	/***/
	FORCEINLINE TArray<class AFGHologram*> GetHologramChildren() const { return mChildren; }

	/** Set the build class for this hologram, called before BeginPlay. */
	void SetBuildClass( TSubclassOf< class AActor > buildClass );

protected:
	/** OnHologramTransformUpdated
	 * Let's holograms react to rotation and location chnages applied after the initial move. Currently used for stuff like snapping and having sub holograms like hub parts update.
	 *
	 */
	virtual void OnHologramTransformUpdated();

	/**
	* Setup function. Called when setting up the hologram and when copying the actors content to the hologram in the start.
	* Called for every boxComponent in the actor.
	*Setup clearance if possible and needed
	*Default is to assign the mClearanceDetector by making a copy. This will happen and override the existing detector if called multiple times...*/
	virtual void SetupClearance( class UBoxComponent* boxComponent );

	void SetupClearanceDetector( class UBoxComponent* boxComponent );

	/** Duplicate component for the hologram */
	template<typename T>
	T* DuplicateComponent( USceneComponent* attachParent, T* templateComponent, const FName& componentName );

	/**
	 * @return true if the placement is valid, false otherwise.
	 */
	virtual void CheckValidPlacement();

	/**
	 * @return true if we can afford to build the hologram; false otherwise.
	 */
	virtual void CheckCanAfford( class UFGInventoryComponent* inventory );

	/**
	 * Called when the hologram snapped to something.
	 * E.g. a conveyor snapped to an output.
	 * NOT called when we align to a grid, e.g. building placed on a foundation or wall "snapped" to another wall.
	 */
	void OnSnap();

	/** So we can set the material on client. */
	UFUNCTION()
	void OnRep_PlacementMaterial();

	/**
	 * Set the material on the hologram.
	 *
	 * @param material - The new override material.
	 */
	virtual void SetMaterial( class UMaterialInterface* material );

	/**
	 * Get the actor this build gun constructs
	 */
	//@todo This has the same name as a deprecated function in Actor, rename.
	TSubclassOf< AActor > GetActorClass() const;

	/**
	* Setup function. Called when setting up the hologram and when copying the actors content to the hologram in the start.
	 * Setup a component from the buildable template.
	 * @param attachParent - Set the new component's AttachParent to this.
	 * @param componentTemplate - Create the component using this template.
	 * @return - The newly created component.
	 */
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName );

	/**
	* Setup function. Called when setting up the hologram and when copying the actors content to the hologram in the start.
	 * Setup a custom depth component for each mesh.
	 * Default it's called for every mush when setting up components.
	 * @note Hax to get custom depth to work with translucent materials.
	 * @note This does not work well with animated skeletal meshes, so do not add animations to holograms.
	 * @todo FIXME when custom depth works with translucent materials.
	 */
	virtual void SetupDepthMeshComponent( USceneComponent* attachParent, UMeshComponent* componentTemplate );

	/** Mark the hologram as changed. */
	void SetIsChanged();

	/**
	 * @return true if this is a local hologram, placed by a locally controlled player; false if a remote hologram.
	 */
	bool IsLocalHologram() const;

	/** Use this to add a valid hit class for this hologram in blueprints begin play. */
	UFUNCTION( BlueprintCallable, Category = "Hologram" )
	void AddValidHitClass( TSubclassOf< AActor > hitClass ) { mValidHitClasses.Add( hitClass ); }

	/** Check if a class is a valid hit. */
	bool IsValidHitActor( AActor* hitActor ) const;

	/** @return The overridden rotation step size to use when rotating. */
	virtual int32 GetRotationStep() const;

	/**
	 * Applies the user rotation to the given base rotation. [degrees]
	 * @return The rotation with the users rotation applied.
	 */
	float ApplyScrollRotationTo( float base, bool onlyUseBaseForAlignment = false ) const;

private:
	/**
	* Setup function. Called when setting up the hologram and when copying the actors content to the hologram in the start.
	* This initiate all the component copying and other setup calls. Called in early begin play.
	 * Setup the components from the buildable, meshes, collisions, connections etc.
	 */
	void SetupComponents();
	
	/**
	 * Play snapping sound. @todo Now when things are simulated, this can be done locally
	 */
	UFUNCTION( Client, Reliable )
	void Client_PlaySnapSound();

	UFUNCTION()
	void OnRep_InitialScrollModeValue();

protected:
	/**
	 * These classes will be considered a valid hit when checking is valid hit result.
	 * By default all static geometry is considered valid.
	 * Buildings, vehicles and pawns are not considered valid by default.
	 */
	UPROPERTY( VisibleDefaultsOnly, Category = "Hologram" )
	TArray< TSubclassOf< class AActor > > mValidHitClasses;

	/** The recipe for this hologram. */
	UPROPERTY( Replicated )
	TSubclassOf< class UFGRecipe > mRecipe;

	/** Looping sound to play on holograms */
	UPROPERTY()
	class UAkComponent* mLoopSound;

	/** Clearance detector box. Used to detect nearby clearances an display them during the build steps */
	UPROPERTY()
	class UBoxComponent* mClearanceDetector = nullptr;

	/** No enforced snapping, foundations use this for now. */
	bool mNoSnapMode;

	/** Whether the hologram should snap to guide lines or not */
	bool mSnapToGuideLines;

	/** Current scroll mode, determines what calls to Scroll() does. */
	EHologramScrollMode mScrollMode;

	/** Current scroll value of the rotation. How this is interpreted as a rotation is up to the hologram placement code. */
	int32 mScrollRotation;

	/** Current scroll value of the raise/lower. How this is interpreted as a height is up to the hologram placement code. */
	int32 mScrollRaiseLowerValue;

	/** Current scroll value of the Spline path enum. How this enum is used depends on individual spline based hologram implementation */
	EHologramSplinePathMode mSplineMode;

	/** Can we construct the building, updated by SetCanConstruct from the build gun. */
	UPROPERTY( ReplicatedUsing = OnRep_PlacementMaterial )
	bool mPlacementMaterial;

	/** Material on hologram for valid placement. */
	UPROPERTY()
	class UMaterialInstance* mValidPlacementMaterial;

	/** Material on hologram for invalid placement. */
	UPROPERTY()
	class UMaterialInstance* mInvalidPlacementMaterial;

	/** Tags for marking components in the hologram. */
	static const FName HOLOGRAM_MESH_TAG;
	static const FName HOLOGRAM_DEPTH_MESH_TAG;

	/**
	 * Enables composite holograms.
	 * Children are included in the cost and are constructed together with this hologram.
	 * Children can be optionally disabled with mIsDisabled.
	 *
	 * You're responsible for:
	 *  - updating the childrens location/rotation.
	 *  - validate placement for children.
	 *  - set correct materials on children.
	 */
	UPROPERTY()
	TArray< class AFGHologram* > mChildren;
	
	/** Should we use the simplified material for valid placement? */
	bool mUseSimplifiedHologramMaterial;

	/** Used to identify buildables on client once server has spawned the building */
	FNetConstructionID mLocalNetConstructionID;

	/** The class for the build actor this hologram wants to construct. Set on spawn. */
	UPROPERTY( Replicated )
	TSubclassOf< AActor > mBuildClass;

	UPROPERTY( EditDefaultsOnly )
	bool mUseBuildClearanceOverlapSnapp = false
		;
	bool mUseAutomaticBuildClearanceOverlapSnapp = true;

	/** The reason why we couldn't construct this hologram, if it's empty then we can construct it */
	TArray< TSubclassOf< class UFGConstructDisqualifier > > mConstructDisqualifiers;

private:
	/** Who is building */
	UPROPERTY( Replicated /*, CustomSerialization*/ )
	APawn* mConstructionInstigator;

	/** If this hologram is disabled and should not be visible or constructed. */
	UPROPERTY( /*CustomSerialization*/ )
	bool mIsDisabled;

	/** If the hologram has changed, i.e. multi step placement or rotation. */
	UPROPERTY( Replicated )
	bool mIsChanged;

	/** The client needs to know the initial saved scroll mode value from the BuildGun. */
	UPROPERTY( ReplicatedUsing = OnRep_InitialScrollModeValue )
	int32 mInitialScrollModeValue;

	/** This hologram is marked to be constructed, will not disappear if the build gun is unequipped for client */
	bool mIsPendingToBeConstructed = false;

	/** Temp memory holders for when holograms are serialized for construction messages (replication) */
	UPROPERTY( /*CustomSerialization*/ )
	FVector mConstructionPosition;

	/** Temp memory holders for when holograms are serialized for construction messages (replication) */
	UPROPERTY( /*CustomSerialization*/ )
	FRotator mConstructionRotation;
public:

public:
	FORCEINLINE ~AFGHologram() = default;
};

template<typename T>
T* AFGHologram::DuplicateComponent( USceneComponent* attachParent, T* templateComponent, const FName& componentName )
{
	T* newComponent = NewObject<T>( attachParent,
									templateComponent->GetClass(),
									componentName,
									RF_NoFlags,
									templateComponent );
	newComponent->SetMobility( EComponentMobility::Movable );

	return newComponent;
}
