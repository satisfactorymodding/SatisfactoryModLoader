// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGServerStateListener.generated.h"

enum class EFGServerAPIState : uint8;
class UFGServerObject;

/**
 * Aggregates the three states that can be determine what operations are possible into on state to simplify logic in blueprints
 **/ 
UENUM( BlueprintType )
enum class EServerComplexState : uint8
{
	/**
	 * Server is offline. Nothing can be done to it in this state
	 */ 
	ServerOffline,
	/**
	 * The server is online and it is currently idle (not running a game). We have no control connection established to it and that
	 * is the only thing we can do in this state
	 */ 
	NoGameRunning_NotConnected_CompatibleVersion,
	NoGameRunning_NotConnected_IncompatibleVersion,
	/**
	 * Server online and connection pending
	 */ 
	NoGameRunning_ConnectionPending,
	NoGameRunning_ConnectionFailed,
	/**
	 * Server Online, game not running and we are connected as clients. In this state we can't do much other than wait for an administrator to start a game.
	 */ 
	NoGameRunning_Connected_Client,
	/**
	 * Server Online, game not running and we are connected as admins. In this state we can create a game on the server or perform any admin operations, such as changing server settings. 
	 */
	NoGameRunning_Connected_Admin,
	/**
	 * Server Online, game not running and we are not authenticated
	 */ 
	NoGameRunning_Connected_NonAuthenticated,
	/**
	 * The server is loading a game. At this point, all we can do is wait for it to finish as it is unable to receive connections in this state
	 */
	GameLoading,
	/**
	 * A game is running and we are not connected. We need to establish a connection before we can do anything. 
	 */
	GameRunning_NotConnected_CompatibleVersion,
	GameRunning_NotConnected_IncompatibleVersion,
	/**
	 * Game is running and connection is pending
	 */
	GameRunning_ConnectionPending,
	GameRunning_ConnectionFailed,
	/**
	 * A game is running and we are connected as clients. At this point we can join the game
	 */ 
	GameRunning_Connected_Client,
	/**
	 * Game running, us admins, we can perform any admin operation. 
	 */ 
	GameRunning_Connected_Admin,
	/**
	 * Game running, we are not authenticated. 
	 */ 
	GameRunning_Connected_NonAuthenticated
};
