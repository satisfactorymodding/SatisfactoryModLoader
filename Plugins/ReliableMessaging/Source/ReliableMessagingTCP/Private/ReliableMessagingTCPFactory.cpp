#include "ReliableMessagingTCPFactory.h"

TUniquePtr<IReliableMessageTransportServer> UReliableMessagingTCPFactory::CreateListeningServer(UNetDriver* NetDriver) const{ return Super::CreateListeningServer(NetDriver); }
TUniquePtr<IReliableMessageTransportConnection> UReliableMessagingTCPFactory::Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData, FGuid ConnectionId) const{ return Super::Connect(Connection, CustomClientConnectionData, ConnectionId); }
TArray<uint8> UReliableMessagingTCPFactory::GetCustomClientConnectionData(IReliableMessageTransportServer& Server) const{ return Super::GetCustomClientConnectionData(Server); }
