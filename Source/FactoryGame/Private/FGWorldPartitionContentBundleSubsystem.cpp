// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGWorldPartitionContentBundleSubsystem.h"
#include "FGAssetManager.h"
#include "AssetRegistry/IAssetRegistry.h"

void UFGWorldPartitionContentBundleSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
	// Subscribe to the callbacks about asset state changes
	IAssetRegistry& assetRegistry = IAssetRegistry::GetChecked();
	assetRegistry.OnAssetAdded().AddUObject( this, &UFGWorldPartitionContentBundleSubsystem::OnAssetCreated );
	assetRegistry.OnAssetRemoved().AddUObject( this, &UFGWorldPartitionContentBundleSubsystem::OnAssetDeleted );

	// Discover existing content bundles
	DiscoverContentBundles();
}

void UFGWorldPartitionContentBundleSubsystem::RefreshBundleContentState( UFGWorldPartitionContentBundle* contentBundle )
{
	if ( const FFGWorldPartitionContentBundleRegistration* registration = mActiveContentBundles.Find( contentBundle ) )
	{
		const TSharedPtr<FContentBundleClient> contentBundleClient = registration->ContentBundleClient;
		fgcheck( contentBundleClient );
		const bool contentBundleRuntimeState = registration->RuntimeState;

		const bool isContentInjected = contentBundleClient->GetState() == EContentBundleClientState::ContentInjectionRequested;
		const bool shouldContentBeInjected = ShouldInjectContentBundle( contentBundle, contentBundleRuntimeState );

		if ( isContentInjected != shouldContentBeInjected )
		{
			if ( isContentInjected )
			{
				contentBundleClient->RequestRemoveContent();
			}
			else
			{
				contentBundleClient->RequestContentInjection();
			}
		}
	}
}

void UFGWorldPartitionContentBundleSubsystem::SetContentBundleEnabled( UFGWorldPartitionContentBundle* bundle, bool enabled )
{
	if ( FFGWorldPartitionContentBundleRegistration* registration = mActiveContentBundles.Find( bundle ) )
	{
		registration->RuntimeState = enabled;
		RefreshBundleContentState( bundle );
	}
}

bool UFGWorldPartitionContentBundleSubsystem::IsContentBundleEnabled( const UFGWorldPartitionContentBundle* bundle ) const
{
	if ( const FFGWorldPartitionContentBundleRegistration* registration = mActiveContentBundles.Find( bundle ) )
	{
		// Our content bundle is enabled if we have requested the content registration (even if there are no worlds in which it is currently active)
		if ( registration->ContentBundleClient.IsValid() )
		{
			return registration->ContentBundleClient->GetState() == EContentBundleClientState::ContentInjectionRequested;
		}
	}
	return false;
}

bool UFGWorldPartitionContentBundleSubsystem::ShouldInjectContentBundle( const UFGWorldPartitionContentBundle* contentBundle, bool runtimeState )
{
#if WITH_EDITOR
	// Check the build availability in the editor as we will always have all the assets since they are not cooked
	if ( contentBundle != nullptr )
	{
		const EIncludeInBuilds availability = contentBundle->GetBuildAvailability();

		// Do not include content that is never available even in the editor, it is functionally disabled
		if ( availability == EIncludeInBuilds::IIB_Never )
		{
			return false;
		}
	}
#endif
	// If we are currently running as the editor, disregard the runtime state to make sure content is always editable
	// In runtime, we inject content when the runtime state tells us to inject the content
	return GIsEditor || runtimeState;
}

bool UFGWorldPartitionContentBundleSubsystem::ShouldLoadContentBundle( const FAssetData& assetData )
{
#if WITH_EDITOR
	// We only want to exclude based on the availability if we are cooking the content to prevent the content associated with content bundle from being cooked
	if ( IsRunningCookCommandlet() )
	{
		if ( const UFGAssetManager* assetManager = Cast<UFGAssetManager>( &UAssetManager::Get() ) )
		{
			FString buildAvailabilityString;
			if ( assetData.GetTagValue( GET_MEMBER_NAME_CHECKED( UFGWorldPartitionContentBundle, mBuildAvailability ), buildAvailabilityString ) )
			{
				const EIncludeInBuilds minimumFlag = assetManager->GetMinimumIncludeInBuildFlag();
				const EIncludeInBuilds assetFlag = static_cast<EIncludeInBuilds>(StaticEnum<EIncludeInBuilds>()->GetValueByNameString( buildAvailabilityString ));

				// If the current minimum include in build level is higher than the level we are cooking with, do not try to load the asset content
				if ( assetFlag < minimumFlag )
				{
					return false;
				}
			}
		}
	}
#endif
	// In runtime, build availability does not matter as it has already been decided during the cooking
	return true;
}

void UFGWorldPartitionContentBundleSubsystem::DiscoverContentBundles()
{
	// Scan the asset registry
	const IAssetRegistry& assetRegistry = IAssetRegistry::GetChecked();

	const FTopLevelAssetPath classPath = UFGWorldPartitionContentBundle::StaticClass()->GetClassPathName();
	TArray<FAssetData> foundAssetData;

	if ( assetRegistry.GetAssetsByClass( classPath, foundAssetData ) )
	{
		for ( const FAssetData& assetData : foundAssetData )
		{
			if ( ShouldLoadContentBundle( assetData ) )
			{
				if ( UFGWorldPartitionContentBundle* contentBundle = Cast<UFGWorldPartitionContentBundle>( assetData.GetAsset() ) )
				{
					InitializeContentBundle( contentBundle );
				}
			}
		}
	}
}

void UFGWorldPartitionContentBundleSubsystem::OnAssetCreated( const FAssetData& newAssetData )
{
	const UClass* assetClass = newAssetData.GetClass();
	if ( assetClass != nullptr && assetClass->IsChildOf( UFGWorldPartitionContentBundle::StaticClass() ) )
	{
		if ( ShouldLoadContentBundle( newAssetData ) )
		{
			if ( UFGWorldPartitionContentBundle* contentBundle = Cast<UFGWorldPartitionContentBundle>( newAssetData.GetAsset() ) )
			{
				InitializeContentBundle( contentBundle );	
			}
		}
	}
}

void UFGWorldPartitionContentBundleSubsystem::OnAssetDeleted( const FAssetData& deletedAssetData )
{
	const UClass* assetClass = deletedAssetData.GetClass();
	if ( assetClass != nullptr && assetClass->IsChildOf( UFGWorldPartitionContentBundle::StaticClass() ) )
	{
		DestroyContentBundleByPath( TSoftObjectPtr<UFGWorldPartitionContentBundle>( deletedAssetData.GetSoftObjectPath() ) );
	}
}

void UFGWorldPartitionContentBundleSubsystem::DestroyContentBundleByPath( TSoftObjectPtr<UFGWorldPartitionContentBundle> contentBundlePath )
{
	FFGWorldPartitionContentBundleRegistration registration;
	if ( mActiveContentBundles.RemoveAndCopyValue( contentBundlePath, registration ) )
	{
		// Unregister the underlying content bundle client if it is valid
		if ( registration.ContentBundleClient.IsValid() )
		{
			registration.ContentBundleClient->RequestUnregister();
		}
	}
}

void UFGWorldPartitionContentBundleSubsystem::InitializeContentBundle( UFGWorldPartitionContentBundle* contentBundle )
{
	fgcheck( contentBundle );

	// Make sure to never double register existing content bundles
	if ( contentBundle != nullptr && !mActiveContentBundles.Contains( contentBundle ) )
	{
		fgcheck( contentBundle->GetContentBundleDescriptor() );
		const TSharedPtr<FContentBundleClient> newContentBundleClient = FContentBundleClient::CreateClient( contentBundle->GetContentBundleDescriptor(), TEXT("FGWorldPartitionContentBundleSubsystem") );

		if ( newContentBundleClient.IsValid() )
		{
			const FFGWorldPartitionContentBundleRegistration registration{ contentBundle, newContentBundleClient, contentBundle->mEnabledInRuntime };

			mActiveContentBundles.Add( contentBundle, registration );
			RefreshBundleContentState( contentBundle );

			// Subscribe to the content bundle availability flag change delegate
			contentBundle->mOnBuildAvailabilityChanged.AddUObject( this, &UFGWorldPartitionContentBundleSubsystem::OnContentBundleAvailabilityChanged, contentBundle );
			contentBundle->mOnBeginDestroy.AddUObject( this, &UFGWorldPartitionContentBundleSubsystem::DestroyContentBundleByPath, TSoftObjectPtr<UFGWorldPartitionContentBundle>( contentBundle ) );
		}
	}
}

void UFGWorldPartitionContentBundleSubsystem::OnContentBundleAvailabilityChanged( UFGWorldPartitionContentBundle* contentBundlePath )
{
	if ( contentBundlePath != nullptr && mActiveContentBundles.Contains( contentBundlePath ) )
	{
		RefreshBundleContentState( contentBundlePath );
	}
}
