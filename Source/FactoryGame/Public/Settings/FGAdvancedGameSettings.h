// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGOptionInterfaceImpl.h"
#include "FGPlayerState.h"
#include "FGUserSetting.h"
#include "Subsystems/EngineSubsystem.h"
#include "FGAdvancedGameSettings.generated.h"

class UFGUserSettingApplyType;

/** Common interface for advanced game settings that is implemented both by the local AGS subsystem and by the dedicated server */
UINTERFACE( BlueprintType, NotBlueprintable )
class FACTORYGAME_API UFGAdvancedGameSettingsInterface : public UFGOptionInterfaceImpl
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGAdvancedGameSettingsInterface : public IFGOptionInterfaceImpl
{
	GENERATED_BODY()
public:
	/** Checks if we have any changes that should put us into creative mode. This is created for a very specific case in the main menu. */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	virtual bool HasChangesThatShouldEnableCreativeMode() const;

	void ApplySettingsFromMap( const TMap<FString, FString>& SettingValues ) const;
	void SerializeSettingsToMap( TMap<FString, FString>& OutSettingValues ) const;

	FString SerializeSettingsToString() const;
	void DeserializeSettingsFromString( const FString& serializedString );
};

/**
 * This subsystem acts as an abstraction layer between the advanced game settings (game modes) and UI and exposes all of them in a structured manner
 */
UCLASS()
class FACTORYGAME_API UFGAdvancedGameSettings : public UWorldSubsystem, public IFGAdvancedGameSettingsInterface
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem
	
	// Begin IFGAdvancedGameSettingsInterface
	virtual void GetAllUserSettings(TArray<UFGUserSettingApplyType*>& OutUserSettings) const override;
	virtual UFGUserSettingApplyType* FindUserSetting(const FString& SettingId) const override;
	virtual bool HasAnyUnsavedOptionValueChanges() const override;
	virtual bool HasPendingApplyOptionValue(const FString& cvar) const override;
	virtual void RevertUnsavedChanges() override;
	virtual void ApplyChanges() override;
	virtual IFGOptionInterface* GetPrimaryOptionInterface(UWorld* world) const override;
	virtual bool IsInMainMenu() const override;
	// End IFGAdvancedGameSettingsInterface

	void GetDebugData( TArray<FString>& out_debugData );
	void OnPreLoadMap( const FString &MapName );
#if WITH_EDITOR
	void OnBeginPIE(const bool bIsSimulating);
#endif
private:
	// Collects all user relevant advanced game user settings that exists in the game. Safe to call more than once since it only inits if needed too
	void TryInitAdvancedGameSettings();
private:
	UPROPERTY( Transient )
	TMap< FString, class UFGUserSettingApplyType* > mUserSettings;
};
