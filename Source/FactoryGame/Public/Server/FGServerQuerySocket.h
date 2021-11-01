#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Server/FGDedicatedServerTypes.h"
#include "HAL/Runnable.h"
#include "SocketSubsystem.h"

DECLARE_LOG_CATEGORY_EXTERN( LogServerQuery, Log, Log );

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

class FContinuousRunnable: public FRunnable
{
public:
	virtual void Stop() override;
	
protected:
	bool ShouldStop() const;
	
private:
	bool mShouldStop = false;
};

class FServerQuerySocket: public FContinuousRunnable
{
public:
	FServerQuerySocket( uint16 QueryPort );

	virtual bool Init() override;
	virtual uint32 Run() override;

	void SetState( EServerState State );
	void SetBeaconPort( uint16 Port );
	
private:
	FUniqueSocket mSocket;
	std::atomic<EServerState> mServerState = EServerState::Offline;
	const uint32 mNetCL = 0;
	std::atomic<uint16> mBeaconPort = 0;
	uint16 mQueryPort = 0;
};

class FClientQuerySocket: public FContinuousRunnable
{
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	
	// Queue from quick socket thread to Game thread
	TQueue< FServerStatePollResponse > mServerStatePollResponses;
	// Queue from Game thread to quick socket thread. 
	TQueue< TSharedPtr< FInternetAddr > > mServerStatePollRequestQueue;
private:
	FUniqueSocket mSocket;
	bool mShouldStop = false;
};
