// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGClientRequestBase.h"
#include "FGClientAuthenticationRequester.generated.h"

enum class EPrivilegeLevel : uint8;
struct FFGServerErrorResponse;
UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientAuthenticationRequester : public UFGClientRequestBase
{
	GENERATED_BODY()
public:
	/** Returns OK when login token is valid and has at least the given privilege level, or an error otherwise. */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Client" )
	FFGPendingClientRequest Request_VerifyAuthenticationToken( UPARAM( FGServerRequestPassThrough ) EPrivilegeLevel MinimumPrivilegeLevel, UPARAM( FGServerRequestPassThrough ) bool bAutomaticLogin );

	/** Called to handle the login token verification result */
	UFUNCTION( FGServerResponse )
	void Response_VerifyAuthenticationToken( FFGServerErrorResponse& ErrorResponse, EPrivilegeLevel MinimumPrivilegeLevel, bool bAutomaticLogin ) const;
	
	/** Attempts a password-less login when the server is not claimed or when the client password is not set */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGPendingClientRequest Request_PasswordlessLogin( EPrivilegeLevel MinimumPrivilegeLevel, UPARAM( FGServerRequestPassThrough ) EPrivilegeLevel LocalMinimumPrivilegeLevel, UPARAM( FGServerRequestPassThrough ) bool bAutomaticLogin ) const;

	/** Called as a result of the passwordless login */
	UFUNCTION( FGServerResponse )
	void Response_PasswordlessLogin( FFGServerErrorResponse& ErrorResponse, const FString& AuthenticationToken, EPrivilegeLevel LocalMinimumPrivilegeLevel, bool bAutomaticLogin ) const;
	
	/** Logins the client to the server using the given password. */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGPendingClientRequest Request_PasswordLogin( const FString& Password, EPrivilegeLevel MinimumPrivilegeLevel, UPARAM( FGServerRequestPassThrough ) EPrivilegeLevel LocalMinimumPrivilegeLevel ) const;

	/** Called as a result of the password login */
	UFUNCTION( FGServerResponse )
	void Response_PasswordLogin( FFGServerErrorResponse& ErrorResponse, const FString& AuthenticationToken, EPrivilegeLevel LocalMinimumPrivilegeLevel ) const;
};