// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableText.h"
#include "FGEditableText.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEditableText : public UEditableText
{
	GENERATED_BODY()

public:
	// Set keyboard focus to this widget and select all text in it
	UFUNCTION( BlueprintCallable, Category = "Editable text" )
	void SetKeyboardFocusAndSelectAllText();
};
