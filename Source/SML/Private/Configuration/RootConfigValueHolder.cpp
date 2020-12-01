#include "Configuration/RootConfigValueHolder.h"
#include "ConfigValueSection.h"

void URootConfigValueHolder::MarkDirty_Implementation() {
    if (ConfigManager != NULL) {
        ConfigManager->MarkConfigurationDirty(ConfigId);
    }
}

void URootConfigValueHolder::SetupRootValue(UConfigManager* ConfigManager, const FConfigId& ConfigId, UConfigValueSection* ConfigValue) {
    this->ConfigManager = ConfigManager;
    this->ConfigId = ConfigId;
    this->RootWrappedValue = ConfigValue;
}

void URootConfigValueHolder::UpdateWrappedValue(UConfigValueSection* NewWrappedRootValue) {
    this->RootWrappedValue = NewWrappedRootValue;
}
