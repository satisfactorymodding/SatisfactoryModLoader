#include "AlpakitModEntry.h"


#include "AlpakitSettings.h"
#include "AlpakitStyle.h"
#include "UATHelper/Public/IUATHelperModule.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntry::Construct(const FArguments& Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner) {
	Mod = InMod;
	ChildSlot[
		SNew(SHorizontalBox)
		+SHorizontalBox::Slot().FillWidth(1)[
			SNew(STextBlock)
			.Text_Lambda([InMod]() {
				const FString DisplayText = FString::Printf(TEXT("%s (%s)"), *InMod->GetDescriptor().FriendlyName, *InMod->GetName());
				return FText::FromString(DisplayText);
			})
			.HighlightText_Lambda([InOwner]() {
				return FText::FromString(InOwner->GetLastFilter());
			})
		]
		+SHorizontalBox::Slot().AutoWidth()[
			SNew(SButton)
			.Text(LOCTEXT("PackageModAlpakit", "Alpakit!"))
			.OnClicked_Lambda([this]() {
				PackageMod();
				return FReply::Handled();
			})
			.ToolTipText_Lambda([this]() {
				return FText::FromString(FString::Printf(TEXT("Alpakit %s"), *this->Mod->GetName()));
			})
		]
	];
}

FString GetArgumentForLaunchType(EAlpakitStartGameType LaunchMode) {
	switch (LaunchMode) {
	case EAlpakitStartGameType::STEAM:
		return TEXT("-Steam");
	case EAlpakitStartGameType::EPIC_EARLY_ACCESS:
		return TEXT("-EpicEA");
	case EAlpakitStartGameType::EPIC_EXPERIMENTAL:
		return TEXT("-EpicExp");
	default:
		return TEXT("");
	}
}

FText GetCurrentPlatformName() {
#if PLATFORM_WINDOWS
	return LOCTEXT("PlatformName_Windows", "Windows");
#elif PLATFORM_MAC
	return LOCTEXT("PlatformName_Mac", "Mac");
#elif PLATFORM_LINUX
	return LOCTEXT("PlatformName_Linux", "Linux");
#else
	return LOCTEXT("PlatformName_Other", "Other OS");
#endif
}

void SAlpakitModEntry::PackageMod() const {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	const FString PluginName = Mod->GetName();
	const FString GamePath = Settings->SatisfactoryGamePath.Path;

	const FString ProjectPath = FPaths::IsProjectFilePathSet() ?
		FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath()) :
		FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");

	FString AdditionalUATArguments;
	if (Settings->bCopyModsToGame) {
		AdditionalUATArguments.Append(TEXT("-CopyToGameDir "));
	}
	if (Settings->LaunchGameAfterPacking != EAlpakitStartGameType::NONE) {
		AdditionalUATArguments.Append(TEXT("-LaunchGame "));
		AdditionalUATArguments.Append(GetArgumentForLaunchType(Settings->LaunchGameAfterPacking)).Append(TEXT(" "));
	}
	
	const FString LaunchGameArgument = GetArgumentForLaunchType(Settings->LaunchGameAfterPacking);

	const FString CommandLine = FString::Printf(TEXT("-ScriptsForProject=\"%s\" PackagePlugin -Project=\"%s\" -PluginName=\"%s\" -GameDir=\"%s\" %s"),
	                                            *ProjectPath, *ProjectPath, *PluginName, *Settings->SatisfactoryGamePath.Path, *AdditionalUATArguments);

	const FText PlatformName = GetCurrentPlatformName();
	IUATHelperModule::Get().CreateUatTask(CommandLine, PlatformName,
			LOCTEXT("PackageModTaskName", "Packaging Mod"),
        LOCTEXT("PackageModTaskShortName", "Package Mod Task"),
        FAlpakitStyle::Get().GetBrush("Alpakit.OpenPluginWindow"));
}

#undef LOCTEXT_NAMESPACE