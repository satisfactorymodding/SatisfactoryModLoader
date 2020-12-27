#include "BlueprintLibrary.h"
#include "BlueprintModLoadingLibrary.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"
#include "JsonObject.h"
#include "JsonSerializer.h"
#include "LegacyConfigurationHelper.h"
#include "SatisfactoryModLoader.h"
#include "Toolkit/PropertySerializer.h"

DEFINE_LOG_CATEGORY(LogBlueprintLegacy);

bool USMLBlueprintLibrary::IsModLoaded(const FString& ModReference) {
	return UBlueprintModLoadingLibrary::IsModLoaded(ModReference);
}

TArray<FString> USMLBlueprintLibrary::GetLoadedMods() {
	return UBlueprintModLoadingLibrary::GetLoadedMods();
}

FModInfo USMLBlueprintLibrary::GetLoadedModInfo(const FString& ModReference) {
	return UBlueprintModLoadingLibrary::GetLoadedModInfo(ModReference);
}

FVersion USMLBlueprintLibrary::GetSMLVersion() {
	return UBlueprintModLoadingLibrary::GetSMLVersion();
}

FVersion USMLBlueprintLibrary::GetBootstrapperVersion() {
	const TMap<FName, FString> ExtraAttributes = FSatisfactoryModLoader::GetExtraAttributes();
	FVersion BootstrapperVersion = FVersion{1, 0, 0};

	//We no longer expose bootstrapper version separately since it's an implementation detail
	//Try to extract it from extra attributes, and fallback to 1.0.0 if it fails
	if (ExtraAttributes.Contains(FModLoaderExtraAttributes::EA_BootstrapperVersion)) {
		const FString BootstrapperVersionString = ExtraAttributes.FindChecked(FModLoaderExtraAttributes::EA_BootstrapperVersion);
		FString OutErrorMessage;
		BootstrapperVersion.ParseVersion(BootstrapperVersionString, OutErrorMessage);
	}
	
	return BootstrapperVersion;
}

bool USMLBlueprintLibrary::GetDevelopmentModeEnabled() {
	return UBlueprintModLoadingLibrary::IsDevelopmentModeEnabled();
}


void USMLBlueprintLibrary::LogDebug(const FString& Str, bool bIgnoreDebugMode) {
	UE_LOG(LogBlueprintLegacy, Verbose, TEXT("%s"), *Str);
}

void USMLBlueprintLibrary::LogInfo(const FString& Str) {
	UE_LOG(LogBlueprintLegacy, Display, TEXT("%s"), *Str);
}

void USMLBlueprintLibrary::LogWarning(const FString& Str) {
	UE_LOG(LogBlueprintLegacy, Warning, TEXT("%s"), *Str);
}

void USMLBlueprintLibrary::LogError(const FString& Str) {
	UE_LOG(LogBlueprintLegacy, Error, TEXT("%s"), *Str);
}

void USMLBlueprintLibrary::LogFatal(const FString& Str) {
	UE_LOG(LogBlueprintLegacy, Fatal, TEXT("%s"), *Str);
}

void USMLBlueprintLibrary::SaveConfig(const FString& ModReference, const FDynamicStructInfo& Config) {
	const FString ModConfigFilePath = FLegacyConfigurationHelper::GetModConfigFilePath(ModReference);
	FString OutSerializedJson;
	StructToJson(OutSerializedJson, true, Config);
	if (!FFileHelper::SaveStringToFile(OutSerializedJson, *ModConfigFilePath)) {
		UE_LOG(LogBlueprintLegacy, Error, TEXT("Failed to save mod configuration to %s"), *ModConfigFilePath);
	}
}

void USMLBlueprintLibrary::LoadConfig(const FString& ModReference, const FDynamicStructInfo& Config) {
	const FString ModConfigFilePath = FLegacyConfigurationHelper::GetModConfigFilePath(ModReference);

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*ModConfigFilePath)) {
		FString InSerializedJson;
		if (!FFileHelper::LoadFileToString(InSerializedJson, *ModConfigFilePath)) {
			UE_LOG(LogBlueprintLegacy, Error, TEXT("Failed to load mod configuration from %s"), *ModConfigFilePath);
			return;
		}
		StructFromJson(InSerializedJson, true, Config);
	}
}

FString PrettifyPropertyName(const FString& PropertyName) {
	int32 SecondUnderscoreFromEnd = INDEX_NONE;
	int32 UnderscoreNum = 0;
	for (int32 i = PropertyName.Len() - 1; i >= 0; i--) {
		if (PropertyName[i] == TEXT('_')) {
			UnderscoreNum++;
			if (UnderscoreNum == 2) {
				SecondUnderscoreFromEnd = i;
				break;
			}
		}
	}
	if (SecondUnderscoreFromEnd != INDEX_NONE) {
		return PropertyName.Mid(0, SecondUnderscoreFromEnd);
	}
	return PropertyName;
}

void USMLBlueprintLibrary::StructToJson(FString& String, bool bUsePrettyPropertyNames, const FDynamicStructInfo& Struct) {
	const TSharedRef<FJsonObject> ResultObject = MakeShareable(new FJsonObject());
	UPropertySerializer* PropertySerializer = NewObject<UPropertySerializer>();

	for (UProperty* Property = Struct.Struct->PropertyLink; Property; Property = Property->PropertyLinkNext) {
		FString PropertyName = Property->GetName();
		const void* PropertyValue = Property->ContainerPtrToValuePtr<void>(Struct.StructValue);
		if (bUsePrettyPropertyNames) {
			PropertyName = PrettifyPropertyName(PropertyName);
		}
		ResultObject->SetField(PropertyName, PropertySerializer->SerializePropertyValue(Property, PropertyValue));
	}
	
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&String);
	FJsonSerializer::Serialize(ResultObject, Writer);
}

void USMLBlueprintLibrary::StructFromJson(const FString& String, bool bUsePrettyPropertyNames, const FDynamicStructInfo& Struct) {
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(String);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		return;
	}
	UPropertySerializer* PropertySerializer = NewObject<UPropertySerializer>();

	for (UProperty* Property = Struct.Struct->PropertyLink; Property; Property = Property->PropertyLinkNext) {
		FString PropertyName = Property->GetName();
		void* PropertyValue = Property->ContainerPtrToValuePtr<void>(Struct.StructValue);
		if (bUsePrettyPropertyNames) {
			PropertyName = PrettifyPropertyName(PropertyName);
		}
		if (JsonObject->HasField(PropertyName)) {
			PropertySerializer->DeserializePropertyValue(Property, JsonObject->Values.FindChecked(PropertyName).ToSharedRef(), PropertyValue);
		}
	}
}