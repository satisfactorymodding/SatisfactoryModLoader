// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Delegates/DelegateSignatureImpl.inl"
#include "Containers/Queue.h"
#include "HAL/Runnable.h"
#include "SocketSubsystem.h"
#include "Templates/UniquePtr.h"

class FInternetAddr;
class FSocket;
class FRunnableThread;
class FReliableMessagingTCPAsyncConnHandler;

class FReliableMessagingTCPAsyncListener: public FRunnable
{
	
public:
	FReliableMessagingTCPAsyncListener(FUniqueSocket&& InSocket, ISocketSubsystem* InSocketSubsystem, FTimespan InExpectedConnectionLifetime);

	void StartThread();
	void Terminate();

	void GetListenAddress(FInternetAddr& OutAddr) const;
	bool DequeueIncomingConnectionHandler(TUniquePtr<FReliableMessagingTCPAsyncConnHandler>& OutHandler);
	void EnqueueExpectedConnectionPeer(TSharedPtr<FInternetAddr> PeerAddr, FGuid ConnectionId);

protected:
	// Begin FRunnable interface.
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	// End FRunnable interface

private:
	TUniquePtr<FRunnableThread> Thread = nullptr;
	std::atomic<bool> bStopRequested = false;
	const FUniqueSocket Socket;
	ISocketSubsystem* SocketSubsystem = nullptr;
	TQueue<TUniquePtr<FReliableMessagingTCPAsyncConnHandler>> IncomingConnectionHandlers;
	TArray<TUniquePtr<FReliableMessagingTCPAsyncConnHandler>> PendingConnectionHandlers;

	struct FExpectedConnection
	{
		TSharedPtr<FInternetAddr> PeerAddress;
		FGuid ConnectionId;
		FDateTime Timestamp;
	};
	
	// The queue of expected connection peers exclusively used by the game thread to register expected connections with the server.
	TQueue<FExpectedConnection> ExpectedConnectionQueue;

	// This is a set of addresses that we expect to receive connections from. This is used to validate incoming connections.
	// If the address is not in this set, the connection is rejected.
	// And array is used instead of a set because we may in fact expect multiple connections from the same address
	TArray<FExpectedConnection> ExpectedConnections;
	FTimespan ExpectedConnectionLifetime;
};
