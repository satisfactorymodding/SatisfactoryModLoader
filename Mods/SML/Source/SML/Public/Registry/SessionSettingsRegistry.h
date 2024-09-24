#pragma once
#include "CoreMinimal.h"
#include "SessionSettings/SessionSetting.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SessionSettingsRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSessionSettingsRegistry, All, All);

USTRUCT(BlueprintType)
struct SML_API FSMLSessionSettingInfo {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Setting Info")
	FString OwningPluginName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Setting Info")
	USMLSessionSetting* SessionSetting;

	FORCEINLINE FSMLSessionSettingInfo() : SessionSetting(NULL) {
	}
};

UCLASS()
class SML_API USMLSessionSettingsRegistry : public UGameInstanceSubsystem {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Session Settings Registry")
	TArray<FSMLSessionSettingInfo> AllSessionSettings;
public:
	USMLSessionSettingsRegistry();
	
	UFUNCTION(BlueprintCallable, Category = "Session Settings Registry")
	void RegisterSessionSetting(const FString& PluginName, USMLSessionSetting* SessionSetting);

	UFUNCTION(BlueprintCallable, Category = "Session Settings Registry")
	void UnregisterSessionSetting(USMLSessionSetting* SessionSetting);

	/** Retrieves all session settings relevant for the given map */
	UFUNCTION(BlueprintPure, Category = "Session Settings Registry")
	TArray<FSMLSessionSettingInfo> GetSettingsForMap(const TSoftObjectPtr<UWorld>& MapName);
};
