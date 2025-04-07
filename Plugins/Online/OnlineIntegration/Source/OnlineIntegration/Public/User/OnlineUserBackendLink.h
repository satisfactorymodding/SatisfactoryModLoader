// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Async/Future.h"
#include "MVVMViewModelBase.h"
#include "Online/CoreOnline.h"
#include "OnlineIntegrationTypes.h"

#include "OnlineUserBackendLink.generated.h"

class UGameplayTagContainerViewModel;
class UOnlineIntegrationBackend;
class UOnlineUserInfo;

/**
 * The link between an online user and an online backend.
 * Also serves as a data cache for the respective user on the respective backend
 */
UCLASS()
class ONLINEINTEGRATION_API UOnlineUserBackendLink : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UOnlineUserBackendLink();

	[[nodiscard]] ECommonUserLoginStatus GetLoginStatus() const;
	[[nodiscard]] const FPlayerAvatar& GetAvatar() const;
	[[nodiscard]] const FString& GetNickname() const;
	[[nodiscard]] const FString& GetDisplayPictureURL() const;
	[[nodiscard]] UE::Online::FAccountId GetAccountId() const;
	[[nodiscard]] UOnlineIntegrationBackend* GetOnlineBackend() const;
	[[nodiscard]] UOnlineUserInfo* GetOnlineUser() const;

	const UGameplayTagContainerViewModel& GetTagContainer() const;
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOnlineIntegrationBackend> OnlineBackend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserLoginStatus LoginStatus;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineUserInfo> OnlineUser;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FPlayerAvatar Avatar;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString Nickname;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString DisplayPictureURL;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UGameplayTagContainerViewModel> LinkTags;

	UE::Online::FAccountId AccountId;
};
