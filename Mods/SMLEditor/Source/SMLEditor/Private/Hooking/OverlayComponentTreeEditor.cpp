#include "Hooking/OverlayComponentTreeEditor.h"
#include "AssetSelection.h"
#include "ComponentAssetBroker.h"
#include "GraphEditorActions.h"
#include "ScopedTransaction.h"
#include "DragAndDrop/AssetDragDropOp.h"
#include "Framework/Commands/GenericCommands.h"
#include "Hooking/HookBlueprintEditor.h"
#include "Styling/SlateIconFinder.h"
#include "Widgets/SToolTip.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphSchema_K2_Actions.h"
#include "K2Node_VariableGet.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/MemberReference.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/ComponentEditorUtils.h"
#include "Misc/MessageDialog.h"
#include "Nodes/K2Node_GetMixinTargetObject.h"
#include "Patching/BlueprintHookBlueprint.h"
#include "Widgets/Layout/SSpacer.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

bool FOverlayComponentData::IsDirectlyAttachedToParent(const TSharedPtr<FOverlayComponentData>& InParentNode) const {
	return InParentNode && ParentNode == InParentNode;
}

bool FOverlayComponentData::IsAttachedToParent(const TSharedPtr<FOverlayComponentData>& InParentNode) const {
	// Walk the parent chain of this node until we reach the given node or run out of nodes
	TSharedPtr<FOverlayComponentData> CurrentNodeParent = ParentNode.Pin();
	while (CurrentNodeParent && CurrentNodeParent != InParentNode) {
		CurrentNodeParent = CurrentNodeParent->ParentNode.Pin();
	}
	// This node is atached to the parent if current parent is the provided parent
	return CurrentNodeParent == InParentNode;
}

void FOverlayComponentData::GetChildrenNodes(TArray<TSharedPtr<FOverlayComponentData>>& OutChildrenNodes) const {
	OutChildrenNodes.Append(ChildNodes);
}

void FOverlayComponentData::ClearHierarchyData() {
	ParentNode.Reset();
	ChildNodes.Reset();
}

void FOverlayComponentData::AddChildNode(const TSharedPtr<FOverlayComponentData>& InNewChildNode) {
	ensure(InNewChildNode->ParentNode == nullptr);
	InNewChildNode->ParentNode = SharedThis(this);
	ChildNodes.Add(InNewChildNode);
}

FImmutableSCSNodeComponentData::FImmutableSCSNodeComponentData(UBlueprintGeneratedClass* InActualOwnerClass, const USCS_Node* InDataNode) : ActualOwnerClass(InActualOwnerClass), DataNode(InDataNode) {}

FText FImmutableSCSNodeComponentData::GetNameLabel() const {
	if (const USCS_Node* PinnedDataNode = DataNode.Get()) {
		return FText::FromName(PinnedDataNode->GetVariableName());
	}
	return FText::GetEmpty();
}

UClass* FImmutableSCSNodeComponentData::GetOwnerClass() const {
	if (const USCS_Node* PinnedDataNode = DataNode.Get()) {
		return PinnedDataNode->GetTypedOuter<UBlueprintGeneratedClass>();
	}
	return nullptr;
}

FName FImmutableSCSNodeComponentData::GetComponentVariableName() const {
	if (const USCS_Node* PinnedDataNode = DataNode.Get()) {
		return PinnedDataNode->GetVariableName();
	}
	return NAME_None;
}

const UActorComponent* FImmutableSCSNodeComponentData::GetImmutableActorComponentTemplate() const {
	// Return the actual component template from the derived class, not the one from the base class
	if (UBlueprintGeneratedClass* PinnedActualOwnerClass = ActualOwnerClass.Get()) {
		if (const USCS_Node* PinnedDataNode = DataNode.Get()) {
			return PinnedDataNode->GetActualComponentTemplate(PinnedActualOwnerClass);
		}
	}
	return nullptr;
}

const USCS_Node* FImmutableSCSNodeComponentData::GetSCSNode() const {
	return DataNode.Get();
}

FImmutableNativeComponentData::FImmutableNativeComponentData(UClass* InOwnerClass, const UActorComponent* InActorComponentTemplate) : OwnerClass(InOwnerClass), ActorComponentTemplate(InActorComponentTemplate) {
}

FText FImmutableNativeComponentData::GetNameLabel() const {
	if (const UActorComponent* PinnedActorComponentTemplate = ActorComponentTemplate.Get()) {
		return FText::FromName(PinnedActorComponentTemplate->GetFName());
	}
	return FText::GetEmpty();
}

UClass* FImmutableNativeComponentData::GetOwnerClass() const {
	return OwnerClass.Get();
}

FName FImmutableNativeComponentData::GetComponentVariableName() const {
	if (const UActorComponent* PinnedActorComponentTemplate = ActorComponentTemplate.Get()) {
		if (const UClass* PinnedOwnerClass = OwnerClass.Get()) {

			// Iterate all properties in the class and attempt to find the one matching the component
			for (TFieldIterator<FObjectProperty> PropertyIterator(PinnedOwnerClass, EFieldIterationFlags::IncludeAll); PropertyIterator; ++PropertyIterator) {
				
				// We are not interested in non-blueprint-visible properties
				if (!PropertyIterator->HasAnyPropertyFlags(CPF_BlueprintVisible)) {
					continue;
				}
				// Only the properties that have a type that matches the type of the component are considered to own the component
				// This is to ensure that properties like RootComponent cannot be used to refer to the root component
				if (PropertyIterator->PropertyClass == PinnedActorComponentTemplate->GetClass()) {
					continue;
				}

				// If this property currently holds the value of the component archetype, this property is the component variable
				const UObject* ObjectPropertyValue = PropertyIterator->GetObjectPropertyValue_InContainer(PinnedOwnerClass->GetDefaultObject());
				if (ObjectPropertyValue == PinnedActorComponentTemplate) {
					return PropertyIterator->GetFName();
				}
			}
		}
	}
	// We do not have a variable that can be used to access this component otherwise
	return NAME_None;
}

const UActorComponent* FImmutableNativeComponentData::GetImmutableActorComponentTemplate() const {
	return ActorComponentTemplate.Get();
}

FMutableMixinComponentNodeData::FMutableMixinComponentNodeData(const UBlueprintMixinComponentNode* InDataNode) : DataNode(InDataNode) {}

FText FMutableMixinComponentNodeData::GetNameLabel() const {
	if (const UBlueprintMixinComponentNode* PinnedDataNode = DataNode.Get()) {
		return FText::FromName(PinnedDataNode->ComponentVariableName);
	}
	return FText::GetEmpty();
}

UClass* FMutableMixinComponentNodeData::GetOwnerClass() const {
	if (const UBlueprintMixinComponentNode* PinnedDataNode = DataNode.Get()) {
		return PinnedDataNode->GetTypedOuter<UBlueprintGeneratedClass>();
	}
	return nullptr;
}

FName FMutableMixinComponentNodeData::GetComponentVariableName() const {
	if (const UBlueprintMixinComponentNode* PinnedDataNode = DataNode.Get()) {
		return PinnedDataNode->ComponentVariableName;
	}
	return NAME_None;
}

const UActorComponent* FMutableMixinComponentNodeData::GetImmutableActorComponentTemplate() const {
	return GetMutableActorComponentTemplate();
}

bool FMutableMixinComponentNodeData::CheckValidRename(const FText& InNewComponentName, FText& OutErrorMessage) const {
	if (const UBlueprintMixinComponentNode* PinnedDataNode = DataNode.Get()) {
		const FName NewComponentFName = *InNewComponentName.ToString();
		
		// Rename is valid if the current name matches the provided name
		if (PinnedDataNode->ComponentVariableName == NewComponentFName) {
			return true;
		}
		// Ensure that owner blueprint generated class is actually valid
		const UBlueprintGeneratedClass* OwnerBlueprintGeneratedClass = PinnedDataNode->GetTypedOuter<UBlueprintGeneratedClass>();
		if (OwnerBlueprintGeneratedClass == nullptr) {
			return false;
		}
		// Ensure that owner blueprint is valid
		const UBlueprint* Blueprint = CastChecked<UBlueprint>(OwnerBlueprintGeneratedClass->ClassGeneratedBy);
		if (Blueprint == nullptr) {
		    return false;
		}
		
		// Run the kismet variable name validator to ensure that the name is valid
		const TSharedPtr<INameValidatorInterface> NameValidator = MakeShareable(new FKismetNameValidator(Blueprint, PinnedDataNode->ComponentVariableName, nullptr));
		const EValidatorResult ValidatorResult = NameValidator->IsValid(NewComponentFName.ToString());

		// Provide a meaningful error message for the variable
		if(ValidatorResult == EValidatorResult::AlreadyInUse) {
			OutErrorMessage = FText::Format(LOCTEXT("RenameFailed_InUse", "{0} is in use by another variable or function!"), InNewComponentName);
		}
		else if(ValidatorResult == EValidatorResult::EmptyName) {
			OutErrorMessage = LOCTEXT("RenameFailed_LeftBlank", "Names cannot be left blank!");
		}
		else if(ValidatorResult == EValidatorResult::TooLong) {
			OutErrorMessage = FText::Format( LOCTEXT("RenameFailed_NameTooLong", "Names must have fewer than {0} characters!"), FText::AsNumber( FKismetNameValidator::GetMaximumNameLength()));
		}
		return ValidatorResult == EValidatorResult::Ok;
	}
	return false;
}

UActorComponent* FMutableMixinComponentNodeData::GetMutableActorComponentTemplate() const {
	if (const UBlueprintMixinComponentNode* PinnedDataNode = DataNode.Get()) {
		return PinnedDataNode->ComponentTemplate;
	}
	return nullptr;
}

const UBlueprintMixinComponentNode* FMutableMixinComponentNodeData::GetComponentNode() const {
	return DataNode.Get();
}

void SOverlayComponentTreeView::Construct(const FArguments& InArgs, const TSharedPtr<SOverlayComponentTreeEditor>& InOwnerTreeEditor) {
	OwnerTreeEditor = InOwnerTreeEditor;
	STreeView::Construct(InArgs);
}

FReply SOverlayComponentTreeView::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) {
	const TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();

	// Allow dragging over assets of the supported class and component types
	if (Operation.IsValid() && (Operation->IsOfType<FExternalDragOperation>() || Operation->IsOfType<FAssetDragDropOp>())) {
		const FReply ParentReply = AssetUtil::CanHandleAssetDrag(DragDropEvent);
		if (!ParentReply.IsEventHandled() && Operation->IsOfType<FAssetDragDropOp>()) {
			const TSharedPtr<FAssetDragDropOp> AssetDragDropOp = StaticCastSharedPtr<FAssetDragDropOp>(Operation);
			if (ContainsAnyClassAssets(AssetDragDropOp)) {
				return FReply::Handled();
			}
		}
		return ParentReply;
	}
	return FReply::Unhandled();
}

bool SOverlayComponentTreeView::ContainsAnyClassAssets(const TSharedPtr<FAssetDragDropOp>& AssetDragNDropOp) {
	for (const FAssetData& AssetData : AssetDragNDropOp->GetAssets()) {
		if (const UClass* AssetClass = AssetData.GetClass()) {
			if (AssetClass->IsChildOf(UClass::StaticClass())) {
				return true;
			}
		}
	}
	return false;
}

FReply SOverlayComponentTreeView::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) {
	if (const TSharedPtr<SOverlayComponentTreeEditor> OwnerEditor = OwnerTreeEditor.Pin()) {
		return OwnerEditor->TryHandleAssetDragNDropOperation(DragDropEvent);
	}
	return FReply::Unhandled();
}

void SOverlayComponentTreeViewRowWidget::Construct(const FArguments&, TSharedPtr<SOverlayComponentTreeEditor> InOwnerTreeOverlay, const TSharedPtr<FOverlayComponentData> InNodePtr, TSharedPtr<STableViewBase> InOwnerTableView) {
	OwnerTreeOverlay = InOwnerTreeOverlay;
	ComponentData = InNodePtr;

	const FSuperRowType::FArguments Args = FSuperRowType::FArguments()
		.Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("SceneOutliner.TableViewRow"))
		.Padding(FMargin(0.0f, 4.0f, 0.0f, 4.0f))
		.OnDragDetected(this, &SOverlayComponentTreeViewRowWidget::HandleOnDragDetected)
		.OnDragEnter(this, &SOverlayComponentTreeViewRowWidget::HandleOnDragEnter)
		.OnDragLeave(this, &SOverlayComponentTreeViewRowWidget::HandleOnDragLeave)
		.OnCanAcceptDrop(this, &SOverlayComponentTreeViewRowWidget::HandleOnCanAcceptDrop)
		.OnAcceptDrop(this, &SOverlayComponentTreeViewRowWidget::HandleOnAcceptDrop);

	SMultiColumnTableRow::Construct(Args, InOwnerTableView.ToSharedRef());
}

TSharedRef<SWidget> SOverlayComponentTreeViewRowWidget::GenerateWidgetForColumn(const FName& ColumnName) {
	// Component name column
	if (ColumnName == TEXT("ComponentName")) {
		return SNew(SHorizontalBox)
		.ToolTip(CreateTooltipWidget())
		+SHorizontalBox::Slot().Padding(FMargin(0.0f, 0.0f, 0.0f, 0.0f)).AutoWidth().VAlign(VAlign_Center) [
			SNew(SExpanderArrow, SharedThis(this))
			.Visibility(EVisibility::Visible)
		]
		+SHorizontalBox::Slot().Padding(FMargin(0.0f, 0.0f, 0.0f, 0.0f)).AutoWidth().VAlign(VAlign_Center) [
			SNew(SImage)
			.Image(GetIconBrush())
			.ColorAndOpacity(FSlateColor::UseForeground())
		]
		+SHorizontalBox::Slot().VAlign(VAlign_Center).HAlign(HAlign_Left).AutoWidth().Padding(6.f, 0.0f, 0.0f, 0.0f) [
			SAssignNew(EditableNameTextBlock, SInlineEditableTextBlock)
			.Text(this, &SOverlayComponentTreeViewRowWidget::GetNameLabel)
			.ColorAndOpacity(ComponentData->IsNodeEditable() ? FSlateColor(FLinearColor(0.25f, 0.72f, 0.1f)) : FSlateColor::UseForeground())
			.OnVerifyTextChanged(this, &SOverlayComponentTreeViewRowWidget::OnNameTextVerifyChanged)
			.OnTextCommitted(this, &SOverlayComponentTreeViewRowWidget::OnNameTextCommit)
			.IsSelected(this, &SOverlayComponentTreeViewRowWidget::IsSelectedExclusively)
			.IsReadOnly(!ComponentData->IsNodeEditable())
		];
	}
	return SNew(STextBlock).Text(LOCTEXT("UnknownColumn", "Unknown Column"));
}

void SOverlayComponentTreeViewRowWidget::StartEditingComponentName() {
	if (EditableNameTextBlock) {
		EditableNameTextBlock->EnterEditingMode();
	}
}

FText SOverlayComponentTreeViewRowWidget::GetNameLabel() const {
	return ComponentData->GetNameLabel();
}

bool SOverlayComponentTreeViewRowWidget::OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage) {
	return ComponentData->CheckValidRename(InNewText, OutErrorMessage);
}

void SOverlayComponentTreeViewRowWidget::OnNameTextCommit(const FText& InNewName, ETextCommit::Type) {
	if (const TSharedPtr<SOverlayComponentTreeEditor> PinnedOwnerTreeEditor = OwnerTreeOverlay.Pin()) {
		PinnedOwnerTreeEditor->OnUpdateComponentNameAction(ComponentData, InNewName);	
	}
}

const FSlateBrush* SOverlayComponentTreeViewRowWidget::GetIconBrush() const {
	if (const UActorComponent* SourceActorComponent = ComponentData->GetImmutableActorComponentTemplate()) {
		return FSlateIconFinder::FindIconBrushForClass(SourceActorComponent->GetClass(), TEXT("SCS.Component"));
	}
	return FAppStyle::GetBrush("SCS.NativeComponent");
}

EVisibility SOverlayComponentTreeViewRowWidget::GetAssetVisibility() const {
	if (const UActorComponent* SourceActorComponent = ComponentData->GetImmutableActorComponentTemplate()) {
		// This might not be safe (to cast away const-ness like this), but asset broker must never modify the original component
		if (FComponentAssetBrokerage::SupportsAssets(const_cast<UActorComponent*>(SourceActorComponent))) {
			return EVisibility::Visible;
		}
	}
	return EVisibility::Hidden;
}

FText SOverlayComponentTreeViewRowWidget::GetAssetName() const {
	if (const UActorComponent* SourceActorComponent = ComponentData->GetImmutableActorComponentTemplate()) {
		// This might not be safe (to cast away const-ness like this), but asset broker must never modify the original component
		if (const UObject* Asset = FComponentAssetBrokerage::GetAssetFromComponent(const_cast<UActorComponent*>(SourceActorComponent))) {
			return FText::FromString(Asset->GetName());
		}
	}
	return LOCTEXT("None", "None");
}

FText SOverlayComponentTreeViewRowWidget::GetAssetPath() const {
	if (const UActorComponent* SourceActorComponent = ComponentData->GetImmutableActorComponentTemplate()) {
		// This might not be safe (to cast away const-ness like this), but asset broker must never modify the original component
		if (const UObject* Asset = FComponentAssetBrokerage::GetAssetFromComponent(const_cast<UActorComponent*>(SourceActorComponent))) {
			return FText::FromString(Asset->GetPathName());
		}
	}
	return LOCTEXT("None", "None");
}

FText SOverlayComponentTreeViewRowWidget::GetMobilityToolTipText() const {
	if (const USceneComponent* SourceSceneComponent = Cast<USceneComponent>(ComponentData->GetImmutableActorComponentTemplate())) {
		if (SourceSceneComponent->Mobility == EComponentMobility::Movable) {
			return LOCTEXT("MovableMobilityTooltip", "Movable");
		}
		if (SourceSceneComponent->Mobility == EComponentMobility::Stationary) {
			return LOCTEXT("StationaryMobilityTooltip", "Stationary");
		}
		if (SourceSceneComponent->Mobility == EComponentMobility::Static) {
			return LOCTEXT("StaticMobilityTooltip", "Static");
		}
	}
	return LOCTEXT("NoMobilityTooltip", "Non-scene component");;
}

FSlateBrush const* SOverlayComponentTreeViewRowWidget::GetMobilityIconImage() const {
	if (const USceneComponent* SourceSceneComponent = Cast<USceneComponent>(ComponentData->GetImmutableActorComponentTemplate())) {
		if (SourceSceneComponent->Mobility == EComponentMobility::Movable) {
			return FAppStyle::GetBrush(TEXT("ClassIcon.MovableMobilityIcon"));
		}
		if (SourceSceneComponent->Mobility == EComponentMobility::Stationary) {
			return FAppStyle::GetBrush(TEXT("ClassIcon.StationaryMobilityIcon"));
		}
	}
	return nullptr;
}

FText SOverlayComponentTreeViewRowWidget::GetComponentEditorOnlyTooltipText() const {
	const UActorComponent* SourceComponent = ComponentData->GetImmutableActorComponentTemplate();
	if (SourceComponent != nullptr && SourceComponent->bIsEditorOnly) {
		return LOCTEXT("ComponentEditorOnly_True", "True");
	}
	return LOCTEXT("ComponentEditorOnly_False", "False");
}

FText SOverlayComponentTreeViewRowWidget::GetComponentEditableTooltipText() const {
	return ComponentData->IsNodeEditable() ? LOCTEXT("ComponentEditableTooltip_Editable", "Editable (Overlay Component)") :
		LOCTEXT("ComponentEditableTooltip_Immutable", "Inherited (Target Component)");
}

void SOverlayComponentTooltipBlock::Construct(const FArguments& InArgs) {
	ChildSlot [
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot().AutoWidth().Padding(0.0f, 0.0f, 4.0f, 0.0f) [
			SNew(STextBlock)
			.TextStyle(FAppStyle::Get(), InArgs._Important ? "SCSEditor.ComponentTooltip.ImportantLabel" : "SCSEditor.ComponentTooltip.Label")
			.Text(FText::Format(LOCTEXT("AssetViewTooltipFormat", "{0}:"), InArgs._Key))
		]
		+SHorizontalBox::Slot().AutoWidth() [
			InArgs._ValueIcon.Widget
		]
		+SHorizontalBox::Slot().AutoWidth() [
			SNew(STextBlock)
			.TextStyle(FAppStyle::Get(), InArgs._Important ? "SCSEditor.ComponentTooltip.ImportantValue" : "SCSEditor.ComponentTooltip.Value")
			.Text(InArgs._Value)
		]
	];
}

TSharedRef<SToolTip> SOverlayComponentTreeViewRowWidget::CreateTooltipWidget() const {
	const UActorComponent* ComponentTemplate = ComponentData->GetImmutableActorComponentTemplate();
	const TSharedRef<SVerticalBox> InfoBox = SNew(SVerticalBox);

	// Add the tooltip for the component class
	if (ComponentTemplate != nullptr) {
		const UClass* TemplateClass = ComponentTemplate->GetClass();
		const FText ClassTooltip = TemplateClass->GetToolTipText(true);

		InfoBox->AddSlot().AutoHeight().HAlign(HAlign_Center).Padding(FMargin(0.0f, 2.0f, 0.0f, 4.0f)) [
			SNew(STextBlock)
			.TextStyle(FAppStyle::Get(), "SCSEditor.ComponentTooltip.ClassDescription")
			.Text(ClassTooltip)
			.WrapTextAt(400.0f)
		];
	}

	// Add tooltip specifying whenever this component is editable or not
	InfoBox->AddSlot().AutoHeight().Padding(0.0f, 1.0f) [
		SNew(SOverlayComponentTooltipBlock)
		.Key(LOCTEXT("TooltipEditableComponent", "Editable"))
		.Value(this, &SOverlayComponentTreeViewRowWidget::GetComponentEditableTooltipText)
		.Important(true)
	];

	// Add mobility tooltip if this is a scene component
	if (ComponentTemplate != nullptr && ComponentTemplate->IsA<USceneComponent>()) {
		InfoBox->AddSlot().AutoHeight().Padding(0.0f, 1.0f) [
			SNew(SOverlayComponentTooltipBlock)
			.Key(LOCTEXT("TooltipComponentMobility", "Mobility"))
			.Value(this, &SOverlayComponentTreeViewRowWidget::GetMobilityToolTipText)
			.ValueIcon() [
				SNew(SImage).Image(this, &SOverlayComponentTreeViewRowWidget::GetMobilityIconImage)
			]
		];
	}

	// Add asset if applicable to this node
	if (GetAssetVisibility() == EVisibility::Visible) {
		InfoBox->AddSlot() [
			SNew(SSpacer).Size(FVector2D(1.0f, 8.0f))
		];
		InfoBox->AddSlot().AutoHeight().Padding(0.0f, 1.0f) [
			SNew(SOverlayComponentTooltipBlock)
			.Key(LOCTEXT("TooltipComponentAsset", "Asset"))
			.Value(this, &SOverlayComponentTreeViewRowWidget::GetAssetName)
		];
	}

	// If the component is marked as editor only, then display that info here
	InfoBox->AddSlot().AutoHeight().Padding(0.0f, 1.0f) [
		SNew(SOverlayComponentTooltipBlock)
		.Key(LOCTEXT("TooltipComponentEditorOnly", "Editor Only"))
		.Value(this, &SOverlayComponentTreeViewRowWidget::GetComponentEditorOnlyTooltipText)
	];

	return SNew(SToolTip)
	.BorderImage( FCoreStyle::Get().GetBrush("ToolTip.BrightBackground") )
	.TextMargin(FMargin(11.0f))
	.Content() [
		SNew(SVerticalBox)
		+SVerticalBox::Slot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 4.0f) [
			SNew(SVerticalBox)
			+SVerticalBox::Slot().AutoHeight() [
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(2.0f) [
					SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), "SCSEditor.ComponentTooltip.Title")
					.Text(this, &SOverlayComponentTreeViewRowWidget::GetTooltipText)
				]
			]
		]
		+SVerticalBox::Slot().AutoHeight() [
			SNew(SBorder).BorderImage(FAppStyle::GetBrush("NoBorder")).Padding(2.0f) [
				InfoBox
			]
		]
	];
}

FText SOverlayComponentTreeViewRowWidget::GetTooltipText() const {
	const UActorComponent* ComponentTemplate = ComponentData->GetImmutableActorComponentTemplate();
	const UClass* Class = ComponentTemplate ? ComponentTemplate->GetClass() : nullptr;
	const FText ClassDisplayName = FBlueprintEditorUtils::GetFriendlyClassDisplayName(Class);

	return FText::Format(LOCTEXT("ComponentTooltip", "{0} ({1})"), ClassDisplayName, ComponentData->GetNameLabel());
}

void SOverlayComponentTreeViewRowWidget::HandleOnDragEnter(const FDragDropEvent& DragDropEvent) {
	const TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();
	const TSharedPtr<SOverlayComponentTreeEditor> PinnedOwnerTreeEditor = OwnerTreeOverlay.Pin();

	// Exit early if operation or our owner are not valid
	if (!Operation.IsValid() || !PinnedOwnerTreeEditor.IsValid()) {
		return;
	}

	// If this is a drag and drop action from another node, evaluate its payload to determine which action dropping it on this node would result in
	if (const TSharedPtr<FOverlayComponentTreeRowDragDropOp> DragRowOp = DragDropEvent.GetOperationAs<FOverlayComponentTreeRowDragDropOp>()) {
		// Evaluate the selected nodes, and stop once one of them fails to attach
		FText FeedbackMessage;
		for (const TSharedPtr<FOverlayComponentData>& SelectedNodeData : DragRowOp->SourceNodes) {
			DragRowOp->PendingDropAction = CheckCanAttachSelectedNodeToNode(SelectedNodeData, ComponentData, FeedbackMessage);
			if (DragRowOp->PendingDropAction == FOverlayComponentTreeRowDragDropOp::DropAction_None) {
				break;
			}
		}

		// If we have a pending operation, the drop can be performed, otherwise, it is not allowed
		const FSlateBrush* StatusSymbol = DragRowOp->PendingDropAction != FOverlayComponentTreeRowDragDropOp::DropAction_None
				? FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.OK"))
				: FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.Error"));
		if (FeedbackMessage.IsEmpty()) {
			DragRowOp->SetFeedbackMessage(nullptr);
		} else {
			DragRowOp->SetSimpleFeedbackMessage(StatusSymbol, FLinearColor::White, FeedbackMessage);
		}
	}
	// Let the tree handle the external drag operations and asset dragging
	else if (Operation->IsOfType<FExternalDragOperation>() || Operation->IsOfType<FAssetDragDropOp>()) {
		if (const TSharedPtr<SOverlayComponentTreeView>& ComponentTree = PinnedOwnerTreeEditor->GetComponentTree()) {
			ComponentTree->OnDragEnter(FGeometry(), DragDropEvent);
		}
	}
}

void SOverlayComponentTreeViewRowWidget::HandleOnDragLeave(const FDragDropEvent& DragDropEvent) {
	// Cleanup the pending drop action once the operation leaves this widget
	if (const TSharedPtr<FOverlayComponentTreeRowDragDropOp> DragRowOp = DragDropEvent.GetOperationAs<FOverlayComponentTreeRowDragDropOp>()) {
		const TSharedPtr<SWidget> NoWidget;
		DragRowOp->SetFeedbackMessage(NoWidget);
		DragRowOp->PendingDropAction = FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
}

FReply SOverlayComponentTreeViewRowWidget::HandleOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
	const TSharedPtr<SOverlayComponentTreeEditor> PinnedOwnerTreeOverlay = OwnerTreeOverlay.Pin();
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && PinnedOwnerTreeOverlay.IsValid() && PinnedOwnerTreeOverlay->IsEditingAllowed()) {
		TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = PinnedOwnerTreeOverlay->GetSelectedNodes();
		if (SelectedNodes.Num() == 0) {
			SelectedNodes.Add(ComponentData);
		}

		// Begin the drag and drop operation with no set action and selected nodes as payload
		const TSharedRef<FOverlayComponentTreeRowDragDropOp> Operation = FOverlayComponentTreeRowDragDropOp::Create(SelectedNodes);
		return FReply::Handled().BeginDragDrop(Operation);
    }
	return FReply::Unhandled();
}

TOptional<EItemDropZone> SOverlayComponentTreeViewRowWidget::HandleOnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, const TSharedPtr<FOverlayComponentData> TargetItem) {
	if (const TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation()) {
		// If we have a valid drag and drop operation set for this action, drop it onto this item
		if (Operation->IsOfType<FOverlayComponentTreeRowDragDropOp>()) {
			const TSharedPtr<FOverlayComponentTreeRowDragDropOp> DragRowOp = StaticCastSharedPtr<FOverlayComponentTreeRowDragDropOp>(Operation);
			if (DragRowOp->PendingDropAction != FOverlayComponentTreeRowDragDropOp::DropAction_None) {
				return EItemDropZone::OntoItem;
			}
		}
		// Assume that component overlay tree will handle all the external and asset drag operations
		else if (Operation->IsOfType<FExternalDragOperation>() || Operation->IsOfType<FAssetDragDropOp>()) {
			return EItemDropZone::OntoItem;
		}
	}
	return TOptional<EItemDropZone>();
}

FReply SOverlayComponentTreeViewRowWidget::HandleOnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FOverlayComponentData> TargetItem) {
	const TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();
	const TSharedPtr<SOverlayComponentTreeEditor> PinnedTreeEditor = OwnerTreeOverlay.Pin();
	if (!Operation.IsValid() || !PinnedTreeEditor.IsValid()) {
		return FReply::Handled();
	}

	// If this is a component drag and drop operation with a defined action, forward it to the tree overlay to perform the operation in question
	if (Operation->IsOfType<FOverlayComponentTreeRowDragDropOp>()) {
		const TSharedPtr<FOverlayComponentTreeRowDragDropOp> DragRowOp = StaticCastSharedPtr<FOverlayComponentTreeRowDragDropOp>(Operation);	
		switch(DragRowOp->PendingDropAction) {
			case FOverlayComponentTreeRowDragDropOp::DropAction_AttachTo: PinnedTreeEditor->OnAttachToDropAction(ComponentData, DragRowOp->SourceNodes); break;
			case FOverlayComponentTreeRowDragDropOp::DropAction_DetachFrom: PinnedTreeEditor->OnDetachFromDropAction(DragRowOp->SourceNodes); break;
			default: break;
		}
	}
	// Let the component tree handle the external drag operations and asset dragging
	else if (Operation->IsOfType<FExternalDragOperation>() || Operation->IsOfType<FAssetDragDropOp>()) {
		if (const TSharedPtr<SOverlayComponentTreeView>& ComponentTree = PinnedTreeEditor->GetComponentTree()) {
			ComponentTree->OnDrop(FGeometry(), DragDropEvent);
		}
	}
	return FReply::Handled();
}

void SOverlayComponentTreeSeparatorRowWidget::Construct(const FArguments&, const TSharedPtr<STableViewBase>& InOwnerTableView) {
	const FSuperRowType::FArguments Args = FSuperRowType::FArguments()
		.Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.NoHoverTableRow"))
		.Padding(FMargin(0.0f, 4.0f, 0.0f, 4.0f))
		.ShowSelection(false);
	SMultiColumnTableRow::Construct(Args, InOwnerTableView.ToSharedRef());
}

TSharedRef<SWidget> SOverlayComponentTreeSeparatorRowWidget::GenerateWidgetForColumn(const FName& ColumnName) {
	return SNew(SBox).Padding(1.0f) [
		SNew(SSeparator)
		.SeparatorImage(FAppStyle::Get().GetBrush("Menu.Separator"))
		.Thickness(1.0f)
	];
}

void SOverlayComponentTreeEditor::Construct(const FArguments& InArgs, const TSharedPtr<FHookBlueprintEditor>& InOwnerBlueprintEditor) {
	OwnerBlueprintEditor = InOwnerBlueprintEditor;

	RegisterEditorCommands();
	RefreshComponentTreeFromBlueprint();

	// Create header row to generate the tree hierarchy
	const TSharedPtr<SHeaderRow> HeaderRow = SNew(SHeaderRow)
		+SHeaderRow::Column(TEXT("ComponentName")).DefaultLabel(LOCTEXT("OverlayTreeHeaderColumn_ComponentName", "Component")).FillWidth(4.0f);

	ChildSlot [
		SNew(SVerticalBox)
		+SVerticalBox::Slot().AutoHeight().VAlign(VAlign_Top).Padding(4.0f, 0.0f, 4.0f, 4.0f) [
			SNew(SVerticalBox)
			+SVerticalBox::Slot().VAlign(VAlign_Center).AutoHeight() [
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().VAlign(VAlign_Center).Padding(0.0f, 0.0f, 4.0f, 0.0f).AutoWidth() [
					SNew(SComponentClassCombo)
					.OnSubobjectClassSelected(this, &SOverlayComponentTreeEditor::PerformComboAddClass)
					.ToolTipText(LOCTEXT("AddOverlayComponent_Tooltip", "Adds a new component to the target Blueprint Component Tree"))
					.IsEnabled(true)
				]
			]
		]
		+SVerticalBox::Slot() [
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("SCSEditor.Background"))
			.Padding(4.0f) [
				SAssignNew(ComponentTreeView, SOverlayComponentTreeView, SharedThis(this))
				.ToolTipText(LOCTEXT("DropAssetToAddComponent", "Drop asset here to add a component."))
				.TreeItemsSource(&RootNodes)
				.SelectionMode(ESelectionMode::Multi)
				.OnGenerateRow(this, &SOverlayComponentTreeEditor::MakeTableRowWidget)
				.OnGetChildren(this, &SOverlayComponentTreeEditor::OnGetChildrenForTree)
				.OnSetExpansionRecursive(this, &SOverlayComponentTreeEditor::SetItemExpansionRecursive)
				.OnSelectionChanged(this, &SOverlayComponentTreeEditor::OnTreeSelectionChanged)
				// TODO: Create context menu later.
				//.OnContextMenuOpening(this, &SOverlayComponentTreeEditor::CreateContextMenu)
				.OnItemScrolledIntoView(this, &SOverlayComponentTreeEditor::OnItemScrolledIntoView)
				.ClearSelectionOnClick(true)
				.HighlightParentNodesForSelection(true)
				.ItemHeight(24)
				.HeaderRow(HeaderRow)
			]
		]
	];
	HeaderRow->SetVisibility(EVisibility::Collapsed);

	// Expand all default nodes in the current tree
	for (const TSharedPtr<FOverlayComponentData>& ComponentNode : AllNodes) {
		ComponentTreeView->SetItemExpansion(ComponentNode, true);
	}
}

FReply SOverlayComponentTreeEditor::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) {
	// Process generic keyboard actions from commands (like copy and paste)
	if (CommandList->ProcessCommandBindings(InKeyEvent)) {
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

void SOverlayComponentTreeEditor::RegisterEditorCommands() {
	CommandList = MakeShared<FUICommandList>();

	CommandList->MapAction(FGenericCommands::Get().Delete,
		FUIAction(FExecuteAction::CreateSP(this, &SOverlayComponentTreeEditor::OnDeleteNodes),
		FCanExecuteAction::CreateSP(this, &SOverlayComponentTreeEditor::CanDeleteNodes))
	);
	CommandList->MapAction(FGenericCommands::Get().Rename,
		FUIAction(FExecuteAction::CreateSP(this, &SOverlayComponentTreeEditor::OnRenameComponent),
		FCanExecuteAction::CreateSP(this, &SOverlayComponentTreeEditor::CanRenameComponent))
	);
	CommandList->MapAction(FGraphEditorCommands::Get().GetFindReferences(),
		FUIAction(FExecuteAction::CreateSP(this, &SOverlayComponentTreeEditor::OnFindReferences))
	);
}

void SOverlayComponentTreeEditor::RefreshComponentTreeFromBlueprint() {
	// Retrieve the current hook blueprint we are editing
	const UHookBlueprint* BlueprintObject = nullptr;
	if (const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin()) {
		BlueprintObject = Cast<UHookBlueprint>(BlueprintEditor->GetBlueprintObj());
	}

	// Cache a list of all nodes that we had prior to this point
	const TArray<TSharedPtr<FOverlayComponentData>> AllNodesOld = AllNodes;
	const TMap<TWeakObjectPtr<const UObject>, TSharedPtr<FOverlayComponentData>> OldObjectToComponentLookup = ObjectToComponentDataCache;
	
	// Wipe hierarchy data from the nodes that we might want to keep around
	for (const TSharedPtr<FOverlayComponentData>& OldNodeObject : AllNodesOld) {
		OldNodeObject->ClearHierarchyData();
	}

	// Clean up the current list of nodes and the current node cache
	RootNodes.Empty();
	AllNodes.Empty();
	ObjectToComponentDataCache.Empty();

	// We cannot populate new set of nodes without a valid blueprint or without a valid target class
	if (BlueprintObject == nullptr || BlueprintObject->MixinTargetClass == nullptr) {
		return;
	}
	UBlueprintGeneratedClass* ActualBlueprintGeneratedClass = BlueprintObject->MixinTargetClass;

	// Retrieve a list of native components registered on the actor
	TArray<UActorComponent*> DefaultNativeComponents;
	if (const AActor* DefaultActorObject = BlueprintObject->MixinTargetClass->GetDefaultObject<AActor>()) {
		DefaultActorObject->GetComponents(DefaultNativeComponents);
	}
	
	// Create nodes for native actor components
	TMap<FName, TSharedPtr<FOverlayComponentData>> NativeComponentNameToComponentData;
	for (const UActorComponent* NativeActorComponent : DefaultNativeComponents) {
		TSharedPtr<FOverlayComponentData> NodeComponentData;

		// Attempt to find an existing component node for this node
		if (const TSharedPtr<FOverlayComponentData>* ExistingComponentData = OldObjectToComponentLookup.Find(NativeActorComponent)) {
			NodeComponentData = *ExistingComponentData;
		} else {
			// Create a new component data otherwise
			NodeComponentData = MakeShared<FImmutableNativeComponentData>(ActualBlueprintGeneratedClass, NativeActorComponent);
		}
		// Add the node to the all nodes list and the node to the tree node mapping
		AllNodes.Add(NodeComponentData);
		ObjectToComponentDataCache.Add(NativeActorComponent, NodeComponentData);
		NativeComponentNameToComponentData.Add(NativeActorComponent->GetFName(), NodeComponentData);
	}

	// Setup attachments between native components. Native components will never be attached to SCS components
	for (const UActorComponent* NativeActorComponent : DefaultNativeComponents) {
		const TSharedPtr<FOverlayComponentData> NativeComponentData = ObjectToComponentDataCache.FindChecked(NativeActorComponent); 

		// If this is a scene component that has an attachment parent we have registered, add it as a child to that component
		const USceneComponent* NativeSceneComponent = Cast<USceneComponent>(NativeActorComponent);
		if (NativeSceneComponent != nullptr && NativeSceneComponent->GetAttachParent() && ObjectToComponentDataCache.Contains(NativeSceneComponent->GetAttachParent())) {
			const TSharedPtr<FOverlayComponentData> ParentComponentData = ObjectToComponentDataCache.FindChecked(NativeSceneComponent->GetAttachParent());
			ParentComponentData->AddChildNode(NativeComponentData);
		} else {
			// Add this component to the root set otherwise since it has no attachment parent
			RootNodes.Add(NativeComponentData);
		}
	}

	// Create a hierarchy of construction scripts from the most base one to the most derived one
	TArray<USimpleConstructionScript*> SimpleConstructionScriptHierarchy;
	UBlueprintGeneratedClass* CurrentParentClass = ActualBlueprintGeneratedClass;
	while (CurrentParentClass != nullptr) {
		if (USimpleConstructionScript* SimpleConstructionScript = CurrentParentClass->SimpleConstructionScript) {
			SimpleConstructionScriptHierarchy.Add(SimpleConstructionScript);
		}
		CurrentParentClass = Cast<UBlueprintGeneratedClass>(CurrentParentClass->GetSuperClass());
	}
	Algo::Reverse(SimpleConstructionScriptHierarchy);
	
	// Create nodes or reuse existing nodes from the SCS
	TMap<TPair<FName, FName>, TSharedPtr<FOverlayComponentData>> BlueprintSCSComponentKeyToComponentData;
	for (const USimpleConstructionScript* SimpleConstructionScript : SimpleConstructionScriptHierarchy) {

		// Create component data for each component node in the construction script
		for (const USCS_Node* ComponentTreeNode : SimpleConstructionScript->GetAllNodes()) {
			TSharedPtr<FOverlayComponentData> NodeComponentData;

			// Attempt to find an existing component node for this node
			if (const TSharedPtr<FOverlayComponentData>* ExistingComponentData = OldObjectToComponentLookup.Find(ComponentTreeNode)) {
				NodeComponentData = *ExistingComponentData;
			} else {
				// Create a new component data otherwise
				NodeComponentData = MakeShared<FImmutableSCSNodeComponentData>(ActualBlueprintGeneratedClass, ComponentTreeNode);
			}
			
			// Add the node to the all nodes list and the node to the tree node mapping
			AllNodes.Add(NodeComponentData);
			ObjectToComponentDataCache.Add(ComponentTreeNode, NodeComponentData);

			// Map the component using its class name and variable name, this is how child SCS components can refer to parent SCS components
			const FName OwnerClassFName = SimpleConstructionScript->GetOwnerClass()->GetFName();
			BlueprintSCSComponentKeyToComponentData.Add({OwnerClassFName, ComponentTreeNode->GetVariableName()}, NodeComponentData);
		}

		// Add children nodes to the SCS nodes that we have added above. Note that we will not handle nodes parented to native components here.
		for (const USCS_Node* ParentComponentTreeNode : SimpleConstructionScript->GetAllNodes()) {
			const TSharedPtr<FOverlayComponentData> ParentComponentData = ObjectToComponentDataCache.FindChecked(ParentComponentTreeNode);
			
			for (const USCS_Node* ChildComponentTreeNode : ParentComponentTreeNode->ChildNodes) {
				const TSharedPtr<FOverlayComponentData> ChildComponentData = ObjectToComponentDataCache.FindChecked(ChildComponentTreeNode);
				ParentComponentData->AddChildNode(ChildComponentData);
			}
		}

		// Add root nodes into the tree, or add SCS components as children of native components
		for (const USCS_Node* RootTreeNode : SimpleConstructionScript->GetRootNodes()) {
			const TSharedPtr<FOverlayComponentData> ComponentData = ObjectToComponentDataCache.FindChecked(RootTreeNode);

			// If this component node has a parent name, we need to resolve it using the previously created nodes from the native class or from a parent blueprint
			if(RootTreeNode->ParentComponentOrVariableName != NAME_None) {

				// If this is a native component, we can look it up using its name
				if (RootTreeNode->bIsParentComponentNative) {
					if (NativeComponentNameToComponentData.Contains(RootTreeNode->ParentComponentOrVariableName)) {
						const TSharedPtr<FOverlayComponentData> ParentComponentData = NativeComponentNameToComponentData.FindChecked(RootTreeNode->ParentComponentOrVariableName);
						ParentComponentData->AddChildNode(ComponentData);
						continue;
					}
				} else {
					// We have to look it up using the parent BP class name and the name of the component variable otherwise
					const TPair<FName, FName> ParentComponentKey{RootTreeNode->ParentComponentOwnerClassName, RootTreeNode->ParentComponentOrVariableName};
					if (BlueprintSCSComponentKeyToComponentData.Contains(ParentComponentKey)) {
						const TSharedPtr<FOverlayComponentData> ParentComponentData = BlueprintSCSComponentKeyToComponentData.FindChecked(ParentComponentKey);
						ParentComponentData->AddChildNode(ComponentData);
						continue;
					}
				}
			}
			// This component does not have a parent component/variable name (or it is invalid), so just add it to the root node set
			RootNodes.Add(ComponentData);
		}
	}

	// Create nodes for the overlay this blueprint applies on top of the target blueprint
	if (BlueprintObject->OverlayComponentTree != nullptr) {
		// Create component data for each component node in the overlay component tree
		for (const UBlueprintMixinComponentNode* ComponentTreeNode : BlueprintObject->OverlayComponentTree->AllNodes) {
			TSharedPtr<FOverlayComponentData> NodeComponentData;

			// Attempt to find an existing component node for this node
			if (const TSharedPtr<FOverlayComponentData>* ExistingComponentData = OldObjectToComponentLookup.Find(ComponentTreeNode)) {
				NodeComponentData = *ExistingComponentData;
			} else {
				// Create a new component data otherwise
				NodeComponentData = MakeShared<FMutableMixinComponentNodeData>(ComponentTreeNode);
			}
			// Add the node to the all nodes list and the node to the tree node mapping
			AllNodes.Add(NodeComponentData);
			ObjectToComponentDataCache.Add(ComponentTreeNode, NodeComponentData);
		}

		// Setup hierarchy for the nodes we have created
		for (const UBlueprintMixinComponentNode* ParentComponentTreeNode : BlueprintObject->OverlayComponentTree->AllNodes) {
			const TSharedPtr<FOverlayComponentData> ParentComponentData = ObjectToComponentDataCache.FindChecked(ParentComponentTreeNode);
			
			// Register all child components into their parent tree
			for (const UBlueprintMixinComponentNode* ChildComponentTreeNode : ParentComponentTreeNode->ChildNodes) {
				const TSharedPtr<FOverlayComponentData> ChildComponentData = ObjectToComponentDataCache.FindChecked(ChildComponentTreeNode);
				ParentComponentData->AddChildNode(ChildComponentData);
			}
		}

		// Add all the overlay component root nodes into the tree
		for (const UBlueprintMixinComponentNode* RootTreeNode : BlueprintObject->OverlayComponentTree->RootNodes) {
			const TSharedPtr<FOverlayComponentData> ComponentData = ObjectToComponentDataCache.FindChecked(RootTreeNode);
			
			// If this component node has a parent name, we need to resolve it using the previously created nodes from the native class or from a parent blueprint
			if(RootTreeNode->ParentComponentOrVariableName != NAME_None) {
				// If this is a native component, we can look it up using its name
				if (RootTreeNode->bIsParentComponentNative) {
					if (NativeComponentNameToComponentData.Contains(RootTreeNode->ParentComponentOrVariableName)) {
						const TSharedPtr<FOverlayComponentData> ParentComponentData = NativeComponentNameToComponentData.FindChecked(RootTreeNode->ParentComponentOrVariableName);
						ParentComponentData->AddChildNode(ComponentData);
						continue;
					}
				} else {
					// We have to look it up using the parent BP class name and the name of the component variable otherwise
					const TPair<FName, FName> ParentComponentKey{RootTreeNode->ParentComponentOwnerClassName, RootTreeNode->ParentComponentOrVariableName};
					if (BlueprintSCSComponentKeyToComponentData.Contains(ParentComponentKey)) {
						const TSharedPtr<FOverlayComponentData> ParentComponentData = BlueprintSCSComponentKeyToComponentData.FindChecked(ParentComponentKey);
						ParentComponentData->AddChildNode(ComponentData);
						continue;
					}
				}
			}
			// This component does not have a parent component/variable name (or it is invalid), so just add it to the root node set
			RootNodes.Add(ComponentData);
		}
	}
}

bool SOverlayComponentTreeEditor::IsEditingAllowed() const {
	// Editing allowed if the blueprint editor is in the editing mode, e.g. no PIE session is running
	if (const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin()) {
		return BlueprintEditor->InEditingMode();
	}
	return false;
}

TArray<TSharedPtr<FOverlayComponentData>> SOverlayComponentTreeEditor::GetSelectedNodes() const {
	TArray<TSharedPtr<FOverlayComponentData>> SelectedTreeNodes = ComponentTreeView->GetSelectedItems();

	// Sort the nodes from the parent to the child
	SelectedTreeNodes.StableSort([](const TSharedPtr<FOverlayComponentData>& A, const TSharedPtr<FOverlayComponentData>& B) {
		return B.IsValid() && B->IsAttachedToParent(A);
	});
	return SelectedTreeNodes;
}

TSharedRef<ITableRow> SOverlayComponentTreeEditor::MakeTableRowWidget(TSharedPtr<FOverlayComponentData> InNodePtr, const TSharedRef<STableViewBase>& OwnerTable) {
	// Create row widget for normal nodes and separator widget for null nodes
	if (InNodePtr.IsValid()) {
		return SNew(SOverlayComponentTreeViewRowWidget, SharedThis(this), InNodePtr, OwnerTable);	
	}
	return SNew(SOverlayComponentTreeSeparatorRowWidget, OwnerTable);
}

void SOverlayComponentTreeEditor::OnGetChildrenForTree(const TSharedPtr<FOverlayComponentData> InNodePtr, TArray<TSharedPtr<FOverlayComponentData>>& OutChildren) {
	// Populate the children nodes using the function on the component data
	if (InNodePtr) {
		InNodePtr->GetChildrenNodes(OutChildren);
	}
}

void SOverlayComponentTreeEditor::SetItemExpansionRecursive(const TSharedPtr<FOverlayComponentData> InNodeToChange, bool bInExpansionState) {
	if (ComponentTreeView.IsValid() && InNodeToChange.IsValid()) {
		// Expand the provided item
		ComponentTreeView->SetItemExpansion(InNodeToChange, bInExpansionState);

		// Retrieve the children of the provided item and expand them too
		TArray<TSharedPtr<FOverlayComponentData>> Children;
		InNodeToChange->GetChildrenNodes(Children);
		for (const TSharedPtr<FOverlayComponentData>& Child : Children) {
			SetItemExpansionRecursive(Child, bInExpansionState);
		}
	}
}

void SOverlayComponentTreeEditor::UpdateSelectionFromNodes(const TArray<TSharedPtr<FOverlayComponentData>>& SelectedNodes) {
	if (const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin()) {
		// Collect all objects from the nodes that we want to edit
		TArray<UObject*> ComponentObjectsToEdit;
		FText InspectorTitle;
		for (const TSharedPtr<FOverlayComponentData>& ComponentData : SelectedNodes) {
			if (ComponentData->IsNodeEditable()) {
				if (UActorComponent* EditableActorComponent = ComponentData->GetMutableActorComponentTemplate()) {
					ComponentObjectsToEdit.Add(EditableActorComponent);
					InspectorTitle = ComponentData->GetNameLabel();
				}
			}
		}

		// Show the inspector with the new selection if we have any valid objects
		if (!ComponentObjectsToEdit.IsEmpty()) {
			SKismetInspector::FShowDetailsOptions DetailsOptions(InspectorTitle, true);
			DetailsOptions.bShowComponents = false;
			BlueprintEditor->GetInspector()->ShowDetailsForObjects(ComponentObjectsToEdit, DetailsOptions);
		}

		// Push the selection to the components on the overlay tree preview actor
		if (const AActor* OverlayPreviewActor = BlueprintEditor->GetOverlayPreviewActor()) {
			for (UActorComponent* Component : OverlayPreviewActor->GetComponents()) {
				if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component)) {
					PrimitiveComponent->PushSelectionToProxy();
				}
			}
		}
	}
}

void SOverlayComponentTreeEditor::OnTreeSelectionChanged(TSharedPtr<FOverlayComponentData>, ESelectInfo::Type) {
	// Update the details panel state from a list of the selected nodes
	UpdateSelectionFromNodes(ComponentTreeView->GetSelectedItems());
}

void SOverlayComponentTreeEditor::OnItemScrolledIntoView(TSharedPtr<FOverlayComponentData> InItem, const TSharedPtr<ITableRow>& InWidget) {
	// If we have a component rename pending, once the component is scrolled into the view, we need to start the edit mode on the name label
	if (PendingRenameComponentData.IsValid() && PendingRenameComponentData == InItem) {
		if (const TSharedPtr<SOverlayComponentTreeViewRowWidget> RowWidget = StaticCastSharedPtr<SOverlayComponentTreeViewRowWidget>(InWidget)) {
			RowWidget->StartEditingComponentName();
		}
		PendingRenameComponentData.Reset();
	}
}

FReply SOverlayComponentTreeEditor::TryHandleAssetDragNDropOperation(const FDragDropEvent& DragDropEvent) {
	// Check that the drag event is of the supported type
	const TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();
	if (!Operation.IsValid() || (!Operation->IsOfType<FExternalDragOperation>() && !Operation->IsOfType<FAssetDragDropOp>())) {
		return FReply::Unhandled();
	}

	// Iterate all assets contained in the drop action and attempt to create components from them
	const FScopedTransaction ScopedTransaction(LOCTEXT("Transaction_CreateComponentsFromAssets", "Create Components from Assets"));
	TArray<FAssetData> DroppedAssetData = AssetUtil::ExtractAssetDataFromDrag(Operation);

	for (int32 DroppedAssetIdx = 0; DroppedAssetIdx < DroppedAssetData.Num(); ++DroppedAssetIdx) {
		const FAssetData& AssetData = DroppedAssetData[DroppedAssetIdx];

		UClass* AssetClass = AssetData.GetClass();
		UObject* Asset = AssetData.GetAsset();
		const UBlueprint* BPClass = Cast<UBlueprint>(Asset);

		// Determine the class of the potential component that we are about to create
		UClass* PotentialComponentClass = nullptr;
		if (BPClass != nullptr && BPClass->GeneratedClass != nullptr) {
			if (BPClass->GeneratedClass->IsChildOf(UActorComponent::StaticClass())) {
				PotentialComponentClass = BPClass->GeneratedClass;
			}
		}
		else if (AssetClass && AssetClass->IsChildOf(UClass::StaticClass())){
			UClass* AssetAsClass = CastChecked<UClass>(Asset);
			if (AssetAsClass->IsChildOf(UActorComponent::StaticClass())) {
				PotentialComponentClass = AssetAsClass;
			}
		}

		// If we can look up a component class for the provided asset class, use that component class with the asset override
		if (TSubclassOf<UActorComponent> MatchingComponentClassForAsset = FComponentAssetBrokerage::GetPrimaryComponentForAsset(AssetClass)) {
			CreateComponentFromClass(MatchingComponentClassForAsset, Asset, nullptr);
		}
		// Otherwise, just create a new component from the provided class
		else if (PotentialComponentClass != nullptr && !PotentialComponentClass->HasAnyClassFlags(CLASS_Deprecated | CLASS_Abstract | CLASS_NewerVersionExists)) {
			if (PotentialComponentClass->HasMetaData(FBlueprintMetadata::MD_BlueprintSpawnableComponent)) {
				CreateComponentFromClass(PotentialComponentClass, nullptr, nullptr);
			}
		}
	}
	return FReply::Handled();
}

FSubobjectDataHandle SOverlayComponentTreeEditor::PerformComboAddClass(TSubclassOf<UActorComponent> ComponentClass, EComponentCreateAction::Type ComponentCreateAction, UObject* AssetOverride) {
	// We do not support the creation of C++ classes and new blueprints from the overlay editor
	if (ComponentCreateAction == EComponentCreateAction::CreateNewCPPClass) {
		FMessageDialog::Open(EAppMsgCategory::Info, EAppMsgType::Ok, LOCTEXT("CannotCreateCPPClassFromOverlayEditor", "To create a new C++ class, use Tools menu or create new files through your IDE manually."));
		return FSubobjectDataHandle::InvalidHandle;
	}
	if (ComponentCreateAction == EComponentCreateAction::CreateNewBlueprintClass) {
		FMessageDialog::Open(EAppMsgCategory::Info, EAppMsgType::Ok, LOCTEXT("CannotCreateBPClassFromOverlayEditor", "To create a new Blueprint Asset, right click in the Content Browser and select Blueprint as the Asset type."));
		return FSubobjectDataHandle::InvalidHandle;
	}

	// This delegate does not actually require you to return the component, and the return value is not used in any way
	if (ComponentClass) {
		const FScopedTransaction ScopedTransaction(LOCTEXT("Transaction_CreateNewComponentFromClass", "Create New Component"));
		CreateComponentFromClass(ComponentClass, AssetOverride, nullptr);
	}
	return FSubobjectDataHandle::InvalidHandle;
}

TSharedPtr<FOverlayComponentData> SOverlayComponentTreeEditor::FindComponentDataForComponentInstance(const UActorComponent* InPreviewComponent) const {
	for (const TSharedPtr<FOverlayComponentData>& PotentialComponentNode : AllNodes) {
		if (InPreviewComponent->CreationMethod == EComponentCreationMethod::Native && InPreviewComponent->ComponentHasTag(UBlueprintMixinOverlayComponentTree::OverlayComponentTag)) {
			if (const TSharedPtr<FMutableMixinComponentNodeData> MixinComponentNode = PotentialComponentNode->GetAs<FMutableMixinComponentNodeData>()) {
				// This is the node we are looking for if the variable name matches the component name
				const UBlueprintMixinComponentNode* ComponentNode = MixinComponentNode->GetComponentNode();
				if (ComponentNode && ComponentNode->ComponentName == InPreviewComponent->GetFName()) {
					return MixinComponentNode;
				}
			}
		} else if (InPreviewComponent->CreationMethod == EComponentCreationMethod::SimpleConstructionScript) {
			if (const TSharedPtr<FImmutableSCSNodeComponentData> SCSComponentNode = PotentialComponentNode->GetAs<FImmutableSCSNodeComponentData>()) {
				// This is the node we are looking for if the variable name matches the component name
				const USCS_Node* SCSNode = SCSComponentNode->GetSCSNode();
				if (SCSNode && SCSNode->GetVariableName() == InPreviewComponent->GetFName()) {
					return SCSComponentNode;
				}
			}
		} else if (InPreviewComponent->CreationMethod == EComponentCreationMethod::Native) {
			if (const TSharedPtr<FImmutableNativeComponentData> ImmutableNativeComponentNode = PotentialComponentNode->GetAs<FImmutableNativeComponentData>()) {
				// We could also check for RF_ClassDefaultSubobject on the preview component here
				const UActorComponent* NativeComponentTemplate = ImmutableNativeComponentNode->GetImmutableActorComponentTemplate();
				if (NativeComponentTemplate && NativeComponentTemplate->GetFName() == InPreviewComponent->GetFName() && InPreviewComponent->GetClass() == NativeComponentTemplate->GetClass()) {
					return ImmutableNativeComponentNode;
				}
			}
		}
	}
	return nullptr;
}

UActorComponent* SOverlayComponentTreeEditor::FindComponentInstanceInActor(AActor* InActor, const TSharedPtr<FOverlayComponentData>& InComponentData) const {
	if (const TSharedPtr<FMutableMixinComponentNodeData> MixinComponentNode = InComponentData->GetAs<FMutableMixinComponentNodeData>()) {
		// Overlay components have stable full names and an additional tag that identifies them
		if (const UBlueprintMixinComponentNode* ComponentNode = MixinComponentNode->GetComponentNode()) {
			TArray<UActorComponent*> AllActorComponents;
			InActor->GetComponents(AllActorComponents);

			// Look for a component that has a mixin tag and a matching fully qualified name
			for (UActorComponent* ActorComponent : AllActorComponents) {
				if (ActorComponent->ComponentHasTag(UBlueprintMixinOverlayComponentTree::OverlayComponentTag) && ActorComponent->GetFName() == ComponentNode->ComponentName) {
					return ActorComponent;
				}
			}
		}
	}
	// SCS nodes will assign their components to the variable name on the node, so we can retrieve that component simply by reading the property on the actor instance
	if (const TSharedPtr<FImmutableSCSNodeComponentData> SCSComponentNode = InComponentData->GetAs<FImmutableSCSNodeComponentData>()) {
		const USCS_Node* TargetComponentNode = SCSComponentNode->GetSCSNode();
		if (TargetComponentNode && TargetComponentNode->GetVariableName() != NAME_None) {
			// Read the value of the property on the actor instance
			if (const FObjectProperty* ComponentVariableProperty = FindFProperty<FObjectProperty>(InActor->GetClass(), TargetComponentNode->GetVariableName())) {
				return Cast<UActorComponent>(ComponentVariableProperty->GetObjectPropertyValue_InContainer(InActor));
			}
		}
	} else if (const TSharedPtr<FImmutableNativeComponentData> ImmutableNativeComponentNode = InComponentData->GetAs<FImmutableNativeComponentData>()) {
		// Native component nodes can be looked up simply by their name, which should always be stable
		if (const UActorComponent* NativeComponentTemplate = ImmutableNativeComponentNode->GetImmutableActorComponentTemplate()) {
			TArray<UActorComponent*> AllActorComponents;
			InActor->GetComponents(AllActorComponents);

			// Look for native component that has a matching component name
			for (UActorComponent* ActorComponent : AllActorComponents) {
				if (ActorComponent->CreationMethod == EComponentCreationMethod::Native && Cast<AActor>(ActorComponent->GetOuter()) &&
					ActorComponent->GetFName() == NativeComponentTemplate->GetFName() && ActorComponent->GetClass() == NativeComponentTemplate->GetClass()) {
					return ActorComponent;
				}
			}
		}
	}
	return nullptr;
}

void SOverlayComponentTreeEditor::SetSelectionOverrideForComponent(UPrimitiveComponent* InPreviewComponent) {
	if (InPreviewComponent != nullptr) {
		InPreviewComponent->SelectionOverrideDelegate.BindSP(this, &SOverlayComponentTreeEditor::IsComponentInstanceSelected);
	}
}

void SOverlayComponentTreeEditor::SelectNodeForComponent(const UActorComponent* InPreviewComponent, bool bIsMultiSelectActive) {
	if (const TSharedPtr<FOverlayComponentData> ComponentNode = FindComponentDataForComponentInstance(InPreviewComponent)) {
		if (bIsMultiSelectActive) {
			ComponentTreeView->SetItemSelection(ComponentNode, true);
		} else {
			ComponentTreeView->SetSelection(ComponentNode);
		}
		// Scroll the selected item into the view
		ComponentTreeView->RequestScrollIntoView(ComponentNode);
	}
}

bool SOverlayComponentTreeEditor::IsComponentInstanceSelected(const UPrimitiveComponent* InPreviewComponent) const {
	const TSharedPtr<FOverlayComponentData> ComponentNode = FindComponentDataForComponentInstance(InPreviewComponent);
	return ComponentNode && ComponentTreeView->IsItemSelected(ComponentNode);
}

void SOverlayComponentTreeEditor::OnDeleteAction(const TArray<TSharedPtr<FOverlayComponentData>>& NodesToDelete) {
	const FScopedTransaction ScopedTransaction(LOCTEXT("DeleteComponentNodesAction", "Delete Components"));
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin();
	
	// Remove nodes from their parents and move the children away
	for (const TSharedPtr<FOverlayComponentData>& ComponentData : NodesToDelete) {
		if (const TSharedPtr<const FMutableMixinComponentNodeData> MutableNodeData = ComponentData->GetAs<FMutableMixinComponentNodeData>()) {
			if (UBlueprintMixinComponentNode* ComponentNode = const_cast<UBlueprintMixinComponentNode*>(MutableNodeData->GetComponentNode())) {

				// Detach all children node of this component first
				for (UBlueprintMixinComponentNode* ChildComponentNode : ComponentNode->ChildNodes) {
					ChildComponentNode->DetachFromParent();
				}
				// Remove this node from its parent now that it does not have any children
				ComponentNode->RemoveNodeFromParent();

				// If we are presently editing the deleted component template, reset the inspector
				if (BlueprintEditor && BlueprintEditor->GetInspector()->IsSelected(ComponentNode->ComponentTemplate)) {
					BlueprintEditor->GetInspector()->ShowDetailsForSingleObject(nullptr);
				}
			}
		}
	}
	
	// Notify blueprint editor that the tree structure has changed
	BlueprintEditor->OnOverlayComponentTreeChanged();

	// Refresh the tree since we have just changed the hierarchy
	UpdateTree();
}

void SOverlayComponentTreeEditor::OnUpdateComponentNameAction(const TSharedPtr<FOverlayComponentData>& ComponentData, const FText& InNewComponentName) {
	const FScopedTransaction ScopedTransaction(LOCTEXT("RenameComponenNodesAction", "Rename Component"));
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin();

	// We do not need to refresh the tree since the tree hierarchy did not change
	if (const TSharedPtr<const FMutableMixinComponentNodeData> MutableNodeData = ComponentData->GetAs<FMutableMixinComponentNodeData>()) {
		if (UBlueprintMixinComponentNode* ComponentNode = const_cast<UBlueprintMixinComponentNode*>(MutableNodeData->GetComponentNode())) {
			const FName OldVariableName = ComponentNode->ComponentVariableName;
			ComponentNode->SetInternalVariableName(*InNewComponentName.ToString());

			// Rename all references to the component variable in this blueprint automatically
			UHookBlueprint* OwnerBlueprint = Cast<UHookBlueprint>(BlueprintEditor->GetBlueprintObj());
			if (OwnerBlueprint && ComponentNode->GetOuter() == OwnerBlueprint->OverlayComponentTree) {
				FBlueprintEditorUtils::ReplaceVariableReferences(OwnerBlueprint, OldVariableName, ComponentNode->ComponentVariableName);	
			}
		}
	}

	// Notify blueprint editor that the tree structure has changed
	BlueprintEditor->OnOverlayComponentTreeChanged();
}

void SOverlayComponentTreeEditor::OnAttachToDropAction(const TSharedPtr<FOverlayComponentData>& AttachToComponentData, const TArray<TSharedPtr<FOverlayComponentData>>& NodesToAttach) {
	const FScopedTransaction ScopedTransaction(LOCTEXT("DeleteComponentNodesAction", "Move Components"));

	// Attach the nodes to the new parent node
	for (const TSharedPtr<FOverlayComponentData>& ComponentData : NodesToAttach) {
		// Resolve the mutable component node reference
		const TSharedPtr<const FMutableMixinComponentNodeData> MutableNodeData = ComponentData->GetAs<FMutableMixinComponentNodeData>();
		if (!MutableNodeData.IsValid()) continue;

		if (UBlueprintMixinComponentNode* ComponentNode = const_cast<UBlueprintMixinComponentNode*>(MutableNodeData->GetComponentNode())) {
			AttachComponentNodeToComponentData(ComponentNode, AttachToComponentData);
		}
	}

	// Notify blueprint editor that the tree structure has changed
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin();
	BlueprintEditor->OnOverlayComponentTreeChanged();

	// Refresh the tree since we have just changed the hierarchy
	UpdateTree();
}

void SOverlayComponentTreeEditor::OnDetachFromDropAction(const TArray<TSharedPtr<FOverlayComponentData>>& NodesToAttach) {
	const FScopedTransaction ScopedTransaction(LOCTEXT("DetachComponentNodesAction", "Detach Components"));

	// Remove nodes from their parents and move the children away
	for (const TSharedPtr<FOverlayComponentData>& ComponentData : NodesToAttach) {
		if (const TSharedPtr<const FMutableMixinComponentNodeData> MutableNodeData = ComponentData->GetAs<FMutableMixinComponentNodeData>()) {
			if (UBlueprintMixinComponentNode* ComponentNode = const_cast<UBlueprintMixinComponentNode*>(MutableNodeData->GetComponentNode())) {
				ComponentNode->DetachFromParent();
			}
		}
	}

	// Notify blueprint editor that the tree structure has changed
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin();
	BlueprintEditor->OnOverlayComponentTreeChanged();

	// Refresh the tree since we have just changed the hierarchy
	UpdateTree();
}

void SOverlayComponentTreeEditor::CreateComponentFromClass(UClass* InComponentClass, UObject* InComponentAsset, UObject* InComponentTemplate) {
	// This function is assumed to run inside the transaction, so we do not open one here
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin();
	UHookBlueprint* EditedBlueprint = BlueprintEditor ? Cast<UHookBlueprint>(BlueprintEditor->GetBlueprintObj()) : nullptr;
	const TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = GetSelectedNodes();

	if (EditedBlueprint && EditedBlueprint->OverlayComponentTree && EditedBlueprint->MixinTargetClass) {
		// Generate variable name based on the component class or the asset provided
		AActor* TargetClassDefaultObject = EditedBlueprint->MixinTargetClass->GetDefaultObject<AActor>();
		FString NewComponentVariableName;
		if (InComponentAsset != nullptr) {
			NewComponentVariableName = FComponentEditorUtils::GenerateValidVariableNameFromAsset(InComponentAsset, TargetClassDefaultObject);
		} else {
			NewComponentVariableName = FComponentEditorUtils::GenerateValidVariableName(InComponentClass, TargetClassDefaultObject);
		}

		// Make sure the generated name is actually unique in the scope of our blueprint, and if it is not, adjust it
		FKismetNameValidator Validator(EditedBlueprint);
		FName UniqueComponentVariableName = *NewComponentVariableName;
		if (Validator.IsValid(UniqueComponentVariableName) != EValidatorResult::Ok) {
			UniqueComponentVariableName = FBlueprintEditorUtils::FindUniqueKismetName(EditedBlueprint, FName(*NewComponentVariableName).GetPlainNameString());
		}

		// Create the component finally usong the generated name, component class, and optionally a provided component template
		if (UBlueprintMixinComponentNode* NewComponentNode = EditedBlueprint->OverlayComponentTree->CreateNewNode(InComponentClass, UniqueComponentVariableName, Cast<UActorComponent>(InComponentTemplate))) {
			NewComponentNode->Modify();

			// Assign the asset to the component if we were provided with an asset
			if (NewComponentNode->ComponentTemplate && InComponentAsset) {
				NewComponentNode->ComponentTemplate->Modify();
                FComponentAssetBrokerage::AssignAssetToComponent(NewComponentNode->ComponentTemplate, InComponentAsset);
			}
			// Attempt to attach to the first selected node as a parent, and if we failed, just attach to the root with no parent component reference
			if (SelectedNodes.IsEmpty() || !AttachComponentNodeToComponentData(NewComponentNode, SelectedNodes[0])) {
				EditedBlueprint->OverlayComponentTree->AddRootNode(NewComponentNode);
			}
		}
		
		// Notify blueprint editor that the tree structure has changed
		BlueprintEditor->OnOverlayComponentTreeChanged();
	}
	// Refresh the tree since we have just changed the hierarchy
	UpdateTree();
}

bool SOverlayComponentTreeEditor::AttachComponentNodeToComponentData(UBlueprintMixinComponentNode* InComponentNode, const TSharedPtr<FOverlayComponentData>& InAttachToComponentData) {
	// Determine the type of the node we need to attach to set valid data
	if (const TSharedPtr<const FImmutableSCSNodeComponentData> SCSNodeComponentData = InAttachToComponentData->GetAs<FImmutableSCSNodeComponentData>()) {
		if (const USCS_Node* NewParentSCSNode = SCSNodeComponentData->GetSCSNode()) {
			return InComponentNode->AttachToSCSNode(NewParentSCSNode);
		}
	} else if (const TSharedPtr<const FImmutableNativeComponentData> NativeComponentData = InAttachToComponentData->GetAs<FImmutableNativeComponentData>()) {
		if (const UActorComponent* NewNativeParentComponent = NativeComponentData->GetImmutableActorComponentTemplate()) {
			return InComponentNode->AttachToNativeActorComponent(NewNativeParentComponent);
		}
	} else if (const TSharedPtr<const FMutableMixinComponentNodeData> NodeComponentData = InAttachToComponentData->GetAs<FMutableMixinComponentNodeData>()) {
		if (const UBlueprintMixinComponentNode* NewParentNode = NodeComponentData->GetComponentNode()) {
			return InComponentNode->AttachToNode(const_cast<UBlueprintMixinComponentNode*>(NewParentNode));
		}
	}
	return false;
}

void SOverlayComponentTreeEditor::UpdateTree() {
	// Refresh the component tree now that we have saved the selection state
	RefreshComponentTreeFromBlueprint();

	// Request the refresh of the component tree widget
	if (ComponentTreeView.IsValid()) {
		ComponentTreeView->RequestTreeRefresh();
	}
}

bool SOverlayComponentTreeEditor::CanRenameComponent() const {
	const TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = GetSelectedNodes();
	return IsEditingAllowed() && (SelectedNodes.Num() == 1 && SelectedNodes[0]->IsNodeEditable());
}

void SOverlayComponentTreeEditor::OnRenameComponent() {
	const TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = GetSelectedNodes();
	if (SelectedNodes.Num() == 1 && SelectedNodes[0]->IsNodeEditable()) {
		PendingRenameComponentData = SelectedNodes[0];
		ComponentTreeView->RequestScrollIntoView(SelectedNodes[0]);
	}
}

bool SOverlayComponentTreeEditor::CanDeleteNodes() const {
	if(!IsEditingAllowed()) {
		return false;
	}
	// Components can be deleted if their nodes are editable
	const TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = GetSelectedNodes();
	for (const TSharedPtr<FOverlayComponentData>& SelectedNode : SelectedNodes) {
		if (!SelectedNode->IsNodeEditable()) {
			return false;
		}
	}
	return true;
}

void SOverlayComponentTreeEditor::OnDeleteNodes() {
	const TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = GetSelectedNodes();
	OnDeleteAction(SelectedNodes);
}

void SOverlayComponentTreeEditor::OnFindReferences() {
	if (const TSharedPtr<FHookBlueprintEditor> BlueprintEditor = OwnerBlueprintEditor.Pin()) {
		const TArray<TSharedPtr<FOverlayComponentData>> SelectedNodes = GetSelectedNodes();
		if (SelectedNodes.Num() == 1) {
			UBlueprint* OwnerBlueprint = BlueprintEditor->GetBlueprintObj();
			UClass* OwnerClass = SelectedNodes[0]->GetOwnerClass();
			const FName VariableName = SelectedNodes[0]->GetComponentVariableName();

			// If this node is editable, we need to look for it in the self context
			if (SelectedNodes[0]->IsNodeEditable() && OwnerBlueprint && VariableName != NAME_None) {
				FMemberReference MemberReference;
				MemberReference.SetSelfMember(*VariableName.ToString());
				const FString SearchTerm = MemberReference.GetReferenceSearchString(OwnerBlueprint->SkeletonGeneratedClass);
				BlueprintEditor->SummonSearchUI(true, SearchTerm);	
			}
			// Otherwise, look for it in the context of the class that defined it
			else if (OwnerClass && VariableName != NAME_None) {
				FMemberReference MemberReference;
				FProperty* ResolvedMemberProperty = FindFProperty<FProperty>(OwnerClass, VariableName);
				MemberReference.SetFromField<FProperty>(ResolvedMemberProperty, false);
				const FString SearchTerm = MemberReference.GetReferenceSearchString(OwnerClass);
				BlueprintEditor->SummonSearchUI(true, SearchTerm);	
			}
		}
	}
}

void FOverlayComponentTreeRowDragDropOp::HoverTargetChanged() {
	const FSlateBrush* ErrorStatusSymbol = FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.Error"));
	const FSlateBrush* SuccessStatusSymbol = FAppStyle::GetBrush(TEXT("Graph.ConnectorFeedback.OK"));

	// Make sure we have a valid variable that we are dragging
	const TSharedPtr<FOverlayComponentData> FirstVariableData = SourceNodes.IsEmpty() ? nullptr : SourceNodes[0];
	if (FirstVariableData == nullptr || FirstVariableData->GetComponentVariableName() == NAME_None) {
		SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, LOCTEXT("InvalidComponentNodeDragSource", "Invalid component node being dragged!"));
		return;
	}
	
	// Validate that we have dropped this variable on a valid Kismet graph first
	UEdGraph* TheHoveredGraph = GetHoveredGraph();
	if (TheHoveredGraph == nullptr || TheHoveredGraph->GetSchema() == nullptr || !TheHoveredGraph->GetSchema()->IsA<UEdGraphSchema_K2>()) {
		SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, LOCTEXT("InvalidComponentNodeDropTarget", "Invalid drop target!"));
		return;
	}

	UBlueprint* GraphOwnerBlueprint = FBlueprintEditorUtils::FindBlueprintForGraph(TheHoveredGraph);
	const bool bIsSelfContext = GraphOwnerBlueprint && (FirstVariableData->GetOwnerClass() == nullptr || FirstVariableData->GetOwnerClass()->ClassGeneratedBy == GraphOwnerBlueprint);

	// Resolve the variable property and determine if it is valid
	const UClass* VariableTargetClass = bIsSelfContext ? GraphOwnerBlueprint->SkeletonGeneratedClass.Get() : FirstVariableData->GetOwnerClass();
	FObjectProperty* VariableProperty = VariableTargetClass ? FindFProperty<FObjectProperty>(VariableTargetClass, FirstVariableData->GetComponentVariableName()) : nullptr;
	if (VariableProperty == nullptr) {
		SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White,
			FText::Format(LOCTEXT("InvalidComponentNodeProperty", "Component Node {0} does not have a Variable associated with it."), FirstVariableData->GetNameLabel()));
		return;
	}
	// Validate that variable can be dropped on this graph at all
	if (!TheHoveredGraph->GetSchema()->CanVariableBeDropped(TheHoveredGraph, VariableProperty)) {
		SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, LOCTEXT("CannotCreateComponentNodeInThisSchema", "Cannot access variables in this type of graph."));
		return;
	}

	// If we have a pin under the cursor, validate that this pin is actually compatible with the node type
	if (UEdGraphPin* PinUnderCursor = GetHoveredPin()) {
		// Make sure the pin is not orphaned
		if (PinUnderCursor->bOrphanedPin) {
			SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, FText::Format(LOCTEXT("CannotConnectComponentNodeToOrhapedPin", "Cannot make connection to orphaned pin {0}."),
				PinUnderCursor->GetDisplayName()));
			return;
		}

		// Double check that graph schema is actually a valid K2 schema
		const UEdGraphSchema_K2* Schema = Cast<const UEdGraphSchema_K2>(PinUnderCursor->GetSchema());
		if (Schema == nullptr) {
			SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, LOCTEXT("CannotCreateComponentNodeInThisSchema", "Cannot access variables in this type of graph."));
			return;
		}
		// Pin must be an input pin, component getter node cannot be connected to an output pin
		if (PinUnderCursor->Direction != EGPD_Input) {
			SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, LOCTEXT("CannotConnectComponentNodeToInputPin", "Component variables cannot be connected to Output pins."));
			return;
		}

		// Convert type of the component property to the kismet type 
		FEdGraphPinType VariablePinType;
		Schema->ConvertPropertyToPinType(VariableProperty, VariablePinType);

		// Determine if types match, can be auto converted or auto cast
		const bool bTypeMatch = Schema->ArePinTypesCompatible(VariablePinType, PinUnderCursor->PinType);
		const bool bCanAutoConvert = Schema->FindSpecializedConversionNode(VariablePinType, *PinUnderCursor, false).IsSet();
		const bool bCanAutocast = Schema->SearchForAutocastFunction(PinUnderCursor->PinType, VariablePinType).IsSet();

		// If either of the above is true, this pin can be connected 
		if (bCanAutocast || bCanAutoConvert || bTypeMatch) {
			// Target pins allow multiple connections, so to give more accurate feedback check if this will actually break existing connections
			const bool bMultipleSelfConnectionException = Schema->IsSelfPin(*PinUnderCursor) &&
				Cast<UK2Node>(PinUnderCursor->GetOuter()) && CastChecked<UK2Node>(PinUnderCursor->GetOuter())->AllowMultipleSelfs(false);
			if (PinUnderCursor->HasAnyConnections() && !bMultipleSelfConnectionException) {
				// We have to break existing connections to connect this pin
				SetSimpleFeedbackMessage(SuccessStatusSymbol, FLinearColor::White, FText::Format(LOCTEXT("CreateComponentNodeOnPin_ReplaceConnection", "Connect pin {0} to Component variable {1}.\nThis will break existing pin connections!"),
					PinUnderCursor->GetDisplayName(), FirstVariableData->GetNameLabel()));
			} else {
				// There are no existing pins, we will just create a new connection
				SetSimpleFeedbackMessage(SuccessStatusSymbol, FLinearColor::White, FText::Format(LOCTEXT("CreatetComponentNodeOnPin_NewConnection", "Connect pin {0} to Component variable {1}."),
					PinUnderCursor->GetDisplayName(), FirstVariableData->GetNameLabel()));
			}
		} else {
			// Pin types are incompatible connection is not possible
			SetSimpleFeedbackMessage(ErrorStatusSymbol, FLinearColor::White, FText::Format(
				LOCTEXT("CannotConnectComponentNodeToIncompatiblePin", "Cannot make connection to pin {0} because its type is not compatible with Component variable type."), PinUnderCursor->GetDisplayName()));
			return;
		}
	} else {
		// We are not hovering over a pin, so just tell the user that a new node can be created here
		SetSimpleFeedbackMessage(SuccessStatusSymbol, FLinearColor::White, FText::Format(LOCTEXT("CreateComponentNodeInGraph", "Read Component variable {0}."), FirstVariableData->GetNameLabel()));
	}
}

UK2Node_VariableGet* FOverlayComponentTreeRowDragDropOp::SpawnVariableGetNodeForComponentData(UEdGraph* InTargetGraph, const TSharedPtr<FOverlayComponentData>& InComponentData, const FVector2D& InGraphPosition) {
	const UEdGraphSchema_K2* K2_Schema = Cast<const UEdGraphSchema_K2>(InTargetGraph->GetSchema());
	UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraph(InTargetGraph);
	const FName VariableName = InComponentData->GetComponentVariableName();
	UClass* VariableOwnerClass = InComponentData->GetOwnerClass();

	// Check for a valid K2 graph schema and a valid blueprint first
	if (K2_Schema != nullptr && Blueprint != nullptr && VariableName != NAME_None && VariableOwnerClass != nullptr) {
		
		// Spawn the variable read node and return nothing if it failed
		const bool bIsSelfContext = VariableOwnerClass && VariableOwnerClass->ClassGeneratedBy == Blueprint;
		UK2Node_VariableGet* NewVariableNode = K2_Schema->SpawnVariableGetNode(InGraphPosition, InTargetGraph, VariableName, bIsSelfContext ? nullptr : VariableOwnerClass);
		if (NewVariableNode == nullptr) {
			return nullptr;
		}

		// If this variable is not on this class instance, e.g. not in a self context, we have to plug in the mixin target object to connect it to the actual target object
		if (!bIsSelfContext) {
			const UK2Node_GetMixinTargetObject* TargetObjectNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_GetMixinTargetObject>(
				InTargetGraph, FVector2D(InGraphPosition.X - 200.0f, InGraphPosition.Y), EK2NewNodeFlags::None);
			check(TargetObjectNode);
			
			UEdGraphPin* TargetOutputPin = TargetObjectNode->FindPinChecked(UK2Node_GetMixinTargetObject::TargetOutputPinName, EGPD_Output);
			UEdGraphPin* VariableTargetInputPin = K2_Schema->FindSelfPin(*NewVariableNode, EGPD_Input);
			check(VariableTargetInputPin);
			TargetOutputPin->MakeLinkTo(VariableTargetInputPin);
		}
		return NewVariableNode;
	}
	return nullptr;
}

FReply FOverlayComponentTreeRowDragDropOp::DroppedOnPanel(const TSharedRef<SWidget>& Panel, FVector2D ScreenPosition, FVector2D GraphPosition, UEdGraph& Graph) {
	TArray<UK2Node_VariableGet*> SpawnedVariableGetters;

	// Check for a valid K2 graph schema and a valid blueprint first
	if (Graph.GetSchema()->IsA<UEdGraphSchema_K2>()) {
		const FScopedTransaction ScopedTransaction(LOCTEXT("DropComponentNodeOnGraphAction", "Drop Component variable(s) on Graph")); 
		
		for (const TSharedPtr<FOverlayComponentData>& ComponentData : SourceNodes) {
			if (UK2Node_VariableGet* NewVariableNode = SpawnVariableGetNodeForComponentData(&Graph, ComponentData, GraphPosition)) {
			
				// Add the node to the spawned list and advance the position vertically enough to spawn the next node
				SpawnedVariableGetters.Add(NewVariableNode);
				ScreenPosition.Y += 50.0f;
			}
		}
	}
	// Reply was handled if we spawned at least a single node
	return SpawnedVariableGetters.IsEmpty() ? FReply::Unhandled() : FReply::Handled();
}

FReply FOverlayComponentTreeRowDragDropOp::DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition) {
	UEdGraphPin* CurrentHoveredPin = GetHoveredPin();

	// Make sure we have a valid pin type before we attempt to handle the drop
	if (CurrentHoveredPin == nullptr ||
		CurrentHoveredPin->Direction != EGPD_Input ||
		CurrentHoveredPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Object) {
		return FReply::Unhandled();
	}
	
	const UClass* PinTargetClass = Cast<UClass>(CurrentHoveredPin->PinType.PinSubCategoryObject);
	const UEdGraphSchema_K2* K2_Schema = Cast<const UEdGraphSchema_K2>(CurrentHoveredPin->GetOwningNode()->GetGraph()->GetSchema());

	// Make sure this is a K2 graph schema and a pin has a valid target class
	if (K2_Schema != nullptr && PinTargetClass != nullptr) {
		const FScopedTransaction ScopedTransaction(LOCTEXT("DropComponentNodeOnPinAction", "Drop Component variable on Pin")); 
		
		for (const TSharedPtr<FOverlayComponentData>& ComponentData : SourceNodes) {
			const FName VariableName = ComponentData->GetComponentVariableName();
			const UClass* VariableOwnerClass = ComponentData->GetOwnerClass();

			if (VariableName != NAME_None && VariableOwnerClass != nullptr) {
				const FObjectProperty* TargetProperty = FindFProperty<FObjectProperty>(VariableOwnerClass, VariableName);

				// Check that target property type is actually compatible with the pin type
				if (TargetProperty != nullptr && TargetProperty->HasAnyPropertyFlags(CPF_BlueprintVisible) && !TargetProperty->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPrivate) &&
					TargetProperty->PropertyClass && TargetProperty->PropertyClass->IsChildOf(PinTargetClass)) {
					
					if (const UK2Node_VariableGet* NewVariableNode = SpawnVariableGetNodeForComponentData(CurrentHoveredPin->GetOwningNode()->GetGraph(), ComponentData, GraphPosition)) {

						// Attempt to create a connection to the node now
						if (UEdGraphPin* OutputValuePin = NewVariableNode->GetValuePin()) {
							CurrentHoveredPin->Modify();
							if (K2_Schema->TryCreateConnection(OutputValuePin, CurrentHoveredPin)) {
								return FReply::Handled();	
							}
						}
					}
				}
			}
		}
	}
	// We could not find a variable with a compatible type
	return FReply::Unhandled();
}

TSharedRef<FOverlayComponentTreeRowDragDropOp> FOverlayComponentTreeRowDragDropOp::Create(const TArray<TSharedPtr<FOverlayComponentData>>& InSourceNodes) {
	TSharedRef<FOverlayComponentTreeRowDragDropOp> NewOperation = MakeShared<FOverlayComponentTreeRowDragDropOp>();
	NewOperation->SourceNodes = InSourceNodes;
	NewOperation->PendingDropAction = EDropActionType::DropAction_None;
	NewOperation->Construct();
	return NewOperation;
}

FOverlayComponentTreeRowDragDropOp::EDropActionType SOverlayComponentTreeViewRowWidget::CheckCanAttachSelectedNodeToNode(const TSharedPtr<FOverlayComponentData>& SelectedNode, const TSharedPtr<FOverlayComponentData>& DraggedOverNode, FText& OutDescriptionMessage) {
	const UActorComponent* CurrentNodeActorComponentTemplate = DraggedOverNode->GetImmutableActorComponentTemplate();
	const USceneComponent* CurrentNodeComponentTemplate = Cast<USceneComponent>(CurrentNodeActorComponentTemplate);
	
	// If we are hovering the actor root or the separator node, tell the user to hover over a component instead
	if (CurrentNodeActorComponentTemplate == nullptr) {
		OutDescriptionMessage = LOCTEXT("DropActionToolTip_FriendlyError_DragToAComponent", "Drag to another component in order to attach to that component.\nDrag to a Blueprint graph in order to drop a reference.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	// Tell the user that scene components cannot be attached to non-scene components
	if (CurrentNodeComponentTemplate == nullptr) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_FriendlyError_CannotAttachToNotSceneComponent", "This component is not a scene component and other components cannot be attached to it. \nDrag over scene components to attach the selected component to them.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	// If this is a component node on the target actor, it cannot be re-attached or edited in any way
	if (!SelectedNode->IsNodeEditable()) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotAttachNotEditableComponent", "The selected component belongs to the target Actor Blueprint and cannot be edited. \nDrag another component over the selected component to attach it to it.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	// Make sure that the selected node actually represents a scene component
	const USceneComponent* SelectedNodeComponentTemplate = Cast<USceneComponent>(SelectedNode->GetImmutableActorComponentTemplate());
	if (SelectedNodeComponentTemplate == nullptr) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotAttachNotSceneComponent", "The selected component is not a scene component and cannot be attached to other components.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	// We cannot attach the component to itself
	if (DraggedOverNode == SelectedNode) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotAttachToSelf", "Cannot attach the selected component to itself.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}

	// If we are directly attached to the node we are dragging over, we want to detach from it
	if (SelectedNode->IsDirectlyAttachedToParent(DraggedOverNode)) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_DetachFromParent", "Drop here to detach the selected component from its parent.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_DetachFrom;
	}
	
	// Make sure we are not attempting to attach a parent component to its child component
	if (DraggedOverNode->IsAttachedToParent(SelectedNode)) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotAttachToChild", "Cannot attach the selected component to one of its children.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	// Cannot attach non-editor-only component to an editor-only component
	if (CurrentNodeComponentTemplate->IsEditorOnly() && !SelectedNodeComponentTemplate->IsEditorOnly()) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotReparentEditorOnly", "Cannot attach game components to an editor-only component.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	// Check mobility flags since we cannot attach movable components to static ones
	if (CurrentNodeComponentTemplate->Mobility == EComponentMobility::Static && (SelectedNodeComponentTemplate->Mobility == EComponentMobility::Movable || SelectedNodeComponentTemplate->Mobility == EComponentMobility::Stationary)) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotAttachToStatic", "Cannot attach Movable components to Static or Stationary components.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}
	if (CurrentNodeComponentTemplate->Mobility == EComponentMobility::Stationary && SelectedNodeComponentTemplate->Mobility == EComponentMobility::Movable) {
		OutDescriptionMessage = LOCTEXT("DropActionTooltip_Error_CannotAttachToStationary", "Cannot attach Movable components to Stationary components.");
		return FOverlayComponentTreeRowDragDropOp::DropAction_None;
	}

	// We can attach the selected component to this component otherwise
	OutDescriptionMessage = FText::Format(LOCTEXT("DropActionTooltip_AttachToComponent", "Drop here to attach the selected component to {0}"), DraggedOverNode->GetNameLabel());
	return FOverlayComponentTreeRowDragDropOp::DropAction_AttachTo;
}

#undef LOCTEXT_NAMESPACE
