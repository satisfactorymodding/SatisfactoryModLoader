// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "DelegateSignatureImpl.inl"
#include "Queue.h"
#include "Runnable.h"
#include "SocketSubsystem.h"
#include "UniquePtr.h"

class FInternetAddr;
class FSocket;
class FRunnableThread;
class FReliableMessagingTCPAsyncConnHandler;

class FReliableMessagingTCPAsyncListener: public FRunnable
{
	
public:
	FReliableMessagingTCPAsyncListener(FUniqueSocket&& InSocket, ISocketSubsystem* InSocketSubsystem);

	void StartThread();
	void Terminate();

	void GetListenAddress(FInternetAddr& OutAddr) const;
	bool DequeueIncomingConnectionHandler(TUniquePtr<FReliableMessagingTCPAsyncConnHandler>& OutHandler);
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
};
