// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/GameUserSettings.h"
#include "FGOptionInterface.h"

// <FL> [PfaffN] Cleaned up includes
#include "OnlineIntegrationTypes.h"
#include "FGInputLibrary.h"
#include "FGOptionInterfaceImpl.h"
#include "FGGameUserSettings.generated.h"
// </FL>

class UFGUserSettingApplyType;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FArachnophobiaModeChangedDelegate, bool, isArachnophobiaMode );
DECLARE_MULTICAST_DELEGATE( FOnFGGameUserSettingsInitialized );

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


/**
 * Enum for selecting the upscaling method to be used in-game.
 */
UENUM( BlueprintType )
enum class EUpscalingMethod : uint8
{
	EUM_None = 0	UMETA(DisplayName = "None"),
	EUM_TSR  = 1	UMETA(DisplayName = "EPIC Temporal Super-Resolution (TSR)"),
	EUM_DLSS = 2	UMETA(DisplayName = "NVIDIA Deep learning super sampling (DLSS)"),
	EUM_FSR  = 3	UMETA(DisplayName = "AMD FidelityFX Super Resolution (FSR)"),
	EUM_XeSS = 4	UMETA(DisplayName = "INTEL Xe Super Sampling (XeSS)"),
};

UENUM( BlueprintType )
enum class EGameUserSettingsState : uint8
{
	EGUSS_Default		UMETA( DisplayName = "Default" ),
	EGUSS_Init			UMETA( DisplayName = "Init" ),
	EGUSS_Applying		UMETA( DisplayName = "Applying" ),
	EGUSS_Reset			UMETA( DisplayName = "Reset"  )
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

UENUM( BlueprintType )
enum class EOnlineIntegrationMode: uint8
{
	Undefined,
	PlatformOnly,
	CrossPlay
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnlineIntegrationModeChangedDelegate, EOnlineIntegrationMode, mode);

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
class FACTORYGAME_API UFGGameUserSettings : public UGameUserSettings, public IFGOptionInterfaceImpl
{
	GENERATED_BODY()
public:

	/** Returns the game local machine settings (resolution, windowing mode, scalability settings, etc...) */
	UFUNCTION( BlueprintCallable, Category = Settings )
	static UFGGameUserSettings* GetFGGameUserSettings();
	
	bool HasInitialized() const { return !mUserSettings.IsEmpty(); }

	//~Begin GameUserSettings interface
	virtual void LoadSettings( bool bForceReload = false ) override;
	virtual void ApplyNonResolutionSettings() override;
	virtual void ApplyResolutionSettings( bool bCheckForCommandLineOverrides ) override;
	virtual void ApplySettings( bool bCheckForCommandLineOverrides ) override;
	virtual void SaveSettings() override;
	virtual float GetEffectiveFrameRateLimit() override;
	virtual void ConfirmVideoMode() override;
	virtual void RunHardwareBenchmark(int32 WorkScale = 10, float CPUMultiplier = 1.0f, float GPUMultiplier = 1.0f) override;
	virtual void ApplyHardwareBenchmarkResults() override;
	//~End GameUserSettings interfaces
	
	UFUNCTION(BlueprintCallable)
	FString RunAndApplyHardwareBenchmark( int32 WorkScale = 10, float CPUMultiplier = 1.0f, float GPUMultiplier = 1.0f );

	/** Auto-detects and applies default video settings based on hardware capabilities, skipping the process if in editor mode. */
	void TryAutoDetectSettings();
	
	/** Sets default video settings based on hardware benchmarks and optional command-line overrides. */
	void SetDefaultValuesFromHardwareBenchmark();

	/**
	 * Validates the given upscaling method based on hardware support.
	 * Returns the best available upscaling method if the requested one is not supported.
	 * if considerVRAM is true and VRAM is lower than UPSCALING_VRAM_MINIMUM we return EUpscalingMethod::EUM_None
	 * For example, the preference hierarchy is DLSS > XeSS > TSR.
	 * 
	 * @param upscalingMethod The upscaling method to validate.
	 * @param considerVRAM If we should take the VRAM of the hardware into consideration
	 * @return The validated or preferred upscaling method.
	 */
	EUpscalingMethod ValidateUpscalingMethod( EUpscalingMethod upscalingMethod, bool considerVRAM = true ) const;

	/**
	 * Validates a given scalability setting by ensuring the system/hardware can handle the specified value.
	 * Otherwise returns a more fitting value
	 * 
	 * @param keyString The key that identifies the scalability setting to be validated.
	 * @param valueString The value for the scalability setting represented as a string.
	 * @return The validated value as a string. If no validation is needed, the original value is returned.
	 */
	FString ValidateScalabilityValue( const FString& keyString, const FString& valueString ) const;

	/** Returns the video quality level based on hardware benchmark results, falling back to a default value if no mappings are available. */
	int32 GetVideoQualityLevelFromHardwareBenchmark();

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

	/** Updates applied FOV scaling for the given world. Takes applied camera modifiers on the local player into account */
	void UpdateFOVScalingForWorld( UWorld* world );

	UFUNCTION( BlueprintCallable, Category = Settings )
	void UpdateVideoQuality();
	void OnVideoQualityUpdated( FString strId, FVariant value );
	void OnFOVScalingUpdated( FString strId, FVariant value );
	void InitVideoQualityValues();
	void UpdateVideoQualityCvars( const FString& cvar );
	void OnUpScalingUpdated( FString strId, FVariant value );

	void OnFrameGenerationUpdated(FString strId, FVariant value);
	void InitFrameGeneration();
	
	void InitUpScalingMethod();
	bool IsUsingThirdPartyUpscaler() const;
	UFUNCTION(BlueprintPure, Category = "Satisfactory|Settings|Upscaler" )
	static bool IsXeSSSupported();
	UFUNCTION(BlueprintPure, Category = "Satisfactory|Settings|Upscaler" )
	static bool IsDLSSSupported();
	
	/** Checks if we want to apply some scalability settings based on cmd line arguments. No applied in shipping. Used for profiling.
	 *	If a video quality argument is present we don't used saved values or save changed values.
	 */
	void HandleCmdLineVideoQuality();
	bool GetCmdLineVideoQualityLevel( int32& out_value );
	bool HasVideoQualityCmdLineArg();
	void TestCmdLineVideoQuality();
	void SetGroupQualityLevel( const TCHAR* InGroupName, int32 InQualityLevel, int32 InNumLevels );
	
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

	UFUNCTION()
	void OnOnlineIntegrationModeUpdated();

	/** Triggered when motion blur option have changed */
	UFUNCTION()
	void OnMotionBlurEnabledUpdated( FString updatedCvar );

	/** Triggered when Pool light quality scalabilty cvar have changed */
	UFUNCTION()
	void OnPoolLightQualityUpdated( FString updatedCvar );

	/** Triggered when cloud quality scalabilty cvar have changed */
	UFUNCTION()
	void OnCloudQualityUpdated( FString updatedCVar );

	/** Triggered when AA method cvar have changed */
	void OnAntiAliasingMethodUpdated( FString strId, FVariant value, bool forceSet );

	/** Make sure TSR preset is correct depending on AA method */
	void InitUpscalingPresetValue();
	/** Triggered when TSR preset scalabilty cvar have changed */
	void OnUpscalingPresetUpdated( FString strId, FVariant value );

	/** Triggered when Screen percentage setting is updated */
	void OnScreenPercentageUpdated( FString strId, FVariant value );
	UFUNCTION( BlueprintPure, Category = Settings )
	bool IsUsingCustomScreenPercentage() const;
	
	/** Triggered when Foliage loading distance preset scalabilty cvar have changed */
	void OnFoliageLoadDistanceUpdated( FString strId, FVariant value );

	/** Triggered when network quality option have changed */
	UFUNCTION()
	void OnNetworkQualityUpdated( FString updatedCvar );
	
	/** Returns the default quality setting value */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	int32 GetDefaultPostProcessQualitySetting( FString settingName );

	/** Update network values in config files */
	void RefreshNetworkQualityValues();

	/** Get custom enhanced bindings */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	FORCEINLINE TArray< FFGCustomInputActionMapping >GetPlayerMappedKeys() { return mPlayerMappedKeys; }

	bool GetPlayerMappedKey(const FName& inActionName, FFGCustomInputActionMapping& out_FoundMapping) const;
	
	void AddPlayerMappedKey( const FFGCustomInputActionMapping& newMapping );

	/** Remove all player mapped keys that the player have rebound */
	void RemoveAllPlayerMappedKeys();

	// Begin IFGOptionInterface
	virtual void GetAllUserSettings(TArray<UFGUserSettingApplyType*>& OutUserSettings) const;
	virtual UFGUserSettingApplyType* FindUserSetting(const FString& SettingId) const override;
	virtual void SetOptionValue(const FString& strId, const FVariant& value) override;
	virtual void ApplyChanges() override;
	virtual void ResetAllSettingsToDefault() override;
	virtual void ResetAllSettingsInCategory( TSubclassOf< class UFGUserSettingCategory > category, TSubclassOf< class UFGUserSettingCategory > subCategory ) override;
	virtual bool IsGlobalManager() const override;
	virtual bool IsInMainMenu() const override;
	virtual IFGOptionInterface* GetPrimaryOptionInterface(UWorld* world) const override;
	// End IFGOptionInterface

	FORCEINLINE const FVector& GetHologramBuildColor() const { return mBuildHologramColour; }
	FORCEINLINE const FVector& GetHologramDismantleColor() const { return mDismantleHologramColour; }
	FORCEINLINE const FVector& GetHologramInvalidColor() const { return mInvalidPlacementHologramColour; }
	FORCEINLINE const FVector& GetHologramSoftClearanceColor() const { return mSoftClearanceHologramColour; }
	
	void InitSavedValues();
	void SetupAudioSettingBindings();

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

	// Is any of the cvars controlled by video quality preset changed? This is to know if we should display "Custom" in options menu or not
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool IsUsingCustomVideoQualitySettings() const;
	
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

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void UpdateFoliageLoadingDistance(UObject* World);

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void UpdatePaniniFOVScaling();

	/** Returns true if first launch pop-up screen should be shown to the user */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool ShouldShowFirstLaunchPopUpScreen();

	/** Marks the first launch pop-up screen as accepted by the user. It will not be shown again */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings")
	void MarkFirstLaunchPopUpScreenAccepted();
	
	UMaterialParameterCollection* GetHologramMaterialCollectionAsset() const;

	EOnlineIntegrationMode GetPreferredOnlineIntegrationMode() const { return mPreferredOnlineIntegrationMode; }

	UFUNCTION( BlueprintCallable )
	void SetPreferredOnlineIntegrationMode( EOnlineIntegrationMode preferredOnlineIntegrationMode );

	/** Debug */
	void DumpDynamicOptionsSettings();
	void GetOptionsDebugData( TArray<FString>& out_debugData );
private:
	friend class OptionValueContainer;
	
	/**
	 * Checks if a given module is loaded and sets up a handler to initialize settings when the module is loaded.
	 * @param moduleName - The name of the module to check.
	 * @return True if the module is already loaded, false otherwise.
	 */
	bool AwaitModuleLoadIfNeeded( const FName& moduleName );
	
	/** Callback function that gets invoked when a module's status changes. Used to initialize settings when required modules are loaded. */
	void OnModuleChanged( FName name, EModuleChangeReason reason );
	
	/** Attempts to initialize user settings, delaying the initialization if required modules are not yet loaded. */
	void TryInitUserSettings();
	
	/** Collects and initializes all user-relevant settings in the game. Assumes required modules are loaded. */
	void InitUserSettings();
	
#if WITH_EDITOR
	void OnBeginPIE( const bool bIsSimulating );
	void OnEndPIE( const bool bIsSimulating );
#endif
	void OnPreMapLoad( const FString& MapName ); 
	
	/** Update the console variable with a new int value */
	void SetCvarValue( FString cvar, int32 value );
	
	/** Update the console variable with a new float value */
	void SetCvarValue( FString cvar, float value );
	
	/** Bind up events for changing RTPC audio volume when audio cvar is changed */
	void SetupAudioOption( const FString& strId  );

	/** Check if any cvar should be checked and applied */
	void CheckForCvarOverrides();
	
	/** Check if any cvar should be checked and applied for video settings */
	void CheckForVideoCvarOverrides();
	
	static void CVarSinkHandler();

	/** CVar sink. Update the internal values so they are the same as the console variables  */
	void UpdateCvars();
	
	/** Handle changes before we do any logic. Can be used to migrate old options to new system */
	void PreSetup();
	
	/** Can we use this cvar? trims and checks for empty string */
	bool ValidateCVar( const FString& cvar );
	
	void TestSavedValues();
	UWorld* GetGameWorld();
	
	void FlushRenderingCommandsThenApplyUpscaler( EUpscalingMethod upscalingMethod );

	void SetUpscalerCVars( EUpscalingMethod upscalingMethod );
	
	void SetAAMethodFromUpscalingMethod( EUpscalingMethod upscalingMethod );

public:
	/** Called when arachnophobia mode is changed */
	UPROPERTY( BlueprintAssignable, Category = "Arachnophobia", DisplayName = "OnArachnophobiaModeChanged" )
	FArachnophobiaModeChangedDelegate OnArachnophobiaModeChangedDelegate;

	UPROPERTY( BlueprintAssignable, Category = "Online", DisplayName = "OnOnlineIntegrationModeChanged" )
	FOnlineIntegrationModeChangedDelegate OnOnlineIntegrationModeChangedDelegate;

	/** Called when user settings are initialized. By that point HasInitialized will return true */
	FOnFGGameUserSettingsInitialized mOnUserSettingsInitialized;
protected:

	UPROPERTY( Transient )
	TMap< FString, class UFGUserSettingApplyType* > mUserSettings;

	/** List of remapped enhanced key mappings */
	UPROPERTY( config, EditAnywhere, Category = "Bindings" )
	TArray< FFGCustomInputActionMapping > mPlayerMappedKeys;

	/** Delegate used for broadcasting updates to subscribed options */
	UPROPERTY()
	FOptionUpdated OptionUpdatedDelegate;

private:
	/** The changed values that we want to save to file. @todok2 Can we save this in a different way that is more generic */
	UPROPERTY( Config )
	TMap<FString, int32> mIntValues;
	UPROPERTY( Config )
	TMap<FString, float> mFloatValues;

	TArray<FString> mAudioOptions;

	/* The cached value for last hardware benchmark. Not saved */
	Scalability::FQualityLevels mHardwareBenchmarkResults;

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

	/** True if first launch pop-up screen has been dismissed by the user */
	UPROPERTY( Config )
	bool mDismissedFirstLaunchPopupScreen;

	UPROPERTY( Config )
	EOnlineIntegrationMode mPreferredOnlineIntegrationMode = EOnlineIntegrationMode::Undefined;

	TOptional<EGraphicsAPI> mDesiredGraphicsAPI;

	/** Current state if user setting. Used so we can know when we are taking actions like reset and apply so we can gate certain actions */ 
	EGameUserSettingsState mCurrentState = EGameUserSettingsState::EGUSS_Default;
	
	/** const variables */
	static const TMap<FString, int32> NETWORK_QUALITY_CONFIG_MAPPINGS;
};
