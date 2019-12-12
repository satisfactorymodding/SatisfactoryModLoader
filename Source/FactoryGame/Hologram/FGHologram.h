// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "../ItemAmount.h"
#include "Components/MeshComponent.h"
#include "FGHologram.generated.h"


/**
 * Enum for different scroll modes a hologram can implement.
 */
UENUM( BlueprintType )
enum class EHologramScrollMode : uint8
{
	HSM_NONE = 0			UMETA( DisplayName = "None" ),
	HSM_ROTATE = 1			UMETA( DisplayName = "Rotate" ),
	HSM_RAISE_LOWER = 2		UMETA( DisplayName = "Raise/Lower" ),
	HSM_MAX					UMETA( Hidden )
};

/**
 * The base class for all holograms.
 * It defines the interface all "buildable things" must follow.
 *
 * Note : Do not use SetActorLocation(), SetActorRotation() etc to move a hologram.
 *       Use SetHologramLocationAndRotation() instead as this handles snapping etc.
 */
UCLASS( hidecategories = ( "Actor", "Input", "Replication", "Rendering", "Actor Tick" ) )
class FACTORYGAME_API AFGHologram : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Ctor */
	AFGHologram();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Set the item descriptor for this hologram, called before BeginPlay. */
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Get the item descriptor for the building being built. */
	TSubclassOf< class UFGItemDescriptor > GetItemDescriptor() const;

	/** Set who is building with this hologram. */
	void SetConstructionInstigator( APawn* instigator ) { mConstructionInstigator = instigator; }
	FORCEINLINE APawn* GetConstructionInstigator() const { return mConstructionInstigator; }

	/**
	 * Do all custom initialization here.
	 */
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void SetActorHiddenInGame( bool newHidden ) override;

	/**
	 * Let the hologram check if the hit result is valid.
	 *
	 * @return true if the hit result is invalid for SetLocationAndRotation, this causes the hologram to be hidden and updating to be skipped.
	 */
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const;

	/**
	 * See if the hit actor can be upgraded with this hologram and set the holograms location and rotation accordingly.
	 * @return true if an upgrade is possible; false if not.
	 */
	virtual bool TryUpgrade( const FHitResult& hitResult );

	/**
	 * Adjust the placement for the ground, this should be the last step in the placement
	 */
	virtual void AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation );

	/**
	 * See if we can snap to the hit actor.
	 * @return true if we can snap; false if not.
	 */
	virtual bool TrySnapToActor( const FHitResult& hitResult );

	/**
	 * Update the holograms location and rotation. Snaps if possible.
	 *
	 * @param hitResult - the hit result from the trace preformed in BuildGun
	 */
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult );

	/**
	 * Notify that the hologram hit result is invalid and that the hologram is potentially hidden. E.g. Aiming up in the sky.
	 */
	virtual void OnInvalidHitResult();

	/**
	 * Checks placement and cost.
	 */
	void ValidatePlacementAndCost( class UFGInventoryComponent* inventory );
	
	/**
	 * Place parts of the hologram for each call to this function.
	 * For objects built in multiple steps call this methods for each step in the build process.
	 * When it returns true, then Construct can be called to construct the actor.
	 *
	 * @return - true if placement is finished and Construct can be called; false if placement is not finished.
	 */
	virtual bool MultiStepPlacement();

	/**
	 * Use scroll on the hologram.
	 * @param delta	The scroll direction and amount, negative is down and positive is up.
	 */
	virtual void Scroll( int32 delta );

	//@todoscroll Cleanup or use old scroll with modes, there are some problems with how it was implemented before -G2
	virtual void ScrollRotate( int32 delta, int32 step );
	int32 GetScrollRotateValue() const { return mScrollRotation; }

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

	/** Set the no snap mode. @see mNoSnapMode */
	void SetNoSnapMode( bool isEnabled ) { mNoSnapMode = isEnabled; }

	/** Set hologram to snap to guide lines */
	void SetSnapToGuideLines( bool isEnabled );

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
	 * @return The actor to replace when upgrading; if any.
	 */
	virtual AActor* GetUpgradedActor() const;

	/**
	* @return true if the hologram can be constructed.
	*/
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	bool CanConstruct() const;

	/**
	 * Construct the real deal.
	 * @param out_children All children constructed, if any.
	 * @return The constructed actor; nullptr on failure.
	 */
	virtual AActor* Construct( TArray< AActor* >& out_children );

	/** The base cost for this hologram. */
	TArray< FItemAmount > GetBaseCost() const;

	/**
	 * Returns the cost of this hologram.
	 * @param includeChildren Include child holograms cost in the cost.
	 * @note DO NOT expose this to blueprint, use the provided functions in the build guns build state.
	 */
	virtual TArray< FItemAmount > GetCost( bool includeChildren ) const;

	/** Can be null if the building has no clearance */
	class UBoxComponent* GetClearanceDetector() const{ return mClearanceDetector; }

	/** Disable this hologram. */
	void SetDisabled( bool disabled  );

	/** @return Is this hologram disabled. */
	bool IsDisabled() const;

	/**
	 * Let the hologram spawn any children.
	 * @param state The build gun state responsible for spawning the states.
	 *              Use state->SpawnChildHologram( ... )
	 */
	virtual void SpawnChildren( class UFGBuildGunStateBuild* state );

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

protected:
	/** Setup clearance if possible and needed */
	virtual void SetupClearance( class UBoxComponent* boxComponent );

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
	virtual TSubclassOf< AActor > GetActorClass() const;

	/**
	 * Setup a component from the buildable template.
	 * @param attachParent - Set the new component's AttachParent to this.
	 * @param componentTemplate - Create the component using this template.
	 * @return - The newly created component.
	 */
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName );

	/**
	 * Setup a custom depth component for each mesh.
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

	/** Clearance detector box */
	UPROPERTY()
	class UBoxComponent* mClearanceDetector;

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
private:
	/** Who is building */
	UPROPERTY( Replicated )
	APawn* mConstructionInstigator;

	/** If this hologram is disabled and should not be visible or constructed. */
	UPROPERTY()
	bool mIsDisabled;

	/** If the hologram has changed, i.e. multi step placement or rotation. */
	UPROPERTY( Replicated )
	bool mIsChanged;

	/** The reason why we couldn't construct this hologram, if it's empty then we can construct it */
	TArray< TSubclassOf< class UFGConstructDisqualifier > > mConstructDisqualifiers;

	/** The client needs to know the initial saved scroll mode value from the BuildGun. */
	UPROPERTY( ReplicatedUsing = OnRep_InitialScrollModeValue )
	int32 mInitialScrollModeValue;
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
