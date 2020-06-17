// Copyright 2016-2020 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGPopupWidgetContent.h"
#include "FGLocalPlayer.h"
#include "FGPopupConnectAccounts.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPopupConnectAccounts : public UFGPopupWidgetContent
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

	/** UFUNCTION so we can use it with a delegate */
	UFUNCTION()
	void OnNativeConnectAccountsEvent( const FName currentPlatform, EEosAccountConnectionResult result );
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnConnectAccountsEvent();

	UFUNCTION( BlueprintCallable )
	void ConnectAccount();
	
	UFUNCTION( BlueprintCallable )
	void LoginAndConnectAccount( );

	UFUNCTION( BlueprintCallable )
	void CreateNewAccountConnection();

	UFUNCTION( BlueprintCallable )
	void ContinueWithoutConnectingAccount();

	UFUNCTION( BlueprintCallable )
	void LoginAndConnectOtherEpicAccount();

	UFUNCTION( BlueprintCallable )
	void LogoutEpicAccountAndContinue();

	UFUNCTION( BlueprintCallable )
	void ContinueWithAndHookUpSteamToEOSAfterEpicLogout();

	UFUNCTION( BlueprintCallable )
	void LogOutEpicAndCreateNewAccountConnection();

	UPROPERTY( BlueprintReadOnly )
	FName mCurrentPlatform;

	UPROPERTY( BlueprintReadWrite )
	EEosAccountConnectionResult mConnectionResult;

private: 
	UFGLocalPlayer* mLocalPlayer;


public:
	FORCEINLINE ~UFGPopupConnectAccounts() = default;
};
