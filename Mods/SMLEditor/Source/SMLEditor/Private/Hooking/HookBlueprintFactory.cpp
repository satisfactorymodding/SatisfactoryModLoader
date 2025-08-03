#include "Hooking/HookBlueprintFactory.h"
#include "AssetTypeCategories.h"
#include "Hooking/EdGraphSchema_HookTarget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Patching/BlueprintHookBlueprint.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

UHookBlueprintFactory::UHookBlueprintFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UHookBlueprint::StaticClass();
	ParentClass = UStaticBlueprintHook::StaticClass();
	BlueprintType = BPTYPE_FunctionLibrary;
	bSkipClassPicker = true;
}

FText UHookBlueprintFactory::GetDisplayName() const {
	return LOCTEXT("BlueprintHookFactoryDescription", "Blueprint Hook (SML)");
}

FName UHookBlueprintFactory::GetNewAssetThumbnailOverride() const {
	return TEXT("ClassThumbnail.BlueprintFunctionLibrary");
}

uint32 UHookBlueprintFactory::GetMenuCategories() const {
	return EAssetTypeCategories::Blueprint;
}

FText UHookBlueprintFactory::GetToolTip() const {
	return LOCTEXT("BlueprintHookTooltip", "Blueprint Hooks are Blueprint assets that contain definitions for Functions, the calls to which are injected into other Blueprints at runtime.\n\nImplemented by SMLEditor");
}

UObject* UHookBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) {
	// Make sure we are trying to factory a blueprint, then create and init one
	check(Class->IsChildOf(UBlueprint::StaticClass()));
	if (UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, BlueprintType, UHookBlueprint::StaticClass(), UHookBlueprintGeneratedClass::StaticClass(), CallingContext))) {
		// Create hook target graph.
		// TODO: We might want to ensure one is created on PostLoad as well
		HookBlueprint->HookTargetGraph = FBlueprintEditorUtils::CreateNewGraph(HookBlueprint, TEXT("HookTargetGraph"), UEdGraph::StaticClass(), UEdGraphSchema_HookTarget::StaticClass());
		HookBlueprint->HookTargetGraph->bAllowDeletion = false;
		HookBlueprint->HookTargetGraph->bAllowRenaming = false;
		
		HookBlueprint->Status = BS_Dirty;
		HookBlueprint->Modify();
		return HookBlueprint;
	}
	return nullptr;
}

FString UHookBlueprintFactory::GetDefaultNewAssetName() const {
	return FString(TEXT("NewBlueprintHook"));
}

#undef LOCTEXT_NAMESPACE
