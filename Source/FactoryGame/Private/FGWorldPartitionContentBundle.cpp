// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGWorldPartitionContentBundle.h"
#include "WorldPartition/ContentBundle/ContentBundleDescriptor.h"

UFGWorldPartitionContentBundle::UFGWorldPartitionContentBundle() : mBuildAvailability( EIncludeInBuilds::IIB_PublicBuilds ), mEnabledInRuntime( true )
{
	mContentBundleDescriptor = CreateDefaultSubobject<UContentBundleDescriptor>( TEXT("ContentBundleDescriptor") );

#if WITH_EDITOR
	const FName packageMountPoint = FPackageName::GetPackageMountPoint(GetPackage()->GetName());

	mContentBundleDescriptor->InitializeObject(FPackageName::GetShortName(GetPackage()), packageMountPoint.ToString());
#endif
}

#if WITH_EDITOR

void UFGWorldPartitionContentBundle::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if ( PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED( ThisClass, mBuildAvailability ) )
	{
		mOnBuildAvailabilityChanged.Broadcast();
	}
}

#endif
void UFGWorldPartitionContentBundle::BeginDestroy()
{
	// Before we call Super::BeginDestroy we still retain our outer and name, which SoftObjectPath relies on.
	mOnBeginDestroy.Broadcast();
	
	Super::BeginDestroy();
}
