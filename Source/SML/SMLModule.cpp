#include "SMLModule.h"

#define LOCTEXT_NAMESPACE "FSMLModule"

#if WITH_EDITOR
#include "Factories/BlueprintFactory.h"
#include "ContentBrowserModule.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/Blueprint.h"
#include "FileHelper.h"
#include "LevelEditor.h"
#include "Framework/Commands/Commands.h"
#include "MultiBoxBuilder.h"
#include "BlueprintEditorUtils.h"
#include "AssetRegistryModule.h"
#include "UserDefinedStructureCompilerUtils.h"

class FSMLCommands : public TCommands<FSMLCommands> {
public:
	FSMLCommands() : TCommands<FSMLCommands>(
		TEXT("SatisfactoryModLoader"), 
		NSLOCTEXT("Contexts", "SML", "SML Plugin"), 
		NAME_None, 
		FCoreStyle::Get().GetStyleSetName()) {}

	// TCommands<> interface
	virtual void RegisterCommands() override {
		UI_COMMAND(DebugBlueprintsCommand, "SML Debugging", "Debug blueprint generation", EUserInterfaceActionType::Button, FInputChord());
	}
public:
	TSharedPtr<FUICommandInfo> DebugBlueprintsCommand;
};

void SMLDebugButtonClicked() {
	UBlueprintFactory* Factory = NewObject<UBlueprintFactory>();
	Factory->ParentClass = AActor::StaticClass();
	const FString PackageName = TEXT("/Game/FactoryGame/Recipe_IndustrialTank");
	UPackage* BlueprintPackage = CreatePackage(nullptr, *PackageName);
	EObjectFlags Flags = RF_Public | RF_Standalone;
	UBlueprint* BlueprintObject = Cast<UBlueprint>(Factory->FactoryCreateNew(UBlueprint::StaticClass(), BlueprintPackage, FName(TEXT("Recipe_IndustrialTank")), Flags, nullptr, GWarn));
	if (BlueprintObject) {
		FAssetRegistryModule::AssetCreated(BlueprintObject);
		BlueprintPackage->MarkPackageDirty();

		
		//FStructureEditorUtils for UUserDefinedStruct
		//BlueprintCompilationManager.h for requesting blueprint compilation
		//FAssetEditorManager::Get().OpenEditorForAsset(BlueprintObject);
		//Save can be forced via calling FileHelpers.h SavePackagesAndPromptUser
	}
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
