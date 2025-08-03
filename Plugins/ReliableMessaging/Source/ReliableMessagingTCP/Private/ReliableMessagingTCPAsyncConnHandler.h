// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "BulkDataReplicationModule.h"
#include "Delegate.h"
#include "Guid.h"
#include "ReliableMessagingProtocol.h"
#include "Queue.h"
#include "Runnable.h"
#include "SocketSubsystem.h"
#include "UniquePtr.h"

enum class EReliableMessagingConnectionState : uint8;
class FInternetAddr;
class FSocket;

class FReliableMessagingTCPAsyncConnHandler
	: public FRunnable
	, public FReliableDataTransferProtocolReader<FReliableMessagingTCPAsyncConnHandler>
	, public TSharedFromThis<FReliableMessagingTCPAsyncConnHandler, ESPMode::ThreadSafe>
{
public:
	FReliableMessagingTCPAsyncConnHandler(ISocketSubsystem* InSocketSubsystem, FUniqueSocket&& InSocket);
	virtual ~FReliableMessagingTCPAsyncConnHandler() override;
	
	void StartThread();
	void Terminate();

	void GetRemoteAddress(FInternetAddr& Addr) const;

	/**
	 * Returns the connection id of this connection. Will only be valid as long as HasReceivedConnectionId() returns true. 
	 */
	FGuid GetConnectionId() const;

	/**
	 * Tells us whether we have received a connection id from the remote host. 
	 */
	bool HasReceivedConnectionId() const;

	template <typename FuncType>
	void DispatchMessages(FuncType&& Dispatcher)
	{
		RDTProtocol::FMessage DispatchMessage;
		while(ReceiveQueue.Dequeue(DispatchMessage))
		{
			UE_LOG(LogReliableMessaging, Verbose, TEXT("Dispatching message with payload size %d on channel %d"), DispatchMessage.Data.Num(), DispatchMessage.ChannelId);
			Dispatcher(MoveTemp(DispatchMessage));
		}
	}

	/**
	 * Yields out a pointer to the socket but does not relinquish ownership.
	 */
	FSocket* GetSocket() const { return Socket.Get(); }

	void HandleConnectionIdReceived(FGuid InConnectionId);
    void HandleMessageReceived(RDTProtocol::FMessage&& InMessage);
    bool ReadData(uint8* Buffer, const int32 InBufferLength, int32& BytesRead);
	void CloseConnection();

	[[nodiscard]] EReliableMessagingConnectionState GetConnectionState() const;

protected:	
	// Begin FRunnable interface.
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	// End FRunnable interface
	
private:
	TQueue<RDTProtocol::FMessage, EQueueMode::Spsc> ReceiveQueue;
	
	TUniquePtr<FRunnableThread> Thread = nullptr;
	FUniqueSocket Socket;
	std::atomic<bool> bIsExitRequested = false;
	std::atomic<bool> bHasReceivedConnectionId = false;
	/** breaking down the 4 components of */ 
	std::atomic<uint32> ConnectionIdA = 0;
	std::atomic<uint32> ConnectionIdB = 0;
	std::atomic<uint32> ConnectionIdC = 0;
	std::atomic<uint32> ConnectionIdD = 0;
	const TSharedRef<FInternetAddr> RemoteAddress;
	std::atomic<EReliableMessagingConnectionState> ConnectionState;
};
