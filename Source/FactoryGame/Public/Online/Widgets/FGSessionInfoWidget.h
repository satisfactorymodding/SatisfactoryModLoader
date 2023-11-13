// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Blueprint/UserWidget.h"
#include "CommonSessionTypes.h"
#include "CoreMinimal.h"
#include "FGOnlineSessionSettings.h"
#include "FGSessionInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGSessionInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetSession(const FCommonSession& session);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnSessionUpdate(const FFGOnlineSessionSettings& Session);

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	FCommonSession mSession;
};
