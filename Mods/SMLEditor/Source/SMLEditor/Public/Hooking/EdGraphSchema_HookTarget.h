#pragma once

#include "CoreMinimal.h"
#include "ConnectionDrawingPolicy.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_HookTarget.generated.h"

/** Action to add hook graph node to the graph and automatically connect its pins */
USTRUCT()
struct SMLEDITOR_API FEdGraphSchemaAction_NewHookTargetNode : public FEdGraphSchemaAction {
	GENERATED_BODY()

	// Simple type info
	static FName StaticGetTypeId() { static FName Type("FEdGraphSchemaAction_NewHookTargetNode"); return Type; }
	virtual FName GetTypeId() const override { return StaticGetTypeId(); } 

	/** Template of node we want to create */
	UPROPERTY()
	TObjectPtr<UEdGraphNode> NodeTemplate{};

	FEdGraphSchemaAction_NewHookTargetNode() = default;

	FEdGraphSchemaAction_NewHookTargetNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{}

	// Begin FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End FEdGraphSchemaAction interface

	/** Checks if this node action is relevant to the current graph context and, as such, whenever it should be registered */
	bool IsNodeActionRelevantToTheGraphContext(const FGraphContextMenuBuilder& ContextMenuBuilder) const;
};

/** Action to add hook graph node to the graph and automatically connect its pins */
USTRUCT()
struct SMLEDITOR_API FEdGraphSchemaAction_NewHookComment : public FEdGraphSchemaAction {
	GENERATED_BODY()

	// Simple type info
	static FName StaticGetTypeId() { static FName Type("FEdGraphSchemaAction_NewHookComment"); return Type; }
	virtual FName GetTypeId() const override { return StaticGetTypeId(); } 

	FEdGraphSchemaAction_NewHookComment() = default;

	FEdGraphSchemaAction_NewHookComment(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
	{}

	// Begin FEdGraphSchemaAction interface
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
	// End FEdGraphSchemaAction interface
};

UCLASS()
class SMLEDITOR_API UEdGraphSchema_HookTarget : public UEdGraphSchema {
	GENERATED_BODY()
public:
	static const FName PC_HookTargetExpression;
	static const FName PN_TargetExpression;
	static const FName MD_HookMemberReference;
	static const FName MD_HookGraphPin;
	static const FName MD_HookSelfContextOnly;
	static const FName MD_HookAllowFunctionsWithScriptOnly;
	static const FName MD_HookPropertyReference;
	
	// Begin UEdGraphSchema interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual FString IsPinDefaultValid(const UEdGraphPin* Pin, const FString& NewDefaultValue, TObjectPtr<UObject> NewDefaultObject, const FText& InNewDefaultText) const override;
	virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
	virtual bool ShouldAlwaysPurgeOnModification() const override { return false; }
	virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;
	virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;
	virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;
	virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	// End UEdGraphSchema interface

	/** Determines the pin category for the provided object class. Returns NAME_None if there is no mapping available */
	virtual FName CreatePinCategoryForObjectClass(const UClass* ObjectClass) const;

	/** Refreshes the provided node in a transaction */
	virtual void RefreshNode(UEdGraphNode* InGraphNode);
protected:
	virtual bool PinCategorySupportsDefaultValue(const FName& PinCategory) const;
	/** Checks to ensure that the output connection is not a dependency of the input connection */
	virtual bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;
	/** Checks if the provided pins have compatible types */
	virtual bool ArePinsCompatible_Internal(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin, FText& OutErrorMessage) const;
};

class FHookTargetConnectionDrawingPolicy : public FConnectionDrawingPolicy {
public:
	FHookTargetConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, const UEdGraph* InGraph);

	// Begin FConnectionDrawingPolicy interface
	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;
	// End FConnectionDrawingPolicy interface
private:
	const UEdGraphSchema_HookTarget* Schema{};
};

