#include "Hooking/HookBlueprintEditor.h"
#include "BlueprintEditorModes.h"
#include "SBlueprintEditorToolbar.h"
#include "EdGraph/EdGraph.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Patching/BlueprintHookBlueprint.h"
#include "Toolkits/ToolkitManager.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "SMLEditor"

void FHookBlueprintEditorCommands::RegisterCommands() {
	UI_COMMAND(EditHookBlueprintHookGraph, "Hook Graph", "Edit Hook Blueprint Hook Graph", EUserInterfaceActionType::Button, FInputChord());
}

FName FHookBlueprintEditor::GetToolkitFName() const {
	return TEXT("HookBlueprintEditor");
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

UToolMenu* FHookBlueprintEditor::RegisterModeToolbarIfUnregistered(const FName InModeName) {
	UToolMenu* UnregisteredToolMenu = FBlueprintEditor::RegisterModeToolbarIfUnregistered(InModeName);

	// Augment default blueprint editor mode
	if (UnregisteredToolMenu && InModeName == FBlueprintEditorApplicationModes::StandardBlueprintEditorMode) {
		FToolMenuSection& Section = UnregisteredToolMenu->FindOrAddSection(TEXT("HookBlueprintSettings"));
		Section.InsertPosition = FToolMenuInsert(TEXT("Compile"), EToolMenuInsertType::After);

		Section.AddDynamicEntry("HookBlueprintGlobalOptions", FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection) {
			const FHookBlueprintEditorCommands& Commands = FHookBlueprintEditorCommands::Get();
			const FSlateIcon SlateIconOverride(FAppStyle::GetAppStyleSetName(), TEXT("FullBlueprintEditor.EditClassDefaults"));
			InSection.AddEntry(FToolMenuEntry::InitToolBarButton(Commands.EditHookBlueprintHookGraph, TAttribute<FText>(), TAttribute<FText>(), SlateIconOverride));
		}));
	}
	return UnregisteredToolMenu;
}

void FHookBlueprintEditor::InitHookBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UHookBlueprint* Blueprint) {
	// Perform normal editor initialization
	InitBlueprintEditor(Mode, InitToolkitHost, {Blueprint}, false);

	// Open the hook target graph by default when opening the editor
	if (Blueprint->HookTargetGraph) {
		OpenBlueprintHookGraphTab();
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
			return true;
		}
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
