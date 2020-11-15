#include "BlueprintSerializationHelper.h"

#include "Engine/SCS_Node.h"

#define ENSURE_NODE_HAS_INDEX(Node) if (!SCSNodeToIndex.Contains(Node)) SCSNodeToIndex.Add(Node, LastSCSNodeIndex++);

TSharedRef<FJsonObject> FBlueprintSerializationHelper::WriteSimpleConstructionScript(USimpleConstructionScript* SCS, UObjectHierarchySerializer* HierarchySerializer) {
    TSharedRef<FJsonObject> ConstructionScript = MakeShareable(new FJsonObject());
	TMap<USCS_Node*, uint32> SCSNodeToIndex;
	uint32 LastSCSNodeIndex = 1;
	TArray<TSharedPtr<FJsonValue>> AllSCSNodes;
	for (USCS_Node* SCSNode : SCS->GetAllNodes()) {
		ENSURE_NODE_HAS_INDEX(SCSNode);
		uint32 NodeIndex = SCSNodeToIndex.FindChecked(SCSNode);
		TSharedRef<FJsonObject> NodeObject = MakeShareable(new FJsonObject());
		NodeObject->SetNumberField(TEXT("NodeIndex"), NodeIndex);
		NodeObject->SetStringField(TEXT("VariableName"), SCSNode->GetVariableName().ToString());
		NodeObject->SetStringField(TEXT("VariableGuid"), SCSNode->VariableGuid.ToString());
		NodeObject->SetStringField(TEXT("ComponentClass"), SCSNode->ComponentClass->GetPathName());
		NodeObject->SetNumberField(TEXT("ComponentTemplate"), HierarchySerializer->SerializeObject(SCSNode->ComponentTemplate));
		NodeObject->SetStringField(TEXT("ParentComponentOrVariableName"), SCSNode->ParentComponentOrVariableName.ToString());
		NodeObject->SetStringField(TEXT("ParentComponentOwnerClassName"), SCSNode->ParentComponentOwnerClassName.ToString());
		NodeObject->SetStringField(TEXT("AttachToName"), SCSNode->AttachToName.ToString());
		NodeObject->SetBoolField(TEXT("ParentComponentNative"), SCSNode->bIsParentComponentNative);
		TArray<TSharedPtr<FJsonValue>> ChildNodes;
		for (USCS_Node* ChildNode : SCSNode->ChildNodes) {
			ENSURE_NODE_HAS_INDEX(ChildNode);
			const uint32 ChildNodeIndex = SCSNodeToIndex.FindChecked(ChildNode);
			ChildNodes.Add(MakeShareable(new FJsonValueNumber(ChildNodeIndex)));
		}
		NodeObject->SetArrayField(TEXT("ChildNodes"), ChildNodes);
		AllSCSNodes.Add(MakeShareable(new FJsonValueObject(NodeObject)));
	}
	ConstructionScript->SetArrayField(TEXT("AllNodes"), AllSCSNodes);
	TArray<TSharedPtr<FJsonValue>> RootSCSNodes;
	for (USCS_Node* RootSCSNode : SCS->GetRootNodes()) {
		uint32 RootNodeIndex = SCSNodeToIndex.FindChecked(RootSCSNode);
		RootSCSNodes.Add(MakeShareable(new FJsonValueNumber(RootNodeIndex)));
	}
	ConstructionScript->SetArrayField(TEXT("RootNodes"), RootSCSNodes);
	return ConstructionScript;
}
