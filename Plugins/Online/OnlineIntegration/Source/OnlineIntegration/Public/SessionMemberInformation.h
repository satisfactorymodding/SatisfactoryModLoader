// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Online/CoreOnline.h"
#include "SessionMemberInformation.generated.h"

class APlayerState;
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

	UFUNCTION(BlueprintCallable)
	APlayerState* GetPlayerState() const
	{
		return PlayerState;
	}

	UFUNCTION(BlueprintCallable)
	UOnlineUserInfo* GetOnlineUserInfo() const
	{
		return OnlineUserInfo;
	}

	/**
	 * Account ID for the platform the player is currently logged in on (main backend)
	 * This is different from PlayerState UniqueId which will be the cross play ID
	 * This information is only available when player state is provided and is game-defined
	 */
	FORCEINLINE UE::Online::FAccountId GetPlatformAccountId() const
	{
		return PlatformAccountId;
	}

	// Do not call these setters from the outside, they are meant for internal use only.
	void SetPlayerState(APlayerState* InPlayerState);
	void SetOnlineUserInfo(UOnlineUserInfo* InOnlineUserInfo);

	UFUNCTION(BlueprintCallable)
	virtual void ShowProfileUI();
protected:
	void SetPlatformAvatarURL(const FString& InPlatformAvatarURL);
	void SetPlayingPlatformName(const FName& InPlayingPlatformName);
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Session Member")
	TObjectPtr<class APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Session Member")
	TObjectPtr<UOnlineUserInfo> OnlineUserInfo;

	UE::Online::FAccountId PlatformAccountId;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Session Member")
	FName PlayingPlatformName;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = "Session Member")
	FString PlatformAvatarURL;
};
