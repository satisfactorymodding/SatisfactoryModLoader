#include "AlpakitModEntry.h"


#include "AlpakitSettings.h"
#include "AlpakitStyle.h"
#include "UATHelper/Public/IUATHelperModule.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntry::Construct(const FArguments& Args, TSharedRef<IPlugin> InMod) {
	Mod = InMod;
	ChildSlot[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot().FillWidth(1)[
			SNew(STextBlock)
			.Text_Lambda([InMod]() {
				return FText::FromString(InMod->GetName());
			})
		]
		+SHorizontalBox::Slot().AutoWidth()[
			SNew(SButton)
			.Text(LOCTEXT("PackageModAlpakit", "Alpakit!"))
			.OnClicked_Lambda([this]() {
				PackageMod();
				return FReply::Handled();
			})
		]
	];
}

void SAlpakitModEntry::PackageMod() {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();

	FString ModFileName = Mod->GetDescriptorFileName();
	FString ModFilePath = FPaths::ConvertRelativePathToFull(ModFileName);

	FString ProjectPath = FPaths::IsProjectFilePathSet() ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()) : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");
	
	FString GamePath = Settings->SatisfactoryGamePath.Path;

	FString CopyToGame = "";
	if (Settings->bCopyModsToGame) {
		CopyToGame = FString::Printf(TEXT("-CopyToGameDir -GameDir=\"%s\""), *GamePath);
	}

	FString LaunchType;
	switch (Settings->LaunchGameAfterPacking) {
	case EAlpakitStartGameType::STEAM:
		LaunchType = "Steam";
		break;
	case EAlpakitStartGameType::EPIC_EARLY_ACCESS:
		LaunchType = "EpicEA";
		break;
	case EAlpakitStartGameType::EPIC_EXPERIMENTAL:
		LaunchType = "EpicExp";
		break;
	default:
		LaunchType = "";
	}
	FString LaunchGame = "";
	if (LaunchType.Len() > 0) LaunchGame = FString::Printf(TEXT("-LaunchGame -LaunchType=%s"), *LaunchType);
	
	FString CommandLine = FString::Printf(TEXT("-ScriptsForProject=\"%s\" PackagePlugin -project=\"%s\" -pluginpath=\"%s\" %s %s %s"),
		*ProjectPath,
        *ProjectPath,
        *ModFilePath,
        FApp::IsEngineInstalled() ? TEXT("-installed") : TEXT(""),
		*CopyToGame,
        *LaunchGame
        );

#if PLATFORM_WINDOWS
	FText PlatformName = LOCTEXT("PlatformName_Windows", "Windows");
#elif PLATFORM_MAC
	FText PlatformName = LOCTEXT("PlatformName_Mac", "Mac");
#elif PLATFORM_LINUX
	FText PlatformName = LOCTEXT("PlatformName_Linux", "Linux");
#else
	FText PlatformName = LOCTEXT("PlatformName_Other", "Other OS");
#endif

	IUATHelperModule::Get().CreateUatTask(CommandLine, PlatformName, LOCTEXT("PackageModTaskName", "Packaging Mod"),
        LOCTEXT("PackageModTaskShortName", "Package Mod Task"), FAlpakitStyle::Get().GetBrush("Alpakit.OpenPluginWindow"));
}

#undef LOCTEXT_NAMESPACE