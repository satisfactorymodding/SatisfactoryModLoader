// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonSessionTypes.h"
#include "MVVMViewModelBase.h"
#include "OnlineFriendTypes.h"
#include "Styling/SlateBrush.h"
#include "OnlineIntegrationViewModels.generated.h"

UCLASS(NotBlueprintable, BlueprintType)
class ONLINEINTEGRATION_API UOnlineSessionInfoViewModel: public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetSessionHandle(const FCommonSession& InSessionHandle, class UCommonSessionSubsystem* SessionSubsystem);

	UFUNCTION(BlueprintCallable)
	void InviteFriend(const UOnlineFriend* Friend);

	UFUNCTION(BlueprintCallable)
	void InvitePressed();

protected:
	void OnSessionUpdateReceived(const UE::Online::FSessionUpdate &SessionUpdate, TSharedRef<const UE::Online::ISession> Session);

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonSessionJoinPolicy JoinPolicy = ECommonSessionJoinPolicy::InviteOnly;

	// UPROPERTY(BlueprintReadOnly, FieldNotify)
	// int32 OpenConnections = 0;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	bool IsOnlineSession = false;

private:
	UPROPERTY()
	FCommonSession SessionHandle;
};

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineModelConversionFunctionLibrary: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category=OnlineIntegrationConversionFunctions)
	static FSlateBrush MakeBrushFromPlayerAvatar(const struct FPlayerAvatar& PlayerAvatar);
};
