// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ReliableMessagingTCPAsyncListener.h"
#include "ReliableMessagingTCPAsyncConnHandler.h"
#include "ReliableMessagingTransportLayer.h"
#include "ReliableMessagingProtocol.h"

// Cap the maximum transmission size to 1MB throughout the TCP implementation of the protocol.
constexpr int32 MaxRMPTransmissionSize = 1024 * 1024;

class UReliableMessagingTCPFactory;

class FReliableMessageProtocolTCPServer: public IReliableMessageTransportServer
{
public:
	virtual ~FReliableMessageProtocolTCPServer() override;
	bool StartListening(UNetDriver* InNetDriver, const UReliableMessagingTCPFactory& Factory);

	int32 GetListenPort() const;
protected:
	virtual void Shutdown() override;
	virtual TArray<TUniquePtr<IReliableMessageTransportConnection>> Tick(float DeltaTime) override;
	
private:
	/**
	 * Determines the externally facing listen port, the one the clients will actually attempt to connect to. This is needed because the server may be behind a NAT
	 * and port remapping may be involved. Since clients will not know what port a server might be listening on, the server must tell them as part of the
	 * initial connection handshake handled through the regular net driver via RPCs. 
	 */
	void ComputeListenPort(const UReliableMessagingTCPFactory& Factory, int32 BoundPort, bool bPortFromCommandLine);

	/**
	 * The port that clients will have to connect to. This may differ from the port the server socket is bound to,
	 * in cast port remapping by the server maintainer
	 */
	int32 ListenPort = INDEX_NONE;
	/** The listener thread that is responsible for intercepting new connections */
	TUniquePtr<FReliableMessagingTCPAsyncListener> ListenerThread = nullptr;
	TWeakObjectPtr<UNetDriver> NetDriver;
	ISocketSubsystem* SocketSubsystem = nullptr;
	TArray<TUniquePtr<FReliableMessagingTCPAsyncConnHandler>> PendingConnectionHandlers;
};


class FReliableMessageProtocolTCPConnection: public IReliableMessageTransportConnection, public FReliableDataTransferProtocolWriter<FReliableMessageProtocolTCPConnection>
{
public:
	virtual ~FReliableMessageProtocolTCPConnection() override;

	FReliableMessageProtocolTCPConnection(UNetConnection* NetConnection, uint16 ListeningPort, FGuid InConnectionId);
	explicit FReliableMessageProtocolTCPConnection(TUniquePtr<FReliableMessagingTCPAsyncConnHandler> &&InConnectionHandler);
	bool WriteData(const uint8* Data, const int32 BufferLength, int32& BytesWritten);

protected:
	virtual FGuid GetConnectionId() const override;
	virtual void EnqueueMessage(uint8 Channel, TArray<uint8>&& Message) override;
	virtual EReliableMessagingConnectionState Tick(float DeltaTime) override;
	virtual void DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher) override;
	virtual void Close() override;

	TUniquePtr<FReliableMessagingTCPAsyncConnHandler> ConnectionHandler;
	FSocket* Socket = nullptr;
	TQueue<RDTProtocol::FMessage> InboundMessages;
};

