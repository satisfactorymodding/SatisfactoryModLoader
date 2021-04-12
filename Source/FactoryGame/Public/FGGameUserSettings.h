// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/GameUserSettings.h"
#include "GameFramework/PlayerInput.h"
#include "FGInputLibrary.h"
#include "FGOptionsSettings.h"
#include "OptionValueContainer.h"
#include "FGGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FArachnophobiaModeChangedDelegate, bool, isArachnophobiaMode );
DECLARE_DYNAMIC_DELEGATE_OneParam( FOptionUpdated, FString, updatedCvar );

/** Name and value combination for the options with audio */
USTRUCT()
struct FAudioVolumeMap
{
	GENERATED_BODY()
	
	/** Name of the RTPC that this maps to */
	UPROPERTY()
	FString Name;

	/** The stored value of the RTPC */
	UPROPERTY()
	float Value;
	
};

/** Holds delegates to be called when a specific option is changed */
USTRUCT()
struct FOptionUpdateDelegateData
{
	GENERATED_BODY();
public:

	UPROPERTY()
	TArray<FOptionUpdated> OptionUpdatedDelegates;
};

UCLASS(BlueprintType)
class FACTORYGAME_API UFGGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:

	//~Begin GameUserSettings interface
	virtual void ApplyNonResolutionSettings() override;
	virtual void ApplyResolutionSettings( bool bCheckForCommandLineOverrides ) override;
	virtual void ApplySettings( bool bCheckForCommandLineOverrides ) override;
	virtual void SaveSettings() override;
	virtual void LoadSettings( bool bForceReload = false ) override;
	virtual float GetEffectiveFrameRateLimit() override;
	virtual void ConfirmVideoMode() override;
	//~End GameUserSettings interfaces
	
	/** Reset the option with the given cvar */
	void ResetOption( FString cvar );

	/** Called after all options in the category have been reseted. Used if we need to do something after a category is reseted */
	UFUNCTION( BlueprintCallable, Category = Settings )
	void ResetOptionCategory( EOptionCategory optionCategory );

	UFUNCTION( BlueprintCallable, Category = Settings )
	void RevertUnsavedChanges();

	void SetupBindings();

	UFUNCTION( BlueprintPure, Category = Settings )
	virtual bool IsStableVideoModeDirty();

	UFUNCTION( BlueprintCallable, Category = Settings )
	virtual void ResetVideoModeToLatestStable();

	UFUNCTION( BlueprintCallable, Category = Settings )
	virtual void ConfirmStableVideoMode();

	/** If we are switching to fullscreen mode make sure we have a valid resolution */
	void SanitizeResolution();

	/** Switch between fullscreen and windowed mode */
	void ToggleFullscreenMode();

	/** Returns the game local machine settings (resolution, windowing mode, scalability settings, etc...) */
	UFUNCTION( BlueprintCallable, Category = Settings )
	static UFGGameUserSettings* GetFGGameUserSettings();

	UFUNCTION()
	void UpdateAudioOption( FString updatedCvar );

	/** Triggered when arachnophobia mode option have changed */
	UFUNCTION()
	void OnArachnophobiaModeUpdated( FString updatedCvar );

	/** Triggered when foliage quality option have changed */
	UFUNCTION()
	void OnFoliageQualityUpdated( FString updatedCvar );

	/** Triggered when motion blur option have changed */
	UFUNCTION()
	void OnMotionBlurEnabledUpdated( FString updatedCvar );

	/** Triggered when Pool light quality scalabilty cvar have changed */
	UFUNCTION()
	void OnPoolLightQualityUpdated( FString updatedCvar );

	/** Triggered when network quality option have changed */
	UFUNCTION()
	void OnNetworkQualityUpdated( FString updatedCvar );
	
	/** Returns the default quality setting value */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	int32 GetDefaultPostProcessQualitySetting( FString settingName );

	/** Update network values in config files */
	void RefreshNetworkQualityValues();

	/** Get custom bindings */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE TArray< struct FFGKeyMapping > GetKeyMappings() { return mCustomKeyMappings; }

	/** Add a new custom mapping */
	void AddCustomActionMapping( FFGKeyMapping newMapping );

	/** Clears array of custom mappings */
	void RemoveAllCustomActionMappings();

	/** Get if we require restart of the session for the settings to apply */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Settings")
    bool GetRequireSessionRestart() const;

	/** Get if we require restart of the game for the settings to apply */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Settings")
    bool GetRequireGameRestart() const;

	/** Get the applied/active option value for a bool */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool GetBoolOptionValue( FString cvar );
	
	/** Set the applied/active option value for a bool */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetBoolOptionValue( FString cvar, bool value );

	/** Get the applied/active option value for a integer */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	int32 GetIntOptionValue( FString cvar );

	/** Set the option value for a integer */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetIntOptionValue( FString cvar, int32 newValue );

	/** Get the option value for a float */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	float GetFloatOptionValue( FString cvar );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	float GetFloatUIDisplayValue( FString cvar );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	int32 GetIntUIDisplayValue( FString cvar );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool GetBoolUIDisplayValue( FString cvar );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool HasAnyUnsavedOptionValueChanges();

	/** Get if we have a pending option value waiting to be applied for this cvar */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool HasPendingApplyOptionValue( FString cvar );

	/** Get if we have a pending option value waiting to be applied for this cvar after we restart game or session */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool HasPendingAnyRestartOptionValue( FString cvar );
	
	/** Set the option value for a float */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetFloatOptionValue( FString cvar, float newValue );

	/** Update the console variable with a new int value */
	void SetCvarValue( FString cvar, int32 value );
	
	/** Update the console variable with a new float value */
	void SetCvarValue( FString cvar, float value );
	
	/** Setup the default value for an int option, registers a cvar if it doesn't already exists */
	void InitDefaultIntOptionValue( FString cvar, int32 value, FText tooltip, EOptionApplyType optionApplyType );

	/** Setup the default value for an float option, registers a cvar if it doesn't already exists */
	void InitDefaultFloatOptionValue( FString cvar, float value, FText tooltip, EOptionApplyType optionApplyType );
	
	void SetupDefaultOptionsValues();

	/** Bind up events for changing RTPC audio volume when audio cvar is changed */
	void SetupAudioOption( struct FOptionRowData data );

	/** Register an int console variable */
	void RegisterConsoleVariable( FString cvar, int32 value, FString tooltip );

	/** Register a float console variable */
	void RegisterConsoleVariable( FString cvar, float value, FString tooltip );
	
	/** Apply settings that have been changed and are pending */
	void ApplyPendingChanges();

	/** Check if any cvar should be checked and applied */
	void CheckForCvarOverrides();
	
	/** Check if any cvar should be checked and applied for video settings */
	void CheckForVideoCvarOverrides();

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void OnExitToMainMenu();

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void OnExitToDesktop();
	
	static void CVarSinkHandler();

	/** CVar sink. Update the internal values so they are the same as the console variables  */
	void UpdateCvars();

	/** Subscribe to changes for this option. The given delegate will be called when cvar is updated  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SubscribeToDynamicOptionUpdate( FString cvar, const FOptionUpdated& optionUpdatedDelegate );

	/** Unsubscribe to changes for this option  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void UnsubscribeToDynamicOptionUpdate( FString cvar, const FOptionUpdated& optionUpdatedDelegate );
	
	/** Unsubscribe to all changes for options this object have subscribed to  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void UnsubscribeToAllDynamicOptionUpdate( UObject* boundObject );
	
	/** Get language data */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	TMap<FString, FText> GetLanguageData();

	/** Set the language data */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetLanguageData( TMap<FString, FText> languageData );

	/** Get the secondary language for quick switch language functionality */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE FString GetSecondaryLanguage() const { return mSecondaryLanguage; }

	/** Set the secondary language for quick switch language functionality */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetSecondaryLanguage( FString language ) { mSecondaryLanguage = language; }

	/** Set the primary language for quick switch language functionality */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
    void SetPrimaryLanguage( FString language ) { mPrimaryLanguage = language; }

	/** Quick switch language between primary and secondary language */
	void QuickSwitchLanguage();

	/** Reset language to default language if it's been changed by quick switch. Used on exit to revert back changes */
	void ResetLanguageToPrimary();

	/** Migrate old options to new system */
	void HandleFGGameUserSettingsVersionChanged();

	/** Debug */
	void DumpDynamicOptionsSettings();

	void GetOptionsDebugData( TArray<FString>& out_debugData );

private:
	friend class OptionValueContainer;
	
	/** Can we use this cvar? trims and checks for empty string */
	bool ValidateCVar( FString &cvar );

	void BroadcastDynamicOptionUpdate( FString cvar );

public:
	/** Called when arachnophobia mode is changed */
	UPROPERTY( BlueprintAssignable, Category = "Arachnophobia", DisplayName = "OnArachnophobiaModeChanged" )
	FArachnophobiaModeChangedDelegate OnArachnophobiaModeChangedDelegate;

protected:
	/** Audio volumes for the options */
	UPROPERTY(Config)
	TArray<FAudioVolumeMap> mAudioVolumes;

	/** Sets Field of View */
	UPROPERTY( Config )
	int32 mFOV;

	/** Motion blur quality. 0 = off */
	UPROPERTY( Config )
	int32 mMotionBlurQuality;

	/** Is HZBO enabled */
	UPROPERTY( Config )
	bool mHZBOEnabled;

	/** List of remapped key Mappings */
	UPROPERTY( config, EditAnywhere, Category = "Bindings" )
	TArray< FFGKeyMapping > mCustomKeyMappings;

	/** The current network quality setting */
	UPROPERTY( Config )
	int32 mNetworkQuality;
	
	/** Used to detect if network quality is dirty */
	int32 mLastValidatedNetworkQuality;

	/**Scale of headbobbing */
	UPROPERTY( Config )
	float mHeadBobScale;

	/** When true, arachnid-like creatures are replaced with cats. */
	UPROPERTY(Config)
	uint8 mIsArachnophobiaMode:1;

	/** Sets the Look-axis to inverted */
	UPROPERTY( Config ) 
	uint8 mInvertY:1;

	/** True means old-school hold down key to sprint, false = toggle sprint by pressing */
	UPROPERTY( Config )
	uint8 mHoldToSprint:1;

	UPROPERTY( Config ) // @todok2 SEEMS TO HAVE BEEN REMOVED. Should it be added back?
	uint8 mAutoSortInventory:1;

	/** Whether the user has opted out of analytics or not */
	UPROPERTY( Config )
	uint8 mAnalyticsDisabled:1;

	/** If true, then we require a restart to properly apply the settings */
	uint8 mRestartRequired:1;

	/** How often in seconds to autosave */
	UPROPERTY( Config )
	int32 mAutosaveInterval;

	/** Whether or not we should show the take break notification */
	UPROPERTY( Config )
	bool mShowBreakNotification;

	/** Delegate used for broadcasting updates to subscribed options */
	UPROPERTY()
	FOptionUpdated OptionUpdatedDelegate;

private:
	/** The changed values that we want to save to file */
	UPROPERTY( Config )
	TMap<FString, int32> mIntValues;
	UPROPERTY( Config )
	TMap<FString, float> mFloatValues;

	TArray<FString> mAudioOptions;

	OptionValueContainer mOptionValueContainer;

	/** The last stable window mode that the user have confirmed working by accepting the window mode change. Differs from base classes last confirmed window mode which changes when we apply settings. We want to keep it a little longer if we need to auto revert if we reach a weird state */
	int32 mLastStableWindowMode;

	/** Same as last stable window mode above but holds the last stable resolution instead */
	FIntPoint mLastStableResolution;

	/** All options that have been subscribed to and the delegates that will be called when the relevant option updates */
	TMap<FString, FOptionUpdateDelegateData> SubscribedOptions;

	/** CVar sink that let use listen for changes in CVars and update or internal values accordingly */
	static FAutoConsoleVariableSink mCVarSink;

	/** language data so we can fetch it later and populate the language dropdown */
	TMap<FString, FText> mLanguageData;

	/** The current selected secondary language. Used for localization debugging and quick switching of languages */
	UPROPERTY( Config )
	FString mSecondaryLanguage;
	
	/** The current set priamry language. Used for to know what to switch back to when using quick switch to go to primary language. */
	UPROPERTY( Config )
    FString mPrimaryLanguage;

	/** Which version of game user settings dow we have saved. Used to migrate or perform actions when options are updated/refactored */
	UPROPERTY(config)
	uint32 CurrentFGGameUserSettingsVersion;

	/** const variables */
	static const TMap<FString, int32> NETWORK_QUALITY_CONFIG_MAPPINGS;
};


