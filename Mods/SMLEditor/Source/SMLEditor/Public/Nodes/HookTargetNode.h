#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Engine/MemberReference.h"
#include "HookTargetNode.generated.h"

class UEdGraphPin;

UENUM()
enum class EHTNMemberRefFlags : uint64 {
	FunctionReference = 0x00,
	PropertyReference = 0x01,
	SelfContext = 0x02,
	FunctionsWithScriptOnly = 0x04,
	ShowDelegateSignatureFunctions = 0x08,
	HookTargetFunctionReference = 0x10,
};
ENUM_CLASS_FLAGS(EHTNMemberRefFlags);

USTRUCT()
struct FHookTargetNodeMemberReferenceDescriptor {
	GENERATED_BODY()

	/** Name of the descriptor, to be passed back to other functions */
	UPROPERTY()
	FName Name;

	/** Name of the member reference as it is shown to the user */
	UPROPERTY()
	FText DisplayName;

	/** Hover tool tip text shown to the user */
	UPROPERTY()
	FText ToolTip;
	
	/** Flags for the descriptor */
	UPROPERTY()
	EHTNMemberRefFlags Flags{EHTNMemberRefFlags::FunctionReference};
};

UCLASS(Abstract)
class SMLEDITOR_API UHookTargetNode : public UEdGraphNode {
	GENERATED_BODY()
public:
	// Begin UEdGraphNode interface
	virtual bool ShowPaletteIconOnNode() const override { return true; }
	virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	// End UEdGraphNode interface

	/** Called on the duplicated graph to prepare the node for compilation. Node is free to modify the graph and its connections, as well as connections of other nodes */
	virtual void PrepareForCompilation(FCompilerResultsLog& MessageLog, UEdGraph* InSourceGraph);

	/** Called to compile the value of the output pin for this node. Result objects must be created in DerivedDataOuter */
	virtual UObject* CompileOutput(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* OutputPin);

	/** Returns true if this node should be considered a part of the root set and allowed to not have any output connections */
	virtual bool IsRootSetNode() const { return false; }

	/** Utility function to get the generated class from a node. */
	UClass* GetBlueprintClassFromNode() const;

	/** Called by the UI to generate elements for any member references held by this node */
	virtual void GetMemberReferenceDescriptors(TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberReferenceDescriptors) const {}
	/** Returns member reference by name */
	virtual FMemberReference GetMemberReferenceByName(const FName& Name) const { return FMemberReference(); }
	/** Updates member reference by name */
	virtual bool SetMemberReferenceByName(const FName& Name, const FMemberReference& NewMemberReference) { return false; }
protected:
	/** Evaluates the input pin of this node */
	UObject* EvaluateNodeInputPin(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* InputPin, UClass* ExpectedObjectClass) const;

	/** Evaluates the input pin of this node */
	template<typename T>
	T* EvaluateNodeInputPin(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, const UEdGraphPin* InputPin) const {
		return Cast<T>(EvaluateNodeInputPin(MessageLog, SelfClass, DerivedDataOuter, InputPin, T::StaticClass()));
	}
};
