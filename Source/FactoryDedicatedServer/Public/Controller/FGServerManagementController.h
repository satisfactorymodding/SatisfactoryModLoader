// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGServerControllerBase.h"
#include "FGServerManagementController.generated.h"

class UFGServerSubsystem;
struct FFGRequestHandlerContextWrapper;

/**
 * This class hosts API entry points for managing the server state, such as:
 *  - Save and Session management
 *  - Server name and password management
 *  - Console command execution/log viewing
 *  - Updating server options (e.g. user options that are relevant for the dedicated servers, such as network quality)
 *
 *  Most commands in this Controller require the User to have Administrator privileges.
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerManagementController : public UFGServerControllerBase
{
	GENERATED_BODY()
public:
	// Send by the initial admin to claim the server. After the server is claimed, only server renaming and admin password change is possible
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "InitialAdmin" )
	FFGServerErrorResponse Handler_ClaimServer( const FString& ServerName, const FString& AdminPassword, FString& OutAuthenticationToken, const FFGRequestHandlerContextWrapper& RequestContext ) const;

	// Changes the server name. Should only be used once the server is claimed.
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_RenameServer( const FString& ServerName ) const;

	// Updates the client password for the server
	// This will automatically invalidate all session tokens issued earlier that are based on the client password
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_SetClientPassword( const FString& Password ) const;

	// Updates the admin password for the server.
	// This request will invalidate the current session token if it is based on the admin password, and return a new one in that case
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_SetAdminPassword( const FString& Password, FString& OutAuthenticationToken, const FFGRequestHandlerContextWrapper& RequestContext ) const;

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	void Handler_SetAutoLoadSessionName( const FString &SessionName ) const;
	
	// Runs a console command on the server
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	bool Handler_RunCommand( const FString& Command, FString& OutCommandResult ) const;

	// Shuts down the server
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	static void Handler_Shutdown( const FFGRequestHandlerContextWrapper& RequestContext );

	// Updates the server option values to the provided ones.
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	void Handler_ApplyServerOptions( const TMap<FString, FString>& UpdatedServerOptions ) const;
};
