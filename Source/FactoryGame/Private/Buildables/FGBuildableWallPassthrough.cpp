#include "Buildables/FGBuildableWallPassthrough.h"
#include "Net/UnrealNetwork.h"

AFGBuildableWallPassthrough::AFGBuildableWallPassthrough() : Super() {
	this->mConnectionClass = nullptr;
	this->mPassthroughConnectionMesh = nullptr;
	this->mConnectionDepthOffset = 0.0;
	this->mConnections[0] = nullptr;
	this->mConnections[1] = nullptr;
	this->mPassthroughDepth = 0.0;
}
void AFGBuildableWallPassthrough::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGBuildableWallPassthrough::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableWallPassthrough, mConnections);
	DOREPLIFETIME(AFGBuildableWallPassthrough, mPassthroughDepth);
}
bool AFGBuildableWallPassthrough::DoesContainLightweightInstances_Native() const{ return Super::DoesContainLightweightInstances_Native(); }
TArray<FInstanceData> AFGBuildableWallPassthrough::GetActorLightweightInstanceData_Implementation() const{ return Super::GetActorLightweightInstanceData_Implementation(); }
void AFGBuildableWallPassthrough::GetClearanceData_Implementation(TArray<FFGClearanceData>& out_data) const{ Super::GetClearanceData_Implementation(out_data); }
void AFGBuildableWallPassthrough::InitializeConnectionMeshClearanceData(FFGClearanceData& data) const{ }
void AFGBuildableWallPassthrough::SetConnection(int32 connectionIndex, class UFGConnectionComponent* connection){ }
bool AFGBuildableWallPassthrough::TrySnap(const FHitResult& hitResult, int32& out_SnapIndex){ return false; }
void AFGBuildableWallPassthrough::DisconnectConnections(){ }
class UFGConnectionComponent* AFGBuildableWallPassthrough::GetConnection(int32 index) const{ return nullptr; }
