#include "AlpakitModEntry.h"
#include "Alpakit.h"
#include "AlpakitEditModDialog.h"
#include "AlpakitSettings.h"
#include "ISourceControlModule.h"
#include "ModTargetsConfig.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntry::Construct(const FArguments& Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner) {
	FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>("Alpakit");
	AlpakitModule.GetOnQueueStarted().AddSP(this, &SAlpakitModEntry::QueueStarted);
	AlpakitModule.GetOnQueueComplete().AddSP(this, &SAlpakitModEntry::QueueComplete);
	
    Mod = InMod;
	Owner = InOwner;

    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();

    Checkbox = SNew(SCheckBox)
        .ToolTipText(LOCTEXT("AlpakitModEntryEnabled_Tooltip", "If enabled, this mod will be packaged when the Alpakit Dev or Alpakit Release buttons are pressed"))
        .OnCheckStateChanged(this, &SAlpakitModEntry::OnEnableCheckboxChanged)
        .IsChecked(Settings->ModSelection.FindOrAdd(PluginName, false) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);

    ModTargetsConfig = FModTargetsConfig(InMod);
    
    ChildSlot[
        SNew(SHorizontalBox)
        + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
            Checkbox.ToSharedRef()
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
            SAssignNew(EditButton, SButton)
            .Text(LOCTEXT("EditModAlpakit", "Edit"))
            .OnClicked_Lambda([this](){
                const TSharedRef<SAlpakitEditModDialog> EditModDialog = SNew(SAlpakitEditModDialog, Mod.ToSharedRef());
                FSlateApplication::Get().AddModalWindow(EditModDialog, Owner);
                return FReply::Handled();
            })
            .ToolTipText_Lambda([this](){
                return FText::FromString(FString::Printf(TEXT("Edit %s via the wizard"), *this->Mod->GetName()));
            })
        ]
        + SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[
            SNew(STextBlock)
            .Text_Lambda([InMod]() {
                const FString DisplayText = FString::Printf(TEXT("%s (%s)"), *InMod->GetDescriptor().FriendlyName, *InMod->GetName());
                return FText::FromString(DisplayText);
            })
            .HighlightText_Lambda([InOwner]() {
                return FText::FromString(InOwner->GetLastFilter());
            })
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(20, 0)[
            SNew(SCheckBox)
            .IsChecked(ModTargetsConfig.bWindowsNoEditor ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
            .OnCheckStateChanged_Lambda([this](ECheckBoxState State) {
                ModTargetsConfig.bWindowsNoEditor = State == ECheckBoxState::Checked;
                ModTargetsConfig.Save();
            })
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(38, 0)[
            SNew(SCheckBox)
            .IsChecked(ModTargetsConfig.bWindowsServer ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
            .OnCheckStateChanged_Lambda([this](ECheckBoxState State) {
                ModTargetsConfig.bWindowsServer = State == ECheckBoxState::Checked;
                ModTargetsConfig.Save();
            })
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(28, 0)[
            SNew(SCheckBox)
            .IsChecked(ModTargetsConfig.bLinuxServer ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
            .OnCheckStateChanged_Lambda([this](ECheckBoxState State) {
                ModTargetsConfig.bLinuxServer = State == ECheckBoxState::Checked;
                ModTargetsConfig.Save();
            })
        ]
    ];
}

void SAlpakitModEntry::QueueStarted() {
	EditButton->SetEnabled(false);
}

void SAlpakitModEntry::QueueComplete() {
	EditButton->SetEnabled(true);
}

void SAlpakitModEntry::OnEnableCheckboxChanged(ECheckBoxState NewState) {
    // Save new checked state for the mod at the
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();

    Settings->ModSelection.Add(PluginName, NewState == ECheckBoxState::Checked);

    Settings->SaveSettings();

	Owner->UpdateAllCheckbox();
}

#undef LOCTEXT_NAMESPACE
