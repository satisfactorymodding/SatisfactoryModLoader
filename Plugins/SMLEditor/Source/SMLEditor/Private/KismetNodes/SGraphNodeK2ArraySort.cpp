#include "KismetNodes/SGraphNodeK2ArraySort.h"
#include "SSearchableComboBox.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Editor/UnrealEd/Public/Kismet2/KismetEditorUtilities.h"
#include "Editor/UnrealEd/Public/ScopedTransaction.h"
#include "Editor/BlueprintGraph/Classes/BlueprintNodeBinder.h"
#include "Editor/BlueprintGraph/Classes/BlueprintEventNodeSpawner.h"
#include "Editor/BlueprintGraph/Classes/K2Node_CustomEvent.h"
#include "Editor/GraphEditor/Public/SGraphNode.h"
#include "Node/K2Node_ArraySort.h"

PRAGMA_DISABLE_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SMLEditor"

SGraphNodeK2ArraySort::~SGraphNodeK2ArraySort() {
	const TSharedPtr<SSearchableComboBox> SelectFunctionWidgetPtr = FunctionOptionComboBox.Pin();
	if (SelectFunctionWidgetPtr.IsValid()) {
		SelectFunctionWidgetPtr->SetIsOpen(false);
	}
}

void SGraphNodeK2ArraySort::Construct(const FArguments& InArgs, UK2Node* InNode) {
	GraphNode = InNode;
	UpdateGraphNode();
}

FText SGraphNodeK2ArraySort::GetCurrentFunctionDescription() const {
	const UK2Node_ArraySort* Node = Cast<UK2Node_ArraySort>(GraphNode);

	if (const UFunction* Function = Node->ResolveFunctionNoUpdate()) {
		return CreateFunctionDescription(Function);
	}

	if (Node->GetFunctionName() != NAME_None) {
		return FText::Format(NSLOCTEXT("GraphNodeK2Create", "ErrorLabelFmt", "Error? {0}"), FText::FromName(Node->GetFunctionName()));
	}
	return NSLOCTEXT("GraphNodeK2Create", "SelectFunctionLabel", "Select Function...");
}

FText SGraphNodeK2ArraySort::GetCurrentElementTypeDescription() const {
	const UK2Node_ArraySort* Node = Cast<UK2Node_ArraySort>(GraphNode);
	if (Node == NULL) {
		return FText::GetEmpty();
	}
	const FEdGraphPinType ArrayPinType = Node->GetCachedArrayPinType();
	FText ContainerElementType;
		
	if (ArrayPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) {
		FEdGraphPinType ArrayElementType = ArrayPinType;
		ArrayElementType.ContainerType = EPinContainerType::None;
		ArrayElementType.bIsReference = false;
		ContainerElementType = UEdGraphSchema_K2::TypeToText(ArrayElementType);
	} else {
		ContainerElementType = LOCTEXT("ArraySortNode_WildcardElementType", "Pick Any");
	}
	FFormatNamedArguments FormatArguments;
	FormatArguments.Add(TEXT("ElementType"), ContainerElementType);
	return FText::Format(LOCTEXT("ArraySortNode_ElementType", "Element Type: {ElementType}"), FormatArguments);
}

FText SGraphNodeK2ArraySort::CreateFunctionDescription(const UFunction* Function, const bool bOnlyDescribeSignature, const int32 CharacterLimit) {
	if (!Function || !Function->GetOuter()) {
		return NSLOCTEXT("GraphNodeK2Create", "Error", "Error");
	}
	FString Result;
	
	// Show function name.
	if (!bOnlyDescribeSignature) {
		Result = Function->GetName();
	}
	Result += TEXT("(");

	// Describe input parameters.
	{
		bool bFirstParameter = true;
		for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt) {
			FProperty* const Param = *PropIt;
			const bool bIsFunctionInput = Param && (!Param->HasAnyPropertyFlags(CPF_OutParm) || Param->HasAnyPropertyFlags(CPF_ReferenceParm));

			if (bIsFunctionInput) {
				if (!bFirstParameter) {
					Result += TEXT(", ");
				}
				if (CharacterLimit > INDEX_NONE && Result.Len() > CharacterLimit) {
					Result += TEXT("...");
					break;
				}
				Result += bOnlyDescribeSignature ? UEdGraphSchema_K2::TypeToText(Param).ToString() : Param->GetName();
				bFirstParameter = false;
			}
		}
	}
	Result += TEXT(")");

	// Describe outputs.
	{
		TArray<FString> Outputs;

		FProperty* FunctionReturnProperty = Function->GetReturnProperty();
		if (FunctionReturnProperty) {
			Outputs.Add(UEdGraphSchema_K2::TypeToText(FunctionReturnProperty).ToString());
		}

		for (TFieldIterator<FProperty> PropIt(Function); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt) {
			FProperty* const Param = *PropIt;
			const bool bIsFunctionOutput = Param && Param->HasAnyPropertyFlags(CPF_OutParm);
			if (bIsFunctionOutput) {
				Outputs.Add(bOnlyDescribeSignature ? UEdGraphSchema_K2::TypeToText(Param).ToString() : Param->GetName());
			}
		}

		if (Outputs.Num() > 0) {
			Result += TEXT(" -> ");
		}
		if (Outputs.Num() > 1) {
			Result += TEXT("[");
		}
		bool bFirst = true;
		for (const FString& Output : Outputs) {
			if (!bFirst) {
				Result += TEXT(", ");
			}
			if (CharacterLimit > INDEX_NONE && Result.Len() > CharacterLimit) {
				Result += TEXT("...");
				break;
			}
			Result += Output;
			bFirst = false;
		}
		if (Outputs.Num() > 1) {
			Result += TEXT("]");
		}
	}
	return FText::FromString(Result);
}

void PopulateFunctionGraphWithComparatorData(UEdGraph* FunctionGraph, const FEdGraphPinType& ArrayPinType) {
	TArray<UK2Node_FunctionEntry*> FunctionEntries;
	FunctionGraph->GetNodesOfClass(FunctionEntries);

	check(FunctionEntries.Num());
	UK2Node_FunctionEntry* FunctionEntryNode = FunctionEntries[0];
	
	FEdGraphPinType ArrayElementType = ArrayPinType;
	ArrayElementType.ContainerType = EPinContainerType::None;
	ArrayElementType.bIsReference = false;

	//Create two input pins of the element
	FunctionEntryNode->CreateUserDefinedPin(TEXT("A"), ArrayElementType, EGPD_Input);
	FunctionEntryNode->CreateUserDefinedPin(TEXT("B"), ArrayElementType, EGPD_Input);

	//Configure function as blueprint pure
	FunctionEntryNode->SetExtraFlags(FunctionEntryNode->GetExtraFlags() | FUNC_BlueprintPure);

	//Create the return value exit node
	TArray<UK2Node_FunctionResult*> FunctionReturns;
	FunctionGraph->GetNodesOfClass(FunctionReturns);
	UK2Node_FunctionResult* ReturnNode = FunctionReturns.Num() ? FunctionReturns[0] : NULL;

	//Create exit node if we do not have one
	if (ReturnNode == NULL) {
		FGraphNodeCreator<UK2Node_FunctionResult> NodeCreator(*FunctionGraph);
	
		ReturnNode = NodeCreator.CreateNode();
		ReturnNode->FunctionReference = FunctionEntryNode->FunctionReference;
		ReturnNode->NodePosX = FunctionEntryNode->NodePosX + FunctionEntryNode->NodeWidth + 256;
		ReturnNode->NodePosY = FunctionEntryNode->NodePosY;

		NodeCreator.Finalize();
		UEdGraphSchema::SetNodeMetaData(ReturnNode, FNodeMetadata::DefaultGraphNode);
	}

	//Create boolean result pin
	if (ReturnNode != NULL) {
		FEdGraphPinType OutputPinType{};
		OutputPinType.PinCategory = UEdGraphSchema_K2::PC_Boolean;
		ReturnNode->CreateUserDefinedPin(TEXT("Result"), OutputPinType, EGPD_Input);
	}

	// Auto-connect the pins for entry and exit, so that by default the signature is properly generated
	if (ReturnNode != NULL) {
		const UEdGraphSchema_K2* GraphSchema = GetDefault<UEdGraphSchema_K2>();
		UEdGraphPin* EntryNodeExec = GraphSchema->FindExecutionPin(*FunctionEntryNode, EGPD_Output);
		UEdGraphPin* ResultNodeExec = GraphSchema->FindExecutionPin(*ReturnNode, EGPD_Input);
	
		if (!EntryNodeExec->LinkedTo.Num()) {
			EntryNodeExec->MakeLinkTo(ResultNodeExec);
		}
	}
}

void SGraphNodeK2ArraySort::OnFunctionSelected(TSharedPtr<FString> FunctionItemData, ESelectInfo::Type SelectInfo) {
	const FScopedTransaction Transaction(NSLOCTEXT("GraphNodeK2Create", "CreateMatchingSigniture", "Create matching signiture"));
	UK2Node_ArraySort* Node = Cast<UK2Node_ArraySort>(GraphNode);
	
	if (FunctionItemData.IsValid() && Node != NULL) {
		UBlueprint* NodeBP = Node->GetBlueprint();
		UEdGraph* SourceGraph = Node->GetGraph();
		check(NodeBP && SourceGraph);

		SourceGraph->Modify();
		NodeBP->Modify();
		Node->Modify();
		
		if (CreateMatchingFunctionData.IsValid() && FunctionItemData == CreateMatchingFunctionData) {
			//Get a valid name for the function graph
			FEdGraphPinType ArrayPinType = Node->GetCachedArrayPinType();
			FString BasicFunctionNamePrefix = NodeBP->GetName();
			
			if (ArrayPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) {
				FEdGraphPinType ArrayElementType = ArrayPinType;
				ArrayElementType.ContainerType = EPinContainerType::None;
				ArrayElementType.bIsReference = false;

				BasicFunctionNamePrefix = UEdGraphSchema_K2::TypeToText(ArrayElementType).ToString();
			}
			const FString ProposedFuncName = NodeBP->GetName() + BasicFunctionNamePrefix + "_Comparator";
			const FName NewFuncName = FBlueprintEditorUtils::GenerateUniqueGraphName(NodeBP, ProposedFuncName);
			
			UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(NodeBP, NewFuncName,
				SourceGraph->GetClass(), SourceGraph->GetSchema() ? SourceGraph->GetSchema()->GetClass() : GetDefault<UEdGraphSchema_K2>()->GetClass());

			if (NewGraph != nullptr) {
				FBlueprintEditorUtils::AddFunctionGraph<UFunction>(NodeBP, NewGraph, true, NULL);

				if (ArrayPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) {
					PopulateFunctionGraphWithComparatorData(NewGraph, ArrayPinType);
				}
				FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(NewGraph);
			}
			Node->SetFunction(NewFuncName);
		} else {
			const FName FuncName(**FunctionItemData.Get());
			Node->SetFunction(FuncName);
		}
	
		const TSharedPtr<SSearchableComboBox> SelectFunctionWidgetPtr = FunctionOptionComboBox.Pin();
		if (SelectFunctionWidgetPtr.IsValid()) {
			SelectFunctionWidgetPtr->SetIsOpen(false);
		}
	}
}

TSharedPtr<FString> SGraphNodeK2ArraySort::AddDefaultFunctionDataOption(const FText& DisplayName) {
	TSharedPtr<FString> Res = MakeShareable(new FString(DisplayName.ToString()));
	FunctionOptionList.Add(Res);
	return Res;
}

bool FunctionCanBeUsedAsComparator(UFunction* InFunction, const FEdGraphPinType& ArrayPinType) {
	if (!InFunction ||
		!UEdGraphSchema_K2::CanUserKismetCallFunction(InFunction) ||
		InFunction->HasMetaData(FBlueprintMetadata::MD_Latent) ||
		!InFunction->HasAllFunctionFlags(FUNC_BlueprintPure)) {
		return false;
	}

	FEdGraphPinType FunctionPinType;
	if (!UK2Node_ArraySort::ResolveArrayPinTypeFromFunction(InFunction, FunctionPinType)) {
		return false;
	}
	
	if (ArrayPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) {
		return FunctionPinType == ArrayPinType;
	}
	return true;
}

void SGraphNodeK2ArraySort::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) {
	const UK2Node_ArraySort* Node = Cast<UK2Node_ArraySort>(GraphNode);
	if (Node == NULL) {
		return;
	}
	const UClass* ScopeClass = Node->GetScopeClass();
	if (ScopeClass == NULL) {
		return;
	}
	const FEdGraphPinType ArrayPinType = Node->GetCachedArrayPinType();
	
	MainBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Fill)
		.Padding(4.0f)
		[
			SNew(STextBlock)
			.Text(this, &SGraphNodeK2ArraySort::GetCurrentElementTypeDescription)
		];

	FunctionOptionList.Empty();

	// add an empty row, so the user can clear the selection if they want
	AddDefaultFunctionDataOption(NSLOCTEXT("GraphNodeK2Create", "EmptyFunctionOption", "[None]"));

	//Only allow function creation if we have a signature
	CreateMatchingFunctionData.Reset();
	if (ArrayPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) {
		CreateMatchingFunctionData = AddDefaultFunctionDataOption(NSLOCTEXT("GraphNodeK2Create", "CreateMatchingFunctionOption", "[Create a matching function]"));
	}

	struct FFunctionItemData {
		FName Name;
		FText Description;
	};
	TArray<FFunctionItemData> ClassFunctions;

	for (TFieldIterator<UFunction> It(ScopeClass); It; ++It) {
		UFunction* Func = *It;
		if (Func && FunctionCanBeUsedAsComparator(Func, ArrayPinType)) {
			FFunctionItemData ItemData;
			ItemData.Name = Func->GetFName();
			ItemData.Description = CreateFunctionDescription(Func);
			ClassFunctions.Emplace(MoveTemp(ItemData));
		}
	}
	ClassFunctions.Sort([](const FFunctionItemData& A, const FFunctionItemData& B) {
		return A.Description.CompareTo(B.Description) < 0;
	});

	for (const FFunctionItemData& ItemData : ClassFunctions) {
		// Add this to the searchable text box as an FString so users can type and find it
		FunctionOptionList.Add(MakeShareable(new FString(ItemData.Name.ToString())));
	}

	const TSharedRef<SSearchableComboBox> SelectFunctionWidgetRef =
		SNew(SSearchableComboBox)
		.OptionsSource(&FunctionOptionList)
		.OnGenerateWidget(this, &SGraphNodeK2ArraySort::MakeFunctionOptionComboWidget)
		.OnSelectionChanged(this, &SGraphNodeK2ArraySort::OnFunctionSelected)
		.ContentPadding(2)
		.MaxListHeight(200.0f)
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &SGraphNodeK2ArraySort::GetCurrentFunctionDescription)
		];
	
	MainBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Fill)
		.Padding(4.0f)
		[
			SelectFunctionWidgetRef
		];
	FunctionOptionComboBox = SelectFunctionWidgetRef;
}

TSharedRef<SWidget> SGraphNodeK2ArraySort::MakeFunctionOptionComboWidget(TSharedPtr<FString> InItem) {
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}

#undef LOCTEXT_NAMESPACE

PRAGMA_ENABLE_OPTIMIZATION