// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAmmoType.h"
#include "FGAmmoTypeHomingBase.generated.h"

UENUM()
enum class EHomingPriority : uint8
{
	HP_None		UMETA( displayName = "None" ),
	
	HP_Low		UMETA( displayName = "Low" ),
	HP_Medium	UMETA( displayName = "Medium" ),
	HP_High		UMETA( displayName = "High" ),

	HP_Num		UMETA( Hidden )
};

/** A type of actor which can be hit by homing ammo. */
USTRUCT( BlueprintType )
struct FFGHomingTarget
{
	GENERATED_BODY()

	FFGHomingTarget()
		: HomingPriority( EHomingPriority::HP_Medium )
	{
	}

	/** What actor class we want to be able to hit. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< AActor > ActorClass;

	/** What priority level this actor should have. */
	UPROPERTY( EditDefaultsOnly )
	EHomingPriority HomingPriority;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAmmoTypeHomingBase : public UFGAmmoType
{
	GENERATED_BODY()

public:
	UFGAmmoTypeHomingBase();

	/** Generates a hitresult towards a homing target. Returns true if successful. If unsuccessful, sets out_hitResult to the result from a line trace towards mFiringDirection. */
	UFUNCTION( BlueprintPure, Category = "Ammunition|Homing")
	bool GetNewHomingTarget( FHitResult& out_hitResult ) const;

	/** Whether or not we can hit the specified target with homing. */
	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|Homing" )
	bool CanHomingHitTarget( const AActor* target ) const;
    
    /** Gets the priority level for the specified actor. Higher priority targets are prioritized by the homing shot. */
    UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|Homing" )
    EHomingPriority GetPriorityLevelForActor( const AActor* actor ) const;

private:
    /** Extent of the box we overlap with when looking for targets along the aim direction. */
    UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Homing" )
    float mHomingOverlapSize;

	/** Targets outside of this angle from where we're aiming wont be targeted by the homing. Will ignore if <= 0. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Homing" )
	float mHomingAngleLimit;

	/** Additional types of actors which should be possible to hit. Mainly intended for exceptions and outliers. Can also be used to override priority for certain classes. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Homing" )
	TArray< FFGHomingTarget > mHomingOverrideTargets;
};
