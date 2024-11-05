// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGWorldPartitionContentBundle.h"
#include "Subsystems/EngineSubsystem.h"
#include "WorldPartition/ContentBundle/ContentBundleClient.h"
#include "FGWorldPartitionContentBundleSubsystem.generated.h"

class UFGWorldPartitionContentBundle;

USTRUCT()
struct FFGWorldPartitionContentBundleRegistration
{
	GENERATED_BODY()

	/** Needed to keep the content bundle in memory as World Partition relies on clients doing that themselves for whatever reason */
	UPROPERTY()
	UFGWorldPartitionContentBundle* LoadedContentBundle{};
	
	TSharedPtr<FContentBundleClient> ContentBundleClient{};
	bool RuntimeState{false};
};

/** Manages lifetime of World Partition Content Bundles and their states*/
UCLASS( BlueprintType )
class FACTORYGAME_API UFGWorldPartitionContentBundleSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Updates the status of the content bundle in Runtime. Does not do anything in Editor builds. */
	UFUNCTION( BlueprintCallable, Category = "World Partition Content Bundle" )
	void SetContentBundleEnabled( UFGWorldPartitionContentBundle* bundle, bool enabled );

	/** Returns true if the given bundle is currently enabled (and available) */
	UFUNCTION( BlueprintPure, Category = "World Partition Content Bundle" )
	bool IsContentBundleEnabled( const UFGWorldPartitionContentBundle* bundle ) const;

private:
	void OnAssetCreated( const FAssetData& newAssetData );
	void OnAssetDeleted( const FAssetData& deletedAssetData );

	/** Returns true if the bundle in question is eligible to get loaded in current configuration */
	static bool ShouldLoadContentBundle( const FAssetData& assetData );
	static bool ShouldInjectContentBundle( const UFGWorldPartitionContentBundle* contentBundlePath, bool runtimeState );
protected:
	void DiscoverContentBundles();
	void InitializeContentBundle( UFGWorldPartitionContentBundle* contentBundle );
	void DestroyContentBundleByPath( TSoftObjectPtr<UFGWorldPartitionContentBundle> contentBundlePath );
	void OnContentBundleAvailabilityChanged( UFGWorldPartitionContentBundle* contentBundlePath );

	void RefreshBundleContentState( UFGWorldPartitionContentBundle* contentBundlePath );
protected:
	UPROPERTY()
	TMap< TSoftObjectPtr<UFGWorldPartitionContentBundle>, FFGWorldPartitionContentBundleRegistration > mActiveContentBundles;
};
