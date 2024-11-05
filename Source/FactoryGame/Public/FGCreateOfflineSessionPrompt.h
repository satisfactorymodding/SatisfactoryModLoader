// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGPopupWidgetContent.h"
#include "OnlineInteractionHandlers.h"
#include "FGCreateOfflineSessionPrompt.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreateOfflineSessionPrompt : public UFGPopupWidgetContent
{
	GENERATED_BODY()
public:
	void SetDelegate( FOnlineSessionPromptResultKnown inDelegate );
protected:
	UFUNCTION(BlueprintCallable)
	void CancelSessionCreation();

	UFUNCTION(BlueprintCallable)
	void CreateOfflineSession();
	
	FOnlineSessionPromptResultKnown mOnResultKnownDelegate;
};
