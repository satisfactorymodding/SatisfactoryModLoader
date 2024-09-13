// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGServerControllerBase.h"
#include "Networking/FGServerAPIManager.h"
#include "FGServerStateController.generated.h"

struct FFGServerJoinDataResponse;
class UFGServerSubsystem;

/**
 * Server State Controller provides server state operations such as:
 *  - Querying the Server State
 *  - Joining the Server (e.g. the game session)
 *
 * Operations in this controller can be accessed by any player with at least Client level.
 * Application Token based clients cannot join the server (because they are not a game).
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerStateController : public UFGServerControllerBase
{
	GENERATED_BODY()

public:
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Client" )
	FFGServerErrorResponse Handler_JoinGameRequest( const FFGRequestHandlerContextWrapper& requestHandlerContext, FFGServerJoinDataResponse& ServerJoinData ) const;
	
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Client" )
	void Handler_QueryServerState( FServerGameState& outServerGameState ) const;

	/**
	 * Returns the current values of the server options. Only a DS relevant subset of options is returned.
	 * If the option has a pending value that cannot for whatever reason be applied right now, the pending server options will also contain an entry
	 * with the value that is pending to be applied but has not been applied yet.
	 */
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Client" )
	void Handler_GetServerOptions( TMap<FString, FString>& OutServerOptions, TMap<FString, FString>& OutPendingServerOptions ) const;

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Client" )
	void Handler_GetAdvancedGameSettings( bool& bOutCreativeModeEnabled, TMap<FString, FString>& OutAdvancedGameSettings ) const;

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Client" )
	void Handler_ApplyAdvancedGameSettings( const TMap<FString, FString>& AppliedAdvancedGameSettings ) const;

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGServerErrorResponse Handler_HealthCheck( const FString& ClientCustomData, FString& OutHealth, FString& OutServerCustomData ) const;
};