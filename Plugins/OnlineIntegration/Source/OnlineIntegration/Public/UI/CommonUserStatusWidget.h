// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineIntegrationTypes.h"
#include "CommonUserStatusWidget.generated.h"

class ULocalUserInfo;
class ULocalUserInfoViewModel;
/**
 * 
 */
UCLASS(Blueprintable)
class ONLINEINTEGRATION_API UCommonUserStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	// UUserWidget interface
	virtual void NativeOnInitialized() override;
	// UUserWidget end

	void SetUserInfo(ULocalUserInfo* InUserInfo);

	UFUNCTION()
	void OnCommonUserInitializeComplete(ULocalUserInfo* InuUserInfo);

	UPROPERTY(EditAnywhere, Category="OnlineStatus")
	int32 PlayerIndex = 0;
};
