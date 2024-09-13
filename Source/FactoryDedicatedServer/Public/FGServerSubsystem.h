// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "FGServerSettings.h"
#include "IPAddress.h"
#include "SocketSubsystem.h"
#include "Engine/TimerHandle.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Server/FGDSGameplayTypes.h"
#include "Server/FGDSAuthenticationTypes.h"
#include "Server/FGDSSharedTypes.h"
#include "Networking/FGOffThreadServerQuerySocket.h"
#include "FGServerSubsystem.generated.h"

struct FSaveHeader;
enum class EServerSubStateId : uint8;
enum class EServerFlags : uint64;
struct FFGStoredPasswordData;
class UFGServerSettings;
class UFGServerAPIManager;
class UFGServerControllerArray;
class FFGOffThreadServerQuerySocket;

DECLARE_DELEGATE_RetVal_TwoParams( FFGServerErrorResponse, FFGServerCheckHealthCheckCompatibility, const FString& /** ClientCustomData */, FString& /** OutServerCustomData */ );

/**
 * Server-side class that serves as the entry point for all dedicated server related operations. Also manages all server specific settings.
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerSubsystem : public UGameInstanceSubsystem, public FTSTickerObjectBase, public IFGDedicatedServerInterface
{
	GENERATED_BODY()
public:
	UFGServerSubsystem();

	// Begin UGameInstanceSubsystem interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End UGameInstanceSubsystem interface

	// Begin FTSTickerObjectBase interface
	bool Tick(float DeltaTime) override;
	// End FTSTickerObjectBase interface

	// Begin IFGDedicatedServerInterface
	virtual bool AttemptAutoLoadMostRecentSession() override;
	virtual UFGDedicatedServerGameModeComponentInterface* MakeGameModeComponent(AFGGameMode* GameMode) const override;
	virtual USessionMigrationSequence* CreateSession(const FCommonSessionCreationSettings& SessionCreationSettings) override;
	virtual FEncryptionKeyResponse GenerateEncryptionKey(const FString& EncryptionToken) override;
	virtual EEncryptionFailureAction IsEncryptionRequired() const override;
	// End IFGDedicatedServerInterface

	/** Returns true if we should encrypt join requests */
	bool ShouldEncryptJoinRequests() const;

	/** Retrieves the instance of the server subsystem for the specified world context */
	static UFGServerSubsystem* Get( const UObject* WorldContext );

	/** Returns the server API manager instance that can be used to register external handlers outside of DS subsystem. Useful for Mods. */
	FORCEINLINE UFGServerAPIManager* GetServerAPIManager() const { return mServerAPIManager; }

	/** Returns the name of the server set by the user */
	FString GetServerName() const;

	/** Returns true if the server is currently claimed (that is, has a valid name and an admin password set) */
	bool IsServerClaimed() const;

	/** Claims the server by updating the server name and admin password */
	void ClaimServer( const FString& ServerName, const FString& AdminPassword ) const;

	/** Updates the server name and saves it to the server settings */
	void SetServerName( const FString& ServerName ) const;

	/** Updates the name of the session to automatically load on server start and writes it to the server settings */
	void SetAutoLoadSessionName( const FString& SessionName ) const;

	/** Updates admin password the server has set. This will automatically invalidate all admin tokens */
	void SetAdminPassword( const FString& PlainTextPassword ) const;

	/** Updates client password the server has set. This will automatically invalidate all client tokens */
	void SetClientPassword( const FString& PlainTextPassword ) const;

	/** Returns privilege level that uses the password if the given plaintext password is in use, ignoring the given privilege level */
	EPrivilegeLevel CheckPasswordInUse( const FString& PlainTextPassword, EPrivilegeLevel IgnoredPrivilegeLevel = EPrivilegeLevel::None ) const;

	/** Updates the certificate data */
	void SetCertificateData( const FFGGeneratedCertificateData& NewCertificateData ) const;

	/** Generates an authentication token with the given privilege level for the given player. Used when claiming the servers and changing passwords */
	FServerAuthenticationToken GenerateAuthenticationToken( EPrivilegeLevel PrivilegeLevel, UE::Online::FAccountId Player ) const;
	
	/**
	 * Checks if the password provided matches any of the set passwords and generates an authentication token, valid only for this player at this address
	 */
	FServerAuthenticationToken AuthenticatePlayer( const FString& PlainTextPassword, EPrivilegeLevel MinimumTargetPrivilege, UE::Online::FAccountId Player ) const;

	/**
	 * If no admin password is set, an InitialAdmin privilege will be crated. Otherwise if there is an admin password but no join password is set,
	 * the player will be granted plain client privilege
	 */
	FServerAuthenticationToken AttemptPasswordlessLogin( EPrivilegeLevel MinimumPrivilegeLevel, UE::Online::FAccountId Player ) const;

	/**
	 * Cryptographically verifies the authenticity of the provided authentication token.
	 * IE: If this token was generated by this server for this player at this address
	 * 
	 * This will also take the currently set password into account based on the privilege level.
	 * This means that the previously issued token will be automatically invalidated if any of the relevant passwords change.
	 */
	bool VerifyAuthToken( const FServerAuthenticationToken& Cookie, UE::Online::FAccountId Player ) const;
	bool VerifyGameTicket( const FServerEntryToken& Ticket, UE::Online::FAccountId Player ) const;

	/** Generates a new GUID to be used as a seed for the Server API Tokens. That automatically invalidates all previously issued tokens. */
	void GenerateNewAPITokenSeed() const;

	/** Creates a new Server API Application token. This token cannot be used to join the game and is not bound to any PlayerID or IP Address. */
	FServerAuthenticationToken GenerateNewServerAPIToken() const;

	/** Creates a ticket that may be used to join the game. The ticket expires after 1 minute and another one must be generated. */
	FServerEntryToken IssueTicket(UE::Online::FAccountId Player, TSharedPtr<const FInternetAddr> PlayerAddr, EPrivilegeLevel Privilege) const;

	void SetServerFlag( EServerFlags ServerFlags );
	void ClearServerFlag( EServerFlags ServerFlags );

	void IncrementSubStateVersion( EServerSubStateId ServerSubStateId );
	
	FORCEINLINE EServerFlags GetServerFlags() const { return mServerFlags; }
	FORCEINLINE TMap<EServerSubStateId, uint16> GetServerSubStateVersions() const { return mServerSubStateVersions; }
	FORCEINLINE float GetAverageTickRate() const { return mAverageTickRate; }

	FString GetAutoLoadSessionName() const;
	FServerGameState GetServerGameState() const;
	FFGGeneratedCertificateData GetCertificateData() const;

	/** Returns true if we currently can re-claim the socket */
	bool CanReclaimSocket() const;
	/** If the Server Subsystem has claimed the NetDriver socket, stops the off main thread ping responder and transfers the socket back to the NetDriver */
	FUniqueSocket ReclaimServerQuerySocket();
	/** Re-claims the socket from the net driver and ticks it off main thread */
	void ClaimServerQuerySocket( FUniqueSocket&& NetDriverSocket );
public:
	static const TCHAR* EntryTicketOptionName;

	/**
	 * Can be bound to to check custom data received by the server from the client and perform additional
	 * compatibility checks on the client.
	 */
	FFGServerCheckHealthCheckCompatibility CheckHealthCheckCompatibility;
private:
	void OnUserOptionChanged( FString OptionName, FVariant OptionValue );
	void OnSaveCollectionChanged();
	void ShutdownServerQuerySocket();
	
	void SaveSettings() const;
	void LoadSettings();

	/** Generates a fingerprint to be used with an authentication token. */
	FString GenerateFingerprint( UE::Online::FAccountId Player, EPrivilegeLevel Privilege, TOptional<FDateTime> IssueDate = {} ) const;

	/** Takes the given data buffer as an input and returns it's hashed representation using the server secret */
	FString HashDataWithServerSecret( const TArray<uint8>& InData ) const;
	/** Raw version of the function above that allows picking a digest to be used and returns output in bytes */
	TArray<uint8> HashDataWithServerSecret( const struct evp_md_st* InMessageDigest, const TArray<uint8>& InData ) const;

	/** Creates a new password data */
	FFGStoredPasswordData CreatePasswordData( const FString& PlainTextPassword ) const;

	/** Validates previously set password data */
	bool ValidatePasswordData( const FFGStoredPasswordData& PasswordData, const FString& PlainTextPassword ) const;

	UPROPERTY()
	UFGServerAPIManager* mServerAPIManager;

	UPROPERTY()
	UFGServerControllerArray* mServerControllerArray;

	UPROPERTY()
	UFGServerSettings* mSettings;

	FString mCredentialsFile;

	EServerState mState = EServerState::Offline;
	EServerFlags mServerFlags;
	TMap<EServerSubStateId, uint16> mServerSubStateVersions;

	float mAverageTickRate = 0.0f;

	/** Thread used to tick the server query socket during the loading when the game thread is not processing packets */
	TUniquePtr<FRunnableThread> mServerQuerySocketLoadingThread;
	TUniquePtr<FFGOffThreadServerQuerySocket> mOffThreadServerQuerySocket;

	/** True if we are attempting to startup the game instance and the current travel should use GEngine->Browse instead of ServerTravel */
	bool mStartupTravelToMap{false};
	/** Result of the last hard map travel (e.g. GEngine::Browse). First hard travel is the startup of the server */
	bool mLastTravelToMapResult{false};
};

