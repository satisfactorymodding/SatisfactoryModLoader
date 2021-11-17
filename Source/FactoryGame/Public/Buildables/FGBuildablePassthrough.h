// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildablePassthrough.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePassthrough : public AFGBuildable
{
	GENERATED_BODY()

public:

	AFGBuildablePassthrough();

	// Begin Actor Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End Actor Interface

	// Begin IFGDismantleInterface
	virtual void StartIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	// End IFGDismantleInterface


	float GetMidMeshLength() { return mMidMeshLength; }
	class UStaticMesh* GetMidMesh() { return mMidMesh; }
	class UStaticMesh* GetCapMesh() { return mCapMesh; }
	FRotator GetMidMeshRotation() { return mMidMeshRotation; }
	FRotator GetEndCapRotation() { return mEndCapRotation; }
	FVector GetEndCapTranslation() { return mEndCapTranslation; }

	bool GetIsUsingSoftClearance() const { return mUseSoftClearance; }

	// returns the thickness of the buildable this passthrough snapped to
	FORCEINLINE float GetSnappedBuildingThickness() { return mSnappedBuildingThickness; }

	// Does this passthrough  have any buildings attached?
	FORCEINLINE bool HasAnyAttachedBuildings() { return mBottomSnappedConnection || mTopSnappedConnection; }

	// When performing clearance checks, ignore these buildables as they are relevant to the passthrough and shouldn't impact clearance
	void GetIgnoredBuildablesForClearanceOnSnap( TArray< AFGBuildable* >& out_ignoredBuildables );

	// Get the conneciton component class
	TSubclassOf< class UFGConnectionComponent > GetConnectionClass() { return mConnectionComponentClass; }

	// Outputs the normalized direction that a lift can snapped to this connection on. This will return a zero vector if both directions are valid
	// Returns false if no directions are valid
	bool GetValidAttachDirection( FVector& out_validDir );

	template< class ConnectionType >
	ConnectionType* GetBottomSnappedConnection() { return Cast< ConnectionType >( mBottomSnappedConnection ); }
	
	void SetBottomSnappedConnection( class UFGConnectionComponent* connection );
	
	template< class ConnectionType >
	ConnectionType* GetTopSnappedConnection() { return Cast< ConnectionType >( mTopSnappedConnection ); }
	
	void SetTopSnappedConnection( class UFGConnectionComponent* connection );

	// Called when an attached buildable is dismantled to let us know that it no longer needs to be considered
	void OnAttachedBuildableDismantled( class AFGBuildable* dismantledBuildable );

protected:
	UPROPERTY( SaveGame, Replicated )
	float mSnappedBuildingThickness;

	UPROPERTY( EditDefaultsOnly )
	float mMidMeshLength;

	/** Should be generate collision for the tunnel portion of this component */
	UPROPERTY( EditDefaultsOnly )
	bool mGenerateTunnelCollision;

	/** Mesh place at each entrance to the passthrough */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mCapMesh;

	/** Mesh to repeat to create the center area */
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mMidMesh;

	UPROPERTY( EditDefaultsOnly )
	FRotator mEndCapRotation;

	UPROPERTY( EditDefaultsOnly )
	FRotator mMidMeshRotation;

	UPROPERTY( EditDefaultsOnly )
	FVector mEndCapTranslation;

	UPROPERTY( EditDefaultsOnly )
	float mClearanceHeightMin;

	UPROPERTY( EditDefaultsOnly )
	float mClearanceThickness;

	UPROPERTY( EditDefaultsOnly )
	bool mUseSoftClearance;

	UPROPERTY( SaveGame, Replicated )
	class UFGConnectionComponent* mBottomSnappedConnection;

	UPROPERTY( SaveGame, Replicated )
	class UFGConnectionComponent* mTopSnappedConnection;


	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UFGConnectionComponent > mConnectionComponentClass;

private:
	friend class AFGPassthroughHologram;

	template< typename MeshConstructor > static void BuildStaticMeshes( USceneComponent* parent, 
								const FVector& stepDir, 
								float thickness,
								float stepSize, 
								FRotator midRotation , 
								FRotator endRotation ,
								FVector endCapTranslation,
								UStaticMesh* midMesh, 
								UStaticMesh* capMesh, 
								TArray< UStaticMeshComponent* >& meshPool, 
								MeshConstructor meshConstructor );
	
};


/**
 * Mesh Constructor. Similar to the ConveyorLift template
 */
template< typename MeshConstructor >
void AFGBuildablePassthrough::BuildStaticMeshes( USceneComponent* parent, const FVector& stepDir, float thickness, float stepSize, FRotator midRotation, FRotator endRotation,
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
