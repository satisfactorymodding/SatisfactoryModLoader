#pragma once
#include "CoreMinimal.h"
#include "FGRemoteCallObject.h"
#include "SessionSettingsManager.h"
#include "SessionSettingsSubsystem.generated.h"

class USessionSettingsSubsystem;

UCLASS()
class SML_API USessionSettingsSubsystem : public UWorldSubsystem {
	GENERATED_BODY()
private:
	UPROPERTY()
	USMLSessionSettingsManager* SessionSettingsManager;

	TMap<IConsoleVariable*, USMLSessionSetting*> ConsoleVariableAssociations;
public:
	/**
	 * Called right after session settings have been initialized for the current world
	 * You only need to subscribe to this delegate if your code is executing very early on during the world initialization
	 * (before BeginPlay has been called on the world actors)
	 * Otherwise you can assume that session settings have already been loaded and valid.
	 * Because this would be true in the majority of the cases, this delegate is not exposed to blueprints.
	 */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionSettingsLoaded, USessionSettingsSubsystem* Subsystem);
	FOnSessionSettingsLoaded OnSessionSettingsLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionSettingChanged, USessionSettingsSubsystem*, Subsystem, USMLSessionSetting*, SessionSetting);

	/** Called right after active session setting value has been changed */
	UPROPERTY(BlueprintAssignable, Category = "Session Settings Subsystem")
	FOnSessionSettingChanged OnSessionSettingChanged;

	/** The player that has caused the current setting updates (if they are caused by the remote player) */
	FString CurrentInstigatorPlayer;
	/** True if we are currently applying settings updates received from the server, and as such need to ignore the delegate fires */
	bool bIsUpdatingSettingsFromServer;
	/** True if we are currently updating the CVar values and thus should ignore any CVar change callbacks */
	bool bIsUpdatingCVarValue;
public:
	USessionSettingsSubsystem();

	/** Retrieves the active value (the one currently used by the world) of the session setting */
	FVariant GetSessionSettingValue(const USMLSessionSetting* SessionSetting) const;

	/** Retrieves the active value (the one currently used by the world) of the session setting */
	UFUNCTION(BlueprintPure, Category = "Session Settings Subsystem")
	bool GetSessionSettingBoolValue(const USMLSessionSetting* SessionSetting) const;

	/** Retrieves the active value (the one currently used by the world) of the session setting */
	UFUNCTION(BlueprintPure, Category = "Session Settings Subsystem")
	float GetSessionSettingFloatValue(const USMLSessionSetting* SessionSetting) const;

	/** Retrieves the active value (the one currently used by the world) of the session setting */
	UFUNCTION(BlueprintPure, Category = "Session Settings Subsystem")
	int32 GetSessionSettingIntValue(const USMLSessionSetting* SessionSetting) const;

	/** Retrieves the active value (the one currently used by the world) of the session setting */
	UFUNCTION(BlueprintPure, Category = "Session Settings Subsystem")
	FString GetSessionSettingStringValue(const USMLSessionSetting* SessionSetting) const;

	/** Retrieves the session settings object that can be used for updating the session settings */
	UFUNCTION(BlueprintPure, Category = "Session Settings Subsystem")
	USMLSessionSettingsManager* GetSessionSettingsManager() const;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	FORCEINLINE void SetIsUpdatingSettingsFromServer(bool bInUpdatingSettingsFromServer) { bIsUpdatingSettingsFromServer = bInUpdatingSettingsFromServer; }
	FORCEINLINE void SetCurrentInstigator(const FString& InCurrentInstigator) { CurrentInstigatorPlayer = InCurrentInstigator; };
protected:
	void OnWorldActorsInitialized(const UWorld::FActorsInitializedParams& ActorsInitializedParams);
	void OnConsoleVariableChanged(IConsoleVariable* ConsoleVariable);

	UFUNCTION()
	void OnActiveSessionSettingChanged(USMLSessionSettingsManager* InSessionSettingsManager, USMLSessionSetting* SessionSetting);
	UFUNCTION()
	void OnCurrentSessionSettingChanged(USMLSessionSettingsManager* InSessionSettingsManager, USMLSessionSetting* SessionSetting);
};

UCLASS(NotBlueprintable)
class SML_API USMLSessionSettingsRemoteCallObject : public UFGRemoteCallObject {
	GENERATED_BODY()
public:
	USMLSessionSettingsRemoteCallObject();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void RequestSessionSettingUpdate(const FString& SessionSettingName, const FString& NewSettingValue);

	UFUNCTION(Client, Reliable)
	void NotifyCurrentSessionSettingChanged(const FString& SessionSettingName, const FString& NewSettingValue);

	UFUNCTION(Client, Reliable)
	void NotifyActiveSessionSettingChanged(const FString& SessionSettingName, const FString& NewSettingValue);
private:
	UPROPERTY(Replicated)
	bool mForceNetField_USMLSessionSettingsRemoteCallObject;
};