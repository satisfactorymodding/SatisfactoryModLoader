#pragma once
#include "FGInputLibrary.h"
#include "Module/GameInstanceModule.h"
#include "ModKeyBindRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogModKeyBindRegistry, All, All);

USTRUCT()
struct SML_API FModKeyBindRegistrationEntry {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Default")
	FString PluginName;

	UPROPERTY(VisibleAnywhere, Category = "Default")
	FFGKeyMapping KeyMapping;
};

UCLASS()
class SML_API UModKeyBindRegistry : public UEngineSubsystem {
    GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = "Default")
	TArray<FModKeyBindRegistrationEntry> RegistrationEntries;
public:
    /**
     * Register given key mapping and associates it with mod reference provided
     * Action name should be unique and start with "ModReference." prefix to avoid conflicts with other mods
     * 
     * @param PluginName reference of the mod this key bind belongs to
     * @param KeyMapping information about KeyMapping being registered. 
     */
    UFUNCTION(BlueprintCallable, Category = "Input")
	void RegisterModKeyBind(const FString& PluginName, const FFGKeyMapping& KeyMapping);

	/**
	 * Registers display name and tooltip for the provided action key mapping
	 */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RegisterModActionKeyBindDisplayName(const FString& PluginName, const FActionMappingDisplayName& ActionMappingDisplayName);

	/**
	 * Registers display name and tooltip for the provided axis key mapping
	 */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void RegisterModAxisKeyBindDisplayName(const FString& PluginName, const FAxisMappingDisplayName& AxisMappingDisplayName);
	
	/**
	 * Retrieves the name of the plugin that has registered the passed key binding
	 * @param ActionName the key binding
	 * @param OutPluginName if successful, name of the plugin holding the registration
	 * @return true if lookup is successful, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "Input")
	bool FindKeyBindOwnerPluginName(const FName& ActionName, bool bIsAxisMapping, FString& OutPluginName);
};
