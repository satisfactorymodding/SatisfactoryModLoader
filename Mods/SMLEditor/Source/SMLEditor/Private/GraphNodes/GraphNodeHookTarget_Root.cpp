#include "GraphNodes/GraphNodeHookTarget_Root.h"
#include "Nodes/HookTargetNode_Root.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

void SGraphNodeHookTarget_Root::Construct(const FArguments& InArgs, UHookTargetNode_Root* InNode) {
	SGraphNodeHookTarget::Construct(SGraphNodeHookTarget::FArguments(), InNode);
}

void SGraphNodeHookTarget_Root::UpdateGraphNode() {
	SGraphNodeHookTarget::UpdateGraphNode();
}

#undef LOCTEXT_NAMESPACE
