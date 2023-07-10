#pragma once

#include "IPluginWizardDefinition.h"

struct FModTemplateDescription;

class FModWizardDefinition : public IPluginWizardDefinition
{
public:
	FModWizardDefinition();

	// Begin IPluginWizardDefinition interface
	virtual const TArray<TSharedRef<FPluginTemplateDescription>>& GetTemplatesSource() const override;
	virtual void OnTemplateSelectionChanged(TSharedPtr<FPluginTemplateDescription> InSelectedItem, ESelectInfo::Type SelectInfo) override;
	virtual TSharedPtr<FPluginTemplateDescription> GetSelectedTemplate() const override;
	virtual void ClearTemplateSelection() override;
	virtual bool HasValidTemplateSelection() const override;

	virtual bool CanShowOnStartup() const override { return false; }
	virtual bool HasModules() const override;
	virtual bool IsMod() const override;
	virtual void OnShowOnStartupCheckboxChanged(ECheckBoxState CheckBoxState) override {}
	virtual ECheckBoxState GetShowOnStartupCheckBoxState() const override { return ECheckBoxState::Undetermined; }
	virtual TSharedPtr<class SWidget> GetCustomHeaderWidget() override { return nullptr; }
	virtual FText GetInstructions() const override;

	virtual bool GetPluginIconPath(FString& OutIconPath) const override;
	virtual EHostType::Type GetPluginModuleDescriptor() const override;
	virtual ELoadingPhase::Type GetPluginLoadingPhase() const override;
	virtual bool GetTemplateIconPath(TSharedRef<FPluginTemplateDescription> InTemplate, FString& OutIconPath) const override;
	virtual FString GetPluginFolderPath() const override;
	virtual TArray<FString> GetFoldersForSelection() const override;
	virtual void PluginCreated(const FString& PluginName, bool bWasSuccessful) const override;
	// End IPluginWizardDefinition interface

private:
	/** Gets the folder for the specified template. */
	FString GetFolderForTemplate(TSharedRef<FPluginTemplateDescription> InTemplate) const;

private:
	/** The templates available to this definition */
	TArray<TSharedRef<FModTemplateDescription>> ModTemplateDefinitions;
	
	/** The inner templates available to this definition */
	TArray<TSharedRef<FPluginTemplateDescription>> TemplateDefinitions;

	/** The currently selected template definition */
	TSharedPtr<FModTemplateDescription> CurrentTemplateDefinition;

	/** Base directory of the plugin templates */
	FString PluginBaseDir;
};

struct FModTemplateDependency
{
	FString Name;
	FString Version;
	bool bOptional;
	bool bBasePlugin;

	FModTemplateDependency(const FString& InName, const FString& InVersion, bool bInOptional, bool bInBasePlugin)
		: Name(InName)
		, Version(InVersion)
		, bOptional(bInOptional)
		, bBasePlugin(bInBasePlugin)
	{
	}
	
	static TSharedPtr<FModTemplateDependency> Load(const TSharedPtr<FJsonObject> JSON, FString& Error);
};

struct FModTemplateDescription
{
	TSharedRef<FPluginTemplateDescription> TemplateDescription;

	TArray<TSharedPtr<FModTemplateDependency>> Dependencies;

	FModTemplateDescription(TSharedRef<FPluginTemplateDescription> InTemplateDescription, const TArray<TSharedPtr<FModTemplateDependency>>& InDependencies)
		: TemplateDescription(InTemplateDescription)
		, Dependencies(InDependencies)
	{
	}
	
	static TSharedPtr<FModTemplateDescription> Load(const TSharedPtr<FJsonObject> JSON, const FString TemplatesPath, FString& Error);
};