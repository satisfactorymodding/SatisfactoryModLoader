// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGOnScreenCallWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOnScreenCallWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION( BlueprintCallable, Category = "Call" )
	void AnswerCall();

	UPROPERTY( BlueprintReadWrite )
	TSubclassOf<class UFGAudioMessage> mMessageClass;
};
