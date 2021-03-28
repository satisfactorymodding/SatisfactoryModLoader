#include "Configuration/RootConfigValueHolder.h"

void URootConfigValueHolder::MarkDirty_Implementation() {
    if (ConfigManager != NULL) {
        ConfigManager->MarkConfigurationDirty(ConfigId);
    }
}

void URootConfigValueHolder::SetupRootValue(UConfigManager* NewConfigManager, const FConfigId& NewConfigId) {
    this->ConfigManager = NewConfigManager;
    this->ConfigId = NewConfigId;
}

void URootConfigValueHolder::UpdateWrappedValue(UConfigPropertySection* RootValueTemplate) {
    this->RootWrappedValue = NewObject<UConfigPropertySection>(this, RootValueTemplate->GetClass(), TEXT("RootConfigValue"), RF_NoFlags, RootValueTemplate);
}
