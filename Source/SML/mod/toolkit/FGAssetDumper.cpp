#include "FGAssetDumper.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "Json.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/MemberReference.h"
#include "IPlatformFilePak.h"
#include <excpt.h>
#include "ExceptionHandling.h"

#define DEFAULT_ITERATOR_FLAGS EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::IncludeInterfaces

struct FSerializationObjectInfo {
	uint32 ObjectId;
	TSet<FString> AlreadySerializedSubobjects;
	bool bIsReferenced = false;
};

struct FSerializationContext {
	TMap<const void*, FSerializationObjectInfo> SerializationStack;
	uint32 CurrentObjectIndex = 1;
};

//Defined Originally In EDGraphSchema_K2.h, re-implemented below to work out of Editor.
//Note that some information cannot be recovered because UObject metadata is missing
bool ConvertPropertyToPinType(const UProperty* Property, /*out*/ FEdGraphPinType& TypeOut);

//Performs property serialization. Defined below.
TSharedPtr<FJsonValue> SerializePropertyValue(const UProperty* TestProperty, const void* Value, FSerializationContext& Context);

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

bool CheckValueEqualDefault(UProperty* Property, const void* PropertyValue) {
	const SIZE_T PropertyValueSize = Property->GetSize();
	void* DefaultValue = FMemory::Malloc(PropertyValueSize);
	Property->InitializeValue(DefaultValue);
	const bool bRes = Property->Identical(PropertyValue, DefaultValue);
	FMemory::Free(DefaultValue);
	return bRes;
}

UClass* FindFirstClassWithValueOverride(UObject* ClassObject, UProperty* Property) {
	UClass* EndClass = Cast<UClass>(Property->GetOuter());
	UClass* TargetClass = ClassObject->GetClass();
	void* CurrentValue = Property->ContainerPtrToValuePtr<void>(ClassObject);
	while (TargetClass != EndClass) {
		UClass* ParentClass = TargetClass->GetSuperClass();
		UObject* ParentClassObject = ParentClass->GetDefaultObject();
		void* ParentPropertyValue = Property->ContainerPtrToValuePtr<void>(ParentClassObject);
		if (!Property->Identical(CurrentValue, ParentPropertyValue)) {
			//Values are different! So TargetClass is the class where value is overriden
			return TargetClass;
		}
		//Values are the same, so parent class becomes next target class
		TargetClass = ParentClass;
		CurrentValue = ParentPropertyValue;
	}
	//value is the same as in the property initial class
	return EndClass;
}

bool CanSkipPropertyValue(UProperty* Property, UObject* ClassObject) {
	UClass* ClassWithValueOverride = FindFirstClassWithValueOverride(ClassObject, Property);
	//We can use parent value if it's not set in native class (we don't have .cpp for native classes in editor), and it's not us who set the value
	const bool bCanUseParentValue = ClassWithValueOverride != ClassObject->GetClass() && !ClassWithValueOverride->GetPathName().StartsWith(TEXT("/Script/FactoryGame."));
	const bool bIsValueEqualDefault = CheckValueEqualDefault(Property, Property->ContainerPtrToValuePtr<void>(ClassObject));
	//we can skip property value if we're able to use parent value or it is default value anyway
	return bCanUseParentValue || bIsValueEqualDefault;
}

TSharedPtr<FJsonObject> CreateFieldDescriptor(UProperty* Property, const void* defaultObjectPtr, UObject* defaultObject, FSerializationContext& Context) {
	TSharedRef<FJsonObject> fieldEntry = MakeShareable(new FJsonObject());
	fieldEntry->SetStringField(TEXT("Name"), Property->GetFName().ToString());
	bool bIsParentProperty = false;
	bool WroteFieldValue = false;
	
	if (defaultObjectPtr != nullptr) {
		const void* propertyValue = Property->ContainerPtrToValuePtr<void>(defaultObjectPtr);
		if (defaultObject != nullptr) {
			UClass* PropertyClass = Cast<UClass>(Property->GetOuter());
			//it is parent if we're net the property's outer
			bIsParentProperty = PropertyClass != defaultObject->GetClass();
		}
		if (defaultObject == nullptr || !CanSkipPropertyValue(Property, defaultObject)) {
			const TSharedPtr<FJsonValue> FieldValue = SerializePropertyValue(Property, propertyValue, Context);
			fieldEntry->SetField(TEXT("Value"), FieldValue);
			WroteFieldValue = true;
		}
	}
	//If we didn't write default value, and property is defined in parent, skip it
	if (!WroteFieldValue && bIsParentProperty)
		return TSharedPtr<FJsonObject>();
	
	//do not include attributes and type for parent properties, they are already defined, we need name and value only
	if (!bIsParentProperty) {
		fieldEntry->SetObjectField(TEXT("PinType"), CreatePropertyTypeDescriptor(Property));
		fieldEntry->SetNumberField(TEXT("PropertyFlags"), Property->PropertyFlags);
	}
	return fieldEntry;
}

TSharedRef<FJsonObject> CreateFunctionSignature(UFunction* function) {
	TSharedRef<FJsonObject> resultJson = MakeShareable(new FJsonObject());
	resultJson->SetStringField(TEXT("Name"), function->GetFName().ToString());

	TArray<TSharedPtr<FJsonValue>> argumentArray;
	TArray<TSharedPtr<FJsonValue>> outputsArray;
	for (TFieldIterator<UProperty> It(function); It && (It->PropertyFlags & CPF_Parm); ++It) {
		UProperty* Param = *It;
		TSharedPtr<FJsonObject> ParamType = MakeShareable(new FJsonObject());
		ParamType->SetStringField(TEXT("Name"), Param->GetFName().ToString());
		ParamType->SetObjectField(TEXT("PinType"), CreatePropertyTypeDescriptor(Param));
		const bool bIsFunctionInput = !Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm);
		if (bIsFunctionInput) {
			argumentArray.Add(MakeShareable(new FJsonValueObject(ParamType)));
		} else {
			outputsArray.Add(MakeShareable(new FJsonValueObject(ParamType)));
		}
	}
	resultJson->SetArrayField(TEXT("Arguments"), argumentArray);
	resultJson->SetArrayField(TEXT("Outputs"), outputsArray);
	
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

	FSerializationContext Context;
	void* allocatedDefaultInstance = FMemory::Malloc(definedStruct->GetStructureSize());
	definedStruct->InitializeStruct(allocatedDefaultInstance);
	TArray<TSharedPtr<FJsonValue>> fields;
	for (TFieldIterator<UProperty> It(definedStruct, EFieldIteratorFlags::ExcludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::ExcludeInterfaces); It; ++It) {
		UProperty* Property = *It;
		const TSharedPtr<FJsonObject>& fieldEntry = CreateFieldDescriptor(Property, allocatedDefaultInstance, nullptr, Context);
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

	FSerializationContext Context;
	TArray<TSharedPtr<FJsonValue>> fields;
	UObject* defaultObject = generatedClass->GetDefaultObject();
	Context.SerializationStack.Add(defaultObject, FSerializationObjectInfo{ 0 });
	for (TFieldIterator<UProperty> It(generatedClass, DEFAULT_ITERATOR_FLAGS); It; ++It) {
		UProperty* Property = *It;
		if (Property->GetFName().ToString() == TEXT("UberGraphFrame"))
			continue; //Skip graph frame pointer (cannot be meaningfully serialized)
		const TSharedPtr<FJsonObject>& fieldEntry = CreateFieldDescriptor(Property, defaultObject, defaultObject, Context);
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
		if (Function->GetFName().ToString().StartsWith(TEXT("ExecuteUbergraph_")))
			continue; //Skip autogenerated UBG execute function
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

FString CreateClassPathFromPackageName(const FString& PackagePath) {
	int32 PackageIndex;
	PackagePath.FindLastChar('/', PackageIndex);
	check(PackageIndex != INDEX_NONE);
	const FString ResultFileName = PackagePath.Mid(PackageIndex + 1);
	return FString::Printf(TEXT("%s.%s_C"), *PackagePath, *ResultFileName);
}

void dumpSatisfactoryAssetsInternal(const FName& rootPath, const FString& fileName) {
	SML::Logging::info(TEXT("Dumping assets on path "), *rootPath.ToString(), TEXT(" to json file "), *fileName);
	TArray<TSharedPtr<FJsonValue>> blueprints;
	TArray<TSharedPtr<FJsonValue>> userDefinedStructs;
	TArray<TSharedPtr<FJsonValue>> userDefinedEnums;

	TSet<FString> ResultAssetList;
	FPakPlatformFile* PakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().GetPlatformFile(TEXT("PakFile")));
	PakPlatformFile->IterateDirectoryRecursively(TEXT("../../../FactoryGame/Content/"), [&ResultAssetList](const TCHAR* FileName, bool IsDirectory) {
		if (!IsDirectory) {
			const FString PackageName = FPackageName::FilenameToLongPackageName(FileName);
			ResultAssetList.Add(PackageName);
		}
		return true;
	});
	for (const FString& PackageName : ResultAssetList) {
		UObject* LoadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *PackageName);
		if (LoadedObject == nullptr) {
			//Will happen for blueprints. UBlueprints don't exist in cooked game, and they are considered PrimaryAsset for their package.
			//So we need to retrieve full BlueprintGeneratedClass path from UBlueprint path
			FString BlueprintClassPath = CreateClassPathFromPackageName(PackageName);
			LoadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *BlueprintClassPath);
		}
		if (LoadedObject == nullptr)
			continue; //Can happen sometimes for some assets actually
		if (LoadedObject->IsA(UUserDefinedStruct::StaticClass())) {
			UUserDefinedStruct* definedStruct = Cast<UUserDefinedStruct>(LoadedObject);
			if (definedStruct != nullptr) {
				const TSharedRef<FJsonObject>& classJson = dumpUserDefinedStruct(definedStruct);
				userDefinedStructs.Add(MakeShareable(new FJsonValueObject(classJson)));
			}
		}
		if (LoadedObject->IsA(UUserDefinedEnum::StaticClass())) {
			UUserDefinedEnum* definedEnum = Cast<UUserDefinedEnum>(LoadedObject);
			if (definedEnum != nullptr) {
				const TSharedRef<FJsonObject>& classJson = dumpUserDefinedEnum(definedEnum);
				userDefinedEnums.Add(MakeShareable(new FJsonValueObject(classJson)));
			}
		}
		if (LoadedObject->IsA(UBlueprintGeneratedClass::StaticClass())) {
			UBlueprintGeneratedClass* generatedClass = Cast<UBlueprintGeneratedClass>(LoadedObject);
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

void SML::dumpSatisfactoryAssets(const FName& rootPath, const FString& fileName) {
	__try {
		dumpSatisfactoryAssetsInternal(rootPath, fileName);
	} __except (1) {
		uint64 ExCode = GetExceptionCode();
		SML::Logging::info(TEXT("Windows SEG Exception Code: "), ExCode);
	}
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

//Note that CDO's don't call this method, they call SerializePropertyValue directly,
//so it is safe to assume that passed value is not a class default object
//Note that DefaultValue can be nullptr, because not all structs have default values
bool ShouldSerializeProperty(UProperty* Property, const void* Value, const void* DefaultValue) {
	if (Property->HasAnyPropertyFlags(EPropertyFlags::CPF_Transient) ||
		Property->HasAnyPropertyFlags(EPropertyFlags::CPF_DuplicateTransient))
		return false; //Skip transient properties (they should be persisted only for CDOs)
	if (DefaultValue != nullptr && Property->Identical(Value, DefaultValue))
		return false; //Skip serialization if value is the same as in the object's defaults
	//Can serialize now probably
	return true;
}

void SerializeFieldsInternal(UStruct* Struct, const void* Object, const void* DefaultObject, const TSharedRef<FJsonObject>& ObjectJson, FSerializationContext& Context) {
	for (TFieldIterator<UProperty> It(Struct); It; ++It) {
		UProperty* Property = *It;
		const void* PropertyValue = Property->ContainerPtrToValuePtr<void>(Object);
		const void* DefaultPropertyValue = DefaultObject ? Property->ContainerPtrToValuePtr<void>(DefaultObject) : nullptr;
		if (ShouldSerializeProperty(Property, PropertyValue, DefaultPropertyValue)) {
			TSharedPtr<FJsonValue> Value = SerializePropertyValue(Property, PropertyValue, Context);
			ObjectJson->SetField(Property->GetFName().ToString(), Value);
		}
	}
}

TSharedPtr<FJsonValue> SerializeStruct(UScriptStruct* StructType, const void* StructValue, FSerializationContext& Context) {
	const TSharedRef<FJsonObject> Object = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Serializing struct "), *StructType->GetPathName(), TEXT(" Address "), StructValue);
	void* DefaultObject = nullptr;
	if (UUserDefinedStruct* UserDefinedStruct = Cast<UUserDefinedStruct>(StructType)) {
		DefaultObject = FMemory::Malloc(StructType->GetStructureSize());
		StructType->InitializeStruct(DefaultObject);
	}
	SerializeFieldsInternal(StructType, StructValue, DefaultObject, Object, Context);
	if (DefaultObject != nullptr) {
		FMemory::Free(DefaultObject);
	}
	return MakeShareable(new FJsonValueObject(Object));
}

bool CheckObjectNotSerializedAlready(const UObject* Object, FSerializationContext& Context) {
	const FString SelfObjectName = Object->GetFName().ToString();
	
	FSerializationObjectInfo* OuterObjectInfo = Context.SerializationStack.Find(Object->GetOuter());
	SML::Logging::info(TEXT("Object's "), *Object->GetPathName(), TEXT(" Outer: "), *Object->GetOuter()->GetPathName(), TEXT(" ; Info = "), OuterObjectInfo);
	if (OuterObjectInfo == nullptr)
		return true;
	if (OuterObjectInfo->AlreadySerializedSubobjects.Contains(SelfObjectName)) {
		return false;
	}
	OuterObjectInfo->AlreadySerializedSubobjects.Add(SelfObjectName);
	return true;
}

TSharedPtr<FJsonValue> SerializeUObject(const UObject* Object, FSerializationContext& Context) {
	const TSharedRef<FJsonObject> ObjectJson = MakeShareable(new FJsonObject());
	if (Object == nullptr) {
		ObjectJson->SetBoolField(TEXT("$Empty"), true);
	} else if (Object->IsAsset()) {
		//For asset we only need to serialize asset path
		ObjectJson->SetStringField(TEXT("$AssetPath"), Object->GetPathName());
	} else if (FSerializationObjectInfo* ObjectInfo = Context.SerializationStack.Find(Object)) {
		//Object is already written as outer, so we need just object index
		ObjectJson->SetNumberField(TEXT("$ObjectRef"), ObjectInfo->ObjectId);
		ObjectInfo->bIsReferenced = true;
	} else if (!CheckObjectNotSerializedAlready(Object, Context)) {
		//Object with such name already exists within given outer, so we need just it's name as reference
		FSerializationObjectInfo* OuterObjectInfo = Context.SerializationStack.Find(Object->GetOuter());
		ObjectJson->SetNumberField(TEXT("$OuterObjectRef"), OuterObjectInfo->ObjectId);
		ObjectJson->SetStringField(TEXT("$ObjectNameRef"), Object->GetFName().ToString());
	} else {
		//Object is not written, write it
		SML::Logging::info(TEXT("Recursively serializing object "), *Object->GetPathName());
		UClass* ObjectClass = Object->GetClass();
		const void* DefaultObject = ObjectClass->GetDefaultObject();
		//Start name with $ which cannot appear in UE property names to avoid conflicts
		ObjectJson->SetStringField(TEXT("$ObjectClass"), ObjectClass->GetPathName());
		ObjectJson->SetNumberField(TEXT("$ObjectFlags"), static_cast<uint32>(Object->GetFlags()));
		ObjectJson->SetStringField(TEXT("$ObjectName"), Object->GetFName().ToString());
		const uint32 ObjectIndex = Context.CurrentObjectIndex++;
		Context.SerializationStack.Add(Object, FSerializationObjectInfo{ ObjectIndex });
		
		SerializeFieldsInternal(ObjectClass, Object, DefaultObject, ObjectJson, Context);

		const bool bWasReferenced = Context.SerializationStack.FindAndRemoveChecked(Object).bIsReferenced;
		Context.CurrentObjectIndex--;
		if (bWasReferenced) {
			ObjectJson->SetNumberField(TEXT("$ObjectIndex"), ObjectIndex);
		}
	}
	return MakeShareable(new FJsonValueObject(ObjectJson));
}

TSharedPtr<FJsonValue> SerializePropertyValueInternal(const UProperty* TestProperty, const void* Value, FSerializationContext& Context);

TSharedPtr<FJsonValue> SerializePropertyValue(const UProperty* Property, const void* Value, FSerializationContext& Context) {
	SML::Logging::info(TEXT("Serialize property "), *Property->GetFName().ToString(), TEXT(" of class "), *Property->GetOuter()->GetPathName(), TEXT(" value with type "), *Property->GetClass()->GetName());
	const UMapProperty* MapProperty = Cast<const UMapProperty>(Property);
	const USetProperty* SetProperty = Cast<const USetProperty>(Property);
	const UArrayProperty* ArrayProperty = Cast<const UArrayProperty>(Property);
	if (MapProperty) {
		const UProperty* KeyProperty = MapProperty->KeyProp;
		const UProperty* ValueProperty = MapProperty->ValueProp;
		FScriptMapHelper MapHelper(MapProperty, Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (int32 i = 0; i < MapHelper.Num(); i++) {
			TSharedPtr<FJsonValue> EntryKey = SerializePropertyValue(KeyProperty, MapHelper.GetKeyPtr(i), Context);
			TSharedPtr<FJsonValue> EntryValue = SerializePropertyValue(ValueProperty, MapHelper.GetValuePtr(i), Context);
			TSharedRef<FJsonObject> Pair = MakeShareable(new FJsonObject());
			Pair->SetField(TEXT("Key"), EntryKey);
			Pair->SetField(TEXT("Value"), EntryValue);
			ResultArray.Add(MakeShareable(new FJsonValueObject(Pair)));
		}
		return MakeShareable(new FJsonValueArray(ResultArray));
	} else if (SetProperty) {
		const UProperty* ElementProperty = SetProperty->ElementProp;
		FScriptSetHelper SetHelper(SetProperty, Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (int32 i = 0; i < SetHelper.Num(); i++) {
			TSharedPtr<FJsonValue> Element = SerializePropertyValue(ElementProperty, SetHelper.GetElementPtr(i), Context);
			ResultArray.Add(Element);
		}
		return MakeShareable(new FJsonValueArray(ResultArray));
		
	} else if (ArrayProperty) {
		const UProperty* ElementProperty = ArrayProperty->Inner;
		FScriptArrayHelper ArrayHelper(ArrayProperty, Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (int32 i = 0; i < ArrayHelper.Num(); i++) {
			TSharedPtr<FJsonValue> Element = SerializePropertyValue(ElementProperty, ArrayHelper.GetRawPtr(i), Context);
			ResultArray.Add(Element);
		}
		return MakeShareable(new FJsonValueArray(ResultArray));
	}

	// Check to see if this is the wildcard property for the target container type
	TSharedPtr<FJsonValue> Result = SerializePropertyValueInternal(Property, Value, Context);
	return Result;
}

//Copies data layout of FMulticastScriptDelegate, because Epic is retarded and made this field private
//Since TMulticastScriptDelegate doesn't have any virtual methods (so no vtable), it is (mostly) safe to assume that layout is the same
class FMulticastScriptDelegateAccessor {
	/** Ordered list functions to invoke when the Broadcast function is called */
public: TArray<FScriptDelegate> InvocationList;
};

TSharedPtr<FJsonValue> SerializePropertyValueInternal(const UProperty* TestProperty, const void* Value, FSerializationContext& Context) {
	if (TestProperty->IsA<UMulticastDelegateProperty>()) {
		//For multicast delegate, we need to serialize each script delegate
		const FMulticastScriptDelegateAccessor* DelegateMulti = reinterpret_cast<const FMulticastScriptDelegateAccessor*>(Value);
		TArray<TSharedPtr<FJsonValue>> ResultArray;
		for (const FScriptDelegate& Delegate : DelegateMulti->InvocationList) {
			if (Delegate.IsBound()) {
				TSharedPtr<FJsonObject> Object = MakeShareable(new FJsonObject());
				Object->SetField(TEXT("Object"), SerializeUObject(Delegate.GetUObject(), Context));
				Object->SetStringField(TEXT("FunctionName"), Delegate.GetFunctionName().ToString());
				ResultArray.Add(MakeShareable(new FJsonValueObject(Object)));
			}
		}
		return MakeShareable(new FJsonValueArray(ResultArray));

	} else if (TestProperty->IsA<UDelegateProperty>()) {
		//Single delegate, serialize object and function name
		const FScriptDelegate* Delegate = reinterpret_cast<const FScriptDelegate*>(Value);
		TSharedRef<FJsonObject> Object = MakeShareable(new FJsonObject());
		if (Delegate->IsBound()) {
			Object->SetField(TEXT("Object"), SerializeUObject(Delegate->GetUObject(), Context));
			Object->SetStringField(TEXT("FunctionName"), Delegate->GetFunctionName().ToString());
		}
		return MakeShareable(new FJsonValueObject(Object));
		
	} else if (TestProperty->IsA<UInterfaceProperty>()) {
		//UObject is enough to re-create value, since we known property on deserialization
		const FScriptInterface* Interface = reinterpret_cast<const FScriptInterface*>(Value);
		return SerializeUObject(Interface->GetObject(), Context);

	} else if (const UClassProperty* ClassProperty = Cast<const UClassProperty>(TestProperty)) {
		UClass* ClassObject = Cast<UClass>(ClassProperty->GetObjectPropertyValue(Value));
		//For class it's enough just to have it's path name for deserialization
		return MakeShareable(new FJsonValueString(ClassObject->GetPathName()));
		
	} else if (TestProperty->IsA<USoftObjectProperty>()) {
		//For soft object reference, path is enough too for deserialization.
		const FSoftObjectPtr* ObjectPtr = reinterpret_cast<const FSoftObjectPtr*>(Value);
		return MakeShareable(new FJsonValueString(ObjectPtr->ToSoftObjectPath().ToString()));
		
	} else if (const UObjectPropertyBase* ObjectProperty = Cast<const UObjectPropertyBase>(TestProperty)) {
		//Need to serialize full UObject for object property
		UObject* ObjectPointer = ObjectProperty->GetObjectPropertyValue(Value);
		return SerializeUObject(ObjectPointer, Context);
		
	} else if (const UStructProperty* StructProperty = Cast<const UStructProperty>(TestProperty)) {
		//To serialize struct, we need it's type and value pointer, because struct value doesn't contain type information
		return SerializeStruct(StructProperty->Struct, Value, Context);

	//Primitives below, they are serialized as plain json values
	} else if (const UNumericProperty* NumberProperty = Cast<const UNumericProperty>(TestProperty)) {
		double ResultValue;
		if (NumberProperty->IsFloatingPoint())
			ResultValue = NumberProperty->GetFloatingPointPropertyValue(Value);
		else ResultValue = NumberProperty->GetSignedIntPropertyValue(Value);
		return MakeShareable(new FJsonValueNumber(ResultValue));

	} else if (const UBoolProperty* BoolProperty = Cast<const UBoolProperty>(TestProperty)) {
		const bool bBooleanValue = BoolProperty->GetPropertyValue(Value);
		return MakeShareable(new FJsonValueBoolean(bBooleanValue));
		
	} else if (TestProperty->IsA<UStrProperty>()) {
		const FString& StringValue = *reinterpret_cast<const FString*>(Value);
		return MakeShareable(new FJsonValueString(StringValue));
		
	} else if (const UEnumProperty* EnumProperty = Cast<const UEnumProperty>(TestProperty)) {
		// K2 only supports byte enums right now - any violations should have been caught by UHT or the editor
		if (!EnumProperty->GetUnderlyingProperty()->IsA<UByteProperty>()) {
			SML::Logging::fatal(TEXT("Unsupported Underlying Enum Property Found: "), *EnumProperty->GetUnderlyingProperty()->GetClass()->GetName());
		}
		//Prefer readable enum names in result json to raw numbers
		const uint8 UnderlyingValue = *reinterpret_cast<const uint8*>(Value);
		const FString EnumName = EnumProperty->GetEnum()->GetNameByValue(UnderlyingValue).ToString();
		return MakeShareable(new FJsonValueString(EnumName));

	} else if (TestProperty->IsA<UNameProperty>()) {
		//Name is perfectly representable as string
		FName* Temp = ((FName*) Value);
		return MakeShareable(new FJsonValueString(Temp->ToString()));
		
	} else if (const UTextProperty* TextProperty = Cast<const UTextProperty>(TestProperty)) {
		FString ResultValue;
		const FText& TextValue = TextProperty->GetPropertyValue(Value);
		FTextStringHelper::WriteToBuffer(ResultValue, TextValue);
		return MakeShareable(new FJsonValueString(ResultValue));
	} else {
		SML::Logging::fatal(TEXT("Found unsupported property type when serializing value: "), *TestProperty->GetClass()->GetName());
		return TSharedPtr<FJsonValue>();
	}
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
