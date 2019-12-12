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
	static FName mClearanceComponentName;
	static FName mPowerConnectionMeshTag;
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Ctor */
	AFGBuildableHologram();

	/** Set the buildable class for this hologram, called before BeginPlay. */
	void SetBuildableClass( TSubclassOf< class AFGBuildable > buildableClass );

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children ) override;
	// End AFGHologram interface

	class AFGBuildable* GetSnappedBuilding() { return mSnappedBuilding; }

protected:
	// Begin AFGHologram interface
	virtual TSubclassOf< AActor > GetActorClass() const override;
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void CheckValidPlacement() override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram interface

	/** Helper function to snap to the factory building grid. */
	void SnapToFloor( class AFGBuildableFactoryBuilding* floor, FVector& location, FRotator& rotation );

	/**
	 * Helper to check if the floor is valid.
	 * @return - true if the floor is valid; false if the floor is to steep, another building etc.
	 */
	virtual void CheckValidFloor();

	/** Minimum Z value for a floor normal. If less the hologram is not placeable. */
	FORCEINLINE float GetMinPlacementFloorZ() const
	{
		return FMath::Cos( FMath::DegreesToRadians( mMaxPlacementFloorAngle ) );
	}

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
	bool CheckClearanceForPrimitive( UPrimitiveComponent* comp, const FComponentQueryParams& params = FComponentQueryParams::DefaultComponentQueryParams );

	/**
	 * Configure the snapping to a building, i.e. foundation, floor etc.
	 */
	virtual void ConfigureSnappedBuilding( class AFGBuildable* inBuildable ) const;

	/**
	 * Configure snapping to a power grid, i.e. when placing a buildable on a foundation it should hook up to any powered walls.
	 */
	virtual void ConfigureSnappedPower( class AFGBuildable* inBuildable ) const;

	/**
	 * Configure the actor with values from the hologram here.
	 * @note DO NOT TOUCH COMPONENTS HERE as they'll be overwritten! Use ConfigureComponents for that
	 */
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const;
	/**
	 * Configure the actor with values from the hologram here.
	 * @note DO NOT TOUCH COMPONENTS HERE as they'll be overwritten! Use ConfigureComponents for that
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void ReceiveConfigureActor( class AFGBuildable* inBuildable );

	/**
	 * Configure the actor's components with values from the hologram here.
	 * @note This is a good place to initialize snapped connections etc.
	 */
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const;
	/**
	 * Configure the actor's components with values from the hologram here.
	 * @note This is a good place to initialize snapped connections etc.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void ReceiveConfigureComponents( class AFGBuildable* inBuildable );

	/** Configures the build effect for the constructed actor. */
	void ConfigureBuildEffect( class AFGBuildable* inBuildable );

	// Begin AFGHologram interface
	virtual void SetupClearance( class UBoxComponent* boxComponent ) override;
	// End AFGHologram interface

	/** Setup the mesh for visualizing connections. */
	void SetupFactoryConnectionMesh( class UFGFactoryConnectionComponent* connectionComponent );
	void SetupPowerConnectionMesh( class UFGPowerConnectionComponent* connectionComponent );

	/** Useful for getting the default buildable */
	template< class TBuildableClass >
	TBuildableClass* GetDefaultBuildable() const
	{
		TBuildableClass* cdo = mBuildableClass->GetDefaultObject< TBuildableClass >();
		check( cdo );
		return cdo;
	}

protected:
	/** The class for the buildable this hologram wants to construct. Set on spawn. */
	UPROPERTY( Replicated )
	TSubclassOf< class AFGBuildable > mBuildableClass;

	/** The maximum allowed angle on the floor for this hologram to be placed on (in degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram", meta = ( ClampMin = "0.0", ClampMax = "90.0", UIMin = "0.0", UIMax = "90.0" ) )
	float mMaxPlacementFloorAngle;
	UPROPERTY()
	class UFGFactoryLegsComponent* mLegs;

	/** If the frame mesh should be used to highlight connections in hologram. */
	uint32 mUseConveyorConnectionFrameMesh : 1;

	/** If the arrow mesh should be used to highlight a connection's direction in hologram. */
	uint32 mUseConveyorConnectionArrowMesh : 1;

	/** Component to check build clearance to other buildings. */
	UPROPERTY()
	class UBoxComponent* mClearanceBox;

	/** If we have snapped to another buildable, i.e. foundation, floor etc, this is it. */
	class AFGBuildable* mSnappedBuilding;
};
