#include "Registry/ModKeyBindRegistry.h"
#include "FGGameUserSettings.h"
#include "FGOptionsSettings.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY(LogModKeyBindRegistry);

void UModKeyBindRegistry::RegisterModKeyBind(const FString& PluginName, const FFGKeyMapping& KeyMapping) {
    UInputSettings* InputSettings = UInputSettings::GetInputSettings();

    //Check for uniqueness first
    if (!KeyMapping.IsAxisMapping) {
        TArray<FInputActionKeyMapping> ActionMappings;
        InputSettings->GetActionMappingByName(KeyMapping.ActionKeyMapping.ActionName, ActionMappings);

        //We allow up to two registrations for every key, one for gamepad and one for normal keyboard keys
        const FInputActionKeyMapping* ConflictingMapping = ActionMappings.FindByPredicate([&](const FInputActionKeyMapping& OtherMapping) {
            return OtherMapping.Key.IsGamepadKey() == KeyMapping.ActionKeyMapping.Key.IsGamepadKey();
        });
        if (ConflictingMapping != NULL) {
            UE_LOG(LogModKeyBindRegistry, Error, TEXT("Attempt to register action key mapping %s by mod %s with conflicting input type (must have at most one registration for keyboard and one for game pad)"),
                *KeyMapping.ActionKeyMapping.ActionName.ToString(), *PluginName);
            return;
        }
    } else {
        TArray<FInputAxisKeyMapping> AxisMappings;
        InputSettings->GetAxisMappingByName(KeyMapping.AxisKeyMapping.AxisName, AxisMappings);

        //We allow up to two registrations for axis mappings, one for positive and one for negative axis
        const FInputAxisKeyMapping* ConflictingMapping = AxisMappings.FindByPredicate([&](const FInputAxisKeyMapping& OtherMapping) {
            return OtherMapping.Key.IsGamepadKey() == KeyMapping.AxisKeyMapping.Key.IsGamepadKey() &&
                FMath::Sign(OtherMapping.Scale) == FMath::Sign(KeyMapping.AxisKeyMapping.Scale);
        });
        if (ConflictingMapping != NULL) {
            UE_LOG(LogModKeyBindRegistry, Error, TEXT("Attempt to register axis key mapping %s by mod %s with conflicting input type (must have at most one registration for keyboard and one for game pad per axis direction)"),
                *KeyMapping.AxisKeyMapping.AxisName.ToString(), *PluginName);
            return;
        }
    }

    //Register inside of the input settings then
    //TODO: Not very good idea to register plugin key bindings globally, this way they will end up in engine input configuration files
    //TODO: But we need deeper engine support for other sources, which we do not have unfortunately
    if (!KeyMapping.IsAxisMapping) {
        InputSettings->AddActionMapping(KeyMapping.ActionKeyMapping);

        UE_LOG(LogModKeyBindRegistry, Log, TEXT("Registered action key mapping %s by mod %s (Gamepad: %d)"),
            *KeyMapping.ActionKeyMapping.ActionName.ToString(), *PluginName, (int32)KeyMapping.ActionKeyMapping.Key.IsGamepadKey());
    } else {
        InputSettings->AddAxisMapping(KeyMapping.AxisKeyMapping);

        UE_LOG(LogModKeyBindRegistry, Log, TEXT("Registered axis key mapping %s by mod %s (Gamepad: %d, Axis: %d)"),
            *KeyMapping.AxisKeyMapping.AxisName.ToString(), *PluginName, KeyMapping.AxisKeyMapping.Key.IsGamepadKey(), (int32)FMath::Sign(KeyMapping.AxisKeyMapping.Scale));
    }

    //Add mod registration into the registry list
    FModKeyBindRegistrationEntry RegistrationEntry;
    RegistrationEntry.PluginName = PluginName;
    RegistrationEntry.KeyMapping = KeyMapping;

    RegistrationEntries.Add(RegistrationEntry);
}

void UModKeyBindRegistry::RegisterModActionKeyBindDisplayName(const FString& PluginName, const FActionMappingDisplayName& ActionMappingDisplayName) {
    const FModKeyBindRegistrationEntry* RegistrationEntry = RegistrationEntries.FindByPredicate([&](const FModKeyBindRegistrationEntry& OtherEntry) {
        return OtherEntry.PluginName == PluginName &&
            !OtherEntry.KeyMapping.IsAxisMapping &&
            OtherEntry.KeyMapping.ActionKeyMapping.ActionName == ActionMappingDisplayName.ActionMappingName;
    });

    //Only allow registering display names for registered modded key bindings
    if (RegistrationEntry == NULL) {
        UE_LOG(LogModKeyBindRegistry, Error, TEXT("Attempt to register action key mapping display name %s by plugin %s for unknown key mapping"), *ActionMappingDisplayName.ActionMappingName.ToString(), *PluginName);
        return;
    }
    
    UFGOptionsSettings* OptionsSettings = GetMutableDefault<UFGOptionsSettings>();
    const FActionMappingDisplayName* ExistingMapping = OptionsSettings->mActionBindingsDisplayNames.FindByPredicate([&](const FActionMappingDisplayName& OtherDisplayName) {
               return OtherDisplayName.ActionMappingName == ActionMappingDisplayName.ActionMappingName;
    });

    //Do not allow registering multiple display names
    if (ExistingMapping != NULL) {
        UE_LOG(LogModKeyBindRegistry, Error, TEXT("Attempt to register duplicate action key mapping display name %s by plugin %s"), *ActionMappingDisplayName.ActionMappingName.ToString(), *PluginName);
        return;
    }
    OptionsSettings->mActionBindingsDisplayNames.Add(ActionMappingDisplayName);
}

void UModKeyBindRegistry::RegisterModAxisKeyBindDisplayName(const FString& PluginName, const FAxisMappingDisplayName& AxisMappingDisplayName) {
    const FModKeyBindRegistrationEntry* RegistrationEntry = RegistrationEntries.FindByPredicate([&](const FModKeyBindRegistrationEntry& OtherEntry) {
       return OtherEntry.PluginName == PluginName &&
           OtherEntry.KeyMapping.IsAxisMapping &&
           OtherEntry.KeyMapping.AxisKeyMapping.AxisName == AxisMappingDisplayName.AxisMappingName;
    });

    //Only allow registering display names for registered modded key bindings
    if (RegistrationEntry == NULL) {
        UE_LOG(LogModKeyBindRegistry, Error, TEXT("Attempt to register axis key mapping display name %s by plugin %s for unknown key mapping"), *AxisMappingDisplayName.AxisMappingName.ToString(), *PluginName);
        return;
    }
    
    UFGOptionsSettings* OptionsSettings = GetMutableDefault<UFGOptionsSettings>();
    const FAxisMappingDisplayName* ExistingMapping = OptionsSettings->mAxisBindingsDisplayNames.FindByPredicate([&](const FAxisMappingDisplayName& OtherDisplayName) {
        return OtherDisplayName.AxisMappingName == AxisMappingDisplayName.AxisMappingName;
    });

    //Do not allow registering multiple display names
    if (ExistingMapping != NULL) {
        UE_LOG(LogModKeyBindRegistry, Error, TEXT("Attempt to register duplicate axis key mapping display name %s by plugin %s"), *AxisMappingDisplayName.AxisMappingName.ToString(), *PluginName);
        return;
    }
    OptionsSettings->mAxisBindingsDisplayNames.Add(AxisMappingDisplayName);
}

bool UModKeyBindRegistry::FindKeyBindOwnerPluginName(const FName& ActionName, bool bIsAxisMapping, FString& OutPluginName) {
    
    const FModKeyBindRegistrationEntry* RegistrationEntry = RegistrationEntries.FindByPredicate([&](const FModKeyBindRegistrationEntry& OtherEntry) {
        return OtherEntry.KeyMapping.IsAxisMapping == bIsAxisMapping &&
            (bIsAxisMapping ? OtherEntry.KeyMapping.AxisKeyMapping.AxisName == ActionName :
                OtherEntry.KeyMapping.ActionKeyMapping.ActionName == ActionName);
    });

    //If we have a registration entry, it's a modded key binding
    if (RegistrationEntry != NULL) {
        OutPluginName = RegistrationEntry->PluginName;
        return true;
    }
    //Otherwise assume FactoryGame ownership
    OutPluginName = FApp::GetProjectName();
    return true;
}

