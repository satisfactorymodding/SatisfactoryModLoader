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
#include "BlueprintEditorUtils.h"
#include "util/TopologicalSort.h"
#include "Json.h"
#include "FileHelpers.h"
#include "BlueprintCompilationManager.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "K2Node_CallFunction.h"
#include "K2Node_Event.h"
#include "util/Logging.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EdGraphSchema_K2_Actions.h"

struct FPackageObjectData {
	FString ObjectPath;
	TSharedPtr<FJsonObject> SourceObject;
	bool bIsUserStruct;
	bool bIsBlueprint;
};

FPackageObjectData OBJECT_DATA_Empty;

void ParseObjectPath(const FString& ObjectPath, FString& PackageName, FString& ObjectName);
FEdGraphPinType CreateGraphPinType(const TSharedRef<FJsonObject>& PinJson);
void GatherPinTypeDependencies(const TSharedRef<FJsonObject>& PinJson, TArray<FString>& Dependencies);
bool IsObjectAlreadyLoaded(const FString& ObjectPath);
void AddDependencyIfNeeded(const FString& ObjectPath, TArray<FString>& Dependencies);

void AddDependenciesForStruct(const FPackageObjectData& ObjectData, TArray<FString>& Dependencies);
void AddDependenciesForBlueprint(const FPackageObjectData& ObjectData, TArray<FString>& Dependencies);

UPackage* CreateEnumerationFromJson(const TSharedRef<FJsonObject>& EnumJson);
UPackage* CreateGenericObject(const FPackageObjectData& PackageObjectData, bool bHasDependents);
UPackage* CreateStructFromJson(const TSharedRef<FJsonObject>& StructJson);
UPackage* CreateBlueprintFromJson(const TSharedRef<FJsonObject>& BlueprintJson, bool bHasDependents);

void InitializeBlueprint(UBlueprint* Blueprint, const TSharedPtr<FJsonObject>& BlueprintJson, bool bHasDepdents);

void PostInitializeObject(UObject* Object, const TSharedPtr<FJsonObject>& JsonObject);

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
		DependencyGraph.addEdge(DependencyIndex, ObjectIndex);
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
	//Save all defined enumerations now
	UEditorLoadingAndSavingUtils::SavePackages(DefinedPackages, true);
	DefinedPackages.Empty();
	
	const TArray<TSharedPtr<FJsonValue>>& UserDefinedStructs = ResultJsonObject->GetArrayField(TEXT("UserDefinedStructs"));
	const TArray<TSharedPtr<FJsonValue>>& Blueprints = ResultJsonObject->GetArrayField(TEXT("Blueprints"));

	SML::TopologicalSort::DirectedGraph<uint64> DependencyGraph;
	TMap<uint64, FPackageObjectData> ObjectHeaders;
	TMap<FString, uint64> ObjectPathToIndex;
	TMap<uint64, bool> HasDependentsMap;
	uint64 LastObjectIndex = 2;

	SML::Logging::info(TEXT("Building structure dependency graph..."));
	//Gather UserStruct and Blueprint dependencies now
	for (const TSharedPtr<FJsonValue>& Value : UserDefinedStructs) {
		TSharedPtr<FJsonObject> StructJson = Value->AsObject();
		const FString& ObjectPath = StructJson->GetStringField(TEXT("StructName"));
		const FPackageObjectData& ObjectData = FPackageObjectData{ ObjectPath, StructJson, true, false };
		if (!ObjectData.ObjectPath.IsEmpty()) {
			TArray<FString> Dependencies;
			AddDependenciesForStruct(ObjectData, Dependencies);
			uint64 ObjectIndex = AddPackageDependencies(ObjectData.ObjectPath, Dependencies, DependencyGraph, LastObjectIndex, ObjectPathToIndex, HasDependentsMap);
			ObjectHeaders.Add(ObjectIndex, ObjectData);
		}
	}
	
	SML::Logging::info(TEXT("Building blueprint dependency graph..."));
	for (const TSharedPtr<FJsonValue>& Value : Blueprints) {
		TSharedPtr<FJsonObject> StructJson = Value->AsObject();
		const FString& ObjectPath = StructJson->GetStringField(TEXT("Blueprint"));
		const FPackageObjectData& ObjectData = FPackageObjectData{ ObjectPath, StructJson, false, true };
		if (!ObjectData.ObjectPath.IsEmpty()) {
			TArray<FString> Dependencies;
			AddDependenciesForBlueprint(ObjectData, Dependencies);
			uint64 ObjectIndex = AddPackageDependencies(ObjectData.ObjectPath, Dependencies, DependencyGraph, LastObjectIndex, ObjectPathToIndex, HasDependentsMap);
			ObjectHeaders.Add(ObjectIndex, ObjectData);
		}
	}

	//Apply topological sort now
	const TArray<uint64> SortingResult = SML::TopologicalSort::topologicalSort(DependencyGraph);
	SML::Logging::info(TEXT("Loading assets..."));
	
	//Load assets in sorted order now
	for (int32 i = 0; i < SortingResult.Num(); i++) {
		uint64 ObjectIndex = SortingResult[i];
		const FPackageObjectData& ObjectData = ObjectHeaders.FindChecked(ObjectIndex);
		check(!ObjectData.ObjectPath.IsEmpty());
		SML::Logging::info(TEXT("Loading object "), *ObjectData.ObjectPath, TEXT(" ("), i, TEXT("/"), SortingResult.Num(), TEXT(")"));
		bool bHasDependents = HasDependentsMap.Contains(ObjectIndex);
		UPackage* Package = CreateGenericObject(ObjectData, bHasDependents);
		if (Package != nullptr) {
			DefinedPackages.Add(Package);
			if (bHasDependents) {
				//Force package save now if it has dependents available
				UEditorLoadingAndSavingUtils::SavePackages(DefinedPackages, true);
				DefinedPackages.Empty();
			}
		}
	}
	
	//Save packages after all assets have been re-created
	UEditorLoadingAndSavingUtils::SavePackages(DefinedPackages, true);
	DefinedPackages.Empty();
	
	//Compile queued blueprints without dependents now
	SML::Logging::info(TEXT("Flushing compilation queue.."));
	FBlueprintCompilationManager::FlushCompilationQueueAndReinstance();

	SML::Logging::info(TEXT("Initializing objects.."));
	
	//Finish blueprint construction once all dependencies have been defined and saved
	for (int32 i = 0; i < SortingResult.Num(); i++) {
		uint64 ObjectIndex = SortingResult[i];
		const FPackageObjectData& ObjectData = ObjectHeaders[ObjectIndex];
		if (ObjectData.bIsBlueprint) {
			const FString& ObjectPath = ObjectData.ObjectPath.LeftChop(2);
			UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *ObjectPath);
			bool bHasDependents = HasDependentsMap.Contains(ObjectIndex);
			check(Blueprint != nullptr);
			InitializeBlueprint(Blueprint, ObjectData.SourceObject, bHasDependents);
		}
	}
	
	//Compile delay initialized blueprints now
	SML::Logging::info(TEXT("Flushing compilation queue.."));
	FBlueprintCompilationManager::FlushCompilationQueueAndReinstance();
	
	SML::Logging::info(TEXT("Post-initializing loaded assets.."));
	
	//Now, post initialize delayed default properties
	for (int32 i = 0; i < SortingResult.Num(); i++) {
		uint64 ObjectIndex = SortingResult[i];
		const FPackageObjectData& ObjectData = ObjectHeaders[ObjectIndex];
		UObject* Object = nullptr;
		if (ObjectData.bIsBlueprint) {
			const FString& ObjectPath = ObjectData.ObjectPath.LeftChop(2);
			Object = LoadObject<UBlueprint>(nullptr, *ObjectPath);
		}
		if (ObjectData.bIsUserStruct) {
			const FString& ObjectPath = ObjectData.ObjectPath;
			Object = LoadObject<UUserDefinedStruct>(nullptr, *ObjectPath);
		}
		if (Object != nullptr) {
			PostInitializeObject(Object, ObjectData.SourceObject);
		} else {
			SML::Logging::error(TEXT("Object not found for object path "), *ObjectData.ObjectPath);
		}
	}

	SML::Logging::info(TEXT("Saving Packages..."));
	//Now, save all packages we defined
	UEditorLoadingAndSavingUtils::SavePackages(DefinedPackages, true);
	SML::Logging::info(TEXT("Success!"));
}

void AddDependenciesForBlueprint(const FPackageObjectData& ObjectData, TArray<FString>& Dependencies) {
	const TSharedPtr<FJsonObject> StructJson = ObjectData.SourceObject;
	//add parent class as only dependency
	const FString& ParentClass = StructJson->GetStringField(TEXT("ParentClass"));
	AddDependencyIfNeeded(ParentClass, Dependencies);

	if (StructJson->HasField(TEXT("Functions"))) {
		const TArray<TSharedPtr<FJsonValue>> Functions = StructJson->GetArrayField(TEXT("Functions"));
		for (const TSharedPtr<FJsonValue>& Value : Functions) {
			const TSharedPtr<FJsonObject>& MethodObject = Value.Get()->AsObject();
			const FString& MethodName = MethodObject->GetStringField(TEXT("Name"));

			if (MethodName.StartsWith(TEXT("ExecuteUbergraph_"))) {
				continue; //Skip generated uber graph entry point function
			}
			if (MethodObject->HasField(TEXT("SuperClass"))) {
				const FString& SuperObjectPath = MethodObject->GetStringField(TEXT("SuperClass"));
				AddDependencyIfNeeded(SuperObjectPath, Dependencies);
			}
		}
	}
}


void PostInitializeObject(UObject* Object, const TSharedPtr<FJsonObject>& JsonObject) {
	UUserDefinedStruct* UserDefinedStruct = Cast<UUserDefinedStruct>(Object);
	
	if (UserDefinedStruct) {
		const TArray<TSharedPtr<FJsonValue>>& Fields = JsonObject->GetArrayField(TEXT("Fields"));
		//re-initialize all properties to their new defaults, then request recompile
		bool bSetDefaultValues = false;
		for (const TSharedPtr<FJsonValue>& Value : Fields) {
			const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
			const FString& FieldName = ValueObject->GetStringField(TEXT("Name"));
			const FGuid& VariableGuid = FStructureEditorUtils::GetGuidFromPropertyName(*FieldName);
			if (ValueObject->HasField(TEXT("Value"))) {
				FStructVariableDescription* VariableDesc = FStructureEditorUtils::GetVarDescByGuid(UserDefinedStruct, VariableGuid);
				check(VariableDesc != nullptr);
				const FString& VariableDefaultValue = ValueObject->GetStringField(TEXT("Value"));
				if (VariableDefaultValue != VariableDesc->DefaultValue) {
					VariableDesc->DefaultValue = VariableDefaultValue;
					bSetDefaultValues = true;
				}
			}
		}
		//request structure recompile when we actually set some default values
		if (bSetDefaultValues) {
			//will also mark package dirty, so we don't have to do it ourselves
			FStructureEditorUtils::OnStructureChanged(UserDefinedStruct, FStructureEditorUtils::EStructureEditorChangeInfo::DefaultValueChanged);
		}
	}
	
	UBlueprint* Blueprint = Cast<UBlueprint>(Object);
	if (Blueprint && JsonObject->HasField(TEXT("Fields"))) {
		const TArray<TSharedPtr<FJsonValue>> Fields = JsonObject->GetArrayField(TEXT("Fields"));
		//Blueprint should have been already compiled at that moment
		check(Blueprint->GeneratedClass != nullptr);
		UClass* BlueprintGeneratedClass = Blueprint->GeneratedClass;
		UObject* ClassDefaultObject = BlueprintGeneratedClass->GetDefaultObject();
		bool bSetDefaultValues = false;
		for (const TSharedPtr<FJsonValue>& Value : Fields) {
			const TSharedPtr<FJsonObject>& FieldObject = Value.Get()->AsObject();
			const FString& FieldName = FieldObject->GetStringField(TEXT("Name"));
			if (FieldName == TEXT("UberGraphFrame"))
				continue; //Skip generated uber graph frame field
			if (FieldObject->HasField(TEXT("Value"))) {
				UProperty* ResultProperty = BlueprintGeneratedClass->FindPropertyByName(*FieldName);
				SML::Logging::info(TEXT("BP "), *BlueprintGeneratedClass->GetPathName(), TEXT(" "), *FieldName);
				check(ResultProperty != nullptr);
				const FString& DefaultValue = FieldObject->GetStringField(TEXT("Value"));
				void* PropertyData = ResultProperty->ContainerPtrToValuePtr<void>(ClassDefaultObject);
				ResultProperty->ImportText(*DefaultValue, PropertyData, 0, ClassDefaultObject);
				bSetDefaultValues = true;
			}
		}
		if (bSetDefaultValues) {
			//Mark default class object package as dirty now
			ClassDefaultObject->MarkPackageDirty();
		}
	}
}

void AddDependenciesForStruct(const FPackageObjectData& ObjectData, TArray<FString>& Dependencies) {
	const TArray<TSharedPtr<FJsonValue>>& Fields = ObjectData.SourceObject->GetArrayField(TEXT("Fields"));
	for (const TSharedPtr<FJsonValue>& Value : Fields) {
		const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
		TSharedPtr<FJsonObject> PinData = ValueObject->GetObjectField(TEXT("PinType"));
		GatherPinTypeDependencies(PinData.ToSharedRef(), Dependencies);
	}
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
	return Struct;
}

FGuid AddStructVariableWithName(UUserDefinedStruct* Struct, const FEdGraphPinType& VarType, const FString& PredefinedUniqueName) {
	FString ErrorMessage;
	const bool Result = FStructureEditorUtils::CanHaveAMemberVariableOfType(Struct, VarType, &ErrorMessage);
	if (!Result) {
		SML::Logging::error(TEXT("Error Adding Field Because of: "), *ErrorMessage);
		check(false);
	}
	
	const FGuid& Guid = FStructureEditorUtils::GetGuidFromPropertyName(*PredefinedUniqueName);
	int32 FirstUnderscoreIndex;
	PredefinedUniqueName.FindChar('_', FirstUnderscoreIndex);
	check(FirstUnderscoreIndex != INDEX_NONE);
	const FString& DisplayName = PredefinedUniqueName.Mid(0, FirstUnderscoreIndex);
	const FName VarName = FName(*PredefinedUniqueName);

	//Only add variable if it doesn't exist already
	if (FStructureEditorUtils::GetVarDescByGuid(Struct, Guid) == nullptr && !FindObject<UObject>(Struct, *PredefinedUniqueName, false)) {
		FStructureEditorUtils::ModifyStructData(Struct);
		FStructVariableDescription NewVar;
		NewVar.VarName = VarName;
		NewVar.FriendlyName = DisplayName;
		NewVar.SetPinType(VarType);
		NewVar.VarGuid = Guid;
		NewVar.bDontEditoOnInstance = false;
		NewVar.bInvalidMember = false;
		FStructureEditorUtils::GetVarDesc(Struct).Add(NewVar);
	}

	//Do not fire struct change event now, fire it only after all fields have been added
	return Guid;
}

UPackage* CreateGenericObject(const FPackageObjectData& PackageObjectData, bool bHasDependents) {
	if (PackageObjectData.bIsUserStruct) {
		return CreateStructFromJson(PackageObjectData.SourceObject.ToSharedRef());
	}
	if (PackageObjectData.bIsBlueprint) {
		return CreateBlueprintFromJson(PackageObjectData.SourceObject.ToSharedRef(), bHasDependents);
	}
	return nullptr;
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
			if (ParameterName == TEXT("__WorldContext"))
				continue; //World context pin is created automatically in AllocateDefaultPins()
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

UK2Node* CreateFunctionOverride(UBlueprint* Blueprint, UFunction* OverrideFunc) {
	UClass* FunctionClass = Cast<UClass>(OverrideFunc->GetOuter());
	UEdGraph* EventGraph = FBlueprintEditorUtils::FindEventGraph(Blueprint);
	if (UEdGraphSchema_K2::FunctionCanBePlacedAsEvent(OverrideFunc) && EventGraph) {
		// Add to event graph
		FName EventName = OverrideFunc->GetFName();
		UK2Node_Event* ExistingNode = FBlueprintEditorUtils::FindOverrideForFunction(Blueprint, FunctionClass, EventName);

		if (!ExistingNode) {
			return FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_Event>(
				EventGraph,
				EventGraph->GetGoodPlaceForNewNode(),
				EK2NewNodeFlags::SelectNewNode,
				[EventName, FunctionClass](UK2Node_Event* NewInstance) {
				NewInstance->EventReference.SetExternalMember(EventName, FunctionClass);
				NewInstance->bOverrideFunction = true;
			});
		}
	} else {
		// Implement the function graph
		UEdGraph* const NewGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, OverrideFunc->GetFName(), UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());
		FBlueprintEditorUtils::AddFunctionGraph(Blueprint, NewGraph, /*bIsUserCreated=*/ false, FunctionClass);
		TArray<UK2Node_FunctionEntry*> ResultArray;
		NewGraph->GetNodesOfClass<UK2Node_FunctionEntry>(ResultArray);
		return ResultArray.Num() > 0 ? ResultArray[0] : nullptr;
	}
	return nullptr;
}

bool IsInterfaceImplemented(UBlueprint* Blueprint, UClass* InterfaceClass) {
	for (int32 i = 0; i < Blueprint->ImplementedInterfaces.Num(); i++) {
		if (Blueprint->ImplementedInterfaces[i].Interface == InterfaceClass) {
			return true;
		}
	}
	return false;
}

void InitializeBlueprint(UBlueprint* Blueprint, const TSharedPtr<FJsonObject>& BlueprintJson, bool bHasDependents) {
	const FString& ParentClassPath = BlueprintJson->GetStringField(TEXT("ParentClass"));
	TArray<UClass*> OverrideFunctionSources;
	UClass* ParentClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *ParentClassPath));
	check(ParentClass != nullptr);
	OverrideFunctionSources.Add(ParentClass);
	
	//Implement required interfaces for generated blueprint
	if (BlueprintJson->HasField(TEXT("ImplementedInterfaces"))) {
		const TArray<TSharedPtr<FJsonValue>> ImplementedInterfaces = BlueprintJson->GetArrayField(TEXT("ImplementedInterfaces"));
		for (const TSharedPtr<FJsonValue>& Value : ImplementedInterfaces) {
			const FString& InterfaceName = Value.Get()->AsString();
			UClass* InterfaceClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *InterfaceName));
			//Ensure that class exists and is in fact interface
			check(InterfaceClass != nullptr && InterfaceClass->HasAnyClassFlags(EClassFlags::CLASS_Interface));
			//Only implement interface if it isn't already implemented
			if (!IsInterfaceImplemented(Blueprint, InterfaceClass)) {
				FBlueprintEditorUtils::ImplementNewInterface(Blueprint, *InterfaceName);
			}
			//Still add it to function sources for resolving overrides
			OverrideFunctionSources.Add(InterfaceClass);
		}
	}

	//Generate blueprint own properties (only properties with specified pin type)
	if (BlueprintJson->HasField(TEXT("Fields"))) {
		const TArray<TSharedPtr<FJsonValue>> Fields = BlueprintJson->GetArrayField(TEXT("Fields"));
		for (const TSharedPtr<FJsonValue>& Value : Fields) {
			const TSharedPtr<FJsonObject>& FieldObject = Value.Get()->AsObject();
			const FString& FieldName = FieldObject->GetStringField(TEXT("Name"));
			if (FieldName == TEXT("UberGraphFrame"))
				continue; //Skip generated uber graph frame field
			if (FBlueprintEditorUtils::FindMemberVariableGuidByName(Blueprint, *FieldName).IsValid())
				continue; //Skip adding variable if it is already there
			if (FieldObject->HasField(TEXT("PinType"))) {
				//It is blueprint's own variable, generate it
				FEdGraphPinType PinType = CreateGraphPinType(FieldObject->GetObjectField(TEXT("PinType")).ToSharedRef());
				SML::Logging::info(TEXT("Adding member variable "), *FieldName, TEXT(" TO BP "), *Blueprint->GetPathName());
				FBlueprintEditorUtils::AddMemberVariable(Blueprint, *FieldName, PinType);
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
			
			if (MethodName.StartsWith(TEXT("ExecuteUbergraph_"))) {
				continue; //Skip generated uber graph entry point function
			}
			
			UEdGraph* ExistingGraph = FindObject<UEdGraph>(Blueprint, *MethodName);
			if (ExistingGraph != nullptr) {
				continue; //Graph is already there, no need to create it again
			}

			UK2Node* ResultEntryNode = nullptr;
			if (MethodObject->HasField(TEXT("SuperClass"))) {
				//if this is override function, set super class for it
				const FString& SuperObjectPath = MethodObject->GetStringField(TEXT("SuperClass"));
				UClass* ParentFunctionClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *SuperObjectPath));
				check(ParentFunctionClass != nullptr);
				if (ParentFunctionClass->HasAllClassFlags(EClassFlags::CLASS_Interface)) {
					continue; //Do not create overrides manually from interface classes - already implemented via ImplementNewInterface
				}
				if (FBlueprintEditorUtils::FindOverrideForFunction(Blueprint, ParentFunctionClass, *MethodName) != nullptr) {
					continue; //Function override is already implemented, skip it
				}
				UFunction* Function = ParentFunctionClass->FindFunctionByName(*MethodName);
				SML::Logging::info(TEXT("BP "), *Blueprint->GetPathName(), TEXT(" Class "), *SuperObjectPath, TEXT(" Function "), *MethodName);
				check(Function != nullptr);
				ResultEntryNode = CreateFunctionOverride(Blueprint, Function);
			} else {
				UEdGraph* FunctionGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, *MethodName, UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());
				FBlueprintEditorUtils::AddFunctionGraph(Blueprint, FunctionGraph, false, static_cast<UClass*>(nullptr));
				TArray<UK2Node_FunctionEntry*> EntryNodes;
				FunctionGraph->GetNodesOfClass(EntryNodes);
				UK2Node_FunctionEntry* EntryNode = EntryNodes[0];
				DefineCustomFunctionFromJson(*FunctionGraph, EntryNode, MethodObject);
				ResultEntryNode = EntryNode;
			}
			if (ResultEntryNode != nullptr) {
				ResultEntryNode->bCommentBubblePinned = true;
				ResultEntryNode->bCommentBubbleVisible = true;
				ResultEntryNode->OnUpdateCommentText(TEXT("Function Stub: Implementation not available."));
			}
		}
	}

	if (bHasDependents) {
		//compile immediately if we have dependents
		FBPCompileRequest CompileRequest{ Blueprint, EBlueprintCompileOptions::None, nullptr };
		FBlueprintCompilationManager::CompileSynchronously(CompileRequest);
	} else {
		//Otherwise, queue recompilation
		FBlueprintCompilationManager::QueueForCompilation(Blueprint);
	}
}

UBlueprint* CreateBlueprint(UPackage* Package, const FString& Name, const FString& ParentClassPath) {
	UClass* ParentClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), ANY_PACKAGE, *ParentClassPath));
	SML::Logging::info(TEXT("Parent Class: "), *ParentClass->GetPathName());
	check(ParentClass != nullptr);
	EBlueprintType BlueprintType = BPTYPE_Normal;
	if (ParentClass == UBlueprintFunctionLibrary::StaticClass()) {
		BlueprintType = BPTYPE_FunctionLibrary;
	} else if (ParentClass == UInterface::StaticClass()) {
		BlueprintType = BPTYPE_Interface;
	}
	return FKismetEditorUtilities::CreateBlueprint(ParentClass, Package, *Name, BlueprintType, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
}

UPackage* CreateBlueprintFromJson(const TSharedRef<FJsonObject>& BlueprintJson, bool bHasDependents) {
	//Remove _C from the object name because we got a class name, while we are creating blueprint object itself
	const FString& ObjectPath = BlueprintJson->GetStringField(TEXT("Blueprint"));
	FString PackageName, ObjectName;
	ParseObjectPath(ObjectPath, PackageName, ObjectName);
	ObjectName = ObjectName.Mid(0, ObjectName.Len() - 2);

	UPackage* TargetPackage = CreatePackage(nullptr, *PackageName);
	SML::Logging::info(TEXT("Creating blueprint "), *ObjectPath, TEXT("; Has Dependents? "), bHasDependents);

	UBlueprint* Blueprint = LoadObject<UBlueprint>(TargetPackage, *ObjectName);
	if (Blueprint == nullptr) {
		const FString& ParentClassPath = BlueprintJson->GetStringField(TEXT("ParentClass"));
		Blueprint = CreateBlueprint(TargetPackage, ObjectName, ParentClassPath);
		check(Blueprint != nullptr);
	}
	//Force Blueprint synchronous compilation now if somebody depends on it
	if (bHasDependents) {
		const FBPCompileRequest CompileRequest{ Blueprint, EBlueprintCompileOptions::None, nullptr };
		FBlueprintCompilationManager::CompileSynchronously(CompileRequest);
	} else {
		//Otherwise, queue blueprint for further compilation with all other blueprints
		FBlueprintCompilationManager::QueueForCompilation(Blueprint);
	}
	return TargetPackage;
}

void InitializeUserStruct(UUserDefinedStruct* StructObject, const TSharedPtr<FJsonObject>& StructJson) {
	//create all required struct fields
	const TArray<TSharedPtr<FJsonValue>>& Fields = StructJson->GetArrayField(TEXT("Fields"));
	for (const TSharedPtr<FJsonValue>& Value : Fields) {
		const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
		const FString& FieldName = ValueObject->GetStringField(TEXT("Name"));
		const FEdGraphPinType& PinType = CreateGraphPinType(ValueObject->GetObjectField(TEXT("PinType")).ToSharedRef());
		AddStructVariableWithName(StructObject, PinType, FieldName);
	}
	//fire structure change event now, after all variables have been added
	//it will cause structure recompile, and also mark package dirty.
	FStructureEditorUtils::OnStructureChanged(StructObject, FStructureEditorUtils::EStructureEditorChangeInfo::AddedVariable);
}

UPackage* CreateStructFromJson(const TSharedRef<FJsonObject>& StructJson) {
	const FString& ObjectPath = StructJson->GetStringField(TEXT("StructName"));
	SML::Logging::info(TEXT("Creating user defined struct "), *ObjectPath);
	
	UUserDefinedStruct* StructObject = LoadObject<UUserDefinedStruct>(nullptr, *ObjectPath);
	if (StructObject == nullptr) {
		FString PackageName, ObjectName;
		ParseObjectPath(ObjectPath, PackageName, ObjectName);
		UPackage* TargetPackage = CreatePackage(nullptr, *PackageName);
		const EObjectFlags Flags = RF_Public | RF_Standalone;
		FGuid PredefinedGuid = FGuid::NewGuid();
		FGuid::Parse(StructJson->GetStringField(TEXT("Guid")), PredefinedGuid);
		//create structure with predefined FGuid value
		StructObject = CreateUserDefinedStructWithGUID(TargetPackage, FName(*ObjectName), Flags, PredefinedGuid);
		check(StructObject != nullptr);
	}
	
	InitializeUserStruct(StructObject, StructJson);
	return Cast<UPackage>(StructObject->GetTypedOuter(UPackage::StaticClass()));
}

UPackage* CreateEnumerationFromJson(const TSharedRef<FJsonObject>& EnumJson) {
	const FString& ObjectPath = EnumJson->GetStringField(TEXT("StructName"));
	SML::Logging::info(TEXT("Creating user defined enumeration "), *ObjectPath);
	
	UUserDefinedEnum* EnumObject = LoadObject<UUserDefinedEnum>(nullptr, *ObjectPath);
	if (EnumObject == nullptr) {
		FString PackageName, ObjectName;
		ParseObjectPath(ObjectPath, PackageName, ObjectName);
		UPackage* TargetPackage = CreatePackage(nullptr, *PackageName);
		const EObjectFlags Flags = RF_Public | RF_Standalone;
		EnumObject = Cast<UUserDefinedEnum>(FEnumEditorUtils::CreateUserDefinedEnum(TargetPackage, FName(*ObjectName), Flags));
		check(EnumObject != nullptr);
	}

	const TArray<TSharedPtr<FJsonValue>>& Values = EnumJson->GetArrayField(TEXT("Values"));
	const int32 EnumsCurrently = EnumObject->NumEnums();
	const int32 EnumsExpected = Values.Num();
	//Ensure enums holds exactly as much values as we need it to
	if (EnumsCurrently != EnumsExpected) {
		const bool ShouldTruncate = EnumsCurrently > EnumsExpected;
		const uint32 Difference = FMath::Abs(EnumsCurrently - EnumsExpected);
		for (uint32 i = 0; i < Difference; i++) {
			if (ShouldTruncate)
				FEnumEditorUtils::RemoveEnumeratorFromUserDefinedEnum(EnumObject, 0);
			else FEnumEditorUtils::AddNewEnumeratorForUserDefinedEnum(EnumObject);
		}
	}
	
	//after that, enumerate entries and update their display names
	for (const TSharedPtr<FJsonValue>& Value : Values) {
		const FJsonObject* ValueObject = Value.Get()->AsObject().Get();
		if (!ValueObject->HasField(TEXT("DisplayName"))) {
			continue; //skip entries without display name, including _MAX
		}
		const int32 EnumIndex = ValueObject->GetIntegerField(TEXT("Value"));
		const FString& DisplayName = ValueObject->GetStringField(TEXT("DisplayName"));
		const FString& CurrentName = EnumObject->GetDisplayNameText(EnumIndex).ToString();
		if (CurrentName != DisplayName) {
			FEnumEditorUtils::SetEnumeratorDisplayName(EnumObject, EnumIndex, FText::AsCultureInvariant(DisplayName));
		}
	}
	return Cast<UPackage>(EnumObject->GetTypedOuter(UPackage::StaticClass()));
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
	return StaticFindObject(UObject::StaticClass(), ANY_PACKAGE, *ObjectPath);
}

void AddDependencyIfNeeded(const FString& ObjectPath, TArray<FString>& Dependencies) {
	//add to required dependencies only if we couldn't find it
	if (!IsObjectAlreadyLoaded(ObjectPath)) {
		Dependencies.Add(ObjectPath);
	}
}
#endif
