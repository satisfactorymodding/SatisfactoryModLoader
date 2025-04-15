#include "Nodes/K2Node_GetMixinTargetObject.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "EditorCategoryUtils.h"
#include "K2Node_CallFunction.h"
#include "K2Node_DynamicCast.h"
#include "K2Node_Self.h"
#include "KismetCompiler.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Patching/BlueprintHookBlueprint.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

const FName UK2Node_GetMixinTargetObject::TargetOutputPinName(TEXT("Target"));

void UK2Node_GetMixinTargetObject::AllocateDefaultPins() {
	const UHookBlueprint* OwnerBlueprint = Cast<UHookBlueprint>(FBlueprintEditorUtils::FindBlueprintForNode(this));

	// Fallback to UObject as output pin if we cannot resolve the real target type
	UClass* TargetClass = OwnerBlueprint && OwnerBlueprint->BlueprintType != BPTYPE_FunctionLibrary && OwnerBlueprint->MixinTargetClass ? OwnerBlueprint->MixinTargetClass : UObject::StaticClass();
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, TargetClass, TargetOutputPinName);
}

FText UK2Node_GetMixinTargetObject::GetTooltipText() const {
	return LOCTEXT("MixinTargetNode_Desc", "Returns a reference to an Object this Mixin is attached to. Type of the reference is based on the Mixin Target Class.");
}

FText UK2Node_GetMixinTargetObject::GetNodeTitle(const ENodeTitleType::Type TitleType) const {
	if (TitleType == ENodeTitleType::MenuTitle) {
		return LOCTEXT("MixinTargetNode_MenuTitle", "Get a reference to Mixin Target");
	}
	return LOCTEXT("MixinTargetNode_Title", "Mixin Target");
}

void UK2Node_GetMixinTargetObject::ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const {
	Super::ValidateNodeDuringCompilation(MessageLog);

	// Make sure the owner function is not static
	const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();
	if(Schema->IsStaticFunctionGraph(GetGraph())) {
		MessageLog.Error(*LOCTEXT("InvalidMixinTargetNode_CannotBeStatic", "Mixin Target Node @@ cannot be used in a static function.").ToString(), this);
	}

	// We might not actually have an owner blueprint in some cases on intermediate graph nodes
	const UBlueprint* OwnerBlueprint = FBlueprintEditorUtils::FindBlueprintForNode(this);
	if (OwnerBlueprint != nullptr) {
		// This node cannot be used outside the hook blueprints with a valid target class
		const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(OwnerBlueprint);
		if (HookBlueprint == nullptr || HookBlueprint->BlueprintType == BPTYPE_FunctionLibrary || HookBlueprint->MixinTargetClass == nullptr) {
			MessageLog.Error(*LOCTEXT("InvalidMixinTargetNode_InvalidOuterBlueprint", "Mixin Target Node @@ can only be used in a Mixin Blueprint.").ToString(), this);
		}
	}
}

void UK2Node_GetMixinTargetObject::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) {
	UEdGraphPin* TargetOutputPin = FindPinChecked(TargetOutputPinName, EGPD_Output);
	UClass* TargetClass = Cast<UClass>(TargetOutputPin->PinType.PinSubCategoryObject);
	
	// Create self node
	UK2Node_Self* SelfNode = CompilerContext.SpawnIntermediateNode<UK2Node_Self>(this, SourceGraph);
	SelfNode->AllocateDefaultPins();
	UEdGraphPin* SelfPin = SelfNode->FindPinChecked(UEdGraphSchema_K2::PN_Self);

	// Create Get Outer Object node
	UK2Node_CallFunction* GetOuterObjectNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	GetOuterObjectNode->SetFromFunction(UKismetSystemLibrary::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UKismetSystemLibrary, GetOuterObject)));
	GetOuterObjectNode->AllocateDefaultPins();
	UEdGraphPin* OuterObjectReturnValuePin = GetOuterObjectNode->FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue);
	UEdGraphPin* ObjectInputPin = GetOuterObjectNode->FindPinChecked(TEXT("Object"));

	// Link self node to object input pin on the Get Outer Object node
	ObjectInputPin->MakeLinkTo(SelfPin);

	// Create dynamic cast node
	UK2Node_DynamicCast* DynamicCastNode = CompilerContext.SpawnIntermediateNode<UK2Node_DynamicCast>(this, SourceGraph);
	DynamicCastNode->TargetType = TargetClass ? TargetClass : UObject::StaticClass();
	DynamicCastNode->SetPurity(true);
	DynamicCastNode->AllocateDefaultPins();

	// Link outer node to a cast node, and move pinks from our target pin to the cast result pin of the cast node
	DynamicCastNode->GetCastSourcePin()->MakeLinkTo(OuterObjectReturnValuePin);
	DynamicCastNode->NotifyPinConnectionListChanged(DynamicCastNode->GetCastSourcePin());
	CompilerContext.MovePinLinksToIntermediate(*TargetOutputPin, *DynamicCastNode->GetCastResultPin());
}

void UK2Node_GetMixinTargetObject::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const {
	if (ActionRegistrar.IsOpenForRegistration(GetClass())) {
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		ActionRegistrar.AddBlueprintAction(GetClass(), NodeSpawner);
	}
}

bool UK2Node_GetMixinTargetObject::IsActionFilteredOut(const FBlueprintActionFilter& Filter) {
	for (UBlueprint* TargetBlueprint : Filter.Context.Blueprints) {
		// Filter the action out if any of the target blueprints are not mixin blueprints
		const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(TargetBlueprint);
		if (HookBlueprint == nullptr || HookBlueprint->BlueprintType == BPTYPE_FunctionLibrary || HookBlueprint->MixinTargetClass == nullptr) {
			return true;
		}
	}
	return Super::IsActionFilteredOut(Filter);
}

FText UK2Node_GetMixinTargetObject::GetMenuCategory() const {
	return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::Variables);
}

#undef LOCTEXT_NAMESPACE
