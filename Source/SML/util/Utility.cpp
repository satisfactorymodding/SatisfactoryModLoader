#include "Utility.h"
#include "util/Logging.h"
#include <fstream>
#include <regex>

namespace SML {
	TSharedPtr<FJsonObject> parseJsonLenient(const std::wstring& input) {
		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(input.c_str());
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> result;
		Serializer.Deserialize(reader, result);
		return result;
	}
	
	path getModConfigFilePath(std::wstring modid) {
		path configDirPath = getConfigDirectory();
		std::wstring fileName = formatStr(modid, TEXT(".cfg"));
		return configDirPath / fileName;
	}
	
	TSharedRef<FJsonObject> readModConfig(std::wstring modid, const TSharedRef<FJsonObject>& defaultValues) {
		path configPath = getModConfigFilePath(modid);
		if (!exists(configPath)) {
			writeModConfig(modid, defaultValues);
			return defaultValues;
		}
		std::wifstream fileStream(configPath);

		auto iterator = std::istreambuf_iterator<TCHAR>(fileStream);
		auto endIterator = std::istreambuf_iterator<TCHAR>();
		std::wstring contents{iterator, endIterator};
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

	void writeModConfig(std::wstring modid, const TSharedRef<FJsonObject>& config) {
		path configPath = getModConfigFilePath(modid);
		std::wofstream fileStream(configPath, std::ios::out);
		FString resultString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
		FJsonSerializer Serializer;
		Serializer.Serialize(config, writer);
		fileStream << *resultString;
		fileStream.close();
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
