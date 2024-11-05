// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGHologram.h"
#include "FGBuildableHologram.generated.h"

UENUM()
enum class EGuideLineType : uint8
{
	GLT_Default			UMETA( DisplayName = "Default" ),
	GLT_ConveyorBelt	UMETA( DisplayName = "Conveyor Belt" ),
	GLT_Pipe			UMETA( DisplayName = "Pipe" )
};

UENUM()
enum class EGuideLineConnectionType : uint8
{
	GLCT_None			UMETA( DisplayName = "None" ),
	GLCT_Input			UMETA( DisplayName = "Input" ),
	GLCT_Output			UMETA( DisplayName = "Output" ),
	GLCT_Any			UMETA( DisplayName = "Any" )
};


USTRUCT()
struct FFGHologramGuidelineData
{
	GENERATED_BODY()

	FFGHologramGuidelineData()
		: mGuidelineStartObject( nullptr )
		, mGuidelineEndObject( nullptr )
		, mGuidelineLocationOffset( 0.0f )
		, mGuidelineType( EGuideLineType::GLT_Default )
		, mGuidelineConnectionTypeStart( EGuideLineConnectionType::GLCT_None )
		, mGuidelineConnectionTypeEnd( EGuideLineConnectionType::GLCT_None )
	{}
	
	FFGHologramGuidelineData( class UObject* guidelineStartObject, class UObject* guidelineEndObject, const FTransform& transform, const FVector& guidelineLocationOffset, EGuideLineType type, EGuideLineConnectionType connectionTypeStart = EGuideLineConnectionType::GLCT_None, EGuideLineConnectionType connectionTypeEnd = EGuideLineConnectionType::GLCT_None )
		: mGuidelineStartObject( guidelineStartObject )
		, mGuidelineEndObject( guidelineEndObject )
		, mTransform( transform )
		, mGuidelineLocationOffset( guidelineLocationOffset )
		, mGuidelineType( type )
		, mGuidelineConnectionTypeStart( connectionTypeStart )
		, mGuidelineConnectionTypeEnd( connectionTypeEnd )
	{	
	}

	// The object this guideline was created from
	UPROPERTY()
	class UObject* mGuidelineStartObject;

	// The object this guideline was created for
	UPROPERTY()
	class UObject* mGuidelineEndObject;

	// Transform of the object the guideline was created for
	FTransform mTransform;
	
	// How much the guideline location should be offset, in case of snapping with components
	FVector mGuidelineLocationOffset;

	// What type of guideline this is
	EGuideLineType mGuidelineType;

	// In case of connection guidelines, this is the connection type for the "start" connection
	EGuideLineConnectionType mGuidelineConnectionTypeStart;

	// In case of connection guidelines, this is the connection type for the "end" connection
	EGuideLineConnectionType mGuidelineConnectionTypeEnd;
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
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void PreHologramPlacement( const FHitResult& hitResult ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual void AdjustForGround( FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	virtual bool CanNudgeHologram() const override;
	virtual ENudgeFailReason NudgeTowardsWorldDirection( const FVector& Direction ) override;
	virtual FTransform GetNudgeSpaceTransform() const override;
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

	/** Whether or not the specified actor should be considered for our guideline alignments. */
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const;

	virtual TArray< class UFGFactoryConnectionComponent* > GetRelevantFactoryConnectionsForGuidelines() const;
	virtual TArray< class UFGPipeConnectionComponent* > GetRelevantPipeConnectionsForGuidelines() const;

	/** Checks if connections face the same direction and are in line with eachother in order for guidelines to be used. */
	bool AreConnectionsAlignedForGuidelines( class UFGConnectionComponent* connection, class UFGConnectionComponent* otherConnection, const FVector& connectionOffset, float perpDistanceThreshold, float allowedAngleDeviation ) const;

	/** Checks whether there's anything obstructing guidelines between start and end. */
	bool IsClearPathForGuidelines( const FVector& start, const FVector& end, const TArray< class AActor* >& excludedActors ) const;

	/** Sweep for nearby guideline sources the hologram can snap to. */
	void GatherNearbyGuidelines( const FVector& hologramLocation, TArray< FFGHologramGuidelineData >& out_guidelineData, float perpDistanceThreshold, float allowedAngleDeviation = 10.0f, const struct FRuntimeFloatCurve* perpDistanceThresholdCurve = nullptr ) const;
	
	/** Used to snap to nearby guidelines of other actors. */
	FFGHologramGuidelineSnapResult SnapLocationToGuidelines( const FVector& location );

	/** Generic guideline snapping functionality. */
	void SnapHologramToGuidelines();

	/** Updates the visual representation for our snapped guideline. */
	void UpdateGuidelineVisuals( const TArray< FFGHologramGuidelineData >& guidelineData );

	void ClearGuidelineVisuals();

	FORCEINLINE void SetHideGuidelineVisuals( bool hide ) { mHideGuidelineVisuals = hide; }
	FORCEINLINE bool GetHideGuidelineVisuals() const { return mHideGuidelineVisuals; }

	void SetNeedsValidFloor( bool needsValidFloor ) { mNeedsValidFloor = needsValidFloor; }
	bool GetNeedsValidFloor() const { return mNeedsValidFloor; }

	/**
     * Function used to filter unwanted attachment points on the buildable based on hitresult. Such as removing all points which are pointing sideways.
     */
    virtual void FilterAttachmentPoints( TArray< const FFGAttachmentPoint* >& Points, class AFGBuildable* pBuildable, const FHitResult& HitResult ) const;

	FORCEINLINE bool ShouldUseConveyorConnectionFrameMesh() const { return mUseConveyorConnectionFrameMesh; }
	FORCEINLINE bool ShouldUseConveyorConnectionArrowMesh() const { return mUseConveyorConnectionArrowMesh; }
	
	FORCEINLINE bool ShouldUsePipeConnectionFrameMesh() const { return mUsePipeConnectionFrameMesh; }
	FORCEINLINE bool ShouldUsePipeConnectionArrowMesh() const { return mUsePipeConnectionArrowMesh; }

	FORCEINLINE void SetSuppressBuildEffect( bool bNewSuppressBuildEffect ) { mSuppressBuildEffect = bNewSuppressBuildEffect; }
protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual void CheckValidPlacement() override;
	virtual int32 GetRotationStep() const override;
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FVector& hologramLocationOffset ) const override;
	virtual void SerializeConstructMessage(FArchive& ar, FNetConstructionID id) override;
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

	/**
	 * Do any validation checks to ensure a hologram is not connecting a building inside a blueprint designer
	 * To one outside the designer. Ofter clearance will disallow this but this is an additional safety check
	 * Wires for example wont have a collision problem so in their hologram we verify the connections / placement
	 */
	virtual void CheckBlueprintCommingling();

	/** Minimum Z value for a floor normal. If less the hologram is not placeable. */
	FORCEINLINE float GetMinPlacementFloorZ() const { return FMath::Cos( FMath::DegreesToRadians( mMaxPlacementFloorAngle ) ); }

	/**
	 * Function used to snap to other clearance boxes if our own clearance box is overlapping with them.
	 */
	void HandleClearanceSnapping( FVector& newLocation, FRotator& newRotation, const FHitResult& hitResult );

	/**
	 * Snaps the hologram to the target clearance box.
	 */
	void SnapToClearanceBox( const AActor* clearanceOwner, const FVector& testLocation, FVector& newLocation, FRotator& newRotation );

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
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	// End AFGHologram interface

	/** Setup the mesh for visualizing connections. */
	void SetupFactoryConnectionMesh( class UFGFactoryConnectionComponent* connectionComponent, bool bUseFrameMesh, bool bUseArrowMesh, class USceneComponent* attachParent = nullptr );
	void SetupPowerConnectionMesh( class UFGPowerConnectionComponent* connectionComponent, class USceneComponent* attachParent = nullptr );
	void SetupPipeConnectionMesh( class UFGPipeConnectionComponentBase* connectionComponent, bool bUseFrameMesh, bool bUseArrowMesh, class USceneComponent* attachParent = nullptr );

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

	/** True if the build effect should be suppressed for the buildable constructed from this hologram */
	uint32 mSuppressBuildEffect : 1;

	/** Cached array of all our factory connection components. */
	TArray< class UFGFactoryConnectionComponent* > mCachedFactoryConnectionComponents;

	/** Cached array of all our factory connection components. */
	TArray< class UFGPowerConnectionComponent* > mCachedPowerConnectionComponents;

	/** Cached array of all our factory connection components. */
	TArray< class UFGPipeConnectionComponent* > mCachedPipeConnectionComponents;
	
	/** Mesh component used to display the active guideline */
	UPROPERTY()
	class UInstancedStaticMeshComponent* mInstancedGuidelineMeshComponent;

	UPROPERTY()
	FFGHologramGuidelineSnapResult mGuidelineSnapResult;

	/** If we have snapped to another buildable, i.e. foundation, floor etc, this is it. */
	UPROPERTY( CustomSerialization, Replicated )
	class AFGBuildable* mSnappedBuilding;

	UPROPERTY()
	class AFGBuildable* mSnappedFloor;

	UPROPERTY()
	class AFGBuildable* mSnappedWall;

	/** If we've snapped a wall, this is the worldspace direction from us towards the "wall". */
	FVector mWorldSpaceSnapDirection;

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

	/** Whether or not to hide guideline visuals for this hologram. */
	bool mHideGuidelineVisuals;

	UPROPERTY()
	FFactoryCustomizationData mCustomizationData;

	/** The Color Swatch to use when building this hologram */
	UPROPERTY()
	TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > mDefaultSwatch;

	int32 mSelectedHologramAttachmentPointIndex;
};
