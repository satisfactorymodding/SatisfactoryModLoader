#include "AlpakitWidget.h"
#include "Alpakit.h"
#include "AlpakitModEntryList.h"
#include "AlpakitSettings.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"

#define LOCTEXT_NAMESPACE "AlpakitWidget"

void SAlpakitWidget::Construct(const FArguments& InArgs) {
    FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));
    
    AlpakitModule.GetOnQueueStarted().AddSP(this, &SAlpakitWidget::QueueStarted);
    AlpakitModule.GetOnQueueComplete().AddSP(this, &SAlpakitWidget::QueueComplete);
    AlpakitModule.GetOnQueueChanged().AddSP(this, &SAlpakitWidget::QueueChanged);
    
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
                    .OnClicked_Lambda([this] {
                        PackageAllMods(false);
                        return FReply::Handled();
                    })
                ]
                + SHorizontalBox::Slot().AutoWidth()[
                    SAssignNew(AlpakitAllReleaseButton, SButton)
                    .Text(LOCTEXT("PackageModAlpakitAllRelease", "Alpakit Release"))
                    .OnClicked_Lambda([this] {
                        PackageAllMods(true);
                        return FReply::Handled();
                    })
                ]
                + SHorizontalBox::Slot().FillWidth(1.0f)
                + SHorizontalBox::Slot().AutoWidth()[
                    SNew(SButton)
                    .Text(LOCTEXT("CreateMod", "Create Mod"))
                    .OnClicked(this, &SAlpakitWidget::CreateMod)
                ]
            ]
        ]
        +SVerticalBox::Slot().AutoHeight()[
            SAssignNew(QueueText, STextBlock)
            .Text(LOCTEXT("QueuedPlaceholder", "Queued (0): "))
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
    AlpakitModule.PackageMods(ModsToPackage, ReleaseBuild);

    return FReply::Handled();
}

FReply SAlpakitWidget::CreateMod()
{
    FGlobalTabmanager::Get()->TryInvokeTab(FAlpakitModule::ModCreatorTabName);
    return FReply::Handled();
}

void SAlpakitWidget::QueueStarted() {
    AlpakitAllDevButton->SetEnabled(false);
    AlpakitAllReleaseButton->SetEnabled(false);
}

void SAlpakitWidget::QueueComplete() {
    AlpakitAllDevButton->SetEnabled(true);
    AlpakitAllReleaseButton->SetEnabled(true);
}

void SAlpakitWidget::QueueChanged(TArray<TSharedRef<IPlugin>> NewQueue) {
    TArray<FString> NewQueueNames;
    for (auto Plugin : NewQueue) {
        NewQueueNames.Add(Plugin->GetName());
    }
    QueueText->SetText(FText::FromString(FString::Printf(TEXT("Queued (%d): %s"), NewQueueNames.Num(), *FString::Join(NewQueueNames, TEXT(", ")))));
}


#undef LOCTEXT_NAMESPACE
