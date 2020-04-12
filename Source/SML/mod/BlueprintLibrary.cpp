#include "BlueprintLibrary.h"

#include "SML/util/Logging.h"

FString makeBetterPropName(FString name) {
	int32 index;
	FString temp = name;
	name.FindLastChar('_', index);
	name = name.Left(index);
	name.FindLastChar('_', index);
	name = name.Left(index);
	if (name == "")
		return temp;
	return name;
}

TSharedPtr<FJsonObject> USMLBlueprintLibrary::convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct, bool UsePrettyName) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		if(UsePrettyName == true)
			obj->SetField(makeBetterPropName(prop->GetName()), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
		else
			obj->SetField(prop->GetName(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

void USMLBlueprintLibrary::convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct, bool UsePrettyName) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		FString FieldName;
		if (UsePrettyName == true)
			FieldName = makeBetterPropName(prop->GetName());
		else
			FieldName = prop->GetName();
		auto field = json->TryGetField(FieldName);
		if (!field.IsValid()) continue;
		convertJsonValueToUProperty(field, *prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct));
	}
}

void USMLBlueprintLibrary::convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		strProp->SetPropertyValue(ptrToProp, json->AsString());
	} else if (auto fProp = Cast<UFloatProperty>(prop)) {
		fProp->SetPropertyValue(ptrToProp, json->AsNumber());
	} else if (auto iProp = Cast<UIntProperty>(prop)) {
		iProp->SetPropertyValue(ptrToProp, json->AsNumber());
	} else if (auto bProp = Cast<UBoolProperty>(prop)) {
		bProp->SetPropertyValue(ptrToProp, json->AsBool());
	} else if (auto eProp = Cast<UEnumProperty>(prop)) {
		UByteProperty* ByteProp = Cast<UByteProperty>(eProp->GetUnderlyingProperty());
		int64 ENumb = json->AsNumber();
		void* EnumPtr = eProp->ContainerPtrToValuePtr<void>(ptrToProp);
		ByteProp->SetIntPropertyValue(EnumPtr, ENumb);
	} else if (auto aProp = Cast<UArrayProperty>(prop)) {
		FScriptArrayHelper helper(aProp, ptrToProp);
		helper.EmptyValues();
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		for (int i = 0; i < jsonArr.Num(); i++) {
			int64 valueIndex = helper.AddValue();
			convertJsonValueToUProperty(jsonArr[i], aProp->Inner, helper.GetRawPtr(valueIndex));
		}
	} else if (auto sProp = Cast<UStructProperty>(prop)) {
		convertJsonObjectToUStruct(json->AsObject(), sProp->Struct, ptrToProp);
	}
}

TSharedPtr<FJsonValue> USMLBlueprintLibrary::convertUPropToJsonValue(UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(strProp->GetPropertyValue(ptrToProp)));
	} else if (auto fProp = Cast<UFloatProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(fProp->GetPropertyValue(ptrToProp)));
	} else if (auto iProp = Cast<UIntProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(iProp->GetPropertyValue(ptrToProp)));
	} else if (auto bProp = Cast<UBoolProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueBoolean(bProp->GetPropertyValue(ptrToProp)));
	} else if (auto eProp = Cast<UEnumProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(eProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(ptrToProp)));
	} else if (auto nProp = Cast<UNumericProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(nProp->GetUnsignedIntPropertyValue(ptrToProp)));
	} else if (auto aProp = Cast<UArrayProperty>(prop)) {
		auto& arr = aProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			jsonArr.Add(convertUPropToJsonValue(aProp->Inner, (void*)((size_t)arr.GetData() + i * aProp->Inner->ElementSize)));
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	} else if (auto sProp = Cast<UStructProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueObject(convertUStructToJsonObject(sProp->Struct, ptrToProp)));
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


void USMLBlueprintLibrary::InternalGetStructAsJson(UStructProperty *Structure, void* StructurePtr, FString &String, bool UsePretty)
{
	TSharedPtr<FJsonObject> JsonObject = convertUStructToJsonObject(Structure->Struct,StructurePtr, UsePretty);
	FString write;
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	String = write;
}
