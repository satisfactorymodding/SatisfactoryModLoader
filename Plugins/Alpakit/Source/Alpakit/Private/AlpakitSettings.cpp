#include "AlpakitSettings.h"

#include "Json.h"

UAlpakitSettings* UAlpakitSettings::Get() {
	return GetMutableDefault<UAlpakitSettings>();
}

void UAlpakitSettings::SaveSettings() {
	SaveConfig();
}


UAlpakitModSelectionSettings* UAlpakitModSelectionSettings::Get() {
	return GetMutableDefault<UAlpakitModSelectionSettings>();
}

void UAlpakitModSelectionSettings::SaveSettings() {
	SaveConfig();
}

void UAlpakitModSelectionSettings::loadJson() {
	auto jsonReader = TJsonReaderFactory<TCHAR>::Create(modSelection);
	cacheJsonObject = MakeShareable(new FJsonObject);

	if (!FJsonSerializer::Deserialize(jsonReader, cacheJsonObject) || !cacheJsonObject.IsValid()) {
		cacheJsonObject = MakeShareable(new FJsonObject);
	}
}

void UAlpakitModSelectionSettings::SetPluginSelection(const FString& PluginName, bool selected) {
	if (!cacheJsonObject) {
		loadJson();
	}

	cacheJsonObject->SetBoolField(PluginName, selected);

	auto jsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&modSelection);
	FJsonSerializer::Serialize(cacheJsonObject.ToSharedRef(), jsonWriter);

	SaveSettings();
}

bool UAlpakitModSelectionSettings::GetPluginSelection(const FString& PluginName) {
	if (!cacheJsonObject) {
		loadJson();
	}

	bool outBool = false;
	return cacheJsonObject->TryGetBoolField(PluginName, outBool) && outBool;
}
