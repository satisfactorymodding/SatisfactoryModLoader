// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGFoliageResourceUserData.h"
#include "FGFoliageRemovalSubsystem.generated.h"

#define DEBUG_FOLIAGE_REMOVAL_SUBSYSTEM ( UE_BUILD_SHIPPING == 0 )


struct FoliageInstanceData
{
	FoliageInstanceData( int index, int id, FTransform transform, class UHierarchicalInstancedStaticMeshComponent* component );

	/**
	* Index into the FoliageTypeData::foliageInstances array, for replication
	*/
	int index = 0;

	/**
	* ID into the HISM internal data structure
	*/
	int id = 0;

	/**
	* World placement
	*/
	FTransform transform;

	/**
	* The component to which the id applies
	*/
	TWeakObjectPtr< class UHierarchicalInstancedStaticMeshComponent > component;

	/**
	 * True if this instance is removed
	 */
	bool isRemoved = false;
};

using FoliageLocationToDataMultiMap = TMultiMap< FVector, FoliageInstanceData* >;

struct FoliageTypeData
{
	/**
	* Foliage instance data, sorted on location
	*/
	TArray< FoliageInstanceData > foliageInstances;

	/**
	* Map for quick lookup by location
	*/
	FoliageLocationToDataMultiMap foliageLocationToDataMultiMap;

	/**
	* The components referenced by instances in this data
	*/
	TSet< TWeakObjectPtr< class UHierarchicalInstancedStaticMeshComponent > > components;

	class AFGFoliageRemoval* foliageRemoval = nullptr;
};

using FoliageTypeToDataMap = TMap< FName, FoliageTypeData >;

struct LevelFoliageData
{
	/**
	* Foliage-entry data mapped by foliage-type name
	*/
	FoliageTypeToDataMap foliageTypeToDataMap;

	bool isCacheBuilt = false;

	bool isLevelLoaded = false;
};

using LevelFoliageDataMap = TMap< FName, LevelFoliageData >;


UCLASS()
class FACTORYGAME_API AFGFoliageRemovalSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	/** ctor */
	AFGFoliageRemovalSubsystem();

	// Begin AActor interface
	virtual void Destroyed() override;
	// End AActor interface

	/** Called to initialize the subsystem and spawn actors for the levels that's already loaded when we was created */
	void Init();

	/** Get the foliage removal subsystem, this should always return something unless you call it really early */
	static AFGFoliageRemovalSubsystem* Get( UWorld* world );

	/** Get the foliage removal subsystem from a world context, this should always return something unless you call it really early */
	UFUNCTION(BlueprintPure, Category="Foliage", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGFoliageRemovalSubsystem* GetFoliageRemovalSubsystem( UObject* worldContext );
	
	/** Get the foliage removal actor that is associated with the component */
	class AFGFoliageRemoval* FindFoliageRemovalActorByComponent( class UHierarchicalInstancedStaticMeshComponent* component ) const;

	/** Alternative way of getting a foliage removal actor */
	class AFGFoliageRemoval* FindFoliageRemovalActor( const FName& levelName, const FName& foliageTypeName );

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
	bool GetLookAtFoliage( const FVector& viewLocation, const FVector& endViewLocation, TSubclassOf<class UFGFoliageIdentifier> foliageIdentifier, class UHierarchicalInstancedStaticMeshComponent*& out_component, int32& out_instanceId, FVector& out_instanceLocation );

	/**
	* Finds the closest foliage instance to a location
	*
	* @network: Server and Client
	*
	* @param location - the location you want to look around
	* @param maxDistance - max distance from the location that the foliage needs to exist (note, looks at the root location of the foliage, not the bounds)
	* @param foliageIdentifier - find foliage that matches this tag
	* @param out_component - the closest component of foliage, only valid if we return true
	* @param out_instanceId - id of the foliage we want to remove, only valid if we return true
	* @param out_instanceLocation - the location of the instance, only valid if we return true
	* @return true if there was any foliage close by
	**/
	bool GetClosestFoliage( const FVector& location, float maxDistance, TSubclassOf<class UFGFoliageIdentifier> foliageIdentifier, class UHierarchicalInstancedStaticMeshComponent*& out_component, int32& out_instanceId, FVector& out_instanceLocation, TEnumAsByte<EProximityEffectTypes> &out_Type );

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
	bool GetFoliageAroundLocationOfGivenTypes( const FVector& location, float maxDistance, TSubclassOf< class UFGFoliageIdentifier > foliageIdentifier, TArray< TEnumAsByte< EProximityEffectTypes > > desiredTypes, class UHierarchicalInstancedStaticMeshComponent*& out_component, int32& out_instanceId, FVector& out_instanceLocation, TEnumAsByte< EProximityEffectTypes > &out_Type);

	/**
	 * @return true if at least one instance was found
	 */
	int32 FindInstanceByTransform( const FTransform& foliageTransform, const class UHierarchicalInstancedStaticMeshComponent* component, const FName& levelName, const FName& foliageTypeName );

	/**
	 * Takes the foliage component and checks if it is indeed in a cave level or not.
	 */
	UFUNCTION(BlueprintPure	, Category = "Foliage")
	static bool IsFoliageComponentInACave(UHierarchicalInstancedStaticMeshComponent* TestComponent);
	
	/**
	 * Finds foliage within a provided radius to a specified location.
	 * 
	 * 
	*/
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	bool GetFoliageWithinRadius( const FVector& location, float radius, TArray<int32>& out_instanceArray, TArray<FVector>& out_locationArray, TArray<class UHierarchicalInstancedStaticMeshComponent*>& out_componentArray, bool includeLocations );

	bool GetFoliageWithinRadius( const FVector& location, float radius, TMap< class UHierarchicalInstancedStaticMeshComponent*, TArray< int32 > >& result );

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
	bool HasIdentifier( const class UHierarchicalInstancedStaticMeshComponent* component, TSubclassOf<class UFGFoliageIdentifier> foliageIdentifier );

	/**
	 * Register a foliage removal actor with the subsystem, this should not be used except from the AFGFoilageRemoval actor
	 *
	 * @param actor - need to be valid and not already registered
	 */
	void Register( class AFGFoliageRemoval* actor );

	/**
	 * Unregisters a foliage removal actor from the subsystem, this should not be used except from the AFGFoilageRemoval actor
	 *
	 * @param actor - need to be valid and registered
	 */
	void UnRegister( class AFGFoliageRemoval* actor );

	/**
	 * @return true if the foliage type is removable
	 */
	bool IsRemovable( const class UFoliageType* foliageType ) const;

	// Begin FactoryStatHelpers functions
	int32 Stat_NumRemovedInstances() const;
	// End FactoryStatHelpers functions

protected:
	/**
	 * Called when a new level was found
	 *
	 * @param level - valid level
	 */
	void LevelFound( ULevel* level );

	void BuildFoliageRemovalCache( ULevel* level, struct LevelFoliageData& levelFoliageData );

	/**
	 * Searches for all HierarchicalInstancedStaticMeshComponents in the level, and adds them to the potential list
	 * of components to be able to remove
	 *
	 * @param level - must be valid, the level we want to gather components from
	 */
	void SetupFoliageRemovalsForLevel( ULevel* level, struct LevelFoliageData& levelFoliageData, bool firstLoad );

	/**
	 * Take existing foliage and remove it from this level (usally when streamed in, or loaded)
	 *
	 * @param inLevel - must be 
	 */
	void ApplyInitialRemovals_Server( const FName& levelName, bool firstLoad );

	/**
	 * Mark the level as it has no foliage actor
	 */
	void MarkAsLevelAsWithoutRemovableFoliage( const FName& levelName );

	/**
	 * Mark the level as it has spawned foliage actors
	 */
	void MarkAsLevelAsSpawnedRemovableFoliage( const FName& levelName );

	/**
	 * @return true if the level has spawned a foliage removal actor
	 */
	bool HasSpawnedFoliageActor( const FName& levelName ) const;
	
	/**
	 * Spawn a foliage removal actor
	 * SERVER ONLY!
	 *
	 * @param levelBounds - the bounds of the level we want to spawn the actor in (used for net cull distance + location)
	 * @param levelName - the name of the level that the actor should handle spawning for
	 * @param meshComponent - the component that the actor is responsible for removing foliage for
	 * @return return a new foliage removal actor if one was created (client will always return nullptr)
	 **/
	class AFGFoliageRemoval* SpawnFoliageRemovalActor( const FBox& levelBounds, const FName& levelName, class UFoliageType* foilageType, class UHierarchicalInstancedStaticMeshComponent* meshComponent, bool firstLoad );

	/** Called whenever a level is added to the world, used to gather more potential components to get foliage from */
	UFUNCTION()
	void OnLevelAddedToWorld( ULevel* inLevel, UWorld* inWorld );

	/** Called whenever a level is removed from the world, used to remove components that is no longer relevant for to be able to pickup */
	UFUNCTION()
	void OnLevelRemovedFromWorld( ULevel* inLevel, UWorld* inWorld );

	/**
	* Remove all HierarchicalInstancedStaticMeshComponents that was in the level
	* of components to be able to remove
	*
	* @param level - if null, all levels was removed from world, so just remove all components, else the level we want to remove the components in
	*/
	void RemoveComponentsInLevel( ULevel* level );

	/**
	 * Get the name of the level
	 *
	 * @param level - must be valid
	 * @return the name of the level
	 */
	FName GetLevelName( ULevel* level ) const;

	/**
	 * If the level contains a level bounds actor, then get the center of the level bounds, else, calculate it (expensive)
	 * SERVER ONLY!
	 *
	 * @param level - must be valid
	 */
	FVector GetLevelCenter( ULevel* level ) const;

	/**
	 * If the level contains a level bounds actor, then get the bounds of the level, else, calculate it (expensive)
	 * SERVER ONLY!
	 *
	 * @param level - must be valid
	 */
	FBox GetLevelBounds( ULevel* level ) const;
protected:
	/** Data that is waiting for it's foliage removal actor to be replicated */
	struct FPendingLevelData
	{
		FPendingLevelData( class UFoliageType* foliage, const FName& levelName, class UHierarchicalInstancedStaticMeshComponent* component ) :
			Foliage( foliage ),
			LevelName( levelName ),
			Component( component )
		{
		}

		// To be able to use Contains/Find etc.
		bool operator==( const FPendingLevelData& other ) const
		{
			return Foliage == other.Foliage && LevelName == other.LevelName && Component == other.Component;
		}

		// Need this pair to identify the level actor
		class UFoliageType* Foliage; // @todogc: Verify that this is safe have without UPROPERTY
		FName LevelName;

		// Component we should assign to the actor when it becomes relevant
		class UHierarchicalInstancedStaticMeshComponent* Component; // @todogc: Verify that this is safe have without UPROPERTY

	};
	
	/** Store level data for non relevant foliage removal actors until they become relevant  */
	TArray< FPendingLevelData > mDataForNonRelevantFoliageRemovals;

	/** Keep track of what maps has spawned their foliage removals */
	TSet< FName > mMapsWithSpawnedFoliageRemovals;

	/** SERVER ONLY: The maps that doesn't have any removable foliage on it  (@todonow: Remove?)*/
	TSet< FName > mMapsWithNoRemovableFoliage;

	/** All foliage mesh components that have potential for contain instances to remove */
	TArray< class UHierarchicalInstancedStaticMeshComponent* > mFoilageMeshComponents;

	TSet< ULevel* > mLoadedLevels;

public:
	LevelFoliageDataMap mLevelFoliageDataMap;
};
