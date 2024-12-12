#include "AlpakitReleaseWidget.h"
#include "Alpakit.h"
#include "AlpakitModEntryList.h"
#include "AlpakitSettings.h"
#include "AlpakitStyle.h"
#include "ModTargetsConfig.h"
#include "Util/SemVersion.h"

#define LOCTEXT_NAMESPACE "AlpakitWidget"

void SAlpakitReleaseWidget::Construct(const FArguments& InArgs) {
	const float TargetColumnWidth = 90;

	FString TargetSMLVersion = TEXT("^") + FAlpakitModule::GetCurrentSMLVersion();
	// FPaths::ProjectSavedDir() points to an appdata folder when the project is loaded via "restore last opened project", so use ProjectDir instead
	FString archivePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Saved") / TEXT("ArchivedPlugins"));

	ChildSlot[
		SNew(SVerticalBox)
		+SVerticalBox::Slot().FillHeight(1).Padding(3)[
			SAssignNew(ModList, SAlpakitModEntryList)
			.BarSlot()[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SButton)
					.Text(LOCTEXT("PackageModAlpakitAllRelease", "Alpakit Selected (Release)"))
					.ToolTipText(LOCTEXT("PackageModAlpakitAllRelease_Tooltip", "For each selected mod, prepare the multi-target zip for upload to the Mod Repository.\nThe targets included in the zip are controlled by what you have marked in Release Targets.\nCan build Shipping C++ as required."))
					.OnClicked_Lambda([this] {
						PackageAllMods();
						return FReply::Handled();
					})
					.IsEnabled(this, &SAlpakitReleaseWidget::IsPackageButtonEnabled)
				]
				// Open ArchivedPlugins folder(root of all packaged mods), if it exists, otherwise the button isn't shown
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SButton)
					.Text(LOCTEXT("PackageDirRootAlpakit", "Open Archive Folder"))
					.OnClicked_Lambda([this, archivePath]
					{
						FPlatformProcess::ExploreFolder(*archivePath);
						return FReply::Handled();
					})
					.IsEnabled_Lambda([this]
					{
						return !FAlpakitModule::Get().IsPackaging();
					})
					.Visibility_Lambda([this, archivePath]
					{
						if (FPaths::DirectoryExists(archivePath))
							return EVisibility::Visible;
						return EVisibility::Hidden;
					})
					.ToolTipText(LOCTEXT("PackageDirRootAlpakit_Tooltip", "Open the ArchivedPlugins folder to view all mod release packages."))
				]
			]
			.SearchTrail() [
				SNew(SHorizontalBox)
					+SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Fill).Padding(15,0, 5, 0)[
						SNew(SSeparator)
						.Orientation(Orient_Vertical)
					]

					+SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5, 0, 15, 0)[
						SNew(SVerticalBox)
							+SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 0, 0, 5)[
								SNew(STextBlock)
								.ToolTipText(LOCTEXT("ReleaseTargets_Tooltip", "Select what target platforms this mod supports."))
								.Text(LOCTEXT("ReleaseTargets", "Release Targets"))
							]
							+SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 5, 0, 0)[
								SNew(SHorizontalBox)
									+SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5,0)[
										SNew(STextBlock)
										.Text(LOCTEXT("ReleaseWindows", "Windows"))
										.Justification(ETextJustify::Type::Center)
										.MinDesiredWidth(TargetColumnWidth)
									]

									+SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5,0)[
										SNew(STextBlock)
										.Text(LOCTEXT("ReleaseWindowsServer", "Windows Server"))
										.Justification(ETextJustify::Type::Center)
										.MinDesiredWidth(TargetColumnWidth)
									]

									+SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5,0)[
										SNew(STextBlock)
										.Text(LOCTEXT("ReleaseLinuxServer", "Linux Server"))
										.Justification(ETextJustify::Type::Center)
										.MinDesiredWidth(TargetColumnWidth)
									]
							]
					]
			]
			.ModEntryLead_Lambda([this] (const TSharedRef<IPlugin>& Mod) {
				return SNew(SButton)
						.Text(LOCTEXT("PackageModAlpakit", "Alpakit!"))
						.OnClicked_Lambda([this, Mod]{
							FAlpakitModule::Get().PackageModsRelease({Mod});
							return FReply::Handled();
						})
						.ToolTipText_Lambda([this, Mod]{
							return FText::Format(LOCTEXT("PackageModAlpakit_tooltip", "Alpakit Release just {0}\n\nPackage this mod for Release Targets, and archive in the multi-target zip for upload to the Mod Repository.\nCan build Shipping C++ as required."),
												 FText::FromString(Mod->GetName()));
						})
						.IsEnabled_Lambda([this]{
							return !FAlpakitModule::Get().IsPackaging();
						});
			})
			.ModEntryTrail_Lambda([this, TargetColumnWidth, TargetSMLVersion, archivePath] (const TSharedRef<IPlugin>& Mod) {
				TSharedRef<FModTargetsConfig> ModTargetsConfig = ModTargetsConfigs.FindOrAdd(Mod->GetName(), MakeShared<FModTargetsConfig>(Mod));
				FString modPath = archivePath / Mod->GetName() / (Mod->GetName() + TEXT(".zip"));

				return SNew(SBox)
					.Padding(5, 0, 5, 0)
					.Content()[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().Padding(5,0)[
							SNew(SBox)
							.HAlign(HAlign_Center)
							.Visibility_Lambda([this, Mod, TargetSMLVersion]
							{
								FString SMLVersion = GetModSMLDependencyVersion(Mod);
								if (SMLVersion.IsEmpty() || SMLVersion == TargetSMLVersion)
									return EVisibility::Hidden;
								return EVisibility::Visible;
							})
							.Content()[
								SNew(SButton)
								.Content()
								[
									SNew(SImage)
									.Image(FAlpakitStyle::Get().GetBrush("Alpakit.Warning"))
								]
								.ToolTipText_Lambda([Mod, TargetSMLVersion]
								{
									return FText::Format(LOCTEXT("UpdateSMLVersionTooltip", "This mod depends on SML {0}, but the project is using SML {1}. Click to update"), FText::FromString(GetModSMLDependencyVersion(Mod)), FText::FromString(TargetSMLVersion));
								})
								.OnClicked_Lambda([this, Mod, TargetSMLVersion]
								{
									SetModSMLDependencyVersion(Mod, TargetSMLVersion);
									return FReply::Handled();
								})
							]
						]
						+ SHorizontalBox::Slot().AutoWidth().Padding(5,0)[
							SNew(SBox)
							.HAlign(HAlign_Center)
							.Visibility_Lambda([this, Mod]
							{
								FVersion GameVersion;
								FVersionRange ModGameVersionRange, TargetGameVersionRange;
								GetModGameVersionFields(Mod, GameVersion, ModGameVersionRange, TargetGameVersionRange);
								if (FormatGameVersionRange(ModGameVersionRange) == FormatGameVersionRange(TargetGameVersionRange))
									return EVisibility::Hidden;
								return EVisibility::Visible;
							})
							.Content()[
								SNew(SButton)
								.Content()
								[
									SNew(SImage)
									.Image(FAlpakitStyle::Get().GetBrush("Alpakit.Warning"))
								]
								.ToolTipText_Lambda([Mod]
								{
									FString GameVersionRaw = GetModGameVersion(Mod);
									FVersion GameVersion;
									FVersionRange ModGameVersionRange, TargetGameVersionRange;
									GetModGameVersionFields(Mod, GameVersion, ModGameVersionRange, TargetGameVersionRange);
									if (GameVersionRaw.IsEmpty()) {
										GameVersionRaw = "(unspecified)";
									} else {
										GameVersionRaw = FormatGameVersionRange(ModGameVersionRange);
									}
									return FText::Format(LOCTEXT("UpdateGameVersionTooltip", "This mod uses game version {0}, but the project is {1}. Click to update"), FText::FromString(GameVersionRaw), FText::FromString(FormatGameVersionRange(TargetGameVersionRange)));
								})
								.OnClicked_Lambda([this, Mod]
								{
									FVersion GameVersion;
									FVersionRange ModGameVersionRange, TargetGameVersionRange;
									GetModGameVersionFields(Mod, GameVersion, ModGameVersionRange, TargetGameVersionRange);
									SetModGameVersion(Mod, FormatGameVersionRange(TargetGameVersionRange));
									return FReply::Handled();
								})
							]
						]
						//Box here for button to open output folder, if exists (ie packaged)
						+ SHorizontalBox::Slot().AutoWidth().Padding(5, 0)[
							SNew(SBox)
							.HAlign(HAlign_Right)
							.Visibility_Lambda([this, modPath]
								{
									if (FPaths::FileExists(modPath))
										return EVisibility::Visible;
									return EVisibility::Hidden;
								})
							.Content()[
								SNew(SButton)
								.Content()
								[
									SNew(SImage)
									.Image(FAlpakitStyle::Get().GetBrush("Alpakit.FolderOpen"))
								]
								.OnClicked_Lambda([this, modPath]
									{
										FPlatformProcess::ExploreFolder(*modPath);
										return FReply::Handled();
									})
								.IsEnabled_Lambda([this]
									{
										return !FAlpakitModule::Get().IsPackaging();
									})
								.ToolTipText(LOCTEXT("OpenDirToolTip", "Open the mod's ArchivedPlugins directory in File Explorer, which contains the multi-target zip file to upload to the Satisfactory Mod Repository."))
							]
						]
						+ SHorizontalBox::Slot().AutoWidth().Padding(5,0)[
							SNew(SBox)
							.MinDesiredWidth(TargetColumnWidth)
							.HAlign(HAlign_Center)
							.Content()[
								SNew(SCheckBox)
								.IsChecked(ModTargetsConfig->bWindows ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
								.OnCheckStateChanged_Lambda([this, ModTargetsConfig](ECheckBoxState State) {
									ModTargetsConfig->bWindows = State == ECheckBoxState::Checked;
									ModTargetsConfig->Save();
								})
							]
						]
						+ SHorizontalBox::Slot().AutoWidth().Padding(5,0)[
							SNew(SBox)
							.MinDesiredWidth(TargetColumnWidth)
							.HAlign(HAlign_Center)
							.Content()[
								SNew(SCheckBox)
								.IsChecked(ModTargetsConfig->bWindowsServer ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
								.OnCheckStateChanged_Lambda([this, ModTargetsConfig](ECheckBoxState State) {
									ModTargetsConfig->bWindowsServer = State == ECheckBoxState::Checked;
									ModTargetsConfig->Save();
								})
							]
						]
						+ SHorizontalBox::Slot().AutoWidth().Padding(5,0)[
							SNew(SBox)
							.MinDesiredWidth(TargetColumnWidth)
							.HAlign(HAlign_Center)
							.Content()[
								SNew(SCheckBox)
									.IsChecked(ModTargetsConfig->bLinuxServer ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
									.OnCheckStateChanged_Lambda([this, ModTargetsConfig](ECheckBoxState State) {
										ModTargetsConfig->bLinuxServer = State == ECheckBoxState::Checked;
										ModTargetsConfig->Save();
									})
							]
						]
				];
			})
		]
	];
}

FString SAlpakitReleaseWidget::GetModSMLDependencyVersion(TSharedRef<IPlugin> Mod)
{
	FPluginDescriptor Descriptor = Mod->GetDescriptor();
	FPluginReferenceDescriptor* SMLDependency = Descriptor.Plugins.FindByPredicate([](FPluginReferenceDescriptor& Dependency)
	{
		return Dependency.Name == TEXT("SML");
	});
	if (SMLDependency != nullptr)
	{
		FString SemVersion;
		SMLDependency->GetAdditionalStringField(TEXT("SemVersion"), SemVersion);
		return SemVersion;
	}

	return TEXT("");
}

void SAlpakitReleaseWidget::SetModSMLDependencyVersion(TSharedRef<IPlugin> Mod, FString Version)
{
	FPluginDescriptor Descriptor = Mod->GetDescriptor();
	FPluginReferenceDescriptor* SMLDependency = Descriptor.Plugins.FindByPredicate([](FPluginReferenceDescriptor& Dependency)
	{
		return Dependency.Name == TEXT("SML");
	});
	if (SMLDependency == nullptr)
		return;
	SMLDependency->AdditionalFieldsToWrite.Add(TEXT("SemVersion"), MakeShared<FJsonValueString>(Version));
	FText Error;
	Mod->UpdateDescriptor(Descriptor, Error);
}

FString SAlpakitReleaseWidget::GetModGameVersion(TSharedRef<IPlugin> Mod)
{
	FPluginDescriptor Descriptor = Mod->GetDescriptor();
	FString GameVersion;

	// FPluginDescriptor does not have GetAdditionalStringField for some reason
	TSharedPtr<FJsonValue>* GameVersionValue = Descriptor.AdditionalFieldsToWrite.Find(TEXT("GameVersion"));
	if (GameVersionValue != nullptr)
		GameVersion = (*GameVersionValue)->AsString();
	else
		Descriptor.CachedJson->TryGetStringField(TEXT("GameVersion"), GameVersion);
	return GameVersion;
}

void SAlpakitReleaseWidget::GetModGameVersionFields(TSharedRef<IPlugin> Mod, FVersion& GameVersion, FVersionRange& ModGameVersionRange, FVersionRange& TargetGameVersionRange) {
	FString ModGameVersion = GetModGameVersion(Mod);

	FString _;
	GameVersion.ParseVersion(FString::Printf(TEXT("%s.0.0"), *FAlpakitModule::GetCurrentGameVersion()), _);
	if (!ModGameVersion.IsEmpty()) {
		ModGameVersionRange.ParseVersionRange(ModGameVersion, _);

		TargetGameVersionRange.ParseVersionRange(ModGameVersion, _);
		for (FVersionComparatorCollection& ComparatorCollection : TargetGameVersionRange.Collections) {
			ComparatorCollection.Comparators.Add(FVersionComparator(EVersionComparisonOp::GREATER_EQUALS, GameVersion));
		}

		if (!TargetGameVersionRange.Matches(GameVersion)) {
			TargetGameVersionRange = FVersionRange::CreateRangeWithMinVersion(GameVersion);
		}
	} else {
		ModGameVersionRange = FVersionRange();
		TargetGameVersionRange = FVersionRange::CreateRangeWithMinVersion(GameVersion);
	}
}

FString SAlpakitReleaseWidget::FormatGameVersionRange(const FVersionRange& TargetGameVersionRange) {
	return TargetGameVersionRange.ToString().Replace(TEXT(".0.0"), TEXT(""));
}


void SAlpakitReleaseWidget::SetModGameVersion(TSharedRef<IPlugin> Mod, FString Version)
{
	FPluginDescriptor Descriptor = Mod->GetDescriptor();
	Descriptor.AdditionalFieldsToWrite.Add(TEXT("GameVersion"), MakeShared<FJsonValueString>(Version));
	FText Error;
	Mod->UpdateDescriptor(Descriptor, Error);
}

FReply SAlpakitReleaseWidget::PackageAllMods() {
	FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));

	TArray<TSharedRef<IPlugin>> ModsToPackage;

	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	for (TSharedRef<IPlugin> Mod : ModList->GetFilteredMods()) {
		if (Settings->ModSelection.FindOrAdd(Mod->GetName(), false)) {
			ModsToPackage.Add(Mod);
		}
	}

	AlpakitModule.PackageModsRelease(ModsToPackage);

	return FReply::Handled();
}

bool SAlpakitReleaseWidget::IsPackageButtonEnabled() const {
	return !FAlpakitModule::Get().IsPackaging();
}

#undef LOCTEXT_NAMESPACE
