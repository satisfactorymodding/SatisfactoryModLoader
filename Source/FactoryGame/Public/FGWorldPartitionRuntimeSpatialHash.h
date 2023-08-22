// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorldPartition/WorldPartitionRuntimeSpatialHash.h"
#include "FGWorldPartitionRuntimeSpatialHash.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGWorldPartitionRuntimeSpatialHash : public UWorldPartitionRuntimeSpatialHash
{
	GENERATED_BODY()
#if WITH_EDITOR
public:
	uint32 GetGridCellSize(FName GridName);
protected:
	/**
	 * Called once on cook before @PopulateGeneratedPackageForCook gets called for every generated level (WP Cell). In this context, we use it to
	 * gather WP runtime data that we need to later perform validation against
	 */ 
	virtual bool PopulateGeneratorPackageForCook(const TArray<FWorldPartitionCookPackage*>& PackagesToCook, TArray<UPackage*>& OutModifiedPackage) override;
#endif
};
