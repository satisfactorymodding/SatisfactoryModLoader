// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IncludeInBuild.h"
#include "Engine/DataAsset.h"
#include "FGWorldPartitionContentBundle.generated.h"

class FContentBundleClient;
class UContentBundleDescriptor;

UCLASS( NotBlueprintable )
class FACTORYGAME_API UFGWorldPartitionContentBundle : public UDataAsset
{
	GENERATED_BODY()
public:
	UFGWorldPartitionContentBundle(); 

#if WITH_EDITOR
	/** Called to notify that the build availability has changed */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	/** Called to notify the world partition system that we are no longer available and give the last chance to un-register */
	virtual void BeginDestroy() override;
	
	FORCEINLINE UContentBundleDescriptor* GetContentBundleDescriptor() const { return mContentBundleDescriptor; }
	FORCEINLINE EIncludeInBuilds GetBuildAvailability() const { return mBuildAvailability; }
	FORCEINLINE FSimpleMulticastDelegate& OnBuildAvailabilityChanged() { return mOnBuildAvailabilityChanged; }
	FORCEINLINE FSimpleMulticastDelegate& OnBeginDestroy() { return mOnBeginDestroy; }
protected:
	friend class UFGWorldPartitionContentBundleSubsystem;

	/** Descriptor for the content bundle, holds the GUID of the bundle */
	UPROPERTY( VisibleAnywhere, Category = "Content Bundle", meta=( EditInline ) )
	UContentBundleDescriptor* mContentBundleDescriptor;

	/** Specifies in which builds this content bundle will be available */
	UPROPERTY( EditAnywhere, AssetRegistrySearchable, Category = "Content Bundle" )
	EIncludeInBuilds mBuildAvailability;

	/** Initial state of this content bundle in runtime. It can be toggled using FGWorldPartitionContentBundleSubsystem functions */
	UPROPERTY( EditAnywhere, Category = "Content Bundle" )
	bool mEnabledInRuntime;

	/** Called when the availability of this content bundle changes. Only called in the Editor. */
	FSimpleMulticastDelegate mOnBuildAvailabilityChanged;
	FSimpleMulticastDelegate mOnBeginDestroy;
};