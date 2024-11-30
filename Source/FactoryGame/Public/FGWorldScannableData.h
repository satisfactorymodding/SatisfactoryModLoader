// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGWorldScannableData.generated.h"

class AFGCreature;
class AFGCreatureSpawner;

USTRUCT()
struct FWorldScannableData
{
	GENERATED_BODY()

	FWorldScannableData() = default;
#if WITH_EDITOR
	explicit FWorldScannableData( const AActor* actor );
	explicit FWorldScannableData( const class FWorldPartitionActorDesc* ActorDesc, int32 PIEInstanceIndex = INDEX_NONE );
#endif

	UPROPERTY( VisibleAnywhere, Category = "Scannable Data" )
	TSoftObjectPtr<AActor> Actor;

	UPROPERTY( VisibleAnywhere, Category = "Scannable Data" )
	FGuid ActorGuid{};

	UPROPERTY( VisibleAnywhere, Category = "Scannable Data" )
	TSubclassOf<AActor> ActorClass;

	UPROPERTY( VisibleAnywhere, Category = "Scannable Data" )
	FVector ActorLocation{ForceInit};
};

USTRUCT()
struct FCreatureSpawnerWorldScannableData : public FWorldScannableData
{
	GENERATED_BODY()

	FCreatureSpawnerWorldScannableData() = default;
#if WITH_EDITOR
	explicit FCreatureSpawnerWorldScannableData( const AFGCreatureSpawner* actor );
	explicit FCreatureSpawnerWorldScannableData( const class FWorldPartitionActorDesc* ActorDesc, int32 PIEInstanceIndex = INDEX_NONE );
#endif

	/** Class of the creature that is spawned by this spawner */
	UPROPERTY( VisibleAnywhere, Category = "Scannable Data" )
	TSoftClassPtr<AFGCreature> CreatureClass;
};

UCLASS()
class FACTORYGAME_API AFGWorldScannableDataGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGWorldScannableDataGenerator();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	// End AActor interface
private:
#if WITH_EDITOR
	void CacheWorldScannableData();
#endif
public:
	/** Item pickups that were found in the world */
	UPROPERTY()
	TArray<FWorldScannableData> mItemPickups;

	/** Drop pods that were found in the world */
	UPROPERTY()
	TArray<FWorldScannableData> mDropPods;

	/** Creature spawners that were found in the world */
	UPROPERTY()
	TArray<FCreatureSpawnerWorldScannableData> mCreatureSpawners;
};
