#pragma once
#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_ArraySort.generated.h"

UCLASS()
class SMLEDITOR_API UK2Node_ArraySort : public UK2Node {
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BlueprintSearchable = "true"))
	FName SelectedFunctionName;

	UPROPERTY()
	FGuid SelectedFunctionGuid;

	UPROPERTY()
	FEdGraphPinType CachedArrayPinType;
public:
	UK2Node_ArraySort();
	
	// UEdGraphNode interface
	virtual void AllocateDefaultPins() override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PinTypeChanged(UEdGraphPin* Pin) override;
	virtual void NodeConnectionListChanged() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual void AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	// End of UEdGraphNode interface

	// UK2Node interface
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual FText GetMenuCategory() const override;
	// End of UK2Node interface

	bool ValidateNode(FText& OutErrorMessage) const;
	FEdGraphPinType GetCachedArrayPinType() const;

	UFunction* ResolveFunction(bool bAllowRefresh = true);
	UFunction* ResolveFunctionNoUpdate() const;
	
	/** Set new Function name (Without notifying about the change) */
	void SetFunction(FName Name);
	UClass* GetScopeClass(bool bDontUseSkeletalClassForSelf = false) const;

	void UpdateArrayPinTypesAndSortFunction();
	static bool ResolveArrayPinTypeFromFunction(UFunction* Function, FEdGraphPinType& OutArrayPinType);

	FName GetFunctionName() const;
	UEdGraphPin* GetArrayInPin() const;
	UEdGraphPin* GetObjectInPin() const;
};