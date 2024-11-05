// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGItemPickup.h"
#include "FGCrate.h"
#include "FGItemPickup_Spawnable.generated.h"

UCLASS( NotPlaceable )
class FACTORYGAME_API AFGItemPickup_Spawnable : public AFGItemPickup
{
	GENERATED_BODY()
public:
	AFGItemPickup_Spawnable();

	//~ Begin AActor interface
	virtual void PostLoad() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor interface

	//~ Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	virtual bool NeedTransform_Implementation() override;
	//~ End IFGSaveInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	//~ End IFGUseableInterface

	//~ Begin AFGItemPickup interface
	virtual bool ShouldBeRegisteredForPickup() const override;
	//~ End AFGItemPickup interface
	
	/**
	* Creates a item drop in the world
	* NOTE: Server only
	*
	* @param world - the world we try to spawn the item drop in
	* @param item - the item stack we want to drop
	* @param spawnLocation - the location where we want to spawn the item drop in
	* @param spawnRotation - the rotation where we want to spawn the item drop with
	* @param itemDropClass - what class of item drop do we want to spawn, nullptr means default class that's specified in FGResourceSettings
	*
	* @return a valid item drop if everything went well
	*/
	static AFGItemPickup_Spawnable* CreateItemDrop( UWorld* world, const FInventoryStack& item, FVector spawnLocation, FRotator spawnRotation, TSubclassOf< AFGItemPickup_Spawnable> itemDropClass = nullptr, ULevel* spawnLevelOverride = nullptr, FName spawnNameOverride = NAME_None )
	{
		return CreateItemDrop( nullptr, world, item, spawnLocation, spawnRotation, itemDropClass, spawnLevelOverride, spawnNameOverride );
	}
	UFUNCTION( BlueprintCallable, Category = "ItemDrop", meta = ( DefaultToSelf = "worldContext" ) )
	static AFGItemPickup_Spawnable* CreateItemDrop( UFGInventoryComponent* inventoryComponent, const FInventoryStack& item, FVector spawnLocation, FRotator spawnRotation, TSubclassOf< AFGItemPickup_Spawnable> itemDropClass = nullptr, ULevel* spawnLevelOverride = nullptr, FName spawnNameOverride = NAME_None )
	{
		return CreateItemDrop( inventoryComponent, inventoryComponent->GetWorld(), item, spawnLocation, spawnRotation, itemDropClass, spawnLevelOverride, spawnNameOverride );
	}
	/**
	* @copydoc AFGItemPickup_Spawnable::CreateItemDrop
	*/
	static AFGItemPickup_Spawnable* CreateItemDrop( UFGInventoryComponent* inventoryComponent, UWorld* world, const FInventoryStack& item, FVector spawnLocation, FRotator spawnRotation, TSubclassOf< AFGItemPickup_Spawnable> itemDropClass = nullptr, ULevel* spawnLevelOverride = nullptr, FName spawnNameOverride = NAME_None );

	UFUNCTION()
	void OnColorUpdated( int32 index );

	/**
	* Will drop item at location if there are no stack found on location that have enough space available.
	*/
	UFUNCTION( BlueprintCallable, Category = "ItemDrop", meta = ( DefaultToSelf = "worldContext" ) )
	static AFGItemPickup_Spawnable* AddItemToWorldStackAtLocation( UFGInventoryComponent* inventoryComponent, const FInventoryStack& item, const FVector& spawnLocation, const FRotator& spawnRotation, TSubclassOf< AFGItemPickup_Spawnable > itemDropClass = nullptr );

	/**
	 * @copydoc AFGItemPickup_Spawnable::CreateItemDropsInCylinder
	 */
	static void CreateItemDropsInCylinder( class UWorld* world, const TArray<FInventoryStack>& items, FVector aroundLocation, float sphereRadius, const TArray<class AActor*>& actorsToIgnore, TArray<class AFGItemPickup_Spawnable*>& out_itemDrops, TSubclassOf<class AFGItemPickup_Spawnable> itemDropClass = nullptr );

	/**
	* Spawns a crate that contains and inventory that can be opened by the player.
	*
	* @param world - the world we try to spawn the item drop in
	* @param items - the items we want to drop in the crate.
	* @param spawnLocation - the location where we want to spawn the item drop in
	* @param crateClass - crate class to use, if null then we take the default one in FactorySettings.
	*/
	static void SpawnInventoryCrate( class UWorld* world, const TArray< FInventoryStack >& items, FVector spawnLocation, const TArray<class AActor*>& actorsToIgnore, class AFGCrate*& out_Crate, EFGCrateType crateType = EFGCrateType::CT_DismantleCrate, TSubclassOf< AFGCrate > crateClass = nullptr );
	
	/**
	 * Creates item drops in a sphere in the world around a location
	 * NOTE: Server only
	 *
	 * @param world - the world we try to spawn the item drops in
	 * @param items - the item stack we want to drop
	 * @param aroundLocation - the location where we want to spawn the item drop in
	 * @param sphereRadius - the rotation where we want to spawn the item drop with
	 * @param itemDropClass - what class of item drop do we want to spawn, nullptr means default class that's specified in FGResourceSettings
	 *
	 * @return a valid item drop if everything went well
	 */
	UFUNCTION( BlueprintCallable, Category = "ItemDrop", meta = ( DefaultToSelf = "worldContext" ) )
	static void CreateItemDropsInCylinder( class UObject* worldContext, const TArray<FInventoryStack>& items, FVector aroundLocation, float sphereRadius, const TArray<class AActor*>& actorsToIgnore, TArray<class AFGItemPickup_Spawnable*>& out_itemDrops, TSubclassOf<class AFGItemPickup_Spawnable> itemDropClass = nullptr )
	{
		AFGItemPickup_Spawnable::CreateItemDropsInCylinder( worldContext->GetWorld(), items, aroundLocation, sphereRadius, actorsToIgnore, out_itemDrops, itemDropClass );
	}

	/**
	 * @copydoc AFGItemPickup_Spawnable::FindGroundLocationAndRotation
	 */
	static void FindGroundLocationAndRotation( class UWorld* world, FVector fromLocation, const TArray<AActor*>& actorsToIgnore, FVector& out_location, FRotator& out_rotation );

	/**
	 * Find the ground above/below the specified location and how to rotate a mesh to align with it
	 *
	 * @param world - the world we try to find the ground in
	 * @param fromLocation - the location we want to try to find the ground above/below
	 * @param actorsToIgnore - the actors we want to ignore when trying to find the ground
	 * @param out_location - location to put the item on the ground
	 * @param out_rotation - rotation to put the item on the ground
	 *
	 * @return a valid item drop if everything went well
	*/
	UFUNCTION( BlueprintCallable, Category = "ItemDrop", meta = ( DefaultToSelf = "worldContext" ) )
	static void FindGroundLocationAndRotation( class UObject* worldContext, FVector fromLocation, const TArray<AActor*>& actorsToIgnore, FVector& out_location, FRotator& out_rotation )
	{
		FindGroundLocationAndRotation( worldContext->GetWorld(), fromLocation, actorsToIgnore, out_location, out_rotation );
	}

	/**
	* Finds a suitable drop location in front of an actor, taking into account roofs, walls and such.
	*
	* @param world - the world we try to find the ground in
	* @param fromLocation - the location we want to try to find the ground above/below
	* @param actorsToIgnore - the actors we want to ignore when trying to find the ground
	* @param out_location - location to put the item on the ground
	* @param out_rotation - rotation to put the item on the ground
	*
	* @return a valid item drop if everything went well
	*/
	UFUNCTION( BlueprintCallable, Category = "ItemDrop", meta = ( DefaultToSelf = "worldContext" ) )
	static void FindGroundLocationInfrontOfActor( const AActor* sourceActor, float offsetLength, const FInventoryStack& item, FVector& out_location, FRotator& out_rotation );

	/** Place to play spawn effect */
	UFUNCTION( BlueprintImplementableEvent, Category = "ItemDrop" )
	void PlaySpawnEffect();

	/** Audio event to spawn on pickup */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class UAkAudioEvent* mPickupSound;

	virtual void PlayPickupEffectImpl() override;

protected:
	/** Generates spheres in a capsule around the radius */
	static bool GenerateSpheresInCapsule( FVector center, float radius, float innerRadius, TArray<FVector>& out_result );
protected:
	/** The mesh to represent the item */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class UStaticMeshComponent* mMeshComponent;

	/** Marker on the map associated with this pickup */
	UPROPERTY( SaveGame )
	class AFGItemPickupMarker* mPickupMarker;
private:
	/** Should we play a spawn effect? */
	UPROPERTY( SaveGame )
	bool mPlaySpawnEffect;
};