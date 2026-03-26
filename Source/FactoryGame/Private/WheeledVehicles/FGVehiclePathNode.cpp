#include "WheeledVehicles/FGVehiclePathNode.h"
#include "Net/UnrealNetwork.h"

AFGVehiclePathNode::AFGVehiclePathNode() : Super() {
	this->mPathNetworkID = -1;
	this->mAllowColoring = false;
	this->mAllowPatterning = false;
	this->mSkipBuildEffect = true;
	this->mShouldApplyCustomizationData = false;
}
void AFGVehiclePathNode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGVehiclePathNode, mPathNodeGUID);
	DOREPLIFETIME(AFGVehiclePathNode, mPathNetworkID);
	DOREPLIFETIME(AFGVehiclePathNode, mArrivingConnections);
	DOREPLIFETIME(AFGVehiclePathNode, mLeavingConnections);
}
void AFGVehiclePathNode::BeginPlay(){ Super::BeginPlay(); }
void AFGVehiclePathNode::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGVehiclePathNode::PostSerializedFromBlueprint(bool isBlueprintWorld){ Super::PostSerializedFromBlueprint(isBlueprintWorld); }
void AFGVehiclePathNode::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ Super::PostLoadGame_Implementation(saveVersion, gameVersion); }
void AFGVehiclePathNode::GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const{ Super::GetChildDismantleActors_Implementation(out_ChildDismantleActors); }
bool AFGVehiclePathNode::HasConnectionArrivingToNode(const AFGVehiclePathNode* endNode) const{ return false; }
TOptional<FVector> AFGVehiclePathNode::GetNodeForcedForwardDirection() const{ return TOptional<FVector>(); }
void AFGVehiclePathNode::GetConnectedNodes(TArray<AFGVehiclePathNode*>& out_connectedNodes) const{ }
AFGVehiclePathSegment* AFGVehiclePathNode::FindConnectionArrivingToNode(const AFGVehiclePathNode* endNode) const{ return nullptr; }
void AFGVehiclePathNode::MoveConnectionsToNode(AFGVehiclePathNode* newPathNode){ }
void AFGVehiclePathNode::AddArrivingConnection(AFGVehiclePathSegment* pathSegment){ }
void AFGVehiclePathNode::AddLeavingConnection(AFGVehiclePathSegment* pathSegment){ }
void AFGVehiclePathNode::RemoveArrivingConnection(AFGVehiclePathSegment* pathSegment, bool bAllowNodeCleanup){ }
void AFGVehiclePathNode::RemoveLeavingConnection(AFGVehiclePathSegment* pathSegment, bool bAllowNodeCleanup){ }
void AFGVehiclePathNode::SetPathNetworkID(int32 newPathNetworkID){ }
void AFGVehiclePathNode::OnNodeConnectionsChanged(){ }
void AFGVehiclePathNode::OnVehicleSubsystemValid(){ }
void AFGVehiclePathNode::OnRep_NodeConnections(){ }
void AFGVehiclePathNode::UpdateOrCleanupConnectionNode(bool bAllowNodeCleanup){ }
