// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "FGDamageOverTime.generated.h"

class UFGDamageType;

/**
 * Shareable info about damage over time 
 */
UCLASS( abstract, Blueprintable )
class FACTORYGAME_API UFGDamageOverTime : public UObject
{
	GENERATED_BODY()
public:
	UFGDamageOverTime();

	/**
	 * Returns the the damage interval of the dot
	 * @return -1 if dotClass is nullptr
	*/
	UFUNCTION( BlueprintPure, Category = "Dot" )
	static float GetDamageInterval( TSubclassOf< UFGDamageOverTime > dotClass );

	/**
	 * Returns the damage types of the dot-class
	 * @return empty array if dotClass is nullptr
	*/
	UFUNCTION( BlueprintPure, Category= "Dot" )
	static TArray< UFGDamageType* > GetDamageTypes( TSubclassOf< UFGDamageOverTime > dotClass );

	/**
	 * Returns true if this dot-class should be applied to the actor
	 * @return false if dotClass or actor is nullptr
	*/
	UFUNCTION( BlueprintPure, Category = "Dot" )
	static bool ShouldBeAppliedToActor( TSubclassOf< UFGDamageOverTime > dotClass, class AActor* actor );

	/** Accessors */
	FORCEINLINE float GetDamageInterval() const { return mDamageInterval; }
	FORCEINLINE TArray< UFGDamageType* > GetDamageTypes() const { return mDamageTypes; }

	/**
	* Return true if we want this damage over time to be applied to the specified actor
	*
	* @param actor - the actor we want to check if we want to apply the damage over time on
	* @return false if actor is nullptr
	*/
	bool ShouldBeAppliedToActor( class AActor* actor ) const;

	UPROPERTY( EditDefaultsOnly )
	bool mIsRelevantToPeakGameplayAchievement = false;
	
protected:
	/** How often should we damage actors inside of this cloud (in seconds) */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	float mDamageInterval;

	UPROPERTY(EditDefaultsOnly, Instanced, Category= "Damage", meta = ( AllowAbstract=true ) )
	TArray< UFGDamageType* > mDamageTypes;

	/** Only deal damage to subclasses of these actor classes */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	TArray< TSubclassOf< class AActor > > mActorFilter;
	
};
