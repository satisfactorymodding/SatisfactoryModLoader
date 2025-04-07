// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Containers/Queue.h"

#include "ReliableMessagingPlayerComponent.generated.h"

class UReliableMessagingTransportLayerFactory;
class UReliableDataTransferNetConnection;
class FReliableMessagingTCPAsyncConnHandler;
class IReliableMessageTransportConnection;

UCLASS(Within=PlayerController)
class RELIABLEMESSAGING_API UReliableMessagingPlayerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UReliableMessagingPlayerComponent();
	/**
	 * Sends a single payload. If called on the client, the payload is sent to the server. If called on the server, the payload is sent to the client.
	 */
	void SendMessage(int32 Channel, TArray<uint8> InPayload);

	const FGuid& GetConnectionId() const;

	static UReliableMessagingPlayerComponent* GetFromPlayer(const APlayerController* PlayerController);

	DECLARE_DELEGATE_OneParam(FOnBulkDataReplicationPayloadReceived, TArray<uint8>&&);
	void RegisterMessageHandler(int32 Channel, FOnBulkDataReplicationPayloadReceived Handler);

	void SetTransportLayerConnection(TUniquePtr<IReliableMessageTransportConnection> InConnection);
	void TickConnection(float DeltaTime);
protected:
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent interface

	APlayerController* GetOwningPlayerController() const;

	/**
	 * This function is called by the client to initiate a connection to the server. It's essentially the kick-starter for the connection.
	 */
	UFUNCTION(Server, Reliable)
	void Server_AdvertiseNewConnection(const FGuid& ConnectionIdentity);

	/**
	 * The server sends the client the port it should connect to. We already know the address from the UNetConnection and we only need the port.
	 */
	UFUNCTION(Client, Reliable)
	void Client_InitiateConnection(TSubclassOf<UReliableMessagingTransportLayerFactory> FactoryClass, const TArray<uint8>& InConnectionData);
private:
	/** Disconnects the player when for example an underlying socket connection is broken. */
	void TriggerDC();
	
	FGuid ConnectionId;

	TUniquePtr<IReliableMessageTransportConnection> TransportLayerConnection;

	struct FTaggedPayload
	{
		FTaggedPayload(int32 InChannel, TArray<uint8>&& InPayload)
			: Channel(InChannel)
			, Payload(MoveTemp(InPayload))
		{
		}
		
		int32 Channel;
		TArray<uint8> Payload;
	};
	
	/** A bunch of payloads that are waiting to be sent. This is used when attempts to send payloads are made while the connection is not yet established. */
	TArray<FTaggedPayload> PayloadsPendingConnection;

	TMap<int32, FOnBulkDataReplicationPayloadReceived> MessageHandlers;
	TArray<TQueue<TArray<uint8>>> InboundMessagesWaitingForHandler;
};

