// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	void InitValueController( FOptionRowData optionRowData, UFGDynamicOptionsRow* parentOptionRow, TScriptInterface< class IFGOptionInterface > optionInterface );
	
	void InitValueController( class UFGUserSetting* userSetting, UFGDynamicOptionsRow* parentOptionRow, TScriptInterface< class IFGOptionInterface > optionInterface );

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
	
	bool CanSelectIndex( int32 newIndex );

	UFUNCTION( BlueprintCallable )
	bool ChangeSelection( FText currentKey, bool incrementSelection );

	FString GetSettingIndentifier() const;

	TArray<FIntegerSelection> GetIntegerSelectionValues() const;
	
	bool GetBlockLastIndexFromManualSelection() const;
	
	EOptionType GetOptionType() const;

protected:

	virtual void NativeConstruct() override;

	UFUNCTION( BlueprintPure, Category = "Option" )
	bool GetBoolOptionValue();

	UFUNCTION(BlueprintGetter)
	FOptionRowData GetOptionRowData() const;

protected:

	UPROPERTY( BlueprintReadOnly, BlueprintGetter = GetOptionRowData )
	FOptionRowData mOptionRowData;

	UPROPERTY( Transient )
	UFGUserSetting* mUserSetting;
	
	UPROPERTY( BlueprintReadOnly )
	bool mIsDynamicOption;

	UPROPERTY( BlueprintReadOnly )
	UFGDynamicOptionsRow* mParentOptionRow;

	UPROPERTY( Transient )
	TScriptInterface< class IFGOptionInterface > mOptionInterface;

};
