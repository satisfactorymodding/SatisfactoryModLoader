#include "Module/GameInstanceModule.h"
#include "Configuration/ConfigManager.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Tooltip/ItemTooltipSubsystem.h"
#include "Patching/BlueprintSCSHookManager.h"
#include "Patching/WidgetBlueprintHookManager.h"
#include "Registry/GameMapRegistry.h"
#include "Registry/SessionSettingsRegistry.h"

UGameInstance* UGameInstanceModule::GetGameInstance() const {
    //Game Instance module hierarchy is built on top of UGameInstanceSubsystem,
    //which has UGameInstance itself as outer object
    //so retrieving game instance pointer is rather trivial: walk outer chain until there is an UFGGameInstance
    return GetTypedOuter<UGameInstance>();
}

UWorld* UGameInstanceModule::GetWorld() const {
    //Return nullptr on class default object to trick ImplementsGetWorld()
    if (HasAllFlags(RF_ClassDefaultObject)) {
        return nullptr;
    }
    
    //Otherwise we retrieve world context from game instance
    UGameInstance* GameInstance = GetGameInstance();
    return GameInstance ? GameInstance->GetWorld() : NULL;
}

void UGameInstanceModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    //Register default content before calling blueprint event logic
    if (Phase == ELifecyclePhase::INITIALIZATION) {
        RegisterDefaultContent();
    }
    
    Super::DispatchLifecycleEvent(Phase);
}

void UGameInstanceModule::RegisterDefaultContent() {
    //Register default content
    UGameInstance* GameInstance = GetGameInstance();
    UConfigManager* ConfigManager = GameInstance->GetSubsystem<UConfigManager>();
    UItemTooltipSubsystem* ItemTooltipSubsystem = GameInstance->GetSubsystem<UItemTooltipSubsystem>();

    const FString OwnerModReferenceString = GetOwnerModReference().ToString();
    
    //Register mod configurations first
    for (const TSubclassOf<UModConfiguration>& Configuration : ModConfigurations) {
        ConfigManager->RegisterModConfiguration(Configuration);
    }

    for (const UClass* GlobalTooltipProvider : GlobalItemTooltipProviders) {
        ItemTooltipSubsystem->RegisterGlobalTooltipProvider(OwnerModReferenceString, GlobalTooltipProvider->GetDefaultObject());
    }
	
    UBlueprintSCSHookManager* HookManager = GameInstance->GetEngine()->GetEngineSubsystem<UBlueprintSCSHookManager>();
    for (URootBlueprintSCSHookData* HookData : BlueprintSCSHooks) {
        HookManager->RegisterBlueprintSCSHook(HookData);
    }

    UWidgetBlueprintHookManager* WidgetHookManager = GameInstance->GetEngine()->GetEngineSubsystem<UWidgetBlueprintHookManager>();
    for (UWidgetBlueprintHookData* HookData : WidgetBlueprintHooks) {
        WidgetHookManager->RegisterWidgetBlueprintHook(HookData);
    }

    USMLGameMapRegistry* GameMapRegistry = GameInstance->GetSubsystem<USMLGameMapRegistry>();
    for (USMLGameMapData* MapData : GameMaps) {
        GameMapRegistry->RegisterGameMap(OwnerModReferenceString, MapData);
    }

    USMLSessionSettingsRegistry* SessionSettingsRegistry = GameInstance->GetSubsystem<USMLSessionSettingsRegistry>();
    if ( SessionSettingsRegistry )
    {
    	for (USMLSessionSetting* SessionSetting : SessionSettings) {
    		SessionSettingsRegistry->RegisterSessionSetting(OwnerModReferenceString, SessionSetting);
    	}
    }

	URemoteCallObjectRegistry* RemoteCallObjectRegistry = GameInstance->GetSubsystem<URemoteCallObjectRegistry>();
    for (TSubclassOf<UFGRemoteCallObject> RemoteCallObject: RemoteCallObjects)
    {
        RemoteCallObjectRegistry->RegisterRemoteCallObject(RemoteCallObject);
    }
}
