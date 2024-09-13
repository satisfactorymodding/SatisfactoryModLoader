// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Security/FGClientCertificateManager.h"
#include "UObject/Interface.h"
#include "FGServerUIProxy.generated.h"

struct FFGServerErrorResponse;
struct FFGServerCertificate;

DECLARE_DYNAMIC_DELEGATE_OneParam( FServerSetAdminPasswordCallback, const FString&, AdminPassword );
DECLARE_DYNAMIC_DELEGATE_OneParam( FServerSetJoinPasswordCallback, const FString&, JoinPassword );
DECLARE_DYNAMIC_DELEGATE_OneParam( FServerClaimCallback, const FString&, ServerName );
DECLARE_DYNAMIC_DELEGATE_OneParam( FServerAcceptCertificateCallback, FFGServerCertificate, Certificate );
DECLARE_DYNAMIC_DELEGATE( FFGServerDeclineCertificateCallback );
DECLARE_DYNAMIC_DELEGATE( FServerCancelOperationCallback );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FServerTryPasswordCallback, const FString&, Password, EPrivilegeLevel, MinimumTargetPrivilege );
DECLARE_DYNAMIC_DELEGATE_OneParam( FServerChangeServerNameCallback, const FString&, NewServerName );

UENUM( BlueprintType )
enum class EServerMessage : uint8
{
	InvalidHost,
	IncorrectPassword,
	Timeout,
	NoGameRunning,
	LoadingGame_Disconnect,
	NotAuthorized,
	PasswordInUse,
};

UINTERFACE( MinimalAPI, Blueprintable )
class UFGDedicatedServerUIProxy : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface that a dedicated server connection needs to use for User Interaction. Whenever a dedicated server requires user input, it will
 * be requested through this interface. 
 */ 
class IFGDedicatedServerUIProxy
{
	GENERATED_BODY()
public:
	/**
	 * An action from the user was not successful. An appropriate message should be presented to the user
	 **/ 
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleServerMessage( EServerMessage Message );

	/**
	 * An error has occured executing the previously issued request to the server.
	 * The error description is available in the ServerError structure.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleServerError( const FFGServerErrorResponse& ServerError );
	
	/**
	 * The server is asking for a password.
	 * Must be followed up by calling either @TryPasswordCallback or @CancelCallback
	 **/ 
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandlePasswordRequest( EPrivilegeLevel MinimumTargetPrivilege, const FServerTryPasswordCallback &TryPasswordCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	* The client is required to set an administration password.
	* Must be followed up by calling either @SetAdminPasswordCallback or @CancelCallback
	**/ 
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleSetAdminPasswordRequest( const FServerSetAdminPasswordCallback &SetAdminPasswordCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	* The server has not been claimed and is asking the local player to claim it.
	* Must be followed up by calling either @ServerClaimCallback or @CancelCallback
	**/
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleUnclaimedServerGreeting( const FServerClaimCallback &ServerClaimCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	 * The client is required to set an optional join password.
	 * Must be followed up by calling either @SetJoinPasswordCallback or @CancelCallback
	 **/ 
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleSetJoinPasswordRequest( const FServerSetJoinPasswordCallback &SetJoinPasswordCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	 * The client is required to accept the remote certificate before the further communication with the server can be established
	 * Must be followed up by calling either @AcceptCallback or @CancelCallback
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleAllowUntrustedCertificate( const FFGServerCertificate& Certificate, const FServerAcceptCertificateCallback& AcceptCallback, const FServerCancelOperationCallback& CancelCallback );

	/**
	 * The user is willing to change the name of the server, and should be presented with a pop-up to do so
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Server UI Proxy" )
	void HandleChangeServerNameCallback( const FServerChangeServerNameCallback& ChangeServerNameCallback );
};

UCLASS( Abstract, Blueprintable, BlueprintType )
class FACTORYDEDICATEDCLIENT_API UFGBaseServerInteractionHandler : public UObject, public IFGDedicatedServerUIProxy
{
	GENERATED_BODY()
public:
	virtual UWorld* GetWorld() const override;

	/** Returns the first locally controlled player controller to be used with this interact handler */
	UFUNCTION( BlueprintPure, Category = "Server UI Proxy" )
	APlayerController* GetFirstPlayerController() const;

	/** Returns a formatting text for the given server message */
	UFUNCTION( BlueprintPure, Category = "Server UI Proxy" )
	static FText GetServerMessageDescription( EServerMessage Message );
};

