// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGVehicleSubsystem.h"
#include "Components/ActorComponent.h"
#include "FGVehicleSubsystemReplicationComponent.generated.h"

class UFGVehiclePathNetwork;
class AFGVehicleSubsystem;
class AFGWheeledVehicle;
struct FGameplayTag;

enum class EVehicleSubsystemMessageId : uint32
{
	InitialPathNetworkReplication = 0x01,
	RemovePathNetwork = 0x02,
	CreatePathNetwork = 0x03,
	UpdatePathNetworkTraversability = 0x04,
};

struct FVehicleSubsystemInitialPathNetworkReplicationMessage
{
	static constexpr EVehicleSubsystemMessageId MessageId = EVehicleSubsystemMessageId::InitialPathNetworkReplication;
	TArray<FVehiclePathNetworkReplicationData> PathNetworks;
	
	friend FArchive& operator<<(FArchive& Ar, FVehicleSubsystemInitialPathNetworkReplicationMessage& Message);
};

struct FVehicleSubsystemRemovePathNetworkMessage
{
	static constexpr EVehicleSubsystemMessageId MessageId = EVehicleSubsystemMessageId::RemovePathNetwork;
	int32 PathNetworkID{INDEX_NONE};
	
	friend FArchive& operator<<(FArchive& Ar, FVehicleSubsystemRemovePathNetworkMessage& Message);
};

struct FVehicleSubsystemCreatePathNetworkMessage
{
	static constexpr EVehicleSubsystemMessageId MessageId = EVehicleSubsystemMessageId::CreatePathNetwork;
	FVehiclePathNetworkReplicationData PathNetwork;
	
	friend FArchive& operator<<(FArchive& Ar, FVehicleSubsystemCreatePathNetworkMessage& Message);
};

struct FVehicleSubsystemUpdatePathNetworkTraversabilityMessage
{
	static constexpr EVehicleSubsystemMessageId MessageId = EVehicleSubsystemMessageId::UpdatePathNetworkTraversability;
	FVehiclePathNetworkTraversabilityReplicationData UpdateData;
	
	friend FArchive& operator<<(FArchive& Ar, FVehicleSubsystemUpdatePathNetworkTraversabilityMessage& Message);
};

UCLASS(MinimalAPI, NotBlueprintable, Within = PlayerController)
class UFGVehicleSubsystemReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent interface

	void NotifyPathNetworkRemoved(int32 PathNetworkID);
	void NotifyPathNetworkCreated(const FVehiclePathNetworkReplicationData& ReplicationData);
	void NotifyPathNetworkTraversabilityChanged(const FVehiclePathNetworkTraversabilityReplicationData& ReplicationData);
protected:
	/** Called to initialize on the client once the blueprint subsystem is available */
	void InitializeAsClient();
	/** Sends the initial replication message to the player */
	void SendInitialReplicationMessage();
	
	/** Handles a reliable message */
	void HandleRawMessage(FGameplayTag InTag, TArray<uint8>&& InMessageData) const;
	/** Sends a a reliable message */
	void SendRawMessage(EVehicleSubsystemMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	void ReceiveInitialPathNetworkReplication(const FVehicleSubsystemInitialPathNetworkReplicationMessage& Message) const;
	void ReceivePathNetworkRemoval(const FVehicleSubsystemRemovePathNetworkMessage& Message) const;
	void ReceivePathNetworkCreation(const FVehicleSubsystemCreatePathNetworkMessage& Message) const;
	void ReceivePathNetworkTraversabilityUpdate(const FVehicleSubsystemUpdatePathNetworkTraversabilityMessage& Message) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendMessage(T& Message)
	{
		SendRawMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	TObjectPtr<AFGVehicleSubsystem> mVehicleSubsystem;
};
