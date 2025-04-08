#include "Nodes/HookTargetNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "Hooking/EdGraphSchema_HookTarget.h"
#include "GraphNodes/GraphNodeHookTarget.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/CompilerResultsLog.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

void UHookTargetNode::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const {
	Super::ValidateNodeDuringCompilation(MessageLog);

	// Check if we have any output connections. Root set nodes are always considered to have output connections
	bool bHasAnyOutputConnections = IsRootSetNode();
	for (const UEdGraphPin* GraphPin : Pins) {
		if (GraphPin && GraphPin->Direction == EGPD_Output && GraphPin->HasAnyConnections()) {
			bHasAnyOutputConnections = true;
		}
	}

	// Ensure that if we have an output connection, all of our input pins are actually connected as well (unless they are okay with default value)
	if (bHasAnyOutputConnections) {
		for (const UEdGraphPin* GraphPin : Pins) {
			if (GraphPin && GraphPin->Direction == EGPD_Input && GraphPin->bDefaultValueIsIgnored && !GraphPin->HasAnyConnections()) {
				MessageLog.Error(*LOCTEXT("HookTargetNode_DisconnectedInputPin", "Pin @@ of Node @@ is not connected, but does not have a default value.").ToString(), GraphPin, this);
			}
		}
	} else {
		// Just emit a warning that this node is not connected and is not a part of the root set
		MessageLog.Warning(*LOCTEXT("HookTargetNode_NoOutputConnections", "Node @@ does not have any output connections, and will have no effect.").ToString(), this);
	}
}

bool UHookTargetNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const {
	// Hook target nodes are only allowed to be created in the hook target graph schema
	return Schema && Schema->IsA<UEdGraphSchema_HookTarget>();
}

TSharedPtr<SGraphNode> UHookTargetNode::CreateVisualWidget() {
	return SNew(SGraphNodeHookTarget, this);
}

void UHookTargetNode::AutowireNewNode(UEdGraphPin* FromPin) {
	const UEdGraphSchema* GraphSchema = GetGraph()->GetSchema();
	TArray<UEdGraphPin*> PotentialAutoConnectPins;

	// Find all pins of this node with matching connection direction
	for (UEdGraphPin* ToPin : Pins) {
		if (ToPin && FromPin) {
			// If from pin is input, we need output pins, and vice versa
			if (FromPin->Direction == EGPD_Input && ToPin->Direction == EGPD_Output) {
				PotentialAutoConnectPins.Add(ToPin);
			} else if (FromPin->Direction == EGPD_Output && ToPin->Direction == EGPD_Input) {
				PotentialAutoConnectPins.Add(ToPin);
			}
		}
	}

	// Sort the pins before attempting to connect them
	PotentialAutoConnectPins.Sort([&](const UEdGraphPin& A, const UEdGraphPin& B) {
		// If one of the pins has the direct name match with the "from" pin, prefer that pin
		if (A.PinName == FromPin->PinName || B.PinName == FromPin->PinName) {
			return A.PinName == FromPin->PinName;
		}
		// Sort lexicographically otherwise
		return A.GetDisplayName().CompareToCaseIgnored(B.GetDisplayName()) < 0;
	});

	// Attempt to connect first matching pin
	for (UEdGraphPin* PotentialToPin : PotentialAutoConnectPins) {
		if (GraphSchema && GraphSchema->ArePinsCompatible(FromPin, PotentialToPin, GetBlueprintClassFromNode())) {
			// Break once we make the first connection
			if (GraphSchema->TryCreateConnection(FromPin, PotentialToPin)) {
				break;
			}
		}
	}
}

void UHookTargetNode::PrepareForCompilation(FCompilerResultsLog& MessageLog, UEdGraph* InSourceGraph) {
	// Nothing to do here, subclasses can override it to perform additional validation and expansion
}

UObject* UHookTargetNode::CompileOutput(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* OutputPin) {
	// Subclasses have to override this function if they have output pins
	if (!IsRootSetNode()) {
		MessageLog.Error(*LOCTEXT("HooKTargetNode_CompileNotImplemented", "Node @@ does not implement CompileOutput, but has connected Output pins").ToString(), this);	
	} else {
		// This function must never be called for root set nodes, they must use CompileRoot instead
		MessageLog.Error(*LOCTEXT("HooKTargetNode_CompileOnRootNode", "Node @@ is a Root node, but CompileOutput has been called on it. Root nodes are not allowed to have Output pins.").ToString(), this);	
	}
	return nullptr;
}

UClass* UHookTargetNode::GetBlueprintClassFromNode() const {
	// Prefer skeleton class since we will not generally have a function
	if (const UBlueprint* OwnerBlueprint = FBlueprintEditorUtils::FindBlueprintForNode(this)) {
		return OwnerBlueprint->SkeletonGeneratedClass ? OwnerBlueprint->SkeletonGeneratedClass : OwnerBlueprint->GeneratedClass;
	}
	return nullptr;
}

UObject* UHookTargetNode::EvaluateNodeInputPin(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* InputPin, UClass* ExpectedObjectClass) const {
	// Attempt to evalaute a pin connection first
	for (const UEdGraphPin* ConnectedOutputPin : InputPin->LinkedTo) {
		if (ConnectedOutputPin && ConnectedOutputPin->Direction == EGPD_Output) {
			if (UHookTargetNode* HookTargetNode = Cast<UHookTargetNode>(ConnectedOutputPin->GetOwningNode())) {
				UObject* CompilationOutput = HookTargetNode->CompileOutput(MessageLog, SelfClass, DerivedDataOuter, ConnectedOutputPin);

				// Check that we have compiled successfully
				if (CompilationOutput == nullptr) {
					MessageLog.Error(*LOCTEXT("HookTargetNode_ConnectedNodeFailed", "Node @@ cannot be compiled because its dependency node @@ did not compile successfully").ToString(), this, HookTargetNode);
					return nullptr;
				}
				// Check that the type of the object matches the expected type
				if (ExpectedObjectClass && !CompilationOutput->IsA(ExpectedObjectClass)) {
					MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNode_ConnectedNodeInvalid", "Node @@ cannot be compiled because its dependency node @@ produced object of type {0}, but expected object type was {1}"),
						FText::FromString(CompilationOutput->GetClass()->GetPathName()), FText::FromString(ExpectedObjectClass->GetPathName())).ToString(),
						this, HookTargetNode);
					return nullptr;
				}
				return CompilationOutput;
			}
		} 
	}

	// If we have a default value of the correct type, use that
	if (InputPin->DefaultObject && InputPin->DefaultObject->IsA(ExpectedObjectClass)) {
		return InputPin->DefaultObject;
	}

	// We do not have a default value or a connected pin
	MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNode_NoPinConnection", "Node @@ does not have Input Pin {0} connected."), InputPin->GetDisplayName()).ToString(), this);
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
