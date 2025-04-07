#include "Environment/FGFoliageDestructionData.h"

void UFGFoliageDestructionData::SpawnFoliageDestructionEffects(UObject* WorldContext, UStaticMesh* Mesh, FTransform Transform, bool& bFailed){ }
void UFGFoliageDestructionData::HandleTrunkCrumbleEffect(UObject* WorldContext, UStaticMesh* Mesh, const UFGFoliageDestructionData* DestructionData, const FVector& CrumbleEffectLocation, const FTransform& InstanceTransform){ }
void UFGFoliageDestructionData::HandleLeafSplatterEffect(UObject* WorldContext, UStaticMesh* Mesh, const UFGFoliageDestructionData* DestructionData, const FVector& LeafEffectLocation, const FTransform& InstanceTransform){ }
