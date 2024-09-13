// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGServerControllerBase.h"
#include "Networking/FGServerAPIManager.h"
#include "FGServerAuthenticationController.generated.h"

struct FFGRequestHandlerContextWrapper;
class UFGServerSubsystem;

/**
 * Handles Authentication for the Server API and tasks such as:
 *  - Authenticating players using the client or server passwords
 *  - Verifying the state of previously issued tokens
 *  - Issuing application tokens
 *  - Confirming the identity of the players
 *
 * Functions in this controller do not require any authentication.
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerAuthenticationController : public UFGServerControllerBase
{
	GENERATED_BODY()

	// Returns OK if authentication token provided is valid.
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Client" )
	static FFGServerErrorResponse Handler_VerifyAuthenticationToken();

	// Attempts a password-less login when the server is not claimed or when the client password is not set
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGServerErrorResponse Handler_PasswordlessLogin( EPrivilegeLevel MinimumPrivilegeLevel, FString& OutAuthenticationToken, const FFGRequestHandlerContextWrapper& RequestHandlerContext ) const;

	// Logins the client to the server using the given password.
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGServerErrorResponse Handler_PasswordLogin( const FString& Password, EPrivilegeLevel MinimumPrivilegeLevel, FString& OutAuthenticationToken, const FFGRequestHandlerContextWrapper& RequestHandlerContext ) const;
};