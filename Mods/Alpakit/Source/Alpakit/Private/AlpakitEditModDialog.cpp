#include "AlpakitEditModDialog.h"

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
	
	SWindow::Construct(SWindow::FArguments()
		.ClientSize(FVector2D(800.0f, 700.0f))
		.Title(FText::Format(LOCTEXT("ModMetadata", "{0} ({1}) Properties"), FText::FromString(Mod->GetFriendlyName()), FText::FromString(Mod->GetName())))
		.Content()
		[
			SNew(SBorder)
			.Padding(FMargin(8.0f, 8.0f))
			[
				SNew(SVerticalBox)

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

FReply SAlpakitEditModDialog::OnOkClicked() {
	FPluginDescriptor OldDescriptor = Mod->GetDescriptor();

	// Update the descriptor with the new metadata
	FPluginDescriptor NewDescriptor = OldDescriptor;
	MetadataObject->CopyIntoDescriptor(NewDescriptor);
	MetadataObject->RemoveFromRoot();

	// Close the properties window
	RequestDestroyWindow();

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

#undef LOCTEXT_NAMESPACE
