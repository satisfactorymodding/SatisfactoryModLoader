// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGC4Explosive.generated.h"

UCLASS()
class FACTORYGAME_API AFGC4Explosive : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGC4Explosive();

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Exoplodes this actor. Vilken jaevla smaell! */
	void Detonate();

	/** Play the sound and particle effect for this explosion */
	UFUNCTION( BlueprintNativeEvent, BlueprintCosmetic, Category = "Effects" )
	void PlayExplosionEffects();

	/** Called when the server has blown this explosive */
	UFUNCTION()
	void OnRep_IsDetonated();

protected:
	/** Base damage used for the radial apply damage */
	UPROPERTY( EditDefaultsOnly, Category = "Explosive" )
	float mBaseDamage;

	/** Damage radius used for the radial apply damage */
	UPROPERTY( EditDefaultsOnly, Category = "Explosive" )
	float mDamageRadius;

	/** Damage type used for the radial apply damage */
	UPROPERTY( EditDefaultsOnly, Category = "Explosive" )
	TSubclassOf< class UDamageType > mDamageType;

	/** Tells client to blow this shit up */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsDetonated )
	bool mIsDetonated;


public:
	FORCEINLINE ~AFGC4Explosive() = default;
};
