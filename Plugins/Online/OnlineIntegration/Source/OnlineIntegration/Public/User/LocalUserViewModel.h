// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVMViewModelContextResolver.h"

#include "LocalUserViewModel.generated.h"

class ULocalPlayer;
class ULocalUserInfo;

/**
 * A utility model that can keep track of a local user. Can be used even if the local user does not exist yet and it will track its creation automatically.
 */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API ULocalUserViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SetLocalPlayer(ULocalPlayer* InLocalPlayer);
	
protected:
	UFUNCTION()
	void LocalUserCreated(ULocalUserInfo* NewLocalUser);

	/**
	 * The local user gets updated when @LocalPlayer is changed or when created/
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<ULocalUserInfo> LocalUser;

	/**
	 * The local player that we want to access the equivalent user info for.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ULocalPlayer> LocalPlayer;

	FDelegateHandle LocalUserCreatedDelegateHandle;
};
