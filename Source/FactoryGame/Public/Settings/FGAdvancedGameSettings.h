// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGPlayerState.h"
#include "FGUserSetting.h"
#include "Subsystems/EngineSubsystem.h"
#include "FGAdvancedGameSettings.generated.h"

/**
 * This subsystem acts as an abstraction layer between the advanced game settings (game modes) and UI and exposes all of them in a structured manner
 */
UCLASS()
class FACTORYGAME_API UFGAdvancedGameSettings : public UWorldSubsystem, public IFGOptionInterface
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem
	
	// Begin IFGOptionInterface
	virtual FVariant GetOptionValue( const FString& strId ) const override;
	virtual FVariant GetOptionValue( const FString& strId, const FVariant& defaultValue ) const override;
	virtual FVariant GetOptionDisplayValue( const FString& strId ) const override;
	virtual FVariant GetOptionDisplayValue( const FString& strId, const FVariant& defaultValue ) const override;
	virtual void SetOptionValue(const FString& strId, const FVariant& value) override;
	virtual void ForceSetOptionValue( const FString& strId, const FVariant& value, const UObject* instigator ) override;
	virtual void SubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) override;
	virtual void UnsubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) override;
	virtual bool IsDefaultValueApplied(const FString& strId) const override;
	virtual void ApplyChanges() override;
	virtual void ResetAllSettingsToDefault() override;
	virtual void ResetAllSettingsInCategory( TSubclassOf< class UFGUserSettingCategory > category, TSubclassOf< class UFGUserSettingCategory > subCategory ) override;
	virtual bool GetBoolOptionValue( const FString& cvar ) const override;
	virtual bool GetBoolUIDisplayValue( const FString& cvar ) const override;
	virtual void SetBoolOptionValue( const FString& cvar, bool value ) override;
	virtual int32 GetIntOptionValue( const FString& cvar ) const override;
	virtual int32 GetIntUIDisplayValue( const FString& cvar ) const override;
	virtual void SetIntOptionValue( const FString& cvar, int32 newValue ) override;
	virtual float GetFloatOptionValue( const FString& cvar ) const override;
	virtual float GetFloatUIDisplayValue( const FString& cvar ) const override;
	virtual void SetFloatOptionValue( const FString& cvar, float newValue ) override;
	virtual bool HasAnyUnsavedOptionValueChanges() const override;
	virtual bool HasPendingApplyOptionValue( const FString& cvar ) const override;
	virtual bool HasAnyPendingRestartOptionValue( const FString& cvar ) const override;
	virtual bool GetRequireSessionRestart() const override;
	virtual bool GetRequireGameRestart() const override;
	virtual void SubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) override;
	virtual void UnsubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) override;
	virtual void UnsubscribeToAllDynamicOptionUpdate( UObject* boundObject ) override;
	virtual TArray<FUserSettingCategoryMapping> GetCategorizedSettingWidgets( UObject* worldContext, UUserWidget* owningWidget ) override;
	virtual IFGOptionInterface* GetActiveOptionInterface() const override;
	// End IFGOptionInterface

	// Checks if we have any changes that should put us into creative mode. This is created for a very specific case in the main menu.
	// @todok2 see if we can solve this in a more generic way.
	UFUNCTION( BlueprintCallable, Category=UI )
	bool HasChangesThatShouldEnableCreativeMode();

	void GetDebugData( TArray<FString>& out_debugData );
	
	void OnPreLoadMap( const FString &MapName );
#if WITH_EDITOR
	void OnBeginPIE(const bool bIsSimulating);
#endif

	FString SerializeSettingsToString();
	void DeserializeSettingsFromString( const FString& serializedString );

private:
	// Collects all user relevant advanced game user settings that exists in the game. Safe to call more than once since it only inits if needed too
	void TryInitAdvancedGameSettings();
	
	bool IsInMainMenu() const;

private:
	UPROPERTY( Transient )
	TMap< FString, class UFGUserSettingApplyType* > mUserSettings;
};
