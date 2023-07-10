#include "Module/GameInstanceModule.h"
#include "FGInputSettings.h"
#include "SatisfactoryModLoader.h"
#include "Configuration/ConfigManager.h"
#include "Tooltip/ItemTooltipSubsystem.h"
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
    
    //InputAction GameplayTag bindings
    UFGInputSettings* InputSettings = const_cast<UFGInputSettings*>(UFGInputSettings::Get());
    for (const auto& InputActionTag : InputActionTagBindings) {
        UInputAction* ExistingBinding = InputSettings->GetInputActionForTag(InputActionTag.Value);
        checkf(ExistingBinding == nullptr, TEXT("GameplayTag %s is already bound to InputAction %s. %s requested binding to InputAction %s"), *InputActionTag.Value.ToString(), *ExistingBinding->GetPathName(), *OwnerModReferenceString, *InputActionTag.Key->GetPathName());
        
        FInputActionTagBinding* ActionBinding = InputSettings->mInputActionTagBindings.FindByPredicate([&](const FInputActionTagBinding& Binding) {
            return Binding.ObjectPath == InputActionTag.Key;
        });
        if (!ActionBinding) {
            // FGInputSettings might automatically add a new binding when an UInputAction asset is loaded
            // But it seems like OnAssetAdded does not get triggered in-game
            // So we handle both options, just in case
            ActionBinding = &InputSettings->mInputActionTagBindings.Emplace_GetRef();
            ActionBinding->ObjectPath = InputActionTag.Key;
            ActionBinding->BindingName = *InputActionTag.Key->GetName();
            ActionBinding->CachedInputAction = InputActionTag.Key;
        }
        checkf(ActionBinding->GameplayTag == FGameplayTag::EmptyTag, TEXT("InputAction %s is already bound to GameplayTag %s. %s requested binding to GameplayTag %s"), *InputActionTag.Key->GetName(), *ActionBinding->GameplayTag.ToString(), *OwnerModReferenceString, *InputActionTag.Value.ToString());
        ActionBinding->GameplayTag = InputActionTag.Value;
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
    for (TSubclassOf<UFGRemoteCallObject> RemoteCallObject: RemoteCallObjects) {
        RemoteCallObjectRegistry->RegisterRemoteCallObject(RemoteCallObject);
    }
}
