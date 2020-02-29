#include "FGAssetDumper.h"
#include "IAssetRegistry.h"
#include "AssetRegistryModule.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "util/json.hpp"

#define DEFAULT_ITERATOR_FLAGS EFieldIteratorFlags::ExcludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::ExcludeInterfaces

FString GetFunctionSignature(UFunction* function) {
	TArray<FString> argumentsList;
	FString returnType = TEXT("void");
	for (TFieldIterator<UProperty> It(function); It && (It->PropertyFlags & CPF_Parm); ++It) {
		if (It->PropertyFlags & CPF_ReturnParm) {
			returnType = It->GetCPPType(nullptr, 0);
		} else {
			argumentsList.Add(It->GetCPPType(nullptr, 0));
		}
	}
	FString prefixOperators;
	if (function->HasAllFunctionFlags(EFunctionFlags::FUNC_Static)) {
		prefixOperators += TEXT("static ");
	}
	return FString::Printf(TEXT("%s%s %s(%s);"), *prefixOperators, *returnType, *function->GetFName().ToString(), *FString::Join(argumentsList, TEXT(", ")));
}

nlohmann::json dumpBlueprintContent(UBlueprintGeneratedClass* generatedClass) {
	nlohmann::json resultJson;
	SML::Logging::info(TEXT("Members of class "), *generatedClass->GetFullName(), TEXT(":"));
	resultJson["Blueprint"] = convertStr(*generatedClass->GetPathName());
	resultJson["ParentClass"] = convertStr(*generatedClass->GetSuperClass()->GetPathName());
	nlohmann::json implementedInterfaces;
	for (const FImplementedInterface& iface : generatedClass->Interfaces) {
		UClass* interfaceClass = iface.Class;
		implementedInterfaces.push_back(convertStr(*interfaceClass->GetPathName()));
	}
	resultJson["ImplementedInterfaces"] = implementedInterfaces;
	
	nlohmann::json fields;
	UObject* defaultObject = generatedClass->GetDefaultObject();
	for (TFieldIterator<UProperty> It(generatedClass, DEFAULT_ITERATOR_FLAGS); It; ++It) {
		UProperty* Property = *It;
		FString resultValueString;
		const void* propertyValue = Property->ContainerPtrToValuePtr<void>(defaultObject);
		Property->ExportTextItem(resultValueString, propertyValue, propertyValue, defaultObject, 0);
		nlohmann::json fieldEntry;
		fieldEntry["Name"] = convertStr(*Property->GetFName().ToString());
		fieldEntry["CppType"] = convertStr(*Property->GetCPPType());
		fieldEntry["Value"] = convertStr(*resultValueString);
		fields.push_back(fieldEntry);
	}
	resultJson["Fields"] = fields;
	
	for (TFieldIterator<UFunction> It(generatedClass, DEFAULT_ITERATOR_FLAGS); It; ++It) {
		UFunction* Function = *It;
		//SML::Logging::info(*GetFunctionSignature(Function));
	}
	return resultJson;
}

void SML::dumpSatisfactoryAssets(const FName& rootPath, const FString& fileName) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	TArray<FAssetData> FoundAssets;
	nlohmann::json resultJsonArray;
	AssetRegistry.GetAssetsByPath(rootPath, FoundAssets, true, false);
	SML::Logging::info(*FString::Printf(TEXT("[FG Asset Dumper] FactoryGame total Assets to Dump: %d"), FoundAssets.Num()));
	for (const FAssetData& assetData : FoundAssets) {
		if (assetData.AssetClass.ToString().Contains("Blueprint")) {
			FString resultPath = assetData.ObjectPath.ToString().Append(TEXT("_C"));
			UObject* assetObject = StaticLoadObject(UObject::StaticClass(), nullptr, *resultPath);
			UBlueprintGeneratedClass* generatedClass = Cast<UBlueprintGeneratedClass>(assetObject);
			if (generatedClass != nullptr) {
				SML::Logging::info(TEXT("Members of class "), *resultPath, TEXT(":"));
				const nlohmann::json& classJson = dumpBlueprintContent(generatedClass);
				resultJsonArray.push_back(classJson);
			}
		}
	}
	const path& resultPath = SML::getConfigDirectory() / *fileName;
	const FString& resultString = convertStr(nlohmann::to_string(resultJsonArray).c_str()).c_str();
	FFileHelper::SaveStringToFile(resultString, resultPath.c_str());
}
