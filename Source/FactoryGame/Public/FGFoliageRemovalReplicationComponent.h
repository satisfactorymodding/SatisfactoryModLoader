// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "FGFoliageTypes.h"
#include "GameFramework/Actor.h"

#include "FGFoliageRemovalReplicationComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnNewFoliageRemovalReplicated, uint32);
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogFoliageReplication, Verbose, Verbose );

DECLARE_DELEGATE_TwoParams(FOnPostReplicatedAddFoliage, const TArrayView<int32>& AddedIndices, int32 FinalSize);

USTRUCT()
struct FFoliageReplicationBundle
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString FoliageTypePath;

	UPROPERTY()
	TArray<FVector> RemovedLocations;

	UPROPERTY()
	FIntVector FoliageCell;
};

FArchive& operator<<(FArchive& Ar, FFoliageReplicationBundle& Bundle);

UCLASS(Within=FGPlayerController)
class FACTORYGAME_API UFGFoliageRemovalReplicationComponent: public UActorComponent
{
	GENERATED_BODY()
protected:
	UFGFoliageRemovalReplicationComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnFoliageBucketRemoved(const FIntVector& inCell, const UFoliageType* forFoliageType, int32 bucketId );

	void HandleBulkDataReplicationMessage( TArray<uint8>&& Payload );
	
	/**
	 * Only relevant on the server. All the removal buckets that have been created but for which replication hasn't begun yet
	 */
	TPerCellPerTypeMap< int32 > mFirstUnreplicatedBucketInfos;
	
	/* Replication radius, reflects "very far" foliage loading distance setting.*/
	UPROPERTY(EditDefaultsOnly)
	float mReplicationRadius = 102400.f; 
};


UCLASS( Hidden )
class UE_DEPRECATED(
	5.3, "This class is not used any more and is only kept around because there are a bunch of levels that have instances of it within." )
	FACTORYGAME_API AFGFoliageStateRepProxy : public AActor
{
	GENERATED_BODY()
public:
	AFGFoliageStateRepProxy();
};