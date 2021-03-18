// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGWindow.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGWindow : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Returns the close button in the title label */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	UUserWidget* GetCloseButton();
};
