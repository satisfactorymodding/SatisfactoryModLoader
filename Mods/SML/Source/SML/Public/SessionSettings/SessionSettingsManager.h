#pragma once

#include "CoreMinimal.h"
#include "FGOptionInterface.h"
#include "FGOptionInterfaceImpl.h"
#include "Templates/Identity.h"
#include "Settings/FGUserSetting.h"
#include "Settings/FGUserSettingCategory.h"
#include "Subsystems/WorldSubsystem.h"
#include "SessionSettingsManager.generated.h"

UCLASS(BlueprintType)
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
	virtual bool IsGlobalManager() const override;
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

	/** Set the option value for a string, will need to be applied to take effect and/or get saved */
	UFUNCTION(BlueprintCallable, Category = "Option")
	void SetStringOptionValue(const FString& cvar, const FString& newValue) { SetOptionValueTyped<FString>(cvar, newValue); }

	UFUNCTION(BlueprintCallable, Category = "Option")
	FString GetStringOptionValue(const FString& cvar) const { return GetOptionValueTyped<FString>(cvar); }

	/** Get the current UI value for an string. Doesn't always match the active value. Should only be used in the session settings menu. */
	UFUNCTION(BlueprintCallable, Category = "Option")
	virtual FString GetStringUIDisplayValue(const FString& cvar) const { return GetOptionDisplayValueTyped<FString>(cvar); }

private:
	void OnGameModeInitialized(AGameModeBase* GameModeBase);
	
	void OnOptionUpdated(FString String, FVariant Value) const;
private:
	UPROPERTY(Transient)
	TMap<FString, UFGUserSettingApplyType*> SessionSettings;
};
