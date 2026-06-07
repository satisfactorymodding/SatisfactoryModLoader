#include "Hologram/BlueprintOpenVehiclePathConnectionManager.h"

void FOpenVehiclePathConnection::SerializeConnectionData(FArchive& ar, const AFGBlueprintHologram* ownerHologram){ }
void FBlueprintOpenVehiclePathConnectionManager::Initialize(TArray<AFGBuildable*> buildables){ }
void FBlueprintOpenVehiclePathConnectionManager::HandleBuildableConnectionRemapping(AFGBuildable* Buildable, int32 BlueprintBuildableIndex){ }
void FBlueprintOpenVehiclePathConnectionManager::RegisterNearbyActor(AActor* Actor){ }
void FBlueprintOpenVehiclePathConnectionManager::UnregisterNearbyActor(AActor* Actor){ }
void FBlueprintOpenVehiclePathConnectionManager::ResetAutomaticConnections(){ }
bool FBlueprintOpenVehiclePathConnectionManager::CanSnapConnectionStates() const{ return false; }
bool FBlueprintOpenVehiclePathConnectionManager::AttemptConnectionStateSnap(){ return false; }
void FBlueprintOpenVehiclePathConnectionManager::Construct(TArray<AFGBuildable*>& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID){ }
void FBlueprintOpenVehiclePathConnectionManager::UpdateAutomaticConnections(const FHitResult& hitResult, bool& out_PlaySnapEffects){ }
void FBlueprintOpenVehiclePathConnectionManager::SerializeConstructMessage(FArchive& ar, FNetConstructionID id){ }
void FBlueprintOpenVehiclePathConnectionManager::PostConstructMessageDeserialization(){ }
TArray<FPotentialVehiclePathConnectionPair> FBlueprintOpenVehiclePathConnectionManager::GeneratePotentialConnections(FOpenVehiclePathConnection& vehiclePathConnection, const TSet<AFGVehiclePathNode*>& claimedConnections){ return TArray<FPotentialVehiclePathConnectionPair>(); }
bool FBlueprintOpenVehiclePathConnectionManager::CanDirectlyConnectOpenState(const FOpenVehiclePathConnection& vehiclePathConnection) const{ return false; }
void FBlueprintOpenVehiclePathConnectionManager::ConnectStateDirectly(const FOpenVehiclePathConnection& vehiclePathConnection){ }
void FBlueprintOpenVehiclePathConnectionManager::UpdateOpenConnectionState(FOpenVehiclePathConnection& vehiclePathConnection){ }
void FBlueprintOpenVehiclePathConnectionManager::RemapConnectionsForState(const FOpenVehiclePathConnection& vehiclePathConnection){ }
void FBlueprintOpenVehiclePathConnectionManager::CreateConnectionVisualizationMesh(FOpenVehiclePathConnection& vehiclePathConnection) const{ }
void FBlueprintOpenVehiclePathConnectionManager::UpdateConnectionVisualizationMesh(const FOpenVehiclePathConnection& vehiclePathConnection){ }
