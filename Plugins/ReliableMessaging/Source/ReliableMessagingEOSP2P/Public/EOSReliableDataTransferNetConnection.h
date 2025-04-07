// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ReliableDataTransferNetConnection.h"
#include "ReliableMessagingTransportLayer.h"
#include "SocketEOS.h"

class FSocketEOS;
class FInternetAddrEOS;
class FReliableMessagingServerEOS;

struct FChunkHeader 
{
	int64 MessageId;
	int32 ChunkId;
	int32 TotalChunks;
	int32 ChunkSize;
};

class FEOSReliableDataTransferNetConnection
	: public IReliableMessageTransportConnection
	, public FReliableDataTransferProtocolReader<FEOSReliableDataTransferNetConnection>
	, public FReliableDataTransferProtocolWriter<FEOSReliableDataTransferNetConnection>
{
public:
	virtual ~FEOSReliableDataTransferNetConnection() override;

	explicit FEOSReliableDataTransferNetConnection(TSharedRef<const FInternetAddrEOS> InAddr);
	FEOSReliableDataTransferNetConnection(UNetConnection* Connection, FGuid ConnectionId);
	
	const FInternetAddrEOS& GetAddress() const;
	void ReceiveBytes(const uint8* InData, int32 InLength);
	void InitServerSide(FSocketSubsystemEOS* InSocketSubsystem, FReliableMessagingServerEOS* InServer, TSharedPtr<const FInternetAddrEOS> InAddress, TSharedPtr<FSocketEOS> InSocket);

	// Begin IReliableMessageTransportConnection interface
	virtual FGuid GetConnectionId() const override;
	virtual void EnqueueMessage(uint8 Channel, TArray<uint8>&& Message) override;
	virtual EReliableMessagingConnectionState Tick(float DeltaTime) override;
	virtual void DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher) override;
	virtual void Close() override;
	// End IReliableMessageTransportConnection interface

	TSharedPtr<const FInternetAddr> GetClientAddress() const;
	bool HasReceivedConnectionId() const { return bHasReceivedConnectionId; }

	void HandleConnectionIdReceived(FGuid InConnectionId);
	void HandleMessageReceived(RDTProtocol::FMessage&& InMessage);
	bool ReadData(uint8* Buffer, const int32 InBufferLength, int32& BytesRead);
	bool WriteData(const uint8* Data, const int32 InBufferLength, int32& BytesWritten);
	void CloseConnection();
	EReliableMessagingConnectionState GetConnectionState() const;
protected:

	// Begin UReliableDataTransferNetConnection interface
	bool Connect(UNetConnection* NetConnection, const FGuid& InConnectionId);
	// End UReliableDataTransferNetConnection interface

private:
	bool SendPacket(const uint8* Data, int32 Count);

	FSocketSubsystemEOS* SocketSubsystem = nullptr;;

	TSharedPtr<const FInternetAddrEOS> Address;
	TSharedPtr<FSocketEOS> Socket;
	
	TSharedPtr<FInternetAddrEOS> SenderAddress;
	bool bHasReceivedConnectionId = false;
	FReliableMessagingServerEOS* Server = nullptr;

	FGuid ConnectionId;
	TArray<RDTProtocol::FMessage> IncomingMessages;
	TArrayView<const uint8> ReceivedData;
	int32 ReceivedDataOffset = 0;
	EReliableMessagingConnectionState ConnectionState = EReliableMessagingConnectionState::Connecting;
};
