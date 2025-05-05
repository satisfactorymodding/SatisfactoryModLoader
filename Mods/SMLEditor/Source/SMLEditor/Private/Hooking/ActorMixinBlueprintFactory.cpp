#include "Hooking/ActorMixinBlueprintFactory.h"
#include "AssetTypeCategories.h"
#include "ClassViewerFilter.h"
#include "Hooking/EdGraphSchema_HookTarget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Patching/BlueprintHookBlueprint.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

class FActorBasedBlueprintClassFilter : public IClassViewerFilter {
public:
	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override {
		if(InClass != nullptr) {
			const bool bGeneratedByBlueprint = Cast<UBlueprint>(InClass->ClassGeneratedBy) != nullptr;
			const bool bActorBased = InClass->IsChildOf(AActor::StaticClass());
			return bGeneratedByBlueprint && bActorBased;
		}
		return false;
	}
	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override {
		const bool bActorBased = InUnloadedClassData->IsChildOf(AActor::StaticClass());
		return bActorBased;
	}
};

UActorMixinBlueprintFactory::UActorMixinBlueprintFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UHookBlueprint::StaticClass();
	ParentClass = UBlueprintActorMixin::StaticClass();
	BlueprintType = BPTYPE_Normal;
	bSkipClassPicker = true;
}

bool UActorMixinBlueprintFactory::ConfigureProperties() {
	// Null the target class to ensure one is selected
	MixinTargetClass = nullptr;

	// Fill in options
	FClassViewerInitializationOptions Options;

	// Show tree view selector with no root class and with filter to only allow selection of blueprint actor-derived classes
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.DisplayMode = EClassViewerDisplayMode::TreeView;
	Options.bShowObjectRootClass = false;
	Options.bShowDefaultClasses = false;
	Options.ClassFilters.Add(MakeShared<FActorBasedBlueprintClassFilter>());

	// Allow selecting unloaded blueprints and load them on selection
	Options.bShowUnloadedBlueprints = true;
	Options.bEnableClassDynamicLoading = true;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::Dynamic;
	
	// Allow overriding properties
	OnConfigurePropertiesDelegate.ExecuteIfBound(&Options);

	const FText TitleText = LOCTEXT("CreateBlueprintMixin_SelectTargetClassTitle", "Pick Mixin Target Class");
	UClass* ChosenMixinTargetClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenMixinTargetClass, UHookBlueprint::StaticClass());

	if (bPressedOk && Cast<UBlueprintGeneratedClass>(ChosenMixinTargetClass) != nullptr) {
		MixinTargetClass = Cast<UBlueprintGeneratedClass>(ChosenMixinTargetClass);
		return true;
	}
	return false;
}

FText UActorMixinBlueprintFactory::GetDisplayName() const {
	return LOCTEXT("BlueprintMixinFactoryDescription", "Blueprint Mixin (SML)");
}

FName UActorMixinBlueprintFactory::GetNewAssetThumbnailOverride() const {
	return TEXT("ClassThumbnail.BlueprintInterface");
}

uint32 UActorMixinBlueprintFactory::GetMenuCategories() const {
	return EAssetTypeCategories::Blueprint;
}

FText UActorMixinBlueprintFactory::GetToolTip() const {
	return LOCTEXT("BlueprintMixinTooltip", "Blueprint Mixins are Blueprint assets that are automatically created for each Actor Instance the Mixin is applied to. They can be used to add additional Components to the Target Actor, hook Actor Functions, or implement additional logic.\n\nImplemented by SMLEditor");
}

UObject* UActorMixinBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) {
	check(Class->IsChildOf(UHookBlueprint::StaticClass()));
	check(MixinTargetClass && !MixinTargetClass->IsNative());

	// Create a new blueprint using the provided settings
	if (UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, BlueprintType, Class, UHookBlueprintGeneratedClass::StaticClass(), CallingContext))) {
		// Populate mixin target class and create overlay component tree
		HookBlueprint->MixinTargetClass = MixinTargetClass;
		HookBlueprint->OverlayComponentTree = NewObject<UBlueprintMixinOverlayComponentTree>(HookBlueprint->GeneratedClass, TEXT("OverlayComponentTree"), RF_Transactional);
		
		// Create hook target graph
		HookBlueprint->HookTargetGraph = FBlueprintEditorUtils::CreateNewGraph(HookBlueprint, TEXT("HookTargetGraph"), UEdGraph::StaticClass(), UEdGraphSchema_HookTarget::StaticClass());
		HookBlueprint->HookTargetGraph->bAllowDeletion = false;
		HookBlueprint->HookTargetGraph->bAllowRenaming = false;
		
		HookBlueprint->Status = BS_Dirty;
		HookBlueprint->Modify();
		return HookBlueprint;
	}
	return nullptr;
}

FString UActorMixinBlueprintFactory::GetDefaultNewAssetName() const {
	return FString(TEXT("NewActorMixin"));
}

#undef LOCTEXT_NAMESPACE
