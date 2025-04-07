// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ReliableMessagingTransportLayer.h"
#include "SocketSubsystem.h"
#include "steam/isteamnetworkingutils.h"

class FSteamSocketsSubsystem;
/**
 * 
 */
class FReliableMessagingSteamConnection
	: public IReliableMessageTransportConnection
	, public FReliableDataTransferProtocolReader<FReliableMessagingSteamConnection>
	, public FReliableDataTransferProtocolWriter<FReliableMessagingSteamConnection>
{
public:

	FReliableMessagingSteamConnection(UNetConnection* NetConnection, FGuid InConnectionId);
	FReliableMessagingSteamConnection(HSteamNetConnection InConnectionHandle, FSteamSocketsSubsystem* InSocketSubsystem);
	
	virtual ~FReliableMessagingSteamConnection() override;
	
	virtual void EnqueueMessage(uint8 Channel, TArray<uint8>&& Message) override;
	virtual FGuid GetConnectionId() const override;
	[[nodiscard]] virtual EReliableMessagingConnectionState Tick(float DeltaTime) override;
	virtual void DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher) override;
	virtual void Close() override;

	bool HasReceivedConnectionId() const;

	void HandleConnectionIdReceived(FGuid InConnectionId);
	void HandleMessageReceived(RDTProtocol::FMessage&& InMessage);
	bool ReadData(uint8* Buffer, const int32 BufferLength, int32& BytesRead);
	bool WriteData(const uint8* Data, const int32 BufferLength, int32& BytesWritten);
	void CloseConnection();
	
private:
	void OnSteamConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* Callback);
	// FUniqueSocket Socket;
	FGuid ConnectionId;

	bool bHasReceivedConnectionId = false;

	TArray<RDTProtocol::FMessage> IncomingMessages;
	HSteamNetConnection ConnectionHandle;
	TArray<uint8> ReadCache;
	int32 ReadCachePos = 0;
	EReliableMessagingConnectionState ConnectionState = EReliableMessagingConnectionState::Connecting;
	FDelegateHandle SteamConnectionStatusChangedHandle;
	FSteamSocketsSubsystem* SocketSubsystem = nullptr;

};
