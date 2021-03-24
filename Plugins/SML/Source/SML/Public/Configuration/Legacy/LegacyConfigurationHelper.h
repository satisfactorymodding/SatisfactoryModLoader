#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigManager.h"

class SML_API FLegacyConfigurationHelper {
public:
    /**
     * Returns configuration file path for provided mod reference
     */
    FORCEINLINE static FString GetModConfigFilePath(const FString& ModReference) {
        return UConfigManager::GetConfigurationFolderPath() + FString::Printf(TEXT("%s.cfg"), *ModReference); 
    }
};
