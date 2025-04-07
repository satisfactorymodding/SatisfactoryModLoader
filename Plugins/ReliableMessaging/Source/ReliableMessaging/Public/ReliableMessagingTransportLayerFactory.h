#pragma once

#include "CoreMinimal.h"
#include "ReliableMessagingTransportLayer.h"

#include "ReliableMessagingTransportLayerFactory.generated.h"

class IReliableMessageTransportServer;
class IReliableMessageTransportConnection;
class UNetConnection;

UCLASS(Abstract)
class RELIABLEMESSAGING_API UReliableMessagingTransportLayerFactory : public UObject
{
	GENERATED_BODY()
public:
	/**
	 * Has to be implemented by the derived class.
	 * This function should return a new instance of the server side of the protocol that is already listening for incoming connections.
	 * @return the server instance only if it's listening (ie it succeeded initialization), nullptr otherwise.
	 */
	virtual TUniquePtr<IReliableMessageTransportServer> CreateListeningServer(UNetDriver* NetDriver) const PURE_VIRTUAL(
		UReliableMessageProtocolFactory::CreateServer, return nullptr;);

	virtual TUniquePtr<IReliableMessageTransportConnection> Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData,
		FGuid ConnectionId) const PURE_VIRTUAL(UReliableMessageProtocolFactory::CreateClient, return nullptr;);

	/**
	 * If a certain implementation requires custom data to be sent to the client as part of the initial handshake,
	 * this function should be overridden to provide that data.
	 */
	virtual TArray<uint8> GetCustomClientConnectionData(IReliableMessageTransportServer& Server) const;
};

