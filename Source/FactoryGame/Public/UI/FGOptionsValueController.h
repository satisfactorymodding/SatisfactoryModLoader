// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGOptionsSettings.h"
#include "FGOptionsValueController.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOptionsValueController : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnRowHovered();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnRowUnhovered();

	void InitValueController( FOptionRowData optionRowData, UFGDynamicOptionsRow* parentOptionRow );

	UFUNCTION( BlueprintNativeEvent )
	bool IsPendingApply();

	UFUNCTION( BlueprintNativeEvent )
	bool IsPendingRestart();
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnInitValueController();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionValueUpdated();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	bool ShouldBeClickable();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionClicked();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionApplied();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void OnOptionReverted();

	UFUNCTION( BlueprintPure )
	FText GetCurrentSelectionText();

	UFUNCTION( BlueprintCallable )
	bool ChangeSelection( FText currentKey, bool incrementSelection );

protected:

	virtual void NativeConstruct() override;

	UFUNCTION( BlueprintPure, Category = "Option" )
	bool GetBoolOptionValue();

protected:

	UPROPERTY( BlueprintReadOnly )
	FOptionRowData mOptionRowData;
	
	UPROPERTY( BlueprintReadOnly )
	bool mIsDynamicOption;

	UPROPERTY( BlueprintReadOnly )
	UFGDynamicOptionsRow* mParentOptionRow;

};
