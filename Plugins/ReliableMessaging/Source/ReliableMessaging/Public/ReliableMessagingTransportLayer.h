#pragma once

#include "CoreMinimal.h"
#include "ReliableMessagingProtocol.h"

class UNetDriver;
class UNetConnection;
class FInternetAddr;
class UReliableMessagingPlayerComponent;

enum class EReliableMessagingConnectionState : uint8
{
	Disconnected,
	Connecting,
	Connected
};

class RELIABLEMESSAGING_API IReliableMessageTransportConnection
{
public:
	virtual ~IReliableMessageTransportConnection() = 0;
	virtual void EnqueueMessage(uint8 Channel, TArray<uint8>&& Message) = 0;
	virtual FGuid GetConnectionId() const = 0;
	[[nodiscard]] virtual EReliableMessagingConnectionState Tick(float DeltaTime) = 0;
	virtual void DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher) = 0;
	virtual void Close() = 0;
};

/**
 * Interface instantiated on the server side of a reliable message protocol. It's job is primarily to listen for incoming connections and manage them.
 */
class RELIABLEMESSAGING_API IReliableMessageTransportServer
{
public:
	virtual ~IReliableMessageTransportServer() = 0;
	
	virtual TArray<TUniquePtr<IReliableMessageTransportConnection>> Tick(float DeltaTime) = 0;
	virtual void Shutdown() = 0;
};
