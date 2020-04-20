#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"

#include "FGWorldCreationInterface.h"
#include "FGEngineCommon.generated.h"

/**
 * Filtered and gathered stats we get during each frame
 */
struct FACTORYGAME_API FCollectedStats
{
	// How long was the frame
	float FrameTime;

	// The size of the required mips pool
	float RequiredMips;

	// The amount of drawcalls submitted
	int32 DrawCalls;

	// The amount of triangles drawn this frame
	int32 TrianglesDrawn;

public:
	FORCEINLINE ~FCollectedStats() = default;
};

/** 
 * Interface for stats collectors for our nightly stats gathering from maps
 */
struct FACTORYGAME_API IStatCollector
{
	virtual ~IStatCollector(){}

	/**
	 * Called when we start collecting stats, make sure to reset all members here
	 * @note Called on StatsThread
	 */
	virtual void StartCollection() = 0;

	/**
	 * Called when we stop collecting stats
	 * @note Called on StatsThread
	 */
	virtual void StopCollection() = 0;

	/**
	 * Called every frame whenever new stats has been gathered and filtered to a smaller subset
	 * @note Called on StatsThread
	 */
	virtual void CollectData( const FCollectedStats& filteredData ) = 0;

	/**
	 * Set the label for this stat collector
	 *
	 * @note Called on StatsThread
	 */
	virtual void SetLabel( const FString& label ){ Label = label; }

	/**
	* Set the guid for this stat collector
	*
	* @note Called on StatsThread
	*/
	virtual void SetGUID( const FString& guid ){ GUID = guid; }

	/**
	 * Dumps the stats to file
	 *
	 * @note Called on GameThread
	 */
	virtual void DumpChart() = 0;

protected:
	FORCEINLINE void GetLabel( FString& out_label ){ out_label = Label; }
	FORCEINLINE void GetGUID( FString& out_GUID ){ out_GUID = GUID; }
	
	/**
	 * Get the output directory where we dump our chart
	 */
	void GetAndCreateOutputDirectory( const FDateTime& timestamp, FString& out_directory );

	/**
	 * Get the filename of the stats file
	 */
	void GetDesiredOutputFile( const FDateTime& timestamp, const FString& mapName, const FString& fileTag, FString& out_filename );
private:
	/** The label of the collector */
	FString Label;
	/** The guid of the collector */
	FString GUID;
};

USTRUCT()
struct FACTORYGAME_API FFGEngineCommon
{
	GENERATED_BODY()
public:
	/** Called during startup */
	void Init( UEngine* engine, class IEngineLoop* inEngineLoop );

	/** Slightly later start o.O */
	void Start();

	/** Called right before engine shutdown */
	void PreExit();

	/**
	 * Handle exec commands
	 */
	bool Exec( class UWorld* inWorld, const TCHAR* cmd, FOutputDevice& ar );

	/**
	 * The the created worlds and update the render targets in them
	 */
	void Tick( float dt );

	/** Implements IFGWorldCreationInterface::CreateWorld  */
	class UWorld* CreateWorld( const FString& worldName );

	/** Implements IFGWorldCreationInterface::DestroyWorld */
	void DestroyWorld( class UWorld* world );
protected:
#if WITH_EDITOR
	// For pigment map, we want stuff to be updated when opening maps
	void PostPIEStarted( bool bIsSimulatingInEditor );
	void OnMapOpened( const FString& Filename, bool bAsTemplate );
#endif
private:
#if STATS
	/**
	 * Start collecting stats, to call this send exec: COLLECT START
	 * @note called on StatsThread
	 *
	 * @param label		- label of the collection
	 * @param mapName	- the map we collect stats on
	 * @param guid		- guid of the collection
	 **/
	void StartCollection( FString label, FString mapName, FString guid );

	/**
	 * Stop collecting stats, to call this send exec: COLLECT STOP
	 * @note called on StatsThread
	 **/
	void StopCollection();

	/**
	 * Called every frame between StartCollection and StopCollection when new stats are available
	 * @note called on StatsThread
	 **/
	void CollectStats( int64 frame );

	/**
	 * Dumps stats collection charts to disc
	 * @note called on GameThread, called as a result of calling StopCollection
	 */
	void DumpChart();
#endif
	/** Dump more texture stats that doesn't show up in ListTextures */
	void HandleHiddenTextureStatsCommand( const TCHAR* cmd, FOutputDevice& ar );
protected:
	UPROPERTY( transient )
	class UEngine* Engine;
	
	/** The worlds created through IFGWorldCreationInterface */
	UPROPERTY( transient )
	TArray<UWorld*> CreatedWorlds;

	/** Height fog properties that's controlled from camera */
	UPROPERTY()
	class UFGAtmosphereUpdater* AtmosphereUpdater;
private:
#if STATS
	/** The current stats collectors, @note: Threadcontext StatsThread */
	TArray< IStatCollector* > StatCollectors;

	/** Handle for the delegate the function that get called every frame on the stats thread when collecting stats, @note: Threadcontext StatsThread */
	FDelegateHandle CollectStatsDelegateHandle;

	/** If true, then we are collecting stats */
	bool mCollectStats;
#endif

public:
	FORCEINLINE ~FFGEngineCommon() = default;
};
