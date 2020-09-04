#include "AlpakitSettings.h"

UAlpakitSettings* UAlpakitSettings::Get() {
    return GetMutableDefault<UAlpakitSettings>();
}

void UAlpakitSettings::SaveSettings() {
    SaveConfig();
}

int32 UAlpakitSettings::FindModIndexByModReference(const FString& ModReference) {
    for (int32 i = 0; i < Mods.Num(); i++) {
        FAlpakitMod& AlpakitMod = Mods[i];
        if (AlpakitMod.Name == ModReference)
            return i;
    }
    return INDEX_NONE;
}

FAlpakitModRemoteVersion::FAlpakitModRemoteVersion() {
    this->bModIsNotRequiredOnRemote = false;
}

FAlpakitMod::FAlpakitMod() {
    this->Enabled = true;
}
