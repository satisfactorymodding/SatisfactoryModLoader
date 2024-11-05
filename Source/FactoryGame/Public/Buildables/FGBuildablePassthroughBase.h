// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGBuildablePassthroughBase.generated.h"

UCLASS()
class FACTORYGAME_API AFGBuildablePassthroughBase : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildablePassthroughBase();

	// Begin Actor Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End Actor Interface

	// Begin FGBuildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	// End FGBuildable interface

	FORCEINLINE float GetMidMeshLength() const { return mMidMeshLength; }
	FORCEINLINE class UStaticMesh* GetMidMesh() const { return mMidMesh; }
	FORCEINLINE class UStaticMesh* GetCapMesh() const { return mCapMesh; }
	FORCEINLINE FRotator GetMidMeshRotation() const { return mMidMeshRotation; }
	FORCEINLINE FRotator GetEndCapRotation() const { return mEndCapRotation; }
	FORCEINLINE FVector GetEndCapTranslation() const { return mEndCapTranslation; }
	FORCEINLINE float GetClearanceThickness() const { return mClearanceThickness; }
	FORCEINLINE float GetClearanceMinHeight() const { return mClearanceHeightMin; }
	FORCEINLINE float GetCostSegmentLength() const { return mCostSegmentLength; }

	/** Returns the thickness of the passthrough */
	FORCEINLINE float GetSnappedBuildingThickness() const { return mSnappedBuildingThickness; }

	/** When performing clearance checks, ignore these buildables as they are relevant to the passthrough and shouldn't impact clearance */
	virtual void GetIgnoredBuildablesForClearance( TArray< AFGBuildable* >& out_ignoredBuildables );

	/** Checks the overlap of the foundations with the clearance of this buildable type at the provided location with provided thickness. Safe to call on the CDO */
	void OverlapCheckFoundations( UWorld* world, const FVector& worldLocation, const FQuat& worldRotation, float thickness, TArray<class AFGBuildableFoundation*>& out_foundations ) const;
	
	/** Convenient accessor to build static meshes using the properties of this buildable. Used by the buildable itself and also by the hologram. */
	template<typename MeshConstructor>
	FORCEINLINE void BuildStaticMeshesForPassthrough( USceneComponent* parentComponent, float thickness, TArray< UStaticMeshComponent* >& meshPool, MeshConstructor meshConstructor ) const
	{
		BuildStaticMeshes( parentComponent, FVector::UpVector, thickness, mMidMeshLength, mMidMeshRotation, mEndCapRotation, mEndCapTranslation, mCapMesh, mMidMesh, meshPool, meshConstructor );
	}

	/** Sets the snapped building thickness. Must be called before BeginPlay as the static mobility components cannot be moved after they are registered */
	FORCEINLINE void SetSnappedBuildingThickness_BeforeBeginPlay( float newThickness )
	{
		ensureMsgf( !HasActorBegunPlay(), TEXT("SetSnappedBuildingThickness_BeforeBeginPlay called after BeginPlay") );
		mSnappedBuildingThickness = newThickness;
	}
protected:	
	/** The thickness of the building we are snapped to */
	UPROPERTY( VisibleInstanceOnly, SaveGame, Replicated, Category = "Passthrough" )
	float mSnappedBuildingThickness;

	/** Length of a single segment of the mid mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	float mMidMeshLength;

	/** Should be generate collision for the tunnel portion of this component */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	bool mGenerateTunnelCollision;

	/** Mesh place at each entrance to the passthrough */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	class UStaticMesh* mCapMesh;

	/** Mesh to repeat to create the center area */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	class UStaticMesh* mMidMesh;

	/** Rotation of the end cap mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	FRotator mEndCapRotation;

	/** Rotation of the mid mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	FRotator mMidMeshRotation;

	/** Translation of the cap meshes */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	FVector mEndCapTranslation;

	/** Minimum height of the clearance */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	float mClearanceHeightMin;

	/** Thickness of the clearance box for the buildable */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	float mClearanceThickness;

	/** Length of the single segment for the cost calculation. To retain consistency with current cost and old saves, it is set to the maximum foundation height */
	UPROPERTY( EditDefaultsOnly, Category = "Passthrough" )
	float mCostSegmentLength;
	
	UPROPERTY()
	TArray< UStaticMeshComponent* > mGeneratedMeshComponents;
private:
	template<typename MeshConstructor>
	static void BuildStaticMeshes( USceneComponent* parent, const FVector& stepDir, float thickness, float stepSize, FRotator midRotation, FRotator endRotation,
		FVector endCapTranslation, UStaticMesh* midMesh, UStaticMesh* capMesh, TArray< UStaticMeshComponent* >& meshPool, MeshConstructor meshConstructor );
};

/**
 * Mesh Constructor. Similar to the ConveyorLift template
 */
template< typename MeshConstructor >
void AFGBuildablePassthroughBase::BuildStaticMeshes( USceneComponent* parent, const FVector& stepDir, float thickness, float stepSize, FRotator midRotation, FRotator endRotation,
												 FVector capTranslation, UStaticMesh* capMesh, UStaticMesh* midMesh,
												  TArray< UStaticMeshComponent* >& meshPool, MeshConstructor meshConstructor )
{
	const int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( thickness / stepSize ) + 2 );

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

	// Stack all pieces on top of each other.
	for( int32 i = 1; i < meshPool.Num() - 1; ++i )
	{
		auto mesh = meshPool[ i ];

		const float STEP_ALIGNMENT = thickness / 2.f;
		const float stepDist = ( stepSize * (i - 1) ) - STEP_ALIGNMENT;

		mesh->SetRelativeLocation( stepDir * stepDist );
		mesh->SetRelativeRotation( midRotation );

		mesh->SetStaticMesh( midMesh );
	}

	FVector magicFudgeDir = stepDir * 3.f;
	// Update the last and first piece.
	if( auto mesh = meshPool.Last() )
	{
		mesh->SetRelativeLocationAndRotation( ( ( ( stepDir * thickness ) / 2.f ) + capTranslation ) - magicFudgeDir, endRotation);
		mesh->SetStaticMesh( capMesh );
	}
	if( auto mesh = meshPool[ 0 ] )
	{
		mesh->SetRelativeLocationAndRotation( (-( ( stepDir * thickness ) / 2.f ) - capTranslation ) + magicFudgeDir, FRotator( 0.f, 0.f, 180.f) + endRotation );
		mesh->SetStaticMesh( capMesh );
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
