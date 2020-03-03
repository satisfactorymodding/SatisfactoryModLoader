#pragma once
#include "UObject/Class.h"

#include "Object.h"
#include "FGFoliageIdentifier.generated.h"

/**
 * Class to identify different types of foliage 
 */
UCLASS(abstract, Blueprintable)
class FACTORYGAME_API UFGFoliageIdentifier : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier() = default;
};

/**
 * Foliage that can be removed by buildings
 */
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_RemovableByBuildings : public UFGFoliageIdentifier
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier_RemovableByBuildings() = default;
};

/**
 * Foliage that can be picked up by hand
 */
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_Pickupable : public UFGFoliageIdentifier_RemovableByBuildings
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier_Pickupable() = default;
};

/**
 * Foliage that you need a chainsaw to be able to remove
 */
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_Chainsawable : public UFGFoliageIdentifier
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier_Chainsawable() = default;
};

/**
* xmas tree :3
*/
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_ChainsawableXmasTree : public UFGFoliageIdentifier_Chainsawable
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier_ChainsawableXmasTree() = default;
};

/**
* Will be destroyed by a vehicle that runs over it
*/
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_VehicleDestroyable : public UFGFoliageIdentifier
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier_VehicleDestroyable() = default;
};

/**
* Will be destroyed by explosives
*/
UCLASS()
class FACTORYGAME_API UFGFoliageIdentifier_ExplosiveDestroyable : public UFGFoliageIdentifier
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFoliageIdentifier_ExplosiveDestroyable() = default;
};
