// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "FGUserWidget.h" // <FL> [AZimmermann] Changed to UFGUserWidget
#include "FGOptionsSettings.h"
#include "Settings/FGUserSetting.h"
#include "FGDynamicOptionsRow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnOptionRowHovered, UFGDynamicOptionsRow*, optionRow );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnOptionRowUnhovered, UFGDynamicOptionsRow*, optionRow );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGDynamicOptionsRow : public UFGUserWidget // <FL> [AZimmermann] Changed to UFGUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void InitOptionRow( FOptionRowData optionRowData, TSubclassOf<class UFGOptionsValueController> widgetOptionClass, TScriptInterface< class IFGOptionInterface > optionInterface );
	void InitOptionRow( class UFGUserSetting* userSetting, TScriptInterface< class IFGOptionInterface > optionInterface );
	
	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE EOptionCategory GetOptionCategory() const { return EOptionCategory::OC_Gameplay; }

	UFUNCTION( BlueprintCallable, Category = "Option" )
	void AddSubOption( UFGDynamicOptionsRow* dynamicOptionsRow );
	
	UFUNCTION( Blueprintpure, Category = "Option", meta=(DeprecatedFunction,DeprecationMessage = "DEPRECATED Use GetUserSetting instead") )
	FORCEINLINE FOptionRowData GetOptionRowData() const { return mUserSetting ? mUserSetting->ToOptionRowData() : mOptionRowData; }

	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE UFGUserSetting* GetUserSetting() const { return mUserSetting; }

	UFUNCTION( Blueprintpure, Category = "Option" )
	FORCEINLINE UFGOptionsValueController* GetValueControllerWidget() const { return mValueControllerWidget; }

	UFUNCTION( BlueprintPure, Category = "Option" )
	bool IsPendingApply();

	UFUNCTION( BlueprintPure, Category = "Option" )
	bool IsPendingRestart();

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

	UFUNCTION( BlueprintImplementableEvent, Category = "Option" )
	void OnSubOptionsUpdated();

	UFUNCTION( BlueprintCallable, Category = "Option" )
	FORCEINLINE TArray< UFGDynamicOptionsRow* > GetSubOptions() { return mSubOptions; }

	UFUNCTION( BlueprintPure, Category = "Option" )
	FORCEINLINE bool GetSubOptionsVisibility() { return mSubOptionsVisibility; }
	
	UFUNCTION( BlueprintCallable, Category = "Option" )
	void SetSubOptionsVisibility( bool newVisibilty ) { mSubOptionsVisibility = newVisibilty; }

protected:
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnOptionRowHovered mOnOptionRowHovered;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnOptionRowUnhovered mOnOptionRowUnhovered;
	
private:

	FOptionRowData mOptionRowData;

	UPROPERTY( Transient )
	UFGUserSetting* mUserSetting;

	EOptionType mOptionType;

	UPROPERTY( Transient )
	TScriptInterface< class IFGOptionInterface > mOptionInterface;
	
	UPROPERTY( Transient )
	TSubclassOf<class UFGOptionsValueController> mWidgetOptionClass;

	UPROPERTY( Transient )
	UFGOptionsValueController* mValueControllerWidget;

	UPROPERTY( Transient )
	TArray< UFGDynamicOptionsRow* > mSubOptions;

	bool mSubOptionsVisibility;
	
};
