#include "BlueprintLibrary.h"

#include "SML/util/Logging.h"

FString makeBetterPropName(FString name) {
	int32 index;
	name.FindLastChar('_', index);
	name = name.Left(index);
	name.FindLastChar('_', index);
	name = name.Left(index);
	return name;
}

TSharedPtr<FJsonObject> USMLBlueprintLibrary::convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		obj->SetField(makeBetterPropName(prop->GetName()), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

void USMLBlueprintLibrary::convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		auto field = json->TryGetField(makeBetterPropName(prop->GetName()));
		if (!field.IsValid()) continue;
		convertJsonValueToUProperty(field, *prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct));
	}
}

void USMLBlueprintLibrary::convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp) {
	if (auto vProp = Cast<UStrProperty>(prop)) {
		vProp->SetPropertyValue(ptrToProp, json->AsString());
	} else if (auto vProp = Cast<UFloatProperty>(prop)) {
		vProp->SetPropertyValue(ptrToProp, json->AsNumber());
	} else if (auto vProp = Cast<UIntProperty>(prop)) {
		vProp->SetPropertyValue(ptrToProp, json->AsNumber());
	} else if (auto vProp = Cast<UBoolProperty>(prop)) {
		vProp->SetPropertyValue(ptrToProp, json->AsBool());
	} else if (auto vProp = Cast<UArrayProperty>(prop)) {
		FScriptArray arr;
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		arr.Add(jsonArr.Num(), vProp->Inner->ElementSize);
		for (int i = 0; i < jsonArr.Num(); i++) {
			convertJsonValueToUProperty(jsonArr[i], vProp->Inner, (void*)((size_t)arr.GetData() + i * vProp->Inner->ElementSize));
		}
		vProp->SetPropertyValue(ptrToProp, arr);
	} else if (auto vProp = Cast<UStructProperty>(prop)) {
		convertJsonObjectToUStruct(json->AsObject(), vProp->Struct, ptrToProp);
	}
}

inline TSharedPtr<FJsonValue> USMLBlueprintLibrary::convertUPropToJsonValue(UProperty* prop, void* ptrToProp) {
	if (auto vProp = Cast<UStrProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(vProp->GetPropertyValue(ptrToProp)));
	} else if (auto vProp = Cast<UFloatProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(vProp->GetPropertyValue(ptrToProp)));
	} else if (auto vProp = Cast<UIntProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(vProp->GetPropertyValue(ptrToProp)));
	} else if (auto vProp = Cast<UBoolProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueBoolean(vProp->GetPropertyValue(ptrToProp)));
	} else if (auto vProp = Cast<UArrayProperty>(prop)) {
		auto& arr = vProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			jsonArr.Add(convertUPropToJsonValue(vProp->Inner, (void*)((size_t)arr.GetData() + i * vProp->Inner->ElementSize)));
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	} else if (auto vProp = Cast<UStructProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueObject(convertUStructToJsonObject(vProp->Struct, ptrToProp)));
	} else return TSharedPtr<FJsonValue>(new FJsonValueNull());
}

void USMLBlueprintLibrary::LogDebug(const FString& str, bool ignoreDebugMode) {
	if (ignoreDebugMode) SML::Logging::log(SML::Logging::LogType::Debug, *str);
	else SML::Logging::debug(*str);
}

void USMLBlueprintLibrary::LogWarning(const FString& str) {
	SML::Logging::warning(*str);
}

void USMLBlueprintLibrary::LogError(const FString& str) {
	SML::Logging::error(*str);
}

void USMLBlueprintLibrary::LogFatal(const FString& str) {
	SML::Logging::fatal(*str);
}

FString USMLBlueprintLibrary::GetSMLVersion() {
	return SML::getModLoaderVersion().string();
}

FString USMLBlueprintLibrary::GetBootstrapperVersion() {
	return SML::getBootstrapperVersion().string();
}

void USMLBlueprintLibrary::SaveConfig(const FString& modid, UProperty* AnyStruct) {}
