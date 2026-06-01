#include "GameFeatureModTemplateDescription.h"
#include "AssetToolsModule.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "GameFeaturesSubsystem.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Engine/AssetManagerTypes.h"
#include "HAL/FileManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FeedbackContext.h"
#include "Misc/Paths.h"
#include "Subsystems/AssetEditorSubsystem.h"

void FGameFeatureModTemplateDescription::UpdatePathWhenTemplateSelected(FString& InOutPath)
{
	FString ResultPluginRoot = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*(FPaths::ProjectModsDir() / TEXT("GameFeatures/")));
	if (!DefaultSubfolder.IsEmpty())
	{
		ResultPluginRoot /= DefaultSubfolder + TEXT("/");
	}
	FPaths::MakePlatformFilename(ResultPluginRoot);
	InOutPath = ResultPluginRoot;
}

void FGameFeatureModTemplateDescription::UpdatePathWhenTemplateUnselected(FString& InOutPath)
{
	InOutPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(*FPaths::ProjectModsDir());
	FPaths::MakePlatformFilename(InOutPath);
}

void FGameFeatureModTemplateDescription::CustomizeDescriptorBeforeCreation(FPluginDescriptor& Descriptor)
{
	FGameFeaturePluginTemplateDescription::CustomizeDescriptorBeforeCreation(Descriptor);
	Descriptor.bExplicitlyLoaded = false;
}

void FGameFeatureModTemplateDescription::OnPluginCreated(const TSharedPtr<IPlugin> NewPlugin)
{
	// Create a new game feature data asset
	const FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	const FString AssetName = !GameFeatureDataName.IsEmpty() ? GameFeatureDataName : NewPlugin->GetName();
	UGameFeatureData* GameFeatureDataAsset = Cast<UGameFeatureData>(AssetToolsModule.Get().CreateAsset(AssetName, NewPlugin->GetMountedAssetPath(), GameFeatureDataClass, nullptr));

	if (GameFeatureDataAsset != nullptr)
	{
		// Populate asset manager primary asset data for it from the template
		TArray<FString> PrimaryAssetTypeTemplates;
		GConfig->GetArray(TEXT("GameFeatureModTemplateDescription"), TEXT("PrimaryAssetTypeTemplates"), PrimaryAssetTypeTemplates, GConfig->GetConfigFilename(TEXT("Alpakit")));
		for (const FString& PrimaryAssetTypeTemplate : PrimaryAssetTypeTemplates)
		{
			const FString PrimaryAssetTypeString = PrimaryAssetTypeTemplate.Replace(TEXT("$PluginName"), *NewPlugin->GetName());
			FPrimaryAssetTypeInfo PrimaryAssetTypeInfo;
			UScriptStruct* ScriptStruct = FindObjectChecked<UScriptStruct>(nullptr, TEXT("/Script/Engine.PrimaryAssetTypeInfo"));
			ScriptStruct->ImportText(*PrimaryAssetTypeString, &PrimaryAssetTypeInfo, nullptr, PPF_None, GWarn, TEXT("PrimaryAssetTypeInfo"));
			GameFeatureDataAsset->GetPrimaryAssetTypesToScan().Add(PrimaryAssetTypeInfo);
			GameFeatureDataAsset->MarkPackageDirty();
		}

		// Save the asset now before we attempt to activate the game feature plugin
		UEditorLoadingAndSavingUtils::SavePackages({GameFeatureDataAsset->GetPackage()}, false);

		// Activate the new game feature plugin
		auto AdditionalFilter = [](const FString&, const FGameFeaturePluginDetails&, FBuiltInGameFeaturePluginBehaviorOptions&) -> bool { return true; };
		UGameFeaturesSubsystem::Get().LoadBuiltInGameFeaturePlugin(NewPlugin.ToSharedRef(), AdditionalFilter, FGameFeaturePluginLoadComplete::CreateLambda([GameFeatureDataAsset](const UE::GameFeatures::FResult&)
		{
			// Edit the new game feature data
			if (GameFeatureDataAsset != nullptr)
			{
				GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(GameFeatureDataAsset);
			}
		}));
	}
}
