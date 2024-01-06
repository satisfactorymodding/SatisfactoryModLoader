#include "AlpakitModEntryList.h"
#include "Alpakit.h"
#include "AlpakitModEntry.h"
#include "AlpakitSettings.h"
#include "Interfaces/IPluginManager.h"
#include "Slate.h"

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
                    +SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[
                        SNew(SEditableTextBox)
                        .ToolTipText(LOCTEXT("SearchHint_Tooltip", "Filter the list based on the text entered here. Friendly name and Mod Reference supported"))
                        .HintText(LOCTEXT("SearchHint", "Search Plugin..."))
                        .OnTextChanged_Lambda([this](const FText& InText) {
                            this->Filter(InText.ToString());
                        })
                    ]
                    +SHorizontalBox::Slot().AutoWidth()[
                        SNew(SSpacer)
                        .Size(FVector2D(20.0f, 10.0f))
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
            
            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Fill).Padding(5,0)[
                SNew(SSeparator)
                .Orientation(Orient_Vertical)
            ]

            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5, 0, 15, 0)[
                SNew(SVerticalBox)
                    +SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 0, 0, 5)[
                        SNew(STextBlock)
                        .ToolTipText(LOCTEXT("ReleaseTargets_Tooltip", "Select what target platforms this mod supports, which controls what will be built by the 'Alpakit Release' button. The 'Alpakit Dev' and Alpakit! for one mod buttons ignore this and use the Dev Packaging Settings instead."))
                        .Text(LOCTEXT("ReleaseTargets", "Release Targets"))
                    ]
                    +SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0, 5, 0, 0)[
                        SNew(SHorizontalBox)
                            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5,0)[
                                SNew(STextBlock)
                                .Text(LOCTEXT("ReleaseWindows", "Windows"))
                            ]
                
                            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5,0)[
                                SNew(STextBlock)
                                .Text(LOCTEXT("ReleaseWindowsServer", "Windows Server"))
                            ]
                
                            +SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(5,0)[
                                SNew(STextBlock)
                                .Text(LOCTEXT("ReleaseLinuxServer", "Linux Server"))
                            ]
                    ]
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
                    [this](TSharedRef<IPlugin> Mod, const TSharedRef<STableViewBase>& List) {
                        return SNew(STableRow<TSharedRef<IPlugin>>, List)[
                            SNew(SAlpakitModEntry, Mod, SharedThis(this))
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

void SAlpakitModEntryList::LoadMods() {
    Mods.Empty();
    const TArray<TSharedRef<IPlugin>> EnabledPlugins = IPluginManager::Get().GetEnabledPlugins();
    for (TSharedRef<IPlugin> Plugin : EnabledPlugins) {
        //Skip SMLEditor, editor-only plugin
        if (Plugin->GetName() == TEXT("SMLEditor")) {
            continue;
        }
        //Only include project plugins for now
        //TODO make sure UAT task supports engine plugins
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
        ModEntry->SetSelected(Checked);

        Settings->ModSelection.Add(Mod->GetName(), Checked);
    }

    Settings->SaveSettings();
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
