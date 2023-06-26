#pragma once
#include "FGOptionsSettings.h"
#include "Module/ModModule.h"
#include "GameFramework/PlayerInput.h"
#include "Templates/SubclassOf.h"
#include "FGRemoteCallObject.h"
#include "Registry/RemoteCallObjectRegistry.h"
#include "GameInstanceModule.generated.h"

class UModSubsystemHolder;
class UModConfiguration;
class URootBlueprintSCSHookData;
class UWidgetBlueprintHookData;
class USMLGameMapData;
class USMLSessionSetting;

USTRUCT()
struct SML_API FModKeyBindingInfo {
    GENERATED_BODY()
	
    UPROPERTY()
    FName ActionName;
    UPROPERTY()
    FInputActionKeyMapping KeyMapping;
    UPROPERTY()
    FText DisplayName;
};

USTRUCT()
struct SML_API FModAxisBindingInfo {
    GENERATED_BODY()
	
    UPROPERTY()
    FName AxisName;
    UPROPERTY()
    FInputAxisKeyMapping PositiveAxisMapping;
    UPROPERTY()
    FInputAxisKeyMapping NegativeAxisMapping;
    UPROPERTY()
    FText PositiveAxisDisplayName;
    UPROPERTY()
    FText NegativeAxisDisplayName;
};

USTRUCT()
struct FInputActionKeyMappingNamePair {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName ActionName;

	UPROPERTY(EditAnywhere)
	FInputActionKeyMapping ActionKeyMapping;
};

USTRUCT()
struct FInputAxisKeyMappingNamePair {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName AxisName;

	UPROPERTY(EditAnywhere)
	FInputAxisKeyMapping AxisKeyMapping;
};

/** Describes module loaded with game instance and active as long as game instance is loaded */
UCLASS(Blueprintable)
class SML_API UGameInstanceModule : public UModModule {
    GENERATED_BODY()
public:    
    /** Returns game instance this module is attached to */
    UFUNCTION(BlueprintPure)
    UGameInstance* GetGameInstance() const;
  
    /** Configurations defined and used by this mod */
    UPROPERTY(EditDefaultsOnly, Category = "Default")
    TArray<TSubclassOf<UModConfiguration>> ModConfigurations;

    /**
    * List of classes for objects implementing ISMLItemTooltipProvider
    * These will be registered on startup and used to obtain additional description
    * text/widget for all items
    */
    UPROPERTY(EditDefaultsOnly, Category = "Advanced | Tooltips")
    TArray<UClass*> GlobalItemTooltipProviders;

    /**
     * Key Bindings for this mod to be registered
     * You can register up to two key bindings for a single action name,
     * one for the keyboard layout and one for the gamepad
     */
    UPROPERTY(EditDefaultsOnly, Category = "Advanced | Action Key Mappings")
    TArray<FInputActionKeyMappingNamePair> ModActionMappings;

    /**
     * Display names for action mappings registered by the mod
     */
	UPROPERTY(EditDefaultsOnly, Category = "Advanced | Action Key Mappings")
	TArray<FActionMappingDisplayName> ModActionMappingDisplayNames;

    /**
      * Axis Bindings for this mod to be registered
      * They are very similar to key bindings in behavior, but there are some differences:
      *  - Axis Bindings provide /degrees of input/ and not discrete 0/1 values
      *  - Axis Bindings are continuously polled and not triggered on action (so they are good for movement)
      *  So use them for movement basically
      */
    UPROPERTY(EditDefaultsOnly, Category = "Advanced | Axis Key Mappings")
    TArray<FInputAxisKeyMappingNamePair> ModAxisMappings;

    /**
     * Display names for axis mappings registered by the mod
     */
    UPROPERTY(EditDefaultsOnly, Category = "Advanced | Axis Key Mappings")
    TArray<FAxisMappingDisplayName> ModAxisMappingDisplayNames;
    
    /**
     * Simple construction script hooks to install for this mod
     * SCS hooks allow adding modded components to any blueprint-based actor
     * Consult documentation if you're not sure what you want to achieve
     */
    UPROPERTY(Instanced, EditDefaultsOnly, Category = "Advanced | Hooks")
    TArray<URootBlueprintSCSHookData*> BlueprintSCSHooks;

    /**
     * Widget blueprint hooks to add your custom widget into one of the existing game blueprints
     * Works on the widget archetype level so your widget ends up fully integrated into the game's asset
     * You have full control over slot properties and widget settings
     *
     * It should be noted that a similar effect can be achieved by blueprint hooking the widget's construct
     * and manually adding your widget there, but this system provides a simpler and more convenient way
     */
    UPROPERTY(Instanced, EditDefaultsOnly, Category = "Advanced | Hooks")
    TArray<UWidgetBlueprintHookData*> WidgetBlueprintHooks;

	/** Additional maps to register */
	UPROPERTY(EditDefaultsOnly, Category = "Advanced | World")
	TArray<USMLGameMapData*> GameMaps;

	/** Additional session settings to register */
	UPROPERTY(EditDefaultsOnly, Category = "Advanced | World")
	TArray<USMLSessionSetting*> SessionSettings;

    /** Mod Remote Call Objects to be registered automatically during construction phase */
    UPROPERTY(EditDefaultsOnly, Category = "Advanced | Replication")
	TArray<TSubclassOf<class UFGRemoteCallObject>> RemoteCallObjects;
	
    UPROPERTY()
    TArray<FModAxisBindingInfo> ModAxisBindings_DEPRECATED;
    
    UPROPERTY()
    TArray<FModKeyBindingInfo> ModKeyBindings_DEPRECATED;
    
    /** Game instance modules can access world context from game instance */
    virtual UWorld* GetWorld() const override;

    /** Register content from properties here */
    virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;

	virtual void PostLoad() override;
protected:
    /** Allow SetOwnerModReference access to game instance module manager */
    friend class UGameInstanceModuleManager;
    
    /** Registers default content from properties specified above */
    void RegisterDefaultContent();
};
