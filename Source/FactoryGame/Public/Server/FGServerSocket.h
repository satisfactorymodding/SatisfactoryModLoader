#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGDedicatedServerTypes.h"
#include "HAL/Runnable.h"
#include "SocketSubsystem.h"
#include "FGServerSocket.generated.h"

struct FServerStatePollResponse
{
	uint16 RoundtripTimeMs;
	EServerState State;
	TSharedPtr< FInternetAddr > ServerAddress;
	uint64 RequestTimeMs;
	uint32 ServerNetCL;
	uint16 ServerBeaconPort;
};

enum class EServerQueryId : uint8
{
	PollServerStateRequest,
	PollServerStateResponse
};

enum class EServerStatePollingReqProtocolVersion : uint8
{
	/**
	 * First version of the server state polling request.
	 * Request (PollServerStateRequest) structure:
	 * ==================
	 * protocol version: 1 byte (this enum)
	 * timestamp in milliseconds: uint64
	 *
	 * Response (PollServerStateResponse) structure:
	 * ==================
	 * protocol version: 1 byte (this enum - should match request version)
	 * timestamp in milliseconds: uint64 (should be the same value send with the request)
	 * server state: 1 byte EServerState
	 * server NET CL: uint32 - clients on different NET CLs won't be able to connect to this server
	 * beacon port: uint16
	 */ 
	FirstVersion
};

constexpr int32 PollServerStateResponseSize =
	  sizeof(EServerQueryId)							// Query id
	+ sizeof(EServerStatePollingReqProtocolVersion)		// Protocol version
	+ sizeof(uint64)									// Client timestamp
	+ sizeof(EServerState)								// Server State
	+ sizeof(uint32)									// Server NET CL
	+ sizeof(uint16);									// Server Beacon Port
constexpr int32 PollServerStateRequestSize = sizeof(EServerQueryId) + sizeof(EServerStatePollingReqProtocolVersion) + sizeof(uint64);

/**
 * Utility base class that tracks if a thread should keep running
 */ 
class FRunnableSocketBase: public FRunnable
{
public:
	virtual void Stop() override;
	
protected:
	bool ShouldStop() const;
	
private:
	bool mShouldStop = false;
};

struct FRouteInfo
{
	TUniquePtr<class FServerSocketReceiveThread> ReceiveThread;
	TUniquePtr<class FServerSocketSendThread> SendThread;
	FUniqueSocket Socket;
	
	TSharedPtr<FInternetAddr> FromAddress;
	TSharedPtr<FInternetAddr> ToAddress;

	std::atomic<double> TimeWhenWasLastActive = FApp::GetCurrentTime();
};

/**
 * The main socket for the dedicated server. Can be used to query server state or as a proxy for the game or beacon ports.
 */ 
class FPacketDispatcher
{
public:
	FPacketDispatcher( TSharedRef<FInternetAddr> BindAddress, const class UFGServerSocket& Outer );
	~FPacketDispatcher();
	
	bool Initialize();
	void RegisterReroutedPort( FAnsiStringView MagicHeader, uint16 ListeningPort );
	
private:
	void DispatchPacket( TArray<uint8> Data, TSharedRef<FInternetAddr> Sender );
	void ReroutePacket( TArray<uint8> PacketData, TSharedRef<FInternetAddr> FromAddress, TSharedRef<FInternetAddr> ToAddress );
	void ProcessPoll( const TArray<uint8>& PacketData, TSharedRef<FInternetAddr> FromAddress );
	void CleanupRoutes();
	
	FUniqueSocket mSocket;
	TSharedRef<FInternetAddr> mBindAddress;

	TMap<TSharedRef<FInternetAddr>, TUniquePtr<FRouteInfo>, FDefaultSetAllocator, FInternetAddrKeyMapFuncs<TUniquePtr<FRouteInfo>>> mOpenRoutes;
	TArray<TUniquePtr<FRouteInfo>> mClosingRoutes;
	TMap<FAnsiStringView, TSharedRef<FInternetAddr> > mRoutingTable;
	double mTimeWhenLastCleanedUpRoutes = FApp::GetCurrentTime();
	
	TUniquePtr<class FServerSocketReceiveThread> mReceiveThread;
	TUniquePtr<class FServerSocketSendThread> mSendThread;
	const class UFGServerSocket& mOuter;
};

UCLASS( Within=FGServerSubsystem, Config=Engine )
class UFGServerSocket : public UObject
{
	GENERATED_BODY()
public:
	UFGServerSocket();
	bool Initialize( int32 ListenPort );

	virtual void BeginDestroy() override;
		
	UPROPERTY( Config )
	float RouteTimeout = 300.f;

	UPROPERTY( Config )
	int32 DesiredSendBufferSize = 0x40000;

	UPROPERTY( Config )
	int32 DesiredReceiveBufferSize = 0x40000;

	UPROPERTY( Config )
	int32 DesiredRouteSendBufferSize = 0x20000;

	UPROPERTY( Config )
	int32 DesiredRouteReceiveBufferSize = 0x20000;

	void RegisterReroutedPort( FAnsiStringView MagicHeader, uint16 ListeningPort );

	std::atomic<EServerState> ServerState = EServerState::Offline;
	const uint32 NetCL = 0;
	std::atomic<uint16> ListeningBeaconPort = 0;

	int32 mListenPort = 0;

	TArray<TUniquePtr<FPacketDispatcher>> mPacketDispatchers;
};

class FClientQuerySocket: public FRunnableSocketBase
{
public:
	FClientQuerySocket( TSharedRef< FInternetAddr > BindAddr );
	
	virtual bool Init() override;
	virtual uint32 Run() override;

	TSharedRef< const FInternetAddr > GetBoundAddress()
	{
		return mBindAddress;
	}
	
	// Queue from quick socket thread to Game thread
	TQueue< FServerStatePollResponse > mServerStatePollResponses;
	// Queue from Game thread to quick socket thread. 
	TQueue< TSharedPtr< FInternetAddr > > mServerStatePollRequestQueue;
private:
	FUniqueSocket mSocket;
	TSharedRef< FInternetAddr > mBindAddress;
	bool mShouldStop = false;
	int32 mFailedSends = 0;
};
