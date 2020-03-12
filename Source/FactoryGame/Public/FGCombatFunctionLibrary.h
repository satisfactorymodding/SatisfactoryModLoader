#pragma once
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGCombatFunctionLibrary.generated.h"


UCLASS()
class FACTORYGAME_API UFGCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**
	 * Try get a pawn from a damage causer in take damage
	 */
	UFUNCTION( BlueprintCallable, Category = "Damage" )
	static class AFGCharacterBase* TryGetCharacterFromDamageCauser( class AActor* damageCauser );

	/**
	 * Checks if the aggro target is within attack range of a attack
	 * @param aggroTarget - the aggro target we want to check if they are within our attack range
	 * @param attackClass - the attack that we want to check if we are within attack range for
	 * @return true if they can be attacked and hit from our pawns location
	 */
	UFUNCTION( BlueprintPure, Category = "Attack" )
	static bool IsWithinAttackRange( class APawn* attacker, class TScriptInterface< class IFGAggroTargetInterface > victim, TSubclassOf< class UFGAttack > attackClass );

	/**
	* Checks if the aggro target is within specified range
	* @param aggroTarget - the aggro target we want to check if they are within our  range
	* @param range - the range that we want to check if we are within 
	* @return true if they can be reached from this range
	*/
	UFUNCTION( BlueprintPure, Category = "Attack" )
	static bool IsWithinRange( class APawn* attacker, class TScriptInterface< class IFGAggroTargetInterface > victim, float range );

	/**
	* Uses a shape to do damage within the shape
	* @param controller - controller doing the damage
	* @param collisionShape - shape we want to check for overlapping actors
	* @param centerLocation - the location that damage origins from
	* @param damageType - damagetype for the damage
	* @param damage - how much damage
	* @param radius - radial reach of the damage
	*/
	UFUNCTION( BlueprintCallable, Category = "Damage" )
	static void DoRadialDamageWithinCollision( AController* controller, UShapeComponent* collisionShape, FVector centerLocation, TSubclassOf< class UFGDamageType > damageType, float damage, float radius );

public:
	FORCEINLINE ~UFGCombatFunctionLibrary() = default;
};