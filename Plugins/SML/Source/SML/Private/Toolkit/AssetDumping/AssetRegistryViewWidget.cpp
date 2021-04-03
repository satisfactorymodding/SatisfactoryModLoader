#include "Toolkit/AssetDumping/AssetRegistryViewWidget.h"
#include "AssetRegistryModule.h"
#define LOCTEXT_NAMESPACE "SML"

FAssetTreeNode::FAssetTreeNode() {
	this->bIsLeafNode = false;
	this->AssetClass = NAME_None;
	this->bChildrenNodesInitialized = false;
}

void FAssetTreeNode::RegenerateChildren() {
	if (bIsLeafNode) {
		return;
	}
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.GetRegistry();

	//Retrieve sub paths without recursing into them, we want to populate them lazily
	TArray<FString> OutSubPaths;
	AssetRegistry.GetSubPaths(Path, OutSubPaths, false);

	//Append sub path nodes first into the resulting array
	for (const FString& AssetSubPath : OutSubPaths) {
		TSharedPtr<FAssetTreeNode> Node(new FAssetTreeNode);
		Node->bIsLeafNode = false;
		Node->NodeName = FPaths::GetCleanFilename(AssetSubPath);
		Node->Path = AssetSubPath;
		Children.Add(Node);
	}

	//Now attempt to resolve assets at the provided path
	TArray<FAssetData> OutAssetsAtPath;
	AssetRegistry.GetAssetsByPath(*Path, OutAssetsAtPath, false, false);
	for (const FAssetData& AssetData : OutAssetsAtPath) {
		TSharedPtr<FAssetTreeNode> Node(new FAssetTreeNode);
		Node->bIsLeafNode = true;
		Node->NodeName = AssetData.AssetName.ToString();
		Node->AssetClass = AssetData.AssetClass;
		Node->Path = AssetData.ObjectPath.ToString();
		Children.Add(Node);
	}
}

void FAssetTreeNode::GetChildrenNodes(TArray<TSharedPtr<FAssetTreeNode>>& OutChildrenNodes) {
	if (!bChildrenNodesInitialized) {
		this->bChildrenNodesInitialized = true;
		RegenerateChildren();
	}
	OutChildrenNodes.Append(Children);
}

SAssetRegistryViewWidget::SAssetRegistryViewWidget() {
	//Create initial collection of roots
	const TSharedPtr<FAssetTreeNode> RootAssetTreeNode(new FAssetTreeNode);
	RootAssetTreeNode->bIsLeafNode = false;
	RootAssetTreeNode->Path = TEXT("/");
	RootAssetTreeNode->GetChildrenNodes(this->RootAssetPaths);
}

void SAssetRegistryViewWidget::Construct(const FArguments& InArgs) {
	ChildSlot[
		SNew(STreeView<TSharedPtr<FAssetTreeNode>>)
		.HeaderRow(SNew(SHeaderRow)
					+SHeaderRow::Column(TEXT("Path"))
						.DefaultLabel(LOCTEXT("AssetDumper_ColumnPath", "Asset Path"))
					+SHeaderRow::Column(TEXT("AssetClass"))
						.DefaultLabel(LOCTEXT("AssetDumper_ColumnAssetClass", "Asset Class"))
						.FixedWidth(100)
						.HAlignCell(HAlign_Left)
						.HAlignHeader(HAlign_Center)
					+SHeaderRow::Column(TEXT("ShouldDump"))
						.DefaultLabel(LOCTEXT("AssetDumper_ColumnShouldDump", "Dump"))
						.FixedWidth(50)
						.HAlignCell(HAlign_Center)
						.HAlignHeader(HAlign_Center)
		)
        .OnGenerateRow_Raw(this, &SAssetRegistryViewWidget::OnCreateRow)
        .OnGetChildren_Raw(this, &SAssetRegistryViewWidget::GetNodeChildren)
        .TreeItemsSource(&this->RootAssetPaths)
	];
}

void SAssetRegistryViewWidget::GetNodeChildren(const TSharedPtr<FAssetTreeNode> TreeNode, TArray<TSharedPtr<FAssetTreeNode>>& OutChildren) const {
	TreeNode->GetChildrenNodes(OutChildren);
}

void SAssetTreeNodeRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, const TSharedPtr<FAssetTreeNode>& TreeNodeArg) {
	this->TreeNode = TreeNodeArg;
	FSuperRowType::Construct(FTableRowArgs(), OwnerTable);
}

TSharedRef<SWidget> SAssetTreeNodeRow::GenerateWidgetForColumn(const FName& InColumnName) {
	if (InColumnName == TEXT("Path")) {
		return SNew(SHorizontalBox)
		+SHorizontalBox::Slot()[
			SNew(SExpanderArrow, SharedThis(this))
        ]
        +SHorizontalBox::Slot()[
			SNew(STextBlock)
			.Text(FText::FromString(TreeNode->NodeName))
        ];
	}
	if (InColumnName == TEXT("AssetClass")) {
		if (TreeNode->bIsLeafNode) {
			return SNew(STextBlock)
				.Text(FText::FromString(TreeNode->AssetClass.ToString()));
		}
		return SNullWidget::NullWidget;
	}
	return SNew(SCheckBox);
}

TSharedRef<ITableRow> SAssetRegistryViewWidget::OnCreateRow(const TSharedPtr<FAssetTreeNode> TreeNode, const TSharedRef<STableViewBase>& Owner) const {
	return SNew(SAssetTreeNodeRow, Owner, TreeNode);
}
