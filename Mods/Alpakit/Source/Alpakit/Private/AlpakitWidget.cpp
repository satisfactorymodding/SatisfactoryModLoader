#include "AlpakitWidget.h"
#include "Alpakit.h"
#include "AlpakitModEntryList.h"
#include "AlpakitSettings.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"

#define LOCTEXT_NAMESPACE "AlpakitWidget"

void SAlpakitWidget::Construct(const FArguments& InArgs) {    
    FDetailsViewArgs DetailsViewArgs;
    DetailsViewArgs.bAllowSearch = true;
    DetailsViewArgs.bHideSelectionTip = true;
    DetailsViewArgs.bLockable = false;
    DetailsViewArgs.bSearchInitialKeyFocus = true;
    DetailsViewArgs.bUpdatesFromSelection = false;
    DetailsViewArgs.bShowOptions = true;
    DetailsViewArgs.bShowModifiedPropertiesOption = true;
    DetailsViewArgs.bShowActorLabel = false;
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
                    SAssignNew(AlpakitAllDevButton, SButton)
                    .Text(LOCTEXT("PackageModAlpakitAllDev", "Alpakit Dev"))
                    .ToolTipText(LOCTEXT("PackageModAlpakitAllDev_Tooltip", "For each selected mod, package the mod for each of the targets you have Enabled in your Dev Packaging Settings (NOT Release Targets!).\nAfter all tasks complete, run your after packaging tasks for each target.\nCan build Shipping C++ as required."))
                    .OnClicked_Lambda([this] {
                        PackageAllMods(false);
                        return FReply::Handled();
                    })
                	.IsEnabled(this, &SAlpakitWidget::IsPackageButtonEnabled)
                ]
                + SHorizontalBox::Slot().AutoWidth()[
                    SAssignNew(AlpakitAllReleaseButton, SButton)
                    .Text(LOCTEXT("PackageModAlpakitAllRelease", "Alpakit Release"))
                    .ToolTipText(LOCTEXT("PackageModAlpakitAllRelease_Tooltip", "For each selected mod, prepare the multi-target zip for upload to the Mod Repository. The targets included in the zip are controlled by what you have marked in Release Targets.\nDoes not execute the after packing tasks (those are only for dev).\nCan build Shipping C++ as required."))
                    .OnClicked_Lambda([this] {
                        PackageAllMods(true);
                        return FReply::Handled();
                    })
                	.IsEnabled(this, &SAlpakitWidget::IsPackageButtonEnabled)
                ]
                + SHorizontalBox::Slot().FillWidth(1.0f)
                + SHorizontalBox::Slot().AutoWidth()[
                    SNew(SButton)
                    .Text(LOCTEXT("CreateMod", "Create Mod"))
                    .ToolTipText(LOCTEXT("CreateMod_Tooltip", "Open the wizard to create a new mod from a template"))
                    .OnClicked(this, &SAlpakitWidget::CreateMod)
                ]
            ]
        ]
    ];
}

FReply SAlpakitWidget::PackageAllMods(bool ReleaseBuild) {
    FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));

    TArray<TSharedRef<IPlugin>> ModsToPackage;
    
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    for (TSharedRef<IPlugin> Mod : ModList->GetFilteredMods()) {
        if (Settings->ModSelection.FindOrAdd(Mod->GetName(), false)) {
            ModsToPackage.Add(Mod);
        }
    }

    if (ReleaseBuild) {
        AlpakitModule.PackageModsRelease(ModsToPackage);
    } else {
        AlpakitModule.PackageModsDevelopment(ModsToPackage);
    }

    return FReply::Handled();
}

FReply SAlpakitWidget::CreateMod()
{
    FGlobalTabmanager::Get()->TryInvokeTab(FAlpakitModule::ModCreatorTabName);
    return FReply::Handled();
}

bool SAlpakitWidget::IsPackageButtonEnabled() const {
	return !FAlpakitModule::Get().IsPackaging();
}

#undef LOCTEXT_NAMESPACE
