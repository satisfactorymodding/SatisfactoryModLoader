// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "SessionMemberInformation.generated.h"

class UOnlineUserInfo;

/**
 * Encapsulates a session member's information. Essentially, it connects a player state object with it's online user info, if the former is available.
 * Online user info may be missing if a certain backend denies access to user information for this member which can happen when for example the member is not a
 * friend of the local user. And so this class is required so we can have meaningful member information in all cases. 
 */
UCLASS()
class ONLINEINTEGRATION_API USessionMemberInformation : public UMVVMViewModelBase
{
	GENERATED_BODY()
	friend class USessionInformation;
public:

	APlayerState* GetPlayerState() const
	{
		return PlayerState;
	}

	UOnlineUserInfo* GetOnlineUserInfo() const
	{
		return OnlineUserInfo;
	}

	// Do not call these setters from the outside, they are meant for internal use only.
	void SetPlayerState(APlayerState* InPlayerState);
	void SetOnlineUserInfo(UOnlineUserInfo* InOnlineUserInfo);
	void SetPlayingPlatformName(const FName& InPlayingPlatformName); // <FL> [TranN] See FGPlayerState::mPlayingPlatformName
	void SetPlatformAvatarURL(const FString& InPlatformAvatarURL);	// <FL> [MartinC] See FGPlayerState::mPlatformAvatarURL

	UFUNCTION(BlueprintCallable)
	void ShowProfileUI();
protected:
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Session Member")
	TObjectPtr<class APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Session Member")
	TObjectPtr<UOnlineUserInfo> OnlineUserInfo;

	// <FL> [TranN] See FGPlayerState::mPlayingPlatformName
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Session Member")
	FName PlayingPlatformName;
	// </FL>

	// <FL> [MartinC] See FGPlayerState::mPlatformAvatarURL
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "Session Member")
	FString PlatformAvatarURL;
	// </FL>
};
