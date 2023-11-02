// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGOptionsSettings.h"
#include "Misc/Variant.h"
#include "UObject/Interface.h"
#include "FGOptionInterface.generated.h"

/** Since FVariants isn't supported in blueprint we need two delegates. Both delegates are supported in native code. */
DECLARE_DYNAMIC_DELEGATE_OneParam( FOptionUpdated, FString, updatedCvar );
DECLARE_DELEGATE_TwoParams( FOnOptionUpdated, FString, FVariant );

UINTERFACE( MinimalAPI, BlueprintType, NotBlueprintable )
class UFGOptionInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * Interface for all settings in game including Options Menu and Advanced Game User Settings (Game Modes).
 */
class FACTORYGAME_API IFGOptionInterface
{
	GENERATED_BODY()

public:
	
	/** Returns the applied value for setting with the given strID */
	virtual FVariant GetOptionValue( const FString& strId ) const = 0;
	/** Returns the applied value for setting with the given strID. If no setting with strId is found default value is returned. */
	virtual FVariant GetOptionValue( const FString& strId, const FVariant& defaultValue ) const = 0;
	/** Returns the current display value for setting with the given strID. This is the value we show in settings menus */
	virtual FVariant GetOptionDisplayValue( const FString& strId ) const = 0;
	/** Returns the current display value for setting with the given strID. If no setting with strId is found default value is returned */
	virtual FVariant GetOptionDisplayValue( const FString& strId, const FVariant& defaultValue ) const = 0;
	/** Sets the pending value of the setting with the given StrId to the given value */
	virtual void SetOptionValue( const FString& strId, const FVariant& value ) = 0;
	/** Force set is used when we just want to update a value and not go through the whole apply cycle. This will trigger option updated calls */
	virtual void ForceSetOptionValue( const FString& strId, const FVariant& value, const UObject* instigator ) = 0;
	/** Listen for changes for the setting with the given strId */
	virtual void SubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) = 0;
	/** Stop Listening for changes for the setting with the given strId */ 
	virtual void UnsubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) = 0;
	/** Is the default value applied or have we changed this option */
	virtual bool IsDefaultValueApplied( const FString& strId ) const = 0;
	/** Are we allowed to change this option */
	virtual bool IsOptionEditable( const FString& strId ) const;

	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void ApplyChanges() = 0;
	
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void ResetAllSettingsToDefault() = 0;

	/** Resets all settings in the given categories. If subCategory is null only the main category will be reset. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void ResetAllSettingsInCategory( TSubclassOf< class UFGUserSettingCategory > category, TSubclassOf< class UFGUserSettingCategory > subCategory ) = 0;
	
	/** Get the currently active option value for a bool */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetBoolOptionValue( const FString& cvar ) const = 0;

	/** Get the current UI value for a bool. Doesn't always match the active value. Should only be used in the options menu. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetBoolUIDisplayValue( const FString& cvar ) const = 0;

	/** Set a option value for a bool, will need to be applied to take affect and/or get saved */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SetBoolOptionValue( const FString& cvar, bool value ) = 0;

	/** Get the currently active option value for an integer */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual int32 GetIntOptionValue( const FString& cvar ) const = 0;

	/** Get the current UI value for an integer. Doesn't always match the active value. Should only be used in the options menu. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual int32 GetIntUIDisplayValue( const FString& cvar ) const = 0;

	/** Set the option value for an integer, will need to be applied to take affect and/or get saved */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SetIntOptionValue( const FString& cvar, int32 newValue ) = 0;
	
	/** Get the option value for a float */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual float GetFloatOptionValue( const FString& cvar ) const = 0;

	/** Get the current UI value for an float. Doesn't always match the active value. Should only be used in the options menu. */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual float GetFloatUIDisplayValue( const FString& cvar ) const = 0;

	/** Set the option value for an float, will need to be applied to take affect and/or get saved */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SetFloatOptionValue( const FString& cvar, float newValue ) = 0;

	/** Returns true if we have any option changes that haven't been applied yet */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool HasAnyUnsavedOptionValueChanges() const = 0;

	/** Returns true if we have a option change that haven't been applied yet for this cvar*/
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool HasPendingApplyOptionValue( const FString& cvar ) const = 0;

	/** Returns true if we have a pending option value waiting to be applied for this cvar after we restart game or session */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool HasAnyPendingRestartOptionValue( const FString& cvar ) const = 0;

	/** Returns true if we require restart of the session for any settings to apply */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetRequireSessionRestart() const = 0;

	/** Returns true if we require restart of the game for any settings to apply */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual bool GetRequireGameRestart() const = 0;

	/** Subscribe to changes for this option. The given delegate will be called when cvar is updated */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void SubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) = 0;

	/** Unsubscribe to changes for this option */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void UnsubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) = 0;

	/** Unsubscribe to all changes for options this object have subscribed to */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual void UnsubscribeToAllDynamicOptionUpdate( UObject* boundObject ) = 0;

	/** Returns all setting widgets for all settings this interface owns */
	UFUNCTION( BlueprintCallable, Category = "Option" )
	virtual TArray<FUserSettingCategoryMapping> GetCategorizedSettingWidgets( UObject* worldContext, UUserWidget* owningWidget ) = 0;

	/** When called on the CDO, this will return the active option interface handling options of this type. */
	virtual IFGOptionInterface* GetActiveOptionInterface() const = 0;
};
