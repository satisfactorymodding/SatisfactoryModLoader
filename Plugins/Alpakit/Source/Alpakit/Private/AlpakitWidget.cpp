#include "AlpakitWidget.h"
#include "Alpakit.h"
#include "AlpakitModEntryList.h"
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

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
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
			SNew(SAlpakitModEntryList)
		]
	];
}

#undef LOCTEXT_NAMESPACE
