// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "FGUserWidget.h" // <FL> [AZimmermann] Changed to UFGUserWidget
#include "FGOptionsSettings.h"
#include "Settings/FGUserSetting.h"
#include "FGDynamicOptionsRow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnOptionRowHovered, UFGDynamicOptionsRow*, optionRow );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnOptionRowUnhovered, UFGDynamicOptionsRow*, optionRow );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnOptionSlotButtonFocusChanged, bool, hasFocus );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnOptionBackPressed );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGDynamicOptionsRow : public UFGUserWidget // <FL> [AZimmermann] Changed to UFGUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void InitOptionRow( UFGUserSetting* userSetting, TScriptInterface<IFGOptionInterface> optionInterface );

	UFUNCTION( BlueprintCallable, Category = "Option" )
	void AddSubOption( UFGDynamicOptionsRow* dynamicOptionsRow );

	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE UFGUserSetting* GetUserSetting() const { return mUserSetting; }

	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE UFGOptionsValueController* GetValueControllerWidget() const { return mValueControllerWidget; }

	UFUNCTION( BlueprintPure, Category = "Option" )
	bool IsPendingApply() const;

	UFUNCTION( BlueprintPure, Category = "Option" )
	bool IsPendingRestart() const;

	UFUNCTION( BlueprintImplementableEvent, Category = "Option" )
	void OnOptionRowInit();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option" )
	void OnOptionValueUpdated();

	// Called before an option is applied. So we can take action before option is applied 
	UFUNCTION( BlueprintCallable, Category = "Option", Meta = ( DisplayName=OnOptionPreApplied ) )
	void OnOptionApplied();

	// Called when we reset an option. This is the first thing to be called before the applied value is reset back to the default value
	// Gives the widget a chance to execute logic that is needed for the setting to be reset. Mostly useful for custom settings with custom widgets
	UFUNCTION( BlueprintCallable, Category = "Option" )
	void OnOptionReverted();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option" )
	void UpdatePendingIconsVisibilty();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Option" )
	void OnSubOptionsUpdated();

	UFUNCTION( BlueprintCallable, Category = "Option" )
	FORCEINLINE TArray< UFGDynamicOptionsRow* > GetSubOptions() { return mSubOptions; }

	UFUNCTION( BlueprintPure, Category = "Option" )
	FORCEINLINE bool GetSubOptionsVisibility() const { return mSubOptionsVisibility; }
	
	UFUNCTION( BlueprintCallable, Category = "Option" )
	void SetSubOptionsVisibility( bool newVisibilty ) { mSubOptionsVisibility = newVisibilty; }

	UFUNCTION()
	void SetWidgetLocator( FSettingsWidgetLocationDescriptor widgetLocator ) { mWidgetLocator = widgetLocator; };

protected:
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnOptionRowHovered mOnOptionRowHovered;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnOptionRowUnhovered mOnOptionRowUnhovered;
	
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnOptionBackPressed mOnOptionRowBackPressed;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnOptionSlotButtonFocusChanged mOnOptionSlotButtonFocusChanged;

	UPROPERTY( Transient, BlueprintReadOnly )
	FSettingsWidgetLocationDescriptor mWidgetLocator;
	
private:
	UPROPERTY( Transient )
	TObjectPtr<UFGUserSetting> mUserSetting;

	UPROPERTY( Transient )
	TScriptInterface<IFGOptionInterface> mOptionInterface;
	
	UPROPERTY( Transient )
	TSubclassOf<UFGOptionsValueController> mWidgetOptionClass;

	UPROPERTY( Transient )
	TObjectPtr<UFGOptionsValueController> mValueControllerWidget;

	UPROPERTY( Transient )
	TArray< TObjectPtr<UFGDynamicOptionsRow> > mSubOptions;

	bool mSubOptionsVisibility{false};
};
