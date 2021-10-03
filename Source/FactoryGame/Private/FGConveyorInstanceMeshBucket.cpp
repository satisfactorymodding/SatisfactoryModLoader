#include "FGConveyorInstanceMeshBucket.h"

UFGConveyorInstanceMeshBucket::UFGConveyorInstanceMeshBucket() : Super() { }

void UFGConveyorInstanceMeshBucket::Init() { }

void UFGConveyorInstanceMeshBucket::DirectUpdateInstance(const TArray<FTransform>& Transforms) { }

FBoxSphereBounds UFGConveyorInstanceMeshBucket::CalcBounds(const FTransform& LocalToWorld) const { return Super::CalcBounds(LocalToWorld); }
