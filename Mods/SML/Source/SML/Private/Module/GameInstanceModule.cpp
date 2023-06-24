#include "Module/GameInstanceModule.h"
#include "Configuration/ConfigManager.h"
#include "Tooltip/ItemTooltipSubsystem.h"
#include "Registry/ModKeyBindRegistry.h"
#include "Engine/Engine.h"
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

void UGameInstanceModule::PostLoad() {
    Super::PostLoad();

    //Migrate deprecated properties
    for (const FModKeyBindingInfo& ModKeyBindingInfo : ModKeyBindings_DEPRECATED) {
        FInputActionKeyMappingNamePair Pair;
        Pair.ActionName = ModKeyBindingInfo.ActionName;
        Pair.ActionKeyMapping = ModKeyBindingInfo.KeyMapping;
        ModActionMappings.Add(Pair);

        FActionMappingDisplayName ActionMappingDisplayName;
        ActionMappingDisplayName.ActionMappingName = ModKeyBindingInfo.ActionName;
        ActionMappingDisplayName.DisplayName = ModKeyBindingInfo.DisplayName;
        ModActionMappingDisplayNames.Add(ActionMappingDisplayName);
    }
    ModKeyBindings_DEPRECATED.Empty();
    
    for (const FModAxisBindingInfo& ModAxisBindingInfo : ModAxisBindings_DEPRECATED) {
        FInputAxisKeyMappingNamePair PositivePair;
        PositivePair.AxisName = ModAxisBindingInfo.AxisName;
        PositivePair.AxisKeyMapping = ModAxisBindingInfo.PositiveAxisMapping;

        FInputAxisKeyMappingNamePair NegativePair;
        NegativePair.AxisName = ModAxisBindingInfo.AxisName;
        NegativePair.AxisKeyMapping = ModAxisBindingInfo.NegativeAxisMapping;
        
        ModAxisMappings.Add(PositivePair);
        ModAxisMappings.Add(NegativePair);

        FAxisMappingDisplayName AxisMappingDisplayName;
        AxisMappingDisplayName.AxisMappingName = ModAxisBindingInfo.AxisName;
        AxisMappingDisplayName.DisplayNamePositiveScale = ModAxisBindingInfo.PositiveAxisDisplayName;
        AxisMappingDisplayName.DisplayNameNegativeScale = ModAxisBindingInfo.NegativeAxisDisplayName;
        ModAxisMappingDisplayNames.Add(AxisMappingDisplayName);
    }
    ModAxisBindings_DEPRECATED.Empty();
}

void UGameInstanceModule::RegisterDefaultContent() {
    //Register default content
    UGameInstance* GameInstance = GetGameInstance();
    UConfigManager* ConfigManager = GameInstance->GetEngine()->GetEngineSubsystem<UConfigManager>();
    UItemTooltipSubsystem* ItemTooltipSubsystem = GameInstance->GetSubsystem<UItemTooltipSubsystem>();

    const FString OwnerModReferenceString = GetOwnerModReference().ToString();
    
    //Register mod configurations first
    for (const TSubclassOf<UModConfiguration>& Configuration : ModConfigurations) {
        ConfigManager->RegisterModConfiguration(Configuration);
    }

    for (UClass* GlobalTooltipProvider : GlobalItemTooltipProviders) {
        ItemTooltipSubsystem->RegisterGlobalTooltipProvider(OwnerModReferenceString, GlobalTooltipProvider->GetDefaultObject());
    }
    
    //Key Bindings and Axis Bindings
    UModKeyBindRegistry* ModKeyBindRegistry = GameInstance->GetEngine()->GetEngineSubsystem<UModKeyBindRegistry>();

    //Register action key mappings
    for (const FInputActionKeyMappingNamePair& ActionKeyMapping : ModActionMappings) {
        FFGKeyMapping KeyMapping{};
        KeyMapping.IsAxisMapping = false;
        KeyMapping.ActionKeyMapping = ActionKeyMapping.ActionKeyMapping;
        KeyMapping.ActionKeyMapping.ActionName = ActionKeyMapping.ActionName;
        ModKeyBindRegistry->RegisterModKeyBind(OwnerModReferenceString, KeyMapping);
    }

    //Register axis key mappings
    for (const FInputAxisKeyMappingNamePair& AxisKeyMapping : ModAxisMappings) {
        FFGKeyMapping KeyMapping{};
        KeyMapping.IsAxisMapping = true;
        KeyMapping.AxisKeyMapping = AxisKeyMapping.AxisKeyMapping;
        KeyMapping.AxisKeyMapping.AxisName = AxisKeyMapping.AxisName;
        ModKeyBindRegistry->RegisterModKeyBind(OwnerModReferenceString, KeyMapping);
    }
    
    //Register key mappings display names
    for (const FActionMappingDisplayName& ActionMappingDisplayName : ModActionMappingDisplayNames) {
        ModKeyBindRegistry->RegisterModActionKeyBindDisplayName(OwnerModReferenceString, ActionMappingDisplayName);
    }
    for (const FAxisMappingDisplayName& AxisMappingDisplayName : ModAxisMappingDisplayNames) {
        ModKeyBindRegistry->RegisterModAxisKeyBindDisplayName(OwnerModReferenceString, AxisMappingDisplayName);
    }

    UBlueprintSCSHookManager* HookManager = GetGameInstance()->GetEngine()->GetEngineSubsystem<UBlueprintSCSHookManager>();
    for (URootBlueprintSCSHookData* HookData : BlueprintSCSHooks) {
        HookManager->RegisterBlueprintSCSHook(HookData);
    }

    UWidgetBlueprintHookManager* WidgetHookManager = GetGameInstance()->GetEngine()->GetEngineSubsystem<UWidgetBlueprintHookManager>();
    for (UWidgetBlueprintHookData* HookData : WidgetBlueprintHooks) {
        WidgetHookManager->RegisterWidgetBlueprintHook(HookData);
    }

    USMLGameMapRegistry* GameMapRegistry = GetGameInstance()->GetEngine()->GetEngineSubsystem<USMLGameMapRegistry>();
    for (USMLGameMapData* MapData : GameMaps) {
        GameMapRegistry->RegisterGameMap(OwnerModReferenceString, MapData);
    }

    USMLSessionSettingsRegistry* SessionSettingsRegistry = GetGameInstance()->GetEngine()->GetEngineSubsystem<USMLSessionSettingsRegistry>();
    for (USMLSessionSetting* SessionSetting : SessionSettings) {
        SessionSettingsRegistry->RegisterSessionSetting(OwnerModReferenceString, SessionSetting);
    }

	URemoteCallObjectRegistry* RemoteCallObjectRegistry = GameInstance->GetSubsystem<URemoteCallObjectRegistry>();

    if(RemoteCallObjectRegistry != nullptr){
        for (TSubclassOf<UFGRemoteCallObject> RemoteCallObject: RemoteCallObjects) {
            RemoteCallObjectRegistry->RegisterRemoteCallObject(RemoteCallObject);
        }
    }
}
