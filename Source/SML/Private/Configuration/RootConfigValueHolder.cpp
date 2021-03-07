#include "Configuration/RootConfigValueHolder.h"
#include "Configuration/Values/ConfigValueSection.h"

void URootConfigValueHolder::MarkDirty_Implementation() {
    if (ConfigManager != NULL) {
        ConfigManager->MarkConfigurationDirty(ConfigId);
    }
}

void URootConfigValueHolder::SetupRootValue(UConfigManager* NewConfigManager, const FConfigId& NewConfigId, UConfigValueSection* NewConfigValue) {
    this->ConfigManager = NewConfigManager;
    this->ConfigId = NewConfigId;
    this->RootWrappedValue = NewConfigValue;
}

void URootConfigValueHolder::UpdateWrappedValue(UConfigValueSection* NewWrappedRootValue) {
    this->RootWrappedValue = NewWrappedRootValue;
}
