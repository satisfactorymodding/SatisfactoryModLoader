#pragma once

#include "CoreMinimal.h"
#include "Nodes/HookTargetNode.h"
#include "Templates/SubclassOf.h"
#include "HookTargetNode_TargetExpression.generated.h"

class UBlueprintHookTargetSpecifier;

UCLASS()
class SMLEDITOR_API UHookTargetNode_TargetExpression : public UHookTargetNode {
	GENERATED_BODY()
public:
	/** Class of the target specifier to edit */
	UPROPERTY()
	TSubclassOf<UBlueprintHookTargetSpecifier> TargetSpecifierClass;

	/** Archetype which we will use to create the resulting target specifier */
	UPROPERTY(EditAnywhere, meta = (ShowInnerProperties, ShowOnlyInnerProperties))
	TObjectPtr<UBlueprintHookTargetSpecifier> TargetSpecifierArchetype;

	/** Mapping of the member reference descriptor to the bound member reference */
	UPROPERTY()
	TMap<FName, FMemberReference> MemberReferences;

	UPROPERTY()
	TArray<FName> GeneratedPropertyPinNames;
	UPROPERTY()
	TArray<FHookTargetNodeMemberReferenceDescriptor> GeneratedMemberReferenceDescriptors;

	// Begin UHookTargetNode interface
	virtual void ReconstructNode() override;
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void GetMenuEntries(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;
	virtual UObject* CompileOutput(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* OutputPin) override;
	virtual void GetMemberReferenceDescriptors(TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberReferenceDescriptors) const override;
	virtual FMemberReference GetMemberReferenceByName(const FName& Name) const override;
	virtual bool SetMemberReferenceByName(const FName& Name, const FMemberReference& NewMemberReference) override;
	// End UHookTargetNode interface
protected:
	void CreateTargetClassSpecificData();
	static void GenerateMemberReferencesAndPinsForClass(const UClass* InClass, TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberDescriptors, TArray<TPair<FName, UClass*>>& OutPinDescriptors);
	static FHookTargetNodeMemberReferenceDescriptor CreateMemberReferenceDescriptorFromProperty(const FProperty* InSourceProperty);
};
