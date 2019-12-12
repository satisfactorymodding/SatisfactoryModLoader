// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableConveyorBase.h"
#include "FGBuildableConveyorLift.generated.h"

/** Base for conveyor lifts. */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorLift : public AFGBuildableConveyorBase
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorLift();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

protected:
	// Begin AFGBuildableConveyorBase interface
	virtual void TickItemTransforms( float dt ) override;
	// End AFGBuildableConveyorBase interface

private:
	template< typename MeshConstructor >
	static void BuildStaticMeshes(
		USceneComponent* parent,
		const FTransform& endTransform,
		UStaticMesh* bottomMesh,
		UStaticMesh* midMesh,
		UStaticMesh* topMesh,
		float stepHeight,
		TArray< UStaticMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	static FBoxCenterAndExtent FitClearance(
		float transformZ,
		float stepHeight,
		const FVector2D& extend2D,
		const FVector& extentBias = FVector::ZeroVector );

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

	UPROPERTY( SaveGame, ReplicatedUsing= OnRep_TopTransform )
	FTransform mTopTransform;
	UPROPERTY( SaveGame, Replicated )
	bool mIsReversed;

	/** Meshes for items. */
	UPROPERTY( Meta = ( NoAutoJson ) )
	TMap< FName, class UInstancedStaticMeshComponent* > mItemMeshMap;
};


/**
 * Templated function implementations.
 */
template< typename MeshConstructor >
void AFGBuildableConveyorLift::BuildStaticMeshes(
	USceneComponent* parent,
	const FTransform& endTransform,
	UStaticMesh* bottomMesh,
	UStaticMesh* midMesh,
	UStaticMesh* topMesh,
	float stepHeight,
	TArray< UStaticMeshComponent* >& meshPool,
	MeshConstructor meshConstructor )
{
	check( parent );

	const float height = FMath::Abs( endTransform.GetTranslation().Z );
	const float stepDir = FMath::FloatSelect( endTransform.GetTranslation().Z, 1.f, -1.f );
	const bool isReversed = stepDir < 0.f;
	const int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( height / stepHeight ) + 1 );

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

	// Stack all pieces on top of each other.
	for( int32 i = 1; i < meshPool.Num() - 1; ++i )
	{
		auto mesh = meshPool[ i ];

		const float STEP_ALIGNMENT = 50.f;
		const float stepDist = ( stepDir * stepHeight * i ) - STEP_ALIGNMENT;

		mesh->SetRelativeLocation( FVector::UpVector * stepDist );
		mesh->SetRelativeRotation( midRotation );

		mesh->SetStaticMesh( midMesh );
	}

	// Update the last and first piece.
	if( auto mesh = meshPool.Last() )
	{
		mesh->SetRelativeLocationAndRotation( endTransform.GetLocation(), endTransform.GetRotation() );
		mesh->SetStaticMesh( isReversed ? bottomMesh : topMesh );
	}
	if( auto mesh = meshPool[ 0 ] )
	{
		mesh->SetRelativeLocationAndRotation( FVector::ZeroVector, FRotator::ZeroRotator );
		mesh->SetStaticMesh( isReversed ? topMesh : bottomMesh );
	}

	// Register new meshes, needs to happen after the properties are set for static components.
	for( auto mesh : meshPool )
	{
		if( !mesh->IsRegistered() )
		{
			mesh->RegisterComponent();
		}
	}
}
