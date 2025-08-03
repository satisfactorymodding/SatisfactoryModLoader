#include "ReliableMessagingSteamFactory.h"

TUniquePtr<IReliableMessageTransportServer> UReliableMessagingSteamFactory::CreateListeningServer(UNetDriver* NetDriver) const{ return Super::CreateListeningServer(NetDriver); }
TUniquePtr<IReliableMessageTransportConnection> UReliableMessagingSteamFactory::Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData, FGuid ConnectionId) const{ return Super::Connect(Connection, CustomClientConnectionData, ConnectionId); }

