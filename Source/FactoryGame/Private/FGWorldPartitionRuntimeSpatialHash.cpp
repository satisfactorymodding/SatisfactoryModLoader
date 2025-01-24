// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FGWorldPartitionRuntimeSpatialHash.h"
#include "FGWorldSettings.h"
#include "FactoryGame.h"
#include "WorldPartition/Cook/WorldPartitionCookPackage.h"
#include "WorldPartition/RuntimeSpatialHash/RuntimeSpatialHashGridHelper.h"

#if WITH_EDITOR
uint32 UFGWorldPartitionRuntimeSpatialHash::GetGridCellSize( FName GridName )
{
	uint32 CellSize = 0;
	ForEachStreamingGridBreakable( [&CellSize, GridName](const FSpatialHashStreamingGrid& Grid)
	{
		if(Grid.GridName == GridName)
		{
			CellSize = Grid.CellSize;
			return false;
		}
		return true;
	} );
	return CellSize;
}

bool UFGWorldPartitionRuntimeSpatialHash::PopulateGeneratorPackageForCook( const TArray<FWorldPartitionCookPackage*>& PackagesToCook,
                                                                           TArray<UPackage*>& OutModifiedPackage )
{
	const auto Result = Super::PopulateGeneratorPackageForCook( PackagesToCook, OutModifiedPackage );
	if(const auto* Level = GetWorld()->PersistentLevel.Get(); Level)
	{
		const auto* MainWorld = GetWorld();
		AFGWorldSettings* MainWorldSettings = Cast<AFGWorldSettings>(MainWorld->GetWorldSettings());
		FWPSaveDataMigrationContext::CollectSaveGameValidationDataForPersistentLevel( *Level, *MainWorldSettings );
		ForEachStreamingGrid( [MainWorldSettings](const FSpatialHashStreamingGrid& grid)
		{
			grid.ForEachRuntimeCell( [MainWorldSettings, &grid](const UWorldPartitionRuntimeCell* Cell)-> bool
			{
				FWPSaveDataMigrationContext::CollectSaveGameValidationData(grid, *Cast<const UWorldPartitionRuntimeLevelStreamingCell>(Cell), *MainWorldSettings);
				return true;
			} );
		} );
		
	}

	return Result;
}

#endif
bool UFGWorldPartitionRuntimeSpatialHash::InjectExternalStreamingObject( URuntimeHashExternalStreamingObjectBase* ExternalStreamingObject )
{
	if ( Super::InjectExternalStreamingObject( ExternalStreamingObject ) )
	{
		mNameToCellMapDirty = true;
		return true;
	}
	return false;
}

bool UFGWorldPartitionRuntimeSpatialHash::RemoveExternalStreamingObject( URuntimeHashExternalStreamingObjectBase* ExternalStreamingObject )
{
	if ( Super::RemoveExternalStreamingObject(ExternalStreamingObject) )
	{
		mNameToCellMapDirty = true;
		return true;
	}
	return false;
}

UWorldPartitionRuntimeCell* UFGWorldPartitionRuntimeSpatialHash::FindCellByName( FName cellName ) const
{
	if ( mNameToCellMapDirty )
	{
		RebuildNameToCellMap();
		mNameToCellMapDirty = false;
	}
	UWorldPartitionRuntimeCell* const* cellMapEntry = mNameToCellMap.Find( cellName );
	return cellMapEntry ? *cellMapEntry : nullptr;
}

bool UFGWorldPartitionRuntimeSpatialHash::IsCellContainingWorldLocationLoaded( const FName& GridName, const FVector& Location ) const
{
	bool foundLoadedCell = false;

	ForEachStreamingGridBreakable( [ GridName, Location, &foundLoadedCell ]( const FSpatialHashStreamingGrid& grid )-> bool
	{
		if( grid.GridName == GridName )
		{
			FVector2D Location2D = FVector2D( Location );
			const FSquare2DGridHelper& gridHelper = grid.GetGridHelper();

			//Since we know input location, we can simply calculate the cell coordinates for each grid level.
			//Other FSpatialHashStreamingGrid methods use FULL walkthrough against all cells to find the cell containing the location/radius
			for( int32 GridLevel = 0; GridLevel < gridHelper.Levels.Num(); ++GridLevel )
			{
				FGridCellCoord2 CellCoords;
				if( gridHelper.Levels[ GridLevel ].GetCellCoords( Location2D, CellCoords ) )
				{
					FGridCellCoord Coords( CellCoords.X, CellCoords.Y, GridLevel );

					check( grid.GridLevels.IsValidIndex(Coords.Z) );

					const int64 CoordKey = Coords.Y * gridHelper.Levels[ Coords.Z ].GridSize + Coords.X;

					if( const int32* LayerCellIndexPtr = grid.GridLevels[ Coords.Z ].LayerCellsMapping.Find( CoordKey ) )
					{
						const auto& runtimeCells = grid.GridLevels[ Coords.Z ].LayerCells[ *LayerCellIndexPtr ].GridCells;
						for( const UWorldPartitionRuntimeCell* OutCell: runtimeCells )
						{
							// Check if the X and Y components of the location are within the cell bounds
							if( OutCell->GetStreamingStatus() == EStreamingStatus::LEVEL_Visible )
							{
								foundLoadedCell = true;
								return false;
							}
						}
					}
				}
			}

			//okay, we didn't find it among the regular cells, now lets check always loaded and injected ones.
			//We don't have direct access to them, so just use standard api without spatial query
			FWorldPartitionStreamingQuerySource LocationQuery{ Location };
			LocationQuery.bSpatialQuery = false;
			TSet< const UWorldPartitionRuntimeCell* > OutCells;
			grid.GetCells( LocationQuery, OutCells, false );
			for( const UWorldPartitionRuntimeCell* OutCell: OutCells )
			{
				const FBox CellBounds = OutCell->GetCellBounds();
				// Check if the X and Y components of the location are within the cell bounds
				if( Location.X >= CellBounds.Min.X && Location.X <= CellBounds.Max.X )
				{
					if( Location.Y >= CellBounds.Min.Y && Location.Y <= CellBounds.Max.Y )
					{
						if( OutCell->GetStreamingStatus() == EStreamingStatus::LEVEL_Visible )
						{
							foundLoadedCell = true;
							return false;
						}
					}
				}
			}

			return false;
		}

		return true;
	} );

	return foundLoadedCell;
}

void UFGWorldPartitionRuntimeSpatialHash::RebuildNameToCellMap() const
{
	mNameToCellMap.Empty();
	
	// We cannot use ForEachStreamingCells because it will not consider cells that are "not relevant" according to the client-only visibility
	ForEachStreamingGrid([&]( const FSpatialHashStreamingGrid& streamingGrid )
	{
		for ( const FSpatialHashStreamingGridLevel& gridLevel : streamingGrid.GridLevels )
		{
			for ( const FSpatialHashStreamingGridLayerCell& layerCell : gridLevel.LayerCells )
			{
				for ( UWorldPartitionRuntimeCell* cell : layerCell.GridCells )
				{
					// Make sure cells do not have duplicate names. In theory they can be for cells that come from external objects (e.g. have different outers),
					// but that shouldn't really be the case as external object cells will have their Content Bundle ID encoded in their name
					if ( UWorldPartitionRuntimeCell* const* oldCell = mNameToCellMap.Find( cell->GetFName() ) )
					{
						fgcheckf( false, TEXT("World Partition Cells with Duplicate Names found: '%s' and '%s'"), *GetFullNameSafe( cell ), *GetFullNameSafe( *oldCell ) );
					}
					mNameToCellMap.Add( cell->GetFName(), cell );
				}
			}
		}
	});
	UE_LOG( LogGame, Log, TEXT("Built World Partition cell cache for World '%s', %d cells in cache."), *GetPathNameSafe( GetWorld() ), mNameToCellMap.Num() );
}
