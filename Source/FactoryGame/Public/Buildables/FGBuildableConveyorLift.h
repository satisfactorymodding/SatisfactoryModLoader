// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableConveyorBase.h"
#include "FGBuildablePassthrough.h"
#include "Math/GenericOctree.h"
#include "FGBuildableConveyorLift.generated.h"

class UStaticMesh;

UCLASS( EditInlineNew )
class FACTORYGAME_API UFGBuildableConveyorLiftSparseData : public UObject
{
	GENERATED_BODY()
public:
	/** What's the height of the meshes used. */
	UPROPERTY( EditDefaultsOnly )
	float mMeshHeight;

	/** Mesh at the bottom of the lift. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mBottomMesh;
	
	/** Mesh repeated for the mid section. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mMidMesh;
	
	/** Half Size Mid Mesh for passthrough visuals (200 units is too long so we use a half mesh in certain cases). */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mHalfMidMesh;
	
	/** Mesh at the top of the lift. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mTopMesh;
	
	/** Mesh placed on the input/output as a bellow between a wall or factory. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mBellowMesh;
	
	/** Mesh placed between two joined lift sections. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mJointMesh;
	
	/** Shelf placed under each item. */
	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mShelfMesh;
};


/** Base for conveyor lifts. */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorLift : public AFGBuildableConveyorBase
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorLift();

	friend class AFGConveyorItemSubsystem;
	
	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	virtual bool ShouldShowCenterGuidelinesForHologram( const AFGHologram* hologram ) const override;
	// End Buildable interface
	
	// Begin IFGDismantleInterface
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	// End IFGDismantleInterface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInterface

	/* Force enable lightweight instancing on lifts. */
	virtual bool DoesContainLightweightInstances_Native() const override { return true; }
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() override;
	//virtual void SetupInstances_Native() override;

	/** Get the height for this lift. */
	float GetHeight() const { return FMath::Abs( mTopTransform.GetTranslation().Z ); }

	/** Returns whether this lift is reversed or not */
	FORCEINLINE bool GetIsReversed() const { return mIsReversed; }

	/** Overriden to account for reversal */
	virtual float GetDistanceBetweenFirstConnection() override;
	/** Overriden to account for reversal */
	virtual float GetDistanceBetweenLastConnection() override;

	virtual void BuildStaticItemInstances() override;

	/** Overrided as conveyor lifts lack primitives so they never recieve this otherwise */
	virtual float GetLastRenderTime() const override;

	// Setup the connection locations
	void SetupConnections();

	void DestroyVisualItems();

	FORCEINLINE TArray< class AFGBuildablePassthrough* > GetSnappedPassthroughs() { return mSnappedPassthroughs; }

	FORCEINLINE FTransform GetTopTransform() const { return mTopTransform; }
	
#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Buildable")
	UFGBuildableConveyorLiftSparseData* mConveyorLiftSparesData;
#endif

	UPROPERTY( )
	UFGBuildableConveyorLiftSparseData* mConveyorLiftSparesDataCDO;
	
	FORCEINLINE const UFGBuildableConveyorLiftSparseData* GetConveyorLiftSparesData() const { return mConveyorLiftSparesDataCDO; }

	virtual void PostSerializedFromBlueprint(bool isBlueprintWorld) override;
	
protected:
	// Begin AFGBuildableConveyorBase interface
	virtual void TickItemTransforms( float dt ) override;
	virtual void TickRadioactivity() override;
	virtual void Factory_UpdateRadioactivity( class AFGRadioactivitySubsystem* subsystem ) override;
	// End AFGBuildableConveyorBase interface
	
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
		
private:
	friend class AFGBlueprintHologram;
	
	template< typename MeshConstructor >
	static void BuildStaticMeshes(
		USceneComponent* parent,
		const FTransform& endTransform,
		UStaticMesh* bottomMesh,
		UStaticMesh* midMesh,
		UStaticMesh* halfMidMesh,
		UStaticMesh* topMesh,
		float stepHeight,
		TArray< AFGBuildablePassthrough* > snappedPassthroughs,
		bool isConnectionReversed,
		bool shouldFlipOnReverse,
		TArray< UStaticMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	static FBox FitClearance(
		float transformZ,
		float stepHeight,
		const FVector2D& extend2D,
		const FVector& extentBias = FVector::ZeroVector,
		bool hasBottomHole = false,
		bool hasTopHole = false,
		bool isReversed = false );


public:
	static const FVector2D CLEARANCE_EXTENT_2D;
	static constexpr float CONNECTION_RELATIVE_FORWARD = 0.f;
	static constexpr float BELLOW_MESH_LENGTH = 100.f;

	/** What's the height of the meshes used. */
	UPROPERTY( EditDefaultsOnly )
	float mMeshHeight;

	/** Mesh at the bottom of the lift. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mBottomMesh;
	/** Mesh repeated for the mid section. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mMidMesh;
	/** Half Size Mid Mesh for passthrough visuals (200 units is too long so we use a half mesh in certain cases). */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mHalfMidMesh;
	/** Mesh at the top of the lift. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mTopMesh;
	/** Mesh placed on the input/output as a bellow between a wall or factory. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mBellowMesh;
	/** Mesh placed between two joined lift sections. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mJointMesh;
	/** Shelf placed under each item. */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mShelfMesh;


private:
	friend class AFGConveyorLiftHologram;

	/**
	 * The transform of the top part.
	 * The transform of the bottom part is the same as actor.
	 * If the input and output is reversed so the input is at the top, the reverse flag is set.
	 * From this the mesh and connection transform is calculated.
	 */
	UFUNCTION()
	void OnRep_TopTransform();

	/**
	 * We need the passthrough information to correctly build the lift mesh so when they replicate clients will rebuild their instances
	 */
	UFUNCTION()
	void OnRep_SnappedPassthroughs();
	
	UPROPERTY( SaveGame, ReplicatedUsing= OnRep_TopTransform )
	FTransform mTopTransform;

	UPROPERTY( SaveGame, Replicated )
	bool mIsReversed;

	/** Used by mk6 lifts because they are enclosed and have a directional arrow on them */
	UPROPERTY( EditDefaultsOnly )
	bool mFlipMeshOnReverse;

	/* DEPRECATED */
	/** Meshes for items. */
	UPROPERTY( Meta = ( NoAutoJson ) )
	TMap< FName, class UInstancedStaticMeshComponent* > mItemMeshMap;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_SnappedPassthroughs )
	TArray< class AFGBuildablePassthrough* > mSnappedPassthroughs;

	/** Tobias 2024-05-20: We need this data replicated in order to scale the bellows on client, because clients can't access the opposing connections. */
	UPROPERTY( Replicated )
	float mOpposingConnectionClearance[2];

	UPROPERTY( EditDefaultsOnly, meta = (AllowPrivateAccess = "true") )
	UStaticMeshComponent* mVisibilityComponent;
	
	/** The names of the fog plane components so they can be referenced */
	inline static const FName FOG_PLANE_0 = FName( TEXT( "FogPlane0" ) );
	inline static const FName FOG_PLANE_1 = FName( TEXT( "FogPlane1" ) );

	/** Cached values for conveyor renderer. */
	FRenderTransform PreCachedBaseRenderTransform;
	FVector3f ItemDirection;
};

inline void AFGBuildableConveyorLift::PostSerializedFromBlueprint( bool isBlueprintWorld )
{
	Super::PostSerializedFromBlueprint( isBlueprintWorld );

	if( isBlueprintWorld )
	{
		SetupConnections();
	}
}

/**
 * Templated function implementations.
 */
template< typename MeshConstructor >
void AFGBuildableConveyorLift::BuildStaticMeshes( USceneComponent* parent, const FTransform& endTransform, UStaticMesh* bottomMesh, UStaticMesh* midMesh, UStaticMesh* halfMidMesh, UStaticMesh* topMesh,
												 float stepHeight, TArray< AFGBuildablePassthrough* > snappedPassthroughs, bool isConnectionReversed, bool shouldFlipOnReverse, TArray< UStaticMeshComponent* >& meshPool, MeshConstructor meshConstructor )
{
	fgcheck( parent );
	const bool bHasPassthrough = snappedPassthroughs[ 0 ] && snappedPassthroughs[ 1 ];

	float heightOfBottomPassthrough = snappedPassthroughs[ 0 ] == nullptr ? 0.f : snappedPassthroughs[ 0 ]->GetSnappedBuildingThickness();
	float heightOfTopPassthrough = snappedPassthroughs[ 1 ] == nullptr ? 0.f : snappedPassthroughs[ 1 ]->GetSnappedBuildingThickness();
	float totalPassthroughHeight = heightOfTopPassthrough + heightOfBottomPassthrough;

	const float height = FMath::Abs( endTransform.GetTranslation().Z ) - ( totalPassthroughHeight / 2.f );
	const float stepDir = FMath::FloatSelect( endTransform.GetTranslation().Z, 1., -1. );
	const bool isReversed = stepDir < 0.f;

	const bool bShouldFlipMesh = isConnectionReversed ? (!isReversed && shouldFlipOnReverse) : (isReversed && shouldFlipOnReverse);
	
	int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( height / stepHeight ) + (bHasPassthrough ? 0 : 1) );
	
	// When snapping to two passthroughs it is sometimes neccesary to use a half segment at the end to ensure the mesh doesn't clip through thin foundations
	bool useHalfMeshEnd =	( snappedPassthroughs[ 0 ] && isReversed ) &&
							( snappedPassthroughs[ 0 ] && snappedPassthroughs[ 1 ] && 
							( ( FMath::FloorToInt( height ) % FMath::FloorToInt( stepHeight ) ) != 0 ) );
	
	useHalfMeshEnd =		useHalfMeshEnd ||
							( !snappedPassthroughs[ 0 ] && snappedPassthroughs[ 1 ] && ( ( FMath::FloorToInt( height ) % FMath::FloorToInt( stepHeight ) ) != 0 ) );

	// Special case here for conveyor lifts snapped at the bottom. Their minimum height is allowed to be so small no mid meshes are required
	if( height <= stepHeight && isReversed )
	{
		numMeshes = 1;
	}
	
	// If we end up with 0 meshes, usually if our height is 0, then we'll force it to 1 and use a half mesh end
	if( numMeshes <= 0 )
	{
		numMeshes = 1;
		useHalfMeshEnd = true;
	}

	// Create more or remove the excess meshes.
	if( numMeshes < meshPool.Num() )
	{
		while( meshPool.Num() > numMeshes )
		{
			meshPool.Last()->DestroyComponent();
			meshPool.Pop();
		}
	}
	else if( numMeshes > meshPool.Num() )
	{
		while( meshPool.Num() < numMeshes )
		{
			meshPool.Push( meshConstructor( parent ) );
		}
	}

	const FQuat midRotation = endTransform.GetRotation();

	// Stack all pieces on top of each other. When snapping to a passthrough we begin placing the stepped segments at index 0 rather than 1
	int32 startAtIndex = 1;
	if( snappedPassthroughs[ 0 ] )
	{
		startAtIndex = 0;
	}

	for( int32 i = startAtIndex; i < meshPool.Num(); ++i )
	{
		auto mesh = meshPool[ i ];

		float STEP_ALIGNMENT = 0.f;

		// When snapping to a passthrough we use the half thickness (the surface) of the foundation as the step alignment
		if( snappedPassthroughs[ 0 ] == nullptr )
		{
			STEP_ALIGNMENT = 50.f;
		}
		else
		{
			STEP_ALIGNMENT = ( heightOfBottomPassthrough / 2.f ) * -stepDir;
			if( isReversed )
			{
				if( snappedPassthroughs[ 0 ] && !snappedPassthroughs[ 1 ] && isReversed && i == meshPool.Num() - 2 )
				{
					STEP_ALIGNMENT += stepHeight / 2.f;
				}
				else
				{
					if( bShouldFlipMesh )
					{
						STEP_ALIGNMENT += stepHeight / 2.f;
					}
					else
					{
						STEP_ALIGNMENT += (useHalfMeshEnd && i == meshPool.Num() - 1 ) ? stepHeight / 2.f : stepHeight;
					}
				}
			}
		}

		float stepDist = ( stepDir * stepHeight * i ) - STEP_ALIGNMENT;

		mesh->SetRelativeLocation( FVector::UpVector * stepDist );
		mesh->SetRelativeRotation( midRotation );

		if( i == meshPool.Num() - 2 && snappedPassthroughs[ 0 ] && !snappedPassthroughs[ 1 ] && isReversed )
		{
			mesh->SetStaticMesh( halfMidMesh );
		}
		else
		{
			mesh->SetStaticMesh( midMesh );
		}
	}
	
	// Update the last and first piece.
	if( auto mesh = meshPool.Last() )
	{
		if( snappedPassthroughs[ 1 ] == nullptr )
		{
			mesh->SetRelativeLocationAndRotation( endTransform.GetLocation(), endTransform.GetRotation() );
			mesh->SetStaticMesh( isReversed ? bottomMesh : topMesh );
		}
		else
		{
			// When snapping to a passthrough at the top we replace the top output with a mid mesh segment. Half a mid mesh if that is desirable
			mesh->SetRelativeRotation( midRotation );
			mesh->SetStaticMesh( useHalfMeshEnd ? halfMidMesh : midMesh );
		}
	}
	if( auto mesh = meshPool[ 0 ] )
	{
		if( snappedPassthroughs[ 0 ] == nullptr )
		{
			mesh->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
			mesh->SetStaticMesh( isReversed ? topMesh : bottomMesh );
		}
		else
		{
			if( meshPool.Num() > 1 )
			{
				// When the first snap is to a passthrough, replace the bottom mesh with a mid mesh segment
				mesh->SetStaticMesh( midMesh );
			}
		}
	}

	if( bShouldFlipMesh )
	{
		FTransform flipTransform = FTransform();
		float zOffset = ( snappedPassthroughs[0] || (snappedPassthroughs[0] == nullptr && snappedPassthroughs[1] == nullptr) ) ? -50.f : 0.f; // This is a bit hacky to account for different spacing behaviour. Again, with all the special cases this code should perhaps be rewritten entirely
		flipTransform.SetLocation( endTransform.GetLocation() - FVector( 0.f, 0.f, zOffset ) );
		flipTransform.SetRotation( FRotator( 180.f, 0.f, 0.f).Quaternion() );
		int32 startAt = snappedPassthroughs[0] == nullptr ? 1 : 0;
		int32 endAt = snappedPassthroughs[1] == nullptr ? numMeshes - 1 : numMeshes;
		for( int32 i = startAt; i < endAt; ++i)
		{
			auto& mesh = meshPool[ i ];
			FTransform meshRelative = mesh->GetRelativeTransform();
			meshRelative *= flipTransform;
			mesh->SetRelativeTransform( meshRelative );
		}
	}

	// Register new meshes, needs to happen after the properties are set for static components.
	for( auto mesh: meshPool )
	{
		if( !mesh->IsRegistered() )
		{
			mesh->RegisterComponent();
		}
	}
}
