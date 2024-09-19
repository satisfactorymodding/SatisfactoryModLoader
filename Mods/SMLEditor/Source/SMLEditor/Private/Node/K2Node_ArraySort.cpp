#include "Node/K2Node_ArraySort.h"
#include "Engine/Blueprint.h"
#include "Engine/MemberReference.h"
#include "EdGraph/EdGraph.h"
#include "EdGraphSchema_K2.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/CompilerResultsLog.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "FindInBlueprintManager.h"
#include "K2Node_CallArrayFunction.h"
#include "K2Node_CallFunction.h"
#include "K2Node_Self.h"
#include "KismetCompiler.h"
#include "KismetNodes/SGraphNodeK2ArraySort.h"
#include "Kismet/SMLBlueprintArrayLibrary.h"

PRAGMA_DISABLE_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SMLEditor"

struct FK2Node_ArraySort_Helper {
	static FName ArrayInputName;
};
FName FK2Node_ArraySort_Helper::ArrayInputName(TEXT("InputArray"));

UK2Node_ArraySort::UK2Node_ArraySort() {
	CachedArrayPinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
	CachedArrayPinType.ContainerType = EPinContainerType::Array;
	CachedArrayPinType.bIsReference = true;
}

void UK2Node_ArraySort::AllocateDefaultPins() {
	//Allocate Exec input/outputs pins for this node
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
	
	if (UEdGraphPin* ObjPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), UEdGraphSchema_K2::PN_Self)) {
		ObjPin->PinFriendlyName = LOCTEXT("ArraySortNode_InputObjectName", "Object");
	}
	
	if(UEdGraphPin* ArrayInPin = CreatePin(EGPD_Input, CachedArrayPinType, FK2Node_ArraySort_Helper::ArrayInputName)) {
		ArrayInPin->PinFriendlyName = LOCTEXT("ArraySortNode_InputArrayName", "Array");
	}
	Super::AllocateDefaultPins();
}

bool UK2Node_ArraySort::ValidateNode(FText& OutErrorMessage) const {
	const FName FunctionName = GetFunctionName();
	if (FunctionName == NAME_None) {
		OutErrorMessage = LOCTEXT("ArraySortNode_NoFunction", "No sorter function specified");
		return false;
	}

	UFunction* ResolvedFunction = ResolveFunctionNoUpdate();
	if (ResolvedFunction == NULL) {
		OutErrorMessage = LOCTEXT("ArraySortNode_CannotResolveFunction", "Cannot resolve sorter function reference");
		return false;
	}
	
	const UEdGraphPin* InputArrayPin = GetArrayInPin();
	if (InputArrayPin->LinkedTo.Num() == 0) {
		OutErrorMessage = LOCTEXT("ArraySortNode_ArrayNotConnected", "Array input pin is not connected");
		return false;
	}

	if (InputArrayPin->PinType != CachedArrayPinType) {
		OutErrorMessage = LOCTEXT("ArraySortNode_InvalidArrayPin", "Array input pin type does not match the cached type");
		return false;
	}
	
	FEdGraphPinType FunctionPinType;
	if (!ResolveArrayPinTypeFromFunction(ResolvedFunction, FunctionPinType)) {
		OutErrorMessage = LOCTEXT("ArraySortNode_InvalidFunction", "Provided function is not a valid comparator function");
		return false;
	}

	if (FunctionPinType != CachedArrayPinType) {
		OutErrorMessage = LOCTEXT("ArraySortNode_InputPinMismatch", "Input Pin type does not match the sorter function");
		return false;
	}
	return true;
}

UFunction* UK2Node_ArraySort::ResolveFunction(bool bAllowRefresh) {
	const auto Blueprint = HasValidBlueprint() ? GetBlueprint() : nullptr;
	const auto SelfScopeClass = Blueprint ? Blueprint->SkeletonGeneratedClass : nullptr;
	const auto ParentClass = GetScopeClass();
	const bool bIsSelfScope = SelfScopeClass && ParentClass && (SelfScopeClass->IsChildOf(ParentClass)) ||
		(SelfScopeClass->ClassGeneratedBy == ParentClass->ClassGeneratedBy);

	FMemberReference FunctionReference;
	FunctionReference.SetDirect(SelectedFunctionName, SelectedFunctionGuid, GetScopeClass(), bIsSelfScope);
	
	if (UFunction* ResolvedFunction = FunctionReference.ResolveMember<UFunction>(SelfScopeClass)) {
		if (bAllowRefresh) {
			SelectedFunctionName = FunctionReference.GetMemberName();
			SelectedFunctionGuid = FunctionReference.GetMemberGuid();

			if (!SelectedFunctionGuid.IsValid()) {
				UBlueprint::GetGuidFromClassByFieldName<UFunction>(ParentClass, SelectedFunctionName, SelectedFunctionGuid);
			}
		}
		return ResolvedFunction;
	}
	return NULL;
}

UFunction* UK2Node_ArraySort::ResolveFunctionNoUpdate() const {
	return const_cast<UK2Node_ArraySort*>(this)->ResolveFunction(false);
}

bool UK2Node_ArraySort::ResolveArrayPinTypeFromFunction(UFunction* Function, FEdGraphPinType& OutArrayPinType) {
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	FEdGraphPinType CurrentGraphPinType;
	int32 ParameterCount = 0;
	bool bFoundValidReturnValueOrOutParam = false;

	for (TFieldIterator<FProperty> It(Function); It && It->HasAnyPropertyFlags(CPF_Parm); ++It) {
		//Return value or out parameter should always be the last one, if we are here the function does not suit our needs
		if (bFoundValidReturnValueOrOutParam) {
			return false;
		}
		
		//If we have found a return value parameter, it should be a boolean
		if (It->HasAnyPropertyFlags(CPF_ReturnParm)) {
			if (!It->IsA<FBoolProperty>()) {
				return false;
			}
			bFoundValidReturnValueOrOutParam = true;
			continue;
		}
		
		//If we have found an out parameter, assume it is a return value
		if (It->HasAnyPropertyFlags(CPF_OutParm)) {
			if (!It->IsA<FBoolProperty>()) {
				return false;
			}
			bFoundValidReturnValueOrOutParam = true;
			continue;
		}

		//It is an input by reference parameter, and we do not allow these
		if (It->HasAnyPropertyFlags(CPF_ReferenceParm)) {
			return false;
		}
		//If we have any non convertible parameters, bail out
		FEdGraphPinType ParameterPinType;
		if (!K2Schema->ConvertPropertyToPinType(*It, ParameterPinType)) {
			return false;
		}

		//If the parameters are containers or references, we cannot deal with them, as nested containers types are not supported
		if (ParameterPinType.ContainerType != EPinContainerType::None ||
			ParameterPinType.bIsReference) {
			return false;
		}

		//If we are not the first parameter and our type is different from the previous one, bail out
		if (ParameterCount && ParameterPinType != CurrentGraphPinType) {
			return false;
		}
		CurrentGraphPinType = ParameterPinType;
		ParameterCount++;
	}

	//If we have one or more than two parameters or no return value, function does not work
	if (ParameterCount != 2 || !bFoundValidReturnValueOrOutParam) {
		return false;
	}
	
	//Otherwise, we must be good to go.
	CurrentGraphPinType.ContainerType = EPinContainerType::Array;
	CurrentGraphPinType.bIsReference = true;
	OutArrayPinType = CurrentGraphPinType;
	return true;
}

FEdGraphPinType UK2Node_ArraySort::GetCachedArrayPinType() const {
	return CachedArrayPinType;
}

void UK2Node_ArraySort::UpdateArrayPinTypesAndSortFunction() {
	UEdGraphPin* InputArrayPin = GetArrayInPin();
	bool bChangedSomething = false;

	FEdGraphPinType InputPinType = InputArrayPin->PinType;
	bool bPrioritizeInputPin = false;

	//Make sure we stay true to the connected pin if we have one
	if (InputArrayPin->LinkedTo.Num()) {
		bPrioritizeInputPin = true;

		//Make sure connected to type is a reference
		FEdGraphPinType ConnectedToPinType = InputArrayPin->LinkedTo[0]->PinType;
		ConnectedToPinType.bIsReference = true;
		ensure(ConnectedToPinType.IsArray());
		
		if (ConnectedToPinType != InputPinType) {
			CachedArrayPinType = ConnectedToPinType;
			InputArrayPin->PinType = ConnectedToPinType;
			bChangedSomething = true;
		}
	} 
	
	FName CurrentFunctionName = SelectedFunctionName;
	UFunction* SorterFunction = ResolveFunction();

	FEdGraphPinType SortFunctionArrayType{};
	bool bSortFunctionDataValid = false;
	if (SorterFunction != NULL) {
		bSortFunctionDataValid = ResolveArrayPinTypeFromFunction(SorterFunction, SortFunctionArrayType);
	}

	//We have initially changed something if we caused the function name update
	bChangedSomething |= CurrentFunctionName != SelectedFunctionName;

	//If input types do not match, we need to update them
	if (InputPinType != SortFunctionArrayType) {
		if (bPrioritizeInputPin || !bSortFunctionDataValid) {
			//Prioritize pin when possible
			if (SelectedFunctionName != NAME_None) {
				SelectedFunctionName = NAME_None;
				SelectedFunctionGuid.Invalidate();
				bChangedSomething = true;
			}

			//If we do not prioritize input pin and it is not a wildcard,
			//reset it to the wildcard because it is not connected to anything
			if (!bPrioritizeInputPin) {
				if (InputArrayPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard) {
					CachedArrayPinType = FEdGraphPinType();
					CachedArrayPinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
					CachedArrayPinType.ContainerType = EPinContainerType::Array;
					CachedArrayPinType.bIsReference = true;

					InputArrayPin->PinType = SortFunctionArrayType;
					bChangedSomething = true;
				}
			}
		} else {
			//Otherwise update the input pin to match the function
			if (InputArrayPin->PinType != SortFunctionArrayType) {
				CachedArrayPinType = SortFunctionArrayType;
				InputArrayPin->PinType = SortFunctionArrayType;
				bChangedSomething = true;
			}
		}
	}
	if (bChangedSomething) {
		GetGraph()->NotifyGraphChanged();
		
		UBlueprint* Blueprint = GetBlueprint();
		if(!Blueprint->bBeingCompiled) {
			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
			Blueprint->BroadcastChanged();
		}
	}
}

void UK2Node_ArraySort::PinConnectionListChanged(UEdGraphPin* Pin) {
	Super::PinConnectionListChanged(Pin);
	UpdateArrayPinTypesAndSortFunction();
}

void UK2Node_ArraySort::PinTypeChanged(UEdGraphPin* Pin) {
	Super::PinTypeChanged(Pin);
	UpdateArrayPinTypesAndSortFunction();
}

void UK2Node_ArraySort::NodeConnectionListChanged() {
	Super::NodeConnectionListChanged();
	UpdateArrayPinTypesAndSortFunction();
}

UClass* UK2Node_ArraySort::GetScopeClass(bool bDontUseSkeletalClassForSelf) const {
	UEdGraphPin* Pin = FindPin(UEdGraphSchema_K2::PN_Self);
	if (Pin == nullptr) {
		return nullptr;
	}

	check(Pin->LinkedTo.Num() <= 1);

	bool bUseSelf = false;
	if(Pin->LinkedTo.Num() == 0) {
		bUseSelf = true;
	} else {
		if(const UEdGraphPin* ResultPin = Pin->LinkedTo[0]) {
			ensure(UEdGraphSchema_K2::PC_Object == ResultPin->PinType.PinCategory);
			if (UEdGraphSchema_K2::PN_Self == ResultPin->PinType.PinSubCategory) {
				bUseSelf = true;
			}
			if(UClass* TrueScopeClass = Cast<UClass>(ResultPin->PinType.PinSubCategoryObject.Get())) {
				if(const UBlueprint* ScopeClassBlueprint = Cast<UBlueprint>(TrueScopeClass->ClassGeneratedBy)) {
					if(ScopeClassBlueprint->SkeletonGeneratedClass) {
						return ScopeClassBlueprint->SkeletonGeneratedClass;
					}
				}
				return TrueScopeClass;
			}
		}
	}
	if (bUseSelf && HasValidBlueprint()) {
		if (const UBlueprint* ScopeClassBlueprint = GetBlueprint()) {
			return bDontUseSkeletalClassForSelf ? ScopeClassBlueprint->GeneratedClass : ScopeClassBlueprint->SkeletonGeneratedClass;
		}
	}
	return nullptr;
}

FName UK2Node_ArraySort::GetFunctionName() const {
	return SelectedFunctionName;
}

UEdGraphPin* UK2Node_ArraySort::GetArrayInPin() const {
	return FindPin(FK2Node_ArraySort_Helper::ArrayInputName);
}

UEdGraphPin* UK2Node_ArraySort::GetObjectInPin() const {
	return FindPin(UEdGraphSchema_K2::PN_Self);
}

FText UK2Node_ArraySort::GetNodeTitle(ENodeTitleType::Type TitleType) const {
	return LOCTEXT("ArraySortNodeTitle", "Sort Array");
}

FText UK2Node_ArraySort::GetTooltipText() const {
	return LOCTEXT("ArraySortNodeTitle_Tooltip", "Sort array elements using the provided comparator function\nComparator should return true when item A is less than item B\n\nProvided by SMLEditor");
}

UObject* UK2Node_ArraySort::GetJumpTargetForDoubleClick() const {
	const UClass* ScopeClass = GetScopeClass();

	//We only need to handle actual functions and not the events,
	//because sort nodes require functions that return a value, and events cannot return a value by definition
	if (UBlueprint* ScopeClassBlueprint = (ScopeClass != nullptr) ? Cast<UBlueprint>(ScopeClass->ClassGeneratedBy) : nullptr) {
		if (UEdGraph* FoundGraph = FindObject<UEdGraph>(ScopeClassBlueprint, *GetFunctionName().ToString())) {
			if (!FBlueprintEditorUtils::IsGraphIntermediate(FoundGraph)) {
				return FoundGraph;
			}
		}
	}
	return NULL;
}

void UK2Node_ArraySort::AddSearchMetaDataInfo(TArray<struct FSearchTagDataPair>& OutTaggedMetaData) const {
	Super::AddSearchMetaDataInfo(OutTaggedMetaData);

	const FName FunctionName = GetFunctionName();
	if (!FunctionName.IsNone()) {
		OutTaggedMetaData.Add(FSearchTagDataPair(FFindInBlueprintSearchTags::FiB_NativeName, FText::FromName(FunctionName)));
	}
}

TSharedPtr<SGraphNode> UK2Node_ArraySort::CreateVisualWidget() {
	return SNew(SGraphNodeK2ArraySort, this);
}

void UK2Node_ArraySort::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) {
	Super::ExpandNode(CompilerContext, SourceGraph);

	FText OutErrorText;
	if(!ValidateNode(OutErrorText)) {
		CompilerContext.MessageLog.Error(*FString::Printf( TEXT("@@ %s %s"), *LOCTEXT("ArrayNodeWrongComparatorFunction", "Comparator Function Signature Error:").ToString(), *OutErrorText.ToString()), this);
		return;
	}

	UEdGraphPin* ExecPin = FindPinChecked(UEdGraphSchema_K2::PN_Execute, EGPD_Input);
	UEdGraphPin* InputObjectPin = GetObjectInPin();
	UEdGraphPin* InputArrayPin = GetArrayInPin();
	UEdGraphPin* ThenPin = FindPinChecked(UEdGraphSchema_K2::PN_Then, EGPD_Output);
	
	if (GetFunctionName() == NAME_None) {
		CompilerContext.MessageLog.Error(*LOCTEXT("ArraySortNode_InvalidFunctionName", "Node @@ does not reference a valid sort function").ToString(), this);
		return;
	}

	UK2Node_CallFunction* ArraySortFunctionNode = SourceGraph->CreateIntermediateNode<UK2Node_CallArrayFunction>();
	const FName ArraySortFunctionName = GET_MEMBER_NAME_CHECKED(USMLBlueprintArrayLibrary, Array_Sort);
	ArraySortFunctionNode->FunctionReference.SetExternalMember(ArraySortFunctionName, USMLBlueprintArrayLibrary::StaticClass());

	ArraySortFunctionNode->PostPlacedNewNode();
	ArraySortFunctionNode->AllocateDefaultPins();
	CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ArraySortFunctionNode, this);

	//Move input pins from the original node
	UEdGraphPin* IntermediateExecPin = ArraySortFunctionNode->FindPinChecked(UEdGraphSchema_K2::PN_Execute, EGPD_Input);
	UEdGraphPin* IntermediateObjectPin = ArraySortFunctionNode->FindPinChecked(TEXT("Object"), EGPD_Input);
	UEdGraphPin* IntermediateTargetArrayPin = ArraySortFunctionNode->FindPinChecked(TEXT("TargetArray"), EGPD_Input);
	
	CompilerContext.MovePinLinksToIntermediate(*ExecPin, *IntermediateExecPin);
	ArraySortFunctionNode->NotifyPinConnectionListChanged(IntermediateExecPin);
	
	CompilerContext.MovePinLinksToIntermediate(*InputArrayPin, *IntermediateTargetArrayPin);
	ArraySortFunctionNode->NotifyPinConnectionListChanged(IntermediateTargetArrayPin);

	//Move input pin for the object only if it is actually connected
	if (InputObjectPin->LinkedTo.Num()) {
		CompilerContext.MovePinLinksToIntermediate(*InputObjectPin, *IntermediateObjectPin);
		ArraySortFunctionNode->NotifyPinConnectionListChanged(IntermediateObjectPin);
	} else {
		//If it is not connected, we need to spawn an intermediate self node, because it defaults to self
		UK2Node_Self* SelfNode = SourceGraph->CreateIntermediateNode<UK2Node_Self>();
		SelfNode->PostPlacedNewNode();
		SelfNode->AllocateDefaultPins();
		CompilerContext.MessageLog.NotifyIntermediateObjectCreation(SelfNode, this);

		UEdGraphPin* IntermediateSelfPin = SelfNode->FindPinChecked(UEdGraphSchema_K2::PN_Self);
		IntermediateSelfPin->MakeLinkTo(IntermediateObjectPin);
		ArraySortFunctionNode->NotifyPinConnectionListChanged(IntermediateObjectPin);
	}

	//Setup function name pin
	UEdGraphPin* IntermediateFunctionNamePin = ArraySortFunctionNode->FindPinChecked(TEXT("FunctionName"), EGPD_Input);
	IntermediateFunctionNamePin->DefaultValue = GetFunctionName().ToString();

	//Move output exec pin to the intermediate node
	UEdGraphPin* IntermediateThenPin = ArraySortFunctionNode->FindPinChecked(UEdGraphSchema_K2::PN_Then, EGPD_Output);
	CompilerContext.MovePinLinksToIntermediate(*ThenPin, *IntermediateThenPin);
	ArraySortFunctionNode->NotifyPinConnectionListChanged(IntermediateThenPin);
	
	//Break links to everything just in case
	BreakAllNodeLinks();
}

void UK2Node_ArraySort::SetFunction(FName Name) {
	SelectedFunctionName = Name;
	SelectedFunctionGuid.Invalidate();
	GetGraph()->NotifyGraphChanged();
	
	UpdateArrayPinTypesAndSortFunction();
}

FText UK2Node_ArraySort::GetMenuCategory() const {
	return LOCTEXT("ArraySortNodeCategory", "Utilities | Array");
}

void UK2Node_ArraySort::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const {
	UClass* NodeClass = GetClass();
	
	if (ActionRegistrar.IsOpenForRegistration(NodeClass)) {
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(NodeClass);
		ActionRegistrar.AddBlueprintAction(NodeClass, NodeSpawner);
	}
}

#undef LOCTEXT_NAMESPACE

PRAGMA_ENABLE_OPTIMIZATION