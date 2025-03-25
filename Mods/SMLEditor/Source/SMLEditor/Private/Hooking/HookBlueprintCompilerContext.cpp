#include "Hooking/HookBlueprintCompilerContext.h"
#include "EdGraphUtilities.h"
#include "Hooking/HookTargetNode_Root.h"
#include "Kismet2/KismetReinstanceUtilities.h"
#include "Patching/BlueprintHookBlueprint.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

FHookBlueprintCompilerContext::FHookBlueprintCompilerContext(UHookBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions)
	: FKismetCompilerContext(SourceSketch, InMessageLog, InCompilerOptions) {}

void FHookBlueprintCompilerContext::PreCompile() {
	FKismetCompilerContext::PreCompile();

	// Clear compiler messages before we recompile the blueprint on the hook graph. Kismet will not clear it for us
	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint);
	if(CompileOptions.CompileType == EKismetCompileType::Full && HookBlueprint && HookBlueprint->HookTargetGraph) {
		for (UEdGraphNode* GraphNode : HookBlueprint->HookTargetGraph->Nodes) {
			if (GraphNode) {
				GraphNode->ClearCompilerMessage();
			}
		}
	}
}

void FHookBlueprintCompilerContext::CreateFunctionList() {
	FKismetCompilerContext::CreateFunctionList();

	// All functions in the hook blueprint are for internal use only by the hooking code gen, they cannot be called by other kismet code directly
	for (FKismetFunctionContext& FunctionContext : FunctionList) {
		FunctionContext.MarkAsInternalOrCppUseOnly();
	}

	// Duplicate hook target graph and perform early validation on the nodes. Graph can be null during the first compilation right after creation, this is not an error
	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint);
	if (bIsFullCompile && HookBlueprint && HookBlueprint->HookTargetGraph) {
		SourceHookTargetGraph = FEdGraphUtilities::CloneGraph(HookBlueprint->HookTargetGraph, nullptr, &MessageLog, true);

		// Validate all nodes during compilation
		for (const UEdGraphNode* GraphNode : SourceHookTargetGraph->Nodes) {
			if (GraphNode) {
				GraphNode->ValidateNodeDuringCompilation(MessageLog);
			}
		}

		// Perform the expansion step for the target nodes and let them do any work necessary to prepare for compilation
		for (UEdGraphNode* GraphNode : SourceHookTargetGraph->Nodes) {
			if (UHookTargetNode* TargetNode = Cast<UHookTargetNode>(GraphNode)) {
				TargetNode->PrepareForCompilation(MessageLog, SourceHookTargetGraph);
			}
		}
	}
}

void FHookBlueprintCompilerContext::CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& InOldCDO) {
	FKismetCompilerContext::CleanAndSanitizeClass(ClassToClean, InOldCDO);

	// Remove hook descriptors and move derived data to transient package
	if (UHookBlueprintGeneratedClass* HookBlueprintGeneratedClass = Cast<UHookBlueprintGeneratedClass>(ClassToClean)) {
		// Move derived data to the transient package
		const ERenameFlags RenFlags = REN_DontCreateRedirectors | (Blueprint->bIsRegeneratingOnLoad ? REN_ForceNoResetLoaders : 0) | REN_NonTransactional | REN_DoNotDirty;
		if (UObject* DerivedDataRoot = HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot)
		{
			const FString TransientDerivedDataNameString = FString::Printf(TEXT("TRASH_%s_%s"), *HookBlueprintGeneratedClass->GetName(), *DerivedDataRoot->GetName());
			const FName TransientDerivedDataName = MakeUniqueObjectName(GetTransientPackage(), DerivedDataRoot->GetClass(), FName(*TransientDerivedDataNameString));
			DerivedDataRoot->Rename(*TransientDerivedDataName.ToString(), GetTransientPackage(), RenFlags);
			FLinkerLoad::InvalidateExport(DerivedDataRoot);
		}

		// Clear reference to derived data and void hook descriptors
		HookBlueprintGeneratedClass->HookDescriptors.Empty();
		HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot = nullptr;
	}
}

void FHookBlueprintCompilerContext::FinishCompilingClass(UClass* Class) {
	FKismetCompilerContext::FinishCompilingClass(Class);

	// TODO: This should be done before CompileFunction and PostCompileFunction, but there is no extension point like that in FKismetCompilerContext...
	if (bIsFullCompile && SourceHookTargetGraph) {
		CompileHookTargetGraph();
	}
}

void FHookBlueprintCompilerContext::SpawnNewClass(const FString& NewClassName) {
	// First, attempt to find the class, in case it hasn't been serialized in yet
	NewClass = FindObject<UHookBlueprintGeneratedClass>(Blueprint->GetOutermost(), *NewClassName);
	if (NewClass == NULL)
	{
		// If the class hasn't been found, then spawn a new one
		NewClass = NewObject<UHookBlueprintGeneratedClass>(Blueprint->GetOutermost(), FName(*NewClassName), RF_Public | RF_Transactional);
	}
	else
	{
		// Already existed, but wasn't linked in the Blueprint yet due to load ordering issues
		NewClass->ClassGeneratedBy = Blueprint;
		FBlueprintCompileReinstancer::Create(NewClass);
	}
}

void FHookBlueprintCompilerContext::CompileHookTargetGraph() {
	UHookBlueprintGeneratedClass* HookBlueprintGeneratedClass = Cast<UHookBlueprintGeneratedClass>(TargetClass);

	// Make sure that we have a valid generated class
	if (HookBlueprintGeneratedClass == nullptr) {
		MessageLog.Error(*LOCTEXT("InternalCompilerError_NullHookBPGC", "INTERNAL COMPILER ERROR: Blueprint Generated Class is not a Hook Blueprint Generated Class").ToString());
		return;
	}

	// Create derived data root object on the class
	HookBlueprintGeneratedClass->HookDescriptors.Empty();
	HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot = NewObject<UHookBlueprintDerivedDataRoot>(TargetClass, TEXT("HookBlueprintDerivedData"), RF_DuplicateTransient);

	// Make sure we have created a data root successfully
	if (HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot == nullptr) {
		MessageLog.Error(*LOCTEXT("InternalCompilerError_CannotCreateDerivedData", "INTERNAL COMPILER ERROR: Failed to create Derived Data for Hook Blueprint.").ToString());
		return;
	}
	
	// Resolve all root nodes in the graph
	TArray<UHookTargetNode_Root*> AllRootNodes;
	SourceHookTargetGraph->GetNodesOfClass(AllRootNodes);

	// Compile them and add them to hook descriptors
	TSet<UClass*> UniqueHookTargetClasses;
	for (const UHookTargetNode_Root* TargetNode : AllRootNodes) {
		// Compile the node hierarchy for this hook definition
		FBlueprintHookDefinition ResultHookDefinition;
		TargetNode->CompileRoot(MessageLog, TargetClass, HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot, ResultHookDefinition);

		// Only add the definition to the list if it is actually valid
		if (ResultHookDefinition.HookFunction != nullptr && ResultHookDefinition.TargetFunction != nullptr && ResultHookDefinition.TargetSpecifier != nullptr) {
			HookBlueprintGeneratedClass->HookDescriptors.Add(ResultHookDefinition);
			UniqueHookTargetClasses.Add(ResultHookDefinition.TargetFunction->GetOuterUClass());
		}
	}
}

#undef LOCTEXT_NAMESPACE
