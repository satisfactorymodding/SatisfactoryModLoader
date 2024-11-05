// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGEquipmentStunSpear.generated.h"

class UFGDamageType;

UCLASS()
class FACTORYGAME_API AFGEquipmentStunSpear : public AFGEquipment
{
	GENERATED_BODY()

public:
	AFGEquipmentStunSpear();

	/** Called when the player uses the weapon, e.g. swings */
	UFUNCTION( BlueprintImplementableEvent, Category = "Stun Spear", DisplayName = "PlaySwingEffects" )
	void PlayStunEffects( bool secondSwing );

	/** Called when the weapon swing hits actors */
	UFUNCTION( BlueprintImplementableEvent, Category = "Stun Spear", DisplayName = "PlayHitEffects" )
	void PlayHitEffects( const TArray<FHitResult>& hitResults );

	/** Swings the weapon, assuming the current player is locally controlled. */
	UFUNCTION( BlueprintCallable, Category = "Stun Spear" )
	void Local_SwingWeapon();
	
	/** Perform the attack, should be called on the local instigator side */
	UFUNCTION( BlueprintCallable, Category = "Stun Spear" )
	void Local_Attack();
	
	UFUNCTION( BlueprintCallable, Category = "Stun Spear", meta = ( DeprecatedFunction, DeprecationMessage = "Old function doing nothing, left to let Anim_1P compile. Use Local_Attack instead" ) )
	FORCEINLINE void DoAttack() {}
	
protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
	
	/** Plays hit VFX locally without checking whenever the current player is the instigator or not */
	void PlayHitEffectsInternal( const TArray<FHitResult>& hitLocations );

	/** Processes hit results received from the client and applies damage/VFX */
	UFUNCTION( Reliable, Server )
	void Server_ProcessAttack( const TArray<FHitResult>& hitResults );

	/** Processes player swinging on the server */
	UFUNCTION( Reliable, Server )
	void Server_ProcessPlayerSwing( bool secondSwing );

	UFUNCTION( Unreliable, NetMulticast )
	void Multicast_PlayHitEffects(const TArray<FHitResult> &hitResults);

	UFUNCTION( Unreliable, NetMulticast )
	void Multicast_PlaySwingEffects( bool secondSwing );
private:
	/** Sphere collision component */
	UPROPERTY( VisibleDefaultsOnly, Category = "Stun Spear" )
	class USphereComponent* mCollisionComp;

	UPROPERTY( EditDefaultsOnly, Instanced, Category= "Stun Spear")
	TArray < UFGDamageType* > mDamageTypes;
	
	/** The noise to make when attacking with the spear. */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	TSubclassOf< class UFGNoise > mAttackNoise;

public:
	/** Time of the first swing */
	float mFirstSwingTime;
	/** Time the second swing was made */
	float mSecondSwingTime;
	/** Number of attacks that we are allowed to make since last swing. */
	int32 mAttacksSinceLastSwing;
	
	/** The minimum amount of time after the first swing the player has to wait to trigger a second swing */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mSecondSwingMinDelay;

	/** The maximum amount of time after the first swing the player can wait while they can still make a second swing */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mSecondSwingMaxDelay;

	/** Cooldown after using the second swing, before the player can swing the spear again */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mSecondSwingUseCoolDown;
	
	/** Indicates if we should do the second swing */
	bool mShouldPlaySecondSwing;

	/** How much inf ront of character the attack is */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mAttackDistance;

	/** Defined half-width of the attack in front of the instigator */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mAttackSweepRadius;
};
