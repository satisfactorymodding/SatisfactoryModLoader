#include "Utility.h"
#include "util/Logging.h"

namespace SML {
	TSharedPtr<FJsonObject> ParseJsonLenient(const FString& Input) {
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Input);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> Result;
		Serializer.Deserialize(Reader, Result);
		return Result;
	}
	
	FString GetModConfigFilePath(const FString& ModId) {
		const FString ConfigDirPath = GetConfigDirectory();
		const FString FileName = ModId + TEXT(".cfg");
		return ConfigDirPath / FileName;
	}
	
	TSharedRef<FJsonObject> ReadModConfig(const FString& ModId, const TSharedRef<FJsonObject>& DefaultValues) {
		if (!FModInfo::IsModIdValid(ModId)) {
			SML::Logging::error(TEXT("ReadModConfig: Invalid ModId provided: "), *ModId);
			return MakeShareable(new FJsonObject());
		}
		const FString ConfigPath = GetModConfigFilePath(ModId);
		if (!FPaths::FileExists(ConfigPath)) {
			WriteModConfig(ModId, DefaultValues);
			return DefaultValues;
		}
		
		FString Contents;
		FFileHelper::LoadFileToString(Contents, *ConfigPath);

		const TSharedPtr<FJsonObject> LoadedJson = ParseJsonLenient(Contents);
		if (!LoadedJson.IsValid()) {
			WriteModConfig(ModId, DefaultValues);
			return DefaultValues;
		}
		TSharedRef<FJsonObject> ref = LoadedJson.ToSharedRef();
		if (SetDefaultValues(ref, DefaultValues)) {
			WriteModConfig(ModId, ref);
		}
		return ref;
	}

	void WriteModConfig(const FString& ModId, const TSharedRef<FJsonObject>& Config) {
		if (!FModInfo::IsModIdValid(ModId)) {
			SML::Logging::error(TEXT("WriteModConfig: Invalid ModId provided: "), *ModId);
			return;
		}
		const FString ConfigPath = GetModConfigFilePath(ModId);
		FString ResultString;
		const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ResultString);
		FJsonSerializer Serializer;
		Serializer.Serialize(Config, Writer);
		FFileHelper::SaveStringToFile(ResultString, *ConfigPath);
	}

	bool SetDefaultValues(const TSharedPtr<FJsonObject>& j, const TSharedPtr<FJsonObject>& defaultValues) {
		bool changedSomething = false;
		for (const auto& it : defaultValues.Get()->Values) {
			const auto& key = it.Key;
			const auto& value = it.Value;

			// Add if not existing
			if (!j->HasField(key)) {
				j->SetField(key, value);
				changedSomething = true;
				continue;
			}
			// ignore type checks for key `$` (why tho?)
			if (key.Len() != 1 || key[0] != '$') {
				const auto& jvalue = j->Values[key];
				// Override if wrong type
				if (value->Type != jvalue->Type) {
					j->SetField(key, value);
					changedSomething = true;
					continue;
				}
			}
			// iterate over sub object
			if (value->Type == EJson::Object) {
				changedSomething |= SetDefaultValues(j->Values[key]->AsObject(), value->AsObject());
			}
		}

		TArray<FString> configKeys;
		j->Values.GetKeys(configKeys);
		for (const FString& key : configKeys) {
			// Remove if unused
			if (!defaultValues->HasField(key)) {
				j->RemoveField(key);
				changedSomething = true;
			}
		}
		return changedSomething;
	}
}
