// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGControllerDragWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGControllerDragWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION( BlueprintImplementableEvent )
	void HandleFocusChanged();

	UFUNCTION( BlueprintImplementableEvent )
	void DragStarted();

	UFUNCTION( BlueprintImplementableEvent )
	void DragEnded();

private:
	void HandleSlateFocusChanging(const FFocusEvent& FocusEvent, const FWeakWidgetPath& OldFocusedWidgetPath, const TSharedPtr<SWidget>& OldFocusedWidget, const FWidgetPath& NewFocusedWidgetPath, const TSharedPtr<SWidget>& NewFocusedWidget);

	FDelegateHandle mFocusChangeDelegate;
};
