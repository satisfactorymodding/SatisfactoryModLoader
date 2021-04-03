#pragma once
#include "Slate.h"

struct FAssetTreeNode : TSharedFromThis<FAssetTreeNode> {
public:
	/** Whenever this node represents a complete asset path, or just a directory */
	bool bIsLeafNode;
	/** Full Path to the represented asset OR directory */
	FString Path;
	/** Last fragment of the path, representing this node's name */
	FString NodeName;
	/** Class of the asset, if this info represents an asset */
	FName AssetClass;

	FAssetTreeNode();
private:
	/** True when children nodes have already been initialized */
	bool bChildrenNodesInitialized;
	TArray<TSharedPtr<FAssetTreeNode>> Children;
    void RegenerateChildren();
public:
	void GetChildrenNodes(TArray<TSharedPtr<FAssetTreeNode>>& OutChildrenNodes);
};

class SAssetRegistryViewWidget : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAssetRegistryViewWidget) {}
	SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

	SAssetRegistryViewWidget();
protected:
	TArray<TSharedPtr<FAssetTreeNode>> RootAssetPaths;
	
	TSharedRef<class ITableRow> OnCreateRow(const TSharedPtr<FAssetTreeNode> TreeNode, const TSharedRef<STableViewBase>& Owner) const;
	void GetNodeChildren(const TSharedPtr<FAssetTreeNode> TreeNode, TArray<TSharedPtr<FAssetTreeNode>>& OutChildren) const;
};

class SAssetTreeNodeRow : public SMultiColumnTableRow<TSharedPtr<FAssetTreeNode>> {
	SLATE_BEGIN_ARGS(SAssetTreeNodeRow) {}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedPtr<FAssetTreeNode>& TreeNodeArg);
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;
private:
	TSharedPtr<FAssetTreeNode> TreeNode;
};
