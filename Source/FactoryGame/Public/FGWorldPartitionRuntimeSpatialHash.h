// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorldPartition/WorldPartitionRuntimeLevelStreamingCell.h"
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

	/** We override these to dispatch a delegate when they are changed */
	virtual bool InjectExternalStreamingObject(URuntimeHashExternalStreamingObjectBase* ExternalStreamingObject) override;
	virtual bool RemoveExternalStreamingObject(URuntimeHashExternalStreamingObjectBase* ExternalStreamingObject) override;

public:
	/** Finds the cell by it's name using a fast lookup map */
	UWorldPartitionRuntimeCell* FindCellByName( FName cellName ) const;
	
	bool IsCellContainingWorldLocationLoaded( const FName& GridName, const FVector& Location ) const;
	
private:
	/** Rebuilds the mapping of cell names to their objects */
	void RebuildNameToCellMap() const;
	
	/** Maps cell names to */
	UPROPERTY( Transient )
	mutable TMap<FName, UWorldPartitionRuntimeCell*> mNameToCellMap;
	
	/** True if the cell to name map has not been rebuilt yet */
	mutable bool mNameToCellMapDirty = true;
};
