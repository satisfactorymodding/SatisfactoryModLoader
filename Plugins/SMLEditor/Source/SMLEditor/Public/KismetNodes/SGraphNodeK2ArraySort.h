#pragma once
#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "KismetNodes/SGraphNodeK2Base.h"

class SSearchableComboBox;
class STableViewBase;
class SVerticalBox;
class UK2Node;

class SGraphNodeK2ArraySort : public SGraphNodeK2Base {
public:
	SLATE_BEGIN_ARGS(SGraphNodeK2ArraySort) {}
	SLATE_END_ARGS()

	/** Data that can be used to create a matching function based on the parameters of a create event node */
	TSharedPtr<FString> CreateMatchingFunctionData;
public:
	virtual ~SGraphNodeK2ArraySort();
	void Construct(const FArguments& InArgs, UK2Node* InNode);
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;
protected:
	static FText CreateFunctionDescription(const UFunction* Function, const bool bOnlyDescribeSignature = false, const int32 CharacterLimit = 32);
	FText GetCurrentFunctionDescription() const;
	FText GetCurrentElementTypeDescription() const;
private:
	//~ Begin Searchable combo box options
	TWeakPtr<SSearchableComboBox> FunctionOptionComboBox;
	TArray<TSharedPtr<FString>>	FunctionOptionList;

	TSharedRef<SWidget> MakeFunctionOptionComboWidget(TSharedPtr<FString> InItem);

	/** Callback for when the function selection has changed from the dropdown */
	void OnFunctionSelected(TSharedPtr<FString> FunctionItemData, ESelectInfo::Type SelectInfo);
	//~ End Searchable combo box options

	TSharedPtr<FString> AddDefaultFunctionDataOption(const FText& DescriptionName);
};