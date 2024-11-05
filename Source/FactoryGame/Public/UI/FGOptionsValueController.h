// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGOptionsSettings.h"
#include "UI/FGUserWidget.h" // <FL> [WuttkeP] Added callbacks for updating FFGKeyHints.
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

	// <FL> [WuttkeP] Added more callbacks for supporting several events with a controller.
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionIncreased();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionDecreased();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionValueReset();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnOptionAnalogValueUpdated( float AnalogValue );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnRowFocused();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void OnRowUnfocused();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	bool HandleResetValueDetails( UPARAM(ref) FFGKeyHint& KeyHint );

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	bool HandleActivateDetails( UPARAM(ref) FFGKeyHint& KeyHint );
	// </FL>

	// Called before an option is applied. So we can take action before option is applied 
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Meta = ( DisplayName=OnOptionPreApplied ) )
	void OnOptionApplied();

	// Called when we reset an option. This is the first thing to be called before the applied value is reset back to the default value
	// Gives the widget a chance to execute logic that is needed for the setting to be reset. Mostly useful for custom settings with custom widgets
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void OnOptionReverted();

	UFUNCTION( BlueprintPure )
	FText GetCurrentSelectionText();

	// Is this option allowed to be edited
	UFUNCTION( BlueprintPure )
	bool IsOptionEditable() const;
	
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

	UFUNCTION( BlueprintPure, Category = "Option" )
	FORCEINLINE TScriptInterface< class IFGOptionInterface > GetOptionInterface() const { return mOptionInterface; } 

protected:

	UPROPERTY( BlueprintReadOnly, BlueprintGetter = GetOptionRowData )
	FOptionRowData mOptionRowData;

	UPROPERTY( Transient, BlueprintReadOnly )
	UFGUserSetting* mUserSetting;
	
	UPROPERTY( BlueprintReadOnly )
	bool mIsDynamicOption;

	UPROPERTY( BlueprintReadOnly )
	UFGDynamicOptionsRow* mParentOptionRow;

	UPROPERTY( Transient )
	TScriptInterface< class IFGOptionInterface > mOptionInterface;

};
