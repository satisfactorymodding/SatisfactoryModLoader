// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGTakeDamageDependency.generated.h"

/** We only care about damage events where a player is involved somehow. */
UENUM()
enum class ETakeDamagePlayerInteraction : uint8
{
	Any					UMETA( DisplayName = "Any" ),
	PlayerWasDamaged	UMETA( DisplayName = "Player Was Damaged" ),
	PlayerDealtDamage	UMETA( DisplayName = "Player Dealt Damage" ),
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGTakeDamageDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
public:
	ETakeDamagePlayerInteraction GetInteractionType() const { return mDamageInteraction; }
	const TArray< TSubclassOf< class UDamageType > >& GetDamageTypes() const { return mDamageTypes; }
	const TArray< TSubclassOf< class AActor > >& GetActorClassContextFilter() const { return mActorClassContextFilter; }
	bool IsOnlyKillingblow() const { return mOnlyKillingBlow; }
	
#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** We only care about damage events that involve a player somehow. This controls whether we trigger based on dealing damage to something, receiving damage from something, or both. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	ETakeDamagePlayerInteraction mDamageInteraction;
	
	/** What damage types trigger this dependency, if not specified then any damage will trigger it. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	TArray< TSubclassOf< class UDamageType > > mDamageTypes;

	/** Recipient / Source of the damage, depending on the interaction. If specified, will only trigger if the player dealt damage to / took damage from these actor classes. For example in case of PVP you can specify FGCharacterPlayer. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	TArray< TSubclassOf< class AActor > > mActorClassContextFilter;

	/** Whether or not to trigger this dependency only for a killing blow. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	bool mOnlyKillingBlow;
};
