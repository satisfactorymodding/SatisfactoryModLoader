#pragma once

#include "Engine/Engine.h"
#include "Subsystems/EngineSubsystem.h"
#include "BlueprintHookingTypes.h"
#include "Engine/InputDelegateBinding.h"
#include "BlueprintHookManager.generated.h"

class UBlueprintGeneratedClass;
class UHookBlueprintGeneratedClass;

UCLASS()
class SML_API UBlueprintMixinHostComponent : public UActorComponent {
	GENERATED_BODY()
public:
	UBlueprintMixinHostComponent();
	
	// Begin UActorComponent interface
	virtual void OnComponentCreated() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent interface

	UBlueprintActorMixin* FindMixinByClass(TSubclassOf<UBlueprintActorMixin> MixinClass) const;
protected:
	/** Mixin classes installed on this host */
	UPROPERTY(VisibleAnywhere, Category = "Mixin Host")
	TArray<UHookBlueprintGeneratedClass*> MixinClasses;

	/** Constructed mixins for this actor instance */
	UPROPERTY()
	TArray<UBlueprintActorMixin*> MixinInstances;

	friend class UBlueprintHookManager;
	friend class UMixinInputDelegateBinding;
};

UCLASS()
class SML_API UMixinInputDelegateBinding : public UInputDelegateBinding  {
	GENERATED_BODY()
public:
	virtual void BindToInputComponent(UInputComponent* InputComponent, UObject* ObjectToBindTo) const override;
};

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

	/** Called to sanotize the simple construction script and purge any transient nodes from its lists to avoid runtime crash */
	static void SanitizeSimpleConstructionScript(class USimpleConstructionScript* InSimpleConstructionScript);

	/** Called to sanitize the blueprint generated class and remove any transient dynamic bindings from it */
	static void SanitizeBlueprintGeneratedClass(UBlueprintGeneratedClass* BlueprintGeneratedClass);

	/** Applies currently registered and valid hooks and mixins to the blueprint class */
	void ApplyRegisteredHooksToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass) const;
	
	/** Re-applies currently registered blueprint hooks to the provided BPGC */
	void ApplyBlueprintHooksToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass, const TArray<FBlueprintHookDefinition>& BlueprintHooks) const;

	/** Re-applies currently registered blueprint mixins to the provided BPGC */
	void ApplyActorMixinsToBlueprintClass(UBlueprintGeneratedClass* BlueprintGeneratedClass, TArray<UHookBlueprintGeneratedClass*>& BlueprintMixins) const;

	/** Registers the mixin component on level actors which do not run the construction script */
	void ApplyMixinsToLevelActors(ULevel* Level);

	/** Applies the new script code to the function while also stashing away the original code */
	static void UpdateFunctionScriptCode(UFunction* InFunction, const TArray<uint8>& NewScriptCode, const TArray<uint8>& OriginalScriptCode);
};
