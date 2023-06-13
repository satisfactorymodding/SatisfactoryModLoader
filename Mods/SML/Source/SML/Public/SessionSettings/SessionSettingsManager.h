#pragma once
#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "SessionSetting.h"
#include "SessionSettingsManager.generated.h"

class UFGUserSetting;
class USMLSessionSettingsManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionOptionUpdated, USMLSessionSettingsManager*, SettingsManager, USMLSessionSetting*, Option);

UENUM(BlueprintType)
enum class ESessionSettingsApplyPolicy : uint8 {
	Always UMETA(DisplayName = "Always apply active settings"),
	Never UMETA(DisplayName = "Never apply any active settings"),
	ApplyWhenPossible UMETA(DisplayName = "Only apply active settings if they do not require a restart")
};

UCLASS(BlueprintType)
class SML_API USMLSessionSettingsManager : public UObject, public IFGOptionInterface {
	GENERATED_BODY()
protected:
	/** Option objects by their names */
	UPROPERTY()
	TMap<FString, USMLSessionSetting*> OptionsByName;

	/**
	 * Options values that are currently active if we are running the session
	 * This would be retrieved directly from the current UWorld instance and not from the session settings
	 * If there are any settings that require session restart, they would have their current values here
	 */
	TMap<FString, FVariant> ActiveOptionValues;
	
	/**
	 * Option values that are currently active in the session settings
	 * These would usually reflect the most up to date settings of the session,
	 * but some of them might require session restart and therefore not be applied before it
	 **/
	TMap<FString, FVariant> CurrentOptionValues;
	
	/**
	 * Option value that are not updated instantly and hence are currently in a pending state
	 * User needs to apply changes to push their values into the current and potentially active option values
	 */
	TMap<FString, FVariant> PendingOptionValues;

	/** Callbacks set on option values */
	TMap<FString, TArray<FOnOptionUpdated>> OptionValueCallbacks;
	/** Dynamic option callbacks */
	TMap<FString, TArray<FOptionUpdated>> DynamicOptionValueCallbacks;
	
	/** Name of the map we have been initialized with */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Session Settings Manager")
	TSoftObjectPtr<UWorld> MapName;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Session Settings Manager")
	ESessionSettingsApplyPolicy SettingsApplyPolicy;
public:
	/** Global callbacks set on the manager */
	UPROPERTY(BlueprintAssignable, Category = "Session Settings Manager")
	FOnSessionOptionUpdated OnActiveOptionUpdated;

	/** Global callbacks set on the manager */
	UPROPERTY(BlueprintAssignable, Category = "Session Settings Manager")
	FOnSessionOptionUpdated OnCurrentOptionUpdated;
	
	/** Global callbacks set on the manager */
	UPROPERTY(BlueprintAssignable, Category = "Session Settings Manager")
	FOnSessionOptionUpdated OnPendingOptionUpdated;
public:
	/** Initializes settings manager for map creation screen, optionally attempting to preserve settings from previous initialization */
	UFUNCTION(BlueprintCallable, Category = "Session Settings Manager")
	void InitializeForMap(const TSoftObjectPtr<UWorld>& InMapName, bool bAttemptPreserveValues = true);

	/** Updates the active session settings application policy */
	UFUNCTION(BlueprintCallable, Category = "Session Settings Manager")
	void SetSettingsApplyPolicy(ESessionSettingsApplyPolicy InApplyPolicy);

	/** Creates option row widgets for session settings in this manager */
	UFUNCTION(BlueprintCallable, Category = "Session Settings Manager")
	TArray<UFGDynamicOptionsRow*> GetSessionSettingsOptionWidgets(UUserWidget* OwningWidget);

	/** Converts active session settings into the option string, a simple wrapper around PopulateURLOptions for blueprints */
	UFUNCTION(BlueprintPure, Category = "Session Settings Manager")
	FString ToMapOptionsActive() const;

	/** Populates given option values from the passed in URL */
	void LoadOptionValuesFromURLOptions(const FURL& URL, bool bPopulateCurrentOptions, bool bPopulateActiveOptions);

	void PopulateURLOption(const FString& strId, bool bActiveOption, FURL& OutURL) const;
	void LoadURLOption(const FString& strId, const FURL& URL, bool bActiveOption, bool bCurrentOption);
	
	/** Populates URL option values with the current subsystem values */
	void PopulateURLOptions(bool bActiveOptions, FURL& OutURL) const;
public:
	UFUNCTION(BlueprintPure, Category = "Session Settings Manager")
	TArray<USMLSessionSetting*> GetAllSessionSettings() const;

	UFUNCTION(BlueprintPure, Category = "Session Settings Manager")
	USMLSessionSetting* FindSessionSetting(const FString& strId) const;

	bool CanApplyActiveOptionValue(const USMLSessionSetting* SessionSetting) const;
	bool CanEditOptionValue(const USMLSessionSetting* SessionSetting) const;
	void SetCurrentOptionValue(const FString& strId, const FVariant& variant);
	FVariant GetCurrentOptionValue(const FString& strId) const;
	
	void SetUIOptionValue(const FString& strId, const FVariant& variant);
	FVariant GetUIOptionValue(const FString& strId) const;
	
	void SetActiveOptionValue(const FString& strId, const FVariant& variant);
	FVariant GetActiveOptionValue(const FString& strId) const;
	
	void SetPendingOptionValue(const FString& strId, const FVariant& variant);
	bool HasPendingSessionRestartOptionValue(const FString& strId) const;
	void BroadcastOptionValueChanged(const FString& strId);
	
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
	virtual TArray<UFGDynamicOptionsRow*> GetOptionWidgetsInCategory( UUserWidget* owningWidget, EOptionCategory category ) override;
	// End IFGOptionInterface
protected:
	/** Retrieves current option value if it's type matches the expected one, otherwise returns a default value */
	template<typename T>
	FORCEINLINE T GetOptionValueOrDefault(const FString& OptionName) const {
		const FVariant& CurrentOption = GetOptionValue(OptionName);
		if (CurrentOption.GetType() == TVariantTraits<T>::GetType()) {
			return CurrentOption.GetValue<T>();
		}
		return T();
	}

	/** Retrieves UI option value if it's type matches the expected one, otherwise returns a default value */
	template<typename T>
	FORCEINLINE T GetUIOptionValueOrDefault(const FString& OptionName) const {
		const FVariant& CurrentOption = GetUIOptionValue(OptionName);
		if (CurrentOption.GetType() == TVariantTraits<T>::GetType()) {
			return CurrentOption.GetValue<T>();
		}
		return T();
	}
public:
	static FVariant CreateOptionValueFromString(const FVariant& DefaultValue, const FString& InValue);
	static FString ConvertOptionValueToString(const FVariant& Variant);
}; 
