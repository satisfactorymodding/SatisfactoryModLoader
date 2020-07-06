// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UnrealString.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "BuildableColorSlotBase.h"
#include "FGSaveInterface.h"
#include "FGBuildingColorSlotStruct.h"
#include "FactoryTick.h"
#include "Materials/Material.h"
#include "FGBuildableSubsystem.generated.h"

class UFGProductionIndicatorInstanceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedGlobal, AFGBuildable*, buildable );

/** Used to track constructed (spawned) buildables matched with their holograms between client and server */
USTRUCT()
struct FACTORYGAME_API FNetConstructionID
{
	GENERATED_BODY()

	UPROPERTY()
	int8 NetPlayerID;

	UPROPERTY()
	uint16 Server_ID;

	UPROPERTY()
	uint16 Client_ID;

	FNetConstructionID() : 
		NetPlayerID(-1), 
		Server_ID(0), 
		Client_ID(0)
	{ }

	FString ToString()
	{
		return FString::Printf( TEXT( "{player ID: %d, Server: %d, Client: %d}" ), NetPlayerID, Server_ID, Client_ID );
	}

	// Check whether this net construction ID has has a complete ACK by travel from client -> server -> client
	bool HasCompleteACK()
	{
		return NetPlayerID >= 0 && Server_ID > 0 && Client_ID > 0;
	}

public:
	FORCEINLINE ~FNetConstructionID() = default;
};

/** Distances where we switch tick rate */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FDistanceBasedTickRate
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float Distance;

	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float TickRate;

public:
	FORCEINLINE ~FDistanceBasedTickRate() = default;
};

USTRUCT()
struct FACTORYGAME_API FBuildableBucket
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf< class AFGBuildable > BuildableClass;

	UPROPERTY()
	TArray< class AFGBuildable* > Buildables;

public:
	FORCEINLINE ~FBuildableBucket() = default;
};

USTRUCT()
struct FACTORYGAME_API FConveyorBucket
{
	GENERATED_BODY()

	FConveyorBucket(){}

	UPROPERTY()
	TArray< class AFGBuildableConveyorBase* > Conveyors;

public:
	FORCEINLINE ~FConveyorBucket() = default;
};

USTRUCT()
struct FACTORYGAME_API FBuildableGroupTimeData
{
	GENERATED_BODY()
	
	FBuildableGroupTimeData() :
		RealSeconds( 0 ),
		RealPartialSeconds( 0.f )
	{}
	
	// Returns the combined time data as a double
	double GetTimeAsDouble() { return ( double )RealSeconds + ( double )RealPartialSeconds; }

	int32 RealSeconds;

	float RealPartialSeconds;

public:
	FORCEINLINE ~FBuildableGroupTimeData() = default;
};

/**
 * Subsystem responsible for spawning and maintaining buildables.
 * This enables and disables ticks on the buildable.
 */
UCLASS(Blueprintable, config = Game, defaultconfig, meta = ( DisplayName = "Buildable Subsystem" ) )
class FACTORYGAME_API AFGBuildableSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGBuildableSubsystem();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	/** Calls Factory_Tick on all factory buildings */
	void TickFactory( float dt, ELevelTick TickType );

	/** Get the buildable subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	static AFGBuildableSubsystem* Get( UWorld* world );

	/** Get the buildable subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory", DisplayName = "GetBuildableSubsystem", meta = ( DefaultToSelf = "WorldContext" ) )
	static AFGBuildableSubsystem* Get( UObject* worldContext );

	/**
		* Spawn a buildable at a specified location, you need to call FinishSpawning on the buildable after this to finalize the spawning.
		*
		* @param inClass - The class we want to spawn (need to be valid).
		* @param inTransform - where we want to spawn the buildable.
		*/
	class AFGBuildable* BeginSpawnBuildable( TSubclassOf< class AFGBuildable > inClass, const FTransform& inTransform );

	/** Adds a buildable to the buildable array. */
	void AddBuildable( class AFGBuildable* buildable );

	/** Adds a conveyor to the conveyor buckets */
	void AddConveyor( AFGBuildableConveyorBase* conveyor );

	/** 
	* Get the connected conveyor belt from the given connection. 
	* Can return a nullptr if we have no belt connected or if the connected belt have bucket index assigned to -1 
	*/
	class AFGBuildableConveyorBase* GetConnectedConveyorBelt( class UFGFactoryConnectionComponent* connection );

	/** Remove the buildable from the subsystem, this is called by the buildable when destroyed. */
	void RemoveBuildable( class AFGBuildable* buildable );

	/** Remove the conveyor from the subsystem */
	void RemoveConveyor( AFGBuildableConveyorBase* conveyor );

	/**
	 *	Remove a conveyor from the bucket it's assigned to
	 *	If it's the only conveyor in the bucket the bucket will be removed
	 */
	void RemoveConveyorFromBucket( AFGBuildableConveyorBase* conveyorToRemove );

	/** Rearrange the conveyor buckets after we emptied a bucket */
	void RearrangeConveyorBuckets( int32 emptiedBucketID );

	/**
	*	Splits up a conveyor bucket into two buckets
	*	Empties the current bucket and adds all conveyors again into two buckets
	*/
	void RemoveAndSplitConveyorBucket( AFGBuildableConveyorBase* conveyorToRemove );

	/** Returns true if this subsystem has been created on a server instance */
	bool IsServerSubSystem() const;

	/** Get all buildables of the supplied type. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory" )
	void GetTypedBuildable( TSubclassOf< class AFGBuildable > inClass, TArray< class AFGBuildable* >& out_buildables ) const;

	/** Get all buildables of the supplied type. */
	template< typename T >
	void GetTypedBuildable( TArray< T* >& out_buildables ) const;

	/** Starts replaying of build effects in the build order of the buildings. */
	UFUNCTION()
	void ReplayBuildingEffects();

	/** Check if a material instance manager exists in the Subsystem TMap
	 *  @return - True if the lookupName is a key in mFactoryMaterialInstanceManagerMap. False otherwise.
	 */
	bool HasMaterialInstanceManagerForMaterialInterface( UMaterialInterface* materialInterface, FString& lookupName );

	/**
	*	Attempts to get the correct colored material for a supplied factory building material.
	*	If the material does not exist in the material map, a new dynamic instance is created, filled, and returned.
	*	@note - Params onMeshComp and forBuildable are not needed and are only used for logging purposes
	*/
	class UFGFactoryMaterialInstanceManager* GetOrCreateMaterialManagerForMaterialInterface( UMaterialInterface* materialInterface, FString& lookupName, FString& lookupPrefix, bool canBeColored = true, class UMeshComponent* onMeshComp  = nullptr, class AFGBuildable* forBuildable = nullptr );

	/**
	*	Get the mMaterialInstanceManager TMap of all managers
	*/
	const TMap< FString, class UFGFactoryMaterialInstanceManager* >& GetFactoryMaterialInstanceManagerMap() { return mFactoryColoredMaterialMap; }

	/**
	*	Called on a buildable when it is added to the subsystem to update its materials to utilize pooled DynamicMaterialInstances if they exist for the present factory materials
	*	If no FactoryMaterialInstanceManager can be matched with the present colorable factory materials on the mesh components on the buildable, a new manager object is created and applied
	*/
	void UpdateBuildableMaterialInstances( AFGBuildable* buildable );

	/** Will attempt to remove an entry from the material instance manager map. This is called by buildables when they have a*/
	void RemoveFactoryMaterialInstanceFromMap( const FString& lookupName );

	/** Getters for Color Slots - Now Linear Colors */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	FLinearColor GetColorSlotPrimary_Linear( uint8 index );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	FLinearColor GetColorSlotSecondary_Linear( uint8 index);

	/** Settings for Color Slots - Now linear Colors */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	void SetColorSlotPrimary_Linear( uint8 index, FLinearColor color );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	void SetColorSlotSecondary_Linear( uint8 index, FLinearColor color );

	/** Returns the number of colorable slots actually available to the the player ( this can be less than BUILDABLE_COLORS_MAX_SLOTS ) */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	uint8 GetNbColorSlotsExposedToPlayers() { return mNbPlayerExposedSlots; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	void DebugEnableInstancing( bool enabled );
	void DebugGetFactoryActors( TArray< AActor* >& out_actors );

	/** Returns the factory stat ID of the object used for the profiling tool. */
	FORCEINLINE TStatId GetFactoryStatID( bool forDeferredUse = false ) const
	{
#if STATS
		// this is done to avoid even registering stats for a disabled group (unless we plan on using it later)
		if( forDeferredUse || FThreadStats::IsCollectingData( GET_STATID( STAT_UObjectsStatGroupTester ) ) )
		{
			if( !mFactoryStatID.IsValidStat() )
			{
				CreateFactoryStatID();
			}
			return mFactoryStatID;
		}
#endif
		return TStatId(); // not doing stats at the moment, or ever
	}

	UMaterial* GetFactoryDefaultMaterial()
	{
		return mDefaultFactoryMaterial;
	}

	/** Generates a new NetConstructionID for buildables. Can be used from client to identify buildings that were constructed from server. */
	FNetConstructionID GetNewNetConstructionID();

	/** Populates a given client construction ID with server side ACKs */
	void GetNewNetConstructionID( FNetConstructionID& clientConstructionID );

	void SpawnPendingConstructionHologram( FNetConstructionID netConstructionID, class AFGHologram* templateHologram, class AFGBuildGun* instigatingBuildGun );

	void AddPendingConstructionHologram( FNetConstructionID netConstructionID, class AFGHologram* hologram );
	void RemovePendingConstructionHologram( FNetConstructionID netConstructionID );

protected:
	// Find and return a local player
	class AFGPlayerController* GetLocalPlayerController() const;

	/** Distance from a location to closest point of buildables AABB */
	float GetDistanceSqToBoundingBox( const FVector& point, class AFGBuildable* buildable ) const;

	/** Register/unregister our factory tick function */
	void RegisterFactoryTickFunction( bool shouldRegister );
private:
	/** Create a stat for the buildable */
	void CreateFactoryStatID() const;

	void UpdateReplayEffects( float dt );

	void AddBuildableMeshInstances( class AFGBuildable* buildable );

	/* Tick all factory buildings, conveyors and conveyor attachments */
	void TickFactoryActors( float dt );

public:
	/** Distance used when calculating if a location is near a base */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float mDistanceConsideredClose;

	/** How many factories need to be within the close range for it to count as if a given location is near a base */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	int32 mNumFactoriesNeededForCloseCheck;

	/** Broadcast when a buildable or decor has been constructed. Regardless of who built it */
	UPROPERTY( BlueprintAssignable, Category = "Build", DisplayName = "OnBuildableConstructedGlobal" )
	FOnBuildableConstructedGlobal BuildableConstructedGlobalDelegate;

	/** Print all fixed factory tick information */
	void DumpFixedFactoryTickValues() const;

	/**
	 * Used by UFGColoredInstanceMeshProxy to get an instance if it's not already been assigned
	 */
	class UFGColoredInstanceManager* GetColoredInstanceManager( class UFGColoredInstanceMeshProxy* proxy );

private:
	// Allow the Colored instance manager objects created to directly add entries into the FactoryColoredMaterialMap
	friend class UFGFactoryMaterialInstanceManager;

	/** last used net construction ID. Used to identify pending constructions over network. Will increase ID every constructed building. */
	FNetConstructionID mLastServerNetConstructionID;

	/** List of all buildables. */
	UPROPERTY()
	TArray< class AFGBuildable* > mBuildables;

	/************************************************************************/
	/* Begin variables for parallelization
	/************************************************************************/
	
	/** This contains all factory tickable buildings except conveyors and splitter/mergers */
	TArray< class AFGBuildable* > mFactoryBuildings;

	// Groupings of factory buildings for reduced thread count parallelization
	TArray < TArray < class AFGBuildable* >> mFactoryBuildingGroups;

	// Track if we need to rebuild the factory buildings groupings
	bool mFactoryBuildingGroupsDirty;

	/** All conveyor belts that can be executed in parallel sorted into buckets. 
	*	Each bucket contains a complete section of belts in the order of output to input.
	*	A bucket can contain a single conveyor belt, a section or a looped section
	*	An exception exists for belts that connect to buildables with 2 outputs, those are added to a separate buckets
	*/
	TArray< FConveyorBucket* > mConveyorBuckets;

	/** All conveyors that are not safe to execute in parallel
	*	At the time of writing this is used only for conveyors connecting to buildings with multiple outputs
	*/
	TArray< AFGBuildableConveyorBase* > mSerialConveyorGroup;

	// Groupings of conveyor buckets
	TArray< TArray < FConveyorBucket* > > mConveyorBucketGroups;

	// Track whether or not we need to repopulate our conveyor groups
	bool mConveyorBucketGroupsDirty;

	/** All conveyor attachments */
	UPROPERTY()
	TArray< class AFGBuildableConveyorAttachment* > mConveyorAttachments;

	// Grouping of conveyor attachments for reduced thread count parallelization
	TArray< TArray < class AFGBuildableConveyorAttachment* >> mConveyorAttachmentGroups;

	// Track if we need to rebuild the attachments groupings
	bool mConveyorAttachmentGroupsDirty;

	/************************************************************************/
	/* End variables for parallelization
	/************************************************************************/

	/** Hierarchical instances for the factory buildings. */
	UPROPERTY()
	AActor* mBuildableInstancesActor;
	
	UPROPERTY()
	TMap< class UStaticMesh*, class UProxyHierarchicalInstancedStaticMeshComponent* > mBuildableMeshInstances;

	/**/
	UPROPERTY()
	UFGProductionIndicatorInstanceManager* mProductionIndicatorInstanceManager = nullptr;

	/**/
	UPROPERTY()
	TMap< class UStaticMesh*, class UFGColoredInstanceManager* > mColoredInstances;

	bool mColorSlotsAreDirty = false;
	
	// DEPRECATED - Use Linear Color instead
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Customization" )
	FColor mColorSlotsPrimary[ BUILDABLE_COLORS_MAX_SLOTS ];

	// DEPRECATED - Use Linear Color instead
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Customization" )
	FColor mColorSlotsSecondary[ BUILDABLE_COLORS_MAX_SLOTS ];

	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Customization" )
	TArray< FLinearColor > mColorSlotsPrimary_Linear;

	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Customization" )
	TArray< FLinearColor > mColorSlotsSecondary_Linear;

	uint8 mColorSlotDirty[ BUILDABLE_COLORS_MAX_SLOTS ];

	/** The number of color slots players can adjust/define, this can be less than the total number of color slots actually present */
	UPROPERTY( EditDefaultsOnly, Category = "Customization" )
	uint8 mNbPlayerExposedSlots = 16;

	// Map of all Factory materials that are referenced by Factory buildings. Maps the materials name (and all dynamic instance mat names) to a manager class holding corresponding colored instances
	// This is also used for non-colored materials, for example, the conveyor belt materials so that the same instance can be applied to many different belts
	UPROPERTY()
	TMap< FString, class UFGFactoryMaterialInstanceManager* > mFactoryColoredMaterialMap;

	// Count index for unique naming of new material Insance mangers
	int32 mMaterialManagerIDCounter;


	/** Begin Fixed Factory Tick Config Parameters */
	UPROPERTY( config )
	bool mUseFixedFactoryTick;

	UPROPERTY( config )
	float mMinFactoryTickRate;

	UPROPERTY( config )
	float mMaxFactoryTickRate;

	UPROPERTY( config )
	int mMaxTickSubsteps;
	/** End Fixed Factory Tick Parameters*/

	/** Time in MS of the minimum tick time (1.f / mMinFactoryTickRate)
	*	Minimum factory tick refers to the maximum amount of time that is allowed to pass per factory tick. So minimum here is actually a larger number than max
	*	A little confusing, but this way it can match its respective tickRate var by name: mMinFactoryTickRate, which appears in the config.
	*/
	float mMinFactoryTick;

	/** Time in MS of the maximum tick time (1.f / mMaxFactoryTickRate)
	*	Maximum factory tick refers to the minimum amount of time that is allowed to pass to execute a factory tick. Maximum here is actually a smaller number than min
	*	Again, a little confusing, but this way it can match its respective tickRate var by name: mMaxFactoryTickRate, which appears in the config.
	*/
	float mMaxFactoryTick;

	/** How much time did we not utilize the previous Factory update? */
	float mFixedTickDebt;

	/** Maximum number of buildables that we consider their optimization level during the same frame */
	int32 mMaxConsideredBuildables;

	/** Last buildable that was considered */
	int32 mLastConsideredBuildableIdx;

	/** Distance we disable buildables ticking on */
	float mDisabledBuildableTickDistance;

	/** Information about what distances we change the tick rate on */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	TArray< FDistanceBasedTickRate > mDistanceBasedTickRate;

	/** Is factory optimization ( tick control ) active */
	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	bool mFactoryOptimizationEnabled;

	/** How much time can differ between each build effect */
	UPROPERTY( EditDefaultsOnly, Category = "Replay" )
	float mReplayEffecTimeDilation;

	/** How much time between each build effect when replaying the whole factory */
	UPROPERTY( EditDefaultsOnly, Category = "Replay" )
	float mReplayEffectTimerDefault;

	/** Timer used for the replay effect */
	float mReplayEffectTimer;

	/** Array with all the buildings that should replay their effect */
	TArray< AFGBuildable* > mReplayEffectArray;

	/**used for comparing and finding materials of factory meshes*/
	UPROPERTY( EditDefaultsOnly )
	UMaterial* mDefaultFactoryMaterial;

	bool IsBasedOn( const UMaterialInterface* instance, const UMaterial* base );

	//@todorefactor With meta = ( ShowOnlyInnerProperties ) it does not show and PrimaryActorTick seems to be all custom properties, so I moved to another category but could not expand.
	/** Controls if we should receive Factory_Tick and how frequent. */
	UPROPERTY( EditDefaultsOnly, Category = "Factory Tick", meta = ( NoAutoJson = true ) )
	FFactoryTickFunction mFactoryTickFunction;

	/** Tracking variable to see if our parallel tick group size has changed */
	int32 mLastParallelTickGroupSize;

	/** Factory Stat id of this object, 0 if nobody asked for it yet */
	STAT( mutable TStatId mFactoryStatID; )

	/** Holograms simulated on client to indicate any pending constructions from server */
	TMap<int16, class AFGHologram*> mPendingConstructionHolograms;

public:
	FORCEINLINE ~AFGBuildableSubsystem() = default;
};

template< typename T >
void AFGBuildableSubsystem::GetTypedBuildable( TArray< T* >& out_buildables ) const
{
	for( auto buildable : mBuildables )
	{
		T* specificBuildable = Cast< T >( buildable );
		if( IsValid( specificBuildable ) )
		{
			out_buildables.Add( specificBuildable );
		}
	}
}
