// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGOptionsSettings.h"
#include "UI/FGUserWidget.h" // <FL> [WuttkeP] Added callbacks for updating FFGKeyHints.
#include "FGOptionsValueController.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOptionsValueController : public UFGUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnRowHovered();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnRowUnhovered();

	void InitValueController( class UFGUserSetting* userSetting, UFGDynamicOptionsRow* parentOptionRow, TScriptInterface< class IFGOptionInterface > optionInterface );

	UFUNCTION( BlueprintNativeEvent, Category = "Option Controller" )
	bool IsPendingApply();

	UFUNCTION( BlueprintNativeEvent, Category = "Option Controller" )
	bool IsPendingRestart();
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Option Controller" )
	void OnInitValueController();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionValueUpdated();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Option Controller" )
	bool ShouldBeClickable();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionClicked();

	// <FL> [WuttkeP] Added more callbacks for supporting several events with a controller.
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionIncreased();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionDecreased();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionValueReset();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionAnalogValueUpdated( float AnalogValue );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnRowFocused();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnRowUnfocused();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Option Controller" )
	bool HandleResetValueDetails( UPARAM(ref) FFGKeyHint& KeyHint );

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Option Controller" )
	bool HandleActivateDetails( UPARAM(ref) FFGKeyHint& KeyHint );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionSelectInputValueCustom();
	// </FL>

	// Called before an option is applied. So we can take action before option is applied 
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option Controller", Meta = ( DisplayName=OnOptionPreApplied ) )
	void OnOptionApplied();

	// Called when we reset an option. This is the first thing to be called before the applied value is reset back to the default value
	// Gives the widget a chance to execute logic that is needed for the setting to be reset. Mostly useful for custom settings with custom widgets
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Option Controller" )
	void OnOptionReverted();

	// Is this option allowed to be edited
	UFUNCTION( BlueprintPure, Category = "Option Controller" )
	bool IsOptionEditable() const;
	
	// when true the highlight should be on the option slot (ie OptionsSlider) instead of the whole OptionRow
	UFUNCTION( BlueprintPure, Category = "Option Controller" )
	bool ShouldFocusOptionSlotToEdit() const;

	/** Returns the string ID for the option represented by this selector */
	UFUNCTION( BlueprintPure, Category = "Option Controller" )
	FString GetSettingIdentifier() const;

	UFUNCTION( BlueprintPure, Category = "Option Controller" )
	FORCEINLINE TScriptInterface<IFGOptionInterface> GetOptionInterface() const { return mOptionInterface; }

	UFUNCTION( BlueprintPure, Category = "Option Controller" )
	FORCEINLINE UFGUserSetting* GetUserSetting() const { return mUserSetting; }

	/** Returns the value of this option as a boolean, if this option value is of type boolean */
	UFUNCTION( BlueprintPure, Category = "Option Controller" )
	bool GetBoolOptionValue() const;

	/** Legacy functions used by option selector widget to select int values */
	UFUNCTION( BlueprintPure, Category = "Option Controller|Legacy" )
	FText LegacyIntValueSelector_GetCurrentSelectionText() const;
	UFUNCTION( BlueprintCallable, Category = "Option Controller|Legacy" )
	bool LegacyIntValueSelector_ChangeSelection( const FText& currentKey, bool incrementSelection );
protected:
	// Begin UUserWidget interface
	virtual void NativeConstruct() override;
	// End UUserWidget interface

protected:
	UPROPERTY( Transient )
	TScriptInterface<IFGOptionInterface> mOptionInterface;

	UPROPERTY( Transient, BlueprintReadOnly )
	TObjectPtr<UFGUserSetting> mUserSetting;

	UPROPERTY( BlueprintReadOnly )
	TObjectPtr<UFGDynamicOptionsRow> mParentOptionRow;
};
