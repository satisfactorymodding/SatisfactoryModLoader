#include "Hooking/HookBlueprintCompilerContext.h"
#include "EdGraphUtilities.h"
#include "K2Node_CallFunction.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "K2Node_IfThenElse.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Nodes/HookTargetNode_Root.h"
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

		TArray<FName> HookTargetFunctionGraphNames;

		// Perform the expansion step for the target nodes and let them do any work necessary to prepare for compilation
		for (UEdGraphNode* GraphNode : SourceHookTargetGraph->Nodes) {
			if (UHookTargetNode* TargetNode = Cast<UHookTargetNode>(GraphNode)) {
				TargetNode->PrepareForCompilation(MessageLog, SourceHookTargetGraph);
			}
			// Cache a list of functions that are used as hook targets. We evaluate the function graph list to determine if some of them are not static and need static stubs generated for them
			if (const UHookTargetNode_Root* RootTargetNode = Cast<UHookTargetNode_Root>(GraphNode)) {
				if (RootTargetNode->HookFunctionReference.IsSelfContext() && RootTargetNode->HookFunctionReference.GetMemberName() != NAME_None) {
					HookTargetFunctionGraphNames.Add(RootTargetNode->HookFunctionReference.GetMemberName());
				}
			}
		}

		// We have to do this logic here because there is no hook between PrecompileFunction and Link
		TArray<FInstanceHookStubGenerationData> StubGenerationDataList;
		
		for (FKismetFunctionContext& FunctionContext : FunctionList) {
			// Retrieve all entry points for this graph
			TArray<UK2Node_FunctionEntry*> EntryPoints;
			FunctionContext.SourceGraph->GetNodesOfClass(EntryPoints);
			if (EntryPoints.Num() != 1) continue;

			// If we have a valid function name that is a hook target, mark the function as internal
			const FName NewFunctionName = EntryPoints[0]->CustomGeneratedFunctionName != NAME_None ? EntryPoints[0]->CustomGeneratedFunctionName : EntryPoints[0]->FunctionReference.GetMemberName();
			if (NewFunctionName != NAME_None && HookTargetFunctionGraphNames.Contains(NewFunctionName)) {
				FunctionContext.MarkAsInternalOrCppUseOnly();

				TArray<UK2Node_FunctionResult*> FunctionResults;
				FunctionContext.SourceGraph->GetNodesOfClass(FunctionResults);

				// If this function is not Static, save function name, entry point and terminator to generate static stub for it
				if (!EntryPoints[0]->HasAnyExtraFlags(FUNC_Static)) {
					FInstanceHookStubGenerationData& NewGenerationData = StubGenerationDataList.AddDefaulted_GetRef();
					NewGenerationData.InstanceFunctionName = NewFunctionName;
					NewGenerationData.FunctionEntry = EntryPoints[0];
					NewGenerationData.FunctionResult = FunctionResults.IsEmpty() ? nullptr : FunctionResults[0];
				}
			}
		}

		// Generate stubs for each instance hook
		for (const FInstanceHookStubGenerationData& StubGenerationData : StubGenerationDataList) {
			CreateStaticFunctionStubForInstanceHookFunction(StubGenerationData);
		}
	}

	// All functions in the hook blueprint library are for internal use only, even if they are not a hook target
	if (HookBlueprint->BlueprintType == BPTYPE_FunctionLibrary) {
		for (FKismetFunctionContext& FunctionContext : FunctionList) {
			FunctionContext.MarkAsInternalOrCppUseOnly();
		}	
	}
}

void FHookBlueprintCompilerContext::CreateStaticFunctionStubForInstanceHookFunction(const FInstanceHookStubGenerationData& StubGenerationData) {
	// Ensure the original function is not pure
	if (StubGenerationData.FunctionEntry->HasAnyExtraFlags(FUNC_BlueprintPure)) {
		MessageLog.Error(*LOCTEXT("InvalidHookFunctionisPure", "Hook Function @@ is marked as Pure. Hook functions cannot be Pure.").ToString(), StubGenerationData.FunctionEntry);
		return;
	}
	
	const UFunction* GetHookObjectFunction = Blueprint->ParentClass ? Blueprint->ParentClass->FindFunctionByName(TEXT("GetHookObjectInstanceFromTargetMethodInstance")) : nullptr;
	
	// Ensure that the function to retrieve the hook object instance actually exists
	if (GetHookObjectFunction == nullptr) {
		MessageLog.Error(*FText::Format(LOCTEXT("InvalidParentClassForInstanceFunctionHooks", "Hook Function @@ is not Static, but Parent Class {0} of this Hook Blueprint does not support Instance Hook Functions."),
			FText::FromName(Blueprint->ParentClass ? Blueprint->ParentClass->GetFName() : NAME_None)).ToString(), StubGenerationData.FunctionEntry);
		return;
	}
	
	// Create a new function graph for the static wrapper
	const FString FunctionName = TEXT("__StaticHookWrapper") + StubGenerationData.InstanceFunctionName.ToString();
	UEdGraph* FunctionGraph = FBlueprintEditorUtils::CreateNewGraph(Blueprint, FBlueprintEditorUtils::FindUniqueKismetName(Blueprint, FunctionName), UEdGraph::StaticClass(), UEdGraphSchema_K2::StaticClass());
	FunctionGraph->SetFlags(RF_Transient);
	GeneratedFunctionGraphs.Add(FunctionGraph);

	const UEdGraphSchema_K2* K2Schema = Cast<const UEdGraphSchema_K2>(FunctionGraph->GetSchema());
	K2Schema->CreateDefaultNodesForGraph(*FunctionGraph);
	K2Schema->MarkFunctionEntryAsEditable(FunctionGraph, true);

	// Create function entry node
	UK2Node_FunctionEntry* EntryNode{};
	UK2Node* CurrentNodeInFunctionChain{};
	{
		FGraphNodeCreator<UK2Node_FunctionEntry> FunctionEntryCreator(*FunctionGraph);
		EntryNode = FunctionEntryCreator.CreateNode();

		// Copy function reference from the original entry point, but override function name to match the name of the graph
		EntryNode->FunctionReference = StubGenerationData.FunctionEntry->FunctionReference;
		EntryNode->CustomGeneratedFunctionName = *FunctionName;
		
		// Finalize the node creation. Note that entry point node will not have world context pin because we have not marked the graph as Static yet
		FunctionEntryCreator.Finalize();

		// Copy user defined pins from the original function entry point
		for (const TSharedPtr<FUserPinInfo>& UserDefinedPin : StubGenerationData.FunctionEntry->UserDefinedPins) {
			EntryNode->CreatePinFromUserDefinition(MakeShared<FUserPinInfo>(*UserDefinedPin));
		}
		
		CurrentNodeInFunctionChain = EntryNode;
	}

	// Create call to GetHookObjectInstanceFromTargetMethodInstance on the target instance
	UEdGraphPin* TargetObjectInstancePin{};
	UEdGraphPin* RawHookObjectInstanceReturnValuePin{};
	UEdGraphPin* HookObjectInstanceThenPin{};
	UEdGraphPin* OriginalValuePin{};
	{
		// Resolve existing target pin created by the user, or create a synthetic target pin
		UEdGraphPin* ExecutionTargetPin = EntryNode->FindPin(TEXT("Target"), EGPD_Output);
		if (ExecutionTargetPin == nullptr) {
			ExecutionTargetPin = EntryNode->FindPin(TEXT("__Target"), EGPD_Output);
		}
		if (ExecutionTargetPin == nullptr) {
			const TSharedPtr<FUserPinInfo> GeneratedTargetPinInfo = MakeShared<FUserPinInfo>();
			GeneratedTargetPinInfo->PinName = TEXT("__Target");
			GeneratedTargetPinInfo->DesiredPinDirection = EGPD_Output;
			GeneratedTargetPinInfo->PinType = FEdGraphPinType(UEdGraphSchema_K2::PC_Object, NAME_None, UObject::StaticClass(), EPinContainerType::None, false, FEdGraphTerminalType());
			ExecutionTargetPin = EntryNode->CreatePinFromUserDefinition(GeneratedTargetPinInfo);
		}

		// Resolve potential OriginalValue pin if this is a redirect hook. We will need it later to connect it to the return value.
		OriginalValuePin = EntryNode->FindPin(TEXT("OriginalValue"), EGPD_Output);
		if (OriginalValuePin == nullptr) {
			OriginalValuePin = EntryNode->FindPin(TEXT("__OriginalValue"), EGPD_Output);
		}
		
		FGraphNodeCreator<UK2Node_CallFunction> RetrieveHookObjectCallCreator(*FunctionGraph);
		UK2Node_CallFunction* RetrieveHookObjectCall = RetrieveHookObjectCallCreator.CreateNode();
		RetrieveHookObjectCall->SetFromFunction(GetHookObjectFunction);

		// Finalize the node and place it after the previous node
		RetrieveHookObjectCall->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		RetrieveHookObjectCall->NodePosY = CurrentNodeInFunctionChain->NodePosY;
		RetrieveHookObjectCallCreator.Finalize();

		// Retrieve necessary pins to plug in the function call
		TargetObjectInstancePin = RetrieveHookObjectCall->FindPin(TEXT("InObjectInstance"), EGPD_Input);
		UEdGraphPin* HookObjectClassPin = RetrieveHookObjectCall->FindPin(TEXT("InHookObjectClass"), EGPD_Input);
		RawHookObjectInstanceReturnValuePin = RetrieveHookObjectCall->FindPin(TEXT("ReturnValue"), EGPD_Output);
		HookObjectInstanceThenPin = RetrieveHookObjectCall->GetThenPin();

		// Make sure self pin has CDO as the default connected object, because if this function is in the self context, the pin generation logic will assume that it is not static, which is not the case
		if (UEdGraphPin* SelfPin = RetrieveHookObjectCall->FindPin(UEdGraphSchema_K2::PN_Self, EGPD_Input)) {
			SelfPin->DefaultObject = GetHookObjectFunction->GetOuterUClass()->GetDefaultObject();
		}

		// Validate that all the pins are valid
		if (!RetrieveHookObjectCall->GetExecPin() || !TargetObjectInstancePin || !HookObjectClassPin || !RawHookObjectInstanceReturnValuePin) {
			MessageLog.Error(*LOCTEXT("InternalError_InvalidInstanceFunctionHelperFunc", "INTERNAL COMPILER ERROR: GetHookObjectInstanceFromTargetMethodInstance signature is invalid for blueprint parent class").ToString());
			return;
		}

		// Plug in the function call by connecting the exec pins and object pins, as well as setting up the const pin value
		EntryNode->GetThenPin()->MakeLinkTo(RetrieveHookObjectCall->GetExecPin());
		ExecutionTargetPin->MakeLinkTo(TargetObjectInstancePin);
		HookObjectClassPin->DefaultObject = NewClass;
		CurrentNodeInFunctionChain = RetrieveHookObjectCall;
	}

	// Create cast node to cast object to our expected blueprint type
	UEdGraphPin* CastedHookObjectInstancePin{};
	{
		FGraphNodeCreator<UK2Node_DynamicCast> CastRawHookObjectInstanceToBlueprintClassCreator(*FunctionGraph);
		UK2Node_DynamicCast* CastRawHookObjectInstanceToBlueprintClass = CastRawHookObjectInstanceToBlueprintClassCreator.CreateNode();
		// Set target type to the blueprint class, and mark the cast as pure
		CastRawHookObjectInstanceToBlueprintClass->TargetType = NewClass;
		CastRawHookObjectInstanceToBlueprintClass->SetPurity(true);

		// Finalize the node and place it after the call node
		CastRawHookObjectInstanceToBlueprintClass->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		CastRawHookObjectInstanceToBlueprintClass->NodePosY = CurrentNodeInFunctionChain->NodePosY;
		CastRawHookObjectInstanceToBlueprintClassCreator.Finalize();

		// Retrieve necessary pins to plug in the function call
		UEdGraphPin* ObjectToCastPin = CastRawHookObjectInstanceToBlueprintClass->GetCastSourcePin();
		CastedHookObjectInstancePin = CastRawHookObjectInstanceToBlueprintClass->GetCastResultPin();

		// Connect object to cast pin to the raw hook object return value pin and update the connection to get rid of wildcard type
		ObjectToCastPin->MakeLinkTo(RawHookObjectInstanceReturnValuePin);
		CastRawHookObjectInstanceToBlueprintClass->NotifyPinConnectionListChanged(ObjectToCastPin);
		CurrentNodeInFunctionChain = CastRawHookObjectInstanceToBlueprintClass;
	}

	// Create call to UKismetSystemLibrary::IsValid to check the return value validity
	UEdGraphPin* ObjectInstanceValidPin{};
	{
		FGraphNodeCreator<UK2Node_CallFunction> IsHookObjectInstanceValidCallCreator(*FunctionGraph);
		UK2Node_CallFunction* IsHookObjectInstanceValidCall = IsHookObjectInstanceValidCallCreator.CreateNode();
		IsHookObjectInstanceValidCall->SetFromFunction(UKismetSystemLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetSystemLibrary, IsValid)));

		// Finalize the node and place it after the call node
		IsHookObjectInstanceValidCall->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		IsHookObjectInstanceValidCall->NodePosY = CurrentNodeInFunctionChain->NodePosY;
		IsHookObjectInstanceValidCallCreator.Finalize();

		// Retrieve necessary pins to plug in the function call
		UEdGraphPin* ObjectInstanceToCheckPin = IsHookObjectInstanceValidCall->FindPinChecked(TEXT("Object"), EGPD_Input);
		ObjectInstanceValidPin = IsHookObjectInstanceValidCall->FindPinChecked(TEXT("ReturnValue"), EGPD_Output);

		// Plug in Object pin for IsValid function call
		CastedHookObjectInstancePin->MakeLinkTo(ObjectInstanceToCheckPin);
		CurrentNodeInFunctionChain = IsHookObjectInstanceValidCall;
	}

	// Create branch depending on whenever the object instance is valid or not
	UEdGraphPin* ObjectInstanceValidThenPin{};
	UEdGraphPin* ObjectInstanceInvalidThenPin{};
	{
		FGraphNodeCreator<UK2Node_IfThenElse> BranchNodeCreator(*FunctionGraph);
		UK2Node_IfThenElse* BranchNode = BranchNodeCreator.CreateNode();
		
		// Finalize the node and place it after the previous node
		BranchNode->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		BranchNode->NodePosY = CurrentNodeInFunctionChain->NodePosY;
		BranchNodeCreator.Finalize();

		// Connect execution pin and the branch validity pin
		BranchNode->GetConditionPin()->MakeLinkTo(ObjectInstanceValidPin);
		BranchNode->GetExecPin()->MakeLinkTo(HookObjectInstanceThenPin);
		ObjectInstanceValidThenPin = BranchNode->GetThenPin();
		ObjectInstanceInvalidThenPin = BranchNode->GetElsePin();
		CurrentNodeInFunctionChain = BranchNode;
	}

	// Create function exit node if hook object instance is not valid. That node must return original value if possible, and leave everything else as default
	{
		FGraphNodeCreator<UK2Node_FunctionResult> FunctionReturnCreator(*FunctionGraph);
		UK2Node_FunctionResult* FallbackReturnNode = FunctionReturnCreator.CreateNode();

		// Copy function reference from the original entry point
		FallbackReturnNode->FunctionReference = StubGenerationData.FunctionEntry->FunctionReference;

		// Finally allocate the node pins and finish the creation process
		FallbackReturnNode->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		FallbackReturnNode->NodePosY = CurrentNodeInFunctionChain->NodePosY - FMath::Max(CurrentNodeInFunctionChain->NodeHeight, AverageNodeHeight) - 100;
		FunctionReturnCreator.Finalize();

		// Copy user defined pins from the original function terminator if we have one
		if (StubGenerationData.FunctionResult) {
			for (const TSharedPtr<FUserPinInfo>& UserDefinedPin : StubGenerationData.FunctionResult->UserDefinedPins) {
				FallbackReturnNode->CreatePinFromUserDefinition(MakeShared<FUserPinInfo>(*UserDefinedPin));
			}
		}

		// Connect else pin to the exec pin of fallback return node
		FallbackReturnNode->GetExecPin()->MakeLinkTo(ObjectInstanceInvalidThenPin);

		// If we have a return value pin and original value pin, connect original value to the return pin so that the hook returns the original expression when object instance is not available
		UEdGraphPin* ReturnValuePin = FallbackReturnNode->FindPin(UEdGraphSchema_K2::PN_ReturnValue, EGPD_Input);
		if (OriginalValuePin && ReturnValuePin) {
			ReturnValuePin->MakeLinkTo(OriginalValuePin);
		}
	}

	// Create call to the original function. Connect all parameters from the function entry
	UK2Node_CallFunction* OriginalFunctionCall{};
	{
		FGraphNodeCreator<UK2Node_CallFunction> OriginalFunctionCallCreator(*FunctionGraph);
		OriginalFunctionCall = OriginalFunctionCallCreator.CreateNode();

		// Set the original function as the call target
		OriginalFunctionCall->FunctionReference.SetSelfMember(StubGenerationData.InstanceFunctionName);

		// Finalize the node and place it after the previous node
		OriginalFunctionCall->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		OriginalFunctionCall->NodePosY = CurrentNodeInFunctionChain->NodePosY;
		OriginalFunctionCallCreator.Finalize();

		// Connect exec pin and self pin from the context retrieval function
		UEdGraphPin* FunctionCallSelfPin = OriginalFunctionCall->FindPinChecked(UEdGraphSchema_K2::PN_Self);
		OriginalFunctionCall->GetExecPin()->MakeLinkTo(ObjectInstanceValidThenPin);
		FunctionCallSelfPin->MakeLinkTo(CastedHookObjectInstancePin);
		CurrentNodeInFunctionChain = OriginalFunctionCall;

		// Connect world context to the self pin if world context pin is present
		UEdGraphPin* WorldContextPin = OriginalFunctionCall->FindPin(TEXT("__WorldContext"), EGPD_Input);
		if (WorldContextPin) {
			WorldContextPin->MakeLinkTo(CastedHookObjectInstancePin);
		}

		// Connect function inputs to the function entry node outputs
		for (UEdGraphPin* FunctionCallInputPin : OriginalFunctionCall->GetAllPins()) {
			if (FunctionCallInputPin->Direction == EGPD_Input && FunctionCallInputPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Exec &&
				FunctionCallInputPin != FunctionCallSelfPin && FunctionCallInputPin != WorldContextPin)
			{
				// We should be able to resolve the output pin with the same name on the function entry nod
				UEdGraphPin* FunctionEntryOutputPin = EntryNode->FindPin(FunctionCallInputPin->PinName, EGPD_Output);
				if (FunctionEntryOutputPin != nullptr) {
					FunctionEntryOutputPin->MakeLinkTo(FunctionCallInputPin);
				} else {
					MessageLog.Error(*LOCTEXT("InternalErrorCannotConnectFunctionInputPins", "Cannot connect Hook Function @@ pin @@ because that pin does not exist on the function argument list.").ToString(),
						StubGenerationData.FunctionEntry, FunctionCallInputPin);	
				}
			}
		}
	}

	// Create function exit node after successful hook call
	{
		FGraphNodeCreator<UK2Node_FunctionResult> FunctionReturnCreator(*FunctionGraph);
		UK2Node_FunctionResult* ReturnNode = FunctionReturnCreator.CreateNode();

		// Copy function reference from the original entry point
		ReturnNode->FunctionReference = StubGenerationData.FunctionEntry->FunctionReference;

		// Finally allocate the node pins and finish the creation process
		ReturnNode->NodePosX = CurrentNodeInFunctionChain->NodePosX + FMath::Max(CurrentNodeInFunctionChain->NodeWidth, AverageNodeWidth) + 256;
		ReturnNode->NodePosY = CurrentNodeInFunctionChain->NodePosY;
		FunctionReturnCreator.Finalize();

		// Copy user defined pins from the original function terminator if we have one
		if (StubGenerationData.FunctionResult && StubGenerationData.FunctionResult->IsEditable()) {
			for (const TSharedPtr<FUserPinInfo>& UserDefinedPin : StubGenerationData.FunctionResult->UserDefinedPins) {
				ReturnNode->CreatePinFromUserDefinition(MakeShared<FUserPinInfo>(*UserDefinedPin));
			}
		}

		// Connect function call then pin to the exec pin of the return node
		ReturnNode->GetExecPin()->MakeLinkTo(OriginalFunctionCall->GetThenPin());
		
		// Connect function outputs to the function return node inputs
		for (UEdGraphPin* ReturnNodeInputPin : ReturnNode->GetAllPins()) {
			if (ReturnNodeInputPin->Direction == EGPD_Input && ReturnNodeInputPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Exec) {
				// We should be able to resolve the output pin with the same name on the function call node
				UEdGraphPin* FunctionCallOutputPin = OriginalFunctionCall->FindPin(ReturnNodeInputPin->PinName, EGPD_Output);
				if (FunctionCallOutputPin != nullptr) {
					FunctionCallOutputPin->MakeLinkTo(ReturnNodeInputPin);
				} else {
					MessageLog.Error(*LOCTEXT("InternalErrorCannotConnectFunctionOutputPins", "Cannot connect Hook Function @@ pin @@ because that pin is not returned by the function call.").ToString(),
						StubGenerationData.FunctionEntry, ReturnNodeInputPin);	
				}
			}
		}
	}
	
	// Flag the function as private and static
	constexpr int32 ExtraFunctionFlags = FUNC_Private | FUNC_Static;
	K2Schema->AddExtraFunctionFlags(FunctionGraph, ExtraFunctionFlags);

	// Process the function graph we have created
	const int32 NewFunctionContextIndex = FunctionList.Num();
	ProcessOneFunctionGraph(FunctionGraph, true);

	// Save the mapping from the original function name to the new function context
	if (FunctionList.IsValidIndex(NewFunctionContextIndex)) {
		InstanceHookFunctionToSyntheticStaticFunctionContext.Add(StubGenerationData.InstanceFunctionName, &FunctionList[NewFunctionContextIndex]);
	}
}

void FHookBlueprintCompilerContext::CreateClassVariablesFromBlueprint() {
	FKismetCompilerContext::CreateClassVariablesFromBlueprint();

	// Create overlay component tree defined variables that will be populated once overlay component tree is evaluated
	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint);
	if (HookBlueprint && HookBlueprint->MixinTargetClass && HookBlueprint->OverlayComponentTree) {
		for (const UBlueprintMixinComponentNode* ComponentNode : HookBlueprint->OverlayComponentTree->AllNodes) {
			if (ComponentNode && ComponentNode->ComponentClass != nullptr && ComponentNode->ComponentVariableName != NAME_None) {
				
				// Create the variable name on the class scope
				const FEdGraphPinType Type(UEdGraphSchema_K2::PC_Object, NAME_None, ComponentNode->ComponentClass, EPinContainerType::None, false, FEdGraphTerminalType());
				if (FProperty* NewProperty = CreateVariable(ComponentNode->ComponentVariableName, Type)) {
					const FText CategoryName = FText::FromString(Blueprint->GetName());
					NewProperty->SetMetaData(TEXT("Category"), *CategoryName.ToString());
					NewProperty->SetPropertyFlags(CPF_BlueprintVisible | CPF_NonTransactional);
				}
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
		if (UObject* DerivedDataRoot = HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot) {
			const FString TransientDerivedDataNameString = FString::Printf(TEXT("TRASH_%s_%s"), *HookBlueprintGeneratedClass->GetName(), *DerivedDataRoot->GetName());
			const FName TransientDerivedDataName = MakeUniqueObjectName(GetTransientPackage(), DerivedDataRoot->GetClass(), FName(*TransientDerivedDataNameString));
			DerivedDataRoot->Rename(*TransientDerivedDataName.ToString(), GetTransientPackage(), RenFlags);
			FLinkerLoad::InvalidateExport(DerivedDataRoot);
		}

		// Clear reference to derived data and void hook descriptors
		HookBlueprintGeneratedClass->HookDescriptors.Empty();
		HookBlueprintGeneratedClass->HookDescriptorDerivedDataRoot = nullptr;
	}

	// If this blueprint is a mixin (e.g. not a function library), its instances can only be created within the mixin target class. This way we can ensure consistent way to access the data of the class we are mixing into
	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint);
	if (HookBlueprint && HookBlueprint->MixinTargetClass && HookBlueprint->BlueprintType != BPTYPE_FunctionLibrary) {
		ClassToClean->ClassWithin = HookBlueprint->MixinTargetClass;
	}
}

void FHookBlueprintCompilerContext::SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& SubObjectsToSave, UBlueprintGeneratedClass* ClassToClean) {
	FKismetCompilerContext::SaveSubObjectsFromCleanAndSanitizeClass(SubObjectsToSave, ClassToClean);

	// Since overlay component tree lives on the BPGC instance, we need to make sure it survives the cleaning of the class
	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint);
	if (HookBlueprint && HookBlueprint->OverlayComponentTree) {
		SubObjectsToSave.AddObject(HookBlueprint->OverlayComponentTree);

		// Save all nodes of the overlay component tree as well
		for (const UBlueprintMixinComponentNode* ComponentNode : HookBlueprint->OverlayComponentTree->AllNodes) {
			SubObjectsToSave.AddObject(ComponentNode);
			if (const UActorComponent* ComponentTemplate = ComponentNode->ComponentTemplate) {
				SubObjectsToSave.AddObject(ComponentTemplate);
			}
		}
	}
}

void FHookBlueprintCompilerContext::FinishCompilingClass(UClass* Class) {
	FKismetCompilerContext::FinishCompilingClass(Class);

	// Compile hook graph now that we have function signatures and objects
	if (bIsFullCompile && SourceHookTargetGraph) {
		CompileHookTargetGraph();
	}

	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint);
	UHookBlueprintGeneratedClass* HookBlueprintGeneratedClass = Cast<UHookBlueprintGeneratedClass>(TargetClass);

	// Copy data from the blueprint to the generated class
	if (HookBlueprint != nullptr && HookBlueprintGeneratedClass != nullptr) {
		HookBlueprintGeneratedClass->MixinTargetClass = HookBlueprint->MixinTargetClass;
		HookBlueprintGeneratedClass->OverlayComponentTree = HookBlueprint->OverlayComponentTree;
	}
}

void FHookBlueprintCompilerContext::SpawnNewClass(const FString& NewClassName) {
	// First, attempt to find the class, in case it hasn't been serialized in yet
	NewClass = FindObject<UHookBlueprintGeneratedClass>(Blueprint->GetOutermost(), *NewClassName);
	if (NewClass == nullptr)
	{
		// If the class hasn't been found, then spawn a new one
		NewClass = NewObject<UHookBlueprintGeneratedClass>(Blueprint->GetOutermost(), FName(*NewClassName), RF_Public | RF_Transactional);
		// TODO: This is not good enough, overlay component tree and hook graph will not be populated here
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

		// Replace instance hook function with generated static function
		if (ResultHookDefinition.HookFunction && InstanceHookFunctionToSyntheticStaticFunctionContext.Contains(ResultHookDefinition.HookFunction->GetFName())) {
			const FKismetFunctionContext* StaticFunctionContext = InstanceHookFunctionToSyntheticStaticFunctionContext.FindChecked(ResultHookDefinition.HookFunction->GetFName());
			ResultHookDefinition.HookFunction = StaticFunctionContext->Function;
		}
		
		// Only add the definition to the list if it is actually valid
		if (ResultHookDefinition.HookFunction != nullptr && ResultHookDefinition.TargetFunction != nullptr && ResultHookDefinition.TargetSpecifier != nullptr) {
			HookBlueprintGeneratedClass->HookDescriptors.Add(ResultHookDefinition);
			UniqueHookTargetClasses.Add(ResultHookDefinition.TargetFunction->GetOuterUClass());
		}
	}
}

#undef LOCTEXT_NAMESPACE
