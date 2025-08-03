#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_GetMixinTargetObject.generated.h"

UCLASS()
class SMLEDITOR_API UK2Node_GetMixinTargetObject : public UK2Node {
	GENERATED_BODY()
public:
	static const FName TargetOutputPinName;
	
	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//~ End UEdGraphNode Interface

	//~ Begin UK2Node Interface
	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;
	virtual bool IsNodePure() const override { return true; }
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;
	virtual FText GetMenuCategory() const override;
	//~ End UK2Node Interface
};
