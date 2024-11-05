// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGFoliageResourceUserData.h"
#include "FGFoliageTypes.h"
#include "FGSaveInterface.h"
#include "GameFramework/Info.h"
#include "IntVectorTypes.h"
#include "Math/GenericOctree.h"
#include "FGFoliageRemovalSubsystem.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
DECLARE_STATS_GROUP( TEXT("FoliageRemovalSubsystem"), STATGROUP_FoliageRemovalSubsystem, STATCAT_Advanced );

struct FFoliageOctreeSemantics
{
	// When a leaf gets more than this number of elements, it will split itself into a node with multiple child leaves
	enum { MaxElementsPerLeaf = 10 };

	// This is used for incremental updates.  When removing a polygon, larger values will cause leaves to be removed and collapsed into a parent node.
	enum { MinInclusiveElementsPerNode = 5 };

	// How deep the tree can go.
	enum { MaxNodeDepth = 20 };

	using FOctree = TOctree2<UHierarchicalInstancedStaticMeshComponent*, FFoliageOctreeSemantics>;

	typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;

	static FBoxCenterAndExtent GetBoundingBox(const UHierarchicalInstancedStaticMeshComponent* Element);
	static bool AreElementsEqual(const UHierarchicalInstancedStaticMeshComponent* A, const UHierarchicalInstancedStaticMeshComponent* B);
	static void SetElementId(FOctree& Octree, const UHierarchicalInstancedStaticMeshComponent* Element, FOctreeElementId2 OctreeElementID);
};

struct FFoliageComponentsOctree : public TOctree2<UHierarchicalInstancedStaticMeshComponent*, FFoliageOctreeSemantics>
{
	FFoliageComponentsOctree(const FVector& InOrigin,FVector::FReal InExtent) : TOctree2(InOrigin, InExtent)  {}
	FFoliageComponentsOctree() = default;
	
	TMap<const UHierarchicalInstancedStaticMeshComponent*, FOctreeElementId2> mElementIdMap;
};

USTRUCT()
struct FFoliageRemovalSaveDataForFoliageType
{
	GENERATED_BODY()
	
	bool Append( TArrayView< FVector > newRemovals );
	bool Add(const FVector& Location );

	const TArray<FVector>& Locations() const { return RemovedLocations; }
	bool Contains(const FVector& Location) const;

	int32 NumBuckets() const
	{
		return RemovalBuckets.Num();
	}

	TArrayView<const FVector> GetBucket(int32 bucketId) const
	{
		fgcheck( RemovalBuckets.IsValidIndex( bucketId ) );
		const auto& bucket = RemovalBuckets[bucketId];
		const TArrayView<const FVector> entireArray( RemovedLocations );
		return entireArray.Slice( bucket.GetLowerBound().GetValue(), bucket.Size<int32>() );
	}
	
	TSet< FHashableVectorWrapper > GetRemovalLocations() const;
	void CollapseBuckets(int32 FirstBucket, int32 LastBucket);
	bool IsEmpty() const
	{
		return RemovedLocations.IsEmpty();
	}
	
	bool PostSerialize(const FArchive& Ar);
private:
	/**
	 * An array of all the removed locations.
	 */
	UPROPERTY(SaveGame)
	TArray<FVector> RemovedLocations = {};

	/**
	 * A lookup table for the above array
	 */
	UPROPERTY(SaveGame)
	TSet<uint32> RemovedLocationLookup = {};

	UPROPERTY()
	TArray<FInt32Range> RemovalBuckets = {};
};

template<> struct TStructOpsTypeTraits<FFoliageRemovalSaveDataForFoliageType> : public TStructOpsTypeTraitsBase2<FFoliageRemovalSaveDataForFoliageType>
{
	enum
	{
		WithPostSerialize = true
	};
};


USTRUCT()
struct FFoliageRemovalSaveDataPerCell
{
	GENERATED_BODY()
	using KeyType = const UFoliageType*;
	
	UPROPERTY(SaveGame)
	TMap<const UFoliageType*, FFoliageRemovalSaveDataForFoliageType> SaveDataMap;
};

USTRUCT()
struct FFoliageRemovalUnresolvedSaveDataPerCell
{
	GENERATED_BODY()
	using KeyType = FName;
	
	UPROPERTY(SaveGame)
	TMap<FName, FFoliageRemovalSaveDataForFoliageType> SaveDataMap;
};

DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnNewFoliageBucketRemoved, const FIntVector& cell, const UFoliageType* foliageType, int32 bucketId );
UCLASS()
class FACTORYGAME_API AFGFoliageRemovalSubsystem : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()
	friend class UFGFoliageEditorSubsystem;
public:
	/** ctor */
	AFGFoliageRemovalSubsystem();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;
	virtual void Serialize(FArchive& Ar) override;
#if WITH_EDITORONLY_DATA
	virtual void PostLoad() override;
#endif
	static void AddReferencedObjects( UObject* InThis, FReferenceCollector& Collector );
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Called to initialize the subsystem and spawn actors for the levels that's already loaded when we was created */
	void Init();

	/** Get the foliage removal subsystem, this should always return something unless you call it really early */
	static AFGFoliageRemovalSubsystem* Get( UWorld* world );

	/** Get the foliage removal subsystem from a world context, this should always return something unless you call it really early */
	UFUNCTION(BlueprintPure, Category="Foliage", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGFoliageRemovalSubsystem* GetFoliageRemovalSubsystem( UObject* worldContext );
	
	/**
	 * Tries to emulate looking at a location from a location, and get the closest actor you are looking at
	 *
	 * @network: Server and Client
	 *
	 * @param viewLocation - from where you are looking
	 * @param endViewLocation - end of look trace
	 * @param foliageIdentifier - find foliage that matches this tag
	 * @param out_component - the component we are looking at, only valid if we return true
	 * @param out_instanceId - id that we are looking at, only valid if we return true
	 * @param out_instanceLocation - the location of the instance, only valid if we return true
	 * @return true if we looked at any foliage
	 **/
	bool GetLookAtFoliage( const FVector& viewLocation, const FVector& endViewLocation,
						   TSubclassOf< class UFGFoliageIdentifier > foliageIdentifier,
						   class UHierarchicalInstancedStaticMeshComponent*& out_component, int32& out_instanceId,
						   FVector& out_instanceLocation );

	/**
	 * Finds the closest foliage instance to a location
	 *
	 * @network: Server and Client
	 *
	 * @param location - the location you want to look around
	 * @param maxDistance - max distance from the location that the foliage needs to exist (note, looks at the root location of the foliage,
	 *not the bounds)
	 * @param foliageIdentifier - find foliage that matches this tag
	 * @param out_component - the closest component of foliage, only valid if we return true
	 * @param out_instanceId - id of the foliage we want to remove, only valid if we return true
	 * @param out_instanceLocation - the location of the instance, only valid if we return true
	 * @return true if there was any foliage close by
	 **/
	bool GetClosestFoliage( const FVector& location, float maxDistance, TSubclassOf< class UFGFoliageIdentifier > foliageIdentifier,
							class UHierarchicalInstancedStaticMeshComponent*& out_component, int32& out_instanceId,
							FVector& out_instanceLocation, TEnumAsByte< EProximityEffectTypes >& out_Type );

	/**
	* Finds the closest foliage instance to a location
	*
	* @network: Server and Client
	*
	* @param location - the location you want to look around
	* @param maxDistance - max distance from the location that the foliage needs to exist (note, looks at the root location of the foliage, not the bounds)
	* @param foliageIdentifier - find foliage that matches this tag
	* @param desiredTypes - Array of types that the system should consider
	* @param out_component - the closest component of foliage, only valid if we return true
	* @param out_instanceId - id of the foliage we want to remove, only valid if we return true
	* @param out_instanceLocation - the location of the instance, only valid if we return true
	* @param out_Type - The type the system picked an instance from.
	* @return true if there was any foliage close by
	**/
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	bool GetFoliageAroundLocationOfGivenTypes( const FVector& location, float maxDistance,
											   TSubclassOf< class UFGFoliageIdentifier > foliageIdentifier,
											   TArray< TEnumAsByte< EProximityEffectTypes > > desiredTypes,
											   class UHierarchicalInstancedStaticMeshComponent*& out_component, int32& out_instanceId,
											   FVector& out_instanceLocation, TEnumAsByte< EProximityEffectTypes >& out_Type );

	/**
	 * @return true if at least one instance was found
	 */
	int32 FindInstanceByTransform( const FTransform& foliageTransform, const class UHierarchicalInstancedStaticMeshComponent* component );

	/**
	 * Finds foliage within a provided radius to a specified location.
	 * 
	 * 
	*/
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	bool GetFoliageWithinRadius( const FVector& location, float radius, TArray< int32 >& out_instanceArray,
								 TArray< FVector >& out_locationArray,
								 TArray< class UHierarchicalInstancedStaticMeshComponent* >& out_componentArray, bool includeLocations );

	bool GetFoliageWithinRadius( const FVector& location, float radius,
								 TMap< class UHierarchicalInstancedStaticMeshComponent*, TArray< int32 > >& result );

	/**
	* Finds foliage count within a provided radius to a specified location.
	*/
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	int32 GetFoliageCountWithinRadius( const FVector& location, float radius );
	
	/**
	 * @param component - UHierarchicalInstanctedStaticMeshComponent to check
	 * @param foliageIdentifier - find foliage that matches this tag
	 * @returns true if the UHierarchicalInstanctedStaticMeshComponent has the given foliageIdentifier.
	 */
	static bool HasIdentifier( const class UHierarchicalInstancedStaticMeshComponent* component, TSubclassOf<class UFGFoliageIdentifier> foliageIdentifier );

	/**
	 * @return true if the foliage type is removable
	 */
	static bool IsRemovable( const class UFoliageType* foliageType );

	// Begin FactoryStatHelpers functions
	int32 Stat_NumRemovedInstances() const;
	// End FactoryStatHelpers functions

	/**
	 * Removes a foliage instance from the hism. Handles Replication and save data.
	 * @param component: The Component that the instance will be removed from
	 * @param instanceId: The instance Id that will be removed. This is literally an index into
	 *						UInstancedStaticMeshComponent::PerInstanceSMData. It needs to be a valid index at the time of this call
	 *						(not to be confused with persistent instance id's that are defined by the foliage data cache).
	 */
	bool RemoveFoliageInstance( UHierarchicalInstancedStaticMeshComponent* component, int32 instanceId,
								FTransform* out_InstanceTransform = nullptr );
	
	/**
	 * Tries to remove a foliage instance hash (which could resolve to more than one foliage instances). This will work even if the cell
	 * that the hash belongs to isn't loaded, as the actual resolving of the instance id is delayed until the cell gets loaded.
	 */
	bool RemoveFoliageInstance( APlayerController* instigator, FFoliageInstanceStableId StableId );
	
	/**
	 * Removes all instances specified by @InstanceIds from @Component
	 * Handles replication. Every provided id is assumed to be a valid instance id in the context of @Component.
	 * Not meeting this assumption will have undefined behavior.
	 * @outRemovedInstanceTransforms will be reset and will contain the transforms of all the removed instances
	 */
	bool RemoveFoliageInstances( APlayerController* instigator, UHierarchicalInstancedStaticMeshComponent* hism,
								 const TArray< int32 >& instIds, TArray< FTransform >* outRemovedInstanceTransforms = nullptr );

	void RemoveFoliageInstanceHashes( APlayerController* instigator, FIntVector cell, const UFoliageType* foliageType, const TSet< uint32 >& instanceHashes );
	
	/**
	 * Removes foliage instances by their foliage type. Only useful for legacy foliage removals, as they migrate their legacy save data.
	 */
	UE_DEPRECATED( 5.1, "This function should only be used by legacy AFGFoliageRemoval actors, as they migrate their old save data" )
	void RecordUnregisteredRemovalLocations( const TSet< FVector >& locations, const FName& foliageTypeName );
	
	/**
	 *	Asynchronously looks up the stable instance id of a foliage instance in the foliage data cache.
	 *	A stable id can be reliably replicated and is going to represent the same actual instance on clients and servers.
	 */
	FFoliageInstanceStableId GetStableInstanceId( UHierarchicalInstancedStaticMeshComponent* Component, int32 InstanceId );
	FFoliageInstanceStableId GetStableInstanceId( UHierarchicalInstancedStaticMeshComponent* Component, const FTransform& Transform );
	
	static uint32 HashFoliageInstanceLocation( const FVector& Location );
	FIntVector GetFoliageCellForIFA( class AInstancedFoliageActor* IFA );
	static FIntVector GetFoliageCellForLocation( const FVector& Location, uint32 GridSize );
	uint32 GetFoliageGridSize() const;

	const auto& GetSaveData() const
	{
		return mSaveData;
	}

	const FFoliageRemovalSaveDataForFoliageType* GetSaveDataForCellForFoliageType( const FIntVector& cell,
																				   const UFoliageType* foliageType ) const;
	FOnNewFoliageBucketRemoved OnNewFoliageBucketRemoved;

	/**
	 * Attempts to find the HISM corresponding to a stable foliage id. This may fail if for example the foliage cell for that id isn't streamed in
	 */
	UHierarchicalInstancedStaticMeshComponent* GetHISM( const FFoliageInstanceStableId& stableId );
	UHierarchicalInstancedStaticMeshComponent* GetHISM( FIntVector cell, const UFoliageType* foliageType );
	class UFoliageType* GetFoliageType( const UHierarchicalInstancedStaticMeshComponent* hism );
protected:
	FFoliageRemovalSaveDataForFoliageType* GetSaveDataForCellForFoliageType( const FIntVector& cell, const UFoliageType* foliageType );
	FFoliageRemovalSaveDataForFoliageType& GetOrCreateSaveDataForCellForFoliageType( const FIntVector& cell,
																					 const UFoliageType* foliageType );

	const FFoliageRemovalSaveDataForFoliageType* GetUnresolvedSaveDataForCellForFoliageType( const FIntVector& cell,
																							 FName foliageTypeName ) const;
	FFoliageRemovalSaveDataForFoliageType* GetUnresolvedSaveDataForCellForFoliageType( const FIntVector& cell, FName foliageTypeName );
	FFoliageRemovalSaveDataForFoliageType& GetOrCreateUnresolvedSaveDataForCellForFoliageType( const FIntVector& cell,
																							   FName foliageTypeName );

	void TryResolveOldSavedRemovals( const TSet< FIntVector >& unresolvedCells );
	void TryResolveDeprecatedTypesInSaves( const TSet< FIntVector >& unresolvedCells );
	void TryResolveRemovalHashes( APlayerController* instigator, const TSet< FIntVector >& unresolvedCells );
	TArray< int32 > FindInstanceIdsForHashes( const UHierarchicalInstancedStaticMeshComponent* hism, const TSet< uint32 >& instanceHashes );
	/**
	 * Called when a new level was found
	 *
	 * @param level - valid level
	 */
	void LevelFound( ULevel* level );

	void CacheFoliageHISMsForLevel( ULevel* level );

	/**
	 * Take existing foliage and remove it from this level (usally when streamed in, or loaded)
	 */
	void ApplyInitialRemovals( class AInstancedFoliageActor* IFA );

	/** Called whenever a level is added to the world, used to gather more potential components to get foliage from */
	UFUNCTION()
	void OnLevelAddedToWorld( ULevel* inLevel, UWorld* inWorld );

	/** Called whenever a level is removed from the world, used to remove components that is no longer relevant for to be able to pickup */
	UFUNCTION()
	void OnPreLevelRemovedFromWorld( ULevel* inLevel, UWorld* inWorld );

	/**
	* Remove all HierarchicalInstancedStaticMeshComponents that was in the level
	* of components to be able to remove
	*
	* @param level - if null, all levels was removed from world, so just remove all components, else the level we want to remove the components in
	*/
	void RemoveComponentsInLevel( ULevel* level );

	/** 
	 * An octree with all the currently loaded foliage hisms
	 */ 
	FFoliageComponentsOctree mMeshComponentsOctree;

	
private:
	void RebuildSaveData(int32 OldGridSize, int32 NewGridSize);

	/**
	 * A Map of foliage grid cells to all the loaded IFAs.
	 */
	UPROPERTY()
	TMap<FIntVector, AInstancedFoliageActor*> mCellToLoadedIFAMap;

	UPROPERTY()
	TMap< class UHierarchicalInstancedStaticMeshComponent*, class UFoliageType* > mFoliageComponentTypeMapping;

	UPROPERTY()
	uint32 mFoliageGridSize = 0;
	
	UPROPERTY(VisibleAnywhere, SaveGame)
	uint32 mSavedFoliageGridSize = 0;

	UPROPERTY(SaveGame)
	TMap<FIntVector, FFoliageRemovalSaveDataPerCell> mSaveData;

	UPROPERTY(SaveGame)
	TMap<FIntVector, FFoliageRemovalUnresolvedSaveDataPerCell> mUnresolvedSaveData;

	TPerCellPerTypeMap<TSet<uint32>> mUnresolvedHashes;
};
