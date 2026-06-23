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
	void SendTaggedMessage(FGameplayTag Tag, TArray<uint8> InPayload);

	const FGuid& GetConnectionId() const;

	static UReliableMessagingPlayerComponent* GetFromPlayer(const APlayerController* PlayerController);

	DECLARE_DELEGATE_TwoParams(FOnBulkDataReplicationPayloadReceived, FGameplayTag, TArray<uint8>&&);
	void RegisterTaggedMessageHandler(FGameplayTag Tag, FOnBulkDataReplicationPayloadReceived Handler);

	void SetTransportLayerConnection(TUniquePtr<IReliableMessageTransportConnection> InConnection);
	void TickConnection(float DeltaTime);
	APlayerController* GetOwningPlayerController() const;
	FDateTime GetHandshakeBeginTime() const;
	/** Disconnects the player when for example an underlying socket connection is broken. */
	void TriggerDC();

protected:
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent interface

	/**
	 * This function is called by the client to initiate a connection to the server. It's essentially the kick-starter for the connection.
	 */
	UFUNCTION(Server, Reliable)
	void Server_AdvertiseNewConnection(const FGuid& ConnectionIdentity);

	/**
	 * The server then immediately calls this function. 
	 */
	UFUNCTION(Client, Reliable)
	void Client_AcknowledgeConnectionAdvertisement();

	/**
	 * Which in turn calls this function on the server to request the connection to be established.
	 * This flow is required so we only really try to connect once the Unreal connection is fully established and we know this because we had a successful RPC roundtrip.
	 */
	UFUNCTION(Server, Reliable)
	void Server_RequestInitiateConnection();
	
	/**
	 * The server sends the client the port it should connect to. We already know the address from the UNetConnection and we only need the port.
	 */
	UFUNCTION(Client, Reliable)
	void Client_InitiateConnection(TSubclassOf<UReliableMessagingTransportLayerFactory> FactoryClass, const TArray<uint8>& InConnectionData);
private:
	FGuid ConnectionId;

	TUniquePtr<IReliableMessageTransportConnection> TransportLayerConnection;

	struct FTaggedPayload
	{
		FTaggedPayload(FGameplayTag InTag, TArray<uint8>&& InPayload)
			: Tag(InTag)
			, Payload(MoveTemp(InPayload))
		{
		}
		
		FGameplayTag Tag;
		TArray<uint8> Payload;
	};
	
	/** A bunch of payloads that are waiting to be sent. This is used when attempts to send payloads are made while the connection is not yet established. */
	TArray<FTaggedPayload> PayloadsPendingConnection;

	TMap<FGameplayTag, FOnBulkDataReplicationPayloadReceived> TaggedMessageHandlers;
	TMap<FGameplayTag, TArray<TArray<uint8>>> InboundMessagesWaitingForHandler;
	FDateTime HandshakeBeginTime;
};

