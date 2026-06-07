#include "WheeledVehicles/FGVehicleSubsystem.h"

FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkNodeData& NodeData){ return Ar; }
FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkSegmentData& SegmentData){ return Ar; }
FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkReplicationData& ReplicationData){ return Ar; }
FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkTraversabilityReplicationData& ReplicationData){ return Ar; }
void UFGVehiclePathNetwork::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PostLoadGame_Implementation(saveVersion, gameVersion); }
FVehiclePathNetworkNodeData UFGVehiclePathNetwork::GetPathNodeAtIndex(int32 pathNodeIndex) const{ return FVehiclePathNetworkNodeData(); }
FVehiclePathNetworkSegmentData UFGVehiclePathNetwork::GetPathSegmentAtIndex(int32 pathSegmentIndex) const{ return FVehiclePathNetworkSegmentData(); }
int32 UFGVehiclePathNetwork::FindPathNodeIndexByGuid(const FGuid& pathNodeGuid) const{ return int32(); }
int32 UFGVehiclePathNetwork::FindPathIndexBetweenPathNodes(const int32 fromNodeIndex, const int32 toNodeIndex) const{ return int32(); }
bool UFGVehiclePathNetwork::CanVehicleTraverseSegment(const FVehiclePathNetworkSegmentData& segmentData, const UFGVehiclePathPreset* vehiclePathPreset) const{ return false; }
float UFGVehiclePathNetwork::GetVehicleFuelConsumptionForSegment(const FVehiclePathNetworkSegmentData& segmentData, const TSubclassOf<AFGWheeledVehicle>& vehicleType) const{ return float(); }
bool UFGVehiclePathNetwork::FindVehiclePath(const FGuid& fromNodeGuid, const FGuid& toNodeGuid, const UFGVehiclePathPreset* vehicleType, TArray<FGuid>& out_vehiclePath) const{ return false; }
void UFGVehiclePathNetwork::PopulateNetworkStations(TArray<AFGDockingStationIdentifier*>& out_dockingStations) const{ }
void UFGVehiclePathNetwork::PopulateNetworkVehicles(TArray<AFGWheeledVehicleIdentifier*>& out_vehicles) const{ }
bool UFGVehiclePathNetwork::IsNetworkEmptyOnServer() const{ return false; }
void UFGVehiclePathNetwork::InitializeNewNetwork(int32 newNetworkID, const TArray<AFGVehiclePathNode*>& newNetworkElements){ }
void UFGVehiclePathNetwork::InitializeFromReplicationData(const FVehiclePathNetworkReplicationData& replicationData){ }
bool UFGVehiclePathNetwork::UpdatePathTraversabilityDirectly(const FGuid& fromNode, const FGuid& toNode, uint64 newTraversabilityMask, const TArray<float>& vehicleSegmentVirtualLength){ return false; }
void UFGVehiclePathNetwork::ResetNetworkID(){ }
void UFGVehiclePathNetwork::RemoveNetworkElement(AFGVehiclePathNode* networkElement){ }
void UFGVehiclePathNetwork::BulkRemoveNetworkElements(const TSet<AFGVehiclePathNode*>& networkElements){ }
bool UFGVehiclePathNetwork::UpdateNetworkPathTraversability(const AFGVehiclePathSegment* networkPathSegment, FVehiclePathNetworkTraversabilityReplicationData& out_traversabilityUpdateData){ return false; }
FVehiclePathNetworkReplicationData UFGVehiclePathNetwork::ToReplicationData() const{ return FVehiclePathNetworkReplicationData(); }
void UFGVehiclePathNetwork::RegenerateCachedDataOnServer(){ }
void UFGVehiclePathNetwork::RegenerateNavigationGraph(){ }
uint64 UFGVehiclePathNetwork::CalculateTraversabilityMask(const AFGVehiclePathSegment* networkPathSegment, TArray<float>& out_vehicleSegmentVirtualLength) const{ return uint64(); }
void FVehicleTriggerBoxSemantics::SetElementId(FOctree& Octree, const FVehicleTriggerBoxOctreeElement& Element, FOctreeElementId2 OctreeElementID){ }
AFGVehicleSubsystem::AFGVehicleSubsystem() : Super() {
	this->mDefaultVehiclePathNodeClass = nullptr;
	this->mLegacyTargetNodeClass = nullptr;
	this->mMaxVehicleProximityChecksPerFrame = 10;
	this->mConvertedLegacyPaths = false;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = true;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
}
void AFGVehicleSubsystem::BeginPlay(){ Super::BeginPlay(); }
void AFGVehicleSubsystem::Tick(float dt){ Super::Tick(dt); }
void AFGVehicleSubsystem::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ IFGSaveInterface::PostLoadGame_Implementation(saveVersion, gameVersion); }
AFGVehicleSubsystem* AFGVehicleSubsystem::Get(const UWorld* world){ return nullptr; }
AFGVehicleSubsystem* AFGVehicleSubsystem::Get(const UObject* worldContext){ return nullptr; }
AFGVehiclePathNode* AFGVehicleSubsystem::CreateNewVehiclePathNode(const FVector& pointLocation, const AFGBuildable* sourceBuildable) const{ return nullptr; }
UFGVehiclePathNetwork* AFGVehicleSubsystem::FindNetworkByID(int32 networkID) const{ return nullptr; }
UFGVehiclePathNetwork* AFGVehicleSubsystem::FindNetworkByPathNodeGuid(const FGuid& pathNodeGuid) const{ return nullptr; }
AFGVehiclePathNode* AFGVehicleSubsystem::FindReplicatedPathNodeByGuid(const FGuid& pathNodeGuid) const{ return nullptr; }
AFGDockingStationIdentifier* AFGVehicleSubsystem::FindDockingStationIdentifierForPathNodeGuid(const FGuid& pathNodeGuid) const{ return nullptr; }
void AFGVehicleSubsystem::InvalidateVehiclePathsInVolume(const FBox& invalidationVolume){ }
void AFGVehicleSubsystem::InvalidateVehiclePathsInVolumeList(const TArray<FBox>& invalidationVolumeList){ }
void AFGVehicleSubsystem::RequestVehiclePathVisualization(const TSharedPtr<FVehiclePathVisualizationHandle>& pathVisualizationInfo){ }
void AFGVehicleSubsystem::RemoveVehiclePathVisualization(const TSharedPtr<FVehiclePathVisualizationHandle>& pathVisualizationInfo){ }
void AFGVehicleSubsystem::RequestPathSegmentVisualizationUpdate(AFGVehiclePathSegment* pathSegment){ }
void AFGVehicleSubsystem::RequestPathNodeVisualizationUpdate(AFGStandaloneVehiclePathNode* pathNode){ }
void AFGVehicleSubsystem::RequestFullVisualizationUpdate(){ }
void AFGVehicleSubsystem::NotifyNodeTopologyChanged(AFGVehiclePathNode* networkElement){ }
void AFGVehicleSubsystem::NotifyPathTraversabilityChanged(const AFGVehiclePathSegment* networkSegment){ }
void AFGVehicleSubsystem::AddPathSegment(AFGVehiclePathSegment* pathSegment){ }
void AFGVehicleSubsystem::RemovePathSegment(AFGVehiclePathSegment* pathSegment){ }
void AFGVehicleSubsystem::InvalidateVehiclePathSegment(AFGVehiclePathSegment* pathSegment){ }
void AFGVehicleSubsystem::AddPathNode(AFGVehiclePathNode* pathNode){ }
void AFGVehicleSubsystem::RemovePathNode(AFGVehiclePathNode* pathNode){ }
void AFGVehicleSubsystem::AddDockingStation(AFGDockingStationIdentifier* stationIdentifier){ }
void AFGVehicleSubsystem::RemoveDockingStation(AFGDockingStationIdentifier* stationIdentifier){ }
void AFGVehicleSubsystem::AddVehicle(AFGWheeledVehicleIdentifier* vehicleIdentifier){ }
void AFGVehicleSubsystem::RemoveVehicle(AFGWheeledVehicleIdentifier* vehicleIdentifier){ }
void AFGVehicleSubsystem::AddReplicationComponent(UFGVehicleSubsystemReplicationComponent* replicationComponent){ }
void AFGVehicleSubsystem::RemoveReplicationComponent(UFGVehicleSubsystemReplicationComponent* replicationComponent){ }
void AFGVehicleSubsystem::AddGenericVehicle(AFGVehicle* vehicle){ }
void AFGVehicleSubsystem::RemoveGenericVehicle(AFGVehicle* vehicle){ }
void AFGVehicleSubsystem::AddVehicleTriggerBox(UFGVehicleDetectionComponent* vehicleTriggerBox){ }
void AFGVehicleSubsystem::RemoveVehicleTriggerBox(UFGVehicleDetectionComponent* vehicleTriggerBox){ }
void AFGVehicleSubsystem::PopulateInitialNetworkReplicationData(TArray<FVehiclePathNetworkReplicationData>& out_replicationData) const{ }
void AFGVehicleSubsystem::InitializeNetworksFromReplicationData(const TArray<FVehiclePathNetworkReplicationData>& replicationData){ }
void AFGVehicleSubsystem::RemoveNetworkFromReplicationData(int32 networkID){ }
void AFGVehicleSubsystem::AddNetworkFromReplicationData(const FVehiclePathNetworkReplicationData& replicationData){ }
void AFGVehicleSubsystem::UpdateNetworkTraversabilityFromReplicationData(const FVehiclePathNetworkTraversabilityReplicationData& replicationData){ }
TSubclassOf<AFGVehiclePathSegment> AFGVehicleSubsystem::FindPathTypeForLegacyPath(const UFGVehiclePathPreset* pathPreset) const{ return TSubclassOf<AFGVehiclePathSegment>(); }
TArray<AFGVehiclePathNode*> AFGVehicleSubsystem::ExplodeNode(AFGVehiclePathNode* seedElement, TSet<AFGVehiclePathNode*>& exploredNodeSet){ return TArray<AFGVehiclePathNode*>(); }
void AFGVehicleSubsystem::AddNetworkElement(AFGVehiclePathNode* networkElement){ }
void AFGVehicleSubsystem::RemoveNetworkElement(AFGVehiclePathNode* networkElement) const{ }
void AFGVehicleSubsystem::CleanNetworkIDOnElements(const TArray<AFGVehiclePathNode*>& networkElements){ }
void AFGVehicleSubsystem::CreateNewNetworkOnServer(const TArray<AFGVehiclePathNode*>& newNetworkElements){ }
void AFGVehicleSubsystem::RemoveNetworkOnServer(UFGVehiclePathNetwork* network){ }
void AFGVehicleSubsystem::RebuildDirtyNetworks(){ }
void AFGVehicleSubsystem::UpdateVehiclePathVisualization(){ }
void AFGVehicleSubsystem::RebuildInvalidatedPathSegments(){ }
void AFGVehicleSubsystem::UpdateVehiclePlayerProximity(){ }
void AFGVehicleSubsystem::TickPendingVehicleVisualizationUpdates(){ }
void AFGVehicleSubsystem::TickVehicleAutopilot(float deltaTime){ }
