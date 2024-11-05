// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "FGGameSession.generated.h"

/**
 * Base Game Session class for both Dedicated Servers and Online games
 * Handles common functionality such as not destroying pawns when leaving, granting admin privileges and so on.
 */
UCLASS()
class FACTORYGAME_API AFGGameSession : public AGameSession
{
	GENERATED_BODY()
public:
	AFGGameSession();

	// Begin AGameSession interface
	virtual void PostLogin(APlayerController* newPlayer) override;
	virtual void NotifyLogout(const APlayerController* PC) override;
	virtual bool KickPlayer(APlayerController* kickedPlayer, const FText& kickReason) override;
	virtual void AddAdmin(APlayerController* AdminPlayer) override;
	virtual void RemoveAdmin(APlayerController* AdminPlayer) override;
	// End AGameSession interface
	
	/** Returns true if the player is classified as admin */
	bool IsPlayerAdmin( const class APlayerController* player ) const;
protected:
	/** List of logged in admins */
	UPROPERTY()
	TArray<class APlayerController*> mLoggedInAdmins;
};
