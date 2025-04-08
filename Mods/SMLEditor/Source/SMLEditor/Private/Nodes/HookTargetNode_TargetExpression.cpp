#include "Nodes/HookTargetNode_TargetExpression.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphSchema.h"
#include "Engine/Engine.h"
#include "Hooking/EdGraphSchema_HookTarget.h"
#include "Nodes/HookTargetNode_Root.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

void UHookTargetNode_TargetExpression::ReconstructNode() {
	Super::ReconstructNode();

	// Re-create target specific data. This will also handle re-connecting pins and re-generating inputs
	if (TargetSpecifierClass != nullptr) {
		Modify();
		CreateTargetClassSpecificData();
	}
}

void UHookTargetNode_TargetExpression::AllocateDefaultPins() {
	Super::AllocateDefaultPins();

	// Create outpin pin
	CreatePin(EGPD_Output, UEdGraphSchema_HookTarget::PC_HookTargetExpression, UEdGraphSchema_HookTarget::PN_TargetExpression);

	// Create data based on the target specifier
	if (TargetSpecifierClass != nullptr) {
		CreateTargetClassSpecificData();
	}
}

void UHookTargetNode_TargetExpression::GetMemberReferenceDescriptors(TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberReferenceDescriptors) const {
	OutMemberReferenceDescriptors.Append(GeneratedMemberReferenceDescriptors);
}

FMemberReference UHookTargetNode_TargetExpression::GetMemberReferenceByName(const FName& Name) const {
	if (const FMemberReference* MemberReference = MemberReferences.Find(Name)) {
		return *MemberReference;
	}
	return FMemberReference();
}

bool UHookTargetNode_TargetExpression::SetMemberReferenceByName(const FName& Name, const FMemberReference& NewMemberReference) {
	if (FMemberReference* MemberReference = MemberReferences.Find(Name)) {
		Modify();
		*MemberReference = NewMemberReference;
		if (GetGraph()) {
			GetGraph()->NotifyNodeChanged(this);
		}
		return true;
	}
	return false;
}

FLinearColor UHookTargetNode_TargetExpression::GetNodeTitleColor() const {
	return FLinearColor::Blue;
}

FText UHookTargetNode_TargetExpression::GetNodeTitle(ENodeTitleType::Type TitleType) const {
	if (TargetSpecifierClass != nullptr) {
		return TargetSpecifierClass.GetDefaultObject()->GetTargetSpecifierTitle();
	}
	return LOCTEXT("HookTargetNodeTargetExpression_InvalidName", "Invalid Target Expression");
}

FText UHookTargetNode_TargetExpression::GetTooltipText() const {
	if (TargetSpecifierClass != nullptr) {
		return TargetSpecifierClass.GetDefaultObject()->GetTargetSpecifierDescription();
	}
	return LOCTEXT("HookTargetNodeTargetExpression_InvalidDescription", "Please remove this target expression node as it does not have valid data.");
}

void UHookTargetNode_TargetExpression::GetMenuEntries(FGraphContextMenuBuilder& ContextMenuBuilder) const {
	TArray<UClass*> TargetSpecifierClasses;
	GetDerivedClasses(UBlueprintHookTargetSpecifier::StaticClass(), TargetSpecifierClasses);

	for (UClass* SpecifierClass : TargetSpecifierClasses) {
		// Skip abstract and non-native classes
		if (SpecifierClass->HasAnyClassFlags(CLASS_Abstract) || !SpecifierClass->IsNative()) continue;

		// Skip classes with no valid CDO or classes that do not wish to have an auto-generated node spawner created
		const UBlueprintHookTargetSpecifier* TargetSpecifierCDO = Cast<UBlueprintHookTargetSpecifier>(SpecifierClass->GetDefaultObject());
		if (TargetSpecifierCDO == nullptr || !TargetSpecifierCDO->ShouldCreateNodeSpawnerForTargetSpecifier()) continue;

		const TSharedPtr<FEdGraphSchemaAction_NewHookTargetNode> NodePlacementAction = MakeShared<FEdGraphSchemaAction_NewHookTargetNode>(
			LOCTEXT("HookTargetNodeTargetExpression_Category", "Target Specifiers"),
			TargetSpecifierCDO->GetTargetSpecifierTitle(),
			TargetSpecifierCDO->GetTargetSpecifierDescription(), 0);

		// Create the node template and set the target specifier class on it
		UHookTargetNode_TargetExpression* NodeTemplate = ContextMenuBuilder.CreateTemplateNode<UHookTargetNode_TargetExpression>();
		NodeTemplate->TargetSpecifierClass = SpecifierClass;
		NodePlacementAction->NodeTemplate = NodeTemplate;

		if (NodePlacementAction->IsNodeActionRelevantToTheGraphContext(ContextMenuBuilder)) {
			ContextMenuBuilder.AddAction(NodePlacementAction);
		}
	}
}

void UHookTargetNode_TargetExpression::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const {
	Super::ValidateNodeDuringCompilation(MessageLog);

	// Check for valid target specifier class
	if (TargetSpecifierClass == nullptr || TargetSpecifierClass->HasAnyClassFlags(CLASS_Abstract)) {
		MessageLog.Error(*LOCTEXT("HookTargetNodeTargetExpression_InvalidNodeNoClass", "Node @@ is corrupted and needs to be removed.").ToString(), this);
	}
	// Check for valid archetype of the correct class
	else if (TargetSpecifierArchetype == nullptr || TargetSpecifierArchetype->GetClass() != TargetSpecifierClass) {
		MessageLog.Error(*LOCTEXT("HookTargetNodeTargetExpression_InvalidNodeArchetype", "Node @@ is outdated or misconfigured. Please refresh or remove it.").ToString(), this);
	}
	// Give archetype a chance to perform validation of the provided parameters
	else {
		FText ValidationErrorMessage;
		if (!TargetSpecifierArchetype->ValidateTargetSpecifierConfiguration(ValidationErrorMessage)) {
			MessageLog.Error(*LOCTEXT("HookTargetNodeTargetExpression_ValidationFailed", "Node @@ is not configured correctly: {}").ToString(), this, *ValidationErrorMessage.ToString());
		}
	}
	// TODO: Mark connected but unreferenced pins as orphan
}

UObject* UHookTargetNode_TargetExpression::CompileOutput(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* OutputPin) {
	// Validate the integrity of the data on the node first. ValidateNodeDuringCompilation will give a better error description
	if (TargetSpecifierClass == nullptr || TargetSpecifierArchetype == nullptr || TargetSpecifierArchetype->GetClass() != TargetSpecifierClass) {
		MessageLog.Error(*LOCTEXT("HookTargetNodeTargetExpression_CodeGenerationFailed", "Node @@ cannot be compiled because it is outdated or corrupted.").ToString(), this);
		return nullptr;
	}
	// Create target specifier from the provided archetype
	UBlueprintHookTargetSpecifier* TargetSpecifier = NewObject<UBlueprintHookTargetSpecifier>(DerivedDataOuter, TargetSpecifierClass, NAME_None, RF_NoFlags, TargetSpecifierArchetype);

	// Generate fresh data for the node class rather than relying on the existing data
	TArray<FHookTargetNodeMemberReferenceDescriptor> MemberReferenceDescriptors;
	TArray<TPair<FName, UClass*>> PinDescriptors;
	GenerateMemberReferencesAndPinsForClass(TargetSpecifierClass, MemberReferenceDescriptors, PinDescriptors);

	// Evaluated generated member reference descriptors first
	for (const FHookTargetNodeMemberReferenceDescriptor& MemberDescriptor : MemberReferenceDescriptors) {
		const FMemberReference* MemberReference = MemberReferences.Find(MemberDescriptor.Name);

		// Make sure we actually have a valid member reference pointer
		if (MemberReference == nullptr) {
			MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeTargetExpression_NoMemberReference", "No Member Reference data for Member Reference Descriptor {0} on Node @@. Please refresh the node."),
				FText::FromName(MemberDescriptor.Name)).ToString(), this);
			continue;
		}
		// Resolve up-to-date reference to the member
		FMemberReference ResolvedMemberReference;

		// Resolve as FProperty reference
		if (EnumHasAnyFlags(MemberDescriptor.Flags, EHTNMemberRefFlags::PropertyReference)) {
			const FProperty* ResolvedPropertyReference = MemberReference->ResolveMember<FProperty>(SelfClass);
	
			// Validate that we have actually managed to resolve the member reference
			if (ResolvedPropertyReference == nullptr) {
				MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeTargetExpression_NoPropertyReference", "Failed to resolve Member Reference to Property {0} in Scope {1} on Node @@"),
					FText::FromName(MemberReference->GetMemberName()), FText::FromString(*GetPathNameSafe(MemberReference->GetScope(SelfClass)))).ToString(), this);
				continue;
			}
			ResolvedMemberReference.SetFromField<FProperty>(ResolvedPropertyReference, SelfClass);
		} else {
			// Resolve as UFunction reference
			const UFunction* ResolvedFunctionReference = MemberReference->ResolveMember<UFunction>(SelfClass);
	
			// Validate that we have actually managed to resolve the member reference
			if (ResolvedFunctionReference == nullptr) {
				MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeTargetExpression_NoFunctionReference", "Failed to resolve Member Reference to Function {0} in Scope {1} on Node @@"),
					FText::FromName(MemberReference->GetMemberName()), FText::FromString(*GetPathNameSafe(MemberReference->GetScope(SelfClass)))).ToString(), this);
				continue;
			}
			ResolvedMemberReference.SetFromField<UFunction>(ResolvedFunctionReference, SelfClass);
		}

		// Ensure that the struct property we are writing to is still valid
		const FStructProperty* TargetMemberProperty = FindFProperty<FStructProperty>(TargetSpecifierClass, MemberDescriptor.Name);
		if (TargetMemberProperty == nullptr || TargetMemberProperty->Struct != FMemberReference::StaticStruct()) {
			MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeTargetExpression_OutdatedMemberReference", "Member Reference {0} on Node @@ is no longer present on the Node Type. Please refresh the node."),
					FText::FromName(MemberDescriptor.Name)).ToString(), this);
			continue;
		}
		
		// Write the resolved member reference into the property
		FMemberReference* OutMemberReferencePtr = TargetMemberProperty->ContainerPtrToValuePtr<FMemberReference>(TargetSpecifier);
		*OutMemberReferencePtr = ResolvedMemberReference;
	}

	// Evaluate generated pins now
	const UEdGraphSchema_HookTarget* HookTargetGraphSchema = Cast<UEdGraphSchema_HookTarget>(GetSchema());
	for (const TPair<FName, UClass*>& PinDescriptor : PinDescriptors) {
		const UEdGraphPin* GeneratedPin = FindPin(PinDescriptor.Key, EGPD_Input);
		const FName GeneratedPinExpectedCategory = HookTargetGraphSchema->CreatePinCategoryForObjectClass(PinDescriptor.Value);

		// Make sure the generated pin exists and its type matches the expected type
		if (GeneratedPin == nullptr || GeneratedPin->PinType.PinCategory != GeneratedPinExpectedCategory) {
			MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeTargetExpression_NoGeneratedPropertyPin", "Property Pin {0} not found on Node @@. Please refresh the node."), FText::FromName(PinDescriptor.Key)).ToString(), this);
			continue;
		}

		// Make sure the generated pin property is still valid
		const FObjectProperty* ObjectProperty = FindFProperty<FObjectProperty>(TargetSpecifierClass, PinDescriptor.Key);
		if (ObjectProperty == nullptr || ObjectProperty->PropertyClass == nullptr) {
			MessageLog.Error(*LOCTEXT("HookTargetNodeTargetExpression_NoGeneratedProperty", "Property Pin @@ on Node @@ does not have a valid origin property. Please refresh the node.").ToString(), GeneratedPin, this);
			continue;
		}

		// Evaluate the pin and set the value on the object property
		UObject* EvalutedPinValue = EvaluateNodeInputPin(MessageLog, SelfClass, DerivedDataOuter, GeneratedPin, ObjectProperty->PropertyClass);
		ObjectProperty->SetObjectPropertyValue_InContainer(TargetSpecifier, EvalutedPinValue);
	}
	
	return TargetSpecifier;
}

void UHookTargetNode_TargetExpression::CreateTargetClassSpecificData() {
	// We cannot fix a node that does not have a valid class type
	if (TargetSpecifierClass == nullptr) {
		return;
	}
	
	// Thrash existing archetype
	if (TargetSpecifierArchetype) {
		TargetSpecifierArchetype->Rename(nullptr, GetTransientPackage(), REN_ForceNoResetLoaders);
		TargetSpecifierArchetype->MarkAsGarbage();
	}
	TMap<FName, UEdGraphPin*> OldPinNameToConnectedPin;

	// Remove all pins that have been generated from property names
	for (const FName& GeneratedPinName : GeneratedPropertyPinNames) {
		if (UEdGraphPin* GeneratedPin = FindPin(GeneratedPinName, EGPD_Input)) {

			// Break all links from this pin if we have a valid graph and pin connections
			if (GetGraph() != nullptr && !GeneratedPin->LinkedTo.IsEmpty()) {
				OldPinNameToConnectedPin.Add(GeneratedPinName, GeneratedPin->LinkedTo[0]);
				GeneratedPin->BreakAllPinLinks(true);
			}
			RemovePin(GeneratedPin);
		}
	}

	// Copy old member references and archetype object to salvege as much data as possible from the old node layout
	const TMap<FName, FMemberReference> OldMemberReferences = MemberReferences;
	UObject* OldArchetypeObject = TargetSpecifierArchetype;

	// Cleanup generated data on the node
	GeneratedMemberReferenceDescriptors.Empty();
	GeneratedPropertyPinNames.Empty();
	MemberReferences.Empty();
	TargetSpecifierArchetype = nullptr;

	// Create fresh archetype object
	TargetSpecifierArchetype = NewObject<UBlueprintHookTargetSpecifier>(this, TargetSpecifierClass, TEXT("TargetSpecifierArchetype"), RF_Transactional);

	// Attempt to carry over as much data as possible from the old archetype
	if (OldArchetypeObject && TargetSpecifierArchetype) {
		GEngine->CopyPropertiesForUnrelatedObjects(OldArchetypeObject, TargetSpecifierArchetype);
	}

	// Create derived data from the class properties
	TArray<FHookTargetNodeMemberReferenceDescriptor> NewMemberReferenceDescriptors;
	TArray<TPair<FName, UClass*>> NewPinDescriptors;
	GenerateMemberReferencesAndPinsForClass(TargetSpecifierClass, NewMemberReferenceDescriptors, NewPinDescriptors);

	// Generate member descriptors from class properties
	for (const FHookTargetNodeMemberReferenceDescriptor& Descriptor : NewMemberReferenceDescriptors) {
		GeneratedMemberReferenceDescriptors.Add(Descriptor);

		// Check if we can reuse existing member reference
		const FMemberReference* ExistingMemberReference = OldMemberReferences.Find(Descriptor.Name);
		const bool bCanReuseMemberReference = ExistingMemberReference && ExistingMemberReference->GetMemberName() != NAME_None &&
			(!EnumHasAnyFlags(Descriptor.Flags, EHTNMemberRefFlags::SelfContext) || ExistingMemberReference->IsSelfContext());
		MemberReferences.Add(Descriptor.Name, bCanReuseMemberReference ? *ExistingMemberReference : FMemberReference());
	}

	const UEdGraphSchema_HookTarget* GraphSchema = Cast<UEdGraphSchema_HookTarget>(GetGraph()) ? Cast<UEdGraphSchema_HookTarget>(GetGraph()) : GetDefault<UEdGraphSchema_HookTarget>();
	TArray<UEdGraphPin*> GeneratedInputPins;

	// Generate pins from class properties
	for (const TPair<FName, UClass*>& PinDescriptor : NewPinDescriptors) {
		if (PinDescriptor.Value && GraphSchema) {
			const FName PinCategoryFromClass = GraphSchema->CreatePinCategoryForObjectClass(PinDescriptor.Value);
			if (PinCategoryFromClass != NAME_None && FindPin(PinDescriptor.Key) == nullptr) {
				UEdGraphPin* GeneratedPin = CreatePin(EGPD_Input, PinCategoryFromClass, PinDescriptor.Key);
				GeneratedPropertyPinNames.Add(GeneratedPin->PinName);
				GeneratedInputPins.Add(GeneratedPin);
			}
		}
	}
	
	if (GetGraph() != nullptr) {
		// Attempt to re-connect pins
		for (UEdGraphPin* GeneratedInputPin : GeneratedInputPins) {
			if (GraphSchema && GeneratedInputPin && OldPinNameToConnectedPin.Contains(GeneratedInputPin->PinName)) {
				UEdGraphPin* ConnectedOutputPin = OldPinNameToConnectedPin.FindChecked(GeneratedInputPin->PinName);

				if (ConnectedOutputPin && GraphSchema->ArePinsCompatible(GeneratedInputPin, ConnectedOutputPin)) {
					GraphSchema->TryCreateConnection(GeneratedInputPin, ConnectedOutputPin);
				}
			}
		}

		// Notify the graph that this node has been changed
		GetGraph()->NotifyNodeChanged(this);
	}
}

void UHookTargetNode_TargetExpression::GenerateMemberReferencesAndPinsForClass(const UClass* InClass, TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberDescriptors, TArray<TPair<FName, UClass*>>& OutPinDescriptors) {
	for (TFieldIterator<FProperty> PropIt(InClass, EFieldIterationFlags::IncludeSuper); PropIt; ++PropIt) {
		const FProperty* Property = *PropIt;

		// Handle HookMemberReference properties that point to members
		if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property)) {
			if (StructProperty->Struct == FMemberReference::StaticStruct() && Property->HasMetaData(UEdGraphSchema_HookTarget::MD_HookMemberReference)) {
				OutMemberDescriptors.Add(CreateMemberReferenceDescriptorFromProperty(Property));
			}		
		}
		
		// Handle HookGraphPin properties that generate pins
		if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property)) {
			if (ObjectProperty->PropertyClass != nullptr && ObjectProperty->HasMetaData(UEdGraphSchema_HookTarget::MD_HookGraphPin)) {
				OutPinDescriptors.Add({ObjectProperty->GetFName(), ObjectProperty->PropertyClass});
			}
		}
	}
}

FHookTargetNodeMemberReferenceDescriptor UHookTargetNode_TargetExpression::CreateMemberReferenceDescriptorFromProperty(const FProperty* InSourceProperty) {
	// Construct member reference descriptor
	FHookTargetNodeMemberReferenceDescriptor MemberReferenceDescriptor;
	MemberReferenceDescriptor.Name = InSourceProperty->GetFName();
	MemberReferenceDescriptor.DisplayName = InSourceProperty->GetDisplayNameText();

	// Determine if we only want self context
	if (InSourceProperty->HasMetaData(UEdGraphSchema_HookTarget::MD_HookSelfContextOnly)) {
		MemberReferenceDescriptor.Flags |= EHTNMemberRefFlags::SelfContext;
	}
	// Determine if it is a function or a field reference
	if (InSourceProperty->HasMetaData(UEdGraphSchema_HookTarget::MD_HookPropertyReference)) {
		MemberReferenceDescriptor.Flags |= EHTNMemberRefFlags::PropertyReference;
	}
	// Filter functions with script only if requested
	if (InSourceProperty->HasMetaData(UEdGraphSchema_HookTarget::MD_HookAllowFunctionsWithScriptOnly)) {
		MemberReferenceDescriptor.Flags |= EHTNMemberRefFlags::FunctionsWithScriptOnly;
	}
	return MemberReferenceDescriptor;
}

#undef LOCTEXT_NAMESPACE
