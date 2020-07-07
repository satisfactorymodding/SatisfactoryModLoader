#include "FGAssetDumper.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "Json.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/MemberReference.h"
#include "IPlatformFilePak.h"
#include "ExceptionHandling.h"
#include "Engine/ComponentDelegateBinding.h"
#include "WidgetAnimationDelegateBinding.h"
#include "BPCodeDumper.h"
#include "toolkit/PropertyTypeHandler.h"

#define DEFAULT_ITERATOR_FLAGS EFieldIteratorFlags::IncludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::IncludeInterfaces

struct FSerializationObjectInfo {
	uint32 ObjectId;
	bool bIsReferenced = false;
};

struct FSerializationContext {
	TMap<const void*, FSerializationObjectInfo> SerializationStack;
	uint32 CurrentObjectIndex = 1;
};

bool DumpSingleFile(TSharedRef<FJsonObject> ResultJson, FString Path, FString Folder);

//Performs property serialization. Defined below.
TSharedPtr<FJsonValue> SerializePropertyValue(const UProperty* TestProperty, const void* Value, FSerializationContext& Context);

TSharedPtr<FJsonValue> SerializeUObject(const UObject* Object, FSerializationContext& Context);

TSharedPtr<FJsonValue> SerializeStruct(UScriptStruct* StructType, const void* StructValue, FSerializationContext& Context);

TSharedRef<FJsonObject> CreatePropertyTypeDescriptor(UProperty* Property) {
	FEdGraphPinType graphPinType;
	FPropertyTypeHelper::ConvertPropertyToPinType(Property, graphPinType);
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
	resultJson->SetArrayField(TEXT("Code"), SML::CreateFunctionCode(function));
	return resultJson;
}

bool isBlacklistedClass(const FString& classPath) {
	return false;
}

TSharedRef<FJsonObject> dumpUserDefinedEnum(UUserDefinedEnum* definedEnum) {
	TSharedRef<FJsonObject> ResultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping user defined enum "), *definedEnum->GetFullName());

	ResultJson->SetStringField(TEXT("StructName"), definedEnum->GetPathName());
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
	ResultJson->SetArrayField(TEXT("Values"), enumValues);
	DumpSingleFile(ResultJson, definedEnum->GetPathName(), "Enums");
	return ResultJson;
}

TSharedRef<FJsonObject> dumpUserDefinedStruct(UUserDefinedStruct* definedStruct) {
	TSharedRef<FJsonObject> ResultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping user defined struct "), *definedStruct->GetFullName());

	ResultJson->SetStringField(TEXT("StructName"), definedStruct->GetPathName());
	ResultJson->SetStringField(TEXT("Guid"), definedStruct->Guid.ToString());

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
	ResultJson->SetArrayField(TEXT("Fields"), fields);
	DumpSingleFile(ResultJson, definedStruct->GetPathName(), "Structs");
	return ResultJson;
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

#define ENSURE_NODE_HAS_INDEX(Node) if (!SCSNodeToIndex.Contains(Node)) SCSNodeToIndex.Add(Node, LastSCSNodeIndex++);

#define SERIALIZE_TRACK(Variable, TrackType) \
	TArray<TSharedPtr<FJsonValue>> ##TrackType_Array; \
	for (TrackType& TrackObject : Timeline->##Variable) { \
		##TrackType_Array.Add(SerializeStruct(TrackType::StaticStruct(), &TrackObject, SerializationContext)); \
	} \
	Object->SetArrayField(TEXT(#Variable), ##TrackType_Array);

TSharedRef<FJsonObject> WriteConstructionScript(USimpleConstructionScript* SCS, TArray<FString>& FieldsGeneratedBySCS) {
	TSharedRef<FJsonObject> ConstructionScript = MakeShareable(new FJsonObject());
	TMap<USCS_Node*, uint32> SCSNodeToIndex;
	uint32 LastSCSNodeIndex = 1;
	TArray<TSharedPtr<FJsonValue>> AllSCSNodes;
	for (USCS_Node* SCSNode : SCS->GetAllNodes()) {
		ENSURE_NODE_HAS_INDEX(SCSNode);
		uint32 NodeIndex = SCSNodeToIndex.FindChecked(SCSNode);
		TSharedRef<FJsonObject> NodeObject = MakeShareable(new FJsonObject());
		NodeObject->SetNumberField(TEXT("NodeIndex"), NodeIndex);
		NodeObject->SetStringField(TEXT("VariableName"), SCSNode->GetVariableName().ToString());
		NodeObject->SetStringField(TEXT("VariableGuid"), SCSNode->VariableGuid.ToString());
		NodeObject->SetStringField(TEXT("ComponentClass"), SCSNode->ComponentClass->GetPathName());
		FSerializationContext SerializationContext;
		NodeObject->SetField(TEXT("ComponentTemplate"), SerializeUObject(SCSNode->ComponentTemplate, SerializationContext));
		NodeObject->SetStringField(TEXT("ParentComponentOrVariableName"), SCSNode->ParentComponentOrVariableName.ToString());
		NodeObject->SetStringField(TEXT("ParentComponentOwnerClassName"), SCSNode->ParentComponentOwnerClassName.ToString());
		NodeObject->SetStringField(TEXT("AttachToName"), SCSNode->AttachToName.ToString());
		NodeObject->SetBoolField(TEXT("ParentComponentNative"), SCSNode->bIsParentComponentNative);
		TArray<TSharedPtr<FJsonValue>> ChildNodes;
		for (USCS_Node* ChildNode : SCSNode->ChildNodes) {
			ENSURE_NODE_HAS_INDEX(ChildNode);
			const uint32 ChildNodeIndex = SCSNodeToIndex.FindChecked(ChildNode);
			ChildNodes.Add(MakeShareable(new FJsonValueNumber(ChildNodeIndex)));
		}
		NodeObject->SetArrayField(TEXT("ChildNodes"), ChildNodes);
		FieldsGeneratedBySCS.Add(SCSNode->GetVariableName().ToString());
		AllSCSNodes.Add(MakeShareable(new FJsonValueObject(NodeObject)));
	}
	ConstructionScript->SetArrayField(TEXT("AllNodes"), AllSCSNodes);
	TArray<TSharedPtr<FJsonValue>> RootSCSNodes;
	for (USCS_Node* RootSCSNode : SCS->GetRootNodes()) {
		uint32 RootNodeIndex = SCSNodeToIndex.FindChecked(RootSCSNode);
		RootSCSNodes.Add(MakeShareable(new FJsonValueNumber(RootNodeIndex)));
	}
	ConstructionScript->SetArrayField(TEXT("RootNodes"), RootSCSNodes);
	return ConstructionScript;
}

TArray<TSharedPtr<FJsonValue>> WriteDelegateBindings(UBlueprintGeneratedClass* GeneratedClass) {
	TArray<TSharedPtr<FJsonValue>> BlueprintDelegateBindings;
	for (const UDynamicBlueprintBinding* Binding : GeneratedClass->DynamicBindingObjects) {
		SML::Logging::info(TEXT("Serializing delegate binding "), *Binding->GetClass()->GetName());
		if (Binding->GetClass()->GetName() == TEXT("ComponentDelegateBinding")) {
			const UComponentDelegateBinding* ComponentBinding = static_cast<const UComponentDelegateBinding*>(Binding);
			TSharedRef<FJsonObject> BindingObject = MakeShareable(new FJsonObject());
			BindingObject->SetStringField(TEXT("Type"), TEXT("Component"));
			TArray<TSharedPtr<FJsonValue>> BindingValues;
			for (const FBlueprintComponentDelegateBinding& DelegateBinding : ComponentBinding->ComponentDelegateBindings) {
				TSharedRef<FJsonObject> Object = MakeShareable(new FJsonObject());
				Object->SetStringField(TEXT("ComponentName"), DelegateBinding.ComponentPropertyName.ToString());
				Object->SetStringField(TEXT("DelegatePropertyName"), DelegateBinding.DelegatePropertyName.ToString());
				Object->SetStringField(TEXT("FunctionName"), DelegateBinding.FunctionNameToBind.ToString());
				BindingValues.Add(MakeShareable(new FJsonValueObject(Object)));
			}
			BindingObject->SetArrayField(TEXT("Bindings"), BindingValues);
			BlueprintDelegateBindings.Add(MakeShareable(new FJsonValueObject(BindingObject)));
		}
		if (Binding->GetClass()->GetName() == TEXT("WidgetAnimationDelegateBinding")) {
			const UWidgetAnimationDelegateBinding* WidgetBinding = static_cast<const UWidgetAnimationDelegateBinding*>(Binding);
			TSharedRef<FJsonObject> BindingObject = MakeShareable(new FJsonObject());
			BindingObject->SetStringField(TEXT("Type"), TEXT("WidgetAnimation"));
			TArray<TSharedPtr<FJsonValue>> BindingValues;
			for (const FBlueprintWidgetAnimationDelegateBinding& DelegateBinding : WidgetBinding->WidgetAnimationDelegateBindings) {
				TSharedRef<FJsonObject> Object = MakeShareable(new FJsonObject());
				Object->SetNumberField(TEXT("Action"), static_cast<uint8>(DelegateBinding.Action));
				Object->SetStringField(TEXT("AnimationToBind"), DelegateBinding.AnimationToBind.ToString());
				Object->SetStringField(TEXT("FunctionNameToBind"), DelegateBinding.FunctionNameToBind.ToString());
				Object->SetStringField(TEXT("UserTag"), DelegateBinding.UserTag.ToString());
				BindingValues.Add(MakeShareable(new FJsonValueObject(Object)));
			}
			BindingObject->SetArrayField(TEXT("Bindings"), BindingValues);
			BlueprintDelegateBindings.Add(MakeShareable(new FJsonValueObject(BindingObject)));
		}
	}
	return BlueprintDelegateBindings;
}

FString PropertyPathToString(const FCachedPropertyPath& Path) {
	FString OutString;
	UProperty* Property = FCachedPropertyPath::StaticStruct()->FindPropertyByName(TEXT("Segments"));
	check(Property != nullptr);
	const TArray<FPropertyPathSegment>* Segments = Property->ContainerPtrToValuePtr<const TArray<FPropertyPathSegment>>(&Path);
	
	for (int32 SegmentIndex = 0; SegmentIndex < Segments->Num(); ++SegmentIndex) {
		const FPropertyPathSegment& Segment = (*Segments)[SegmentIndex];

		// Add property name
		OutString += Segment.Name.ToString();

		// Add array index
		if (Segment.ArrayIndex != INDEX_NONE) {
			OutString += FString::Printf(TEXT("[%d]"), Segment.ArrayIndex);
		}

		// Add separator
		if (SegmentIndex < Segments->Num() - 1) {
			OutString += TEXT(".");
		}
	}

	return OutString;
}

void DumpAnimInfo(TSharedRef<FJsonObject>& ResultJson, UAnimBlueprintGeneratedClass* AnimClass) {
	ResultJson->SetStringField(TEXT("BlueprintKind"), TEXT("Animation"));
	FSerializationContext SerializationContext;
	ResultJson->SetField(TEXT("TargetSkeleton"), SerializeUObject(AnimClass->TargetSkeleton, SerializationContext));
	//TODO proper animation serialization? Can we reverse it? do we really need it?
}

void DumpWidgetInfo(TSharedRef<FJsonObject>& ResultJson, UWidgetBlueprintGeneratedClass* WidgetClass, TArray<FString>& FieldsGeneratedByWidget) {
	ResultJson->SetStringField(TEXT("BlueprintKind"), TEXT("Widget"));
	FSerializationContext SerializationContext;
	UWidget* RootWidget = WidgetClass->WidgetTree->RootWidget;
	ResultJson->SetField(TEXT("WidgetTreeRootWidget"), SerializeUObject(RootWidget, SerializationContext));

	//Blacklist widget names from dumped field list
	WidgetClass->WidgetTree->ForEachWidget([&FieldsGeneratedByWidget](UWidget* Widget) {
		FieldsGeneratedByWidget.Add(Widget->GetFName().ToString());
	});

	TArray<TSharedPtr<FJsonValue>> NamedSlots;
	for (FName& NamedSlot : WidgetClass->NamedSlots) {
		NamedSlots.Add(MakeShareable(new FJsonValueString(NamedSlot.ToString())));
	}
	ResultJson->SetArrayField(TEXT("NamedSlots"), NamedSlots);
}

void IterateArray(const TArray<TSharedPtr<FJsonValue>>& code, TFunctionRef<void(const TSharedPtr<FJsonObject>&)> func);
void IterateObject(const TSharedPtr<FJsonObject>& obj, TFunctionRef<void(const TSharedPtr<FJsonObject>&)> func);

void DoValue(const TSharedPtr<FJsonValue>& value, TFunctionRef<void(const TSharedPtr<FJsonObject>&)> func) {
	const TArray<TSharedPtr<FJsonValue>>* arr;
	const TSharedPtr<FJsonObject>* obj;
	if (value->TryGetArray(arr)) {
		IterateArray(*arr, func);
	} else if (value->TryGetObject(obj)) {
		if ((*obj)->HasField("Instruction")) {
			func(*obj);
		}
		IterateObject(*obj, func);
	}
}

void IterateObject(const TSharedPtr<FJsonObject>& obj, TFunctionRef<void(const TSharedPtr<FJsonObject>&)> func) {
	for (const TPair<FString, TSharedPtr<FJsonValue>> field : obj->Values) {
		DoValue(field.Value, func);
	}
}

void IterateArray(const TArray<TSharedPtr<FJsonValue>>& code, TFunctionRef<void(const TSharedPtr<FJsonObject>&)> func) {
	for (const TSharedPtr<FJsonValue>& val : code) {
		DoValue(val, func);
	}
}

TSharedRef<FJsonObject> dumpBlueprintContent(UBlueprintGeneratedClass* GeneratedClass) {
	TSharedRef<FJsonObject> ResultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping blueprint class "), *GeneratedClass->GetFullName());

	ResultJson->SetStringField(TEXT("Blueprint"), GeneratedClass->GetPathName());
	ResultJson->SetStringField(TEXT("ParentClass"), GeneratedClass->GetSuperClass()->GetPathName());
	ResultJson->SetStringField(TEXT("BlueprintKind"), TEXT("Normal"));

	TArray<TSharedPtr<FJsonValue>> ImplementedInterfaces;
	for (const FImplementedInterface& iface : GeneratedClass->Interfaces) {
		UClass* interfaceClass = iface.Class;
		TSharedRef<FJsonValueString> string = MakeShareable(new FJsonValueString(interfaceClass->GetPathName()));
		ImplementedInterfaces.Add(string);
	}
	if (ImplementedInterfaces.Num() > 0) {
		ResultJson->SetArrayField(TEXT("ImplementedInterfaces"), ImplementedInterfaces);
	}

	TArray<FString> FieldsGeneratedBySCS;
	if (GeneratedClass->SimpleConstructionScript != nullptr) {
		ResultJson->SetObjectField(TEXT("ConstructionScript"), WriteConstructionScript(GeneratedClass->SimpleConstructionScript, FieldsGeneratedBySCS));
	}

	TArray<FString> FieldsGeneratedByTimelines;
	for (UTimelineTemplate* Timeline : GeneratedClass->Timelines) {
		FieldsGeneratedByTimelines.Add(Timeline->GetVariableName().ToString());
	}

	TArray<FString> FieldsGeneratedByWidget;
	if (UWidgetBlueprintGeneratedClass* WidgetClass = Cast<UWidgetBlueprintGeneratedClass>(GeneratedClass)) {
		DumpWidgetInfo(ResultJson, WidgetClass, FieldsGeneratedByWidget);
	}
	if (UAnimBlueprintGeneratedClass* AnimClass = Cast<UAnimBlueprintGeneratedClass>(GeneratedClass)) {
		DumpAnimInfo(ResultJson, AnimClass);
	}

	FSerializationContext Context;
	TArray<TSharedPtr<FJsonValue>> Fields;
	UObject* DefaultObject = GeneratedClass->GetDefaultObject();
	Context.SerializationStack.Add(DefaultObject, FSerializationObjectInfo{ 0 });
	for (TFieldIterator<UProperty> It(GeneratedClass, DEFAULT_ITERATOR_FLAGS); It; ++It) {
		UProperty* Property = *It;
		const FString PropertyName = Property->GetFName().ToString();
		if (PropertyName == TEXT("UberGraphFrame"))
			continue; //Skip graph frame pointer (cannot be meaningfully serialized)
		if (FieldsGeneratedBySCS.Contains(PropertyName))
			continue; //Skip fields generated by Simple Construction Script
		if (FieldsGeneratedByTimelines.Contains(PropertyName))
			continue; //Skip fields generated by Timelines
		if (FieldsGeneratedByWidget.Contains(PropertyName))
			continue; //Skip variables generated by widget compiler
		const TSharedPtr<FJsonObject>& fieldEntry = CreateFieldDescriptor(Property, DefaultObject, DefaultObject, Context);
		if (fieldEntry.IsValid()) {
			Fields.Add(MakeShareable(new FJsonValueObject(fieldEntry)));
		}
	}
	if (Fields.Num() > 0) {
		ResultJson->SetArrayField(TEXT("Fields"), Fields);
	}

	TArray<TSharedPtr<FJsonValue>> Methods;
	TMap<FString, int32> Ubergraphs;
	TMap<FString, TMap<int32, FString>> UbergraphEntries;
	for (TFieldIterator<UFunction> It(GeneratedClass, EFieldIteratorFlags::ExcludeSuper, EFieldIteratorFlags::IncludeDeprecated, EFieldIteratorFlags::ExcludeInterfaces); It; ++It) {
		UFunction* Function = *It;
		if (Function->GetFName().ToString().StartsWith(TEXT("ExecuteUbergraph_"))) {
			TSharedPtr<FJsonObject> MethodEntry = MakeShareable(new FJsonObject());
			TArray<TSharedPtr<FJsonValue>> code = SML::CreateFunctionCode(Function);
			if (code.Num() > 0) code.RemoveAt(0);
			MethodEntry->SetStringField(TEXT("Name"), Function->GetName());
			MethodEntry->SetArrayField(TEXT("Code"), code);
			Ubergraphs.Add(Function->GetFName().ToString(), Methods.Add(MakeShareable(new FJsonValueObject(MethodEntry))));
			continue;
		}
		const TSharedPtr<FJsonObject>& MethodEntry = CreateFunctionSignature(Function);
		UClass* FunctionOverrideSrc = GetOverridenFunctionSource(Function);
		if (FunctionOverrideSrc == nullptr) {
			//for blueprint defined functions, record full signature
			if (!MethodEntry.IsValid()) continue;
		} else {
			//For overriden functions, record only their name
			TSharedPtr<FJsonObject> MethodEntry = MakeShareable(new FJsonObject());
			MethodEntry->SetStringField(TEXT("Name"), Function->GetFName().ToString());
			MethodEntry->SetStringField(TEXT("SuperClass"), FunctionOverrideSrc->GetPathName());
			MethodEntry->SetBoolField(TEXT("IsOverride"), true);
			if (Function->FunctionFlags & FUNC_BlueprintEvent) {
				TArray<TSharedPtr<FJsonValue>> code = SML::CreateFunctionCode(Function);
				MethodEntry->SetArrayField(TEXT("Code"), code);
			}
			Methods.Add(MakeShareable(new FJsonValueObject(MethodEntry)));
			continue;
		}
		TArray<TSharedPtr<FJsonValue>> code = MethodEntry->GetArrayField("Code");
		if (code.Num() == 1 && code[0]->AsObject()->GetStringField("Instruction") == "CallUbergraph") {
			UbergraphEntries.FindOrAdd(code[0]->AsObject()->GetStringField("Ubergraph")).Add(code[0]->AsObject()->GetNumberField("UbergraphOffset"), Function->GetName());
		}
		Methods.Add(MakeShareable(new FJsonValueObject(MethodEntry)));
	}

	// Add Ubergraph entries
	for (TPair<FString, TMap<int32, FString>> ug : UbergraphEntries) {
		TSharedPtr<FJsonObject> ubergraph = Methods[Ubergraphs[ug.Key]]->AsObject();
		IterateObject(ubergraph, [&](const TSharedPtr<FJsonObject>& inst) {
			if (FString* func = ug.Value.Find(inst->GetNumberField("InstOffsetFromTop"))) {
				inst->SetStringField("UbergraphFunctionEntry", *func);
			}
		});
	}

	// Resolve Ubergraph references
	for (TSharedPtr<FJsonValue> method : Methods) {
		TSharedPtr<FJsonObject> obj = method.Get()->AsObject();
		const TArray<TSharedPtr<FJsonValue>>& code = obj->GetArrayField("Code");
		if (code.Num() > 1 || (code.Num() == 1 && code[0]->AsObject()->GetStringField("Instruction") != "CallUbergraph")) {
			IterateObject(code[0]->AsObject(), [&](const TSharedPtr<FJsonObject>& inst) {
				if (inst->GetStringField("Instruction") == "CallUbergraph") {
					inst->SetStringField("UbergraphFunction", UbergraphEntries[inst->GetStringField("Ubergraph")][inst->GetNumberField("UbergraphOffset")]);
				}
			});
		}
	}

	if (Methods.Num() > 0) {
		ResultJson->SetArrayField(TEXT("Functions"), Methods);
	}

	TArray<TSharedPtr<FJsonValue>> BlueprintDelegateBindings = WriteDelegateBindings(GeneratedClass);
	if (BlueprintDelegateBindings.Num() > 0) {
		ResultJson->SetArrayField(TEXT("DynamicBindings"), BlueprintDelegateBindings);
	}
	DumpSingleFile(ResultJson, GeneratedClass->GetPathName(), "Blueprints");
	return ResultJson;
}

TSharedRef<FJsonObject> dumpClassContent(UClass* NativeClass) {
	TSharedRef<FJsonObject> ResultJson = MakeShareable(new FJsonObject());
	SML::Logging::info(TEXT("Dumping class "), *NativeClass->GetFullName());

	ResultJson->SetStringField(TEXT("Class"), NativeClass->GetPathName());
	
	FSerializationContext Context;
	TArray<TSharedPtr<FJsonValue>> Fields;
	UObject* DefaultObject = NativeClass->GetDefaultObject();
	Context.SerializationStack.Add(DefaultObject, FSerializationObjectInfo{ 0 });
	for (TFieldIterator<UProperty> It(NativeClass, DEFAULT_ITERATOR_FLAGS); It; ++It) {
		UProperty* Property = *It;
		const TSharedPtr<FJsonObject>& fieldEntry = CreateFieldDescriptor(Property, DefaultObject, DefaultObject, Context);
		if (fieldEntry.IsValid()) {
			Fields.Add(MakeShareable(new FJsonValueObject(fieldEntry)));
		}
	}
	if (Fields.Num() > 0) {
		ResultJson->SetArrayField(TEXT("Fields"), Fields);
	}
	DumpSingleFile(ResultJson, NativeClass->GetPathName(), "Class");
	return ResultJson;
}

bool DumpSingleFile(TSharedRef<FJsonObject> ResultJson, FString Path, FString Folder)
{
	FString right;
	FString left;
	Path.Split("/", &left, &right, ESearchCase::Type::IgnoreCase, ESearchDir::Type::FromEnd);
	if (right != "")
	{
		const FString& resultPath = SML::GetConfigDirectory() / "BPdump" / Folder / *left / "/" / right.Append(".json");
		FString resultString;
		TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
		FJsonSerializer Serializer;
		Serializer.Serialize(ResultJson, writer);
		return FFileHelper::SaveStringToFile(resultString, *resultPath, FFileHelper::EEncodingOptions::ForceUTF8);
	}
	return false;
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
	TArray<TSharedPtr<FJsonValue>> classes;

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

	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* Class = *ClassIt;

		// Only interested in native C++ classes
		if (!Class->IsNative())
		{
			continue;
		}

		if (Class->GetPathName().StartsWith(TEXT("/Script/FactoryGame."))) {
			const TSharedRef<FJsonObject>& classJson = dumpClassContent(Class);
			classes.Add(MakeShareable(new FJsonValueObject(classJson)));
		}
	}

	TSharedRef<FJsonObject> resultObject = MakeShareable(new FJsonObject());
	resultObject->SetArrayField(TEXT("UserDefinedEnums"), userDefinedEnums);
	resultObject->SetArrayField(TEXT("UserDefinedStructs"), userDefinedStructs);
	resultObject->SetArrayField(TEXT("Blueprints"), blueprints);
	resultObject->SetArrayField(TEXT("Classes"), classes);

	const FString& resultPath = SML::GetConfigDirectory() / *fileName;
	FString resultString;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&resultString);
	FJsonSerializer Serializer;
	Serializer.Serialize(resultObject, writer);
	FFileHelper::SaveStringToFile(resultString, *resultPath, FFileHelper::EEncodingOptions::ForceUTF8);
	SML::Logging::info(TEXT("Dumping finished!"));
}

void SML::dumpSatisfactoryAssets(const FName& rootPath, const FString& fileName) {
	dumpSatisfactoryAssetsInternal(rootPath, fileName);
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

TSharedPtr<FJsonValue> SerializePropertyValueInternal(const UProperty* TestProperty, const void* Value, FSerializationContext& Context) {
	if (TestProperty->IsA<UMulticastDelegateProperty>()) {
		//Delegates should not be serialized directly
		return MakeShareable(new FJsonValueNumber(0));

	} else if (TestProperty->IsA<UDelegateProperty>()) {
		//Delegates should not be serialized directly
		return MakeShareable(new FJsonValueNumber(0));
		
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