#include "AlpakitModEntry.h"
#include "Alpakit.h"
#include "AlpakitEditModDialog.h"
#include "AlpakitSettings.h"
#include "ISourceControlModule.h"

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
        .OnCheckStateChanged(this, &SAlpakitModEntry::OnEnableCheckboxChanged)
        .IsChecked(Settings->ModSelection.FindOrAdd(PluginName, false));

    ChildSlot[
        SNew(SHorizontalBox)
        + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
            Checkbox.ToSharedRef()
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
            SAssignNew(AlpakitButton, SButton)
            .Text(LOCTEXT("PackageModAlpakit", "Alpakit!"))
            .OnClicked_Lambda([this](){
                PackageMod();
                return FReply::Handled();
            })
            .ToolTipText_Lambda([this](){
                return FText::FromString(FString::Printf(TEXT("Alpakit %s"), *this->Mod->GetName()));
            })
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
            SAssignNew(EditButton, SButton)
            .Text(LOCTEXT("EditModAlpakit", "Edit"))
            .OnClicked_Lambda([this](){
				this->OnEditMod();
                return FReply::Handled();
            })
            .ToolTipText_Lambda([this](){
                return FText::FromString(FString::Printf(TEXT("Edit %s"), *this->Mod->GetName()));
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
    ];
}
void SAlpakitModEntry::OnEditMod()
{
    const TSharedRef<SAlpakitEditModDialog> EditModDialog = SNew(SAlpakitEditModDialog, Mod.ToSharedRef());
	FSlateApplication::Get().AddModalWindow(EditModDialog, Owner);
}

void SAlpakitModEntry::QueueStarted() {
	AlpakitButton->SetEnabled(false);
	EditButton->SetEnabled(false);
}

void SAlpakitModEntry::QueueComplete() {
	AlpakitButton->SetEnabled(true);
	EditButton->SetEnabled(true);
}

void SAlpakitModEntry::PackageMod() const {
	FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));
	AlpakitModule.PackageMods({ Mod->GetName() });
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
