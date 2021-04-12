// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnNativeConnectAccountsEvent( const FName currentPlatform, EEosAccountConnectionResult result );
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnConnectAccountsEvent();

	UFUNCTION()
    void OnNativeWaitingForEOSConnectLoginUpdated();

	UFUNCTION( BlueprintImplementableEvent )
	void OnWaitingForEOSConnectLoginUpdated( bool waiting );

	UFUNCTION( BlueprintCallable )
	void ContinueWithoutMultiplayer();

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

	UPROPERTY( BlueprintReadOnly )
	bool mIsWaitingForEOSConnectLoginResponse;

private: 
	UFGLocalPlayer* mLocalPlayer;

};
