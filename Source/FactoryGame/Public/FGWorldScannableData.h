// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGWorldScannableData.generated.h"

USTRUCT()
struct FWorldScannableData
{
	GENERATED_BODY()

	FWorldScannableData() = default;
#if WITH_EDITOR
	explicit FWorldScannableData( const AActor* actor );
	FWorldScannableData( const class FWorldPartitionActorDesc* ActorDesc, int32 PIEInstanceIndex = INDEX_NONE );
#endif

	UPROPERTY( VisibleAnywhere )
	TSoftObjectPtr<AActor> Actor;

	UPROPERTY( VisibleAnywhere )
	FGuid ActorGuid{};

	UPROPERTY( VisibleAnywhere )
	TSubclassOf<AActor> ActorClass;

	UPROPERTY( VisibleAnywhere )
	FVector ActorLocation{ForceInit};
	
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

	/** Item pickups that were found in the world */
	UPROPERTY()
	TArray<FWorldScannableData> mItemPickups;

	/** Drop pods that were found in the world */
	UPROPERTY()
	TArray<FWorldScannableData> mDropPods;
};
