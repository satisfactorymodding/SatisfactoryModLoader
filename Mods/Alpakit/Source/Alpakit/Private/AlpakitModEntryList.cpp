#include "AlpakitModEntryList.h"
#include "Alpakit.h"
#include "AlpakitEditModDialog.h"
#include "AlpakitModEntry.h"
#include "AlpakitSettings.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

/**
 * Main entry point for constructing the mod list widget.
 * Sets up the overall layout with a top bar containing filters and a scrollable mod list below.
 */
void SAlpakitModEntryList::Construct(const FArguments& Args) {
	ChildSlot[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 5)[
			CreateTopBar(Args)
		]
		+ SVerticalBox::Slot().FillHeight(1.0f)[
			CreateModList(Args)
		]
	];

	UpdateSortOptions();
	LoadMods();
	UpdateAllCheckbox();
	IPluginManager::Get().OnNewPluginCreated().AddSP(this, &SAlpakitModEntryList::OnNewPluginCreated);
}

/**
 * Creates the top bar containing the main controls and search functionality.
 * The top bar is split into two rows:
 * - Top row: Sort By and Filter checkboxes
 * - Bottom row: Select all checkbox and search box
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateTopBar(const FArguments& Args) {
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)[
				Args._BarSlot.Widget
			]
			+ SVerticalBox::Slot()[
				CreateSearchAndFilters()
			]
		]
		+ SHorizontalBox::Slot().AutoWidth()[
			Args._SearchTrail.Widget
		];
}

/**
 * Creates the search and filter controls arranged in two rows:
 * - Top row: Search By and Engine/Project plugin filters
 * - Bottom row: Select all checkbox and search box
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateSearchAndFilters() {
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 0, 0, 5)[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth()[
				CreateSortByComboBox()
			]
			+ SHorizontalBox::Slot().AutoWidth()[
				SNew(SSpacer)
				.Size(FVector2D(10.0f, 10.0f))
			]
			+ SHorizontalBox::Slot().AutoWidth()[
				CreateEnginePluginsCheckbox()
			]
			+ SHorizontalBox::Slot().AutoWidth()[
				SNew(SSpacer)
				.Size(FVector2D(10.0f, 10.0f))
			]
			+ SHorizontalBox::Slot().AutoWidth()[
				CreateProjectPluginsCheckbox()
			]
		]
		+ SVerticalBox::Slot().AutoHeight()[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0)[
				SAssignNew(AllModsCheckbox, SCheckBox)
				.ToolTipText(LOCTEXT("AllModsCheckboxAlpakit_Tooltip", "Select/deselect all displayed mods. Search can be used to narrow down which are affected"))
				.OnCheckStateChanged_Lambda([this](ECheckBoxState InState) {
					SetAllMods(InState == ECheckBoxState::Checked);
				})
			]
			+ SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[
				SNew(SEditableTextBox)
				.ToolTipText(LOCTEXT("SearchHint_Tooltip", "Filter the list based on the text entered here. Friendly name and Mod Reference supported"))
				.HintText(LOCTEXT("SearchHint", "Search Mod..."))
				.OnTextChanged_Lambda([this](const FText& InText) {
					this->Filter(InText.ToString());
				})
			]
		];
}

/**
 * Creates the checkbox for toggling visibility of engine plugins.
 * Engine plugins are typically not mods, so this is usually disabled.
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateEnginePluginsCheckbox() {
	return SNew(SCheckBox)
		.Content()[
			SNew(STextBlock)
			.ToolTipText(LOCTEXT("ShowEnginePlugins_Tooltip", "Display all Unreal Engine plugins loaded at the engine level (notably not mods, you usually don't need this enabled)"))
			.Text(LOCTEXT("ShowEnginePlugins", "Show Engine Plugins"))
		]
		.OnCheckStateChanged_Lambda([this](ECheckBoxState InState) {
			this->SetShowEngine(InState == ECheckBoxState::Checked);
		});
}

/**
 * Creates the checkbox for toggling visibility of project plugins.
 * Project plugins are typically not mods, so this is usually disabled.
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateProjectPluginsCheckbox() {
	return SNew(SCheckBox)
		.Content()[
			SNew(STextBlock)
			.ToolTipText(LOCTEXT("ShowProjectPlugins_Tooltip", "Display all Unreal Engine plugins loaded at the project level (such as Plugins folder mods, you usually don't need this enabled)"))
			.Text(LOCTEXT("ShowProjectPlugins", "Show Project Plugins"))
		]
		.OnCheckStateChanged_Lambda([this](ECheckBoxState InState) {
			this->SetShowProject(InState == ECheckBoxState::Checked);
		});
}

/**
 * Creates the sort options dropdown that allows sorting by either Mod Reference or Friendly Name.
 * The current selection is persisted in the settings.
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateSortByComboBox() {
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth()[
			SNew(STextBlock)
			.Text(LOCTEXT("SortByLabel", "Sort By:"))
			.Margin(FMargin(0, 2, 5, 0))
		]
		+ SHorizontalBox::Slot().AutoWidth()[
			SNew(SComboBox<TSharedPtr<FText>>)
			.OptionsSource(&SortOptions)
			.OnSelectionChanged_Lambda([this](TSharedPtr<FText> NewSelection, ESelectInfo::Type) {
				CurrentSortOption = NewSelection;
				this->SetOrderByFriendlyName(NewSelection->ToString() == TEXT("Friendly Name"));
			})
			.OnGenerateWidget_Lambda([](TSharedPtr<FText> InOption) {
				return SNew(STextBlock).Text(*InOption);
			})
			[
				SNew(STextBlock)
				.Text_Lambda([this]() {
					return *CurrentSortOption;
				})
			]
		];
}

/**
 * Creates the scrollable list of mods.
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateModList(const FArguments& Args) {
	return SNew(SScrollBox)
		.Orientation(Orient_Vertical)
		.ScrollBarAlwaysVisible(true)
		+ SScrollBox::Slot()[
			SAssignNew(ModList, SListView<TSharedRef<IPlugin>>)
			.SelectionMode(ESelectionMode::None)
			.ListItemsSource(&FilteredMods)
			.OnGenerateRow_Lambda([this, Args](TSharedRef<IPlugin> Mod, const TSharedRef<STableViewBase>& List) {
				return CreateModListRow(Mod, List, Args);
			})
		];
}

/**
 * Creates a single row in the mod list.
 */
TSharedRef<ITableRow> SAlpakitModEntryList::CreateModListRow(TSharedRef<IPlugin> Mod, const TSharedRef<STableViewBase>& List, const FArguments& Args) {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	return SNew(STableRow<TSharedRef<IPlugin>>, List)
		.Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.AlternatingRow"))
		[
			SNew(SAlpakitModEntry, Mod, SharedThis(this))
			.Lead()[
				CreateModEntryLead(Mod, Args)
			]
			.Trail()[
				Args._ModEntryTrail.IsBound() ? Args._ModEntryTrail.Execute(Mod) : SNullWidget::NullWidget
			]
		];
}

/**
 * Creates the lead section of a mod entry row.
 * Contains a checkbox for selection, Alpakit button, and an edit button.
 */
TSharedRef<SWidget> SAlpakitModEntryList::CreateModEntryLead(TSharedRef<IPlugin> Mod, const FArguments& Args) {
	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0)[
			SNew(SCheckBox)
			.ToolTipText(LOCTEXT("AlpakitModEntryEnabled_Tooltip", "If enabled, this mod will be packaged when the 'Alpakit Dev' or 'Alpakit Release' buttons are pressed"))
			.OnCheckStateChanged_Lambda([this, Mod](ECheckBoxState CheckBoxState) {
				OnCheckboxChanged(Mod, CheckBoxState);
			})
			.IsChecked_Lambda([Settings, Mod] { 
				return Settings->ModSelection.FindOrAdd(Mod->GetName(), false) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; 
			})
		]
		+ SHorizontalBox::Slot().AutoWidth()[
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
			.ToolTipText_Lambda([Mod] {
				return FText::Format(LOCTEXT("EditModAlpakit_tooltip", "Edit {0} via the wizard"), FText::FromString(Mod->GetName()));
			})
		];
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

	Mods.Sort([this](const TSharedRef<IPlugin> Plugin1, const TSharedRef<IPlugin> Plugin2) {
		if (bOrderByFriendlyName)
			return Plugin1->GetFriendlyName() < Plugin2->GetFriendlyName();
		else
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

void SAlpakitModEntryList::SetOrderByFriendlyName(bool bInOrderByFriendlyName)
{
	bOrderByFriendlyName = bInOrderByFriendlyName;
	LoadMods();

	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	Settings->OrderByFriendlyName = bInOrderByFriendlyName;
	Settings->SaveSettings();
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

void SAlpakitModEntryList::UpdateSortOptions()
{
	SortOptions.Add(MakeShared<FText>(LOCTEXT("ModReference", "Mod Reference")));
	SortOptions.Add(MakeShared<FText>(LOCTEXT("FriendlyName", "Friendly Name")));
	CurrentSortOption = SortOptions[0]; // Default selection

	UAlpakitSettings* Settings = UAlpakitSettings::Get();
	bOrderByFriendlyName = Settings->OrderByFriendlyName;

	if (bOrderByFriendlyName)
		CurrentSortOption = SortOptions[1];
}

#undef LOCTEXT_NAMESPACE
