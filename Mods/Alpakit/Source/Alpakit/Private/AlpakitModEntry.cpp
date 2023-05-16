#include "AlpakitModEntry.h"
#include "Alpakit.h"
#include "AlpakitSettings.h"
#include "AlpakitStyle.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "ISourceControlOperation.h"
#include "ModMetadataObject.h"
#include "SourceControlOperations.h"
#include "Async/Async.h"
#include "UATHelper/Public/IUATHelperModule.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntry::Construct(const FArguments& Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner) {
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
            SNew(SButton)
            .Text(LOCTEXT("PackageModAlpakit", "Alpakit!"))
            .OnClicked_Lambda([this](){
                PackageMod(TArray<TSharedPtr<SAlpakitModEntry>>());
                return FReply::Handled();
            })
            .ToolTipText_Lambda([this](){
                return FText::FromString(FString::Printf(TEXT("Alpakit %s"), *this->Mod->GetName()));
            })
        ]
        + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[
            SNew(SButton)
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
	// Construct the plugin metadata object using the descriptor for this plugin
	UModMetadataObject* MetadataObject = NewObject<UModMetadataObject>();
	MetadataObject->TargetIconPath = Mod->GetBaseDir() / TEXT("Resources/Icon128.png");
	MetadataObject->PopulateFromDescriptor(Mod->GetDescriptor());
	MetadataObject->AddToRoot();

	// Create a property view
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	EditModule.RegisterCustomClassLayout(UModMetadataObject::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FModMetadataCustomization::MakeInstance));
	TSharedRef<IDetailsView> PropertyView = EditModule.CreateDetailView(FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true));
	PropertyView->SetObject(MetadataObject, true);

	// Create the window
	PropertiesWindow = SNew(SWindow)
		.ClientSize(FVector2D(800.0f, 700.0f))
		.Title(LOCTEXT("ModMetadata", "Mod Properties"))
		.Content()
		[
			SNew(SBorder)
			.Padding(FMargin(8.0f, 8.0f))
			[
				SNew(SVerticalBox)

				+SVerticalBox::Slot()
				.AutoHeight()
				.Padding(FMargin(5.0f, 10.0f, 5.0f, 5.0f))
				[
					SNew(STextBlock)
					.Text(FText::FromString(Mod->GetName()))
				]

				+ SVerticalBox::Slot()
				.Padding(5)
				[
					PropertyView
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5)
				.HAlign(HAlign_Right)
				[
					SNew(SButton)
					.ContentPadding(FMargin(20.0f, 2.0f))
					.Text(LOCTEXT("OkButtonLabel", "Ok"))
					.OnClicked(this, &SAlpakitModEntry::OnEditModFinished, MetadataObject)
				]
			]
		];

	FSlateApplication::Get().AddModalWindow(PropertiesWindow.ToSharedRef(), Owner);
}

FReply SAlpakitModEntry::OnEditModFinished(UModMetadataObject* MetadataObject)
{
	FPluginDescriptor OldDescriptor = Mod->GetDescriptor();

	// Update the descriptor with the new metadata
	FPluginDescriptor NewDescriptor = OldDescriptor;
	MetadataObject->CopyIntoDescriptor(NewDescriptor);
	MetadataObject->RemoveFromRoot();

	// Close the properties window
	PropertiesWindow->RequestDestroyWindow();

	// Write both to strings
	FString OldText;
	OldDescriptor.Write(OldText);
	FString NewText;
	NewDescriptor.Write(NewText);
	if(OldText.Compare(NewText, ESearchCase::CaseSensitive) != 0)
	{
		FString DescriptorFileName = Mod->GetDescriptorFileName();

		// First attempt to check out the file if SCC is enabled
		ISourceControlModule& SourceControlModule = ISourceControlModule::Get();
		if(SourceControlModule.IsEnabled())
		{
			ISourceControlProvider& SourceControlProvider = SourceControlModule.GetProvider();
			TSharedPtr<ISourceControlState, ESPMode::ThreadSafe> SourceControlState = SourceControlProvider.GetState(DescriptorFileName, EStateCacheUsage::ForceUpdate);
			if(SourceControlState.IsValid() && SourceControlState->CanCheckout())
			{
				SourceControlProvider.Execute(ISourceControlOperation::Create<FCheckOut>(), DescriptorFileName);
			}
		}

		// Write to the file and update the in-memory metadata
		FText FailReason;
		if(!Mod->UpdateDescriptor(NewDescriptor, FailReason))
		{
			FMessageDialog::Open(EAppMsgType::Ok, FailReason);
		}
	}
	return FReply::Handled();
}

FString GetArgumentForLaunchType(EAlpakitStartGameType LaunchMode) {
    switch (LaunchMode) {
    case EAlpakitStartGameType::STEAM:
        return TEXT("Steam");
    case EAlpakitStartGameType::STEAM_SERVER:
        return TEXT("SteamDS");
    case EAlpakitStartGameType::EPIC_EARLY_ACCESS:
        return TEXT("EpicEA");
    case EAlpakitStartGameType::EPIC_EXPERIMENTAL:
        return TEXT("EpicExp");
    case EAlpakitStartGameType::EPIC_SERVER:
        return TEXT("EpicDS");
    default:
        return TEXT("");
    }
}

FText GetCurrentPlatformName() {
#if PLATFORM_WINDOWS
    return LOCTEXT("PlatformName_Windows", "Windows");
#elif PLATFORM_MAC
    return LOCTEXT("PlatformName_Mac", "Mac");
#elif PLATFORM_LINUX
    return LOCTEXT("PlatformName_Linux", "Linux");
#else
    return LOCTEXT("PlatformName_Other", "Other OS");
#endif
}

FString MakeUATArguments(FAlpakitTargetSettings TargetSettings, FString TargetName, bool LaunchGame = false)
{
    FString UATArguments;
    
    if(TargetSettings.bCopyModsToGame) {
        UATArguments.Append(FString::Printf(TEXT("-%s_CopyToGameDir "), *TargetName));
    	UATArguments.Append(FString::Printf(TEXT("-%s_GameDir=%s "), *TargetName, *TargetSettings.SatisfactoryGamePath.Path));

    	if(TargetSettings.LaunchGameAfterPacking != EAlpakitStartGameType::NONE && LaunchGame) {
    		UATArguments.Append(FString::Printf(TEXT("-%s_LaunchGame "), *TargetName));
    		UATArguments.Append(FString::Printf(TEXT("-%s_LaunchType=%s "), *TargetName, *GetArgumentForLaunchType(TargetSettings.LaunchGameAfterPacking)));
    	}
    }

    return UATArguments;
}

void SAlpakitModEntry::PackageMod(const TArray<TSharedPtr<SAlpakitModEntry>>& NextEntries) const {
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();

    const FString ProjectPath = FPaths::IsProjectFilePathSet()
        ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath())
        : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");

    FString AdditionalUATArguments;

    if(Settings->WindowsNoEditorTargetSettings.bEnabled)
    {
        AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64\" "));
        AdditionalUATArguments.Append(MakeUATArguments(Settings->WindowsNoEditorTargetSettings, TEXT("WindowsNoEditor"), NextEntries.Num() == 0));
    }

    if(Settings->WindowsServerTargetSettings.bEnabled)
    {
        AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Win64_Server\" "));
        AdditionalUATArguments.Append(MakeUATArguments(Settings->WindowsServerTargetSettings, TEXT("WindowsServer"), NextEntries.Num() == 0));
    }

    if(Settings->LinuxServerTargetSettings.bEnabled)
    {
        AdditionalUATArguments.Append(TEXT("-PluginTarget=\"Linux_Server\" "));
        AdditionalUATArguments.Append(MakeUATArguments(Settings->LinuxServerTargetSettings, TEXT("LinuxServer"), NextEntries.Num() == 0));
    }

	if(Settings->bMerge)
	{
		AdditionalUATArguments.Append(TEXT("-MergeArchive"));	
	}

    UE_LOG(LogAlpakit, Display, TEXT("Packaging plugin \"%s\". %d remaining"), *PluginName, NextEntries.Num());

    const FString CommandLine = FString::Printf(TEXT("-Compile -ScriptsForProject=\"%s\" PackagePlugin -Project=\"%s\" -PluginName=\"%s\" %s"),
                                                *ProjectPath, *ProjectPath, *PluginName, *AdditionalUATArguments);

    const FText PlatformName = GetCurrentPlatformName();
    IUATHelperModule::Get().CreateUatTask(
        CommandLine,
        PlatformName,
        LOCTEXT("PackageModTaskName", "Packaging Mod"),
        LOCTEXT("PackageModTaskShortName", "Package Mod Task"),
        FAlpakitStyle::Get().GetBrush("Alpakit.OpenPluginWindow"),
        NextEntries.Num() == 0 ? (IUATHelperModule::UatTaskResultCallack)nullptr : [NextEntries](FString resultType, double runTime) {
            AsyncTask(ENamedThreads::GameThread, [NextEntries]() {
                TSharedPtr<SAlpakitModEntry> NextMod = NextEntries[0];

                TArray<TSharedPtr<SAlpakitModEntry>> RemainingEntries = NextEntries.FilterByPredicate([NextMod](const TSharedPtr<SAlpakitModEntry>& X) {
                    return X != NextMod;
                });

                NextMod->PackageMod(RemainingEntries);
            });
        }
    );
}

void SAlpakitModEntry::OnEnableCheckboxChanged(ECheckBoxState NewState) {
    // Save new checked state for the mod at the
    UAlpakitSettings* Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();

    Settings->ModSelection.Add(PluginName, NewState == ECheckBoxState::Checked);

    Settings->SaveSettings();
}

#undef LOCTEXT_NAMESPACE
