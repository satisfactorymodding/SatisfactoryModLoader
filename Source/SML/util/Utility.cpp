#include "Utility.h"
#include "util/Logging.h"
#include <regex>

namespace SML {
	TSharedPtr<FJsonObject> parseJsonLenient(const FString& input) {
		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*input);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> result;
		Serializer.Deserialize(reader, result);
		return result;
	}
	
	FString getModConfigFilePath(FString modid) {
		FString configDirPath = getConfigDirectory();
		FString fileName = modid + TEXT(".cfg");
		return configDirPath / fileName;
	}
	
	TSharedRef<FJsonObject> readModConfig(FString modid, const TSharedRef<FJsonObject>& defaultValues) {
		FString configPath = getModConfigFilePath(modid);
		if (!FPaths::FileExists(configPath)) {
			writeModConfig(modid, defaultValues);
			return defaultValues;
		}
		
		FString contents;
		FFileHelper::LoadFileToString(contents, *configPath);

		TSharedPtr<FJsonObject> loadedJson = parseJsonLenient(contents);
		if (!loadedJson.IsValid()) {
			writeModConfig(modid, defaultValues);
			return defaultValues;
		}
		TSharedRef<FJsonObject> ref = loadedJson.ToSharedRef();
		if (setDefaultValues(ref, defaultValues)) {
			writeModConfig(modid, ref);
		}
		return ref;
	}

	void writeModConfig(FString modid, const TSharedRef<FJsonObject>& config) {
		FString configPath = getModConfigFilePath(modid);

		FString resultString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
		FJsonSerializer Serializer;
		Serializer.Serialize(config, writer);
		FFileHelper::SaveStringToFile(resultString, *configPath);
	}

	bool setDefaultValues(const TSharedPtr<FJsonObject>& j, const TSharedPtr<FJsonObject>& defaultValues) {
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
				changedSomething |= setDefaultValues(j->Values[key]->AsObject(), value->AsObject());
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
