#include "InitGameInstance.h"

#include "ConfigManager.h"
#include "ModKeyBindRegistry.h"
#include "SubsystemHolderRegistry.h"
#include "tooltip/ItemTooltipHandler.h"

void UInitGameInstance::InitDefaultContent() {

    //Register mod configurations first
    for (const FModConfigurationEntry& ConfigurationEntry : ModConfigurations) {
        FConfigId ConfigId{GetOwnerModReference(), ConfigurationEntry.ConfigurationCategory};
        UConfigManager::RegisterModConfiguration(ConfigId, ConfigurationEntry.Configuration);
    }
    
    //Subsystems holders
    for (UClass* SubsystemHolderClass : ModSubsystems) {
        USubsystemHolderRegistry::RegisterSubsystemHolder(GetOwnerModReference(), SubsystemHolderClass);
    }
    
    //Key Bindings and Axis Bindings
    for (const FModKeyBindingInfo& KeyBindingInfo : ModKeyBindings) {
        //Because action binding editor UI is stupid and you cannot set action name directly apparently...
        FInputActionKeyMapping FixedKeyMapping = KeyBindingInfo.KeyMapping;
        FixedKeyMapping.ActionName = KeyBindingInfo.ActionName;
        
        //Register fixed key mapping with proper action name now
        UModKeyBindRegistry::RegisterModKeyBind(GetOwnerModReference(), FixedKeyMapping, KeyBindingInfo.DisplayName);
    }
    
    for (const FModAxisBindingInfo& AxisBindingInfo : ModAxisBindings) {
        //Same problem as with action binding editor - see comment above
        FInputAxisKeyMapping FixedPositiveAxisMapping = AxisBindingInfo.PositiveAxisMapping;
        FInputAxisKeyMapping FixedNegativeAxisMapping = AxisBindingInfo.NegativeAxisMapping;
        
        FixedPositiveAxisMapping.AxisName = AxisBindingInfo.AxisName;
        FixedNegativeAxisMapping.AxisName = AxisBindingInfo.AxisName;
        
        //Register fixed axis mapping with proper action names now
        UModKeyBindRegistry::RegisterModAxisBind(GetOwnerModReference(), FixedPositiveAxisMapping, FixedNegativeAxisMapping, AxisBindingInfo.PositiveAxisDisplayName, AxisBindingInfo.NegativeAxisDisplayName);
    }
    
    for (UClass* GlobalTooltipProvider : GlobalItemTooltipProviders) {
        UItemTooltipHandler::RegisterGlobalTooltipProvider(GetOwnerModReference(), GlobalTooltipProvider->GetDefaultObject());
    }
}

void UInitGameInstance::DispatchInitialize() {
    InitDefaultContent();
    Init();
}
