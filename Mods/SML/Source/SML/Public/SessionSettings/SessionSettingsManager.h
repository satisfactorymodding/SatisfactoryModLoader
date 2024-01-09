#pragma once

#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGPlayerState.h"
#include "Settings/FGUserSetting.h"
#include "Settings/FGUserSettingCategory.h"
#include "Subsystems/EngineSubsystem.h"
#include "SessionSettingsManager.generated.h"

UCLASS()
class SML_API USessionSettingsManager : public UWorldSubsystem, public IFGOptionInterface
{
	GENERATED_BODY()

public:
	// Begin USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// End USubsystem interface
	
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
	virtual TArray<FUserSettingCategoryMapping> GetCategorizedSettingWidgets(UObject* worldContext, UUserWidget* owningWidget) override;
	virtual IFGOptionInterface* GetActiveOptionInterface() const override;
	// End IFGOptionInterface

	void SubscribeToAllOptionUpdates(const FOnOptionUpdated& onOptionUpdatedDelegate);
	void UnsubscribeToAllOptionUpdates(const FOnOptionUpdated& onOptionUpdatedDelegate);

	UFUNCTION(BlueprintCallable, Category = "Session Settings Manager")
	void InitializeForMap(const TSoftObjectPtr<UWorld>& World, bool bAttemptPreserveValues);
	
	UFGUserSettingApplyType* FindSessionSetting(const FString& strId) const;

	FString SerializeSettingsToString() const;
	void DeserializeSettingsFromString( const FString& SerializedString );

	static FString VariantToString(FVariant& Variant);
	static FVariant StringToVariant(const FString& String);

	static const TCHAR* SessionSettingsOption;
private:
	void OnGameModeInitialized(AGameModeBase* GameModeBase);
	
	bool IsInMainMenu() const;
	
	void OnOptionUpdated(FString String, FVariant Value) const;

	/*
	 * Using (integer) literals for template argument deduction is troublesome
	 * because the deduced template type is not visible by default. Given that
	 * requiring callers to cast literals is hideous and error-prone, use some
	 * funny template shenanigans to prevent template argument deduction using
	 * the values passed as function arguments. This requires callers of these
	 * function templates to explicitly specify the type argument T.
	 */
	template<typename T>
	FORCEINLINE T GetOptionValue_Typed(const FString& cvar, typename TEnableIf<true, const T>::Type defaultValue) const
	{
		return GetOptionValue(cvar, FVariant(defaultValue)).GetValue<T>();
	}

	template<typename T>
	FORCEINLINE T GetOptionDisplayValue_Typed(const FString& cvar, typename TEnableIf<true, const T>::Type defaultValue) const
	{
		return GetOptionDisplayValue(cvar, FVariant(defaultValue)).GetValue<T>();
	}
private:
	UPROPERTY(Transient)
	TMap<FString, UFGUserSettingApplyType*> SessionSettings;
};