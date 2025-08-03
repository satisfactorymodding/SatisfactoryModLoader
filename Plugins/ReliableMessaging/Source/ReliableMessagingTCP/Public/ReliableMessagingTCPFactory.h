#pragma once

#include "ReliableMessagingTransportLayerFactory.h"

#include "ReliableMessagingTCPFactory.generated.h"


/**
 * Implementation of the transport layer factory for TCP. This specific implementation also doubles down as a configuration entry point for the TCP server
 * as it is conveniently derived from UObject
 */
UCLASS(Config=Engine)
class UReliableMessagingTCPFactory: public UReliableMessagingTransportLayerFactory
{
	GENERATED_BODY()
public:
	virtual TUniquePtr<IReliableMessageTransportServer> CreateListeningServer(UNetDriver* NetDriver) const override;
	virtual TUniquePtr<IReliableMessageTransportConnection> Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData, FGuid ConnectionId) const override;
	virtual TArray<uint8> GetCustomClientConnectionData(IReliableMessageTransportServer& Server) const override;

	/**
	 * The first port that the server will attempt to listen on. If this port is already in use, the server will attempt to bind to the next port in the range.
	 */
	UPROPERTY(Config)
	int32 PortRangeBegin = 8888;

	/**
	 * The number of consecutive ports that should be tried if the initial port is already in use.
	 */
	UPROPERTY(Config)
	int32 PortRangeLength = 512;

	/**
	 * If the server is behind a NAT, the server maintainer may need to remap the port range. If that is the case, this value needs to be set to the first port in the remapped range.
	 * Failing to set this value will result in clients attempting to connect to the bound port, which will differ from the external port and clients outside the NAT subnet will not be able to connect.
	 */
	UPROPERTY(Config)
	int32 ExternalPortRangeBegin = INDEX_NONE;
};
