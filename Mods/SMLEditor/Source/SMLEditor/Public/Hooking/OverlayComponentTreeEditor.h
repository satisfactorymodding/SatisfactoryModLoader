#pragma once

#include "CoreMinimal.h"
#include "GraphEditorDragDropAction.h"
#include "SComponentClassCombo.h"
#include "Components/ActorComponent.h"
#include "Framework/Commands/UICommandList.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"

class UBlueprintMixinComponentNode;
class FHookBlueprintEditor;

/** Generic class to represent the component in the overlaid component tree. Could refer to an immutable base actor Blueprint component or to an overlaid component subtree item */
class SMLEDITOR_API FOverlayComponentData : public TSharedFromThis<FOverlayComponentData> {
public:
	virtual ~FOverlayComponentData() = default;

	/** Returns the name of this component data type */
	virtual FName GetTypeName() const = 0;
	/** Returns true if this component data can be cast to another component data type */
	virtual bool IsOfType(const FName& InTypeName) const { return InTypeName == GetTypeName(); }

	/** Templated version of IsOfType that checks if the component data is of the provided type */
	template<typename T>
	FORCEINLINE bool IsOfType() const { return IsOfType(T::StaticTypeName()); }
	/** Attempts to dynamically cast this overlay data to the provided type. Returns nullptr if the types are not compatible */
	template<typename T>
	FORCEINLINE TSharedPtr<const T> GetAs() const { return IsOfType<T>() ? StaticCastSharedPtr<const T>(SharedThis(this).ToSharedPtr()) : nullptr; }
	template<typename T>
	FORCEINLINE TSharedPtr<T> GetAs() { return IsOfType<T>() ? StaticCastSharedPtr<T>(SharedThis(this).ToSharedPtr()) : nullptr; }
	
	/** Returns the label of this node */
	virtual FText GetNameLabel() const = 0;
	/** Returns the class in which this component has been introduced (specifically introduced, this will return base class if this is a derived class component data) */
	virtual UClass* GetOwnerClass() const = 0;
	/** Returns the name of the variable that contains a reference to this component in the owner class. May return NAME_None for native components with no associated property */
	virtual FName GetComponentVariableName() const = 0;
	/** Returns the immutable actor component template for this component data. The provided object will not be cached. */
	virtual const UActorComponent* GetImmutableActorComponentTemplate() const = 0;
	/** Returns true if this node can be edited or false if it is read only representation */
	virtual bool IsNodeEditable() const { return false; }

	/** Checks if the provided name is a valid name for this component. Only needs to be implemented if the node is editable */
	virtual bool CheckValidRename(const FText& InNewComponentName, FText& OutErrorMessage) const { return false; }
	/** Returns the mutable actor component template for this component data */
	virtual UActorComponent* GetMutableActorComponentTemplate() const { return nullptr; }

	/** Returns true if this component is a direct child of the parent node */
	bool IsDirectlyAttachedToParent(const TSharedPtr<FOverlayComponentData>& InParentNode) const;
	/** Returns true if this component is a child node attached to the provided parent node */
	bool IsAttachedToParent(const TSharedPtr<FOverlayComponentData>& InParentNode) const;
	/** Populate the list with the children nodes of this component */
	void GetChildrenNodes(TArray<TSharedPtr<FOverlayComponentData>>& OutChildrenNodes) const;

	/** Clears list of children and the parent node from this node */
	void ClearHierarchyData();
	/** Adds new child node to this node. Assumes that child node does not have a parent set currently */
	void AddChildNode(const TSharedPtr<FOverlayComponentData>& InNewChildNode);
protected:
	// Transient hierarchy information, will be rebuilt by the tree on demand
	TWeakPtr<FOverlayComponentData> ParentNode;
	TArray<TSharedPtr<FOverlayComponentData>> ChildNodes;
};

/** Component data representing a SCS node */
class SMLEDITOR_API FImmutableSCSNodeComponentData : public FOverlayComponentData {
public:
	FImmutableSCSNodeComponentData(UBlueprintGeneratedClass* InActualOwnerClass, const USCS_Node* InDataNode);

	FORCEINLINE static FName StaticTypeName() { return TEXT("SCSNodeComponentData"); }
	
	virtual FName GetTypeName() const override { return StaticTypeName(); }
	virtual FText GetNameLabel() const override;
	virtual UClass* GetOwnerClass() const override;
	virtual FName GetComponentVariableName() const override;
	virtual const UActorComponent* GetImmutableActorComponentTemplate() const override;
	const USCS_Node* GetSCSNode() const;
protected:
	TWeakObjectPtr<UBlueprintGeneratedClass> ActualOwnerClass;
	TWeakObjectPtr<const USCS_Node> DataNode;
};

/** Component data representing a native component added in C++ constructor */
class SMLEDITOR_API FImmutableNativeComponentData : public FOverlayComponentData {
public:
	FImmutableNativeComponentData(UClass* InOwnerClass, const UActorComponent* InActorComponentTemplate);

	FORCEINLINE static FName StaticTypeName() { return TEXT("NativeComponentData"); }
	
	virtual FName GetTypeName() const override { return StaticTypeName(); }
	virtual FText GetNameLabel() const override;
	virtual UClass* GetOwnerClass() const override;
	virtual FName GetComponentVariableName() const override;
	virtual const UActorComponent* GetImmutableActorComponentTemplate() const override;
protected:
	TWeakObjectPtr<UClass> OwnerClass;
	TWeakObjectPtr<const UActorComponent> ActorComponentTemplate;
};

/** Component data representing a mutable component tree node on the hook blueprint */
class SMLEDITOR_API FMutableMixinComponentNodeData : public FOverlayComponentData {
public:
	explicit FMutableMixinComponentNodeData(const UBlueprintMixinComponentNode* InDataNode);

	FORCEINLINE static FName StaticTypeName() { return TEXT("MixinComponentData"); }
	
	virtual FName GetTypeName() const override { return StaticTypeName(); }
	virtual bool IsNodeEditable() const override { return true; }
	virtual FText GetNameLabel() const override;
	virtual UClass* GetOwnerClass() const override;
	virtual FName GetComponentVariableName() const override;
	virtual const UActorComponent* GetImmutableActorComponentTemplate() const override;
	virtual bool CheckValidRename(const FText& InNewComponentName, FText& OutErrorMessage) const override;
	virtual UActorComponent* GetMutableActorComponentTemplate() const override;
	const UBlueprintMixinComponentNode* GetComponentNode() const;
protected:
	TWeakObjectPtr<const UBlueprintMixinComponentNode> DataNode;
};

class SMLEDITOR_API SOverlayComponentTreeEditor : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SOverlayComponentTreeEditor) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedPtr<FHookBlueprintEditor>& InOwnerBlueprintEditor);
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	/** Returns true if the underlying blueprint editor allows editing under current conditions */
	bool IsEditingAllowed() const;

	/** Returns the component tree for the overlay tree editor */
	TSharedPtr<class SOverlayComponentTreeView> GetComponentTree() const { return ComponentTreeView; }

	/** Returns all nodes currently selected in the component tree, sorted by their depth */
	TArray<TSharedPtr<FOverlayComponentData>> GetSelectedNodes() const;

	/** Handles asset being dropped into the component tree */
	FReply TryHandleAssetDragNDropOperation(const FDragDropEvent& DragDropEvent);
	/** Called to create a new component of the defined class after selecting it from the combo box */
	FSubobjectDataHandle PerformComboAddClass(TSubclassOf<UActorComponent> ComponentClass, EComponentCreateAction::Type ComponentCreateAction, UObject* AssetOverride);

	/** Attempts to find the node mapping to the provided preview component instance */
	TSharedPtr<FOverlayComponentData> FindComponentDataForComponentInstance(const UActorComponent* InPreviewComponent) const;
	/** Attempts to find the component instance for the provided component data in the given actor */
	UActorComponent* FindComponentInstanceInActor(AActor* InActor, const TSharedPtr<FOverlayComponentData>& InComponentData) const;
	/** Sets up selection override for the provided actor component to be shown as selected when it is selected in the overlay component tree */
	void SetSelectionOverrideForComponent(UPrimitiveComponent* InPreviewComponent);
	/** Selects the tree node corresponding to the provided actor template component */
	void SelectNodeForComponent(const UActorComponent* InPreviewComponent, bool bIsMultiSelectActive);

	/** Called to request the provided components to be removed */
	void OnDeleteAction(const TArray<TSharedPtr<FOverlayComponentData>>& NodesToDelete);
	/** Called to request the provided component to be renamed */
	void OnUpdateComponentNameAction(const TSharedPtr<FOverlayComponentData>& ComponentData, const FText& InNewComponentName);
	/** Called to request the provided components to be attached to the provided component */
	void OnAttachToDropAction(const TSharedPtr<FOverlayComponentData>& AttachToComponentData, const TArray<TSharedPtr<FOverlayComponentData>>& NodesToAttach);
	/** Called to request the provided components to be detached from their parent component and moved to the same level as it */
	void OnDetachFromDropAction(const TArray<TSharedPtr<FOverlayComponentData>>& NodesToAttach);

	/** Requests the refresh of the component tree */
	void UpdateTree();
protected:
	// Utility functions for modification or deletion of existing nodes
	bool CanRenameComponent() const;
	void OnRenameComponent();
	bool CanDeleteNodes() const;
	void OnDeleteNodes();
	void OnFindReferences();

	/** Refreshes the component tree from the blueprint. Attempts to preserve as many existing nodes as possible while rebuilding the node hierarchy from scratch */
	void RefreshComponentTreeFromBlueprint();

	/** Called to request a component to be created in this class. This is generic function called for both pasting and new component creation. This does not start a transaction. */
	void CreateComponentFromClass(UClass* InComponentClass, UObject* InComponentAsset = nullptr, UObject* InComponentTemplate = nullptr);
	/** Attaches node to the provided component data. This is a generic function. This does not start a transaction */
	static bool AttachComponentNodeToComponentData(UBlueprintMixinComponentNode* InComponentNode, const TSharedPtr<FOverlayComponentData>& InAttachToComponentData);

	/** Register default commands implementation for the editor (such as copying, pasting, deleting or searching) */
	void RegisterEditorCommands();
	/** Creates a row widget for the tree overlay component */
	TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FOverlayComponentData> InNodePtr, const TSharedRef<STableViewBase>& OwnerTable);
	/** Returns components that are children of the provided component */
	void OnGetChildrenForTree(const TSharedPtr<FOverlayComponentData> InNodePtr, TArray<TSharedPtr<FOverlayComponentData>>& OutChildren);
	/** Recursively expands the tree from the provided item */
	void SetItemExpansionRecursive(const TSharedPtr<FOverlayComponentData> InNodeToChange, bool bInExpansionState);

	/** Update the details panel to point to the selected editable nodes */
	void UpdateSelectionFromNodes(const TArray<TSharedPtr<FOverlayComponentData>>& SelectedNodes);
	/** Called when selection in the tree changes */
	void OnTreeSelectionChanged(TSharedPtr<FOverlayComponentData> InSelectedNodePtr, ESelectInfo::Type SelectInfo);
	/** Callback when a component item is scrolled into view */
	void OnItemScrolledIntoView(TSharedPtr<FOverlayComponentData> InItem, const TSharedPtr<ITableRow>& InWidget);
	/** Returns true if overlay tree node associated with this instance is selected */
	bool IsComponentInstanceSelected(const UPrimitiveComponent* InPreviewComponent) const;

	TWeakPtr<FHookBlueprintEditor> OwnerBlueprintEditor;
	TSharedPtr<SOverlayComponentTreeView> ComponentTreeView;
	TSharedPtr<FUICommandList> CommandList;
	TSharedPtr<FOverlayComponentData> PendingRenameComponentData;

	// Root node set, all nodes in the tree, and caches to reuse existing nodes to avoid completely regenerating the entire tree
	TArray<TSharedPtr<FOverlayComponentData>> RootNodes;
	TArray<TSharedPtr<FOverlayComponentData>> AllNodes;
	TMap<TWeakObjectPtr<const UObject>, TSharedPtr<FOverlayComponentData>> ObjectToComponentDataCache;
};

class SMLEDITOR_API SOverlayComponentTreeView : public STreeView<TSharedPtr<FOverlayComponentData>> {
public:
	void Construct(const FArguments& InArgs, const TSharedPtr<SOverlayComponentTreeEditor>& InOwnerTreeEditor);

	// Begin SWidget interface
	virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;
	// End SWidget interface
protected:
	/** Check if asset drag and drop operation contains any class assets (e.g. blueprints) */
	static bool ContainsAnyClassAssets(const TSharedPtr<class FAssetDragDropOp>& AssetDragNDropOp);
	
	TWeakPtr<SOverlayComponentTreeEditor> OwnerTreeEditor;
};

class SMLEDITOR_API FOverlayComponentTreeRowDragDropOp : public FGraphSchemaActionDragDropAction {
public:
	DRAG_DROP_OPERATOR_TYPE(FOverlayComponentTreeRowDragDropOp, FGraphSchemaActionDragDropAction);

	/** Available drop actions */
	enum EDropActionType {
		DropAction_None,
		DropAction_AttachTo,
		DropAction_DetachFrom
	};

	// Begin FGraphEditorDragDropAction interface
	virtual void HoverTargetChanged() override;
	virtual FReply DroppedOnPanel(const TSharedRef<SWidget>& Panel, FVector2D ScreenPosition, FVector2D GraphPosition, UEdGraph& Graph) override;
	virtual FReply DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition) override;
	// End FGraphEditorDragDropAction interface

	/** Nodes that we started the drag from */
	TArray<TSharedPtr<FOverlayComponentData>> SourceNodes;
	/** The type of drop action that's pending while dragging */
	EDropActionType PendingDropAction{DropAction_None};

	static TSharedRef<FOverlayComponentTreeRowDragDropOp> Create(const TArray<TSharedPtr<FOverlayComponentData>>& InSourceNodes);
protected:
	/** Creates a variable getter node for the provided component data */
	static class UK2Node_VariableGet* SpawnVariableGetNodeForComponentData(UEdGraph* InTargetGraph, const TSharedPtr<FOverlayComponentData>& InComponentData, const FVector2D& InScreenPosition);
};

class SOverlayComponentTreeViewRowWidget : public SMultiColumnTableRow<TSharedPtr<FOverlayComponentData>> {
public:
	SLATE_BEGIN_ARGS(SOverlayComponentTreeViewRowWidget) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, TSharedPtr<SOverlayComponentTreeEditor> InOwnerTreeOverlay, const TSharedPtr<FOverlayComponentData> InNodePtr, TSharedPtr<STableViewBase> InOwnerTableView);

	// Begin SMultiColumnTableRow interface
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;
	// End SMultiColumnTableRow interface

	/** Request the widget to start editing the component name box */
	void StartEditingComponentName();
protected:
	// Accessor and mutators for the name of the component */
	FText GetNameLabel() const;
	bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage);
	void OnNameTextCommit(const FText& InNewName, ETextCommit::Type InTextCommit);
	const FSlateBrush* GetIconBrush() const;

	// Accessors to read the information about the asset that this component is created from
	EVisibility GetAssetVisibility() const;
	FText GetAssetName() const;
	FText GetAssetPath() const;

	// Accessors for the mobility settings of this component. Only relevant for components
	FText GetMobilityToolTipText() const;
	FSlateBrush const* GetMobilityIconImage() const;
	FText GetComponentEditorOnlyTooltipText() const;
	FText GetComponentEditableTooltipText() const;

	// Creates the tooltip widget for this component node
	TSharedRef<SToolTip> CreateTooltipWidget() const;
	FText GetTooltipText() const;

	// Handlers for dragging and dropping the components onto the tree node
	void HandleOnDragEnter(const FDragDropEvent& DragDropEvent);
	void HandleOnDragLeave(const FDragDropEvent& DragDropEvent);
	FReply HandleOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	TOptional<EItemDropZone> HandleOnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, const TSharedPtr<FOverlayComponentData> TargetItem);
	FReply HandleOnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FOverlayComponentData> TargetItem);

	static FOverlayComponentTreeRowDragDropOp::EDropActionType CheckCanAttachSelectedNodeToNode(const TSharedPtr<FOverlayComponentData>& SelectedNode, const TSharedPtr<FOverlayComponentData>& DraggedOverNode, FText& OutDescriptionMessage);

	TSharedPtr<SInlineEditableTextBlock> EditableNameTextBlock;
	TWeakPtr<SOverlayComponentTreeEditor> OwnerTreeOverlay;
	TSharedPtr<FOverlayComponentData> ComponentData;
};

class SMLEDITOR_API SOverlayComponentTooltipBlock : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SOverlayComponentTooltipBlock) : _Important(false) {}
		SLATE_ARGUMENT(FText, Key);
		SLATE_ATTRIBUTE(FText, Value);
		SLATE_NAMED_SLOT(FArguments, ValueIcon);
		SLATE_ARGUMENT(bool, Important);
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs);
};

class SOverlayComponentTreeSeparatorRowWidget : public SMultiColumnTableRow<TSharedPtr<FOverlayComponentData>> {
public:
	SLATE_BEGIN_ARGS(SOverlayComponentTreeSeparatorRowWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView);
	virtual ESelectionMode::Type GetSelectionMode() const override { return ESelectionMode::None; }
	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;
};
