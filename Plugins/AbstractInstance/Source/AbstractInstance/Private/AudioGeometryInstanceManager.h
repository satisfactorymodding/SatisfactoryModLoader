// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AkInstancedGeometryComponent.h"
#include "Math/GenericOctree.h"
#include "AudioGeometryInstanceManager.generated.h"

struct FAudioInstanceData
{
	UAkInstancedGeometryComponent* Component; //may be invalid if the instance was removed
	void* HandlePtr;
	FVector Position;
	FRotator Rotation;
	FVector Scale;
	FBoxCenterAndExtent Bounds;
	bool AddedToAkComponent;
};

struct FAudioInstanceOctreeSemantics
{
	// When a leaf gets more than this number of elements, it will split itself into a node with multiple child leaves
	enum { MaxElementsPerLeaf = 10 };

	// This is used for incremental updates.  When removing a polygon, larger values will cause leaves to be removed and collapsed into a parent node.
	enum { MinInclusiveElementsPerNode = 5 };

	// How deep the tree can go.
	enum { MaxNodeDepth = 20 };

	using FOctree = TOctree2< FAudioInstanceData*, FAudioInstanceOctreeSemantics >;

	using ElementAllocator = TInlineAllocator< MaxElementsPerLeaf >;

	static FBoxCenterAndExtent GetBoundingBox( const FAudioInstanceData* Element );
	static bool AreElementsEqual( const FAudioInstanceData* A, const FAudioInstanceData* B );
	static void SetElementId( FOctree& Octree, const FAudioInstanceData* Element, FOctreeElementId2 OctreeElementID );
};

struct FAudioInstanceOctree : public TOctree2< FAudioInstanceData*, FAudioInstanceOctreeSemantics >
{
	FAudioInstanceOctree( const FVector& InOrigin, FVector::FReal InExtent ) :
		TOctree2( InOrigin, InExtent )
	{
	}

	FAudioInstanceOctree() = default;

	TMap< void*, FOctreeElementId2 > mElementIdMap;
};

UCLASS()
class UAudioGeometryInstanceManager : public UObject
{
	GENERATED_BODY()
public:
	UAudioGeometryInstanceManager();
	virtual ~UAudioGeometryInstanceManager() override;

	void ProcessTick( const FVector& PlayerLocation );

	void AddAudioGeometryInstance( const FTransform& InstanceLocation, const FVector& BoxExtent, const FVector& Scale,
	                               UAkInstancedGeometryComponent* GeometryOwnerComponent, void* HandlePtr );
	void RemoveAudioGeometryInstance( void* HandlePtr );

private:
	void EnsureTaskComplete();

	void FindAddsRemovesWT( const FVector& PlayerLocation ); // Worker thread
	void PerformAddsRemovesGT(); // Game thread

private:
	FAudioInstanceOctree AudioInstanceOctree;
	TSet< FAudioInstanceData* > LocalAudioSurrounding;
	TSet< FAudioInstanceData* > NewLocalAudioSurrounding;

	TSet< FAudioInstanceData* > RemovedInstances;
	TSet< FAudioInstanceData* > AddedInstances;

	FGraphEventRef AudioGeometryUpdateTask;
};