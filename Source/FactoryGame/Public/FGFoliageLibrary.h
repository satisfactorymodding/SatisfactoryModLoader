// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"
#include "FGInventoryComponent.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGFoliageLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGFoliageLibrary : public UObject
{
	GENERATED_BODY()

public:
	/** 
	* Returns true of the player has space for the items in the component
	*
	* @param character - The player owning the inventory
	* @oaram meshComponent - MeshComponent for the foliage to be added to the inventory
	* @return true of player has space in inventory for foliage pickup
	*/
	static bool HasPlayerInventorySpaceFor( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent );
	
	/**
	* Returns true of the player has space for the items in the component
	*
	* @param character - The player owning the inventory
	* @oaram meshComponent - MeshComponent for the foliage to be added to the inventory
	* @param out_validStacks - The stacks that can be added to the inventory
	* @return true of player has space in inventory for foliage pickup
	*/
	static bool CheckInventorySpaceAndGetStacks( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent, TArray<struct FInventoryStack>& out_inventoryStacks );

	/**
	 * Tries to add the foliage pickup from the MeshComponent to the Player inventory. 
	 *
	 * @param character - The player owning the inventory
	 * @oaram meshComponent - MeshComponent for the foliage to be added to the inventory
	 * @return true of player had space in inventory for foliage pickup and it was added to it
	*/
	static bool TryAddToPlayerInventory( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent );

	

protected:

	/** Returns an array of stacks that can be added to the player inventory. */
	static TArray<FInventoryStack> GetValidInventoryStacks( class UFGFoliageResourceUserData* foliageUserData );
};
