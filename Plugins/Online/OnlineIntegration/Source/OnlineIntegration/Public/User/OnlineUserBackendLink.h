// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	
	[[nodiscard]] const FPlayerAvatar& GetAvatar() const;
	[[nodiscard]] const FString& GetNickname() const;
	[[nodiscard]] UE::Online::FAccountId GetAccountId() const;
	[[nodiscard]] UOnlineIntegrationBackend* GetOnlineBackend() const;
	[[nodiscard]] UOnlineUserInfo* GetOnlineUser() const;

	const UGameplayTagContainerViewModel& GetTagContainer() const;
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOnlineIntegrationBackend> OnlineBackend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineUserInfo> OnlineUser;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FPlayerAvatar Avatar;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString Nickname;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UGameplayTagContainerViewModel> LinkTags;

	UE::Online::FAccountId AccountId;
};
