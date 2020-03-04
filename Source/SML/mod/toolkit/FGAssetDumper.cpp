#include "FGAssetDumper.h"
#include "IAssetRegistry.h"
#include "AssetRegistryModule.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "Json.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/UserDefinedEnum.h"

#define DEFAULT_ITERATOR_FLAGS EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::IncludeInterfaces

TSharedPtr<FJsonObject> CreateFieldDescriptor(UProperty* Property, const void* defaultObjectPtr, UObject* defaultObject, UObject* parentObject) {
	FString resultValueString;
	const void* propertyValue = Property->ContainerPtrToValuePtr<void>(defaultObjectPtr);
	if (parentObject != nullptr && parentObject->IsA(static_cast<UClass*>(Property->GetOuter()))) {
		const void* defaultPropertyValue = Property->ContainerPtrToValuePtr<void>(parentObject);
		if (Property->Identical(propertyValue, defaultPropertyValue)) {
			return TSharedPtr<FJsonObject>(); //skip value if it is the same as in the parent class
		}
	}
	Property->ExportTextItem(resultValueString, propertyValue, propertyValue, defaultObject, 0);
	TSharedRef<FJsonObject> fieldEntry = MakeShareable(new FJsonObject());
	fieldEntry->SetStringField(TEXT("Name"), Property->GetFName().ToString());
	fieldEntry->SetStringField(TEXT("Value"), resultValueString);
	fieldEntry->SetStringField(TEXT("Type"), Property->GetCPPType());
	fieldEntry->SetNumberField(TEXT("PropertyFlags"), Property->PropertyFlags);
	return fieldEntry;
}

TSharedRef<FJsonObject> CreateFunctionSignature(UFunction* function) {
	TSharedRef<FJsonObject> resultJson = MakeShareable(new FJsonObject());
	resultJson->SetStringField(TEXT("Name"), function->GetFName().ToString());
	resultJson->SetStringField(TEXT("ReturnType"), TEXT("void"));

	TArray<TSharedPtr<FJsonValue>> argumentArray;
	for (TFieldIterator<UProperty> It(function); It && (It->PropertyFlags & CPF_Parm); ++It) {
		if (It->PropertyFlags & CPF_ReturnParm) {
			resultJson->SetStringField(TEXT("ReturnType"), It->GetCPPType(nullptr, 0));
		} else {
			argumentArray.Add(MakeShareable(new FJsonValueString(It->GetCPPType(nullptr, 0))));
		}
	}
	resultJson->SetArrayField(TEXT("Arguments"), argumentArray);
	
	if (function->HasAllFunctionFlags(EFunctionFlags::FUNC_Static)) {
		resultJson->SetBoolField(TEXT("Static"), true);
	}
	if (function->HasAllFunctionFlags(EFunctionFlags::FUNC_Final)) {
		resultJson->SetBoolField(TEXT("Final"), true);
	}
	TCHAR* accessRights = TEXT("public");
	if (function->HasAllFunctionFlags(EFunctionFlags::FUNC_Protected))
		accessRights = TEXT("protected");
	else if (function->HasAllFunctionFlags(EFunctionFlags::FUNC_Private))
		accessRights = TEXT("private");
	resultJson->SetStringField(TEXT("Access"), accessRights);
	resultJson->SetNumberField(TEXT("FunctionFlags"), function->FunctionFlags);
	return resultJson;
}

bool isBlacklistedClass(const FString& classPath) {
	return false;
}

TSharedRef<FJsonObject> dumpUserDefinedEnum(UUserDefinedEnum* definedEnum) {
	TSharedRef<FJsonObject> resultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping user defined enum "), *definedEnum->GetFullName());

	resultJson->SetStringField(TEXT("StructName"), definedEnum->GetPathName());
	TArray<TSharedPtr<FJsonValue>> enumValues;
	for (int64 i = 0; i <= definedEnum->GetMaxEnumValue(); i++) {
		if (definedEnum->IsValidEnumValue(i)) {
			const FString& enumName = definedEnum->GetNameStringByValue(i);
			TSharedRef<FJsonObject> entryJson = MakeShareable(new FJsonObject());
			entryJson->SetStringField(TEXT("Name"), enumName);
			const FName& constructedName = FName(*enumName, EFindName::FNAME_Add);
			if (definedEnum->DisplayNameMap.Contains(constructedName)) {
				entryJson->SetStringField(TEXT("DisplayName"), definedEnum->DisplayNameMap[constructedName].ToString());
			}	
			entryJson->SetNumberField(TEXT("Value"), i);
			enumValues.Add(MakeShareable(new FJsonValueObject(entryJson)));
		}
	}
	resultJson->SetArrayField(TEXT("Values"), enumValues);
	return resultJson;
}

TSharedRef<FJsonObject> dumpUserDefinedStruct(UUserDefinedStruct* definedStruct) {
	TSharedRef<FJsonObject> resultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping user defined struct "), *definedStruct->GetFullName());

	resultJson->SetStringField(TEXT("StructName"), definedStruct->GetPathName());
	resultJson->SetStringField(TEXT("Guid"), definedStruct->Guid.ToString());

	void* allocatedDefaultInstance = FMemory::Malloc(definedStruct->GetStructureSize());
	definedStruct->InitializeStruct(allocatedDefaultInstance);
	TArray<TSharedPtr<FJsonValue>> fields;
	for (TFieldIterator<UProperty> It(definedStruct, EFieldIteratorFlags::ExcludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::ExcludeInterfaces); It; ++It) {
		UProperty* Property = *It;
		const TSharedPtr<FJsonObject>& fieldEntry = CreateFieldDescriptor(Property, allocatedDefaultInstance, nullptr, nullptr);
		if (fieldEntry.IsValid()) {
			fields.Add(MakeShareable(new FJsonValueObject(fieldEntry)));
		}
	}
	FMemory::Free(allocatedDefaultInstance);
	resultJson->SetArrayField(TEXT("Fields"), fields);
	return resultJson;
}

TSharedRef<FJsonObject> dumpBlueprintContent(UBlueprintGeneratedClass* generatedClass) {
	TSharedRef<FJsonObject> resultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping blueprint class "), *generatedClass->GetFullName());

	resultJson->SetStringField(TEXT("Blueprint"), generatedClass->GetPathName());
	resultJson->SetStringField(TEXT("ParentClass"), generatedClass->GetSuperClass()->GetPathName());

	TArray<TSharedPtr<FJsonValue>> implementedInterfaces;
	for (const FImplementedInterface& iface : generatedClass->Interfaces) {
		UClass* interfaceClass = iface.Class;
		TSharedRef<FJsonValueString> string = MakeShareable(new FJsonValueString(interfaceClass->GetPathName()));
		implementedInterfaces.Add(string);
	}
	if (implementedInterfaces.Num() > 0) {
		resultJson->SetArrayField(TEXT("ImplementedInterfaces"), implementedInterfaces);
	}
	
	if (isBlacklistedClass(generatedClass->GetPathName())) {
		return resultJson;
	}

	TArray<TSharedPtr<FJsonValue>> fields;
	UObject* defaultObject = generatedClass->GetDefaultObject();
	UObject* parentObject = generatedClass->GetSuperClass()->GetDefaultObject();
	for (TFieldIterator<UProperty> It(generatedClass, DEFAULT_ITERATOR_FLAGS); It; ++It) {
		UProperty* Property = *It;
		const TSharedPtr<FJsonObject>& fieldEntry = CreateFieldDescriptor(Property, defaultObject, defaultObject, parentObject);
		if (fieldEntry.IsValid()) {
			fields.Add(MakeShareable(new FJsonValueObject(fieldEntry)));
		}
	}
	if (fields.Num() > 0) {
		resultJson->SetArrayField(TEXT("Fields"), fields);
	}

	TArray<TSharedPtr<FJsonValue>> methods;
	for (TFieldIterator<UFunction> It(generatedClass, EFieldIteratorFlags::ExcludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::ExcludeInterfaces); It; ++It) {
		UFunction* Function = *It;
		const TSharedPtr<FJsonObject>& methodEntry = CreateFunctionSignature(Function);
		if (methodEntry.IsValid()) {
			methods.Add(MakeShareable(new FJsonValueObject(methodEntry)));
		}
	}
	if (methods.Num() > 0) {
		resultJson->SetArrayField(TEXT("Functions"), methods);
	}

	return resultJson;
}

void SML::dumpSatisfactoryAssets(const FName& rootPath, const FString& fileName) {
	SML::Logging::info(TEXT("Dumping assets on path "), *rootPath.ToString(), TEXT(" to json file "), *fileName);
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	TArray<FAssetData> FoundAssets;
	AssetRegistry.GetAssetsByPath(rootPath, FoundAssets, true, false);
	SML::Logging::info(*FString::Printf(TEXT("[FG Asset Dumper] FactoryGame total Assets to Dump: %d"), FoundAssets.Num()));

	TArray<TSharedPtr<FJsonValue>> blueprints;
	TArray<TSharedPtr<FJsonValue>> userDefinedStructs;
	TArray<TSharedPtr<FJsonValue>> userDefinedEnums;
	
	for (const FAssetData& assetData : FoundAssets) {
		const FString& assetClass = assetData.AssetClass.ToString();
		if (assetClass == TEXT("UserDefinedStruct")) {
			UObject* assetObject = assetData.GetAsset();
			UUserDefinedStruct* definedStruct = Cast<UUserDefinedStruct>(assetObject);
			if (definedStruct != nullptr) {
				const TSharedRef<FJsonObject>& classJson = dumpUserDefinedStruct(definedStruct);
				userDefinedStructs.Add(MakeShareable(new FJsonValueObject(classJson)));
			}
		}
		if (assetClass == TEXT("UserDefinedEnum")) {
			UObject* assetObject = assetData.GetAsset();
			UUserDefinedEnum* definedEnum = Cast<UUserDefinedEnum>(assetObject);
			if (definedEnum != nullptr) {
				const TSharedRef<FJsonObject>& classJson = dumpUserDefinedEnum(definedEnum);
				userDefinedEnums.Add(MakeShareable(new FJsonValueObject(classJson)));
			}
		}
		if (assetClass.Contains(TEXT("Blueprint"))) {
			FString resultPath = assetData.ObjectPath.ToString().Append(TEXT("_C"));
			UObject* assetObject = StaticLoadObject(UObject::StaticClass(), nullptr, *resultPath);
			UBlueprintGeneratedClass* generatedClass = Cast<UBlueprintGeneratedClass>(assetObject);
			if (generatedClass != nullptr) {
				const TSharedRef<FJsonObject>& classJson = dumpBlueprintContent(generatedClass);
				blueprints.Add(MakeShareable(new FJsonValueObject(classJson)));
			}
		}
	}
	TSharedRef<FJsonObject> resultObject = MakeShareable(new FJsonObject());
	resultObject->SetArrayField(TEXT("UserDefinedEnums"), userDefinedEnums);
	resultObject->SetArrayField(TEXT("UserDefinedStructs"), userDefinedStructs);
	resultObject->SetArrayField(TEXT("Bluepirnts"), blueprints);

	const FString& resultPath = SML::getConfigDirectory() / *fileName;
	FString resultString;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
	FJsonSerializer Serializer;
	Serializer.Serialize(resultObject, writer);
	FFileHelper::SaveStringToFile(resultString, *resultPath, FFileHelper::EEncodingOptions::ForceUTF8);
	SML::Logging::info(TEXT("Dumping finished!"));
}
