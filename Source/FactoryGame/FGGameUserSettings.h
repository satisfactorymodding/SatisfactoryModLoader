#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "GameFramework/GameUserSettings.h"
#include "GameFramework/PlayerInput.h"
#include "FGInputLibrary.h"
#include "FGGameUserSettings.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FArachnophobiaModeChangedDelegate, bool, isArachnophobiaMode );

/**
 * Name and value combination for the options with audio
 */
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

UCLASS(BlueprintType)
class UFGGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:

	//~Begin GameUserSettings interface
	virtual void ApplyNonResolutionSettings() override;
	virtual void SetToDefaults() override; // Only video settings
	virtual void ResetToCurrentSettings() override; // Only video settings
	virtual void ValidateSettings() override;
	//~End GameUserSettings interfaces

	/** Reset audio settings to default settings */
	UFUNCTION( BlueprintCallable, Category = Settings )
	virtual void SetAudioToDefaults();

	/** Reset audio settings to current settings */
	UFUNCTION( BlueprintCallable, Category = Settings )
	virtual void ResetAudioToCurrentSettings();

	/** Returns the game local machine settings (resolution, windowing mode, scalability settings, etc...) */
	UFUNCTION( BlueprintCallable, Category = Settings )
	static UFGGameUserSettings* GetFGGameUserSettings();

	/** Set the audio volume for a specified channel */
	UFUNCTION(BlueprintCallable,Category="FactoryGame|Settings")
	void SetAudioVolume( FString name, float value );

	/** Gets the audio volumes for all channels */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	float GetAudioVolume( FString name );

	/** Set Arachnophobia Mode */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetArachnophobiaMode( bool newArachnophobiaMode );

	/** Get Arachnophobia Mode */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE bool GetArachnophobiaMode() { return mIsArachnophobiaMode; }

	/** Set Inverty Y mode */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetInvertedLook( bool newInvertLook );

	/** Get Inverty Y mode */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE bool GetInvertedLook() { return mInvertY; }

	/** Set HoldToSprint */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetHoldToSprint( bool newHoldToSprint );

	/** Get HoldToSprint */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE bool GetHoldToSprint() { return mHoldToSprint; }

	/** Set AutoSortInventory */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetAutoSortInventory( bool shouldAutoSort );

	/** Get whether inventory should auto sort */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE bool GetAutoSortInventory() { return mAutoSortInventory; }

	/** Set FOV */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetFOV( int32 newFOV );

	/** Get FOV */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE int32 GetFOV() { return mFOV; }

	/** Sets the user setting for motion blur */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetMotionBlurEnabled( bool enable );

	/** Returns the user setting for motion blur */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool IsMotionBlurEnabled();

	/** Checks if the motion blur user setting is different from current system setting */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool IsMotionBlurDirty() const;

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetHZBOEnabled( bool enable );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool IsHZBOEnabled();

	bool IsHZBODirty() const;

	/** Returns the default quality setting value */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	int32 GetDefaultQualitySetting( FString settingName );

	/** Sets the user setting for network quality */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetNeworkQuality( int32 newNetworkQuality );

	/** Returns the user setting for network quality */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE int32 GetNeworkQuality() { return mNetworkQuality;  }

	/** Update network values in config files */
	void RefreshNetworkQualityValues();

	/** Update if a restart is required for setttings to take full effect */
	void UpdateIsRestartRequired();

	/** Is the provided setting using a custom quality setting  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool IsUsingCustomQualitySetting( FString settingName );

	/** Is post process using a custom setting  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	bool IsPostProcessUsingCustomSettings();

	// MODDING EDIT: Does not override error
	//virtual void SetPostProcessingQuality( int32 Value ) override;

	/** Update the custom post process settings like motion blur etc. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void UpdatePostProcessSettings();

	/** Get custom bindings */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE TArray< struct FFGKeyMapping > GetKeyMappings() { return mCustomKeyMappings; }

	/** Add a new custom mapping */
	void AddCustomActionMapping( FFGKeyMapping newMapping );

	/** Clears array of custom mappings */
	void RemoveAllCustomActionMappings();

	/** Get mHeadBobScale */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE float GetHeadBobScale() { return mHeadBobScale; }

	/** Set mHeadBobScale */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetHeadBobScale( float newHeadBobScale );

	UFUNCTION(BlueprintPure, Category = "FactoryGame|Settings")
	FORCEINLINE bool GetAnalyticsDisabled() { return mAnalyticsDisabled; }

	// MODDING EDIT
	///** Updates the GameUserSettings for analytics and updates the analytics to respond to this change. */
	//UFUNCTION( BlueprintCallable, Category = "Settings" )
	//void SetAnalyticsDisabled( bool isDisabled, UAnalyticsService* analyticsService );

	/** Get if we require restart for the setting to apply */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Settings")
	bool GetRequireRestart() const{ return mRestartRequired; }

	/** Clear that we require restart for setting to apply */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Settings")
	void ClearRequireRestart(){ mRestartRequired = false; }

	/** Gets the autosave interval */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE int32 GetAutosaveInterval() { return mAutosaveInterval;  }

	/** Updates the autosave interval */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetAutosaveInterval( int32 newInterval );

	void ApplyAutosaveInterval();

	/** Gets if we should show the take break notification */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Settings" )
	FORCEINLINE bool GetShowBreakNotification() { return mShowBreakNotification; }

	/** Sets if we should show the take break notification */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Settings" )
	void SetShowBreakNotification( bool enabled );

private:
	void UpdateFoliageQualityChanges();
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

	UPROPERTY( Config )
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

private:
	static const FString MOTION_BLUR_QUALITY;
	static const FString HZBO_SETTING;
	static const TMap<FString, int32> NETWORK_QUALITY_CONFIG_MAPPINGS;
};

