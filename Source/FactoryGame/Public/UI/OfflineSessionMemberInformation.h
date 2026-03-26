// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "SessionMemberInformation.h"
#include "../Online/PlayerInfoCache.h"
#include "OfflineSessionMemberInformation.generated.h"

UCLASS()
class FACTORYGAME_API UOfflineSessionMemberInformation : public USessionMemberInformation
{
	GENERATED_BODY()
public:
	// Begin USessionMemberInformation interface
	virtual void ShowProfileUI() override;
	// End USessionMemberInformation interface

	/** Initializes the session member info from the player info given */
	UFUNCTION( BlueprintCallable, Category = "Offline Session Member" )
	void InitValues(const FCachedPlayerInfo& cachedPlayerInfo);

	UFUNCTION( BlueprintCallable, Category = "Offline Session Member", meta = ( DeprecatedFunction, DeprecationMessage = "Use Preferred Platform Info" ) )
	FORCEINLINE FString GetPlayerName() { return mPreferredPlatformInfo.PlayerName; }

	UFUNCTION( BlueprintCallable, Category = "Offline Session Member", meta = ( DeprecatedFunction, DeprecationMessage = "Use Preferred Platform Info" ) )
	FORCEINLINE FString GetDisplayPictureURL() { return mPreferredPlatformInfo.DisplayPictureURL; }
	
	UFUNCTION( BlueprintCallable, Category = "Offline Session Member", meta = ( DeprecatedFunction, DeprecationMessage = "Use Preferred Platform Info" ) )
	FORCEINLINE FCachedPlayerPlatformInfo GetCachedEpicPlatformInfo() { return mEpicPlatformInfo; }

	/** Returns cached epic user ID string if this user has epic account connected */
	UFUNCTION( BlueprintCallable, Category = "Offline Session Member" )
	FString GetCachedEpicUserIdString();
public:
	/** All player identities cached for this session member */
	UPROPERTY( BlueprintReadOnly, Category = "Offline Session Member" )
	FCachedPlayerInfo mCachedPlayerInfo;

	/** Player identity the player was last seen playing with, or a fallback identity otherwise */
	UPROPERTY( BlueprintReadOnly, Category = "Offline Session Member" )
	FCachedPlayerPlatformInfo mLastSeenPlatformInfo;

	/** Platform information that is preferred for the local user (e.g. preferably from the same platform as the local user primary backend) */
	UPROPERTY( BlueprintReadOnly, Category = "Offline Session Member" )
	FCachedPlayerPlatformInfo mPreferredPlatformInfo;

	/** Platform information for the EGS platform backend (if available) */
	UPROPERTY( BlueprintReadOnly, Category = "Offline Session Member" )
	FCachedPlayerPlatformInfo mEpicPlatformInfo;
};
