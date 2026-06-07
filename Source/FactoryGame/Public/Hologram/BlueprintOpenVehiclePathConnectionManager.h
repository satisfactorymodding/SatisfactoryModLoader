// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBlueprintOpenConnectionManager.h"

class AFGVehiclePathSegmentHologram;
class AFGVehiclePathNode;
class AFGVehiclePathSegment;

struct FOpenVehiclePathConnection
{
	// Data initialized when the connection is initialized from the blueprint
	int32 BlueprintBuildableIndex{INDEX_NONE};
	AFGVehiclePathNode* TemplateConnectionNode{};
	USceneComponent* ConnectionNodeRootComponent{};
	UStaticMeshComponent* ConnectionVisualizationMeshComponent{};
	FVector ConnectionNodeForwardDirection{ForceInit};
	AFGVehiclePathNode* ConstructedConnectionNode{};
	bool bIsOpenArrivingConnection{false};

	// Runtime data updated during the connection snapping
	AFGVehiclePathNode* TargetConnectionNode{};
	AFGVehiclePathNode* PreviousTargetConnectionNode{};
	AFGVehiclePathSegmentHologram* BridgeHologram{};
	bool bHasSnappedTargetConnection{false};
	bool bCanDirectlyConnect{false};
	bool bIsValid{false};
	bool bPreviousIsValid{false};
	
	void SerializeConnectionData( FArchive& ar, const AFGBlueprintHologram* ownerHologram );
};

struct FNearbyVehiclePathConnection
{
	AFGVehiclePathNode* ConnectionNode{};
	bool bIsOpenArrivingConnection{false};
	TArray<const AFGVehiclePathSegment*> OwningPathSegments;
};

struct FPotentialVehiclePathConnectionPair
{
	FOpenVehiclePathConnection* OpenConnectionNode{};
	AFGVehiclePathNode* TargetConnectionNode{};
	float Score{0.0f};
};

class FACTORYGAME_API FBlueprintOpenVehiclePathConnectionManager final : public FGBlueprintOpenConnectionManagerBase
{
public:
	explicit FBlueprintOpenVehiclePathConnectionManager( AFGBlueprintHologram* BlueprintHologram ) : FGBlueprintOpenConnectionManagerBase( BlueprintHologram )
	{
	}

	// Begin FGBlueprintOpenConnectionManagerBase interface
	virtual void Initialize( TArray<AFGBuildable*> buildables ) override;
	virtual void HandleBuildableConnectionRemapping( AFGBuildable* Buildable, int32 BlueprintBuildableIndex ) override;
	virtual void RegisterNearbyActor( AActor* Actor ) override;
	virtual void UnregisterNearbyActor( AActor* Actor ) override;
	virtual void ResetAutomaticConnections() override;
	virtual bool CanSnapConnectionStates() const override;
	virtual bool AttemptConnectionStateSnap() override;
	virtual void Construct( TArray<AFGBuildable*>& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID ) override;
	virtual void UpdateAutomaticConnections( const FHitResult& hitResult, bool& out_PlaySnapEffects ) override;
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void PostConstructMessageDeserialization() override;
	// End FGBlueprintOpenConnectionManagerBase interface
protected:
	TArray<FPotentialVehiclePathConnectionPair> GeneratePotentialConnections( FOpenVehiclePathConnection& vehiclePathConnection, const TSet<AFGVehiclePathNode*>& claimedConnections );
	bool CanDirectlyConnectOpenState( const FOpenVehiclePathConnection& vehiclePathConnection ) const;
	void ConnectStateDirectly( const FOpenVehiclePathConnection& vehiclePathConnection );
	void UpdateOpenConnectionState( FOpenVehiclePathConnection& vehiclePathConnection );
	void RemapConnectionsForState( const FOpenVehiclePathConnection& vehiclePathConnection );
	void CreateConnectionVisualizationMesh( FOpenVehiclePathConnection& vehiclePathConnection ) const;
	void UpdateConnectionVisualizationMesh( const FOpenVehiclePathConnection& vehiclePathConnection );

	TArray<FOpenVehiclePathConnection> mOpenConnections;
	TArray<FNearbyVehiclePathConnection> mNearbyConnections;	
};
