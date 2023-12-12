#pragma once
#include "FGOptionsSettings.h"
#include "Module/ModModule.h"
#include "GameFramework/PlayerInput.h"
#include "Templates/SubclassOf.h"
#include "FGRemoteCallObject.h"
#include "GameplayTagContainer.h"
#include "Registry/RemoteCallObjectRegistry.h"
#include "GameInstanceModule.generated.h"

class UModSubsystemHolder;
class UModConfiguration;
class URootBlueprintSCSHookData;
class UWidgetBlueprintHookData;
class USMLGameMapData;
class USMLSessionSetting;

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
    
    /** Game instance modules can access world context from game instance */
    virtual UWorld* GetWorld() const override;

    /** Register content from properties here.
    Make sure to call super on the C++ side if you have both a C++ and Blueprint implementation. */
    virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;
protected:
    /** Allow SetOwnerModReference access to game instance module manager */
    friend class UGameInstanceModuleManager;
    
    /** Registers default content from properties specified above */
    void RegisterDefaultContent();
};
