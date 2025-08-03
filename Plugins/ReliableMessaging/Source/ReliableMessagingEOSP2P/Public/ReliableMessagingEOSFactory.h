// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "ReliableMessagingTransportLayerFactory.h"

#include "ReliableMessagingEOSFactory.generated.h"

class FEOSReliableDataTransferNetConnection;
class FSocketEOS;
class FInternetAddrEOS;
class FSocketSubsystemEOS;

class FReliableMessagingServerEOS: public IReliableMessageTransportServer
{
public:
	static const FName ReliableTransferSocketName;

	bool StartListening(UNetDriver* InNetDriver);
	virtual TArray<TUniquePtr<IReliableMessageTransportConnection>> Tick(float DeltaTime) override;
	virtual void Shutdown() override;
	
	void DispatchPacket(const TArray<uint8>& Data, TSharedRef<const FInternetAddrEOS> SenderAddress);
	TSharedPtr<FInternetAddrEOS> ListenAddress;
	TSharedPtr<FInternetAddrEOS> SenderAddress;
	TSharedPtr<FSocketEOS> Socket;
	FSocketSubsystemEOS* SocketSubsystem = nullptr;

	void ForgetAboutConnection(FEOSReliableDataTransferNetConnection* Connection);
private:
	TArray<uint8> RecvBuffer;
	TArray<TUniquePtr<FEOSReliableDataTransferNetConnection>> PendingConnections;
	TArray<FEOSReliableDataTransferNetConnection*> EstablishedConnections;
};

UCLASS()
class UReliableMessagingEOSFactory: public UReliableMessagingTransportLayerFactory
{
	GENERATED_BODY()
public:
	virtual TUniquePtr<IReliableMessageTransportServer> CreateListeningServer(UNetDriver* NetDriver) const override;
	virtual TUniquePtr<IReliableMessageTransportConnection> Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData, FGuid ConnectionId) const override;
};