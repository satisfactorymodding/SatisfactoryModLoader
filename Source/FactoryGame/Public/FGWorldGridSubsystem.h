// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "WorldCollision.h"
#include "Engine/DataAsset.h"
#include "Engine/DeveloperSettings.h"

#include "FGWorldGridSubsystem.generated.h"

DECLARE_STATS_GROUP( TEXT( "WorldGridStats" ), STATGROUP_WorldGrid, STATCAT_Advanced );
DECLARE_MEMORY_STAT(TEXT( "World Grid Memory Size" ), Stat_WorldGridSize, STATGROUP_WorldGrid);

DECLARE_LOG_CATEGORY_EXTERN( LogWorldGrid, Log, All );

/** Data contained by every cell in the world grid. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGWorldGridCellData
{
	GENERATED_BODY()

	FFGWorldGridCellData();
	
	// Highest point in the cell
	UPROPERTY( VisibleAnywhere )
	float Elevation;
};

/** Runtime version of a world grid cell. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGWorldGridCell
{
	GENERATED_BODY()

	FFGWorldGridCell();
	FFGWorldGridCell( const FFGWorldGridCellData& Data, const FVector& WorldLocation, int32 CellIndex );

	float GetElevation() const;

	/** The data of this cell. */
	FFGWorldGridCellData mData;

	/** World location in the center of this cell. */
	FVector mWorldLocation;

	/** Index of this cell in the world grid array. */
	int32 mCellIndex;

	/** Function bound to mTraceDelegate */
	void OnTraceCompleted( const FTraceHandle& Handle, FTraceDatum& Data );

	FTraceDelegate mTraceDelegate;
};

/** Data asset for storing world grid. Used to pre-calculate the world grid in editor so it's available in runtime. */
UCLASS()
class FACTORYGAME_API UFGWorldGridDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	void AssignWorldCells( TArray<FFGWorldGridCellData>&& Cells, const FVector2D& GridMin, const FVector2D& GridMax, int32 Divisions );

	const TArray<FFGWorldGridCellData>& GetWorldGridCells() const { return mWorldCells; }
	
	int32 GetNumWorldGridDivisions() const { return mGridDivisions; }

	const FVector2D& GetGridMin() const { return mWorldGridMin; }
	const FVector2D& GetGridMax() const { return mWorldGridMax; }
	
	FVector2D GetGridSize() const { return mWorldGridMax - mWorldGridMin; }

	UFUNCTION( BlueprintCallable, Category = "World Grid", meta = ( CallInEditor = "true" ) )
    void DebugDraw();
	
private:
	UPROPERTY( VisibleAnywhere )
	int32 mGridDivisions;

	UPROPERTY( VisibleAnywhere )
	FVector2D mWorldGridMin;

	UPROPERTY( VisibleAnywhere )
	FVector2D mWorldGridMax;
	
	UPROPERTY( VisibleAnywhere )
	TArray<FFGWorldGridCellData> mWorldCells;
};

/**
 * World grid subsystem. Creates a grid of cells covering the entire world with data in each cell, such as height.
 */
UCLASS( config = Game, Blueprintable, defaultconfig, meta = ( DisplayName = "World Grid Subsystem" ) )
class FACTORYGAME_API AFGWorldGridSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGWorldGridSubsystem();

	/** Get the subsystem, this should always return something unless you call it really early. */
	static AFGWorldGridSubsystem* Get( UWorld* world );

	/** Get the subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|WorldGrid", DisplayName = "GetWorldGridSubsystem", Meta = (DefaultToSelf = "worldContext") )
    static AFGWorldGridSubsystem* Get( UObject* worldContext );

	void UpdateCellContainingBuildable( class AFGBuildable* pBuildable );

	UFUNCTION( BlueprintPure, Category = "WorldGrid")
	FVector2D GetWorldGridCoordinatesForLocation( const FVector& WorldLocation ) const;
	
	FFGWorldGridCell* GetCellContainingWorldLocation( const FVector& WorldLocation );
	int32 GetCellIndexFromWorldLocation( const FVector& WorldLocation ) const;

	TArray<const FFGWorldGridCell*> GetCellNeighbours( const FFGWorldGridCell* Cell ) const;
	TArray<const FFGWorldGridCell*> GetCellNeighboursFromindex( int32 Index ) const;

	FVector2D GetCellSize() const;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

private:
	UPROPERTY( EditDefaultsOnly )
	UFGWorldGridDataAsset* mDefaultWorldGridData;

	UPROPERTY( VisibleAnywhere )
	TArray<FFGWorldGridCell> mWorldGrid;

	TArray<FFGWorldGridCell*> mDirtyCells;
};

/** Settings for world grid generation. */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "World Grid Settings" ) )
class FACTORYGAME_API UFGWorldGridSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	/** How many times we'll divide the world into cells */
	UPROPERTY( EditDefaultsOnly, config )
	int32 mWorldGridDivisions;

	/** Cell elevation works with these steps only, so we don't have to update the height as often. */
	UPROPERTY( EditDefaultsOnly, config )
	float mElevationStepSize;
	
public:
   
	static int32 GetNumWorldGridDivisions()
	{
		return GetDefault<UFGWorldGridSettings>()->mWorldGridDivisions;
	}

	static float GetElevationStepSize()
	{
		return GetDefault<UFGWorldGridSettings>()->mElevationStepSize;
	}
};