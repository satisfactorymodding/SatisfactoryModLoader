// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

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

public:
	FORCEINLINE ~UFGEditableText() = default;
};
