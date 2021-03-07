#include "AlpakitWidget.h"
#include "Alpakit.h"

void SAlpakitWidget::Construct(const FArguments& InArgs) {
	AlpakitSettings = GetMutableDefault<UAlpakitSettings>();
	
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

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(AlpakitSettings);
	//Automatically save alpakit settings when properties are changed
	DetailsView->OnFinishedChangingProperties().AddLambda([this](const FPropertyChangedEvent&) { SaveSettings(); });

	ChildSlot
        .VAlign(VAlign_Fill)
        .HAlign(HAlign_Fill)
        [
            SNew(SVerticalBox)
				+SVerticalBox::Slot()
                .FillHeight(1.0f)
                [
                    SNew(SScrollBox)
                    //The actual list view creation
                    + SScrollBox::Slot()
                        [
                            DetailsView.ToSharedRef()
                        ]
                ]
            +SVerticalBox::Slot()
                .AutoHeight()
                .HAlign(HAlign_Right)
                [
                    SNew(SHorizontalBox)
						+SHorizontalBox::Slot()
                        .Padding(3.0f)
                        .FillWidth(1.0f)
                        .VAlign(VAlign_Center)
                        .HAlign(HAlign_Fill)
						+SHorizontalBox::Slot()
                        .Padding(3.0f)
                        .AutoWidth()
                        .VAlign(VAlign_Center)
                        .HAlign(HAlign_Fill)
                        [
                            SAssignNew(AlpakitButton, SButton)
                            .VAlign(VAlign_Center)
                            .HAlign(HAlign_Center)
                            .Text(FText::FromString("Alpakit!"))
                            .OnClicked_Raw(this, &SAlpakitWidget::PackButtonTriggered)
                        ]
                ]
        ];
}

void SAlpakitWidget::SaveSettings() const {
	AlpakitSettings->SaveSettings();
}

FReply SAlpakitWidget::SavedSettingsTriggered() const {
	SaveSettings();
	return FReply::Handled();
}

FReply SAlpakitWidget::PackButtonTriggered() {
	AlpakitButton->SetEnabled(false);
	FAlpakitModule& AlpakitModule = FModuleManager::GetModuleChecked<FAlpakitModule>(TEXT("Alpakit"));
	AlpakitModule.PackModAssets([=](bool /*bSuccess*/, const FString& /*ErrorMessage*/){
		AlpakitButton->SetEnabled(true);
	});
	return FReply::Handled();
}
