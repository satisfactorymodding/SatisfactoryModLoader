#include "Hooking/EdGraphSchema_HookTarget.h"
#include "EdGraphUtilities.h"
#include "ScopedTransaction.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "EdGraph/EdGraph.h"
#include "Hooking/HookBlueprintEditor.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Patching/BlueprintHookBlueprint.h"
#include "Settings/EditorStyleSettings.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

const FName UEdGraphSchema_HookTarget::PC_HookTargetExpression(TEXT("HookTargetExpression"));
const FName UEdGraphSchema_HookTarget::PN_TargetExpression(TEXT("TargetExpression"));
const FName UEdGraphSchema_HookTarget::MD_HookMemberReference(TEXT("MemberReference"));
const FName UEdGraphSchema_HookTarget::MD_HookGraphPin(TEXT("GraphPin"));
const FName UEdGraphSchema_HookTarget::MD_HookSelfContextOnly(TEXT("SelfContextOnly"));
const FName UEdGraphSchema_HookTarget::MD_HookAllowFunctionsWithScriptOnly(TEXT("ScriptOnly"));
const FName UEdGraphSchema_HookTarget::MD_HookPropertyReference(TEXT("PropertyReference"));

UEdGraphNode* FEdGraphSchemaAction_NewHookTargetNode::PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode) {
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "K2_AddNode", "Add Node"));

	// Mark all the objects that are going to be involved in the transaction as modified to save their state
	ParentGraph->Modify();
	for(UEdGraphPin* FromPin : FromPins) {
		if (FromPin != nullptr) {
			FromPin->Modify();
		}
	}
	
	// Smart pointer that handles fixup after potential node reconstruction
	FWeakGraphPinPtr FromPinPtr = FromPins.Num() > 0 ? FromPins[0] : nullptr;

	// Duplicate template node to create new node, and make sure that the node is marked as transactional, even if the template was not
	UEdGraphNode* ResultNode = DuplicateObject<UEdGraphNode>(NodeTemplate, ParentGraph);
	if (ParentGraph->HasAnyFlags(RF_Transactional)) {
		ResultNode->SetFlags(RF_Transactional);
	}

	// Add the node to the graph, run placement logic and allocate default pins for it
	ParentGraph->AddNode(ResultNode, true, bSelectNewNode);

	ResultNode->CreateNewGuid();
	ResultNode->PostPlacedNewNode();
	ResultNode->AllocateDefaultPins();

	// Push the newly spawned node away from the node that we are running a connection from
	int32 XLocation = static_cast<int32>(Location.X);
	if (FromPinPtr.IsValid() && FromPinPtr->Direction == EGPD_Input) {
		const UEdGraphNode* PinNode = FromPinPtr->GetOwningNode();
		const double XDelta = FMath::Abs(PinNode->NodePosX - Location.X);

		constexpr int32 NodeDistance = 60;
		if (XDelta < NodeDistance) {
			XLocation = PinNode->NodePosX - NodeDistance;
		}
	}
	ResultNode->NodePosX = XLocation;
	ResultNode->NodePosY = static_cast<int32>(Location.Y);

	// Snap the resulting node position to the grid
	ResultNode->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);

	// Connect the pins to the newly created node
	for (UEdGraphPin* FromPin : FromPins) {
		ResultNode->AutowireNewNode(FromPin);
	}

	// Mark the owner blueprint directly
	if (UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(ParentGraph)) {
		FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
	}

	// Clear any error messages that could be present on the node
	ResultNode->ErrorMsg.Empty();
	ResultNode->bHasCompilerMessage = false;

	return ResultNode;
}

UEdGraphNode* FEdGraphSchemaAction_NewHookTargetNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) {
	TArray<UEdGraphPin*> FromPinsList{FromPin};
	return FEdGraphSchemaAction_NewHookTargetNode::PerformAction(ParentGraph, FromPinsList, Location, bSelectNewNode);
}

void FEdGraphSchemaAction_NewHookTargetNode::AddReferencedObjects(FReferenceCollector& Collector) {
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddStableReference(&NodeTemplate);
}

bool FEdGraphSchemaAction_NewHookTargetNode::IsNodeActionRelevantToTheGraphContext(const FGraphContextMenuBuilder& ContextMenuBuilder) const {
	// When we are not dragging the connection out of the existing pin, all node actions are relevant
	if (ContextMenuBuilder.FromPin == nullptr) {
		return true;
	}

	// Allocate a temporary, so we can check its default pins to evaluate whenever it is relevant to the context or not
	if (ContextMenuBuilder.CurrentGraph != nullptr && NodeTemplate != nullptr) {
		const UEdGraphSchema* CurrentGraphSchema = ContextMenuBuilder.CurrentGraph->GetSchema();
		UEdGraphNode* TemporaryPinContextNode = DuplicateObject<UEdGraphNode>(NodeTemplate, ContextMenuBuilder.OwnerOfTemporaries);
		TemporaryPinContextNode->AllocateDefaultPins();

		// If we have at least a single compatible pin, this node is relevant to the current context
		for (const UEdGraphPin* NodeGraphPin : TemporaryPinContextNode->Pins) {
			if (NodeGraphPin && CurrentGraphSchema && CurrentGraphSchema->ArePinsCompatible(NodeGraphPin, ContextMenuBuilder.FromPin)) {
				if ((NodeGraphPin->Direction == EGPD_Input && ContextMenuBuilder.FromPin->Direction == EGPD_Output) ||
					(NodeGraphPin->Direction == EGPD_Output && ContextMenuBuilder.FromPin->Direction == EGPD_Input)) {
					return true;
				}
			}
		}
	}
	// Node is not relevant to the current context otherwise
	return false;
}

UEdGraphNode* FEdGraphSchemaAction_NewHookComment::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) {
	const UHookBlueprint* OwnerBlueprint = Cast<UHookBlueprint>(FBlueprintEditorUtils::FindBlueprintForGraph(ParentGraph));
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = FHookBlueprintEditor::FindEditorForHookBlueprint(OwnerBlueprint);
	
	UEdGraphNode_Comment* CommentTemplate = NewObject<UEdGraphNode_Comment>();
	FVector2D SpawnLocation = Location;

	FSlateRect SelectionBounds{};
	if (BlueprintEditor && BlueprintEditor->GetBoundsForSelectedNodes(SelectionBounds, 50.0f)) {
		CommentTemplate->SetBounds(SelectionBounds);
		SpawnLocation.X = CommentTemplate->NodePosX;
		SpawnLocation.Y = CommentTemplate->NodePosY;
	}
	return FEdGraphSchemaAction_NewNode::SpawnNodeFromTemplate<UEdGraphNode_Comment>(ParentGraph, CommentTemplate, SpawnLocation);
}

void UEdGraphSchema_HookTarget::CreateDefaultNodesForGraph(UEdGraph& Graph) const {
}

const FPinConnectionResponse UEdGraphSchema_HookTarget::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const {
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode()) {
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionSameNode", "Both are on the same node"));
	}

	// Compare the directions
	const UEdGraphPin* InputPin = NULL;
	const UEdGraphPin* OutputPin = NULL;

	// Categorize pins by the input and output direction
	if (!CategorizePinsByDirection(A, B, InputPin, OutputPin)) {
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionIncompatible", "Directions are not compatible"));
	}

	// Check for new and existing loops
	if (ConnectionCausesLoop(InputPin, OutputPin)) {
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("ConnectionLoop", "Connection would cause loop"));
	}

	// Check for incompatible pins and get description if they cannot connect
	FText PinCompatibilityResponseMessage;
	if (!ArePinsCompatible_Internal(InputPin, OutputPin, PinCompatibilityResponseMessage)) {
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, PinCompatibilityResponseMessage);
	}

	// Break existing connections on input pin, but allow multiple connections on the output pin
	if (InputPin->LinkedTo.Num() > 0) {
		ECanCreateConnectionResponse ReplyBreakOutputs;
		if (InputPin == A)
		{
			ReplyBreakOutputs = CONNECT_RESPONSE_BREAK_OTHERS_A;
		}
		else
		{
			ReplyBreakOutputs = CONNECT_RESPONSE_BREAK_OTHERS_B;
		}
		return FPinConnectionResponse(ReplyBreakOutputs, LOCTEXT("ConnectionReplace", "Replace existing connections"));
	}

	// We are allowed to make a connection otherwise
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, FText::GetEmpty());
}

bool UEdGraphSchema_HookTarget::ArePinsCompatible_Internal(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin, FText& OutErrorMessage) const {
	// Pin types must be identical to be compatible
	return InputPin && OutputPin && InputPin->PinType == OutputPin->PinType;
}

FLinearColor UEdGraphSchema_HookTarget::GetPinTypeColor(const FEdGraphPinType& PinType) const {
	if (PinType.PinCategory == PC_HookTargetExpression) {
		return FLinearColor(0.2f, 0.75f, 1.0f);
	}
	return FLinearColor::White;
}

FName UEdGraphSchema_HookTarget::CreatePinCategoryForObjectClass(const UClass* ObjectClass) const {
	// Currently we only support hook target expression pins
	if (ObjectClass && ObjectClass->IsChildOf<UBlueprintHookTargetSpecifier>()) {
		return PC_HookTargetExpression;
	}
	return NAME_None;
}

bool UEdGraphSchema_HookTarget::PinCategorySupportsDefaultValue(const FName& PinCategory) const {
	return false;
}

FString UEdGraphSchema_HookTarget::IsPinDefaultValid(const UEdGraphPin* Pin, const FString& NewDefaultValue, TObjectPtr<UObject> NewDefaultObject, const FText& InNewDefaultText) const {
	if (Pin->bDefaultValueIsIgnored) {
		return TEXT("Pin definition does not allow providing a default value");
	}
	if (!PinCategorySupportsDefaultValue(Pin->PinType.PinCategory)) {
		return TEXT("Pin type does not support default values");
	}
	return TEXT("");
}

bool UEdGraphSchema_HookTarget::ShouldHidePinDefaultValue(UEdGraphPin* Pin) const {
	return Pin && (Pin->bDefaultValueIsIgnored || !PinCategorySupportsDefaultValue(Pin->PinType.PinCategory));
}

void UEdGraphSchema_HookTarget::GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const {
	Super::GetGraphDisplayInformation(Graph, DisplayInfo);
	const UHookBlueprint* OuterHookBlueprint = Graph.GetTypedOuter<UHookBlueprint>();

	// Handle hook target graph pretty name and description
	if (OuterHookBlueprint && OuterHookBlueprint->HookTargetGraph == &Graph) {
		DisplayInfo.DisplayName = LOCTEXT("HookTargetGraph_DisplayName", "Hook Graph");
		DisplayInfo.Tooltip = LOCTEXT("HookTargetGraph_Tooltip", "Hook Graph is a Data-driven Graph describing the application sites of Blueprint Hook functions");
	}
}

FText UEdGraphSchema_HookTarget::GetPinDisplayName(const UEdGraphPin* Pin) const {
	if(GIsEditor && GetDefault<UEditorStyleSettings>()->bShowFriendlyNames && Pin->bAllowFriendlyName) {
		return FText::FromString(FName::NameToDisplayString(Pin->PinName.ToString(), false));
	}
	return Super::GetPinDisplayName(Pin);
}

EGraphType UEdGraphSchema_HookTarget::GetGraphType(const UEdGraph* TestEdGraph) const {
	return GT_MAX; // neither of the K2 types provided. Like base class says, this function is K2 specific and generally does not make a lot of sense to have in UEdGraphSchema
}

FConnectionDrawingPolicy* UEdGraphSchema_HookTarget::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const {
	return new FHookTargetConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

void UEdGraphSchema_HookTarget::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const {
	// Create comment node
	if (!ContextMenuBuilder.FromPin) {
		const UHookBlueprint* OwnerBlueprint = Cast<UHookBlueprint>(FBlueprintEditorUtils::FindBlueprintForGraph(ContextMenuBuilder.CurrentGraph));
		const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = FHookBlueprintEditor::FindEditorForHookBlueprint(OwnerBlueprint);
		
		const bool bIsManyNodesSelected = BlueprintEditor && BlueprintEditor->GetNumberOfSelectedNodes() > 0;
		const FText CommentDesc = LOCTEXT("CommentDesc", "New Comment");
		const FText MultiCommentDesc = LOCTEXT("MultiCommentDesc", "Create Comment from Selection");
		const FText CommentToolTip = LOCTEXT("CommentToolTip", "Creates a comment.");
		const FText MenuDescription = bIsManyNodesSelected ? MultiCommentDesc : CommentDesc;
		const TSharedPtr<FEdGraphSchemaAction_NewHookComment> NewAction = MakeShared<FEdGraphSchemaAction_NewHookComment>(FText::GetEmpty(), MenuDescription, CommentToolTip, 0);
		ContextMenuBuilder.AddAction(NewAction);
	}
	Super::GetGraphContextActions(ContextMenuBuilder);
}

void UEdGraphSchema_HookTarget::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const {
	if (Context->Pin == nullptr && Context->Node != nullptr && !Context->Node->IsA<UEdGraphNode_Comment>()) {
		const FName SectionName = "EdGraphSchemaPinActions";
		FToolMenuSection& Section = Menu->FindOrAddSection(SectionName);
		
		Section.AddMenuEntry("RefreshNode", LOCTEXT("RefreshNode", "Refresh Node"), LOCTEXT("RefreshNodeTooltip", "Refresh this node."), FSlateIcon(),
			FUIAction(FExecuteAction::CreateUObject(const_cast<UEdGraphSchema_HookTarget*>(this), &UEdGraphSchema_HookTarget::RefreshNode, static_cast<UEdGraphNode*>(Context->Node))));
	}
	Super::GetContextMenuActions(Menu, Context);
}

void UEdGraphSchema_HookTarget::RefreshNode(UEdGraphNode* InGraphNode) {
	if (InGraphNode != nullptr) {
		const FScopedTransaction Transaction(LOCTEXT("HooKTargetRefreshNode", "Refresh Node"));
		InGraphNode->Modify();
		InGraphNode->ReconstructNode();
	}
}

bool UEdGraphSchema_HookTarget::ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const {
	TSet<const UEdGraphNode*> VisitedGraphNodes;
	TArray<const UEdGraphNode*> UnexploredDependencySet;

	if (OutputPin && OutputPin->GetOuter()) {
		UnexploredDependencySet.Add(OutputPin->GetOuter());
	}
	while (!UnexploredDependencySet.IsEmpty()) {
		// Pop the node and add it to the visited set
		const UEdGraphNode* UnvisitedNode = UnexploredDependencySet.Pop(false);
		VisitedGraphNodes.Add(UnvisitedNode);

		// Also explore any input connections that this node has
		for (const UEdGraphPin* NodePin : UnvisitedNode->GetAllPins()) {
			if (NodePin && NodePin->Direction == EGPD_Input) {
				for (const UEdGraphPin* ConnectedNodePin : NodePin->LinkedTo) {
					if (ConnectedNodePin && ConnectedNodePin->GetOuter() && !VisitedGraphNodes.Contains(ConnectedNodePin->GetOuter())) {
						VisitedGraphNodes.Add(ConnectedNodePin->GetOuter());
					}
				}
			}
		}
	}
	// The connection will cause a loop if input pin is in the visited graph node set
	return InputPin && VisitedGraphNodes.Contains(InputPin->GetOuter());
}

FHookTargetConnectionDrawingPolicy::FHookTargetConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor,
	const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, const UEdGraph* InGraph) :
	FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements) {

	Schema = Cast<UEdGraphSchema_HookTarget>(InGraph ? InGraph->GetSchema() : nullptr);
	ArrowImage = nullptr;
	ArrowRadius = FVector2D(0.0f);
}

void FHookTargetConnectionDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) {
	FConnectionDrawingPolicy::DetermineWiringStyle(OutputPin, InputPin, Params);

	if (HoveredPins.Contains(InputPin) && HoveredPins.Contains(OutputPin)) {
		Params.WireThickness = Params.WireThickness * 5;
	}

	if (Schema && OutputPin) {
		Params.WireColor = Schema->GetPinTypeColor(OutputPin->PinType);
	}

	if (OutputPin && InputPin) {
		if (OutputPin->bOrphanedPin || InputPin->bOrphanedPin) {
			Params.WireColor = FLinearColor::Red;
		}
	}
}

#undef LOCTEXT_NAMESPACE
