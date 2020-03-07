#include "FGAssetDumper.h"
#include "IAssetRegistry.h"
#include "AssetRegistryModule.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "Json.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/MemberReference.h"

#define DEFAULT_ITERATOR_FLAGS EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::IncludeInterfaces

//Defined Originally In EDGraphSchema_K2.h, re-implemented below to work out of Editor.
//Note that some information cannot be recovered because UObject metadata is missing
bool ConvertPropertyToPinType(const UProperty* Property, /*out*/ FEdGraphPinType& TypeOut);

TSharedRef<FJsonObject> CreatePropertyTypeDescriptor(UProperty* Property) {
	FEdGraphPinType graphPinType;
	ConvertPropertyToPinType(Property, graphPinType);
	TSharedRef<FJsonObject> typeEntry = MakeShareable(new FJsonObject());
	typeEntry->SetStringField(TEXT("PinCategory"), graphPinType.PinCategory.ToString());
	typeEntry->SetStringField(TEXT("PinSubCategory"), graphPinType.PinCategory.ToString());

	UObject* subCategoryObject = graphPinType.PinSubCategoryObject.Get();
	if (subCategoryObject != nullptr) {
		typeEntry->SetStringField(TEXT("PinSubCategoryObject"), subCategoryObject->GetPathName());
	}

	const FSimpleMemberReference& memberRef = graphPinType.PinSubCategoryMemberReference;
	if (memberRef.MemberGuid.IsValid()) {
		TSharedRef<FJsonObject> memberReference = MakeShareable(new FJsonObject());
		if (memberRef.MemberParent != nullptr) {
			memberReference->SetStringField(TEXT("MemberParent"), memberRef.MemberParent->GetPathName());
		}
		memberReference->SetStringField(TEXT("MemberName"), memberRef.MemberName.ToString());
		memberReference->SetStringField(TEXT("MemberGuid"), memberRef.MemberGuid.ToString());
		typeEntry->SetObjectField(TEXT("PinSubCategoryMemberReference"), memberReference);
	}
	
	if (graphPinType.ContainerType == EPinContainerType::Map) {
		TSharedRef<FJsonObject> pinValueType = MakeShareable(new FJsonObject());
		pinValueType->SetStringField(TEXT("TerminalCategory"), graphPinType.PinValueType.TerminalCategory.ToString());
		pinValueType->SetStringField(TEXT("TerminalSubCategory"), graphPinType.PinValueType.TerminalSubCategory.ToString());
		UObject* terminalSubCategoryObject = graphPinType.PinValueType.TerminalSubCategoryObject.Get();
		if (terminalSubCategoryObject != nullptr) {
			pinValueType->SetStringField(TEXT("TerminalSubCategoryObject"), terminalSubCategoryObject->GetPathName());
		}
		pinValueType->SetBoolField(TEXT("TerminalIsConst"), graphPinType.PinValueType.bTerminalIsConst);
		pinValueType->SetBoolField(TEXT("TerminalIsWeakPointer"), graphPinType.PinValueType.bTerminalIsWeakPointer);
		typeEntry->SetObjectField(TEXT("PinValueType"), pinValueType);
	}

	if (graphPinType.ContainerType != EPinContainerType::None) {
		typeEntry->SetNumberField(TEXT("ContainerType"), static_cast<uint8>(graphPinType.ContainerType));
	}
	if (graphPinType.bIsReference) {
		typeEntry->SetBoolField(TEXT("IsReference"), graphPinType.bIsReference);
	}
	if (graphPinType.bIsConst) {
		typeEntry->SetBoolField(TEXT("IsConst"), graphPinType.bIsConst);
	}
	if (graphPinType.bIsWeakPointer) {
		typeEntry->SetBoolField(TEXT("IsWeakPointer"), graphPinType.bIsWeakPointer);
	}
	return typeEntry;
}

TSharedPtr<FJsonObject> CreateFieldDescriptor(UProperty* Property, const void* defaultObjectPtr, UObject* defaultObject, UObject* parentObject) {
	TSharedRef<FJsonObject> fieldEntry = MakeShareable(new FJsonObject());
	fieldEntry->SetStringField(TEXT("Name"), Property->GetFName().ToString());
	bool isParentProperty = false;
	
	if (defaultObjectPtr != nullptr) {
		FString resultValueString;
		const void* propertyValue = Property->ContainerPtrToValuePtr<void>(defaultObjectPtr);

		if (parentObject != nullptr && parentObject->IsA(static_cast<UClass*>(Property->GetOuter()))) {
			isParentProperty = true;
			const void* defaultPropertyValue = Property->ContainerPtrToValuePtr<void>(parentObject);
			if (Property->Identical(propertyValue, defaultPropertyValue)) {
				return TSharedPtr<FJsonObject>(); //skip value if it is the same as in the parent class
			}
		}
		Property->ExportTextItem(resultValueString, propertyValue, propertyValue, defaultObject, 0);
		//only add field value if their default value is not empty or nullptr
		if (resultValueString != TEXT("") && resultValueString != TEXT("None")) {
			fieldEntry->SetStringField(TEXT("Value"), resultValueString);
		}
	}

	//do not include attributes and type for parent properties, they are already defined, we need name and value only
	if (!isParentProperty) {
		fieldEntry->SetObjectField(TEXT("PinType"), CreatePropertyTypeDescriptor(Property));
		fieldEntry->SetNumberField(TEXT("PropertyFlags"), Property->PropertyFlags);
	}
	
	return fieldEntry;
}

TSharedRef<FJsonObject> CreateFunctionSignature(UFunction* function) {
	TSharedRef<FJsonObject> resultJson = MakeShareable(new FJsonObject());
	resultJson->SetStringField(TEXT("Name"), function->GetFName().ToString());

	TArray<TSharedPtr<FJsonValue>> argumentArray;
	for (TFieldIterator<UProperty> It(function); It && (It->PropertyFlags & CPF_Parm); ++It) {
		if (It->PropertyFlags & CPF_ReturnParm) {
			TSharedPtr<FJsonObject> ReturnType = MakeShareable(new FJsonObject());
			ReturnType->SetStringField(TEXT("Name"), It->GetFName().ToString());
			ReturnType->SetObjectField(TEXT("PinType"), CreatePropertyTypeDescriptor(*It));
			resultJson->SetObjectField(TEXT("ReturnType"), ReturnType);
		} else {
			TSharedPtr<FJsonObject> ReturnType = MakeShareable(new FJsonObject());
			ReturnType->SetStringField(TEXT("Name"), It->GetFName().ToString());
			ReturnType->SetObjectField(TEXT("PinType"), CreatePropertyTypeDescriptor(*It));
			argumentArray.Add(MakeShareable(new FJsonValueObject(ReturnType)));
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

UClass* GetOverridenFunctionSource(UFunction* Function) {
	UClass* OuterClass = Cast<UClass>(Function->GetOuter());
	if (OuterClass->GetSuperClass()->FindFunctionByName(Function->GetFName()) != nullptr)
		return OuterClass->GetSuperClass(); //function is defined in super class, overriden in child
	
	for (const FImplementedInterface& Iface : OuterClass->Interfaces) {
		if (Iface.Class->FindFunctionByName(Function->GetFName()) != nullptr)
			return Iface.Class; //function is defined in interface, overriden in child
	}
	//function is not defined in parents
	return nullptr;
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
		UClass* FunctionOverrideSrc = GetOverridenFunctionSource(Function);
		if (FunctionOverrideSrc == nullptr) {
			//for blueprint defined functions, record full signature
			const TSharedPtr<FJsonObject>& methodEntry = CreateFunctionSignature(Function);
			if (methodEntry.IsValid()) {
				methods.Add(MakeShareable(new FJsonValueObject(methodEntry)));
			}
		} else {
			//For overriden functions, record only their name
			TSharedPtr<FJsonObject> methodEntry = MakeShareable(new FJsonObject());
			methodEntry->SetStringField(TEXT("Name"), Function->GetFName().ToString());
			methodEntry->SetStringField(TEXT("SuperClass"), FunctionOverrideSrc->GetPathName());
			methodEntry->SetBoolField(TEXT("IsOverride"), true);
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
	resultObject->SetArrayField(TEXT("Blueprints"), blueprints);

	const FString& resultPath = SML::getConfigDirectory() / *fileName;
	FString resultString;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
	FJsonSerializer Serializer;
	Serializer.Serialize(resultObject, writer);
	FFileHelper::SaveStringToFile(resultString, *resultPath, FFileHelper::EEncodingOptions::ForceUTF8);
	SML::Logging::info(TEXT("Dumping finished!"));
}

//------------------------------------------------------------------
//CODE BELOW IS STRAIGHT COPIED FROM EDGraphSchema_K2.cpp
//BECAUSE IT IS EDITOR-ONLY MODULE WHICH DOESN'T EXIST IN SHIPPING
//Some code was cut off because we don't have editor-only data like function object metadata
//------------------------------------------------------------------

const FName PC_Exec(TEXT("exec"));
const FName PC_Boolean(TEXT("bool"));
const FName PC_Byte(TEXT("byte"));
const FName PC_Class(TEXT("class"));
const FName PC_Int(TEXT("int"));
const FName PC_Int64(TEXT("int64"));
const FName PC_Float(TEXT("float"));
const FName PC_Name(TEXT("name"));
const FName PC_Delegate(TEXT("delegate"));
const FName PC_MCDelegate(TEXT("mcdelegate"));
const FName PC_Object(TEXT("object"));
const FName PC_Interface(TEXT("interface"));
const FName PC_String(TEXT("string"));
const FName PC_Text(TEXT("text"));
const FName PC_Struct(TEXT("struct"));
const FName PC_Wildcard(TEXT("wildcard"));
const FName PC_Enum(TEXT("enum"));
const FName PC_SoftObject(TEXT("softobject"));
const FName PC_SoftClass(TEXT("softclass"));
const FName PSC_Self(TEXT("self"));
const FName PSC_Index(TEXT("index"));
const FName PSC_Bitmask(TEXT("bitmask"));
const FName PN_Execute(TEXT("execute"));

bool GetPropertyCategoryInfo(const UProperty* TestProperty, FName& OutCategory, FName& OutSubCategory, UObject*& OutSubCategoryObject, bool& bOutIsWeakPointer);

bool ConvertPropertyToPinType(const UProperty* Property, /*out*/ FEdGraphPinType& TypeOut) {
	if (Property == nullptr) {
		TypeOut.PinCategory = TEXT("bad_type");
		return false;
	}

	TypeOut.PinSubCategory = NAME_None;

	// Handle whether or not this is an array property
	const UMapProperty* MapProperty = Cast<const UMapProperty>(Property);
	const USetProperty* SetProperty = Cast<const USetProperty>(Property);
	const UArrayProperty* ArrayProperty = Cast<const UArrayProperty>(Property);
	const UProperty* TestProperty = Property;
	if (MapProperty) {
		TestProperty = MapProperty->KeyProp;

		// set up value property:
		UObject* SubCategoryObject = nullptr;
		bool bIsWeakPtr = false;
		bool bResult = GetPropertyCategoryInfo(MapProperty->ValueProp, TypeOut.PinValueType.TerminalCategory, TypeOut.PinValueType.TerminalSubCategory, SubCategoryObject, bIsWeakPtr);
		TypeOut.PinValueType.TerminalSubCategoryObject = SubCategoryObject;

		if (bIsWeakPtr) {
			return false;
		}

		if (!bResult) {
			return false;
		}
	} else if (SetProperty) {
		TestProperty = SetProperty->ElementProp;
	} else if (ArrayProperty) {
		TestProperty = ArrayProperty->Inner;
	}
	TypeOut.ContainerType = FEdGraphPinType::ToPinContainerType(ArrayProperty != nullptr, SetProperty != nullptr, MapProperty != nullptr);
	TypeOut.bIsReference = Property->HasAllPropertyFlags(CPF_OutParm | CPF_ReferenceParm);
	TypeOut.bIsConst = Property->HasAllPropertyFlags(CPF_ConstParm);

	// Check to see if this is the wildcard property for the target container type
	if (const UMulticastDelegateProperty* MulticastDelegateProperty = Cast<const UMulticastDelegateProperty>(TestProperty)) {
		TypeOut.PinCategory = PC_MCDelegate;
		FMemberReference::FillSimpleMemberReference<UFunction>(MulticastDelegateProperty->SignatureFunction, TypeOut.PinSubCategoryMemberReference);
	} else if (const UDelegateProperty* DelegateProperty = Cast<const UDelegateProperty>(TestProperty)) {
		TypeOut.PinCategory = PC_Delegate;
		FMemberReference::FillSimpleMemberReference<UFunction>(DelegateProperty->SignatureFunction, TypeOut.PinSubCategoryMemberReference);
	} else {
		UObject* SubCategoryObject = nullptr;
		bool bIsWeakPointer = false;
		bool bResult = GetPropertyCategoryInfo(TestProperty, TypeOut.PinCategory, TypeOut.PinSubCategory, SubCategoryObject, bIsWeakPointer);
		TypeOut.bIsWeakPointer = bIsWeakPointer;
		TypeOut.PinSubCategoryObject = SubCategoryObject;
		if (!bResult) {
			return false;
		}
	}
	return true;
}

bool GetPropertyCategoryInfo(const UProperty* TestProperty, FName& OutCategory, FName& OutSubCategory, UObject*& OutSubCategoryObject, bool& bOutIsWeakPointer) {
	if (const UInterfaceProperty* InterfaceProperty = Cast<const UInterfaceProperty>(TestProperty)) {
		OutCategory = PC_Interface;
		OutSubCategoryObject = InterfaceProperty->InterfaceClass;
	} else if (const UClassProperty* ClassProperty = Cast<const UClassProperty>(TestProperty)) {
		OutCategory = PC_Class;
		OutSubCategoryObject = ClassProperty->MetaClass;
	} else if (const USoftClassProperty* SoftClassProperty = Cast<const USoftClassProperty>(TestProperty)) {
		OutCategory = PC_SoftClass;
		OutSubCategoryObject = SoftClassProperty->MetaClass;
	} else if (const USoftObjectProperty* SoftObjectProperty = Cast<const USoftObjectProperty>(TestProperty)) {
		OutCategory = PC_SoftObject;
		OutSubCategoryObject = SoftObjectProperty->PropertyClass;
	} else if (const UObjectPropertyBase* ObjectProperty = Cast<const UObjectPropertyBase>(TestProperty)) {
		OutCategory = PC_Object;
		OutSubCategoryObject = ObjectProperty->PropertyClass;
		bOutIsWeakPointer = TestProperty->IsA(UWeakObjectProperty::StaticClass());
	} else if (const UStructProperty* StructProperty = Cast<const UStructProperty>(TestProperty)) {
		OutCategory = PC_Struct;
		OutSubCategoryObject = StructProperty->Struct;
	} else if (TestProperty->IsA<UFloatProperty>()) {
		OutCategory = PC_Float;
	} else if (TestProperty->IsA<UInt64Property>()) {
		OutCategory = PC_Int64;
	} else if (TestProperty->IsA<UIntProperty>()) {
		OutCategory = PC_Int;
	} else if (const UByteProperty* ByteProperty = Cast<const UByteProperty>(TestProperty)) {
		OutCategory = PC_Byte;
		OutSubCategoryObject = ByteProperty->Enum;
	} else if (const UEnumProperty* EnumProperty = Cast<const UEnumProperty>(TestProperty)) {
		// K2 only supports byte enums right now - any violations should have been caught by UHT or the editor
		if (!EnumProperty->GetUnderlyingProperty()->IsA<UByteProperty>()) {
			OutCategory = TEXT("unsupported_enum_type");
			return false;
		}

		OutCategory = PC_Byte;
		OutSubCategoryObject = EnumProperty->GetEnum();
		
	} else if (TestProperty->IsA<UNameProperty>()) {
		OutCategory = PC_Name;
	} else if (TestProperty->IsA<UBoolProperty>()) {
		OutCategory = PC_Boolean;
	} else if (TestProperty->IsA<UStrProperty>()) {
		OutCategory = PC_String;
	} else if (TestProperty->IsA<UTextProperty>()) {
		OutCategory = PC_Text;
	} else {
		OutCategory = TEXT("bad_type");
		return false;
	}

	return true;
}
