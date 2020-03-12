#include "FGAssetGenerator.h"
#if WITH_EDITOR
#include "FileHelper.h"
#include "AssetRegistryModule.h"
#include "EnumEditorUtils.h"
#include "Engine/UserDefinedEnum.h"
#include "StructureEditorUtils.h"
#include "Engine/UserDefinedStruct.h"
#include "EdGraphSchema_K2.h"
#include "UserDefinedStructure/UserDefinedStructEditorData.h"
#include "Factories/BlueprintFactory.h"
#include "BlueprintEditorUtils.h"
#include "util/TopologicalSort.h"
#include "Json.h"
#include "FileHelpers.h"
#include "BlueprintCompilationManager.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "K2Node_CallFunction.h"
#include "util/Logging.h"

struct FPackageObjectData {
	FString ObjectPath;
	TSharedPtr<FJsonObject> SourceObject;
	bool bIsUserStruct;
	bool bIsBlueprint;
};

struct FStructInitData {
	TMap<FGuid, FString> DelayedVariableDefaultValues;
};

struct FBlueprintInitData {
	TMap<FString, FString> DelayedPropertyInitializationData;
};

struct FObjectInfo {
	UObject* LoadedObject;
	UPackage* ObjectPackage;
	TSharedPtr<FStructInitData> StructInitData;
	TSharedPtr<FBlueprintInitData> BlueprintInitData;
};

FPackageObjectData OBJECT_DATA_Empty;

void ParseObjectPath(const FString& ObjectPath, FString& PackageName, FString& ObjectName);
FEdGraphPinType CreateGraphPinType(const TSharedRef<FJsonObject>& PinJson);
void GatherPinTypeDependencies(const TSharedRef<FJsonObject>& PinJson, TArray<FString>& Dependencies);
bool IsObjectAlreadyLoaded(const FString& ObjectPath);
void AddDependencyIfNeeded(const FString& ObjectPath, TArray<FString>& Dependencies);

FPackageObjectData CreateStructHeader(const TSharedRef<FJsonObject>& StructJson, TArray<FString>& Dependencies);
FPackageObjectData CreateBlueprintHeader(const TSharedRef<FJsonObject>& StructJson, TArray<FString>& Dependencies);

UPackage* CreateEnumerationFromJson(const TSharedRef<FJsonObject>& EnumJson);
FObjectInfo CreateGenericObject(const FPackageObjectData& PackageObjectData, bool bHasDependents);
FObjectInfo CreateStructFromJson(const TSharedRef<FJsonObject>& StructJson, bool bHasDependents);
FObjectInfo CreateBlueprintFromJson(const TSharedRef<FJsonObject>& BlueprintJson, bool bHasDependents);

void PostInitializeObject(const FObjectInfo& ObjectInfo);

inline uint64 GetObjectIndex(const FString& Object, uint64& LastIndex, TMap<FString, uint64>& ObjectPathToIndex) {
	if (!ObjectPathToIndex.Contains(Object)) {
		const uint64 ObjectIndex = LastIndex++;
		ObjectPathToIndex.Add(Object, ObjectIndex);
		return ObjectIndex;
	}
	return ObjectPathToIndex[Object];
}

inline uint64 AddPackageDependencies(const FString& ObjectPath, const TArray<FString>& Dependencies, SML::TopologicalSort::DirectedGraph<uint64>& DependencyGraph, uint64& LastObjectIndex, TMap<FString, uint64>& ObjectPathToIndex, TMap<uint64, bool>& HasDependentsMap) {
	const uint64 ObjectIndex = GetObjectIndex(ObjectPath, LastObjectIndex, ObjectPathToIndex);
	DependencyGraph.addNode(ObjectIndex);
	for (const FString& DependencyObjectPath : Dependencies) {
		uint64 DependencyIndex = GetObjectIndex(DependencyObjectPath, LastObjectIndex, ObjectPathToIndex);
		DependencyGraph.addNode(DependencyIndex);
		DependencyGraph.addEdge(ObjectIndex, DependencyIndex);
		HasDependentsMap.Add(DependencyIndex, true);
	}
	return ObjectIndex;
}

void SML::generateSatisfactoryAssets(const FString& DataJsonFilePath) {
	FString LoadedJsonFileText;
	SML::Logging::info(TEXT("Generating assets from dump "), *DataJsonFilePath);
	const bool result = FFileHelper::LoadFileToString(LoadedJsonFileText, *DataJsonFilePath);
	if (!result) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load FG Blueprints definitions json file"));
		return;
	}
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(LoadedJsonFileText);
	FJsonSerializer Serializer;
	TSharedPtr<FJsonObject> ResultJsonObject;
	if (!Serializer.Deserialize(Reader, ResultJsonObject)) {
		UE_LOG(LogTemp, Error, TEXT("Failed to parse FG Blueprints definitions json file"));
		return;
	}
	SML::Logging::info(TEXT("Generating user defined enumerations..."));
	TArray<UPackage*> DefinedPackages;
	const TArray<TSharedPtr<FJsonValue>>& UserDefinedEnums = ResultJsonObject->GetArrayField(TEXT("UserDefinedEnums"));
	for (const TSharedPtr<FJsonValue>& Value : UserDefinedEnums) {
		UPackage* Package = CreateEnumerationFromJson(Value->AsObject().ToSharedRef());
		if (Package != nullptr) {
			DefinedPackages.Add(Package);
		}
	}
	
	const TArray<TSharedPtr<FJsonValue>>& UserDefinedStructs = ResultJsonObject->GetArrayField(TEXT("UserDefinedStructs"));
	const TArray<TSharedPtr<FJsonValue>>& Blueprints = ResultJsonObject->GetArrayField(TEXT("Blueprints"));

	SML::TopologicalSort::DirectedGraph<uint64> DependencyGraph;
	TMap<uint64, FPackageObjectData> ObjectHeaders;
	TMap<FString, uint64> ObjectPathToIndex;
	TMap<uint64, bool> HasDependentsMap;
	uint64 LastObjectIndex = 0;

	SML::Logging::info(TEXT("Building structure dependency graph..."));
	//Gather UserStruct and Blueprint dependencies now
	for (const TSharedPtr<FJsonValue>& Value : UserDefinedStructs) {
		TArray<FString> Dependencies;
		const FPackageObjectData& ObjectData = CreateStructHeader(Value->AsObject().ToSharedRef(), Dependencies);
		if (!ObjectData.ObjectPath.IsEmpty()) {
			uint64 ObjectIndex = AddPackageDependencies(ObjectData.ObjectPath, Dependencies, DependencyGraph, LastObjectIndex, ObjectPathToIndex, HasDependentsMap);
			ObjectHeaders.Add(ObjectIndex, ObjectData);
		}
	}
	SML::Logging::info(TEXT("Building blueprint dependency graph..."));
	for (const TSharedPtr<FJsonValue>& Value : Blueprints) {
		TArray<FString> Dependencies;
		const FPackageObjectData& ObjectData = CreateBlueprintHeader(Value->AsObject().ToSharedRef(), Dependencies);
		if (!ObjectData.ObjectPath.IsEmpty()) {
			uint64 ObjectIndex = AddPackageDependencies(ObjectData.ObjectPath, Dependencies, DependencyGraph, LastObjectIndex, ObjectPathToIndex, HasDependentsMap);
			ObjectHeaders.Add(ObjectIndex, ObjectData);
		}
	}

	//Apply topological sort now
	try {
		const auto& SortingResult = SML::TopologicalSort::topologicalSort(DependencyGraph);
		TMap<uint64, FObjectInfo> ObjectInfoMap;
		SML::Logging::info(TEXT("Loading assets..."));
		//Load assets in sorted order now
		for (uint64 ObjectIndex : SortingResult) {
			const FPackageObjectData& ObjectData = ObjectHeaders[ObjectIndex];
			check(!ObjectData.ObjectPath.IsEmpty());
			bool bHasDependents = HasDependentsMap.Contains(ObjectIndex);
			const FObjectInfo& CreatedObject = CreateGenericObject(ObjectData, bHasDependents);
			check(CreatedObject.LoadedObject != nullptr);
			ObjectInfoMap.Add(ObjectIndex, CreatedObject);
		}
		//Compile queued blueprints without dependents now
		FBlueprintCompilationManager::FlushCompilationQueueAndReinstance();

		SML::Logging::info(TEXT("Post-initializing loaded assets.."));
		//Now, post initialize delayed default properties
		for (uint64 ObjectIndex : SortingResult) {
			const FObjectInfo& ObjectInfo = ObjectInfoMap[ObjectIndex];
			PostInitializeObject(ObjectInfo);
			DefinedPackages.Add(ObjectInfo.ObjectPackage);
		}
		
	} catch (const SML::TopologicalSort::cycle_detected<uint64>& ex) {
		const FString& CyclePath = ObjectHeaders[ex.cycleNode].ObjectPath;
		UE_LOG(LogTemp, Fatal, TEXT("Cycle detected in FG asset dependency graph at asset: "), *CyclePath);
	}

	SML::Logging::info(TEXT("Saving Packages..."));
	//Now, prompt user to save all packages we defined
	UEditorLoadingAndSavingUtils::SavePackages(DefinedPackages, false);
	SML::Logging::info(TEXT("Success!"));
}

FPackageObjectData CreateBlueprintHeader(const TSharedRef<FJsonObject>& StructJson, TArray<FString>& Dependencies) {
	const FString& ObjectPath = StructJson->GetStringField(TEXT("Blueprint"));
	if (IsObjectAlreadyLoaded(ObjectPath)) {
		return OBJECT_DATA_Empty;
	}
	//add parent class
	const FString& ParentClass = StructJson->GetStringField(TEXT("ParentClass"));
	AddDependencyIfNeeded(ParentClass, Dependencies);
	
	//add implemented interfaces as dependencies
	if (StructJson->HasField(TEXT("ImplementedInterfaces"))) {
		const TArray<TSharedPtr<FJsonValue>>& ImplementedInterfaces = StructJson->GetArrayField(TEXT("ImplementedInterfaces"));
		for (const TSharedPtr<FJsonValue>& Value : ImplementedInterfaces) {
			const FString& InterfacePath = Value.Get()->AsString();
			AddDependencyIfNeeded(InterfacePath, Dependencies);
		}
	}
	
	//also iterate fields to add their types
	if (StructJson->HasField(TEXT("Fields"))) {
		const TArray<TSharedPtr<FJsonValue>>& Fields = StructJson->GetArrayField(TEXT("Fields"));
		for (const TSharedPtr<FJsonValue>& Value : Fields) {
			const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
			TSharedPtr<FJsonObject> PinData = ValueObject->GetObjectField(TEXT("PinType"));
			GatherPinTypeDependencies(PinData.ToSharedRef(), Dependencies);
		}
	}
	//check function return types and arguments
	if (StructJson->HasField(TEXT("Functions"))) {
		const TArray<TSharedPtr<FJsonValue>>& Functions = StructJson->GetArrayField(TEXT("Functions"));
		for (const TSharedPtr<FJsonValue>& Value : Functions) {
			const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
			if (ValueObject->HasField(TEXT("ReturnType"))) {
				const TSharedPtr<FJsonObject>& PinType = ValueObject->GetObjectField(TEXT("ReturnType"))->GetObjectField(TEXT("PinType"));
				GatherPinTypeDependencies(PinType.ToSharedRef(), Dependencies);
			}
			if (ValueObject->HasField(TEXT("Arguments"))) {
				const TArray<TSharedPtr<FJsonValue>>& Arguments = ValueObject->GetArrayField(TEXT("Arguments"));
				for (const TSharedPtr<FJsonValue> ArgumentValue : Arguments) {
					const TSharedPtr<FJsonObject>& PinType = ArgumentValue->AsObject()->GetObjectField(TEXT("PinType"));
					GatherPinTypeDependencies(PinType.ToSharedRef(), Dependencies);
				}
			}
		}
	}
	return FPackageObjectData{ ObjectPath, StructJson, false, true };
}

void PostInitializeObject(const FObjectInfo& ObjectInfo) {
	UUserDefinedStruct* UserDefinedStruct = Cast<UUserDefinedStruct>(ObjectInfo.LoadedObject);
	if (UserDefinedStruct) {
		//re-initialize all properties to their new defaults, then request recompile
		bool bSetDefaultValues = false;
		for (const auto& StructVarEntry : ObjectInfo.StructInitData->DelayedVariableDefaultValues) {
			const FGuid& VariableGuid = StructVarEntry.Key;
			const FString& VariableDefaultValue = StructVarEntry.Value;
			FStructVariableDescription* VariableDesc = FStructureEditorUtils::GetVarDescByGuid(UserDefinedStruct, VariableGuid);
			VariableDesc->DefaultValue = VariableDefaultValue;
			bSetDefaultValues = true;
		}
		//request structure recompile when we actually set some default values
		if (bSetDefaultValues) {
			//will also mark package dirty, so we don't have to do it ourselves
			FStructureEditorUtils::OnStructureChanged(UserDefinedStruct, FStructureEditorUtils::EStructureEditorChangeInfo::DefaultValueChanged);
		}
	}
	UBlueprint* Blueprint = Cast<UBlueprint>(ObjectInfo.LoadedObject);
	if (Blueprint) {
		//Blueprint should have been already compiled at that moment
		check(Blueprint->GeneratedClass != nullptr);
		UClass* BlueprintGeneratedClass = Blueprint->GeneratedClass;
		UObject* ClassDefaultObject = BlueprintGeneratedClass->GetDefaultObject();
		for (const auto& BPPropertyEntry : ObjectInfo.BlueprintInitData->DelayedPropertyInitializationData) {
			UProperty* ResultProperty = BlueprintGeneratedClass->FindPropertyByName(*BPPropertyEntry.Key);
			check(ResultProperty != nullptr);
			const FString& DefaultValue = BPPropertyEntry.Value;
			void* PropertyData = ResultProperty->ContainerPtrToValuePtr<void>(ClassDefaultObject);
			ResultProperty->ImportText(*DefaultValue, PropertyData, 0, ClassDefaultObject);
		}
		//Mark default class object package as dirty now
		ClassDefaultObject->MarkPackageDirty();
	}	
}


FPackageObjectData CreateStructHeader(const TSharedRef<FJsonObject>& StructJson, TArray<FString>& Dependencies) {
	const FString& ObjectPath = StructJson->GetStringField(TEXT("StructName"));
	if (IsObjectAlreadyLoaded(ObjectPath)) {
		return OBJECT_DATA_Empty;
	}
	const TArray<TSharedPtr<FJsonValue>>& Fields = StructJson->GetArrayField(TEXT("Fields"));
	for (const TSharedPtr<FJsonValue>& Value : Fields) {
		const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
		TSharedPtr<FJsonObject> PinData = ValueObject->GetObjectField(TEXT("PinType"));
		GatherPinTypeDependencies(PinData.ToSharedRef(), Dependencies);
	}
	return FPackageObjectData{ ObjectPath, StructJson, true, false };
}

UUserDefinedStruct* CreateUserDefinedStructWithGUID(UObject* InParent, const FName& Name, EObjectFlags Flags, const FGuid& PredefinedGuid) {
	UUserDefinedStruct* Struct = NewObject<UUserDefinedStruct>(InParent, Name, Flags);
	check(Struct);
	Struct->EditorData = NewObject<UUserDefinedStructEditorData>(Struct, NAME_None, RF_Transactional);
	check(Struct->EditorData);

	Struct->Guid = PredefinedGuid;
	Struct->SetMetaData(TEXT("BlueprintType"), TEXT("true"));
	Struct->Bind();
	Struct->StaticLink(true);
	Struct->Status = UDSS_Error;
	FStructureEditorUtils::AddVariable(Struct, FEdGraphPinType(UEdGraphSchema_K2::PC_Boolean, NAME_None, nullptr, EPinContainerType::None, false, FEdGraphTerminalType()));
	return Struct;
}

FGuid AddStructVariableWithName(UUserDefinedStruct* Struct, const FEdGraphPinType& VarType, const FString& PredefinedUniqueName) {
	FStructureEditorUtils::ModifyStructData(Struct);

	FString ErrorMessage;
	check(FStructureEditorUtils::CanHaveAMemberVariableOfType(Struct, VarType, &ErrorMessage));
	const FGuid Guid = FGuid::NewGuid();
	int32 FirstUnderscoreIndex;
	PredefinedUniqueName.FindChar('_', FirstUnderscoreIndex);
	check(FirstUnderscoreIndex != INDEX_NONE);
	const FString DisplayName = PredefinedUniqueName.Mid(0, FirstUnderscoreIndex);
	const FName VarName = FName(*PredefinedUniqueName);

	FStructVariableDescription NewVar;
	NewVar.VarName = VarName;
	NewVar.FriendlyName = DisplayName;
	NewVar.SetPinType(VarType);
	NewVar.VarGuid = Guid;
	NewVar.bDontEditoOnInstance = false;
	NewVar.bInvalidMember = false;
	FStructureEditorUtils::GetVarDesc(Struct).Add(NewVar);
	//Do not fire struct change event now, fire it only after all fields have been added
	return Guid;
}

FObjectInfo CreateGenericObject(const FPackageObjectData& PackageObjectData, bool bHasDependents) {
	if (PackageObjectData.bIsUserStruct) {
		return CreateStructFromJson(PackageObjectData.SourceObject.ToSharedRef(), bHasDependents);
	}
	if (PackageObjectData.bIsBlueprint) {
		return CreateBlueprintFromJson(PackageObjectData.SourceObject.ToSharedRef(), bHasDependents);
	}
	return FObjectInfo{ nullptr };
}

void DefineCustomFunctionFromJson(UEdGraph& Graph, UK2Node_FunctionEntry* EntryNode, const TSharedPtr<FJsonObject> FunctionObject) {
	const UEdGraphSchema_K2* Schema = Cast<UEdGraphSchema_K2>(Graph.GetSchema());

	//Add parameters specified in the json for the function entry
	if (FunctionObject->HasField(TEXT("Arguments"))) {
		const TArray<TSharedPtr<FJsonValue>>& Arguments = FunctionObject->GetArrayField(TEXT("Arguments"));
		for (const TSharedPtr<FJsonValue> Value : Arguments) {
			//initialize properties for argument
			const TSharedPtr<FJsonObject>& ArgumentObject = Value->AsObject();
			const FString& ParameterName = ArgumentObject->GetStringField(TEXT("Name"));
			const FEdGraphPinType& GraphPinType = CreateGraphPinType(ArgumentObject->GetObjectField(TEXT("PinType")).ToSharedRef());
	
			//Create argument pin from given information
			UEdGraphPin* Pin = EntryNode->CreatePin(EGPD_Output, NAME_None, *ParameterName);
			Pin->PinType = GraphPinType;
			Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);
		}
	}
	
	//generate function result node if we have return type defined for our function
	if (FunctionObject->HasField(TEXT("ReturnType"))) {
		const TSharedPtr<FJsonObject>& ReturnType = FunctionObject->GetObjectField(TEXT("ReturnType"));
		const FString& ReturnPinName = ReturnType->GetStringField(TEXT("Name"));
		const FEdGraphPinType& GraphPinType = CreateGraphPinType(ReturnType->GetObjectField(TEXT("PinType")).ToSharedRef());

		//Initialize node with default pins and location
		FGraphNodeCreator<UK2Node_FunctionResult> NodeCreator(Graph);
		UK2Node_FunctionResult* ReturnNode = NodeCreator.CreateNode();
		ReturnNode->NodePosX = EntryNode->NodePosX + EntryNode->NodeWidth + 256;
		ReturnNode->NodePosY = EntryNode->NodePosY;
		NodeCreator.Finalize();

		//Create return Value Pin because default one is empty since we don't have UFunction prototype
		UEdGraphPin* Pin = ReturnNode->CreatePin(EGPD_Input, NAME_None, *ReturnPinName);
		Pin->PinType = GraphPinType;
		Schema->SetPinAutogeneratedDefaultValueBasedOnType(Pin);
		Schema->SetNodeMetaData(ReturnNode, FNodeMetadata::DefaultGraphNode);

		// Auto-connect the pins for entry and exit, so that by default the signature is properly generated
		UEdGraphPin* ResultNodeExec = Schema->FindExecutionPin(*ReturnNode, EGPD_Input);
		UEdGraphPin* NextExec = Schema->FindExecutionPin(*EntryNode, EGPD_Output);
		if (ResultNodeExec && NextExec) {
			NextExec->MakeLinkTo(ResultNodeExec);
		}
	}

	//Update function flags to match saved ones
	const uint32 SavedFunctionFlags = FunctionObject->GetIntegerField(TEXT("FunctionFlags"));
	EntryNode->AddExtraFlags(SavedFunctionFlags);
}

FObjectInfo CreateBlueprintFromJson(const TSharedRef<FJsonObject>& BlueprintJson, bool bHasDependents) {
	FString PackageName;
	FString ObjectName;
	const FString& ObjectPath = BlueprintJson->GetStringField(TEXT("Blueprint"));
	ParseObjectPath(ObjectPath, PackageName, ObjectName);
	SML::Logging::info(TEXT("Creating blueprint "), *ObjectPath, TEXT("; Has Dependents? "), bHasDependents);
	UPackage* TargetPackage = CreatePackage(nullptr, *PackageName);
	EObjectFlags Flags = RF_Public | RF_Standalone;
	UBlueprintFactory* BlueprintFactory = NewObject<UBlueprintFactory>();

	const FString& ParentClassPath = BlueprintJson->GetStringField(TEXT("ParentClass"));
	TArray<UClass*> OverrideFunctionSources;
	UClass* ParentClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *ParentClassPath));
	check(ParentClass != nullptr);
	OverrideFunctionSources.Add(ParentClass);
	
	//Generate blueprint object with parent class
	//TODO Do we need to override blueprint type?
	BlueprintFactory->ParentClass = ParentClass;
	UBlueprint* Blueprint = Cast<UBlueprint>(BlueprintFactory->FactoryCreateNew(UBlueprint::StaticClass(), TargetPackage, *ObjectName, Flags, nullptr, GWarn));
	check(Blueprint != nullptr);
	
	//Implement required interfaces for generated blueprint
	if (BlueprintJson->HasField(TEXT("ImplementedInterfaces"))) {
		const TArray<TSharedPtr<FJsonValue>> ImplementedInterfaces = BlueprintJson->GetArrayField(TEXT("ImplementedInterfaces"));
		for (const TSharedPtr<FJsonValue>& Value : ImplementedInterfaces) {
			const FString& InterfaceName = Value.Get()->AsString();
			UClass* InterfaceClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *InterfaceName));
			check(InterfaceClass != nullptr);
			FBlueprintEditorUtils::ImplementNewInterface(Blueprint, *InterfaceName);
			OverrideFunctionSources.Add(InterfaceClass);
		}
	}
	
	//Generate blueprint own properties (only properties with specified pin type)
	TSharedPtr<FBlueprintInitData> BlueprintInitData = MakeShareable(new FBlueprintInitData());
	if (BlueprintJson->HasField(TEXT("Fields"))) {
		const TArray<TSharedPtr<FJsonValue>> Fields = BlueprintJson->GetArrayField(TEXT("Fields"));
		for (const TSharedPtr<FJsonValue>& Value : Fields) {
			const TSharedPtr<FJsonObject>& FieldObject = Value.Get()->AsObject();
			const FString& FieldName = FieldObject->GetStringField(TEXT("Name"));
			if (FieldName == TEXT("UberGraphFrame"))
				continue; //Skip generated uber graph frame field
			if (FieldObject->HasField(TEXT("PinType"))) {
				//It is blueprint's own variable, generate it
				FEdGraphPinType PinType = CreateGraphPinType(FieldObject->GetObjectField(TEXT("PinType")).ToSharedRef());
				FBlueprintEditorUtils::AddMemberVariable(Blueprint, *FieldName, PinType);
			}
			if (FieldObject->HasField(TEXT("Value"))) {
				const FString& VariableValue = FieldObject->GetStringField(TEXT("Value"));
				BlueprintInitData->DelayedPropertyInitializationData.Add(FieldName, VariableValue);
			}
		}
	}

	//Generate dummy method overrides & own methods now
	//TODO can we decompile Kismet VM byte code to have at least pseudo code of blueprints?
	if (BlueprintJson->HasField(TEXT("Functions"))) {
		const TArray<TSharedPtr<FJsonValue>> Functions = BlueprintJson->GetArrayField(TEXT("Functions"));
		for (const TSharedPtr<FJsonValue>& Value : Functions) {
			const TSharedPtr<FJsonObject>& MethodObject = Value.Get()->AsObject();
			const FString& MethodName = MethodObject->GetStringField(TEXT("Name"));
			if (MethodName.StartsWith(TEXT("ExecuteUbergraph_")))
				continue; //Skip generated uber graph entry point function
			UEdGraph* FunctionGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, *MethodName, UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());
			UClass* ParentFunctionClass = nullptr;
			bool bIsUserCreated = true;
			if (MethodObject->HasField(TEXT("SuperClass"))) {
				//if this is override function, set super class for it
				const FString& SuperObjectPath = MethodObject->GetStringField(TEXT("SuperClass"));
				ParentFunctionClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *SuperObjectPath));
				check(ParentFunctionClass != nullptr);
				bIsUserCreated = false;
			}
			FBlueprintEditorUtils::AddFunctionGraph(Blueprint, FunctionGraph, bIsUserCreated, ParentFunctionClass);
			TArray<UK2Node_FunctionEntry*> EntryNodes;
			FunctionGraph->GetNodesOfClass(EntryNodes);
			UK2Node_FunctionEntry* EntryNode = EntryNodes[0];
			if (bIsUserCreated) {
				DefineCustomFunctionFromJson(*FunctionGraph, EntryNode, MethodObject);
			}
			EntryNode->OnUpdateCommentText(TEXT("Function Stub: Implementation not available."));
		}
	}
	
	//Force Blueprint synchronous blueprint compilation now if somebody depends on us
	if (bHasDependents) {
		FBPCompileRequest CompileRequest{ Blueprint, EBlueprintCompileOptions::None, nullptr };
		FBlueprintCompilationManager::CompileSynchronously(CompileRequest);
	} else {
		//Otherwise, queue blueprint for further compilation with all other blueprints
		FBlueprintCompilationManager::QueueForCompilation(Blueprint);
	}
	//Remove temporary blueprint factory
	BlueprintFactory->MarkPendingKill();
	return FObjectInfo{ Blueprint, TargetPackage, TSharedPtr<FStructInitData>(), BlueprintInitData };
}

FObjectInfo CreateStructFromJson(const TSharedRef<FJsonObject>& StructJson, bool bHasDependents) {
	FString PackageName;
	FString ObjectName;
	const FString& ObjectPath = StructJson->GetStringField(TEXT("StructName"));
	SML::Logging::info(TEXT("Creating user defined struct "), *ObjectPath);
	ParseObjectPath(ObjectPath, PackageName, ObjectName);
	UPackage* TargetPackage = CreatePackage(nullptr, *PackageName);
	EObjectFlags Flags = RF_Public | RF_Standalone;
	FGuid PredefinedGuid = FGuid::NewGuid();
	FGuid::Parse(StructJson->GetStringField(TEXT("Guid")), PredefinedGuid);
	//create structure with predefined FGuid value
	UUserDefinedStruct* StructObject = CreateUserDefinedStructWithGUID(TargetPackage, FName(*ObjectName), Flags, PredefinedGuid);
	check(StructObject != nullptr);

	//create all required struct fields
	const TArray<TSharedPtr<FJsonValue>>& Fields = StructJson->GetArrayField(TEXT("Fields"));
	TSharedRef<FStructInitData> StructInitData = MakeShareable(new FStructInitData());
	for (const TSharedPtr<FJsonValue>& Value : Fields) {
		const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
		const FString& FieldName = ValueObject->GetStringField(TEXT("Name"));
		const FEdGraphPinType& PinType = CreateGraphPinType(ValueObject->GetObjectField(TEXT("PinType")).ToSharedRef());
		const FGuid& VariableGuid = AddStructVariableWithName(StructObject, PinType, FieldName);
		if (ValueObject->HasField(TEXT("Value"))) {
			const FString& TextValue = ValueObject->GetStringField(TEXT("Value"));
			StructInitData->DelayedVariableDefaultValues.Add(VariableGuid, TextValue);
		}
	}
	
	//fire structure change event now, after all variables have been added
	//it will cause structure recompile, and also mark package dirty.
	FStructureEditorUtils::OnStructureChanged(StructObject, FStructureEditorUtils::EStructureEditorChangeInfo::AddedVariable);
	return FObjectInfo{ StructObject, TargetPackage, StructInitData };
}

UPackage* CreateEnumerationFromJson(const TSharedRef<FJsonObject>& EnumJson) {
	const FString& ObjectPath = EnumJson->GetStringField(TEXT("StructName"));
	if (IsObjectAlreadyLoaded(ObjectPath)) {
		return nullptr;
	}
	FString PackageName;
	FString ObjectName;
	ParseObjectPath(ObjectPath, PackageName, ObjectName);
	SML::Logging::info(TEXT("Creating enumeration "), *ObjectPath);
	
	UPackage* TargetPackage = CreatePackage(nullptr, *PackageName);
	EObjectFlags Flags = RF_Public | RF_Standalone;
	UUserDefinedEnum* EnumObject = Cast<UUserDefinedEnum>(FEnumEditorUtils::CreateUserDefinedEnum(TargetPackage, FName(*ObjectName), Flags));
	check(EnumObject != nullptr);
	FAssetRegistryModule::AssetCreated(EnumObject);
	const TArray<TSharedPtr<FJsonValue>>& Values = EnumJson->GetArrayField(TEXT("Values"));
	//first, add required amount of values there (one of values is _MAX entry, do not add it)
	for (int32 i = 0; i < Values.Num() - 1; i++) {
		FEnumEditorUtils::AddNewEnumeratorForUserDefinedEnum(EnumObject);
	}
	//after that, enumerate entries and update their display names
	for (const TSharedPtr<FJsonValue>& Value : Values) {
		const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
		if (!ValueObject->HasField(TEXT("DisplayName"))) {
			continue; //skip entries without display name, including _MAX
		}
		const FString& DisplayName = ValueObject->GetStringField(TEXT("DisplayName"));
		int32 EnumIndex = ValueObject->GetIntegerField(TEXT("Value"));
		FEnumEditorUtils::SetEnumeratorDisplayName(EnumObject, EnumIndex, FText::AsCultureInvariant(DisplayName));
	}
	//mark package as dirty for saving
	TargetPackage->MarkPackageDirty();
	return TargetPackage;
}

void ParseObjectPath(const FString& ObjectPath, FString& PackageName, FString& ObjectName) {
	int32 LastDotIndex;
	ObjectPath.FindLastChar('.', LastDotIndex);
	check(LastDotIndex != INDEX_NONE);
	ObjectName = ObjectPath.Mid(LastDotIndex + 1);
	PackageName = ObjectPath.Mid(0, LastDotIndex);
}

void GatherPinTypeDependencies(const TSharedRef<FJsonObject>& PinJson, TArray<FString>& Dependencies) {
	if (PinJson->HasField(TEXT("PinSubCategoryObject"))) {
		const FString& ObjectPath = PinJson->GetStringField(TEXT("PinSubCategoryObject"));
		AddDependencyIfNeeded(ObjectPath, Dependencies);
	}
	if (PinJson->HasField(TEXT("PinSubCategoryMemberReference"))) {
		const TSharedPtr<FJsonObject>& MemberJson = PinJson->GetObjectField(TEXT("PinSubCategoryMemberReference"));
		if (MemberJson->HasField("MemberParent")) {
			const FString& ObjectPath = MemberJson->GetStringField(TEXT("MemberParent"));
			AddDependencyIfNeeded(ObjectPath, Dependencies);
		}
	}
	if (PinJson->HasField(TEXT("PinValueType"))) {
		const TSharedPtr<FJsonObject> ValueJson = PinJson->GetObjectField(TEXT("PinValueType"));
		if (ValueJson->HasField(TEXT("TerminalSubCategoryObject"))) {
			const FString& ObjectPath = ValueJson->GetStringField(TEXT("TerminalSubCategoryObject"));
			AddDependencyIfNeeded(ObjectPath, Dependencies);
		}
	}
}

FEdGraphPinType CreateGraphPinType(const TSharedRef<FJsonObject>& PinJson) {
	FEdGraphPinType GraphPinType;
	GraphPinType.PinCategory = *PinJson->GetStringField(TEXT("PinCategory"));
	GraphPinType.PinSubCategory = *PinJson->GetStringField(TEXT("PinSubCategory"));
	if (PinJson->HasField(TEXT("PinSubCategoryObject"))) {
		const FString& ObjectPath = PinJson->GetStringField(TEXT("PinSubCategoryObject"));
		UObject* PinSubCategoryObject = LoadObject<UObject>(GetTransientPackage(), *ObjectPath);
		check(PinSubCategoryObject != nullptr);
		GraphPinType.PinSubCategoryObject = PinSubCategoryObject;
	}
	if (PinJson->HasField(TEXT("PinSubCategoryMemberReference"))) {
		FSimpleMemberReference& MemberRef = GraphPinType.PinSubCategoryMemberReference;
		const TSharedPtr<FJsonObject>& MemberJson = PinJson->GetObjectField(TEXT("PinSubCategoryMemberReference"));
		if (MemberJson->HasField("MemberParent")) {
			const FString& ObjectPath = MemberJson->GetStringField(TEXT("MemberParent"));
			UObject* MemberParentObject = LoadObject<UObject>(GetTransientPackage(), *ObjectPath);
			check(MemberParentObject != nullptr);
			MemberRef.MemberParent = MemberParentObject;
		}
		MemberRef.MemberName = *MemberJson->GetStringField(TEXT("MemberName"));
		FGuid::Parse(MemberJson->GetStringField(TEXT("MemberGuid")), MemberRef.MemberGuid);
	}

	if (PinJson->HasField(TEXT("PinValueType"))) {
		FEdGraphTerminalType& ValueType = GraphPinType.PinValueType;
		const TSharedPtr<FJsonObject> ValueJson = PinJson->GetObjectField(TEXT("PinValueType"));
		ValueType.TerminalCategory = *ValueJson->GetStringField(TEXT("TerminalCategory"));
		ValueType.TerminalSubCategory = *ValueJson->GetStringField(TEXT("TerminalSubCategory"));
		if (ValueJson->HasField(TEXT("TerminalSubCategoryObject"))) {
			const FString& ObjectPath = ValueJson->GetStringField(TEXT("TerminalSubCategoryObject"));
			UObject* TerminalSubCategoryObject = LoadObject<UObject>(GetTransientPackage(), *ObjectPath);
			check(TerminalSubCategoryObject != nullptr);
			ValueType.TerminalSubCategoryObject = TerminalSubCategoryObject;
		}
		ValueType.bTerminalIsConst = ValueJson->GetBoolField(TEXT("TerminalIsConst"));
		ValueType.bTerminalIsWeakPointer = ValueJson->GetBoolField(TEXT("TerminalIsWeakPointer"));
	}

	if (PinJson->HasField(TEXT("ContainerType"))) {
		GraphPinType.ContainerType = static_cast<EPinContainerType>(PinJson->GetIntegerField(TEXT("ContainerType")));
	}
	if (PinJson->HasField(TEXT("IsReference"))) {
		GraphPinType.bIsReference = PinJson->GetBoolField(TEXT("IsReference"));
	}
	if (PinJson->HasField(TEXT("IsConst"))) {
		GraphPinType.bIsConst = PinJson->GetBoolField(TEXT("IsConst"));
	}
	if (PinJson->HasField(TEXT("IsWeakPointer"))) {
		GraphPinType.bIsWeakPointer = PinJson->GetBoolField(TEXT("IsWeakPointer"));
	}
	return GraphPinType;
}

bool IsObjectAlreadyLoaded(const FString& ObjectPath) {
	return IsValid(FindObject<UObject>(GetTransientPackage(), *ObjectPath));
}

void AddDependencyIfNeeded(const FString& ObjectPath, TArray<FString>& Dependencies) {
	//add to required dependencies only if we couldn't find it
	if (!IsObjectAlreadyLoaded(ObjectPath)) {
		Dependencies.Add(ObjectPath);
	}
}
#endif
