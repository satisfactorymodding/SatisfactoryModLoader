// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Networking/FGClientAPIManager.h"
#include "FGClientRequestBase.h"
#include "FGClientStateRequester.generated.h"

UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientStateRequester : public UFGClientRequestBase
{
	GENERATED_BODY()
public:
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Client" )
	FFGPendingClientRequest Request_QueryServerState() const;

	UFUNCTION( FGServerResponse )
	void Response_QueryServerState( const FFGServerErrorResponse& ServerResponse, const FServerGameState& ServerGameState ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Client" )
	FFGPendingClientRequest Request_JoinGameRequest() const;

	UFUNCTION( FGServerResponse )
	void Response_JoinGameRequest( const FFGServerErrorResponse& ErrorResponse, const FFGServerJoinDataResponse& ServerJoinData ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Client" )
	FFGPendingClientRequest Request_GetServerOptions() const;

	UFUNCTION( FGServerResponse )
	void Response_GetServerOptions( const FFGServerErrorResponse& ServerResponse, const TMap<FString, FString>& ServerOptions, const TMap<FString, FString>& PendingServerOptions ) const;
	
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Client" )
	FFGPendingClientRequest Request_GetAdvancedGameSettings() const;

	UFUNCTION( FGServerResponse )
	void Response_GetAdvancedGameSettings( const FFGServerErrorResponse& ServerResponse, bool creativeModeEnabled, const TMap<FString, FString>& advancedGameSettings ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Client" )
	FFGPendingClientRequest Request_ApplyAdvancedGameSettings( const TMap<FString, FString>& AppliedAdvancedGameSettings ) const;

	UFUNCTION( FGServerResponse )
	void Response_ApplyAdvancedGameSettings( const FFGServerErrorResponse& ErrorResponse ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGPendingClientRequest Request_HealthCheck( const FString& ClientCustomData ) const;

	UFUNCTION( FGServerResponse )
	void Response_HealthCheck( FFGServerErrorResponse& HealthCheckResult, const FString& ServerCustomData ) const;
};
