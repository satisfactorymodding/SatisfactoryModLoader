// Copyright Coffee Stain Studios. All Rights Reserved.

#include "FWPSaveDataMigrationContext.h"
#include "FGArchives64.h"
#include "FGCoreSaveTypes.h"
#include "FGObjectReference.h"
#include "FGSaveInterface.h"
#include "FGSaveSession.h"
#include "FGWorldPartitionRuntimeSpatialHash.h"
#include "FGWorldSettings.h"
#include "FactoryGame.h"
#include "WorldPartition/WorldPartition.h"
#include "WorldPartition/WorldPartitionActorDesc.h"
#include "WorldPartition/WorldPartitionRuntimeCell.h"
#include "WorldPartition/WorldPartitionRuntimeLevelStreamingCell.h"
#include "WorldPartition/WorldPartitionRuntimeSpatialHash.h"

static TAutoConsoleVariable CVarForceFullWPMigration(
	TEXT("FG.WorldPartitionMigration.ForceFullMigration"),
	false,
	TEXT("Whenever to force a full World Partition Migration for the save game data, even if no World Partition has changed"),
	ECVF_Default
);

#if WITH_EDITOR
void FWPSaveDataMigrationContext::CollectSaveGameValidationData( const FSpatialHashStreamingGrid& Grid, const UWorldPartitionRuntimeLevelStreamingCell& Cell, AFGWorldSettings& WorldSettings )
{
	uint32 CellHash = 0;
	// We will need a handle to the world partition instance
	UWorldPartition* ActorDescContainer ;
	if(!WorldSettings.GetWorldPartition()->IsEmpty() )
	{
		ActorDescContainer = WorldSettings.GetWorldPartition();
	}
	else
	{
		const auto *EditorWorld = GEditor->GetEditorWorldContext().World();
		ActorDescContainer = EditorWorld->GetWorldPartition();
	}
	// If this is the first time we are encountering this grid, write down the cell size.
	auto* pGridValidationData = WorldSettings.SaveGameValidationData.Grids.Find(Grid.GridName);
	if( !pGridValidationData )
	{
		pGridValidationData = &WorldSettings.SaveGameValidationData.Grids.Add( Grid.GridName );
		pGridValidationData->CellSize = CastChecked<UFGWorldPartitionRuntimeSpatialHash>(ActorDescContainer->RuntimeHash)->GetGridCellSize( Grid.GridName );
	}
	auto &GridValidationData = *pGridValidationData;

	// Ultimately go through all the packages and write them down in the cell mapping
	for(const FWorldPartitionRuntimeCellObjectMapping& Package: Cell.GetPackages())
	{
		const FSoftObjectPath ObjectPath( Package.Path.ToString() );
		if(const FWorldPartitionActorDesc* ActorDesc = ActorDescContainer->GetActorDesc( Package.ActorInstanceGuid ); ensure(ActorDesc))
		{
			// Only keep track of save game actors to reduce the likelihood of having to rebuild save data
			const auto ActorClassPath = ActorDesc->GetBaseClass();
			const auto ActorNativeClassPath = ActorDesc->GetNativeClass();
			const auto* ActorClass = FindObject<UClass>( ActorClassPath );
			const auto* ActorNativeClass = FindObject<UClass>( ActorNativeClassPath );
			if(ensure(ActorClass || ActorNativeClass))
			{
				if( (ActorNativeClass && ActorNativeClass->ImplementsInterface( UFGSaveInterface::StaticClass() )) || 
					(ActorClass && ActorClass->ImplementsInterface( UFGSaveInterface::StaticClass() )))
				{
					CellHash = HashCombine( CellHash, GetTypeHash( ObjectPath.GetSubPathString() ) );
					WorldSettings.WPActorCellMapping.Add( ObjectPath.GetSubPathString() ) = { Grid.GridName, Cell.GetFName() };
				}
			}
		}
	}
	 
	if( CellHash != 0 )
	{
		GridValidationData.CellHashes.Add( Cell.GetFName(), CellHash );
		GridValidationData.GridHash = HashCombine( GridValidationData.GridHash, CellHash );
	}
}

void FWPSaveDataMigrationContext::CollectSaveGameValidationDataForPersistentLevel( const ULevel& Level, AFGWorldSettings& WorldSettings )
{
	uint32 CellHash = 0;
	auto &GridValidationData = WorldSettings.SaveGameValidationData.Grids.FindOrAdd(NAME_None);

	for(const auto Actor: Level.Actors)
	{
		// TODO we can get null actors for some reason, but they definitely dont  implement the save interface :D
		if( Actor && Actor->Implements<UFGSaveInterface>())
		{
			const FSoftObjectPath ObjectPath(Actor);
			CellHash = HashCombine( CellHash, GetTypeHash( ObjectPath.GetSubPathString() ) );
			WorldSettings.WPActorCellMapping.Add( ObjectPath.GetSubPathString() ) = { NAME_None, NAME_None };
		}
	}
	if( CellHash != 0 )
	{
		GridValidationData.CellHashes.Add( NAME_None, CellHash );
		GridValidationData.GridHash = HashCombine( GridValidationData.GridHash, CellHash );
	}
}

#endif

FWPSaveDataMigrationContext::~FWPSaveDataMigrationContext() = default;

FWPSaveDataMigrationContext::FWPSaveDataMigrationContext( const AFGWorldSettings &InWorldSettings, const struct FSaveHeader& InSaveHeader )
	: WorldSettings( InWorldSettings )
	, SaveHeader( InSaveHeader )
{}

void FWPSaveDataMigrationContext::MigrateBlobs( const TArray<uint8>& TOCBlob, const TArray<uint8>& DataBlob,
	const bool DataIsFromPersistentLevel )
{
	FUnpackedSaveData UnpackedData;

	if( SaveHeader.SaveVersion < FSaveCustomVersion::SwitchTo64BitSaveArchive )
	{
		
		FMemoryReader memArchiveTOC(TOCBlob, true);
		FMemoryReader memArchiveData(DataBlob, true);

		memArchiveTOC.SetIsLoading( true );
		memArchiveData.SetIsLoading( true );
				
		memArchiveTOC.SetCustomVersion( FSaveCustomVersion::GUID, SaveHeader.SaveVersion, SaveSystemConstants::CustomVersionFriendlyName );
		memArchiveData.SetCustomVersion( FSaveCustomVersion::GUID, SaveHeader.SaveVersion, SaveSystemConstants::CustomVersionFriendlyName );

		memArchiveTOC << UnpackedData.Headers;
		UnpackedData.SaveData.Reserve( UnpackedData.Headers.Num() );
		memArchiveData << UnpackedData.SaveData;

		fgcheck( UnpackedData.Headers.Num() == UnpackedData.SaveData.Num() );
		MigrateUnpackedData( UnpackedData, DataIsFromPersistentLevel );	
	}
}

void FWPSaveDataMigrationContext::MigrateBlobs( const TArray<uint8, TSizedDefaultAllocator<64>>& TOCBlob, const TArray<uint8, TSizedDefaultAllocator<64>>& DataBlob, const bool DataIsFromPersistentLevel )
{
	FUnpackedSaveData UnpackedData;
	
	FFGMemoryReader64 memArchiveTOC(TOCBlob, true);
	FFGMemoryReader64 memArchiveData(DataBlob, true);

	memArchiveTOC.SetIsLoading( true );
	memArchiveData.SetIsLoading( true );
			
	memArchiveTOC.SetCustomVersion( FSaveCustomVersion::GUID, SaveHeader.SaveVersion, SaveSystemConstants::CustomVersionFriendlyName );
	memArchiveData.SetCustomVersion( FSaveCustomVersion::GUID, SaveHeader.SaveVersion, SaveSystemConstants::CustomVersionFriendlyName );

	memArchiveTOC << UnpackedData.Headers;
	UnpackedData.SaveData.Reserve( UnpackedData.Headers.Num() );
	memArchiveData << UnpackedData.SaveData;

	fgcheck( UnpackedData.Headers.Num() == UnpackedData.SaveData.Num() );
	MigrateUnpackedData( UnpackedData, DataIsFromPersistentLevel );
}

void FWPSaveDataMigrationContext::MigrateDestroyedActors( const TArray<FObjectReferenceDisc>& DestroyedActors )
{
	for( const FObjectReferenceDisc& originalObjRef: DestroyedActors )
	{
		// WPActorCellMapping contains actor names in the form of PersistentLevel.ActorName
		// So to match the format used by it, we need to prefix the actor name with a PersistentLevel
		FString ActorSubPathString;
		ActorSubPathString.Append(TEXT("PersistentLevel."));
		ActorSubPathString.Append(originalObjRef.GetTopLevelActorName());
		
		if( auto* WpCellInfo = WorldSettings.WPActorCellMapping.Find( ActorSubPathString ); WpCellInfo )
		{
			auto& MigratedData = PerLevelUnpackedSaveData.FindOrAdd( WpCellInfo->CellName );
			MigratedData.DestroyedActors.Add( UFGSaveSession::FixupObjectReferenceForPartitionedWorld( originalObjRef, WorldSettings ) );
			// The cell that we moved the actor into is a part of invalidated cells now
			InvalidatedCells.Add( WpCellInfo->CellName );
		}
		else
		{
			// This object reference does not match any in the new world.
			UE_LOG(LogSave, Log, TEXT("Actor %s was removed from world in save file but does not exist in the world currently"), *originalObjRef.ToString());
		}
	}

}

void FWPSaveDataMigrationContext::MigrateUnpackedData( FUnpackedSaveData& UnpackedSaveData, const bool DataIsFromPersistentLevel )
{
	for( auto& ObjSaveData: UnpackedSaveData.SaveData )
	{
		ObjSaveData.ShouldMigrateObjectRefsToPersistent = true;
		ObjSaveData.SaveVersion = SaveHeader.SaveVersion;
	}
	
	for( int32 Ix = 0; Ix < UnpackedSaveData.Headers.Num(); ++Ix )
	{
		auto& ObjectSaveHeader = UnpackedSaveData.Headers[Ix];
		
		const UClass* Class = ObjectSaveHeader.ResolveClass();
		if( !Class )
		{
			// we cannot resolve the class of this object so we'll dismiss it.
			UE_LOG( LogSave, Log, TEXT("Cannot resolve class name '%s'"), *ObjectSaveHeader.GetBaseHeader().ClassName);
			continue;
		}
		if ( !DataIsFromPersistentLevel && Class->IsChildOf( AFGWorldSettings::StaticClass() ) )
		{
			// There's just no sane way of maintaining both backward and forward compatibility for these so just throw them out.
			continue;
		}

		if( !ObjectSaveHeader.IsActor() )
		{
			FObjectReferenceDisc outerRef;
			outerRef.LevelName = ObjectSaveHeader.GetBaseHeader().Reference.LevelName;
			outerRef.PathName = ObjectSaveHeader.GetObjectHeader().OuterPathName;
			ObjectSaveHeader.GetObjectHeader().OuterPathName = UFGSaveSession::FixupObjectReferenceForPartitionedWorld( outerRef, WorldSettings ).PathName; 
		}
		ObjectSaveHeader.GetBaseHeader().Reference = UFGSaveSession::FixupObjectReferenceForPartitionedWorld( ObjectSaveHeader.GetBaseHeader().Reference, WorldSettings );
				
		// WPActorCellMapping contains actor names in the form of PersistentLevel.ActorName
		// So to match the format used by it, we need to prefix the actor name with a PersistentLevel
		FString ActorSubPathString;
		ActorSubPathString.Append(TEXT("PersistentLevel."));
		ActorSubPathString.Append(ObjectSaveHeader.GetBaseHeader().Reference.GetTopLevelActorName());
		
		if( auto* wpCellInfo = WorldSettings.WPActorCellMapping.Find( ActorSubPathString ); wpCellInfo )
		{
			auto& migratedData = PerLevelUnpackedSaveData.FindOrAdd( wpCellInfo->CellName );
			migratedData.Headers.Emplace( MoveTemp(ObjectSaveHeader) );
			migratedData.SaveData.Emplace( MoveTemp( UnpackedSaveData.SaveData[Ix] ) );
		}
		else
		{
			if( ObjectSaveHeader.IsActor() && ObjectSaveHeader.WasPlacedInLevel() )
			{
				// If it was placed in level and isn't in the cell mapping then it must have been removed
			}
			else
			{
				// not an actor or just wasn't placed in the level so treat it as runtime spawned actor
				auto& migratedData = PerLevelUnpackedSaveData.FindOrAdd( NAME_None );
				migratedData.Headers.Emplace( MoveTemp(ObjectSaveHeader) );
				migratedData.SaveData.Emplace( MoveTemp( UnpackedSaveData.SaveData[Ix] ) );
			}
		}
	}
	MigrateDestroyedActors( std::exchange( UnpackedSaveData.DestroyedActors, {} ) );
}

bool FWPSaveDataMigrationContext::ValidateSaveData( FArchive& ReadAr )
{
	const auto* World = WorldSettings.GetWorld();
	if( SaveHeader.SaveVersion >= FSaveCustomVersion::IntroducedWorldPartition )
	{
		if( SaveHeader.IsPartitionedWorld )
		{
			if( !World->IsPartitionedWorld() )
			{
				UE_LOG( LogSave, Error, TEXT("Loading a save game that was created for a partitioned world into a non-partitioned world is not possibe.") );
				return false;
			}
		}

		FWorldPartitionValidationData SavedValidationData;
		ReadAr << SavedValidationData;

		if( World->IsPartitionedWorld() )
		{
			for(const auto& [GridName, GridInfo]: SavedValidationData.Grids)
			{
				if(const auto* NewGridInfo = WorldSettings.SaveGameValidationData.Grids.Find( GridName ); NewGridInfo)
				{
					if( GridInfo.CellSize != NewGridInfo->CellSize )
					{
						// If the cell size has been changed then none of the existing save data will match any more
						for(const auto &[CellName, CellHash]: GridInfo.CellHashes)
						{
							InvalidatedCells.Add(CellName);
						}
					}
					else if ( GridInfo.GridHash != NewGridInfo->GridHash )
					{
						// If the grid hash doesn't match any more then we have cells with new or removed content.
						// We need to go through all of the cells and invalidate those that have been changed
						for( const auto& [CellName, CellHash]: GridInfo.CellHashes )
						{
							if( const auto* NewCellHash = NewGridInfo->CellHashes.Find( CellName ); !NewCellHash || *NewCellHash != CellHash )
							{
								InvalidatedCells.Emplace( CellName );
							}
						}
					}
				}
				else
				{
					// This grid doesn't even exist any more so all save data on this grid should be considered invalid
					for(const auto &[CellName, CellHash]: GridInfo.CellHashes)
					{
						InvalidatedCells.Add(CellName);
					}
				}
			}
			// Due to buggy behavior old saves may have been correctly flagged as partitioned but they may be lacking any grid validation data
			// If that's the case, just treat all the save data as invalid. 
			if( SavedValidationData.Grids.IsEmpty() )
			{
				bIsFullMigration = true;
			}
		}
	}
	else
	{
		// All save data is invalidated and needs conversion only as long as the world is partitioned
		bIsFullMigration = World->IsPartitionedWorld();
	}

	// Force a full World Partition migration if we were asked to using CVar
	if (CVarForceFullWPMigration.GetValueOnGameThread())
	{
		InvalidatedCells.Empty();
		bIsFullMigration = true;
	}
	return true;
}

void FWPSaveDataMigrationContext::SaveValidationData( FArchive& WriteAr, UFGSaveSession& SaveSession )
{
	auto* WorldSettings = Cast< AFGWorldSettings >( SaveSession.GetWorld()->GetWorldSettings() );
	fgcheck(WorldSettings);
	WriteAr << WorldSettings->SaveGameValidationData;
}

void FWPSaveDataMigrationContext::RepackSaveData( class UFGSaveSession& SaveSession )
{
	SaveSession.mSaveHeader.SaveVersion = FSaveCustomVersion::LatestVersion;
	FPackedSaveDataMap PackedSaveDataMap;
	
	for( auto& [LevelName, LevelSaveData]: PerLevelUnpackedSaveData )
	{
		auto& PackedLevelSaveData = PackedSaveDataMap.FindOrAdd( LevelName.ToString() );
		PackedLevelSaveData = MakeUnique<FPerStreamingLevelSaveData>( FSaveCustomVersion::LatestVersion );
		
		FMemoryWriter64 TOCWriter(PackedLevelSaveData->TOCBlob64);
		FMemoryWriter64 DataWriter(PackedLevelSaveData->DataBlob64);

		TOCWriter.SetIsSaving(true);
		DataWriter.SetIsSaving(true);
			
		TOCWriter.SetCustomVersion(FSaveCustomVersion::GUID, FSaveCustomVersion::LatestVersion, SaveSystemConstants::CustomVersionFriendlyName);
		DataWriter.SetCustomVersion(FSaveCustomVersion::GUID, FSaveCustomVersion::LatestVersion, SaveSystemConstants::CustomVersionFriendlyName);

		TOCWriter << LevelSaveData.Headers;
		DataWriter << LevelSaveData.SaveData;

		PackedLevelSaveData->DestroyedActors = LevelSaveData.DestroyedActors;
	}

	if(bIsFullMigration || InvalidatedCells.Contains(NAME_None))
	{
		TUniquePtr<FPerStreamingLevelSaveData> PersistentSaveData;
		PackedSaveDataMap.RemoveAndCopyValue( FName(NAME_None).ToString(), PersistentSaveData );
		if(ensure(PersistentSaveData))
		{
			SaveSession.mPersistentAndRuntimeData.TOCBlob64 = MoveTemp( PersistentSaveData->TOCBlob64 );
			SaveSession.mPersistentAndRuntimeData.DataBlob64 = MoveTemp( PersistentSaveData->DataBlob64 );
		}
	}

	if(bIsFullMigration)
	{
		SaveSession.mPerLevelDataMap = MoveTemp( PackedSaveDataMap );
	}
	else
	{
		TSet<FName> DeletedCells;
		TSet<FName> ExistingCells;
		for(auto& [CellName, CellSaveData]: SaveSession.mPerLevelDataMap)
		{
			if( !InvalidatedCells.Contains( FName(CellName) ))
			{
				continue;
			}

			const FName CellFName( *CellName );
			if(TUniquePtr<FPerStreamingLevelSaveData>* NewSaveData = PackedSaveDataMap.Find(CellName); NewSaveData)
			{
				CellSaveData = MoveTemp( *NewSaveData );
				ExistingCells.Add( CellFName );
			}
			else
			{
				DeletedCells.Add( CellFName );
			}
		}

		// Delete the cells that are no longer present in the world partition
		for( const FName& DeletedCell : DeletedCells)
		{
			SaveSession.mPerLevelDataMap.Remove( DeletedCell.ToString() );
		}
		
		// Append new cells to the save system
		for ( auto& [CellName, CellSaveData] : PackedSaveDataMap )
		{
			if ( !ExistingCells.Contains( *CellName ) )
			{
				SaveSession.mPerLevelDataMap.Add( CellName, MoveTemp( CellSaveData ) );
			}
		}
	}
}

void FWPSaveDataMigrationContext::PerformSaveDataMigration(UFGSaveSession& SaveSession)
{
	if( !bIsFullMigration && InvalidatedCells.IsEmpty() )
	{
		return;
	}

	// Migrate unresolved world save data before unpacking cells because this can result in extra cells being unpacked because actors were moved to them
	if(!SaveSession.mUnresolvedWorldSaveData.DestroyedActors.IsEmpty())
	{
		MigrateDestroyedActors( std::exchange( SaveSession.mUnresolvedWorldSaveData.DestroyedActors, {} ) );
	}

	for(const auto& [LevelName, LevelData]: SaveSession.mPerLevelDataMap)
	{
		if(bIsFullMigration || InvalidatedCells.Contains(FName(LevelName)))
		{
			if( SaveHeader.SaveVersion < FSaveCustomVersion::SwitchTo64BitSaveArchive )
			{
				MigrateBlobs( LevelData->TOCBlob, LevelData->DataBlob, false );
				MigrateDestroyedActors( LevelData->DestroyedActors );
			}
			else
			{
				MigrateBlobs( LevelData->TOCBlob64, LevelData->DataBlob64, false );
				MigrateDestroyedActors( LevelData->DestroyedActors );
			}
		}
	}
	
	if(bIsFullMigration || InvalidatedCells.Contains(NAME_None))
	{
		if( SaveHeader.SaveVersion < FSaveCustomVersion::SwitchTo64BitSaveArchive )
		{
			MigrateBlobs( SaveSession.mPersistentAndRuntimeData.TOCBlob, SaveSession.mPersistentAndRuntimeData.DataBlob , true );
		}
		else
		{
			MigrateBlobs( SaveSession.mPersistentAndRuntimeData.TOCBlob64, SaveSession.mPersistentAndRuntimeData.DataBlob64 , true );
		}
		MigrateDestroyedActors( SaveSession.mPersistentAndRuntimeData.DestroyedActors );
		for( auto& [levelName, destroyedActorArray]: SaveSession.mPersistentAndRuntimeData.LevelToDestroyedActorsMap )
		{
			MigrateDestroyedActors( destroyedActorArray );
		}
	}

	RepackSaveData( SaveSession );
}
