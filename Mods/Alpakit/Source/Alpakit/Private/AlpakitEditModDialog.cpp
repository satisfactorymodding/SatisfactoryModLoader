#include "AlpakitEditModDialog.h"

#include "Alpakit.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "ISourceControlOperation.h"
#include "ISourceControlState.h"
#include "ModMetadataObject.h"
#include "SourceControlOperations.h"

#define LOCTEXT_NAMESPACE "AlpakitEditMod"

void SAlpakitEditModDialog::Construct(const FArguments& InArgs, TSharedRef<IPlugin> InMod) {
	Mod = InMod;
	
	// Construct the plugin metadata object using the descriptor for this plugin
	MetadataObject = NewObject<UModMetadataObject>();
	MetadataObject->TargetIconPath = Mod->GetBaseDir() / TEXT("Resources/Icon128.png");
	MetadataObject->PopulateFromDescriptor(Mod->GetDescriptor());
	MetadataObject->AddToRoot();

	// Create a property view
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	EditModule.RegisterCustomClassLayout(UModMetadataObject::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FModMetadataCustomization::MakeInstance));
	TSharedRef<IDetailsView> PropertyView = EditModule.CreateDetailView(FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true));
	PropertyView->SetObject(MetadataObject, true);

	FString TargetSMLVersion = TEXT("^") + FAlpakitModule::GetCurrentSMLVersion();
	FString TargetGameVersion = FAlpakitModule::GetCurrentGameVersion();
	
	SWindow::Construct(SWindow::FArguments()
		.ClientSize(FVector2D(800.0f, 700.0f))
		.Title(FText::Format(LOCTEXT("ModMetadata", "{0} ({1}) Properties"), FText::FromString(Mod->GetFriendlyName()), FText::FromString(Mod->GetName())))
		.Content()
		[
			SNew(SBorder)
			.Padding(FMargin(8.0f, 8.0f))
			[
				SNew(SVerticalBox)

				+SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill)
				[
					SNew(SBox)
					.Visibility_Lambda([this, TargetSMLVersion]
					{
						FString SMLVersion = GetSMLDependencyVersion();
						if (SMLVersion.IsEmpty() || SMLVersion == TargetSMLVersion)
							return EVisibility::Collapsed;
						return EVisibility::Visible;
					})
					.Content()
					[
						SNew(SButton)
						.ButtonColorAndOpacity(FLinearColor::Red)
						.Text(FText::Format(LOCTEXT("UpdateSMLVersionButtonLabel", "Click to update SML dependency to {0}"), FText::FromString(TargetSMLVersion)))
						.HAlign(HAlign_Center)
						.OnClicked_Lambda([this, TargetSMLVersion]
						{
							SetSMLDependencyVersion(TargetSMLVersion);
							return FReply::Handled();
						})
					]
				]

				+SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Fill)
				[
					SNew(SBox)
					.Visibility_Lambda([this, TargetGameVersion]
					{
						if (MetadataObject->GameVersion == TargetGameVersion)
							return EVisibility::Collapsed;
						return EVisibility::Visible;
					})
					.Content()
					[
						SNew(SButton)
						.ButtonColorAndOpacity(FLinearColor::Red)
						.Text(FText::Format(LOCTEXT("UpdateGameVersionButtonLabel", "Update Game Version to {0}"), FText::FromString(TargetGameVersion)))
						.HAlign(HAlign_Center)
						.OnClicked_Lambda([this, TargetGameVersion]
						{
							MetadataObject->GameVersion = TargetGameVersion;
							return FReply::Handled();
						})
					]
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
					.OnClicked(this, &SAlpakitEditModDialog::OnOkClicked)
				]
			]
		]
	);
}

FString SAlpakitEditModDialog::GetSMLDependencyVersion() const
{
	FModDependencyDescriptorData* SMLDependency = MetadataObject->Dependencies.FindByPredicate([](FModDependencyDescriptorData& Dependency)
	{
		return Dependency.Name == TEXT("SML");
	});
	if (SMLDependency != nullptr)
		return SMLDependency->SemVersion;
	
	return TEXT("");
}

void SAlpakitEditModDialog::SetSMLDependencyVersion(FString Version) const
{
	FModDependencyDescriptorData* SMLDependency = MetadataObject->Dependencies.FindByPredicate([](FModDependencyDescriptorData& Dependency)
	{
		return Dependency.Name == TEXT("SML");
	});
	if (SMLDependency == nullptr)
		return;
	SMLDependency->SemVersion = Version;
}

FString SAlpakitEditModDialog::GetGameVersion() const
{
	return MetadataObject->GameVersion;
}

FReply SAlpakitEditModDialog::OnOkClicked() {
	FPluginDescriptor OldDescriptor = Mod->GetDescriptor();

	// Update the descriptor with the new metadata
	FPluginDescriptor NewDescriptor = OldDescriptor;
	MetadataObject->CopyIntoDescriptor(NewDescriptor);
	MetadataObject->RemoveFromRoot();

	// Close the properties window
	RequestDestroyWindow();

	// Compare the old and new descriptor, so we don't write to the file if nothing changed
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

#undef LOCTEXT_NAMESPACE
