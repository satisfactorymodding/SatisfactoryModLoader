// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGGameSession.h"
#include "OnlineIntegrationTypes.h"
#include "FGGameSessionOnline.generated.h"

class UFGSessionInformationModel;
/**
 * @OSS: Responsibility:
 * Handle interaction on server and updating the SessionSettings (number of players connected and other things that need to be propagated
 * the the matchmaking services) Internally it converts it to presence and posts it to the hosts presence.
 */
UCLASS()
class FACTORYGAME_API AFGGameSessionOnline : public AFGGameSession
{
	GENERATED_BODY()
public:
	AFGGameSessionOnline();
	
	/**
	 * Takes info from GameMode and GameState and sends it to the OSS to be published
	 * so players searching for games can see it.
	 */
	UE_DEPRECATED( 5.3, "Game session updates will be event driven and this function will be removed alltogether." )
	void UpdateGameSession();

	// Begin AActor interface
	virtual void Destroyed() override;
	// End AActor interface

	// Begin AGameSession interface
	virtual void InitOptions( const FString& options ) override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual void PostLogin(APlayerController* newPlayer) override;
	virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdRepl& UniqueId, bool bWasFromInvite) override;
	virtual void UnregisterPlayer(const APlayerController* ExitingPlayer) override;
	virtual void UnregisterPlayer(FName InSessionName, const FUniqueNetIdRepl& UniqueId) override;
	// End AGameSession interface

protected:
	/** Make sure we have a tutorial intro manager */
	UFUNCTION()
	void ListenForIntroSequenceUpdated();

	/** Game can become public after this, and the current visibility is applied */
	UFUNCTION()
	void IntroSequenceUpdated();

	UPROPERTY()
	TObjectPtr<UFGSessionInformationModel> mSessionInformation;

private:
	/** Set to true when the game is allowed to switch to public */
	bool mGameCanBePublic;
};
