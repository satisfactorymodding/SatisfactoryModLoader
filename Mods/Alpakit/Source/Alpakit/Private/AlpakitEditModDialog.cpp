#include "AlpakitEditModDialog.h"

#include "Alpakit.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "ISourceControlOperation.h"
#include "ISourceControlState.h"
#include "ModMetadataObject.h"
#include "SourceControlOperations.h"
#include "Util/SemVersion.h"

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
	PropertyView->OnFinishedChangingProperties().AddLambda([this](const FPropertyChangedEvent&){
		UpdateGameVersionTarget();
	});

	FString TargetSMLVersion = TEXT("^") + FAlpakitModule::GetCurrentSMLVersion();

	UpdateGameVersionTarget();
	
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
					.Visibility_Lambda([this]
					{
						if (FormatGameVersionRange(ModGameVersionRange) == FormatGameVersionRange(TargetGameVersionRange))
							return EVisibility::Collapsed;
						return EVisibility::Visible;
					})
					.Content()
					[
						SNew(SButton)
						.ButtonColorAndOpacity(FLinearColor::Red)
						.Text_Lambda([this]{ return FText::Format(LOCTEXT("UpdateGameVersionButtonLabel", "Click to update Game Version to {0}"), FText::FromString(FormatGameVersionRange(TargetGameVersionRange))); })
						.HAlign(HAlign_Center)
						.OnClicked_Lambda([this]
						{
							MetadataObject->GameVersion = FormatGameVersionRange(TargetGameVersionRange);
							UpdateGameVersionTarget();
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
				.HAlign(HAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Left)
					[
						SNew(SButton)
						.IsEnabled_Lambda([this]() {
							return !HasCPP();
						})
						.ToolTipText_Lambda([this]() {
							return HasCPP() 
								? LOCTEXT("AddCppButtonDisabledTooltip", "This mod already has C++ module files.") 
								: LOCTEXT("AddCppButtonEnabledTooltip", "Create C++ module files to convert this mod into a hybrid Blueprint and C++ mod. This can't be automatically reversed.");
						})
						.ContentPadding(FMargin(20.0f, 2.0f))
						.Text(LOCTEXT("AddCppButtonLabel", "Convert to C++ & Blueprint Mod"))
						.OnClicked(this, &SAlpakitEditModDialog::OnCPPClicked)
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Right)
					[
						SNew(SButton)
						.ContentPadding(FMargin(20.0f, 2.0f))
						.Text(LOCTEXT("OkButtonLabel", "Ok"))
						.OnClicked(this, &SAlpakitEditModDialog::OnOkClicked)
					]
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

void SAlpakitEditModDialog::UpdateGameVersionTarget() {
	FString _;
	GameVersion.ParseVersion(FString::Printf(TEXT("%s.0.0"), *FAlpakitModule::GetCurrentGameVersion()), _);
	if (!MetadataObject->GameVersion.IsEmpty()) {
		ModGameVersionRange.ParseVersionRange(MetadataObject->GameVersion, _);

		TargetGameVersionRange.ParseVersionRange(MetadataObject->GameVersion, _);
		for (FVersionComparatorCollection& ComparatorCollection : TargetGameVersionRange.Collections) {
			ComparatorCollection.Comparators.Add(FVersionComparator(EVersionComparisonOp::GREATER_EQUALS, GameVersion));
		}

		if (!TargetGameVersionRange.Matches(GameVersion)) {
			TargetGameVersionRange = FVersionRange::CreateRangeWithMinVersion(GameVersion);
		}
	} else {
		ModGameVersionRange = FVersionRange();
		TargetGameVersionRange = FVersionRange::CreateRangeWithMinVersion(GameVersion);
	}
}

FString SAlpakitEditModDialog::FormatGameVersionRange(const FVersionRange& Range) {
	return Range.ToString().Replace(TEXT(".0.0"), TEXT(""));
}

bool SAlpakitEditModDialog::HasCPP()
{
	FString SourceFolderPath = Mod->GetBaseDir() / TEXT("Source");
	return FPaths::DirectoryExists(SourceFolderPath);
}

FReply SAlpakitEditModDialog::OnOkClicked() {
	FPluginDescriptor OldDescriptor = Mod->GetDescriptor();

	// Update the descriptor with the new metadata
	FPluginDescriptor NewDescriptor = OldDescriptor;
	// Ensure we have don't modify the original descriptor for the changed check
	NewDescriptor.CachedJson = MakeShared<FJsonObject>();
	FJsonObject::Duplicate(OldDescriptor.CachedJson, NewDescriptor.CachedJson);
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
		// Don't use UpdateDescriptor here because it doesn't allow removing fields
		FString PluginDescriptorPath = Mod->GetDescriptorFileName();
		FText FailReason;
		if(!NewDescriptor.Save(PluginDescriptorPath, FailReason))
		{
			FMessageDialog::Open(EAppMsgType::Ok, FailReason);
		}
		// Update the descriptor in memory
		if(!Mod->UpdateDescriptor(NewDescriptor, FailReason))
		{
			FMessageDialog::Open(EAppMsgType::Ok, FailReason);
		}
	}
	return FReply::Handled();
}

FReply SAlpakitEditModDialog::OnCPPClicked()
{
	FString SourceDir = Mod->GetBaseDir() / TEXT("Source");
	FString AlpakitDir = IPluginManager::Get().FindPlugin(TEXT("Alpakit"))->GetBaseDir();
	FString TemplatesDir = AlpakitDir / TEXT("Templates");
	FString TemplateSourceDir = TemplatesDir / TEXT("CPPAndBlueprintBlank/Source");
	FString ModName = Mod->GetName();

	// Create Source directory if it doesn't exist
	IFileManager& FileManager = IFileManager::Get();
	if (!FileManager.DirectoryExists(*SourceDir))
	{
		FileManager.MakeDirectory(*SourceDir, true);
	}

	// Copy all files from template Source directory to mod's Source directory
	TArray<FString> Files;
	FileManager.FindFilesRecursive(Files, *TemplateSourceDir, TEXT("*.*"), true, false);
	for (const FString& File : Files)
	{
		FString RelativePath = File.RightChop(TemplateSourceDir.Len() + 1);
		// Replace PLUGIN_NAME in directory and file names
		RelativePath = RelativePath.Replace(TEXT("PLUGIN_NAME"), *ModName);
		FString TargetPath = SourceDir / RelativePath;
		
		// Create target directory if it doesn't exist
		FString TargetDir = FPaths::GetPath(TargetPath);
		if (!FileManager.DirectoryExists(*TargetDir))
		{
			FileManager.MakeDirectory(*TargetDir, true);
		}

		// Read the file content
		FString FileContent;
		if (FFileHelper::LoadFileToString(FileContent, *File))
		{
			// Replace PLUGIN_NAME in file content
			FileContent = FileContent.Replace(TEXT("PLUGIN_NAME"), *ModName);
			
			// Write the modified content to the target file
			FFileHelper::SaveStringToFile(FileContent, *TargetPath);
		}
	}

	// Modify the .uplugin file to add the module configuration
	FString PluginDescriptorPath = Mod->GetDescriptorFileName();
	FString PluginContent;
	if (FFileHelper::LoadFileToString(PluginContent, *PluginDescriptorPath))
	{
		// Parse the JSON content
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(PluginContent);
		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			// Create the module array if it doesn't exist
			if (!JsonObject->HasField(TEXT("Modules")))
			{
				TArray<TSharedPtr<FJsonValue>> ModulesArray;
				TSharedPtr<FJsonObject> ModuleObject = MakeShared<FJsonObject>();
				ModuleObject->SetStringField(TEXT("Name"), ModName);
				ModuleObject->SetStringField(TEXT("Type"), TEXT("Runtime"));
				ModuleObject->SetStringField(TEXT("LoadingPhase"), TEXT("Default"));
				ModulesArray.Add(MakeShared<FJsonValueObject>(ModuleObject));
				JsonObject->SetArrayField(TEXT("Modules"), ModulesArray);

				// Write the modified JSON back to the file
				FString OutputString;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
				FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
				FFileHelper::SaveStringToFile(OutputString, *PluginDescriptorPath);
			}
		}
	}

	// Show popup message
	FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("AddCppFilesSuccessMessage", "C++ files created. You must manually build the project for the Development Editor target before you can use them in the Unreal editor. You also must regenerate Visual Studio project files for them to appear in VS/Rider."));

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
