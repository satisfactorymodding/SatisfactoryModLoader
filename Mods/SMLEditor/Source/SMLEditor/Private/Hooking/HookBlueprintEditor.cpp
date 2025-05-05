#include "Hooking/HookBlueprintEditor.h"
#include "AssetSelection.h"
#include "BlueprintEditorContext.h"
#include "BlueprintEditorModes.h"
#include "BlueprintEditorTabs.h"
#include "ComponentAssetBroker.h"
#include "GraphEditorActions.h"
#include "SBlueprintEditorToolbar.h"
#include "SComponentClassCombo.h"
#include "Components/PrimitiveComponent.h"
#include "EdGraph/EdGraph.h"
#include "Engine/MemberReference.h"
#include "Hooking/MixinBlueprintEditorViewport.h"
#include "Hooking/OverlayComponentTreeEditor.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Misc/MessageDialog.h"
#include "Patching/BlueprintHookBlueprint.h"
#include "Toolkits/ToolkitManager.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

static const FName HookBlueprintComponentTreeEditorID(TEXT("OverlayComponentTreeEditor"));
static const FName HookBlueprintViewportEditorID(TEXT("OverlayComponentTreeViewport"));

void FHookBlueprintEditorCommands::RegisterCommands() {
	UI_COMMAND(EditHookBlueprintHookGraph, "Hook Graph", "Open a window to edit the Hook Blueprint's Hook Graph. If the button is grayed out, you already have the window open.", EUserInterfaceActionType::Button, FInputChord());
}

FName FHookBlueprintEditor::GetToolkitFName() const {
	return TEXT("HookBlueprintEditor");
}

bool FHookBlueprintEditor::ReparentBlueprint_IsVisible() const {
	// Parent class of the hook blueprint defines its type, hook blueprints cannot be reparented.
	return false;
}

void FHookBlueprintEditor::AddReferencedObjects(FReferenceCollector& Collector) {
	FBlueprintEditor::AddReferencedObjects(Collector);
	// Add weak reference to the preview actor so that re-instancing can replace it in case target BP is recompiled
	Collector.AddReferencedObject(OverlayPreviewActorWeakPtr);
}

void FHookBlueprintEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) {
	FBlueprintEditor::NotifyPostChange( PropertyChangedEvent, PropertyThatChanged );

	if (IsEditingSingleBlueprint()) {
		UHookBlueprint* Blueprint = CastChecked<UHookBlueprint>(GetBlueprintObj());

		// Update actor preview if we have edited any objects located inside the blueprint package
		bool bShouldRefreshActorPreview = PropertyChangedEvent.GetNumObjectsBeingEdited() == 0;
		for (int32 ObjectIndex = 0; ObjectIndex < PropertyChangedEvent.GetNumObjectsBeingEdited(); ObjectIndex++) {
			const UObject* Object = PropertyChangedEvent.GetObjectBeingEdited(ObjectIndex);
			if (Object && Object->GetPackage() == Blueprint->GetPackage()) {
				bShouldRefreshActorPreview = true;
				break;
			}
		}

		// Update preview actor if we have changed any properties on the blueprint
		if (bShouldRefreshActorPreview && PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive && OverlayPreviewActorWeakPtr.IsValid()) {
			UpdateOverlayPreviewActor(Blueprint, false);
		}
	}
}

void FHookBlueprintEditor::RefreshEditors(ERefreshBlueprintEditorReason::Type Reason) {
	FBlueprintEditor::RefreshEditors(Reason);

	// Update overlay preview actor if we currently have one. This will be called as a part of Undo transaction which should move the preview components back and undo any property changes
	if (IsEditingSingleBlueprint() && OverlayPreviewActorWeakPtr.IsValid()) {
		UHookBlueprint* Blueprint = CastChecked<UHookBlueprint>(GetBlueprintObj());
		UpdateOverlayPreviewActor(Blueprint, false);
	}
}

void FHookBlueprintEditor::CreateDefaultCommands() {
	FBlueprintEditor::CreateDefaultCommands();

	FHookBlueprintEditorCommands::Register();

	ToolkitCommands->MapAction(
		FHookBlueprintEditorCommands::Get().EditHookBlueprintHookGraph,
		FExecuteAction::CreateSP(this, &FHookBlueprintEditor::OpenBlueprintHookGraphTab),
		FCanExecuteAction::CreateSP(this, &FHookBlueprintEditor::IsBlueprintHookGraphTabOpen));
}

FGraphAppearanceInfo FHookBlueprintEditor::GetGraphAppearance(UEdGraph* InGraph) const {
	UBlueprint* Blueprint = InGraph != nullptr ? FBlueprintEditorUtils::FindBlueprintForGraph(InGraph) : GetBlueprintObj();
	if (const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(Blueprint)) {
		// Override display name for hook graph
		if (HookBlueprint->HookTargetGraph && HookBlueprint->HookTargetGraph == InGraph) {
			FGraphAppearanceInfo HookGraphAppearanceInfo;
			HookGraphAppearanceInfo.CornerText = LOCTEXT("GraphCornerText_HookTargetGraph", "HOOK");
			return HookGraphAppearanceInfo;
		}
	}
	return FBlueprintEditor::GetGraphAppearance(InGraph);
}

void FHookBlueprintEditor::AddBlueprintHookEditorToolbar(UToolMenu* InMenu) {
	FToolMenuSection& Section = InMenu->FindOrAddSection(TEXT("Settings"));

	Section.AddDynamicEntry(TEXT("HookBlueprintGlobalOptions"), FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection) {
		const UBlueprintEditorToolMenuContext* Context = InSection.FindContext<UBlueprintEditorToolMenuContext>();
		if (Context && Context->GetBlueprintObj()) {
			const FHookBlueprintEditorCommands& HookEditorCommands = FHookBlueprintEditorCommands::Get();
			const FSlateIcon SlateIconOverride(FAppStyle::GetAppStyleSetName(), TEXT("FullBlueprintEditor.EditClassDefaults"));
			InSection.AddEntry(FToolMenuEntry::InitToolBarButton(HookEditorCommands.EditHookBlueprintHookGraph, TAttribute<FText>(), TAttribute<FText>(), SlateIconOverride));
		}
	}));
}

void FHookBlueprintEditor::RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated) {
	if (GetBlueprintObj()) {
		AddApplicationMode(FBlueprintEditorApplicationModes::StandardBlueprintEditorMode, MakeShareable(new FHookBlueprintEditorMode(SharedThis(this), BlueprintSupportsOverlayComponentTree())));
		SetCurrentMode(FBlueprintEditorApplicationModes::StandardBlueprintEditorMode);
	}
}

void FHookBlueprintEditor::CreateDefaultTabContents(const TArray<UBlueprint*>& InBlueprints) {
	FBlueprintEditor::CreateDefaultTabContents(InBlueprints);
	CreateComponentTreeOverlayEditor();
}

void FHookBlueprintEditor::InitHookBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UHookBlueprint* Blueprint) {
	// Perform normal editor initialization
	InitBlueprintEditor(Mode, InitToolkitHost, {Blueprint}, false);

	// Open the hook target graph by default if this is a Hook Library Blueprint. Let Mixin blueprints stay in the Event Graph by default
	if (Blueprint->BlueprintType == BPTYPE_FunctionLibrary && Blueprint->HookTargetGraph != nullptr) {
		OpenBlueprintHookGraphTab();
	}
}

bool FHookBlueprintEditor::BlueprintSupportsOverlayComponentTree() const {
	const UHookBlueprint* OwnerBlueprint = Cast<UHookBlueprint>(GetBlueprintObj());
	return OwnerBlueprint &&
		OwnerBlueprint->ParentClass &&
		OwnerBlueprint->ParentClass->IsChildOf<UBlueprintActorMixin>() &&
		OwnerBlueprint->BlueprintType != BPTYPE_FunctionLibrary &&
		OwnerBlueprint->MixinTargetClass != nullptr &&
		OwnerBlueprint->OverlayComponentTree != nullptr;
}

AActor* FHookBlueprintEditor::GetOverlayPreviewActor() const {
	// We do not need to care about actor being potentially re-instanced here because AddReferencedObjects should take care of that and update the pointer
	return OverlayPreviewActorWeakPtr.Get();
}

void FHookBlueprintEditor::DestroyOverlayPreviewActor() {
	// If we do not support a component tree we do not have an actor to show the overlaid components for
	if (!BlueprintSupportsOverlayComponentTree()) {
		return;
	}
	// Destroy the preview actor if we have one and reset the pointer
	AActor* OverlayPreviewActor = GetOverlayPreviewActor();
	if (OverlayPreviewActor) {
		PreviewScene.GetWorld()->EditorDestroyActor( OverlayPreviewActor, false );
	}
	OverlayPreviewActorWeakPtr.Reset();
}

void FHookBlueprintEditor::UpdateOverlayPreviewActor(UHookBlueprint* InBlueprintObject, bool bForceFullActorUpdate) {
	// If we do not support a component tree we do not have an actor to show the overlaid components for
	if (!BlueprintSupportsOverlayComponentTree()) {
		return;
	}
	AActor* PreviewActor = GetOverlayPreviewActor();
	const UHookBlueprint* PreviewBlueprint = Cast<UHookBlueprint>(GetBlueprintObj());

	// If the Blueprint is changing
	if (InBlueprintObject != PreviewBlueprint || bForceFullActorUpdate) {
		// Destroy the previous actor instance
		DestroyOverlayPreviewActor();

		// Save the Blueprint we're creating a preview for
		PreviewBlueprint = InBlueprintObject;

		// Spawn a new preview actor based on the target actor class
		if (PreviewBlueprint && PreviewBlueprint->MixinTargetClass &&
			PreviewBlueprint->MixinTargetClass->IsChildOf(AActor::StaticClass()) &&
			!PreviewBlueprint->MixinTargetClass->HasAnyClassFlags(CLASS_Abstract | CLASS_Deprecated))
		{
			const FVector SpawnLocation = FVector::ZeroVector;
			const FRotator SpawnRotation = FRotator::ZeroRotator;

			// Spawn an Actor based on the Blueprint's generated class
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnInfo.bNoFail = true;
			SpawnInfo.ObjectFlags = RF_Transient;

			OverlayPreviewActorWeakPtr = PreviewActor = PreviewScene.GetWorld()->SpawnActor(PreviewBlueprint->MixinTargetClass, &SpawnLocation, &SpawnRotation, SpawnInfo);
			check(PreviewActor);

			// Ensure that the actor is visible
			if (PreviewActor->IsHidden()) {
				PreviewActor->SetHidden(false);
				PreviewActor->MarkComponentsRenderStateDirty();				
			}
		}
	} else if (PreviewActor) {
		// Destroy all overlay components, we will need to fully regenerate them
		TArray<UActorComponent*> AllActorComponents;
		PreviewActor->GetComponents(AllActorComponents);

		for (UActorComponent* ActorComponent : AllActorComponents) {

			// Determine if this component or its parent have been created by overlay component tree
			const USceneComponent* ParentComponent = Cast<USceneComponent>(ActorComponent);
			bool bIsComponentCreatedByOverlayComponentTree = ActorComponent->ComponentHasTag(UBlueprintMixinOverlayComponentTree::OverlayComponentTag);
			
			while (ParentComponent != nullptr && !bIsComponentCreatedByOverlayComponentTree) {
				bIsComponentCreatedByOverlayComponentTree |= ParentComponent->ComponentHasTag(UBlueprintMixinOverlayComponentTree::OverlayComponentTag);
				ParentComponent = ParentComponent->GetAttachParent();
			}

			// Destroy the component if it has been created by the component tree
			if (bIsComponentCreatedByOverlayComponentTree) {
				ActorComponent->DestroyComponent();

				// Rename component to avoid naming conflicts in the case where we rerun the SCS and name the new components the same way
				const FName NewBaseName = *FString::Printf(TEXT("TRASH_%s"), *ActorComponent->GetClass()->GetName());
				const FName NewObjectName = MakeUniqueObjectName(PreviewActor, PreviewActor->GetClass(), NewBaseName);
				ActorComponent->Rename(*NewObjectName.ToString(), PreviewActor, REN_ForceNoResetLoaders | REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);
			}
		}
		
		// Now re-register the components and rerun the construction scripts of the base class
		PreviewActor->ReregisterAllComponents();
		PreviewActor->RerunConstructionScripts();
	}

	// Now we have either a fresh preview actor, or an old preview actor with all overlay components removed
	if (PreviewActor != nullptr) {
		if (PreviewBlueprint->OverlayComponentTree != nullptr) {
			PreviewBlueprint->OverlayComponentTree->ExecuteOnActor(PreviewActor, nullptr);
		}
	}

	// Compute actor bounds as the sum of its visible parts or parts with collision
	FBoxSphereBounds::Builder BoundsBuilder;
	for (UActorComponent* Component : PreviewActor->GetComponents()) {
		if (const UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component)) {
			if ((!PrimitiveComponent->bHiddenInGame || PrimitiveComponent->IsCollisionEnabled()) && PrimitiveComponent->Bounds.SphereRadius < HALF_WORLD_MAX) {
				BoundsBuilder += PrimitiveComponent->Bounds;
			}
		}
	}
	PreviewActorBounds = BoundsBuilder;
}

void FHookBlueprintEditor::OnOverlayComponentTreeChanged() {
	if (IsEditingSingleBlueprint()) {
		// We need to full refresh the preview actor when the tree structure changes
		UHookBlueprint* Blueprint = CastChecked<UHookBlueprint>(GetBlueprintObj());
		if (OverlayPreviewActorWeakPtr.IsValid()) {
			UpdateOverlayPreviewActor(Blueprint, true);
		}
	}
}

void FHookBlueprintEditor::CreateComponentTreeOverlayEditor() {
	if (BlueprintSupportsOverlayComponentTree()) {
		HookComponentTreeOverlayEditor = SNew(SOverlayComponentTreeEditor, SharedThis(this));
		HookOverlayComponentTreeViewport = SNew(SMixinBlueprintEditorViewport).BlueprintEditor(SharedThis(this));
	}
}

TSharedPtr<FHookBlueprintEditor> FHookBlueprintEditor::FindEditorForHookBlueprint(const UHookBlueprint* HookBlueprint) {
	if (HookBlueprint != nullptr) {
		const TSharedPtr<IToolkit> FoundAssetEditor = FToolkitManager::Get().FindEditorForAsset(HookBlueprint);
		if (FoundAssetEditor.IsValid()) {
			return StaticCastSharedPtr<FHookBlueprintEditor>(FoundAssetEditor);
		}
	}
	return nullptr;
}

void FHookBlueprintEditor::OpenBlueprintHookGraphTab() {
	if (const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(GetBlueprintObj())) {
		OpenDocument(HookBlueprint->HookTargetGraph, FDocumentTracker::EOpenDocumentCause::OpenNewDocument);
	}
}

bool FHookBlueprintEditor::IsBlueprintHookGraphTabOpen() const {
	const UHookBlueprint* HookBlueprint = Cast<UHookBlueprint>(GetBlueprintObj());
	TArray<TSharedPtr<SDockTab>> GraphEditorTabs;
	DocumentManager->FindAllTabsForFactory(GraphEditorTabFactoryPtr, GraphEditorTabs);

	// Check if we have the graph open already
	for (const TSharedPtr<SDockTab>& GraphEditorTab : GraphEditorTabs) {
		const TSharedRef<SGraphEditor> Editor = StaticCastSharedRef<SGraphEditor>(GraphEditorTab->GetContent());

		if (HookBlueprint && HookBlueprint->HookTargetGraph && Editor->GetCurrentGraph() == HookBlueprint->HookTargetGraph) {
			return false;
		}
	}
	return true;
}

FHookBlueprintComponentTreeEditorSummoner::FHookBlueprintComponentTreeEditorSummoner(const TSharedPtr<FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(HookBlueprintComponentTreeEditorID, InHostingApp) {
	TabLabel = LOCTEXT("HookComponentsTabLabel", "Components");
	TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.Tabs.Components");

	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("HookComponentsView", "Overlay Component Tree");
	ViewMenuTooltip = LOCTEXT("HookComponentsView_ToolTip", "Show the components view of the mixin target class with the additional components overlaid on top of it by the mixins");
}

TSharedRef<SWidget> FHookBlueprintComponentTreeEditorSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const {
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditorPtr = StaticCastSharedPtr<FHookBlueprintEditor>(HostingApp.Pin());
	return BlueprintEditorPtr->GetComponentTreeOverlayEditor().ToSharedRef();
}

FText FHookBlueprintComponentTreeEditorSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const {
	return LOCTEXT("HookComponentsTabTooltip", "The Overlay Component Tree tab shows you the component tree of the target class that you can overlay your own components on top like how you would do in derived Blueprints.");
}

FHookBlueprintViewportSummoner::FHookBlueprintViewportSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp) : FWorkflowTabFactory(HookBlueprintViewportEditorID, InHostingApp) {
	TabLabel = LOCTEXT("HookViewportTabLabel", "Viewport");
	TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.Tabs.Components");

	bIsSingleton = true;
	ViewMenuDescription = LOCTEXT("HookViewportView", "Overlay Viewport");
	ViewMenuTooltip = LOCTEXT("HookViewportView_ToolTip", "Show the preview of the target actor with the overlay components applied on top of it.");
}

TSharedRef<SWidget> FHookBlueprintViewportSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const {
	const TSharedPtr<FHookBlueprintEditor> BlueprintEditorPtr = StaticCastSharedPtr<FHookBlueprintEditor>(HostingApp.Pin());
	return BlueprintEditorPtr->GetOverlayComponentTreeViewport().ToSharedRef();
}

FText FHookBlueprintViewportSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const {
	return LOCTEXT("HookViewportTabTooltip", "The Overlay Viewport shows the preview of the actor with Overlay Components applied to the Target Actor.");
}

FHookBlueprintEditorMode::FHookBlueprintEditorMode(const TSharedRef<FHookBlueprintEditor>& InHookBlueprintEditor, bool bAllowOverlayComponentTree) :
	FBlueprintEditorApplicationMode(InHookBlueprintEditor, FBlueprintEditorApplicationModes::StandardBlueprintEditorMode, FBlueprintEditorApplicationModes::GetLocalizedMode, false, false) {

	// Register mode toolbar
	if (UToolMenu* Toolbar = InHookBlueprintEditor->RegisterModeToolbarIfUnregistered(GetModeName())) {
		InHookBlueprintEditor->GetToolbarBuilder()->AddCompileToolbar(Toolbar);
		InHookBlueprintEditor->GetToolbarBuilder()->AddScriptingToolbar(Toolbar);
		InHookBlueprintEditor->GetToolbarBuilder()->AddBlueprintGlobalOptionsToolbar(Toolbar);
		InHookBlueprintEditor->AddBlueprintHookEditorToolbar(Toolbar);
		InHookBlueprintEditor->GetToolbarBuilder()->AddDebuggingToolbar(Toolbar);
	}

	// Register additional tab spawners
	if (bAllowOverlayComponentTree) {
		BlueprintEditorTabFactories.RegisterFactory(MakeShareable(new FHookBlueprintComponentTreeEditorSummoner(InHookBlueprintEditor)));
		BlueprintEditorTabFactories.RegisterFactory(MakeShareable(new FHookBlueprintViewportSummoner(InHookBlueprintEditor)));
	}

	const TSharedRef<FTabManager::FLayoutNode> ComponentTreeSideEditor = FTabManager::NewSplitter()
	->SetOrientation(Orient_Vertical)
    ->SetSizeCoefficient(0.15f)
    ->Split(
	   FTabManager::NewStack()
	   ->SetSizeCoefficient(0.30f)
	   ->AddTab(HookBlueprintComponentTreeEditorID, ETabState::OpenedTab)
    )->Split(
	   FTabManager::NewStack()
	   ->SetSizeCoefficient(0.70f)
	   ->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab)
	);
	const TSharedRef<FTabManager::FLayoutNode> DefaultSideEditor = FTabManager::NewStack()
	->SetSizeCoefficient(0.15f)
	->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab);

	const TSharedRef<FTabManager::FLayoutNode> ViewportMainEditor = FTabManager::NewStack()
	->SetSizeCoefficient(0.80f)
	->AddTab(HookBlueprintViewportEditorID, ETabState::OpenedTab)
	->AddTab("Document", ETabState::ClosedTab);

	const TSharedRef<FTabManager::FLayoutNode> DefaultMainEditor = FTabManager::NewStack()
	->SetSizeCoefficient(0.80f)
	->AddTab("Document", ETabState::ClosedTab);

	// Register layout
	const FString LayoutName = bAllowOverlayComponentTree ? TEXT("Blueprints_ActorMixinBlueprint_v2") : TEXT("Blueprints_UnifiedHookBlueprint_v2");
	TabLayout = FTabManager::NewLayout(*LayoutName)
	->AddArea(FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)->Split(
	FTabManager::NewSplitter()
		->SetOrientation(Orient_Horizontal)
		->Split(
			bAllowOverlayComponentTree ? ComponentTreeSideEditor : DefaultSideEditor
     	)->Split(
     		FTabManager::NewSplitter()
     		->SetOrientation(Orient_Vertical)
     		->SetSizeCoefficient(0.60f)
     		->Split(
				bAllowOverlayComponentTree ? ViewportMainEditor : DefaultMainEditor
     		)
     		->Split(
     			FTabManager::NewStack()
     			->SetSizeCoefficient(0.20f)
     			->AddTab( FBlueprintEditorTabs::CompilerResultsID, ETabState::ClosedTab )
     			->AddTab( FBlueprintEditorTabs::FindResultsID, ETabState::ClosedTab )
     			->AddTab( FBlueprintEditorTabs::BookmarksID, ETabState::ClosedTab )
     		)
     	)->Split(
     		FTabManager::NewSplitter()
     		->SetOrientation(Orient_Vertical)
     		->SetSizeCoefficient(0.25f)
     		->Split(
     			FTabManager::NewStack()
     			->SetSizeCoefficient(0.60f)
     			->AddTab(FBlueprintEditorTabs::DetailsID, ETabState::OpenedTab)
     			->AddTab(FBlueprintEditorTabs::PaletteID, ETabState::ClosedTab)
     		)
     	)
    ));
}

#undef LOCTEXT_NAMESPACE
