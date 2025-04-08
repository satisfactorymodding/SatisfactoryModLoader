#pragma once

#include "CoreMinimal.h"
#include "GraphNodeHookTarget.h"
#include "GraphNodes/GraphNodeHookTarget_Root.h"
#include "Widgets/Input/SComboBox.h"

class SMLEDITOR_API SGraphNodeHookTarget_Root : public SGraphNodeHookTarget {
public:
	SLATE_BEGIN_ARGS(SGraphNodeHookTarget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UHookTargetNode_Root* InNode);

	// Begin SGraphNodeHookTarget interface
	virtual void UpdateGraphNode() override;
	// End SGraphNodeHookTarget interface
};
