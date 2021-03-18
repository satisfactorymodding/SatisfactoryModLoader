// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "FGFoliageIdentifier.generated.h"

/**
 * Class to identify different types of foliage 
 */
UCLASS(abstract, Blueprintable)
class FACTORYGAME_API UFGFoliageIdentifier : public UObject
{
	GENERATED_BODY()
};

/**
 * Foliage that can be removed by buildings
 */
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_RemovableByBuildings : public UFGFoliageIdentifier
{
	GENERATED_BODY()
};

/**
 * Foliage that can be picked up by hand
 */
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_Pickupable : public UFGFoliageIdentifier_RemovableByBuildings
{
	GENERATED_BODY()
};

/**
 * Foliage that you need a chainsaw to be able to remove
 */
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_Chainsawable : public UFGFoliageIdentifier
{
	GENERATED_BODY()
};

/**
* xmas tree :3
*/
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_ChainsawableXmasTree : public UFGFoliageIdentifier_Chainsawable
{
	GENERATED_BODY()
};

/**
* Will be destroyed by a vehicle that runs over it
*/
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_VehicleDestroyable : public UFGFoliageIdentifier
{
	GENERATED_BODY()
};

/**
* Will be destroyed by explosives
*/
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_ExplosiveDestroyable : public UFGFoliageIdentifier
{
	GENERATED_BODY()
};
