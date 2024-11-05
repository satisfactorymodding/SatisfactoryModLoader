// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/CircularQueue.h"

class FInternetAddr;
enum class EServerState : uint8;

struct FServerNetStats
{
	static constexpr int32 NumPollsForAverage = 25;
	
	/// Used to compute the average round trip times over the last @NumPollsForAverage polls
	TCircularQueue<int64> RoundTripTimesQueue = TCircularQueue<int64>( NumPollsForAverage + 1 );

	/// The cached sum of all entries in @RoundTripTimesQueue
	int64 RoundTripTimesSum = 0;

	/// Average roundtrip over the last @NumPollsForAverage polls
	FTimespan AverageRoundTripTime;

	/// When did this server last show any signs of life 
	FDateTime TimeWhenLastResponded;

	/// When did we last try to ping this server
	FDateTime TimeWhenLastPolled;
	FDateTime TimeWhenLastPolledWithTimeout;

	/// Time when last interesting is used to determine whether a server should be pinged or not in relation to it's ping rate
	/// Cannot use TimeWhenLastResponded for this alone as there other other triggers for beginning to poll a server, such as a new listener
	/// subscribing to it's state.
	FDateTime TimeWhenLastInteresting;

	/// The rate at which we are currently polling this server
	float PollingRate = 0.25f;
};

enum class EServerQueryId : uint8
{
	PollServerStateRequest,
	PollServerStateResponse
};

/** A list of known flags. Undefined bits are implied to be server-specific or custom */
enum class EServerFlags : uint64
{
	/** Indicates that the server is running the Mod Loader. Vanilla clients will not be able to connect to modded servers. */
	Modded  = 0x01,
	/** Custom bits that are guaranteed to not be used by the game across the game version changes. */
	Custom1 = 0x02,
	Custom2 = 0x04,
	Custom3 = 0x08,
	Custom4 = 0x10,
};
ENUM_CLASS_FLAGS( EServerFlags );

/** Possible sub state IDs that can be received from the server. Undefined values are implied to be server-specific or custom */
enum class EServerSubStateId : uint8
{
	/** Version of the ServerState (FServerGameState). Updated on player login/logout, game restart, schematic unlock and stage progression */
	ServerGameState,
	/** Version of the ServerOptions (UFGGameUserSettings). Updated when user settings change. */
	ServerOptions,
	/** Version of the AdvancedGameSettings (UFGAdvancedGameSettings). Updated when the AGS change (including save reloads) */
	AdvancedGameSettings,
	/** Version of the save list returned by EnumerateSessions. Updated when UFGSaveSystem::OnSaveCollectionChanged is fired on the server */
	SaveCollection,
	/** Custom versions that are guaranteed to not be used by the game across the game version changes. */
	Custom1,
	Custom2,
	Custom3,
	Custom4,
};

struct FServerStatePollResponse
{
	FTimespan RoundtripTime;
	EServerState State;
	TSharedPtr<FInternetAddr> ServerAddress;
	FDateTime RequestTime;
	uint32 ServerNetCL;
	EServerFlags ServerFlags;
	TMap<EServerSubStateId, uint16> ServerSubStateVersions;
	FString ServerName;
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
	FirstVersion,

	/**
	 * Second version of the server state polling request.
	 * Request (PollServerStateRequest) structure:
	 * ==================
	 * protocol magic: 2 byte (0xF6D5)
	 * protocol message: 1 byte (EServerQueryId::PollServerStateRequest)
	 * protocol version: 1 byte (this enum)
	 * timestamp in milliseconds: uint64
	 * terminator bit: 1 byte (0x1)
	 *
	 * Response (PollServerStateResponse) structure:
	 * ==================
	 * protocol magic: uint16 (0xF6D5)
	 * protocol message: 1 byte (EServerQueryId::PollServerStateRequest)
	 * protocol version: 1 byte (this enum - should match request version)
	 * timestamp in milliseconds: uint64 (should be the same value send with the request)
	 * server state: 1 byte EServerState
	 * server NET CL: uint32 - clients on different NET CLs won't be able to connect to this server
	 * server flags: uint64 - flags that the server has set. A bitmask of EServerFlags
	 * sub state versions length: 1 byte - length of the list of the following entries
	 *  sub state version entry:
	 *   sub state id: 1 byte - one of the values in EServerSubStateId
	 *   sub state version: uint16 - an incrementally changed transient value. The client can determine if the server game state has
	 *		changed by caching the version and comparing it to the version returned by the subsequent queries to the dedicated server
	 * server name:
	 *   server name length: uint16 - length of the following server name payload
	 *   server name data: uint8[server name length] - utf-8 encoded server name
	 * terminator bit: 1 byte (0x1)
	 */ 
	SecondVersion,

	// Add versions above this one
	LatestVersionPlusOne,
	LatestVersion = LatestVersionPlusOne - 1
};

namespace EServerStatePollingReqConstants
{
	// Maximum possible datagram length currently allowed by the dedicated server query protocol.
	// Further extensions can change this field, and it is only used to determine a maximum receive buffer size on the client
	static constexpr int32 MaxDatagramLengthBytes = 256;
}
