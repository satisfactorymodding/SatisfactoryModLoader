// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGHologram.h"
#include "FGBuildableHologram.generated.h"

/**
 * The base class for building holograms.
 * The hologram is created from a buildables class.
 * The hologram is responsible for:
 * Snapping functionality when building.
 * Constructing the buildable.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableHologram : public AFGHologram
{
	GENERATED_BODY()
public:
	/** Tags for marking components in the hologram. */
	static FName mInputConnectionMeshTag;
	static FName mOutputConnectionMeshTag;
	static FName mNeutralConnectionMeshTag;
	static FName mClearanceComponentName;
	static FName mPowerConnectionMeshTag;

public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	AFGBuildableHologram();

	/** Set the buildable class for this hologram. Called from when spawning an hologram, before before BeginPlay is called. */
	void SetBuildableClass( TSubclassOf< class AFGBuildable > buildableClass );

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// AFGHologram interface
	/** Net Construction Messages */
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	// End AFGHologram interface

	class AFGBuildable* GetSnappedBuilding() { return mSnappedBuilding; }

protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void CheckValidPlacement() override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram interface

	/** Helper function to snap to the factory building grid. */
	void SnapToFloor( class AFGBuildable* floor, FVector& location, FRotator& rotation );

	/**
	 * Helper to check if the floor is valid.
	 * @return - true if the floor is valid; false if the floor is to steep, another building etc.
	 */
	virtual void CheckValidFloor();

	/** Minimum Z value for a floor normal. If less the hologram is not placeable. */
	FORCEINLINE float GetMinPlacementFloorZ() const { return FMath::Cos( FMath::DegreesToRadians( mMaxPlacementFloorAngle ) ); }

	/**
	 * Helper to check if we stay clear of other buildings.
	 * @return true if we stay clear of other buildings; false in we're overlapping other buildings clearance.
	 */
	virtual void CheckClearance();

	/**
	 * Check clearance for specific a primitive and adds appropriate disqualifiers.
	 * Do not override this, use CheckClearance in subclasses.
	 * @return true if check found an overlap and added an disqualifier.
	 */
	bool CheckClearanceForPrimitive( UPrimitiveComponent* comp, const FComponentQueryParams& params = FComponentQueryParams::DefaultComponentQueryParams, bool allowSnapAndMoveAlongBuildings = false );

	/**
	 * Check clearance for specific shape and adds appropriate disqualifiers.
	 * Used if a hologram needs cheap manual shape construction and checking and don't want any of the snapping logics and such
	 */
	bool CheckClearanceForShapeSimple( struct FCollisionShape& shape, FTransform transform, ECollisionChannel chanel, const FComponentQueryParams& params = FComponentQueryParams::DefaultComponentQueryParams );

	/**
	* Configure function: Configuring the actor created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable ); 
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   ConfigureSnappedBuilding( buildable );
		-   //Begin play called on the buildable
		-   ConfigureSnappedPower( buildable );
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * Configure the snapping to a building, i.e. foundation, floor etc.
	 */
	virtual void ConfigureSnappedBuilding( class AFGBuildable* inBuildable ) const;

	/**
	* Configure function: Configuring the actor created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable );
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   ConfigureSnappedBuilding( buildable );
		-   //Begin play called on the buildable
		-   ConfigureSnappedPower( buildable );
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * Configure snapping to a power grid, i.e. when placing a buildable on a foundation it should hook up to any powered walls.
	 */
	virtual void ConfigureSnappedPower( class AFGBuildable* inBuildable ) const;

	/**
	* Configure function: Configuring the actor created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable );
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   ConfigureSnappedBuilding( buildable );
		-   //Begin play called on the buildable
		-   ConfigureSnappedPower( buildable );
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * @note DO NOT TOUCH COMPONENTS HERE as they'll be overwritten! Use ConfigureComponents for that
	 */
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const;

	/**
	* For notifying the blueprint. Called after the native equivalent.
	* Configure function: Configuring the actor created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable );
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   ConfigureSnappedBuilding( buildable );
		-   //Begin play called on the buildable
		-   ConfigureSnappedPower( buildable );
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * @note DO NOT TOUCH COMPONENTS HERE as they'll be overwritten! Use ConfigureComponents for that
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void ReceiveConfigureActor( class AFGBuildable* inBuildable );

	/**
	* Configure function: Configuring the actor component created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable );
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   ConfigureSnappedBuilding( buildable );
		-   //Begin play called on the buildable
		-   ConfigureSnappedPower( buildable );
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * @note This is a good place to initialize snapped connections etc.
	 */
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const;
	/**
	* For notifying the blueprint. Called after the native equivalent.
	* Configure function: Configuring the actor's components created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable );
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   ConfigureSnappedBuilding( buildable );
		-   //Begin play called on the buildable
		-   ConfigureSnappedPower( buildable );
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * @note This is a good place to initialize snapped connections etc.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void ReceiveConfigureComponents( class AFGBuildable* inBuildable );

	/** Configures the build effect for the constructed actor. */
	void ConfigureBuildEffect( class AFGBuildable* inBuildable );

	// Begin AFGHologram interface
	virtual void SetupClearance( class UBoxComponent* boxComponent ) override;
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	// End AFGHologram interface

	/** Setup the mesh for visualizing connections. */
	void SetupFactoryConnectionMesh( class UFGFactoryConnectionComponent* connectionComponent );
	void SetupPowerConnectionMesh( class UFGPowerConnectionComponent* connectionComponent );
	void SetupPipeConnectionMesh( class UFGPipeConnectionComponentBase* connectionComponent );

	/** Useful for getting the default buildable */
	template< class TBuildableClass >
	TBuildableClass* GetDefaultBuildable() const
	{
		TBuildableClass* cdo = mBuildClass->GetDefaultObject< TBuildableClass >();
		check( cdo );
		return cdo;
	}

private:
	bool ApplyBuildingClearnaceSnapping( FRotator& newRotation, FVector& newLocation, AFGBuildable* snapTarget, FVector traceStart, FVector traceEnd );

protected:
	/** The maximum allowed angle on the floor for this hologram to be placed on (in degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram", meta = ( ClampMin = "0.0", ClampMax = "90.0", UIMin = "0.0", UIMax = "90.0" ) )
	float mMaxPlacementFloorAngle;
	UPROPERTY()
	class UFGFactoryLegsComponent* mLegs;

	FVector mOriginalPlacementLocation; //used to revert back placement modifications if the placement failed
	bool mHasSetOriginalPlacementLocation = false;

	bool  mPlacingOnSnapGrid; //used for the overlap snap logics on fonudations

	bool mHaveSnappedWithPlacementOverlap = false; //used to make sure we only do snapping once, or we might get pushed back in to what we moved out from

	//If set to true, the building will be allowed to snap to 45 degree intervals on fonudations instead of only 90 as the default.
	bool mUseGradualFoundationRotations = false;


	/** If the frame mesh should be used to highlight connections in hologram. */
	uint32 mUseConveyorConnectionFrameMesh : 1;

	/** If the arrow mesh should be used to highlight a connection's direction in hologram. */
	uint32 mUseConveyorConnectionArrowMesh : 1;

	/** If the frame mesh should be used to highlight the pipe connections in hologram */
	uint32 mUsePipeConnectionFrameMesh : 1;

	/** If the arrow should be used to highlight the pipe connections in hologram */
	uint32 mUsePipeConnectionArrowMesh : 1;



	/** Component to check build clearance to other buildings. */
	UPROPERTY()
	class UBoxComponent* mClearanceBox;

	/** If we have snapped to another buildable, i.e. foundation, floor etc, this is it. */
	UPROPERTY( /*CustomSerialization*/ ) // MODDING EDIT: Another CSS custom engine thing
	class AFGBuildable* mSnappedBuilding;

	bool mIsAimingAtOtherBuilding = false;
	bool mDidSnapDuetoClearance = false;

public:
	FORCEINLINE ~AFGBuildableHologram() = default;
};
