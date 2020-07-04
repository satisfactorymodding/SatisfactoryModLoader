#include "SMLModule.h"

#define LOCTEXT_NAMESPACE "FSMLModule"

#if WITH_EDITOR
#include "ContentBrowserModule.h"
#include "LevelEditor.h"
#include "Framework/Commands/Commands.h"
#include "MultiBoxBuilder.h"
#include "AssetRegistryModule.h"
#include "mod/toolkit/FGAssetGenerator.h"

class FSMLCommands : public TCommands<FSMLCommands> {
public:
	FSMLCommands() : TCommands<FSMLCommands>(
		TEXT("SatisfactoryModLoader"), 
		NSLOCTEXT("Contexts", "SML", "SML Plugin"), 
		NAME_None, 
		FCoreStyle::Get().GetStyleSetName()) {}

	
	virtual void RegisterCommands() override {
		UI_COMMAND(DebugBlueprintsCommand, "Generate FG Assets", "Generate FactoryGame assets from dump file", EUserInterfaceActionType::Button, FInputChord());
	}
public:
	TSharedPtr<FUICommandInfo> DebugBlueprintsCommand;
};

void SMLDebugButtonClicked() {
	FString path = FPaths::GetPath(FPaths::GetProjectFilePath()) / "BPdump" / "";
	SML::generateSatisfactoryAssets(path);
}

#endif

void FSMLModule::StartupModule() {
#if WITH_EDITOR
	TSharedRef<FUICommandList> PluginCommands = MakeShareable(new FUICommandList);
	FSMLCommands::Register();
	PluginCommands->MapAction(
		FSMLCommands::Get().DebugBlueprintsCommand,
		FExecuteAction::CreateStatic(&SMLDebugButtonClicked),
		FCanExecuteAction());
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("FileProject", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& Builder) {
		Builder.AddMenuEntry(FSMLCommands::Get().DebugBlueprintsCommand);
	}));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
#endif
}

void FSMLModule::ShutdownModule() {
#if WITH_EDITOR
	FSMLCommands::Unregister();
#endif
}


IMPLEMENT_GAME_MODULE(FSMLModule, SML);
