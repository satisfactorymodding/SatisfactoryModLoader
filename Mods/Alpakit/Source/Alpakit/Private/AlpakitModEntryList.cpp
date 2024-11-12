#include "AlpakitModEntryList.h"
#include "Alpakit.h"
#include "AlpakitEditModDialog.h"
#include "AlpakitModEntry.h"
#include "AlpakitSettings.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntryList::Construct(const FArguments& Args) {

	ChildSlot[
	SNew(SVerticalBox)
		+SVerticalBox::Slot().AutoHeight().Padding(0, 5)[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[
				SNew(SVerticalBox)
				+SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)[
					Args._BarSlot.Widget
				]
				+SVerticalBox::Slot()[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0)[
						SAssignNew(AllModsCheckbox, SCheckBox)
						.ToolTipText(LOCTEXT("AllModsCheckboxAlpakit_Tooltip", "Select/deselect all displayed mods. Search can be used to narrow down which are affected"))
						.OnCheckStateChanged_Lambda([this](ECheckBoxState InState) {
							SetAllMods(InState == ECheckBoxState::Checked);
						})
					]
					+SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center).Padding(0, 0, 10, 0)[
						SNew(SEditableTextBox)
						.ToolTipText(LOCTEXT("SearchHint_Tooltip", "Filter the list based on the text entered here. Friendly name and Mod Reference supported"))
						.HintText(LOCTEXT("SearchHint", "Search Mod..."))
						.OnTextChanged_Lambda([this](const FText& InText) {
							this->Filter(InText.ToString());
						})
					]
					+SHorizontalBox::Slot().AutoWidth()[
						SNew(SCheckBox)
						.Content()[
							SNew(STextBlock)
							.ToolTipText(LOCTEXT("ShowEnginePlugins_Tooltip", "Display all Unreal Engine plugins loaded at the engine level (notably not mods, you usually don't need this enabled)"))
							.Text(LOCTEXT("ShowEnginePlugins", "Show Engine Plugins"))
						]
						.OnCheckStateChanged_Lambda([this](ECheckBoxState InState) {
							this->SetShowEngine(InState == ECheckBoxState::Checked);
						})
					]
					+SHorizontalBox::Slot().AutoWidth()[
						SNew(SSpacer)
						.Size(FVector2D(10.0f, 10.0f))
					]
					+SHorizontalBox::Slot().AutoWidth()[
						SNew(SCheckBox)
						.Content()[
							SNew(STextBlock)
							.ToolTipText(LOCTEXT("ShowProjectPlugins_Tooltip", "Display all Unreal Engine plugins loaded at the project level (such as Plugins folder mods, you usually don't need this enabled)"))
							.Text(LOCTEXT("ShowProjectPlugins", "Show Project Plugins"))
						]
						.OnCheckStateChanged_Lambda([this](ECheckBoxState InState) {
							this->SetShowProject(InState == ECheckBoxState::Checked);
						})
					]
				]
			]
			+SHorizontalBox::Slot().AutoWidth()
			[
				Args._SearchTrail.Widget
			]
		]
		+ SVerticalBox::Slot().FillHeight(1.0f)[
			SNew(SScrollBox)
			.Orientation(Orient_Vertical)
			.ScrollBarAlwaysVisible(true)
			+ SScrollBox::Slot()[
				SAssignNew(ModList, SListView<TSharedRef<IPlugin>>)
				.SelectionMode(ESelectionMode::None)
				.ListItemsSource(&FilteredMods)
				.OnGenerateRow_Lambda(
					[this, Args](TSharedRef<IPlugin> Mod, const TSharedRef<STableViewBase>& List) {
						UAlpakitSettings* Settings = UAlpakitSettings::Get();
						return SNew(STableRow<TSharedRef<IPlugin>>, List)
							.Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.AlternatingRow"))
							[
								SNew(SAlpakitModEntry, Mod, SharedThis(this))
								.Lead()[
									SNew(SHorizontalBox)
									+SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0)
									[
										SNew(SCheckBox)
											.ToolTipText(LOCTEXT("AlpakitModEntryEnabled_Tooltip", "If enabled, this mod will be packaged when the 'Alpakit Dev' or 'Alpakit Release' buttons are pressed"))
											.OnCheckStateChanged_Lambda([this, Mod](ECheckBoxState CheckBoxState){
												OnCheckboxChanged(Mod, CheckBoxState);
											})
											.IsChecked_Lambda([Settings, Mod] { return Settings->ModSelection.FindOrAdd(Mod->GetName(), false) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
									]
									+SHorizontalBox::Slot().AutoWidth()
									[
										Args._ModEntryLead.IsBound() ? Args._ModEntryLead.Execute(Mod) : SNullWidget::NullWidget
									]
									+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
										SNew(SButton)
										.Text(LOCTEXT("EditModAlpakit", "Edit"))
										.OnClicked_Lambda([this, Mod] {
											const TSharedRef<SAlpakitEditModDialog> EditModDialog = SNew(SAlpakitEditModDialog, Mod);
											FSlateApplication::Get().AddModalWindow(EditModDialog, SharedThis(this));
											return FReply::Handled();
										})
										.ToolTipText_Lambda([Mod]{
											return FText::Format(LOCTEXT("EditModAlpakit_tooltip", "Edit {0} via the wizard"), FText::FromString(Mod->GetName()));
										})
									]
								]
								.Trail()
								[
									Args._ModEntryTrail.IsBound() ? Args._ModEntryTrail.Execute(Mod) : SNullWidget::NullWidget
								]
						];
					})
			]
		]
	];

	LoadMods();
	UpdateAllCheckbox();
	IPluginManager::Get().OnNewPluginCreated().AddSP(this, &SAlpakitModEntryList::OnNewPluginCreated);
}

bool DoesPluginHaveRuntime(const IPlugin& Plugin) {
	//Content plugins always have runtime component
	if (Plugin.GetDescriptor().bCanContainContent) {
		return true;
	}
	//C++ plugins have runtime component as long as one of their modules does
	for (const FModuleDescriptor& Module : Plugin.GetDescriptor().Modules) {
		if (Module.Type == EHostType::Runtime ||
			Module.Type == EHostType::RuntimeNoCommandlet ||
			Module.Type == EHostType::RuntimeAndProgram ||
			Module.Type == EHostType::ClientOnly ||
			Module.Type == EHostType::ClientOnlyNoCommandlet ||
			Module.Type == EHostType::ServerOnly ||
			Module.Type == EHostType::CookedOnly) {
			return true;
		}
	}
	return false;
}

static bool IsPluginEditorOnly(const IPlugin& Plugin) {
    if (TSharedPtr<FJsonObject> Json = Plugin.GetDescriptor().CachedJson) {
        bool Result = false;
        return Json->TryGetBoolField("EditorOnly", Result) && Result;
    }
    return false;
}

void SAlpakitModEntryList::LoadMods() {
	Mods.Empty();
	const TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();
	for (TSharedRef<IPlugin> Plugin : EnabledPlugins) {
		if (IsPluginEditorOnly(Plugin.Get())) {
			continue;
		}

		if ((bShowEngine && Plugin->GetType() == EPluginType::Engine) ||
			(bShowProject && Plugin->GetType() == EPluginType::Project) ||
			Plugin->GetType() == EPluginType::Mod) {

			const bool bHasRuntime = DoesPluginHaveRuntime(Plugin.Get());
			if (bHasRuntime) {
				Mods.Add(Plugin);
			}
		}
	}
	Mods.Sort([](const TSharedRef<IPlugin> Plugin1, const TSharedRef<IPlugin> Plugin2) {
		return Plugin1->GetName() < Plugin2->GetName();
	});
	Filter(LastFilter);
}

bool PluginMatchesSearchTokens(const IPlugin& Plugin, const TArray<FString>& Tokens) {
	const FString PluginName = Plugin.GetName();
	const FString FriendlyName = Plugin.GetDescriptor().FriendlyName;
	const FString Description = Plugin.GetDescriptor().Description;

	for (const FString& Token : Tokens) {
		if (PluginName.Contains(Token) ||
			FriendlyName.Contains(Token) ||
			Description.Contains(Token)) {
			return true;
		}
	}
	return false;
}

void SAlpakitModEntryList::Filter(const FString& InFilter) {
	LastFilter = InFilter;
	FilteredMods.Empty();

	if (InFilter.IsEmpty()) {
		FilteredMods = Mods;
	} else {
		// tokenize filter keywords
		TArray<FString> FilterTokens;
		InFilter.ParseIntoArray(FilterTokens, TEXT(" "), true);

		// check each mod for it to contain the tokens
		for (TSharedRef<IPlugin> Mod : Mods) {
			// check each token in mod name
			if (PluginMatchesSearchTokens(Mod.Get(), FilterTokens)) {
				FilteredMods.Add(Mod);
			}
		}
	}

	ModList->RequestListRefresh();
	UpdateAllCheckbox();
}

FString SAlpakitModEntryList::GetLastFilter() const {
	return LastFilter;
}

void SAlpakitModEntryList::SetShowEngine(bool bInShowEngine) {
	bShowEngine = bInShowEngine;
	LoadMods();
}

void SAlpakitModEntryList::SetShowProject(bool bInShowProject) {
	bShowProject = bInShowProject;
	LoadMods();
}

void SAlpakitModEntryList::OnNewPluginCreated(IPlugin& Plugin)
{
	LoadMods();
}

void SAlpakitModEntryList::SetAllMods(bool Checked) {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	for (TSharedRef<IPlugin> Mod : FilteredMods) {
		TSharedPtr<ITableRow> TableRow = ModList->WidgetFromItem(Mod);
		if (!TableRow.IsValid()) {
			UE_LOG(LogAlpakit, Display, TEXT("TableRow not found!"));
			continue;
		}

		TSharedPtr<SAlpakitModEntry> ModEntry = StaticCastSharedPtr<SAlpakitModEntry>(TableRow->GetContent());
		if (!ModEntry.IsValid()) {
			UE_LOG(LogAlpakit, Display, TEXT("TableRow content is not valid!"));
			continue;
		}

		Settings->ModSelection.Add(Mod->GetName(), Checked);
	}

	Settings->SaveSettings();
}

void SAlpakitModEntryList::OnCheckboxChanged(TSharedRef<IPlugin> Mod, ECheckBoxState NewState) {
	// Save new checked state for the mod at the
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	const FString PluginName = Mod->GetName();

	Settings->ModSelection.Add(PluginName, NewState == ECheckBoxState::Checked);

	Settings->SaveSettings();

	UpdateAllCheckbox();
}

void SAlpakitModEntryList::UpdateAllCheckbox() {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();

	bool allFalse = true;
	bool allTrue = true;

	for (TSharedRef<IPlugin> Mod : FilteredMods) {
		if (Settings->ModSelection.FindOrAdd(Mod->GetName(), false))
			allFalse = false;
		else
			allTrue = false;
	}
	if (!allTrue && !allFalse)
		AllModsCheckbox->SetIsChecked(ECheckBoxState::Undetermined);
	else if (allTrue)
		AllModsCheckbox->SetIsChecked(ECheckBoxState::Checked);
	else if (allFalse)
		AllModsCheckbox->SetIsChecked(ECheckBoxState::Unchecked);
}

#undef LOCTEXT_NAMESPACE
