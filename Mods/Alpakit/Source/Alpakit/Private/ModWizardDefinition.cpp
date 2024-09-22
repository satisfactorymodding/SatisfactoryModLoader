#include "ModWizardDefinition.h"

#include "Alpakit.h"
#include "Dom/JsonObject.h"
#include "Features/IPluginsEditorFeature.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Interfaces/IPluginManager.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/App.h"

#define LOCTEXT_NAMESPACE "NewModWizard"

FModWizardDefinition::FModWizardDefinition()
{
	PluginBaseDir = IPluginManager::Get().FindPlugin(TEXT("Alpakit"))->GetBaseDir();

	ModTemplateDefinitions = FAlpakitModule::Get().GetModTemplates();
	for (TSharedRef<FModTemplateDescription> Template : ModTemplateDefinitions)
	{
		TemplateDefinitions.Add(Template->TemplateDescription);
	}
}

const TArray<TSharedRef<FPluginTemplateDescription>>& FModWizardDefinition::GetTemplatesSource() const
{
	return TemplateDefinitions;
}


void FModWizardDefinition::OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo)
{
	if (InSelectedItem.IsValid())
	{
		TSharedRef<FModTemplateDescription>* Found = ModTemplateDefinitions.FindByPredicate([InSelectedItem](TSharedRef<FModTemplateDescription> Template)
			{ return Template->TemplateDescription == InSelectedItem; });
		if(Found) {
			CurrentTemplateDefinition = *Found;
		}
	}
}

TSharedPtr<FPluginTemplateDescription> FModWizardDefinition::GetSelectedTemplate() const
{
	if(!CurrentTemplateDefinition.IsValid()) {
		return nullptr;
	}
	return CurrentTemplateDefinition->TemplateDescription;
}

bool FModWizardDefinition::HasValidTemplateSelection() const
{
	return CurrentTemplateDefinition.IsValid();
}

void FModWizardDefinition::ClearTemplateSelection()
{
	CurrentTemplateDefinition.Reset();
}

bool FModWizardDefinition::HasModules() const
{
	FString SourceFolderPath = GetPluginFolderPath() / TEXT("Source");
	
	return FPaths::DirectoryExists(SourceFolderPath);
}

bool FModWizardDefinition::IsMod() const
{
	return true;
}

FText FModWizardDefinition::GetInstructions() const
{
	return LOCTEXT("ChooseModTemplate", "Choose a template and then specify a name to create a new mod. Remember, your plugin name (mod reference) can no longer be changed after you release the mod! See the docs for more info.");
}

bool FModWizardDefinition::GetPluginIconPath(FString& OutIconPath) const
{
	if(!CurrentTemplateDefinition.IsValid()) {
		return false;
	}
	return GetTemplateIconPath(CurrentTemplateDefinition.ToSharedRef()->TemplateDescription, OutIconPath);
}

EHostType::Type FModWizardDefinition::GetPluginModuleDescriptor() const
{
	EHostType::Type ModuleDescriptorType = EHostType::Runtime;

	if (CurrentTemplateDefinition.IsValid())
	{
		ModuleDescriptorType = CurrentTemplateDefinition->TemplateDescription->ModuleDescriptorType;
	}

	return ModuleDescriptorType;
}

ELoadingPhase::Type FModWizardDefinition::GetPluginLoadingPhase() const
{
	ELoadingPhase::Type Phase = ELoadingPhase::Default;

	if (CurrentTemplateDefinition.IsValid())
	{
		Phase = CurrentTemplateDefinition->TemplateDescription->LoadingPhase;
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
		SelectedFolders.Add(GetFolderForTemplate(CurrentTemplateDefinition.ToSharedRef()->TemplateDescription));
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
	if (Descriptor.FriendlyName.IsEmpty()) {
		Descriptor.FriendlyName = PluginName;
	}
	Descriptor.AdditionalFieldsToWrite.Add( TEXT("SemVersion"), MakeShared<FJsonValueString>( TEXT("1.0.0") ) );
	Descriptor.AdditionalFieldsToWrite.Add( TEXT("GameVersion"), MakeShared<FJsonValueString>(FString::Printf(TEXT(">=%s"), *FAlpakitModule::GetCurrentGameVersion())) );
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
	SMLDependency.AdditionalFieldsToWrite.Add( TEXT("SemVersion"), MakeShared<FJsonValueString>( TEXT("^") + SMLPlugin->GetDescriptor().VersionName ) );
	Descriptor.Plugins.Add(SMLDependency);

	// Initialize extra dependencies
	for (const TSharedPtr<FModTemplateDependency>& Dependency : CurrentTemplateDefinition->Dependencies) {
		FPluginReferenceDescriptor DependencyDescriptor(Dependency->Name, true);
		DependencyDescriptor.AdditionalFieldsToWrite.Add( TEXT("SemVersion"), MakeShared<FJsonValueString>( TEXT("^") + Dependency->Version ) );
		if(Dependency->bOptional) {
			DependencyDescriptor.bOptional = true;
		}
		if(Dependency->bBasePlugin) {
			DependencyDescriptor.AdditionalFieldsToWrite.Add( TEXT("BasePlugin"), MakeShared<FJsonValueBoolean>( true ) );
		}
		Descriptor.Plugins.Add(DependencyDescriptor);
	}

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
	return GetFolderForTemplate(CurrentTemplateDefinition.ToSharedRef()->TemplateDescription);
}

FString FModWizardDefinition::GetFolderForTemplate(TSharedRef<FPluginTemplateDescription> InTemplate) const
{
	return InTemplate->OnDiskPath;
}

TSharedPtr<FModTemplateDependency> FModTemplateDependency::Load(const TSharedPtr<FJsonObject> JSON, FString& Error)
{
	FString DependencyName;
	if(!JSON->TryGetStringField(TEXT("name"), DependencyName)) {
		Error = TEXT("\"name\" not in dependency");
		return nullptr;
	}

	FString DependencyVersion;
	if(!JSON->TryGetStringField(TEXT("version"), DependencyVersion)) {
		TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(DependencyName);
		if(!Plugin.IsValid()) {
			Error = TEXT("\"version\" not in dependency and plugin not installed");
			return nullptr;
		}
		DependencyVersion = Plugin->GetDescriptor().VersionName;
	}

	bool bOptional = false;
	JSON->TryGetBoolField(TEXT("optional"), bOptional);

	bool bBasePlugin = false;
	JSON->TryGetBoolField(TEXT("basePlugin"), bBasePlugin);

	return MakeShareable(new FModTemplateDependency(DependencyName, DependencyVersion, bOptional, bBasePlugin));
}

TSharedPtr<FModTemplateDescription> FModTemplateDescription::Load(const TSharedPtr<FJsonObject> JSON, const FString TemplatesPath, FString& Error)
{
	FString TemplateName;
	if(!JSON->TryGetStringField(TEXT("name"), TemplateName)) {
		Error = TEXT("\"name\" not in template");
		return nullptr;
	}

	FString TemplateDescription;
	if(!JSON->TryGetStringField(TEXT("description"), TemplateDescription)) {
		Error = TEXT("\"description\" not in template");
		return nullptr;
	}

	FString TemplateFolderName;
	if(!JSON->TryGetStringField(TEXT("path"), TemplateFolderName)) {
		Error = TEXT("\"path\" not in template");
		return nullptr;
	}

	TArray<TSharedPtr<FModTemplateDependency>> Dependencies;
	const TArray<TSharedPtr<FJsonValue>>* DependenciesPtr;
	if(JSON->TryGetArrayField(TEXT("dependencies"), DependenciesPtr)) {
		int i = 0;
		for(const TSharedPtr<FJsonValue>& Item : *DependenciesPtr) {
			i++;
			const TSharedPtr<FJsonObject>* DependencyObjPtr;
			if(!Item->TryGetObject(DependencyObjPtr)) {
				Error = FString::Printf(TEXT("dependency %d: not an object"), i);
				return nullptr;
			}

			FString DependencyError;
			TSharedPtr<FModTemplateDependency> Dependency = FModTemplateDependency::Load(*DependencyObjPtr, DependencyError);
			if (!Dependency.IsValid()) {
				Error = FString::Printf(TEXT("dependency %d: %s"), i, *DependencyError);
				return nullptr;
			}
			
			Dependencies.Add(Dependency);
		}
	}

	TSharedRef<FPluginTemplateDescription> PluginTemplateDescription = MakeShareable(new FPluginTemplateDescription(
			FText::FromString(TemplateName),
			FText::FromString(TemplateDescription),
			TemplatesPath / TemplateFolderName,
			true,
			EHostType::Runtime));
	PluginTemplateDescription->bCanBePlacedInEngine = false;
    return MakeShareable(new FModTemplateDescription(PluginTemplateDescription, Dependencies));
}

#undef LOCTEXT_NAMESPACE
