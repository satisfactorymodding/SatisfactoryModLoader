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
        + SVerticalBox::Slot().AutoHeight()[
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().AutoWidth()[
                SAssignNew(AlpakitAllButton, SButton)
                .Text(LOCTEXT("PackageModAlpakitAll", "Alpakit Selected!"))
                .OnClicked(this, &SAlpakitWidget::PackageAllMods)
            ]
            + SHorizontalBox::Slot().FillWidth(1.0f)
            + SHorizontalBox::Slot().AutoWidth()[
                SNew(SButton)
                .Text(LOCTEXT("CreateMod", "Create Mod"))
                .OnClicked(this, &SAlpakitWidget::CreateMod)
            ]
        ]
        +SVerticalBox::Slot().FillHeight(1).Padding(3)[
            SAssignNew(ModList, SAlpakitModEntryList)
            ]
        +SVerticalBox::Slot().AutoHeight()[
            SAssignNew(QueueText, STextBlock)
            .Text(LOCTEXT("QueuedPlaceholder", "Queued (0): "))
        ]
    ];
}

FReply SAlpakitWidget::PackageAllMods() {
    FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));

    TArray<FString> ModsToPackage;
    
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    for (auto Mod : Settings->ModSelection) {
        if (Mod.Value) {
            ModsToPackage.Add(Mod.Key);
        }
    }
    AlpakitModule.PackageMods(ModsToPackage);

    return FReply::Handled();
}

FReply SAlpakitWidget::CreateMod()
{
    FGlobalTabmanager::Get()->TryInvokeTab(FAlpakitModule::ModCreatorTabName);
    return FReply::Handled();
}

void SAlpakitWidget::QueueStarted() {
    AlpakitAllButton->SetEnabled(false);
}

void SAlpakitWidget::QueueComplete() {
    AlpakitAllButton->SetEnabled(true);
}

void SAlpakitWidget::QueueChanged(TArray<FString> NewQueue) {
    QueueText->SetText(FText::FromString(FString::Printf(TEXT("Queued (%d): %s"), NewQueue.Num(), *FString::Join(NewQueue, TEXT(", ")))));
}


#undef LOCTEXT_NAMESPACE
