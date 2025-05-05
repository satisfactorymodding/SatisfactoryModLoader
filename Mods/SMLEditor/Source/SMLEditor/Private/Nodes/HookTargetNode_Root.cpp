#include "Nodes/HookTargetNode_Root.h"
#include "EdGraph/EdGraph.h"
#include "Hooking/EdGraphSchema_HookTarget.h"
#include "GraphNodes/GraphNodeHookTarget_Root.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Patching/BlueprintHookBlueprint.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

void UHookTargetNode_Root::AllocateDefaultPins() {
	Super::AllocateDefaultPins();
	CreatePin(EGPD_Input, UEdGraphSchema_HookTarget::PC_HookTargetExpression, GetTargetExpressionPinName());
}

FLinearColor UHookTargetNode_Root::GetNodeTitleColor() const {
	return FLinearColor::Yellow;
}

FText UHookTargetNode_Root::GetTooltipText() const {
	return LOCTEXT("HookTargetNodeRoot_Tooltip", "Hook Nodes are Entry Points into the Hook Graph and facilitate injection of user-defined Hook Function Calls into provided Target Functions defined in other Blueprints.");
}

void UHookTargetNode_Root::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const {
	Super::ValidateNodeDuringCompilation(MessageLog);

	// Make sure that we are not attempting to target the function in this blueprint
	if (TargetFunctionReference.IsSelfContext()) {
		MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeRoot_CannotTargetSelf", "Blueprint Hook Node @@ attempt to Target Member {0} in Hook Blueprint. Targeting functions in the same Blueprint as the Hook is not allowed."),
			FText::FromName(TargetFunctionReference.GetMemberName())).ToString(), this);
	}
	// Make sure a reference to the target function can be resolved
    else if (TargetFunctionReference.ResolveMember<UFunction>() == nullptr) {
    	MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNodeRoot_CannotResolveTarget", "Blueprint Hook Node @@ could not resolve Target Member {0} in Scope {1}. Target Function might have been removed or renamed."),
    		FText::FromName(TargetFunctionReference.GetMemberName()), FText::FromString(GetPathNameSafe(TargetFunctionReference.GetScope()))).ToString(), this);
    }

	// Make sure the hook function can be resolved in the self context
	if (!HookFunctionReference.IsSelfContext()) {
		MessageLog.Error(*LOCTEXT("HookTargetNodeRoot_CannotReferenceHookOnOtherBlueprint", "Blueprint Hook Node @@ does not have a valid Hook Implementation").ToString(), this);
	}
	// Cannot check if hooked function is actually defined here, since we have not compiled the class layout at this point
}

TSharedPtr<SGraphNode> UHookTargetNode_Root::CreateVisualWidget() {
	return SNew(SGraphNodeHookTarget_Root, this);
}

void UHookTargetNode_Root::GetMemberReferenceDescriptors(TArray<FHookTargetNodeMemberReferenceDescriptor>& OutMemberReferenceDescriptors) const {
	OutMemberReferenceDescriptors.Add(FHookTargetNodeMemberReferenceDescriptor{
		GET_MEMBER_NAME_CHECKED(ThisClass, TargetFunctionReference),
		LOCTEXT("HookTargetNodeRoot_TargetFunction", "Target Function"),
		LOCTEXT("HookTargetNodeRoot_TargetFunction_Tooltip", "The Blueprint class and function to hook. Actor Mixins always use their Target class."),
		EHTNMemberRefFlags::FunctionReference | EHTNMemberRefFlags::FunctionsWithScriptOnly | EHTNMemberRefFlags::HookTargetFunctionReference
	});
	OutMemberReferenceDescriptors.Add(FHookTargetNodeMemberReferenceDescriptor{
		GET_MEMBER_NAME_CHECKED(ThisClass, HookFunctionReference),
		LOCTEXT("HookTargetNodeRoot_HookFunction", "Hook Implementation"),
		LOCTEXT("HookTargetNodeRoot_HookFunction_Tooltip", "The user-defined Function Call that will be injected by the hook"),
		EHTNMemberRefFlags::FunctionReference | EHTNMemberRefFlags::SelfContext
	});
}

FMemberReference UHookTargetNode_Root::GetMemberReferenceByName(const FName& Name) const {
	if (Name == GET_MEMBER_NAME_CHECKED(ThisClass, TargetFunctionReference)) {
		return TargetFunctionReference;
	}
	if (Name == GET_MEMBER_NAME_CHECKED(ThisClass, HookFunctionReference)) {
		return HookFunctionReference;
	}
	return FMemberReference();
}

bool UHookTargetNode_Root::SetMemberReferenceByName(const FName& Name, const FMemberReference& NewMemberReference) {
	if (Name == GET_MEMBER_NAME_CHECKED(ThisClass, TargetFunctionReference)) {
		Modify();
		TargetFunctionReference = NewMemberReference;
		if (GetGraph()) {
			GetGraph()->NotifyNodeChanged(this);
		}
		return true;
	}
	if (Name == GET_MEMBER_NAME_CHECKED(ThisClass, HookFunctionReference)) {
		Modify();
		HookFunctionReference = NewMemberReference;
		if (GetGraph()) {
			GetGraph()->NotifyNodeChanged(this);
		}
		return true;
	}
	return false;
}

void UHookTargetNode_Root::CompileRoot(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, FBlueprintHookDefinition& OutBlueprintHookDefinition) const {
	// Set hook type and insert location to invalid, child classes will have to override these
	OutBlueprintHookDefinition.Type = EBlueprintFunctionHookType::Invalid;
	OutBlueprintHookDefinition.InsertLocation = EBlueprintFunctionHookInsertLocation::Invalid;
	
	// Copy target selection settings to the hook
	OutBlueprintHookDefinition.TargetSelectionMode = TargetSelectionMode;
	OutBlueprintHookDefinition.TargetOrdinal = TargetOrdinal;

	// If current blueprint is not a Function Library, we must have mixin target class as the target function scope, otherwise this hook is invalid
	const UHookBlueprint* OwnerBlueprint = Cast<UHookBlueprint>(FBlueprintEditorUtils::FindBlueprintForNode(this));
	if (OwnerBlueprint && OwnerBlueprint->BlueprintType != BPTYPE_FunctionLibrary) {
		if (!TargetFunctionReference.IsSelfContext() && TargetFunctionReference.GetScope() && TargetFunctionReference.GetScope() != OwnerBlueprint->MixinTargetClass) {
			MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNode_Root_InvalidHookTargetScope", "Blueprint Hook Node @@ does not have a valid Class as a Target Function Scope. All hooks in this Blueprint must target Class {0}."),
				FText::FromString(GetPathNameSafe(OwnerBlueprint->MixinTargetClass))).ToString(), this);
			return;
		}
	}

	// Resolve target function. Avoid passing self context since we never want the target to be on this blueprint
	OutBlueprintHookDefinition.TargetFunction = TargetFunctionReference.ResolveMember<UFunction>();

	// Resolve hook function in this blueprint
	OutBlueprintHookDefinition.HookFunction = HookFunctionReference.ResolveMember<UFunction>(SelfClass);
	if (OutBlueprintHookDefinition.HookFunction == nullptr) {
		MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNode_Root_CannotResolveHook", "Blueprint Hook Node @@ could not find Hook Implementation function {0}. Hook implementation function might have been removed."),
			FText::FromName(TargetFunctionReference.GetMemberName())).ToString(), this);
		return;
	}

	// Resolve the target specifier pin
	const UEdGraphPin* TargetSpecifierPin = FindPin(GetTargetExpressionPinName(), EGPD_Input);
	if (TargetSpecifierPin == nullptr) {
		MessageLog.Error(*FText::Format(LOCTEXT("HookTargetNode_Root_CannotResolveTargetPin", "INTERNAL COMPILER ERROR: Blueprint Hook Node @@ does not have a valid Target pin {0}."),
			FText::FromName(GetTargetExpressionPinName())).ToString(), this);
		return;
	}
	// Evaluate target specifier pin
	OutBlueprintHookDefinition.TargetSpecifier = EvaluateNodeInputPin<UBlueprintHookTargetSpecifier>(MessageLog, SelfClass, DerivedDataOuter, TargetSpecifierPin);
}

FLinearColor UHookTargetNode_InsertionHook::GetNodeTitleColor() const {
	return InsertLocation == EBlueprintFunctionHookInsertLocation::ReplaceTarget ? FLinearColor::Red : Super::GetNodeTitleColor();
}

FText UHookTargetNode_InsertionHook::HookInsertLocationToText(const EBlueprintFunctionHookInsertLocation InsertLocation) {
	switch(InsertLocation) {
		case EBlueprintFunctionHookInsertLocation::BeforeTarget: return LOCTEXT("HookTargetNodeInsertionHook_BeforeTarget", "Before Statement");
		case EBlueprintFunctionHookInsertLocation::AfterTarget: return LOCTEXT("HookTargetNodeInsertionHook_AfterTarget", "After Statement");
		case EBlueprintFunctionHookInsertLocation::ReplaceTarget: return LOCTEXT("HookTargetNodeInsertionHook_ReplaceTarget", "(Replace Statement)");
		default: return LOCTEXT("HookTargetNodeInsertionHook_Invalid", "Invalid");
	}
}

FText UHookTargetNode_InsertionHook::GetNodeTitle(const ENodeTitleType::Type TitleType) const {
	const FName TargetFunctionName = TargetFunctionReference.GetMemberName();
	const UClass* TargetClass = TargetFunctionReference.GetScope();
	const FName HookFunctionName = HookFunctionReference.GetMemberName();

	// Use full node title if we have a valid hook configuration
	if (TitleType == ENodeTitleType::FullTitle && (TargetFunctionName != NAME_None && HookFunctionName != NAME_None && TargetClass)) {
		return FText::Format(LOCTEXT("HookTargetNodeInsertionHook_FullName", "Call Hook {3}\n{2}\n{1}"),
			FText::FromName(HookFunctionName), FText::FromName(TargetFunctionName), TargetClass->GetDisplayNameText(), HookInsertLocationToText(InsertLocation));
	}
	// Use short title in all other cases
	return FText::Format(LOCTEXT("HookTargetNodeInsertionHook_ShortName", "Call Hook {0}"), HookInsertLocationToText(InsertLocation));
}

FText UHookTargetNode_InsertionHook::GetTooltipText() const {
	return FText::Format(LOCTEXT("HookTargetNodeInsertionHook_Tooltip", "{0}\n\n{1}"), UHookTargetNode_Root::GetTooltipText(), UHookTargetNode_InsertionHook::Description);
}

void UHookTargetNode_InsertionHook::GetMenuEntries(FGraphContextMenuBuilder& ContextMenuBuilder) const {
	// Utility lambda to create a template with the provided insert location
	const auto RegisterInsertionHookAction = [&](const EBlueprintFunctionHookInsertLocation InsertLocation) {
		const TSharedPtr<FEdGraphSchemaAction_NewHookTargetNode> NodePlacementAction = MakeShared<FEdGraphSchemaAction_NewHookTargetNode>(
			LOCTEXT("HookTargetNodeInsertionHook_Category", "Hooks"),
			FText::Format(LOCTEXT("HookTargetNodeInsertionHook_MenuName", "Create Insertion Hook - {0}"), HookInsertLocationToText(InsertLocation)),
			UHookTargetNode_InsertionHook::Description, 0);

		UHookTargetNode_InsertionHook* NodeTemplate = ContextMenuBuilder.CreateTemplateNode<UHookTargetNode_InsertionHook>();
		NodeTemplate->InsertLocation = InsertLocation;
		NodePlacementAction->NodeTemplate = NodeTemplate;

		if (NodePlacementAction->IsNodeActionRelevantToTheGraphContext(ContextMenuBuilder)) {
			ContextMenuBuilder.AddAction(NodePlacementAction);
		}
	};

	RegisterInsertionHookAction(EBlueprintFunctionHookInsertLocation::BeforeTarget);
	RegisterInsertionHookAction(EBlueprintFunctionHookInsertLocation::AfterTarget);
	RegisterInsertionHookAction(EBlueprintFunctionHookInsertLocation::ReplaceTarget);
}

void UHookTargetNode_InsertionHook::CompileRoot(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, FBlueprintHookDefinition& OutBlueprintHookDefinition) const {
	Super::CompileRoot(MessageLog, SelfClass, DerivedDataOuter, OutBlueprintHookDefinition);

	// Override type of the hook and set insertion location
	OutBlueprintHookDefinition.Type = EBlueprintFunctionHookType::InsertionHook;
	OutBlueprintHookDefinition.InsertLocation = InsertLocation;
}

FName UHookTargetNode_InsertionHook::GetTargetExpressionPinName() const {
	return TEXT("TargetStatement");
}

FText UHookTargetNode_Redirect::GetTooltipText() const {
	return FText::Format(LOCTEXT("HookTargetNodeRedirectHook_Tooltip", "{0}\n\n{1}"), UHookTargetNode_Root::GetTooltipText(), UHookTargetNode_Redirect::Description);
}

FText UHookTargetNode_Redirect::GetNodeTitle(const ENodeTitleType::Type TitleType) const {
	const FName TargetFunctionName = TargetFunctionReference.GetMemberName();
	const UClass* TargetClass = TargetFunctionReference.GetScope();
	const FName HookFunctionName = HookFunctionReference.GetMemberName();

	// Use full node title if we have a valid hook configuration
	if (TitleType == ENodeTitleType::FullTitle && (TargetFunctionName != NAME_None && HookFunctionName != NAME_None && TargetClass)) {
		return FText::Format(LOCTEXT("HookTargetNodeRedirectHook_FullName", "Redirect Expression\n{2}\n{1}"),
			FText::FromName(HookFunctionName), FText::FromName(TargetFunctionName), TargetClass->GetDisplayNameText());
	}
	// Use short title in all other cases
	return LOCTEXT("HookTargetNodeRedirectHook_ShortName", "Redirect Expression Through Hook");
}

void UHookTargetNode_Redirect::GetMenuEntries(FGraphContextMenuBuilder& ContextMenuBuilder) const {
	const TSharedPtr<FEdGraphSchemaAction_NewHookTargetNode> NodePlacementAction = MakeShared<FEdGraphSchemaAction_NewHookTargetNode>(
			LOCTEXT("HookTargetNodeRedirectHook_Category", "Hooks"),
			LOCTEXT("HookTargetNodeRedirectHook_MenuName", "Create Redirect Hook"),
			UHookTargetNode_Redirect::Description, 0);
	NodePlacementAction->NodeTemplate = ContextMenuBuilder.CreateTemplateNode<UHookTargetNode_Redirect>();
	
	if (NodePlacementAction->IsNodeActionRelevantToTheGraphContext(ContextMenuBuilder)) {
		ContextMenuBuilder.AddAction(NodePlacementAction);
	}
}

void UHookTargetNode_Redirect::CompileRoot(FCompilerResultsLog& MessageLog, UClass* SelfClass, UObject* DerivedDataOuter, FBlueprintHookDefinition& OutBlueprintHookDefinition) const {
	Super::CompileRoot(MessageLog, SelfClass, DerivedDataOuter, OutBlueprintHookDefinition);

	// Override type of the hook to the redirect hook
	OutBlueprintHookDefinition.Type = EBlueprintFunctionHookType::RedirectHook;

	// Validate that target specifier is not a statement
	if (OutBlueprintHookDefinition.TargetSpecifier && OutBlueprintHookDefinition.TargetSpecifier->IsStatementOnlyTarget()) {
		MessageLog.Error(*LOCTEXT("HookTargetNodeRedirectHook_IncompatibleTargetSpecifier", "Node @@ is a Redirect Hook, but its Target Expression is a Statement, and does not have a valid type.").ToString(), this);
	}
}

FName UHookTargetNode_Redirect::GetTargetExpressionPinName() const {
	return TEXT("TargetExpression");
}

#undef LOCTEXT_NAMESPACE
