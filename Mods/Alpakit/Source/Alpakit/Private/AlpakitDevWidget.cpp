#include "AlpakitDevWidget.h"
#include "Alpakit.h"
#include "AlpakitModEntryList.h"
#include "AlpakitSettings.h"

#define LOCTEXT_NAMESPACE "AlpakitWidget"

void SAlpakitDevWidget::Construct(const FArguments& InArgs) {    
    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.bAllowSearch = true;
    DetailsViewArgs.bHideSelectionTip = true;
    DetailsViewArgs.bLockable = false;
    DetailsViewArgs.bSearchInitialKeyFocus = true;
    DetailsViewArgs.bUpdatesFromSelection = false;
    DetailsViewArgs.bShowOptions = true;
    DetailsViewArgs.bShowModifiedPropertiesOption = true;
    DetailsViewArgs.bShowObjectLabel = false;
    DetailsViewArgs.bCustomNameAreaLocation = true;
    DetailsViewArgs.bCustomFilterAreaLocation = true;
    DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
    DetailsViewArgs.bAllowMultipleTopLevelObjects = true;
    DetailsViewArgs.bShowScrollBar = false;

    FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
    DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    DetailsView->SetObject(UAlpakitSettings::Get());
    DetailsView->OnFinishedChangingProperties().AddLambda([this](const FPropertyChangedEvent&) {
        UAlpakitSettings::Get()->SaveSettings();
    });
    
    ChildSlot[
        SNew(SVerticalBox)
        +SVerticalBox::Slot().AutoHeight()[
            DetailsView.ToSharedRef()
        ]
        +SVerticalBox::Slot().FillHeight(1).Padding(3)[
            SAssignNew(ModList, SAlpakitModEntryList)
            .BarSlot()[
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth()[
                    SNew(SButton)
                    .Text(LOCTEXT("PackageModAlpakitAllDev", "Alpakit Selected (Development)"))
                    .ToolTipText(LOCTEXT("PackageModAlpakitAllDev_Tooltip", "For each selected mod, package the mod for each of the targets you have Enabled in your Dev Packaging Settings.\nAfter all tasks complete, run your after packaging tasks for each target.\nCan build Shipping C++ as required."))
                    .OnClicked_Lambda([this] {
                        PackageAllMods();
                        return FReply::Handled();
                    })
                	.IsEnabled(this, &SAlpakitDevWidget::IsPackageButtonEnabled)
                ]
                + SHorizontalBox::Slot().FillWidth(1.0f)
                + SHorizontalBox::Slot().AutoWidth()[
                    SNew(SButton)
                    .Text(LOCTEXT("CreateMod", "Create Mod"))
                    .ToolTipText(LOCTEXT("CreateMod_Tooltip", "Open the wizard to create a new mod from a template"))
                    .OnClicked(this, &SAlpakitDevWidget::CreateMod)
                ]
            ]
            .ModEntryLead_Lambda([this] (const TSharedRef<IPlugin>& Mod) {
                return SNew(SButton)
                        .Text(LOCTEXT("PackageModAlpakit", "Alpakit!"))
                        .OnClicked_Lambda([this, Mod]{
	                        FAlpakitModule::Get().PackageModsDevelopment({Mod});
                            return FReply::Handled();
                        })
                        .ToolTipText_Lambda([this, Mod]{
                            // TODO localize correctly
                            return FText::FromString(FString::Printf(TEXT("Alpakit Dev just %s\n\nPackage this mod for each of the targets you have Enabled in your Dev Packaging Settings, then run your after packaging tasks for each target.\nCan build Shipping C++ as required."), *Mod->GetName()));
                        })
                        .IsEnabled_Lambda([this]{
                            return !FAlpakitModule::Get().IsPackaging();
                        });
            })
        ]
    ];
}

FReply SAlpakitDevWidget::PackageAllMods() {
    FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));

    TArray<TSharedRef<IPlugin>> ModsToPackage;
    
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    for (TSharedRef<IPlugin> Mod : ModList->GetFilteredMods()) {
        if (Settings->ModSelection.FindOrAdd(Mod->GetName(), false)) {
            ModsToPackage.Add(Mod);
        }
    }

    AlpakitModule.PackageModsDevelopment(ModsToPackage);

    return FReply::Handled();
}

FReply SAlpakitDevWidget::CreateMod()
{
    FGlobalTabmanager::Get()->TryInvokeTab(FAlpakitModule::ModCreatorTabName);
    return FReply::Handled();
}

bool SAlpakitDevWidget::IsPackageButtonEnabled() const {
	return !FAlpakitModule::Get().IsPackaging();
}

#undef LOCTEXT_NAMESPACE
