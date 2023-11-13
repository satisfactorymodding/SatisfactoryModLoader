// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFrontendStateComponent.h"
#include "Blueprint/UserWidget.h"
#include "FGOnlineStartupScreen.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOnlineStartupScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	// Begin UUserWidget interface
	virtual void NativeConstruct() override;
	// End UUserWidget interface
	
	void Native_PromptUserForOnlineIntegrationMode( TPromise<EOnlineIntegrationMode>&& promise );

	void Native_ProgressUpdate( FText descriptionText );
protected:
	UFUNCTION( BlueprintImplementableEvent, Category = Online )
	void PromptUserForOnlineIntegrationMode();

	UFUNCTION( BlueprintImplementableEvent, Category = Online )
	void OnProgressUpdate( const FText& descriptionText );

	UFUNCTION( BlueprintCallable, Category = Online )
	void OnlineIntegrationModeSelected( EOnlineIntegrationMode onlineIntegrationMode );

private:
	TOptional<TPromise<EOnlineIntegrationMode>> mOnlineIntegrationModePromise; 
};
