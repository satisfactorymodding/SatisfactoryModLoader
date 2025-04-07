#include "Hologram/FGBlueprintOpenConnectionManager.h"

void FGBlueprintOpenFactoryConnectionManager::GenerateOpenConnections(class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex){  }
void FGBlueprintOpenFactoryConnectionManager::RemapConnectionsForState(OpenConnectionState& State, const TArray<OpenConnection*>& ConnectionsToRemap, const TArray<UFGFactoryConnectionComponent*>& NewConnections){  }
void FGBlueprintOpenFactoryConnectionManager::UpdateOpenConnectionState(OpenConnectionState& State, const FHitResult& hitResult){  }
TArray<FGBlueprintOpenConnectionManager<UFGFactoryConnectionComponent, AFGConveyorBeltHologram>::PotentialConnectionPair> FGBlueprintOpenFactoryConnectionManager::GeneratePotentialConnections(const OpenConnectionState& State, const TSet<UFGFactoryConnectionComponent*>& ClaimedConnections){ return TArray<PotentialConnectionPair>(); }
bool FGBlueprintOpenFactoryConnectionManager::CanDirectlyConnectOpenState(const OpenConnectionState& State) const{ return bool(); }
void FGBlueprintOpenFactoryConnectionManager::ConnectStateDirectly(OpenConnectionState& State){  }
void FGBlueprintOpenPipeConnectionManager::GenerateOpenConnections(class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex){  }
void FGBlueprintOpenPipeConnectionManager::RemapConnectionsForState(OpenConnectionState& State, const TArray<OpenConnection*>& ConnectionsToRemap, const TArray<UFGPipeConnectionComponentBase*>& NewConnections){  }
void FGBlueprintOpenPipeConnectionManager::UpdateOpenConnectionState(OpenConnectionState& State, const FHitResult& hitResult){  }
TArray<FGBlueprintOpenConnectionManager<UFGPipeConnectionComponentBase, AFGPipelineHologram>::PotentialConnectionPair> FGBlueprintOpenPipeConnectionManager::GeneratePotentialConnections(const OpenConnectionState& State, const TSet<UFGPipeConnectionComponentBase*>& ClaimedConnections){ return TArray<PotentialConnectionPair>(); }
bool FGBlueprintOpenPipeConnectionManager::CanDirectlyConnectOpenState(const OpenConnectionState& State) const{ return bool(); }
void FGBlueprintOpenPipeConnectionManager::ConnectStateDirectly(OpenConnectionState& State){  }
void FGBlueprintOpenRailroadConnectionManager::GenerateOpenConnections(class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex){  }
void FGBlueprintOpenRailroadConnectionManager::Construct(TArray<class AFGBuildable*>& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID){ FGBlueprintOpenConnectionManager::Construct(out_ConstructedBridgeBuildables, NetConstructionID); }
void FGBlueprintOpenRailroadConnectionManager::GenerateOpenConnectionStates(){ FGBlueprintOpenConnectionManager::GenerateOpenConnectionStates(); }
void FGBlueprintOpenRailroadConnectionManager::UpdateOpenConnectionState(OpenConnectionState& State, const FHitResult& hitResult){  }
bool FGBlueprintOpenRailroadConnectionManager::IsBridgeHologramInvalid(AFGRailroadTrackHologram* BridgeHologram) const{ return FGBlueprintOpenConnectionManager::IsBridgeHologramInvalid(BridgeHologram); }
TArray<FGBlueprintOpenConnectionManager<UFGRailroadTrackConnectionComponent, AFGRailroadTrackHologram>::PotentialConnectionPair> FGBlueprintOpenRailroadConnectionManager::GeneratePotentialConnections(const OpenConnectionState& State, const TSet<UFGRailroadTrackConnectionComponent*>& ClaimedConnections){ return TArray<PotentialConnectionPair>(); }
void FGBlueprintOpenRailroadConnectionManager::RemapConnectionsForState(OpenConnectionState& State, const TArray<OpenConnection*>& ConnectionsToRemap, const TArray<UFGRailroadTrackConnectionComponent*>& NewConnections){  }
bool FGBlueprintOpenRailroadConnectionManager::CanDirectlyConnectOpenState(const OpenConnectionState& State) const{ return bool(); }
void FGBlueprintOpenRailroadConnectionManager::ConnectStateDirectly(OpenConnectionState& State){  }