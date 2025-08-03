// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGConveyorChainSubsystemReplicationComponent.generated.h"

class UFGItemDescriptor;
class AFGConveyorChainSubsystem;

enum class EConveyorChainSubsystemMessageId : uint32
{
	InitialReplication = 0x01,
};

struct FConveyorChainSubsystemInitialReplicationMessage
{
	static constexpr EConveyorChainSubsystemMessageId MessageId = EConveyorChainSubsystemMessageId::InitialReplication;
	TArray<TSubclassOf<UFGItemDescriptor>> ItemDescriptorLookup;
	
	friend FArchive& operator<<(FArchive& Ar, FConveyorChainSubsystemInitialReplicationMessage& Message);
};

UCLASS(NotBlueprintable, Within = PlayerController)
class FACTORYGAME_API UFGConveyorChainSubsystemReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	// End UActorComponent interface
protected:
	/** Called to initialize on the client once the conveyor chain subsystem is available */
	void InitializeAsClient();
	/** Sends initial replication data to the client */
	void SendInitialReplicationData();
	
	/** Handles a reliable message */
	void HandleRawMessage(TArray<uint8>&& InMessageData) const;
	/** Sends a a reliable message */
	void SendRawMessage(EConveyorChainSubsystemMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;

	/** Handles Initial Replication Data for Conveyor Chain Subsystem */
	void ReceiveInitialReplicationData(const FConveyorChainSubsystemInitialReplicationMessage& Message) const;
	
	/** Sends a schematic manager message to the player */
	template<typename T>
	void SendMessage(T& Message)
	{
		SendRawMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
	}

	UPROPERTY()
	AFGConveyorChainSubsystem* mConveyorChainSubsystem;
};
