#pragma once

#include "CoreMinimal.h"
#include "GameFeaturePluginTemplate.h"

struct FGameFeatureModTemplateDescription : FGameFeaturePluginTemplateDescription
{
	FGameFeatureModTemplateDescription( const FText& InName, const FText& InDescription, const FString& InOnDiskPath,
		const FString& InDefaultSubfolder, const FString& InDefaultPluginName,
		const TSubclassOf<UGameFeatureData>& GameFeatureDataClassOverride, const FString& GameFeatureDataNameOverride,
		EPluginEnabledByDefault InEnabledByDefault ) :
		FGameFeaturePluginTemplateDescription(
			InName, InDescription, InOnDiskPath, InDefaultSubfolder, InDefaultPluginName, GameFeatureDataClassOverride,
			GameFeatureDataNameOverride, InEnabledByDefault )
	{
	}

	// Begin FGameFeaturePluginTemplateDescription interface
	virtual void UpdatePathWhenTemplateSelected(FString& InOutPath) override;
	virtual void UpdatePathWhenTemplateUnselected(FString& InOutPath) override;
	virtual void CustomizeDescriptorBeforeCreation(FPluginDescriptor& Descriptor) override;
	virtual void OnPluginCreated(TSharedPtr<IPlugin> NewPlugin) override;
	// End FGameFeaturePluginTemplateDescription interface
};