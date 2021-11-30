// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGFactoryColoringTypes.h"
#include "FGSaveInterface.h"
#include "FactoryTick.h"
#include "FGBuildableSubsystem.generated.h"

class UFGProductionIndicatorInstanceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildableConstructedGlobal, AFGBuildable*, buildable );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnBuildableLightColorSlotsUpdated );

/** Used to track constructed (spawned) buildables matched with their holograms between client and server */
USTRUCT()
struct FNetConstructionID
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
};

/** Distances where we switch tick rate */
USTRUCT( BlueprintType )
struct FDistanceBasedTickRate
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float Distance;

	UPROPERTY( EditDefaultsOnly, Category = "Factory" )
	float TickRate;
};

USTRUCT()
struct FBuildableBucket
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf< class AFGBuildable > BuildableClass;

	UPROPERTY()
	TArray< class AFGBuildable* > Buildables;
};

USTRUCT()
struct FConveyorBucket
{
	GENERATED_BODY()

	FConveyorBucket(){}

	UPROPERTY()
	TArray< class AFGBuildableConveyorBase* > Conveyors;
};

USTRUCT()
struct FBuildableGroupTimeData
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
};

enum class EPropagateColorState : uint8
{
	SettingColorOnly,
	Done
};

/**
 * Subsystem responsible for spawning and maintaining buildables.
 * This enables and disables ticks on the buildable.
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Buildable Subsystem" ) )
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

	/** Cleans up fog planes spawned by this buildable. */
	void RemoveFogPlanes(class AFGBuildable* buildable);
	
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

	/** Getters for Color Slots - Now Data Structures */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	const FFactoryCustomizationColorSlot& GetColorSlot_Data( uint8 index ) const;

	/** Settings for Color Slots - Now linear Colors */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	void SetColorSlot_Data( uint8 index, FFactoryCustomizationColorSlot color );

	/** Returns the collection corresponding to the specified type of Customization (Swatch/Pattern/Material) */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Customization" )
	TSubclassOf< class UFGFactoryCustomizationCollection > GetCollectionForCustomizationClass( TSubclassOf< class UFGFactoryCustomizationDescriptor > collectionClassType ) const;

	/** Getter for buildable light color slot for the given index */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    FLinearColor GetBuildableLightColorSlot( int32 index ) const;
    
	/** Getter for all buildable light color slots */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Buildable|Light", meta=(BlueprintPure = false) )
	TArray<FLinearColor> GetBuildableLightColorSlots() const;

	/** Returns the number of colorable slots actually available to the the player  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Buildable|Light" )
    int32 GetNumBuildableLightColorSlots() const { return mBuildableLightColorSlots.Num(); }

	/** Called both on client and server when the buildable light color slots have been updated */
	void BuildableLightColorSlotsUpdated( const TArray< FLinearColor >& colors );
	
	void UpdateBuildableCullDistances(float newFactor);

	/** Gets or adds a conveyor belt track material from a material instance. If the material does not already exist a new one is instantiated from the Interface and returned */
	UMaterialInstanceDynamic* GetConveyorBelTrackMaterialFromSpeed( float speed, UMaterialInterface* currentMaterial );

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	void DebugEnableInstancing( bool enabled );
	void DebugGetFactoryActors( TArray< AActor* >& out_actors );

	static FName GetMeshMapName(UStaticMesh* mesh, UMeshComponent* sourceComponent);
	
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

	/** Preview Customization application on Buildable/Actor */
	void ApplyCustomizationPreview( class IFGColorInterface* colorInterface, const FFactoryCustomizationData& previewData );

	/** Clear a single customization preview */
	void ClearCustomizationPreview( class IFGColorInterface* colorInterface );

	/** Clear all previewed customizations in the cached buildable map */
	void ClearAllCustomizationPreviews();

	/** Remove a detail actor from pending list if it exists. Called when a buildable is interacted with */
	void TryRemovePendingDetailActor( class AFGReplicationDetailActor* detailActor );
	
	/** When a buildable is no longer being interacted with its rep detail actor will be added to this list */
	void AddPendingRemovalDetailActor( class AFGReplicationDetailActor* detailActor );
	
	static uint8 GetCurrentSubStepIteration()
	{
		return mCurrentSubStep;
	}

	static uint8 GetLastSubStepIteration()
	{
		return mCurrentSubStepMax;
	}

	static bool IsLastFactorySubStep()
	{
		return mCurrentSubStep == mCurrentSubStepMax;
	}

	// Called from BuildGunPaint for previewing skin logic
	TArray< TSubclassOf< class AFGBuildable >> GetPreviewSkinsOnBuildableList() { return mPreviewSkinsOnBuildablesList; }
	
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

	/** Internal helpers to setup a buildable that is registered. */
	void AddBuildableMeshInstances( class AFGBuildable* buildable );
	void AddToTickGroup( AFGBuildable* buildable );
	void RemoveFromTickGroup( AFGBuildable* buildable );
	void SetupColoredMeshInstances( AFGBuildable* buildable );
	void SetupProductionIndicatorInstancing( class AFGBuildable* buildable );

	/* Tick all factory buildings, conveyors and conveyor attachments */
	void TickFactoryActors( float dt );

	UFUNCTION()
	void UpdateConveyorRenderType( FString cvar );

	void SetCurrentSubStepValue( uint8 itr )
	{
		mCurrentSubStep = itr;
	}
	
	void SetCurrentMaxSubStepValue( uint8 itr )
	{
		mCurrentSubStepMax = itr;
	}
		
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

	/** Broadcast when buildable light color slots have been updated. Used to update UI */
	UPROPERTY( BlueprintAssignable, Category = "Light Color" )
	FOnBuildableLightColorSlotsUpdated mOnBuildableLightColorSlotsUpdated;

	/**
	 * Used by UFGColoredInstanceMeshProxy to get an instance if it's not already been assigned
	 */
	class UFGColoredInstanceManager* GetColoredInstanceManager( class UFGColoredInstanceMeshProxy* proxy );

	/**
	 * Used by UFGFactoryLegInstanceMeshProxy to get an instance if it's not already been assigned
	 */
	class UFGFactoryLegInstanceManager* GetFactoryLegInstanceManager( class UFGFactoryLegInstanceMeshProxy* proxy );

	/**
	 * Used by buildables in postload to migrate slot data to Customization Swatch. This should only be utilized by loading logic and is using cached data
	 */
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > GetMigrationSwatchForSlot( int32 slotID );

	/** This is externalized from the build gun state to allow for easier mod support */
	UPROPERTY()
	TArray< TSubclassOf< class AFGBuildable > > mPreviewSkinsOnBuildablesList;
	
private:

	/** last used net construction ID. Used to identify pending constructions over network. Will increase ID every constructed building. */
	FNetConstructionID mLastServerNetConstructionID;

	/** List of all buildables. */
	UPROPERTY()
	TArray< class AFGBuildable* > mBuildables;

	/************************************************************************/
	/* Begin variables for parallelization									*/
	/************************************************************************/
	
	/** This contains all factory tickable buildings except conveyors and splitter/mergers */
	TArray< class AFGBuildable* > mFactoryBuildings;

	// Groupings of factory buildings for reduced thread count parallelization
	TArray < TArray < class AFGBuildable* > > mFactoryBuildingGroups;

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
	/* End variables for parallelization									  */
	/************************************************************************/

	/** Hierarchical instances for the factory buildings. */
	UPROPERTY(EditAnywhere, Category="Colorable Instance Actor")
	AActor* mBuildableInstancesActor;

	/** Hierarchical instances for the factory Legs. */
	UPROPERTY( EditAnywhere, Category = "FactoryLeg Instance Actor" )
	AActor* mFactoryLegInstancesActor;

	UPROPERTY()
	TMap< class UStaticMesh*, class UProxyHierarchicalInstancedStaticMeshComponent* > mBuildableMeshInstances;

	/**/
	UPROPERTY()
	UFGProductionIndicatorInstanceManager* mProductionIndicatorInstanceManager = nullptr;

	/** Map of colorable static meshes to their corresponding instance manager */
	UPROPERTY(EditAnywhere, Category="Colored Instance Managers" )
	TMap< FName, class UFGColoredInstanceManager* > mColoredInstances;
//	TMap< class UStaticMesh*, class UFGColoredInstanceManager* > mColoredInstances;

	/** Map of factory leg meshes to their corresponding instance manager */
	UPROPERTY( EditAnywhere, Category = "Factory Leg Instance Managers" )
	TMap< class UStaticMesh*, class UFGFactoryLegInstanceManager* > mFactoryLegInstances;

	bool mColorSlotsAreDirty = false;
	
	// DEPRECATED - Use mColoreSlots_Data
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Customization" )
	FColor mColorSlotsPrimary[ BUILDABLE_COLORS_MAX_SLOTS_LEGACY ];

	// DEPRECATED - Use mColoreSlots_Data
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Customization" )
	FColor mColorSlotsSecondary[ BUILDABLE_COLORS_MAX_SLOTS_LEGACY ];

	// DEPRECATED - Use mColoreSlots_Data
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Customization" )
	TArray< FLinearColor > mColorSlotsPrimary_Linear;

	// DEPRECATED - Use mColoreSlots_Data
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Customization" )
	TArray< FLinearColor > mColorSlotsSecondary_Linear;

	// New color slot implementation
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Customization" )
	TArray< FFactoryCustomizationColorSlot > mColorSlots_Data;

	/** List of actors which are having customizations (color, pattern etc. ) previewed on them so we can clear them later*/
	UPROPERTY()
	TArray< AActor* > mPreviewingCustomizationsList;

	/** This contains all buildable light sources. Used to update light sources when light color slots have changed */
	TArray< class AFGBuildableLightSource* > mBuildableLightSources;

	/** The player adjustable color slots used by the buildable lights. Saved and replicated in game state. */ 
	UPROPERTY( Transient )
	TArray< FLinearColor > mBuildableLightColorSlots;

	/* Current sub~step iteration*/
	static uint8 mCurrentSubStep;
	/* Final sub~step iteration.*/
	static uint8 mCurrentSubStepMax;

	/************************************************************************/
	/* Color Propagation Params                                             */
	/************************************************************************/
	EPropagateColorState mColorPropState = EPropagateColorState::Done;
	int32 mColorPropagationProgressIndex = 0;
	int32 mVehiclePropagationProgressIndex = 0;
	float mColorPropagationTimer = 0;
	/** Array with all the buildings that should replay their effect */
	TArray< AFGBuildable* > mColorPropagationArray;

	/** Array of all vehicles to update while updating color slots */
	TArray< class AFGVehicle* > mVehicleColorPropagationArray;

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

	/** Used to store different belt materials and their speeds so their materials can be shared */
	UPROPERTY()
	TMap< int32, UMaterialInstanceDynamic* > mConveyorTrackSpeedToMaterial;

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

	/** Asset containing list of all Swatch assets */
	UPROPERTY( EditDefaultsOnly, Category = "Customization" )
	TArray< TSubclassOf< class UFGFactoryCustomizationCollection > > mCustomizationCollectionClasses;

	/** List of all Active Replication Detail Actors to be considered for removal */
	UPROPERTY()
	TArray< class AFGReplicationDetailActor* > mRepDetailCleanupArray;

	UPROPERTY()
	float mTimeUntilRepDetailCheck = 1.0f;

	UPROPERTY()
	float mSqDistanceForDetailCleanup = 10000000.f;

	/** Helper map for quicker migrating from old slot data to new swatch desc asset in post load by doing a simple look up*/
	UPROPERTY()
	TMap < int32, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > > mSlotToSwatchDescMigrationMap;

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
