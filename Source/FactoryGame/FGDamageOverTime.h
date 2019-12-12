#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Object.h"
#include "FGDamageOverTime.generated.h"

/**
 * Shareable info about damage over time 
 */
UCLASS( abstract, Blueprintable )
class UFGDamageOverTime : public UObject
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGDamageOverTime();

	/**
	 * Returns the the damage interval of the dot
	 * @return -1 if dotClass is nullptr
	*/
	UFUNCTION( BlueprintPure, Category = "Dot" )
	static float GetDamageInterval( TSubclassOf< UFGDamageOverTime > dotClass );

	/**
	 * Returns how much damage the dot does every interval
	 * @return The damage to take; no damage if dotClass is nullptr.
	*/
	UFUNCTION( BlueprintPure, Category = "Dot" )
	static float GetDamageAmount( TSubclassOf< UFGDamageOverTime > dotClass );

	/**
	 * Returns the damage type of the dot-class
	 * @return nullptr if dotClass is nullptr
	*/
	UFUNCTION( BlueprintPure, Category = "Dot" )
	static TSubclassOf< class UFGDamageType > GetDamageClass( TSubclassOf< UFGDamageOverTime > dotClass );

	/**
	 * Returns true if this dot-class should be applied to the actor
	 * @return false if dotClass or actor is nullptr
	*/
	UFUNCTION( BlueprintPure, Category = "Dot" )
	static bool ShouldBeAppliedToActor( TSubclassOf< UFGDamageOverTime > dotClass, class AActor* actor );

	/** Accessors */
	FORCEINLINE float GetDamageInterval() const{ return mDamageInterval; }
	FORCEINLINE float GetDamageAmount() const{ return mDamageAmount; }
	FORCEINLINE TSubclassOf< class UFGDamageType > GetDamageClass() const{ return mDamageClass; }

	/**
	* Return true if we want this damage over time to be applied to the specified actor
	*
	* @param actor - the actor we want to check if we want to apply the damage over time on
	* @return false if actor is nullptr
	*/
	bool ShouldBeAppliedToActor( class AActor* actor ) const;
protected:
	/** How often should we damage actors inside of this cloud (in seconds) */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	float mDamageInterval;

	/** How much damage should the actor take each time it receives damage */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	float mDamageAmount;

	/** What type of damage should we give the character */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	TSubclassOf< class UFGDamageType > mDamageClass;

	/** Only deal damage to subclasses of these actor classes */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	TArray< TSubclassOf< class AActor > > mActorFilter;
};
