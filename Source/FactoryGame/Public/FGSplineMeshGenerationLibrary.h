// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "InstancedSplineMeshComponent.h"
#include "FactoryGame.h"
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
	 * @oaram maxSplineLengthToFill		The lenght of the spline to fill with meshes, any distance after this will be left without meshes.
	 * 									This can be more than the spline length (in which case spline length is used)
	 * 									If this is 0 or less, no meshes will be generated.
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
	 * 							This is only called when a new mesh needs to be created in the pool,
	 * 							This means that if the number of meshes needed remains constant this
	 * 							is only called the first time the function is called.
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
		float maxSplineLengthToFill,
		UStaticMesh* mesh,
		float meshLength,
		TArray< USplineMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	static void BuildNaniteSplineMeshes(USplineComponent* spline,UStaticMesh* Mesh, float meshLength, TArray<USplineMeshComponent*>& outMeshes);
	static void BuildSplineMeshesInstanced(USplineComponent* spline, float meshLength, class UInstancedSplineMeshComponent* splineInstances);

	/**
	 * Given a spline, this creates an instanced spline mesh along the spline.
	 *
	 * For all parameters see BuildSplineMeshesInstanced.
	 */
	static void BuildSplineMeshesPerSegmentInstanced(
		USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
	    UInstancedSplineMeshComponent* splineInstances );

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
	template< typename ComponentType >
	static TArray< ComponentType* > BuildSplineCollisionBoxesWithVariableSteps(
		class USplineComponent* spline,
		const FVector& collisionExtent,
		float collisionSpacing,
		const FVector& collisionOffset,
		FName collisionProfile,
		USceneComponent* optionalRoot = nullptr );

	/**
	 *
	 *
	 *
	 */
	static UInstancedStaticMeshComponent* BuildSplineMeshCollisionWithDistanceFieldProxies(
		class USplineComponent* spline,
		const FVector& collisionExtent,
		float collisionSpacing,
		const FVector& collisionOffset,
		FName collisionProfile,
		UStaticMesh* oneMeterBoxMesh,
		USceneComponent* optionalRoot = nullptr);
	
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
};

/**
 * Templated function implementations.
 */
template< typename ComponentType >
TArray< ComponentType* > UFGSplineMeshGenerationLibrary::BuildSplineCollisionBoxesWithVariableSteps(
	USplineComponent* spline,
	const FVector& collisionExtent,
	float collisionSpacing,
	const FVector& collisionOffset,
	FName collisionProfile,
	USceneComponent* optionalRoot /* nullptr */ )
{
	fgcheck( spline );
	auto debugActor = spline->GetOwner();

	collisionSpacing *= 0.7f; //just make a bit smaller to make up for potential errors margins in the binary search
	//FVector startPos = spline->GetLocationAtSplinePoint( 0, optionalRoot ? ESplineCoordinateSpace::Local : ESplineCoordinateSpace::World );
	FVector startPos = spline->GetLocationAtSplinePoint( 0, ESplineCoordinateSpace::World );
	FVector endPos = startPos;
	float dist = 0.0f;
	float endDist = 1.0f;
	float length = 1.0f;
	int32 i = 0;
	
	UObject* outer = optionalRoot ? optionalRoot->GetOuter() : spline->GetOuter();
	USceneComponent* attachTo = optionalRoot ? optionalRoot : spline;
	EComponentMobility::Type mobility = optionalRoot ? optionalRoot->Mobility : spline->Mobility;
	TArray< ComponentType* > generatedComopnents;

	FVector lastDir = spline->GetDirectionAtSplinePoint( 0, ESplineCoordinateSpace::World );
	
	while( true )
	{
		bool hasMore = GetNextDistanceExceedingTolerance( spline, startPos, dist, collisionSpacing, 22.0f, endDist, endPos, length );
		FVector dir = ( endPos - startPos ) / length;
		FVector centerPos = ( startPos + endPos ) * 0.5f;

		{
			float radDiff = FMath::Acos( FVector::DotProduct( dir, lastDir ) ) * collisionExtent.Y; //Rough estimate. This is the radians difference, so if we multiply it by the side extent, we get the length of the circle segment missing.
			length += radDiff * 0.5f;
			centerPos -= dir * radDiff * 0.5f;
			////@TODO:[DavalliusA:Wed/05-02-2020] ideally we should apply half this to us and half to next.. and front and back side need different compensation so we need to offset our center...  so for now just try to apply it on us only
		}
		
		// When using an optional root we may be spawning onto an actor that already has splineCollision (blueprints can have many "actors" on a single root when making the hologram)
		// In that case we don't want to assume a name so for simplicity (and since the names are temporary as its a hologram) just allow the engine to find a nice available name
		FName name = optionalRoot ? NAME_None : FName(*FString::Printf( TEXT( "SplineCollision_%i" ), i ));
		
		ComponentType* newComponent = NewObject< ComponentType >( outer, ComponentType::StaticClass(), name );
		fgcheck( newComponent );

		//newComponent->SetupAttachment( attachTo );
		newComponent->SetMobility( mobility ); // Inherit the mobility from the spline, if these mismatch we cannot register.
		newComponent->AttachToComponent( attachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale );
		newComponent->SetNetAddressable();
		FVector  ext = collisionExtent;
		ext.X = ( length * .5f ) - .05f; // Make it a bit smaller so clearance checks can go through in some cases.
		newComponent->SetBoxExtent( ext, false );
		newComponent->SetCollisionProfileName( collisionProfile );
		newComponent->SetWorldLocation( centerPos );
		//newComponent->SetRelativeLocation( centerPos );
		newComponent->AddRelativeLocation( collisionOffset );

		// [ZolotukhinN:21/03/2024] Enforce the horizontal orientation on pipes to make them always walkable by the player, but do not do it if the pipes are close to being vertical
		const float verticalDotProduct = FMath::Abs( FVector::DotProduct( dir, FVector::UpVector ) );

		// 0.8 dot product ~= 37 degrees. So for angle with vertical axis that are smaller than 37 degrees, we do not enforce a horizontal orientation. We take absolute value because direction does not matter.
		const bool bIsVertical = verticalDotProduct >= 0.8f;
		const FQuat segmentRotation = bIsVertical ? FRotationMatrix::MakeFromX( dir ).ToQuat() : FRotationMatrix::MakeFromXZUnsafe( dir, FVector::UpVector ).ToQuat();

		newComponent->SetWorldRotation( segmentRotation );
		//newComponent->SetRelativeRotation( q );
		newComponent->SetRelativeScale3D( FVector( 1.0f ) );

		newComponent->RegisterComponent();
		generatedComopnents.Add( newComponent );
		//if( debugActor ){ DrawDebugBox( debugActor->GetWorld(), centerPos, ext, q, debugColor, false, 90.04f, 99, 1.0f ); }

		lastDir = dir;
		startPos = endPos;
		dist = endDist;
		++i;
		if( !hasMore )
		{
			break;
		}
	}

	return generatedComopnents;
}


template< typename MeshConstructor >
void UFGSplineMeshGenerationLibrary::BuildSplineMeshes(
	class USplineComponent* spline,
	float maxSplineLengthToFill,
	UStaticMesh* mesh,
	float meshLength,
	TArray< USplineMeshComponent* >& meshPool,
	MeshConstructor meshConstructor )
{
	fgcheck( spline );

	const float splineLengthToFill = FMath::Clamp( spline->GetSplineLength(), 0.f, maxSplineLengthToFill );
	const int32 numMeshes = splineLengthToFill > SMALL_NUMBER ? FMath::Max( 1, FMath::RoundToInt( splineLengthToFill / meshLength ) ) : 0;

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
		const float segmentLength = splineLengthToFill / numMeshes;

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
