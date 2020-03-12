// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Blueprint/UserWidget.h"
#include "FGButtonWidget.generated.h"

/**
 * Base class for a widget that should be a button ( regular button, checkbox etc )
 */
UCLASS()
class FACTORYGAME_API UFGButtonWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/** When this widgets receives focus */
	virtual FReply NativeOnFocusReceived( const FGeometry& InGeometry, const FFocusEvent& InFocusEvent );

	/** Sets our internal button that will be used for focus handling */
	UFUNCTION( BlueprintCallable, Category = "Interaction" )
	void SetButton( class UButton* inButton );
private:
	/** Reference to the UButton we have internally */
	class UButton* mInternalButton;

public:
	FORCEINLINE ~UFGButtonWidget() = default;
};
