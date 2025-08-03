#pragma once

#include "CoreMinimal.h"
#include "Engine/MemberReference.h"
#include "Nodes/HookTargetNode.h"
#include "Patching/BlueprintHookingTypes.h"
#include "HookTargetNode_Root.generated.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

struct FBlueprintHookDefinition;

UCLASS(Abstract)
class SMLEDITOR_API UHookTargetNode_Root : public UHookTargetNode {
	GENERATED_BODY()
public:
	/** If target specifier matches multiple expressions, this defines to which of them the hook will be applied */
	UPROPERTY(EditAnywhere, Category = "Target Selection")
	EBlueprintFunctionHookTargetSelectionMode TargetSelectionMode{};

	/** When hooking a target with specific ordinal, this is the index of the target to hook. First target is at index 0, second target is at index 1, and so on */
	UPROPERTY(EditAnywhere, Category = "Target Selection", meta = (ClampMin = "0", EditCondition = "TargetSelectionMode == EBlueprintFunctionHookTargetSelectionMode::Ordinal", EditConditionHides))
	int32 TargetOrdinal{0};

	/** Reference to the function in which the hook must be applied in another blueprint */
	UPROPERTY()
	FMemberReference TargetFunctionReference;

	/** Reference to the hook implementation in this blueprint */
	UPROPERTY()
	FMemberReference HookFunctionReference;

	// Begin UHookTargetNode interface
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;
	virtual bool IsRootSetNode() const override { return true; }
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void GetMemberReferenceDescriptors(TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberReferenceDescriptors) const override;
	virtual FMemberReference GetMemberReferenceByName(const FName& Name) const override;
	virtual bool SetMemberReferenceByName(const FName& Name, const FMemberReference& NewMemberReference) override;
	// End UHookTargetNode interface

	/** Entry point into the graph. Produces blueprint hook definition as a result of compiling this node and its dependencies */
	virtual void CompileRoot(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, FBlueprintHookDefinition& OutBlueprintHookDefinition) const;

	/** Returns the pin name for the target expression (or statement) pin */
	virtual FName GetTargetExpressionPinName() const { return NAME_None; }
};

UCLASS()
class SMLEDITOR_API UHookTargetNode_InsertionHook : public UHookTargetNode_Root {
	GENERATED_BODY()
public:
	/** Location relative to the statement */
	UPROPERTY(EditAnywhere, Category = "Insertion Hook")
	EBlueprintFunctionHookInsertLocation InsertLocation{EBlueprintFunctionHookInsertLocation::BeforeTarget};
	
	// Begin UHookTargetNode_Root interface
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void GetMenuEntries(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void CompileRoot(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, FBlueprintHookDefinition& OutBlueprintHookDefinition) const override;
	virtual FName GetTargetExpressionPinName() const override;
	// End UHookTargetNode_Root interface
private:
	static FText HookInsertLocationToText(EBlueprintFunctionHookInsertLocation InsertLocation);

	const FText Description = LOCTEXT("HookTargetNodeInsertionHook_Description", "Insertion Hooks allow executing user-defined code before/instead of/after the specific Statement in the Target Function.");
};

UCLASS()
class SMLEDITOR_API UHookTargetNode_Redirect : public UHookTargetNode_Root {
	GENERATED_BODY()
public:
	// Begin UHookTargetNode_Root interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void GetMenuEntries(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void CompileRoot(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, FBlueprintHookDefinition& OutBlueprintHookDefinition) const override;
	virtual FName GetTargetExpressionPinName() const override;
	// End UHookTargetNode_Root interface

private:
	const FText Description = LOCTEXT("HookTargetNodeRedirectHook_Description", "Redirect Hooks allow redirecting arbitrary expressions (such as variable reads or function calls) in the Target Function to user-defined code.");
};

#undef LOCTEXT_NAMESPACE
