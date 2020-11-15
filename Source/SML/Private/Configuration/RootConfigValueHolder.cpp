#include "Configuration/RootConfigValueHolder.h"

#include "ConfigValueSection.h"

void URootConfigValueHolder::MarkDirty_Implementation() {
    UConfigManager::MarkConfigurationDirty(ConfigId);
}

void URootConfigValueHolder::SetupRootValue(const FConfigId ConfigId, UConfigValueSection* ConfigValue) {
    this->ConfigId = ConfigId;
    this->RootWrappedValue = ConfigValue;
}
