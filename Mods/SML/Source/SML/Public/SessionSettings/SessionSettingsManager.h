#pragma once

#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGOptionInterfaceImpl.h"
#include "Templates/Identity.h"
#include "Settings/FGUserSetting.h"
#include "Settings/FGUserSettingCategory.h"
#include "Subsystems/EngineSubsystem.h"
#include "SessionSettingsManager.generated.h"

UCLASS()
class SML_API USessionSettingsManager : public UWorldSubsystem, public IFGOptionInterfaceImpl
{
	GENERATED_BODY()

public:
	// Begin USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// End USubsystem interface
	
	// Begin IFGOptionInterfaceImpl
	virtual void GetAllUserSettings( TArray<UFGUserSettingApplyType*>& OutUserSettings ) const override;
	virtual UFGUserSettingApplyType* FindUserSetting( const FString& SettingId ) const override;
	// End IFGOptionInterfaceImpl

	// Begin IFGOptionInterface
	virtual IFGOptionInterface* GetPrimaryOptionInterface(UWorld* world) const override;
	virtual bool IsInMainMenu() const override;
	// End IFGOptionInterface

	void SubscribeToAllOptionUpdates(const FOnOptionUpdated& onOptionUpdatedDelegate);
	void UnsubscribeToAllOptionUpdates(const FOnOptionUpdated& onOptionUpdatedDelegate);

	TMap<FString, UFGUserSettingApplyType*> GetAllSessionSettings() { return SessionSettings; };

	UFUNCTION(BlueprintCallable, Category = "Session Settings Manager")
	void InitializeForMap(const TSoftObjectPtr<UWorld>& World, bool bAttemptPreserveValues);
	
	UFGUserSettingApplyType* FindSessionSetting(const FString& strId) const;

	UFUNCTION(BlueprintCallable, Category = "Session Settings Manager")
	FString SerializeSettingsToString() const;

	void DeserializeSettingsFromString( const FString& SerializedString );

	static FString VariantToString(FVariant& Variant);
	static FVariant StringToVariant(const FString& String);

	static const TCHAR* SessionSettingsOption;

	UFUNCTION(BlueprintPure)
	static FString GetSessionSettingsOption() { return SessionSettingsOption; }
private:
	void OnGameModeInitialized(AGameModeBase* GameModeBase);
	
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
	FORCEINLINE T GetOptionValue_Typed(const FString& cvar, TIdentity_T<const T> defaultValue) const
	{
		return GetOptionValue(cvar, FVariant(defaultValue)).GetValue<T>();
	}

	template<typename T>
	FORCEINLINE T GetOptionDisplayValue_Typed(const FString& cvar, TIdentity_T<const T> defaultValue) const
	{
		return GetOptionDisplayValue(cvar, FVariant(defaultValue)).GetValue<T>();
	}
private:
	UPROPERTY(Transient)
	TMap<FString, UFGUserSettingApplyType*> SessionSettings;
};
