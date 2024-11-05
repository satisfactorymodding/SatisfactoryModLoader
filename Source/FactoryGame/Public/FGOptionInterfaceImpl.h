// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGOptionInterfaceImpl.generated.h"

class UFGUserSettingApplyType;

UINTERFACE( MinimalAPI, BlueprintType, NotBlueprintable )
class UFGOptionInterfaceImpl : public UFGOptionInterface
{
	GENERATED_BODY()
};

/** Implementation of the option interface based on the UFGUserSettingApplyType objects. */
class FACTORYGAME_API IFGOptionInterfaceImpl : public IFGOptionInterface
{
	GENERATED_BODY()
public:
	// [ZolotukhinN:05/02/2024] Looks like something funky is going on with overload visibility when functions are overriden in child classes.
	// Bring the overloads back into the visibility scope by using them
	using IFGOptionInterface::GetOptionValue;
	using IFGOptionInterface::GetOptionDisplayValue;

	/** Returns all settings that are available in this interface */
	virtual void GetAllUserSettings( TArray<UFGUserSettingApplyType*>& OutUserSettings ) const = 0;
	/** Returns an instance of the user setting with a given ID */
	virtual UFGUserSettingApplyType* FindUserSetting( const FString& SettingId ) const = 0;

	// Begin IFGOptionInterface
	virtual FVariant GetOptionValue( const FString& strId, const FVariant& defaultValue ) const override;
	virtual FVariant GetOptionDisplayValue( const FString& strId, const FVariant& defaultValue ) const override;
	virtual void SetOptionValue( const FString& strId, const FVariant& value ) override;
	virtual void ForceSetOptionValue( const FString& strId, const FVariant& value, const UObject* instigator ) override;
	virtual void SubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) override;
	virtual void UnsubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) override;
	virtual bool IsDefaultValueApplied( const FString& strId ) const override;
	virtual void ApplyChanges() override;
	virtual void ResetAllSettingsToDefault() override;
	virtual void ResetAllSettingsInCategory( TSubclassOf<UFGUserSettingCategory> category, TSubclassOf<UFGUserSettingCategory> subCategory ) override;
	virtual bool HasAnyUnsavedOptionValueChanges() const override;
	virtual bool HasPendingApplyOptionValue( const FString& cvar ) const override;
	virtual void RevertUnsavedChanges() override;
	virtual bool HasAnyPendingRestartOptionValue( const FString& cvar ) const override;
	virtual bool GetRequireSessionRestart() const override;
	virtual bool GetRequireGameRestart() const override;
	virtual void SubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) override;
	virtual void UnsubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) override;
	virtual void UnsubscribeToAllDynamicOptionUpdate( UObject* boundObject ) override;
	virtual TArray<FUserSettingCategoryMapping> GetCategorizedSettingWidgets( UObject* worldContext, UUserWidget* owningWidget ) override;
	// End IFGOptionInterface
};