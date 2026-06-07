#include "Resources/FGResourceNodeManager.h"

void AFGResourceNodeUtilities::PerformNodeToMeshAssignment(){ }
void AFGResourceNodeUtilities::CreateDefaultNodeListFromWorld(){ }
AFGResourceNodeManager* AFGResourceNodeManager::Get(UWorld* world){ return nullptr; }
void AFGResourceNodeManager::CreateListOfMeshesFromWorld(const UWorld* world, TArray<AFGNodeMeshActor*>& out_meshActors){ }
void AFGResourceNodeManager::PairNodesWithMeshes(const TArray<AFGResourceNodeBase*>& nodeArray, const TArray<AFGNodeMeshActor*>& meshArray){ }
void AFGResourceNodeManager::PairDepositsWithNodes(const UWorld* world, const TArray<AFGResourceNodeBase*>& nodeArray){ }
void AFGResourceNodeManager::PairDestructiblesWithNodes(const UWorld* world, const TArray<AFGResourceNodeBase*>& nodeArray){ }
FNodeMeshOverrides* AFGResourceNodeManager::GetNodeMeshOverrides(TSubclassOf<UFGResourceDescriptor> resourceDescriptor, ENodeMeshType nodeMeshType){ return nullptr; }
void AFGResourceNodeManager::ApplyRandomizationSettings(ENodeRandomizationMode randomizationMode, ENodePuritySettings puritySettings, const int32 seed){ }
void AFGResourceNodeManager::CheckForcedRandomizationSettings(AFGGameState* gameState){ }
void AFGResourceNodeManager::TryPairNodeWithMesh(AFGNodeMeshActor* mesh, const TArray<AFGResourceNodeBase*>& nodeArray){ }
AFGResourceNodeBase* AFGResourceNodeManager::GetClosestNode(const FVector& location, float cutoff, EResourceNodeType nodeType, const TArray<AFGResourceNodeBase*>& nodeArray){ return nullptr; }
void AFGResourceNodeManager::SetNewSeedInternal(const int32 newSeed){ }
TSet<TSubclassOf<UFGResourceDescriptor>> AFGResourceNodeManager::GetResourceDescriptors(const FGameplayTag& gameplayTag){ return TSet<TSubclassOf<UFGResourceDescriptor>>(); }
FGameplayTag AFGResourceNodeManager::GetResourceDescriptorTag(ENodeRandomizationMode randomizationMode){ return FGameplayTag(); }
uint32 AFGResourceNodeManager::PurityToThroughput(EResourcePurity purity){ return uint32(); }
EResourcePurity AFGResourceNodeManager::ThroughputToPurity(int32 throughput){ return EResourcePurity(); }
float AFGResourceNodeManager::GetDistributionMultiplier(ENodeRandomizationMode randomizationMode){ return float(); }
void AFGResourceNodeManager::DistributeThroughput(AFGResourceNodeFrackingCore* frackingCore, int32 totalThroughput) const{ }
uint32 AFGResourceNodeManager::GetThroughput(AFGResourceNodeFrackingCore* frackingCore) const{ return uint32(); }
void AFGResourceNodeManager::CreateDefaultNodeListFromWorld(const UWorld* world){ }
void AFGResourceNodeManager::ModifyNodeDistribution(TArray<FResourceNodeInfo>& nodePool, const TSet<TSubclassOf<UFGResourceDescriptor>>& resourcesSubset, float resourcesSubsetMultiplier){ }
EResourcePurity AFGResourceNodeManager::GetPurityOverride(EResourcePurity purity, ENodePuritySettings puritySettings) const{ return EResourcePurity(); }
void AFGResourceNodeManager::Shuffle(TArray<FResourceNodeInfo>& nodePool){ }
