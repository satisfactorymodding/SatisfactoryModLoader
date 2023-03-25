#include "ModWizardDefinition.h"

#include "Alpakit.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/App.h"

#define LOCTEXT_NAMESPACE "NewModWizard"

FModWizardDefinition::FModWizardDefinition(bool bContentOnlyProject)
	: bIsContentOnlyProject(bContentOnlyProject)
{
	PluginBaseDir = IPluginManager::Get().FindPlugin(TEXT("Alpakit"))->GetBaseDir();

	PopulateTemplatesSource();
}

void FModWizardDefinition::PopulateTemplatesSource()
{
	const FText CPPTemplateName = LOCTEXT("CPPLabel", "C++ & Blueprint");
	const FText BPTemplateName = LOCTEXT("BPLabel", "Blueprint Only");
	const FText CLBPTemplateName = LOCTEXT("CLBPLabel", "ContentLib: Blueprint Only");

	const FText CPPTemplateDescription = LOCTEXT("CPPDesc", "Create a mod that contains both C++ and Blueprint code.");
	const FText BPTemplateDescription = LOCTEXT("BPDesc", "Create a mod that contains only Blueprint code. (You can add C++ code later)");
	const FText CLBPTemplateDescription = LOCTEXT("BPDesc", "Create a mod that is ready to use ContentLib JSON features. Consider downloading a copy of the ContentLib mod to use its Blueprint/C++ libraries in your editor!");

	TemplateDefinitions.Add(MakeShareable(new FPluginTemplateDescription(BPTemplateName, BPTemplateDescription, TEXT("BlueprintBlank"), true, EHostType::Runtime)));
	if (!bIsContentOnlyProject)
	{
		// Insert the blank template to make sure it appears before the content only template.
		TemplateDefinitions.Insert(MakeShareable(new FPluginTemplateDescription(CPPTemplateName, CPPTemplateDescription, TEXT("CPPAndBlueprintBlank"), true, EHostType::Runtime)), 0);
	}
	TemplateDefinitions.Add(MakeShareable(new FPluginTemplateDescription(CLBPTemplateDescription, CLBPTemplateDescription, TEXT("ContentLibBlueprintBlank"), true, EHostType::Runtime)));
	// TODO template needs to bring along dependency on ContentLib and the other assorted CL folders + readme
}

const TArray<TSharedRef<FPluginTemplateDescription>>& FModWizardDefinition::GetTemplatesSource() const
{
	return TemplateDefinitions;
}


void FModWizardDefinition::OnTemplateSelectionChanged(TArray<TSharedRef<FPluginTemplateDescription>> InSelectedItems, ESelectInfo::Type SelectInfo)
{
	CurrentTemplateDefinition.Reset();
	
	if (InSelectedItems.Num() > 0)
	{
		CurrentTemplateDefinition = InSelectedItems[0];
	}
}

TArray<TSharedPtr<FPluginTemplateDescription>> FModWizardDefinition::GetSelectedTemplates() const
{
	TArray<TSharedPtr<FPluginTemplateDescription>> Selection;
	if (CurrentTemplateDefinition.IsValid())
	{
		Selection.Add(CurrentTemplateDefinition);
	}

	return Selection;
}

bool FModWizardDefinition::HasValidTemplateSelection() const
{
	return CurrentTemplateDefinition.IsValid();
}

void FModWizardDefinition::ClearTemplateSelection()
{
	CurrentTemplateDefinition.Reset();
}

bool FModWizardDefinition::AllowsEnginePlugins() const
{
	// Don't show the option to make an engine plugin in installed builds
	return !FApp::IsEngineInstalled();
}

bool FModWizardDefinition::CanContainContent() const
{
	return CurrentTemplateDefinition.IsValid() ? CurrentTemplateDefinition->bCanContainContent : false;
}

bool FModWizardDefinition::HasModules() const
{
	FString SourceFolderPath = GetPluginFolderPath() / TEXT("Source");
	
	return FPaths::DirectoryExists(SourceFolderPath);
}

bool FModWizardDefinition::IsMod() const
{
	return false; // TODO Update this when migrating to Mods
}

FText FModWizardDefinition::GetInstructions() const
{
	return LOCTEXT("ChooseModTemplate", "Choose a template and then specify a name to create a new mod.");
}

bool FModWizardDefinition::GetPluginIconPath(FString& OutIconPath) const
{
	return GetTemplateIconPath(CurrentTemplateDefinition.ToSharedRef(), OutIconPath);
}

EHostType::Type FModWizardDefinition::GetPluginModuleDescriptor() const
{
	EHostType::Type ModuleDescriptorType = EHostType::Runtime;

	if (CurrentTemplateDefinition.IsValid())
	{
		ModuleDescriptorType = CurrentTemplateDefinition->ModuleDescriptorType;
	}

	return ModuleDescriptorType;
}

ELoadingPhase::Type FModWizardDefinition::GetPluginLoadingPhase() const
{
	ELoadingPhase::Type Phase = ELoadingPhase::Default;

	if (CurrentTemplateDefinition.IsValid())
	{
		Phase = CurrentTemplateDefinition->LoadingPhase;
	}

	return Phase;
}

bool FModWizardDefinition::GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> Template, FString& OutIconPath) const
{
	bool bRequiresDefaultIcon = false;

	FString TemplateFolderName = GetFolderForTemplate(Template);

	OutIconPath = TemplateFolderName / TEXT("Resources/Icon128.png");
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*OutIconPath))
	{
		OutIconPath = PluginBaseDir / TEXT("Resources/DefaultIcon128.png");
		bRequiresDefaultIcon = true;
	}

	return bRequiresDefaultIcon;
}

TArray<FString> FModWizardDefinition::GetFoldersForSelection() const
{
	TArray<FString> SelectedFolders;

	if (CurrentTemplateDefinition.IsValid())
	{
		SelectedFolders.Add(GetFolderForTemplate(CurrentTemplateDefinition.ToSharedRef()));
	}

	return SelectedFolders;
}

void FModWizardDefinition::PluginCreated(const FString& PluginName, bool bWasSuccessful) const
{
	if(!bWasSuccessful)
	{
		UE_LOG(LogAlpakit, Error, TEXT("Failed to create mod %s"), *PluginName);
		return;
	}
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName);
	if(!Plugin.IsValid())
	{
		UE_LOG(LogAlpakit, Error, TEXT("Created mod %s was invalid"), *PluginName);
		return;
	}
	// Initialize SML required fields
	FPluginDescriptor Descriptor = Plugin->GetDescriptor();
	Descriptor.SemVersion = TEXT("1.0.0");
	Descriptor.VersionName = TEXT("1.0.0");
	Descriptor.Version = 1;
	Descriptor.Category = TEXT("Modding");

	// Initialize SML dependency
	TSharedPtr<IPlugin> SMLPlugin = IPluginManager::Get().FindPlugin(TEXT("SML"));
	if(!Plugin.IsValid())
	{
		UE_LOG(LogAlpakit, Error, TEXT("Could not find SML plugin"));
		return;
	}
	
	FPluginReferenceDescriptor SMLDependency(TEXT("SML"), true);
	SMLDependency.SemVersion = TEXT("^") + SMLPlugin->GetDescriptor().SemVersion;
	Descriptor.Plugins.Add(SMLDependency);

	FText FailReason; 
	if(!Plugin->UpdateDescriptor(Descriptor, FailReason))
	{
		UE_LOG(LogAlpakit, Error, TEXT("Failed to update descriptor for mod %s: %s"), *PluginName, *FailReason.ToString());
		return;
	}

	UE_LOG(LogAlpakit, Log, TEXT("Created mod %s"), *PluginName);
}

FString FModWizardDefinition::GetPluginFolderPath() const
{
	return GetFolderForTemplate(CurrentTemplateDefinition.ToSharedRef());
}

FString FModWizardDefinition::GetFolderForTemplate(TSharedRef<FPluginTemplateDescription> InTemplate) const
{
	FString TemplateFolderName = PluginBaseDir / TEXT("Templates") / InTemplate->OnDiskPath;

	return TemplateFolderName;
}

#undef LOCTEXT_NAMESPACE