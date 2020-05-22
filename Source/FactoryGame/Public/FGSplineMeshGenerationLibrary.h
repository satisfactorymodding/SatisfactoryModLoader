// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "FGInstancedSplineMeshComponent.h"
#include "FGSplineMeshGenerationLibrary.generated.h"

/**
 * Helper library for generating spline meshes, collision and meshes along a splines.
 */
UCLASS()
class FACTORYGAME_API UFGSplineMeshGenerationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Given a spline, this creates non-instanced spline meshes along the spline.
	 *
	 * @param spline			The spline the meshes should go along.
	 *
	 * @param mesh				The static mesh to spline, it will be splined along the X-axis.
	 *
	 * @param meshLength		The length of the given mesh, along it's X-axis.
	 *
	 * @param meshPool			Mesh pool to use for the created spline meshes, new meshes are created
	 *							as needed and old meshes are removed if there are too many in a reused pool.
	 *							Pools can be reused and the meshes will be re-splined to fix the current need,
	 *							This is useful for holograms as the spline change around a lot.
	 *
	 * @param meshConstructor	Lambda or other function that creates a new mesh to put in the pool.
	 *							The constructor is responsible for calling SetupAttachment and set the Owner.
	 *							The constructor must never call RegisterComponent.
	 *							If the returned mesh have mobility Static, then the pool cannot be reused as any further changes to the mesh have no effect.
	 *
	 *							Example:
	 *							[]( USplineComponent* spline )
	 *							{
	 *								USplineMeshComponent* newComponent = NewObject< USplineMeshComponent >( spline->GetOwner(), USplineMeshComponent::StaticClass() );
	 *
	 *								newComponent->SetupAttachment( spline );
	 *								newComponent->Mobility = EComponentMobility::Movable;
	 *
	 *								// Custom initialization steps
	 *
	 *								return newComponent;
	 *							}
	 */
	template< typename MeshConstructor >
	static void BuildSplineMeshes(
		class USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
		TArray< USplineMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	/**
	 * Overload that can limit the number of meshes generated.
	 *
	 * @param maxNumMeshes      Maximum number of meshes to generate from the start of the spline,
	 *                          This will cut of the generation after that point even if the
	 *                          spline requires more meshes to be completely filled.
	 */
	template< typename MeshConstructor >
	static void BuildSplineMeshes(
		class USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
		int32 maxNumMeshes,
		TArray< USplineMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	/**
	 * Given a spline, this creates an instanced spline mesh along the spline.
	 *
	 * For all parameters see BuildSplineMeshes.
	 *
	 * @param splineInstances    The instance component to fill up with spline instances.
	 *                           This can be reused between calls to update an existing one.
	 *                           If this have mobility Static, it must not be registered before calling this function, if it is then this function have no effect.
	 */
	static void BuildSplineMeshesInstanced(
		class USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
		UFGInstancedSplineMeshComponent* splineInstances );

	/**
	 * Given a spline, this creates an instanced spline mesh along the spline.
	 *
	 * For all parameters see BuildSplineMeshesInstanced.
	 */
	static void BuildSplineMeshesPerSegmentInstanced(
		class USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
		UFGInstancedSplineMeshComponent* splineInstances );

	/**
	 * Given a spline, this creates collisions along the spline.
	 *
	 * @param spline			The spline the collisions should go along.
	 * @param collisionExtent	The size of the collision, X is forward along the spline, Y is sideways and Z is height.
	 * @param collisionSpacing	The distance between each collision.
	 * @param collisionOffset	The offset of the collision in the spline local space, see collisionExtent above.
	 * @param collisionProfile	The collision profile to apply for the generated collision.
	 *
	 * @note The created collisions are registered and attached to the spline with the same owning actor.
	 */
	static void BuildSplineCollisionBoxesWithFixedSteps_DEPRECATED(
		class USplineComponent* spline,
		const FVector& collisionExtent,
		float collisionSpacing,
		const FVector& collisionOffset,
		FName collisionProfile );

	/**
	 * See function above.
	 * This uses a variable segment length approach to more segments where needed.
	 */
	static void BuildSplineCollisionBoxesWithVariableSteps(
		class USplineComponent* spline,
		const FVector& collisionExtent,
		float collisionSpacing,
		const FVector& collisionOffset,
		FName collisionProfile );

	/**
	 * Given a spline, this creates collisions along the spline.
	 *
	 * @param spline			The spline the collisions should go along.
	 * @param collisionRadius	The radius of the collision on the spline.
	 * @param collisionSpacing	The distance between each collision.
	 * @param collisionOffset	The offset of the collision in the spline local space, see collisionExtent above.
	 * @param collisionProfile	The collision profile to apply for the generated collision.
	 *
	 * @note The created collisions are registered and attached to the spline with the same owning actor.
	 */
	static void BuildSplineCollisionCapsules(
		class USplineComponent* spline,
		float collisionRadius,
		float collisionSpacing,
		const FVector& collisionOffset,
		FName collisionProfile );

	/** GetNextDistanceExceedingTolerance used to step though a spline to take as long straight steps as possible within an error threshold
	 *
	 * @param	startPos - position on spline. In sync with startDistance. Only sent in so we needing less fetches from the spline, as it can be used from last result in a loop
	 * @param	startDistance - distance on spline to start from
	 * @param	stepSize - the distance to take in each test. (will use half distance to search back when violation of limits exceeded)
	 * @param	tolerance - see it as a bound value that as long as the curve stay within, we continue
	 * @param	outEndDistance - the end distance that is just within the threshold
	 * @param	outEndPos - the position on the spline at the end distance
	 * @param	outLength - the length of the segment connecting the start and the end point. Can be used to calculate a direction of the segment if needed for collision or similar
	 * @param	fineTuningIterations - once found the step that takes us outside, how many times should that be refined with binary search to get closer to the exact position? See this a a precision thing.
	 * @param	minStepFactor - what factor of the step size to use for the minimum step we can accept (used to make sure we don't take a too small first step and that we don't leave too little behind in the end. Min step pwill be this factor * stepSize
	 *
	 * @return	bool - returns false if we've reached the end and true if there is still more left
	 */
	static bool GetNextDistanceExceedingTolerance(
		USplineComponent* spline,
		const FVector& startPos,
		float startDistance,
		float stepSize,
		float tolerance,
		float& outEndDistance,
		FVector& outEndPos,
		float& outLength,
		uint8 fineTuningIterations = 5,
		float minStepFactor = 0.5f,
		ESplineCoordinateSpace::Type space = ESplineCoordinateSpace::World );

public:
	FORCEINLINE ~UFGSplineMeshGenerationLibrary() = default;
};

/**
 * Templated function implementations.
 */
template< typename MeshConstructor >
void UFGSplineMeshGenerationLibrary::BuildSplineMeshes(
	class USplineComponent* spline,
	UStaticMesh* mesh,
	float meshLength,
	TArray< USplineMeshComponent* >& meshPool,
	MeshConstructor meshConstructor )
{
	const int32 REASONABLE_MAX_NUM_MESHES = 500;

	BuildSplineMeshes( spline, mesh, meshLength, REASONABLE_MAX_NUM_MESHES, meshPool, meshConstructor );
}

template< typename MeshConstructor >
void UFGSplineMeshGenerationLibrary::BuildSplineMeshes(
	class USplineComponent* spline,
	UStaticMesh* mesh,
	float meshLength,
	int32 maxNumMeshes,
	TArray< USplineMeshComponent* >& meshPool,
	MeshConstructor meshConstructor )
{
	check( spline );

	const float splineLength = spline->GetSplineLength();
	const int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( splineLength / meshLength ) );

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
		while( meshPool.Num() < numMeshes && meshPool.Num() < maxNumMeshes )
		{
			if( auto newMesh = meshConstructor( spline ) )
			{
				meshPool.Push( newMesh );
			}
			else
			{
				// If the constructor failed, any subsequent calls will most likely fail as well. Might as well warn about this and bail.
				UE_LOG( LogGame, Warning, TEXT( "BuildSplineMeshes() failed, mesh constructor return null, spline '%s' with owner '%s'" ),
						*spline->GetName(), spline->GetOwner() ? *spline->GetOwner()->GetName() : TEXT( "none" ) );

				break;
			}
		}
	}

	// Put all pieces along the spline.
	{
		const float segmentLength = splineLength / numMeshes;

		for( int32 i = 0; i < meshPool.Num(); ++i )
		{
			const float startDistance = ( float )i * segmentLength;
			const float endDistance = ( float )( i + 1 ) * segmentLength;
			const FVector startPos = spline->GetLocationAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::Local );
			const FVector startTangent = spline->GetTangentAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::Local ).GetSafeNormal() * segmentLength;
			const FVector endPos = spline->GetLocationAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::Local );
			const FVector endTangent = spline->GetTangentAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::Local ).GetSafeNormal() * segmentLength;

			meshPool[ i ]->SetStartAndEnd( startPos, startTangent, endPos, endTangent, true );
			meshPool[ i ]->SetStaticMesh( mesh );
		}
	}

	// Register new meshes, needs to happen after the properties are set for static components.
	for( auto meshComp : meshPool )
	{
		if( !meshComp->IsRegistered() )
		{
			meshComp->RegisterComponent();
		}
	}
}
