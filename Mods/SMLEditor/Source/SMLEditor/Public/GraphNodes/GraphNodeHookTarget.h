#pragma once

#include "CoreMinimal.h"
#include "Nodes/HookTargetNode.h"
#include "SGraphNodeDefault.h"
#include "Widgets/Input/SComboBox.h"

class SMLEDITOR_API SHookMemberReference : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SHookMemberReference) : _OwnerNode(nullptr), _IsEditable(true) {}
	SLATE_ARGUMENT(UHookTargetNode*, OwnerNode);
	SLATE_ARGUMENT(FHookTargetNodeMemberReferenceDescriptor, MemberDescriptor);
	SLATE_ATTRIBUTE(bool, IsEditable);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
protected:
	const UClass* GetSelectedMemberScope() const;
	void OnSelectedNewMemberScope(const UClass* InNewMemberScope);

	FText GetSelectedMemberName() const;
	void OnSelectedMemberNameChanged(TSharedPtr<FString> InNewMemberName, ESelectInfo::Type InSelectionType);
	void UpdateAvailableMemberNames();

	void OnOwnerBlueprintChanged(UBlueprint* InOwnerBlueprint);
	TSharedRef<SWidget> HandleGenerateTextBoxFunctionNameItem(TSharedPtr<FString> StringItem);
	bool IsEditable() const;
	bool IsClassContextForced() const;
	UClass* GetForcedClassContext() const;

	TAttribute<bool> IsEditableAttribute{false};
	UHookTargetNode* GraphNode{};
	FHookTargetNodeMemberReferenceDescriptor MemberDescriptor;
	TArray<TSharedPtr<FString>> AllMemberNames;
	TSharedPtr<FString> CurrentlySelectedMemberName;
	TSharedPtr<class SSearchableComboBox> MemberSelectionComboBox;
	bool bSuppressSelectedItemChangedDelegate{false};
};

class SMLEDITOR_API SGraphNodeHookTarget : public SGraphNodeDefault {
public:
	SLATE_BEGIN_ARGS(SGraphNodeHookTarget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UHookTargetNode* InNode);

	// Begin SGraphNode Interface
	virtual void UpdateGraphNode() override;
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;
	//End SGraphNode Interface
};
