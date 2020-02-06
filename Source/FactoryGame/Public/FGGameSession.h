// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGOnlineSessionSettings.h"
#include "GameFramework/GameSession.h"
#include "FGGameSession.generated.h"

/**
 * 
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

	//~Begin AActor interface
	virtual void Destroyed() override;
	//~End AActor interface


	//~Begin AGameSession interface
	virtual void InitOptions( const FString& options );
	virtual void OnStartSessionComplete( FName inSessionName, bool wasSuccessful ) override;
	virtual void OnEndSessionComplete( FName InSessionName, bool bWasSuccessful ) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void NotifyLogout(const APlayerController* PC) override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual bool KickPlayer(APlayerController* kickedPlayer, const FText& kickReason) override;
	//~End AGameSession interface
	
	/**
	 * Get session settings from the specified world
	 */
	static FFGOnlineSessionSettings GetSessionSettings( UWorld* forWorld, FString sessionName );

	/** Set the visibility of the current session */
	void SetSessionVisibility( ESessionVisibility visibility );

	/** Get the visibility of the current session */
	FORCEINLINE ESessionVisibility GetSessionVisibility() const{ return mSessionVisibility; }
protected:
	/** Make sure we have a tutorial intro managere */
	UFUNCTION()
	void ListenForIntroSequenceUpdated();

	/** Game can become public after this, and the current visibility is applied */
	UFUNCTION()
	void IntroSequenceUpdated();

	int32 GetNumPrivateConnections() const;
	int32 GetNumPublicConnections() const;

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
};
