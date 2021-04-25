#include "AlpakitSettings.h"

#include "Json.h"

UAlpakitSettings* UAlpakitSettings::Get() {
	return GetMutableDefault<UAlpakitSettings>();
}

void UAlpakitSettings::SaveSettings() {
	SaveConfig();
}
