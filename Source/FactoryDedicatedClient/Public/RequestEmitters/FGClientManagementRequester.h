// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Networking/FGClientAPIManager.h"
#include "FGClientRequestBase.h"
#include "FGClientManagementRequester.generated.h"

UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientManagementRequester : public UFGClientRequestBase
{
	GENERATED_BODY()

public:
	/** Send by the initial admin to claim the server. After the server is claimed, only server renaming and admin password change is possible */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "InitialAdmin" )
	FFGPendingClientRequest Request_ClaimServer( const FString& ServerName, const FString& AdminPassword );

	UFUNCTION( FGServerResponse )
	void Response_ClaimServer( FFGServerErrorResponse& ErrorResponse, const FString& AuthenticationToken ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_RenameServer( const FString& ServerName );

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_SetClientPassword( const FString& Password );
	
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_SetAdminPassword( const FString& Password );
	
	UFUNCTION( FGServerResponse )
	void Response_SetAdminPassword( const FString& AuthenticationToken ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_SetAutoLoadSessionName( const FString& SessionName );

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_RunCommand( const FString& Command );

	UFUNCTION( FGServerResponse )
	void Response_RunCommand( const FFGServerErrorResponse& ErrorResponse, const FString& CommandResult ) const;

	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_ApplyServerOptions( const TMap<FString, FString>& UpdatedServerOptions ) const;

	UFUNCTION( FGServerResponse )
	void Response_ApplyServerOptions( const FFGServerErrorResponse& ErrorResponse ) const;
};
