// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGHologram.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableHologram.generated.h"

UENUM()
enum class EGuideLineType : uint8
{
	GLT_Default			UMETA( DisplayName = "Default" ),
	GLT_ConveyorBelt	UMETA( DisplayName = "Conveyor Belt" ),
	GLT_Pipe			UMETA( DisplayName = "Pipe" )
};

USTRUCT()
struct FFGHologramGuidelineData
{
	GENERATED_BODY()

	FFGHologramGuidelineData()
		: mGuidelineObject( nullptr )
		, mGuidelineLocationOffset( 0.0f )
		, mGuidelineType( EGuideLineType::GLT_Default )
	{}
	
	FFGHologramGuidelineData( class UObject* guidelineObject, const FTransform& transform, const FVector& guidelineLocationOffset, EGuideLineType type )
		: mGuidelineObject( guidelineObject )
		, mTransform( transform )
		, mGuidelineLocationOffset( guidelineLocationOffset )
		, mGuidelineType( type )
	{	
	}

	// The object this guideline was created from
	UPROPERTY()
	class UObject* mGuidelineObject;

	// Transform of the object the guideline was created for
	FTransform mTransform;
	
	// How much the guideline location should be offset, in case of snapping with components
	FVector mGuidelineLocationOffset;

	// What type of guideline this is
	EGuideLineType mGuidelineType;
};

USTRUCT()
struct FFGHologramGuidelineSnapResult
{
	GENERATED_BODY()

	FFGHologramGuidelineSnapResult()
		: mSnapLocation( 0.0f )
		, mSuccessfulSnap( false )
	{
	}

	// The data for the guideline we snapped to
	FFGHologramGuidelineData mSnappedGuidelineData;

	// The resulting location of the snap
	FVector mSnapLocation;

	// Whether or not we successfully snapped to a guideline
	bool mSuccessfulSnap;
};

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
	static FName mPowerConnectionMeshTag;

public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	AFGBuildableHologram();

	virtual void BeginPlay() override;

	/** Set the buildable class for this hologram. Called from when spawning an hologram, before before BeginPlay is called. */
	void SetBuildableClass( TSubclassOf< class AFGBuildable > buildableClass );

	// AFGHologram interface
	/** Net Construction Messages */
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void PreHologramPlacement() override;
	virtual void PostHologramPlacement() override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual void AdjustForGround( FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	// End AFGHologram interface

	class AFGBuildable* GetSnappedBuilding() { return mSnappedBuilding; }

	/** Gets a list of all factory connection components of this hologram. */
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	const TArray< class UFGFactoryConnectionComponent* >& GetCachedFactoryConnectionComponents() const { return mCachedFactoryConnectionComponents; }
	
	/** Gets a list of all power connection components of this hologram. */
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	const TArray< class UFGPowerConnectionComponent* >& GetCachedPowerConnectionComponents() const { return mCachedPowerConnectionComponents; }

	/** Gets a list of all pipe connection components of this hologram. */
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	const TArray< class UFGPipeConnectionComponent* >& GetCachedPipeConnectionComponents() const { return mCachedPipeConnectionComponents; }

	/** Whether or not the specified buildable should be considered for our guideline alignments. */
	virtual bool ShouldBuildableBeConsideredForGuidelines( class AFGBuildable* buildable ) const;

	/** Checks if connections face the same direction and are in line with eachother in order for guidelines to be used. */
	bool AreConnectionsAlignedForGuidelines( class UFGConnectionComponent* connection, class UFGConnectionComponent* otherConnection, const FVector& connectionOffset, float allowedAngleDeviation ) const;

	/** Checks whether there's anything obstructing guidelines between start and end. */
	bool IsClearPathForGuidelines( const FVector& start, const FVector& end, TSet< class AActor* > excludedActors ) const;

	/** Sweep for nearby guideline sources the hologram can snap to. */
	void SweepForNearbyGuidelines( const FVector& hologramLocation, TArray< FFGHologramGuidelineData >& out_guidelineData, float allowedAngleDeviation = 10.0f ) const;
	
	/** Used to snap to nearby guidelines of other actors. */
	FFGHologramGuidelineSnapResult SnapHologramLocationToGuidelines( const FVector& hologramLocation );

	/** Updates the visual representation for our snapped guideline. */
	void UpdateGuidelineVisuals( const TArray< FFGHologramGuidelineData >& guidelineData );

	void ClearGuidelineVisuals();

	/**
     * Function used to filter unwanted attachment points on the buildable based on hitresult. Such as removing all points which are pointing sideways.
     */
    virtual void FilterAttachmentPoints( TArray< const FFGAttachmentPoint* >& Points, class AFGBuildable* pBuildable, const FHitResult& HitResult ) const;

protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void CheckValidPlacement() override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram interface	

	/** Helper function to snap to the factory building grid. */
	void SnapToFloor( class AFGBuildable* floor, FVector& location, FRotator& rotation );

	/** Helper function to snap to any side of a foundation.
	 *  "location" should start as the position you want to snap.
	 *  Both "location" and "rotation" will contain the result once done. */
	void SnapToFoundationSide( class AFGBuildableFoundation* foundation, const FVector& localSideNormal, EAxis::Type snapAxis, FVector& location, FRotator& rotation );

	/** Helper function to snap to the side of a wall. */
	void SnapToWall(
		class AFGBuildableWall* wall,
	    const FVector& aimDirection,
	    const FVector& aimLocation,
	    EAxis::Type snapAxis,
	    const FVector& snapOffsetOnWall,
	    float snapRotationOnWall,
	    FVector& out_location,
	    FRotator& out_rotation );
	
	/**
	 * Helper to check if the floor is valid.
	 * @return - true if the floor is valid; false if the floor is to steep, another building etc.
	 */
	virtual void CheckValidFloor();

	/** Minimum Z value for a floor normal. If less the hologram is not placeable. */
	FORCEINLINE float GetMinPlacementFloorZ() const { return FMath::Cos( FMath::DegreesToRadians( mMaxPlacementFloorAngle ) ); }

	/**
	 * Function used to snap to other clearance boxes if our own clearance box is overlapping with them.
	 */
	void HandleClearanceSnapping( FVector& newLocation, FRotator& newRotation, const FHitResult& hitResult );

	/**
	 * Snaps the hologram to the target clearance box.
	 */
	void SnapToClearanceBox( const UFGClearanceComponent* targetSnapClearanceComponent, FVector& newLocation, FRotator& newRotation );

	/**
	 * Function used to determine if a buildable is identical to ourselves in terms of position, rotation, etc.
	 * Used to avoid overlapping buildables.
	 */
	virtual bool IsHologramIdenticalToBuildable( class AFGBuildable* buildable, const FVector& hologramLocationOffset ) const;

	/**
	 * Function to allow any pre-initialization on the actor before the configuration occurs. This is to allow for
	 * final checks and to set properties as once were configuring its all const from there
	 */
	virtual void PreConfigureActor( class AFGBuildable* inBuildable );

	/**
	* Configure function: Configuring the actor created from the hologram when executed.
	* Configure functions are called in the following order and can thus override each others steps. Be careful:
		-   ConfigureActor( buildable );
		-   ConfigureBuildEffect( buildable );
		-   //Perform the actual spawning in the world
		-   ConfigureComponents( buildable );
		-   //Begin play called on the buildable
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
		-   //Begin play called on the buildable
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
		-   //Begin play called on the buildable
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
		-   //Begin play called on the buildable
	* @param inBuildable - The resulting buildable placed in the world that we are to configure before it's finished.
	 * @note This is a good place to initialize snapped connections etc.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Hologram" )
	void ReceiveConfigureComponents( class AFGBuildable* inBuildable );

	/** Configures the build effect for the constructed actor. */
	void ConfigureBuildEffect( class AFGBuildable* inBuildable );

	// Begin AFGHologram interface
	virtual void SetupClearance( class UFGClearanceComponent* clearanceComponent ) override;
	virtual void HandleClearanceOverlap( const FOverlapResult& overlap, const FVector& locationOffset, bool HologramHasSoftClearance ) override;
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	virtual class UPrimitiveComponent* GetClearanceOverlapCheckComponent() const override;
	// End AFGHologram interface

	/** Call this to replace the transform and extent of the hologram clearance instead of setting it directly. */
	void SetHologramClearanceTransformAndExtent( const FVector& newRelativeLocation, const FRotator& newRelativeRotation, const FVector& newExtent );

	/** Setup the mesh for visualizing connections. */
	void SetupFactoryConnectionMesh( class UFGFactoryConnectionComponent* connectionComponent );
	void SetupPowerConnectionMesh( class UFGPowerConnectionComponent* connectionComponent );
	void SetupPipeConnectionMesh( class UFGPipeConnectionComponentBase* connectionComponent );

	/** Useful for getting the default buildable */
	template< class TBuildableClass >
	TBuildableClass* GetDefaultBuildable() const
	{
		if( mBuildClass->IsChildOf( TBuildableClass::StaticClass() ) )
		{
			TBuildableClass* cdo = mBuildClass->GetDefaultObject< TBuildableClass >();
		
			return cdo;
		}

		UE_LOG( LogBuilding, Warning, TEXT( "\"%s\": Tried to GetDefaultBuildable of class \"%s\" but was not able to. BuildClass is \"%s\"" ), *GetName(), *TBuildableClass::StaticClass()->GetName(), *mBuildClass->GetName() );
		
		ensure( false );

		return nullptr;
	}
	
	/**
	 * Returns best matching candidate for attaching to an attachment point.
	 * Attachment points are in local space.
	 */
	virtual const FFGAttachmentPoint* SelectCandidateForAttachment( const TArray< const FFGAttachmentPoint* >& Candidates, class AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FHitResult& HitResult );
	
	/**
	 * Function called in order to create a transform for attaching an attachment point of our own to another one.
	 * The attachment points are in local space.
	 */
	virtual void CreateAttachmentPointTransform( FTransform& out_transformResult, const FHitResult& HitResult, class AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint );

	void DelayApplyPrimitiveData();
	void ApplyMeshPrimitiveData( const FFactoryCustomizationData& customizationData );

protected:
	/** The maximum allowed angle on the floor for this hologram to be placed on (in degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram", meta = ( ClampMin = "0.0", ClampMax = "90.0", UIMin = "0.0", UIMax = "90.0" ) )
	float mMaxPlacementFloorAngle;
	UPROPERTY()
	class UFGFactoryLegsComponent* mLegs;

	//If set to true, the building will be allowed to snap to 45 degree intervals on fonudations instead of only 90 as the default.
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mUseGradualFoundationRotations = false;

	/** What kind of grid snapping size to use. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	float mGridSnapSize;

	/** If the frame mesh should be used to highlight connections in hologram. */
	uint32 mUseConveyorConnectionFrameMesh : 1;

	/** If the arrow mesh should be used to highlight a connection's direction in hologram. */
	uint32 mUseConveyorConnectionArrowMesh : 1;

	/** If the frame mesh should be used to highlight the pipe connections in hologram */
	uint32 mUsePipeConnectionFrameMesh : 1;

	/** If the arrow should be used to highlight the pipe connections in hologram */
	uint32 mUsePipeConnectionArrowMesh : 1;

	/** Cached array of all our factory connection components. */
	TArray< class UFGFactoryConnectionComponent* > mCachedFactoryConnectionComponents;

	/** Cached array of all our factory connection components. */
	TArray< class UFGPowerConnectionComponent* > mCachedPowerConnectionComponents;

	/** Cached array of all our factory connection components. */
	TArray< class UFGPipeConnectionComponent* > mCachedPipeConnectionComponents;

	/** Real clearance box extents. We save this because we shrink the clearance box a little bit to avoid rounding errors. */
	FVector mRealClearanceBoxExtent;

	/** Component used to check for clearance overlaps instead of the clearance box, if available. More closely matches the shape of the buildable. */
	UPROPERTY()
	class UFGComplexClearanceComponent* mComplexClearanceComponent;
	
	/** Mesh component used to display the active guideline */
	UPROPERTY()
	class UInstancedStaticMeshComponent* mInstancedGuidelineMeshComponent;

	UPROPERTY()
	FFGHologramGuidelineSnapResult mGuidelineSnapResult;

	/** If we have snapped to another buildable, i.e. foundation, floor etc, this is it. */
	UPROPERTY( CustomSerialization )
	class AFGBuildable* mSnappedBuilding;

	UPROPERTY( Transient )
	class UFGClearanceComponent* mSnappedClearanceBox;

	bool mDidSnapDuetoClearance;

	/** Whether or not we should check for valid floor. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mNeedsValidFloor;

	/** Cached list of attachment points. */
	TArray< FFGAttachmentPoint > mCachedAttachmentPoints;

	/** The attachment point we've snapped to. */
	FFGAttachmentPoint* mSnappedAttachmentPoint;
	FFGAttachmentPoint* mPreviousSnappedAttachmentPoint;

	/** Our own attachment point we've used for snapping. */
	const FFGAttachmentPoint* mLocalSnappedAttachmentPoint;

	/** Whether or not we have to snap to an attachment point. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mMustSnapToAttachmentPoint;

	/** Whether or not we can snap with our own attachment points to other objects. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mCanSnapWithAttachmentPoints;

	/** How far away an attachment point is allowed to be in order to be valid for snapping. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	float mAttachmentPointSnapDistanceThreshold;

	UPROPERTY()
	FFactoryCustomizationData mCustomizationData;

	/** The Color Swatch to use when building this hologram */
	UPROPERTY()
	TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > mDefaultSwatch;

	int32 mSelectedHologramAttachmentPointIndex;
};
