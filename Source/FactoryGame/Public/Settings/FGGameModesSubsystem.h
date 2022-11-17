// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGPlayerState.h"
#include "Settings/FGUserSetting.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FGGameModesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameModesSubsystem : public UGameInstanceSubsystem, public IFGOptionInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	// Begin IFGOptionInterface
	virtual FVariant GetOptionValue( const FString& strId ) const override;
	virtual void ForceSetOptionValue( const FString& strId, const FVariant& variant, const UObject* instigator ) override;
	virtual void SubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) override;
	virtual void UnsubscribeToOptionUpdate( const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate ) override;
	virtual void ApplyChanges() override;
	virtual void ResetAllSettingsToDefault() override;
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
	virtual bool HasPendingAnyRestartOptionValue( const FString& cvar ) const override;
	virtual bool GetRequireSessionRestart() const override;
	virtual bool GetRequireGameRestart() const override;
	virtual void SubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) override;
	virtual void UnsubscribeToDynamicOptionUpdate( const FString& cvar, const FOptionUpdated& optionUpdatedDelegate ) override;
	virtual void UnsubscribeToAllDynamicOptionUpdate( UObject* boundObject ) override;
	virtual TArray<class UFGDynamicOptionsRow*> GetOptionWidgetsInCategory( UUserWidget* owningWidget, EOptionCategory category ) override;
	// End IFGOptionInterface
	
	UFUNCTION( BlueprintCallable )
	TArray<class UUserWidget*> GetGameModeSettings( UUserWidget* owningWidget );
	UFUNCTION( BlueprintCallable )
	TArray<FUserSettingCatergoryMapping> GetCategorizedGameModeSettings( UUserWidget* owningWidget );

private:
	UFGUserSetting* GetSettingFromStrId( const FString& strId ) const;
	
	UPROPERTY( Transient )
	TArray< class UFGUserSetting* > mUserSettings;
};
