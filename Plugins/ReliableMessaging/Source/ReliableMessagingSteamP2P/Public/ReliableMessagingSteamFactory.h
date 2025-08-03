
#pragma once
#include "ReliableMessagingTransportLayerFactory.h"

#include "ReliableMessagingSteamFactory.generated.h"


UCLASS()
class UReliableMessagingSteamFactory: public UReliableMessagingTransportLayerFactory
{
	GENERATED_BODY()
public:
	virtual TUniquePtr<IReliableMessageTransportServer> CreateListeningServer(UNetDriver* NetDriver) const override;
	virtual TUniquePtr<IReliableMessageTransportConnection> Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData, FGuid ConnectionId) const override;
};