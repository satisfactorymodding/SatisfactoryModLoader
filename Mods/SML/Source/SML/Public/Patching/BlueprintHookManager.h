#pragma once

#include "Engine/Engine.h"
#include "Subsystems/EngineSubsystem.h"
#include "BlueprintHookingTypes.h"
#include "BlueprintHookManager.generated.h"

class UBlueprintGeneratedClass;
class UHookBlueprintGeneratedClass;

UCLASS()
class SML_API UBlueprintHookManager : public UEngineSubsystem {
    GENERATED_BODY()
private:
	/** Installed hooks per blueprint generated class */
	TMap<FTopLevelAssetPath, TArray<TSoftObjectPtr<UHookBlueprintGeneratedClass>>> InstalledHooksPerBlueprintGeneratedClass;
public:
    /** Registers a blueprint hook. Blueprints will only be kept loaded for the lifetime of the game instance */
    void RegisterBlueprintHook(UGameInstance* OwnerGameInstance, UHookBlueprintGeneratedClass* HookBlueprintGeneratedClass);

	/** Called from the initialization to register static hooks if necessary */
	static void RegisterStaticHooks();

	/** If the function has been hooked, this function retrieves the original, unmodified script code from the hooked function body. Returns normal function script otherwise */
	static bool GetOriginalScriptCodeFromFunction(const UFunction* InFunction, TArray<uint8>& OutOriginalScriptCode);
private:
	/** Called to sanitize the function code prior to the save and remove any hooks from it */
	static void SanitizeFunctionScriptCodeBeforeSave(UFunction* InFunction);
	
	/** Re-applies currently registered blueprint hooks to the provided BPGC */
	void ApplyBlueprintHooksToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass) const;

	/** Applies the new script code to the function while also stashing away the original code */
	static void UpdateFunctionScriptCode(UFunction* InFunction, const TArray<uint8>& NewScriptCode, const TArray<uint8>& OriginalScriptCode);
};
