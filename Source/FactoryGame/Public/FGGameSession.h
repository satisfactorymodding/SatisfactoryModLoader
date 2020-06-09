// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "Engine/World.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGOnlineSessionSettings.h"
#include "GameFramework/GameSession.h"
#include "FGGameSession.generated.h"

/**
 * @OSS: Responsibility:
 * Handle interaction on server and updating the SessionSettings (number of players connected and other things that need to be propagated the the matchmaking services)
 * Internally it converts it to presence and posts it to the hosts presence.
 * @todo DedicatedServers need to propagate this to a real matchmaking backend, as they have no presence to post that data to
 */
UCLASS()
class FACTORYGAME_API AFGGameSession : public AGameSession
{
	GENERATED_BODY()
	
public:
	AFGGameSession();

	/**
	 * Takes info from GameMode and GameState and sends it to the OSS to be published
	 * so players searching for games can see it.
	 */
	void UpdateGameSession();
	void SessionIdUpdated();
	

	//~Begin AActor interface
	virtual void Destroyed() override;
	//~End AActor interface


	//~Begin AGameSession interface
	virtual void InitOptions( const FString& options ) override;
	virtual void OnStartSessionComplete( FName inSessionName, bool wasSuccessful ) override;
	virtual void OnEndSessionComplete( FName InSessionName, bool bWasSuccessful ) override;
	virtual void PostLogin(APlayerController* newPlayer) override;
	virtual void NotifyLogout(const APlayerController* PC) override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual bool KickPlayer(APlayerController* kickedPlayer, const FText& kickReason) override;
	virtual void AddAdmin(APlayerController* AdminPlayer) override;
	virtual void RemoveAdmin(APlayerController* AdminPlayer) override;
	//~End AGameSession interface
	
	/** Returns true if the player is classified as admin */
	bool IsPlayerAdmin( const class APlayerController* player ) const;

	void AdminLogin( class APlayerController* player, const FString& hashedPassword );
	/**
	 * Get session settings from the specified world
	 */
	static FFGOnlineSessionSettings CreateSessionSettingsForPropagation( UWorld* forWorld, FString saveSessionName );
	static void SetTemporaryCSSSessionID(FString tempID);
	static void ClearTemporaryCSSSessionID();
	static FString GetCSSSessionID(UWorld* forWorld, const FString &saveSessionName);

	/** Set the visibility of the current session */
	void SetSessionVisibility( ESessionVisibility visibility );

	/** Get the visibility of the current session */
	FORCEINLINE ESessionVisibility GetSessionVisibility() const{ return mSessionVisibility; }

	/** Admin password option that's parsed from commandline */
	static const TCHAR* AdminPasswordOption;

	int32 GetNumPrivateConnections() const;
	int32 GetNumPublicConnections() const;
protected:
	/** Make sure we have a tutorial intro managere */
	UFUNCTION()
	void ListenForIntroSequenceUpdated();

	/** @return true if we allow login attempts from the specified PC, if he/she/it failed too many times in a row, then we might lock them out */
	bool AllowsLoginAttempts( const class APlayerController* PC ) const;

	/** Clear all failed login attempts of the user */
	void ClearFailTracking( const class APlayerController* PC );

	/** Game can become public after this, and the current visibility is applied */
	UFUNCTION()
	void IntroSequenceUpdated();

	/** Set a random admin password */
	void SetRandomAdminPassword();


	virtual void OnUpdateSessionComplete( FName sessionName, bool wasSuccessful );
private:
	/** Visibility of current game session */
	ESessionVisibility mSessionVisibility;

	/** Set to true when the game is allowed to switch to public */
	bool mGameCanBePublic;

	/** Timer holding the update */
	FTimerHandle mUpdateGameSessionTimerHandle;

	/** Handle for updating sessions */
	FDelegateHandle mOnUpdateSessionCompleteDelegate;

	/** Hashed admin password */
	FString mHashedAdminPassword;

	/** Used to keep track of players when they last tried to login and failed to detect brute force logins */
	UPROPERTY()
	TMap<class APlayerController*, double> mLastLoginFailTime;

	/** Used to keep track of how many times a player has failed to login in a row */
	UPROPERTY()
	TMap<class APlayerController*, int32> mFailedLoginCount;

	/** List of logged in admins */
	UPROPERTY()
	TArray<class APlayerController*> mLoggedInAdmins;

public:
	FORCEINLINE ~AFGGameSession() = default;
};
