#include "AlpakitReleaseWidget.h"
#include "Alpakit.h"
#include "AlpakitModEntryList.h"
#include "AlpakitSettings.h"
#include "ModTargetsConfig.h"

#define LOCTEXT_NAMESPACE "AlpakitWidget"

void SAlpakitReleaseWidget::Construct(const FArguments& InArgs) {
    const float TargetColumnWidth = 90;
    
    ChildSlot[
        SNew(SVerticalBox)
        +SVerticalBox::Slot().FillHeight(1).Padding(3)[
            SAssignNew(ModList, SAlpakitModEntryList)
            .BarSlot()[
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth()[
                    SNew(SButton)
                    .Text(LOCTEXT("PackageModAlpakitAllRelease", "Alpakit Selected (Release)"))
                    .ToolTipText(LOCTEXT("PackageModAlpakitAllRelease_Tooltip", "For each selected mod, prepare the multi-target zip for upload to the Mod Repository. The targets included in the zip are controlled by what you have marked in Release Targets.\nCan build Shipping C++ as required."))
                    .OnClicked_Lambda([this] {
                        PackageAllMods();
                        return FReply::Handled();
                    })
                    .IsEnabled(this, &SAlpakitReleaseWidget::IsPackageButtonEnabled)
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
                            // TODO localize correctly
                            return FText::FromString(FString::Printf(TEXT("Alpakit Release just %s\n\nPackage this mod for Release Targets, and archive in the multi-target zip for upload to the Mod Repository.\nCan build Shipping C++ as required."), *Mod->GetName()));
                        })
                        .IsEnabled_Lambda([this]{
                            return !FAlpakitModule::Get().IsPackaging();
                        });
            })
            .ModEntryTrail_Lambda([this, TargetColumnWidth] (const TSharedRef<IPlugin>& Mod) {
                TSharedRef<FModTargetsConfig> ModTargetsConfig = ModTargetsConfigs.FindOrAdd(Mod->GetName(), MakeShared<FModTargetsConfig>(Mod));
                
                return SNew(SBox)
                    .Padding(5, 0, 5, 0)
                    .Content()[
                        SNew(SHorizontalBox)
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
