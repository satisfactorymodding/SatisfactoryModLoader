// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/GameUserSettings.h"
#include "GameFramework/PlayerInput.h"
#include "FGInputLibrary.h"
#include "FGOptionInterface.h"
#include "FGOptionsSettings.h"
#include "OptionValueContainer.h"
#include "FGGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FArachnophobiaModeChangedDelegate, bool, isArachnophobiaMode );

/** Our representation of the graphics RHI. Used in options menu to select which RHI they want to use.
 * We call it API because I believe that concept is more known than RHI.
 */
UENUM( BlueprintType )
enum class EGraphicsAPI : uint8
{
	EGR_DX11		UMETA( DisplayName = "DirectX 11" ),
	EGR_DX12		UMETA( DisplayName = "DirectX 12" ),
	EGR_Vulkan		UMETA( DisplayName = "Vulkan"  )
};

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
class FACTORYGAME_API UFGGameUserSettings : public UGameUserSettings, public IFGOptionInterface
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

	/** Returns the option interface that handles getting and settings options*/
	UFUNCTION( BlueprintCallable, Category = Settings )
	static UFGOptionInterface* GetOptionInterface();

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

	// Begin IFGActorRepresentationInterface
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
	// End IFGActorRepresentationInterface

	void SetupDefaultOptionsValues();

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void OnExitToMainMenu();

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void OnExitToDesktop();

	/** Get language data */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	TMap<FString, FText> GetLanguageData();

	/** Set the language data */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetLanguageData( TMap<FString, FText> languageData );

	/** Get the secondary language for quick switch language functionality */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE FString GetSecondaryLanguage() const { return mSecondaryLanguage; }

	/** Set the primary language of the game. The store primary language is also used for quick switch language functionality */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetPrimaryLanguage(FString language);

	/** Set the secondary language for quick switch language functionality */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetSecondaryLanguage(FString language);

	/** Quick switch language between primary and secondary language */
	void QuickSwitchLanguage();

	/** Reset language to default language if it's been changed by quick switch. Used on exit to revert back changes */
	void ResetLanguageToPrimary();

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	EGraphicsAPI GetCurrentActiveGraphicsAPI() const;
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	EGraphicsAPI GetCurrentConfigGraphicsAPI() const;
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool GetForcedGraphicsAPI( EGraphicsAPI& out_forcedGraphicsAPI ) const;
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetCurrentConfigGraphicsAPI( EGraphicsAPI newGraphicsAPI );
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void SetHologramColour( FVector inColour );
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void SetDismantleHologramColour( FVector inColour );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void SetInvalidPlacementHologramColour( FVector inColour );

	UFUNCTION( BlueprintCallable,Category = "FactoryGame|Settings")
	void SetSoftClearanceHologramColour( FVector inColour );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void ApplyHologramColoursToCollectionParameterInstance( UObject* World );

	UMaterialParameterCollection* GetHologramMaterialCollectionAsset() const;

	/** Debug */
	void DumpDynamicOptionsSettings();
	void GetOptionsDebugData( TArray<FString>& out_debugData );
	
private:
	friend class OptionValueContainer;
	
	/** Update the console variable with a new int value */
	void SetCvarValue( FString cvar, int32 value );
	
	/** Update the console variable with a new float value */
	void SetCvarValue( FString cvar, float value );
	
	/** Setup the default value for an int option, registers a cvar if it doesn't already exists */
	void InitDefaultIntOptionValue( FString cvar, int32 value, FText tooltip, EOptionApplyType optionApplyType );

	/** Setup the default value for an float option, registers a cvar if it doesn't already exists */
	void InitDefaultFloatOptionValue( FString cvar, float value, FText tooltip, EOptionApplyType optionApplyType );
	
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
	
	static void CVarSinkHandler();

	/** CVar sink. Update the internal values so they are the same as the console variables  */
	void UpdateCvars();
	
	/** Migrate old options to new system */
	void HandleFGGameUserSettingsVersionChanged();
	
	/** Can we use this cvar? trims and checks for empty string */
	bool ValidateCVar( const FString& cvar );

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
	UPROPERTY( Config )
	uint32 CurrentFGGameUserSettingsVersion;

	/** Hologram color variables. */
	UPROPERTY( Config )
	FVector mBuildHologramColour;

	UPROPERTY( Config )
	FVector mDismantleHologramColour;

	UPROPERTY( Config )
	FVector mInvalidPlacementHologramColour;

	UPROPERTY( Config )
	FVector mSoftClearanceHologramColour;

	TOptional<EGraphicsAPI> mDesiredGraphicsAPI;

	/** const variables */
	static const TMap<FString, int32> NETWORK_QUALITY_CONFIG_MAPPINGS;
};


