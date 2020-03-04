#pragma once
#include "Engine/StaticMesh.h"
#include "Engine/Level.h"
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGFoliageRemovalSubsystem.generated.h"

#define DEBUG_FOLIAGE_REMOVAL_SUBSYSTEM ( ( UE_BUILD_SHIPPING == 0 ) && 1 )

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
	UFUNCTION(BlueprintPure, Category = "Foliage" )
	class AFGFoliageRemoval* GetFoliageRemovalActor( class UHierarchicalInstancedStaticMeshComponent* fromComponent ) const;

	/** Alternative way of getting a foliage removal actor */
	class AFGFoliageRemoval* GetFoliageRemovalActor( const FName& levelName, const FName& foliageTypeName ) const;

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
	UFUNCTION(BlueprintCallable,Category="Foliage")
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
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	bool GetClosestFoliage( const FVector& location, float maxDistance, TSubclassOf<class UFGFoliageIdentifier> foliageIdentifier, class UHierarchicalInstancedStaticMeshComponent*& out_component, bool isLocalSpace, int32& out_instanceId, FVector& out_instanceLocation );

	/**
	 * Finds the closest foliage instance to a location in a specified component
	 *
 	 * @network: Server and Client
	 *
	 * @param location - the location you want to look around
	 * @param maxDistance - max distance from the location that the foliage needs to exist (note, looks at the root location of the foliage, not the bounds)
	 * @param component - the component we want to search for foliage
	 * @param isLocalSpace - set this to true if location is in localspace
	 * @param out_instanceId - id of the foliage we want to remove, only valid if we return true
	 * @param out_instanceLocation - the location of the instance, only valid if we return true
	 * @return true if there was any foliage close by
	**/
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	bool GetClosestFoliageForComponent( const FVector& location, float maxDistance, const class UHierarchicalInstancedStaticMeshComponent* component, bool isLocalSpace, int32& out_instanceId, FVector& out_instanceLocation );

	/**
	 * Takes several locations into considerations and find the closest foliage closest to those locations. Use this when you want to get several
	 * foliage locations instead of using GetClosestFoliage several times. As this takes into consideration the locations passed in. So once instance has
	 * been added once to the array, it won't be added again
	 *
	 * @param locations - the locations that we want to find foliage close to
	 * @param maxDistance - maximum distance to any foliage
	 * @param component - component to search in
	 * @param isLocalSpace - set this to true if the locations is in local-space
	 * @param out_instanceArray - id's in component for all the foliage instances
	 */
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	void GetClosestFoliageArrayForComponent( const TArray<FVector>& locations, float maxDistance, const class UHierarchicalInstancedStaticMeshComponent* component, bool isLocalSpace, TArray<int32>& out_instanceArray );

	/**
	 * Finds foliage within a provided radius to a specified location.
	 * 
	 * 
	*/
	UFUNCTION( BlueprintCallable, Category = "Foliage" )
	bool GetFoliageWithinRadius( const FVector& location, float radius, bool isLocalSpace, TArray<int32>& out_instanceArray, TArray<FVector>& out_locationArray, TArray<class UHierarchicalInstancedStaticMeshComponent*>& out_componentArray );

	/**
	 * @param component - UHierarchicalInstanctedStaticMeshComponent to check
	 * @param foliageIdentifier - find foliage that matches this tag
	 * @returns true if the UHierarchicalInstanctedStaticMeshComponent has the given foliageIdentifier.
	 */
	UFUNCTION( BlueprintCallable, Category = "Foliage" ) 
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
	 * @return true if the static mesh is removable
	 */
	virtual bool IsRemovable( class UStaticMesh* staticMesh ) const;

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
	class AFGFoliageRemoval* SpawnFoliageRemovalActor( const FBox& levelBounds, const FName& levelName, class UFoliageType* foilageType, class UHierarchicalInstancedStaticMeshComponent* meshComponent );

	/** Called whenever a level is added to the world, used to gather more potential components to get foliage from */
	UFUNCTION()
	void OnLevelAddedToWorld( ULevel* inLevel, UWorld* inWorld );

	/** Called whenever a level is removed from the world, used to remove components that is no longer relevant for to be able to pickup */
	UFUNCTION()
	void OnLevelRemovedFromWorld( ULevel* inLevel, UWorld* inWorld );

	/**
	 * Take existing foliage and remove it from this level (usally when streamed in, or loaded)
	 *
	 * @param inLevel - must be 
	 */
	void RemoveFoliageFromLevel( ULevel* inLevel );

	/**
	 * Searches for all HierarchicalInstancedStaticMeshComponents in the level, and adds them to the potential list
	 * of components to be able to remove
	 *
	 * @param level - must be valid, the level we want to gather components from
	 */
	void SetupFoliageRemovalsForLevel( ULevel* level );

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
	/** SERVER ONLY: The maps that doesn't have any removable foliage on it  (@todonow: Remove?)*/
	TArray< FName > mMapsWithNoRemovableFoliage;

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

	/** Keep track of what foliage removal actors is in each level (FName is the name of the level) */
	TMultiMap< FName, class AFGFoliageRemoval* > mFoliageRemovalsInLevels; // @todogc: Verify that this is safe have without UPROPERTY

	/** Keep track of what maps has spawned their foliage removals */
	TArray< FName > mMapsWithSpawnedFoliageRemovals;

	/** All foliage mesh components that have potential for contain instances to remove */
	TArray<class UHierarchicalInstancedStaticMeshComponent*> mFoilageMeshComponents; // @todogc: Verify that this is safe have without UPROPERTY

public:
	FORCEINLINE ~AFGFoliageRemovalSubsystem() = default;
};
