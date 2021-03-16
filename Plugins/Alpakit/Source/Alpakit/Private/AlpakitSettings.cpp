#include "AlpakitSettings.h"

UAlpakitSettings* UAlpakitSettings::Get() {
    return GetMutableDefault<UAlpakitSettings>();
}

void UAlpakitSettings::SaveSettings() {
    SaveConfig();
}
