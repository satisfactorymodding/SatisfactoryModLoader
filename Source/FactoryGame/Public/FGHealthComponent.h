#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Components/ActorComponent.h"
#include "FGSaveInterface.h"

#include "FGHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDeathDelegate, AActor*, DeadActor );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams( FTakeAnyDamageDelegate, AActor*, damagedActor, float, damageAmount, const class UDamageType*, damageType, class AController*, instigatedBy, AActor*, damageCauser );

DECLARE_DYNAMIC_DELEGATE_RetVal_FiveParams( float, FAdjustDamageDelegate, AActor*, damagedActor, float, damageAmount, const class UDamageType*, damageType, class AController*, instigatedBy, AActor*, damageCauser );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FHealDelegate, float, amount );

UCLASS( Blueprintable )
class FACTORYGAME_API UFGHealthComponent : public UActorComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Override to be able to set some properties on match start */
	virtual void BeginPlay() override;
	virtual void PostLoad() override;

	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
	//~ End UObject Interface
	virtual void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty, class FDefaultAllocator> & OutReplicatedProps) const override; // MODDING EDIT

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Apply damage to this actor.
	* @see https://www.unrealengine.com/blog/damage-in-ue4
	* @param DamageAmount		How much damage to apply
	* @param DamageType			Damage type of the damage
	* @param InstigatedBy		The Controller responsible for the damage.
	* @param DamageCauser		The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	* @return					The amount of damage actually applied.
	*/
	UFUNCTION()
	virtual void TakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	UFUNCTION()
	virtual void TakePointDamage( AActor* damagedActor, float damage, class AController* instigatedBy, FVector hitLocation, class UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection, const class UDamageType* damageType, AActor* damageCauser );

	UFUNCTION()
	virtual void TakeRadialDamage( AActor* damagedActor, float damage, const class UDamageType* damageType, FVector hitLocation, FHitResult hitInfo, class AController* instigatedBy, AActor* damageCauser );

	/** Sets a new max health */
	void SetMaxHealth( float NewMaxHealth );

	/** Gets our current health */
	UFUNCTION( BlueprintPure, Category = "Health" )
	float GetCurrentHealth() const;

	/** Gets our current health */
	UFUNCTION( BlueprintPure, Category = "Health" )
	float GetMaxHealth() const;

	UFUNCTION( Reliable, NetMulticast )
	void Client_TakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	UFUNCTION( Reliable, NetMulticast )
	void Client_TakePointDamage( AActor* damagedActor, float damage, class AController* instigatedBy, FVector hitLocation, class UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection, const class UDamageType* damageType, AActor* damageCauser );

	UFUNCTION( Reliable, NetMulticast )
	void Client_TakeRadialDamage( AActor* damagedActor, float damage, const class UDamageType* damageType, FVector hitLocation, FHitResult hitInfo, class AController* instigatedBy, AActor* damageCauser );

	UFUNCTION( Reliable, NetMulticast )
	void Client_Died( AActor* deadActor );

	UFUNCTION( Reliable, NetMulticast )
	void Client_Heal( float amount );

	UPROPERTY( BlueprintAssignable, Category = "Events|Health" )
	FTakeAnyDamageDelegate OnTakeAnyDamageDelegate;

	UPROPERTY( BlueprintAssignable, Category = "Events|Health" )
	FTakePointDamageSignature OnTakePointDamageDelegate;

	UPROPERTY( BlueprintAssignable, Category = "Events|Health" )
	FTakeRadialDamageSignature OnTakeRadialDamageDelegate;

	/** SERVER ONLY: Called when we die */
	UPROPERTY( BlueprintAssignable, Category = "Events|Health", DisplayName = "OnDeath" )
	FDeathDelegate DeathDelegate;

	UPROPERTY( BlueprintAssignable, Category = "Events|Health", DisplayName = "OnHeal" )
	FHealDelegate HealDelegate;

	UFUNCTION( BlueprintCallable, Category = "Health" )
	void Heal( float healAmount );

	UFUNCTION( BlueprintCallable, Category = "Health" )
	void ResetHealth();

	UFUNCTION( BlueprintCallable, Category = "Health" )
	void ResetHealthFromDeath();

	UFUNCTION( BlueprintCallable, Category = "Health" )
	void ReviveResetHealth();

	/**
	 * Instantly kill, bypass AdjustDamage event. Will trigger DeathDelegate
	 */
	UFUNCTION( BlueprintCallable, Category = "Damage" )
	void Kill();
	
	/** @return true if our owner is dead */
	UFUNCTION( BlueprintPure, Category="Health" )
	FORCEINLINE bool IsDead() const { return mIsDead; };

	/**
	 * Add a listener for when we take damage. Last added listener will be called first if multiple is added
	 * The return value of the listener will be the adjusted damage and is passed on to the next listener that
	 * get the call
	 */
	UFUNCTION( BlueprintCallable, Category="Health")
	void AddAdjustDamageListener( FAdjustDamageDelegate adjustDamage );

	/**
	 * Remove a listener of damage
	 */
	UFUNCTION( BlueprintCallable, Category = "Health" )
	void RemoveAdjustDamageListener( FAdjustDamageDelegate adjustDamage );

	/** Setter for this var */
	void SetReplicateDamageEvents( bool setReplicates );

	/** Setter for this var */
	void SetReplicateDeathEvents( bool setReplicates );
protected:
	/**
	 * Adjust incoming damage
	 * SERVER ONLY
	 * @return the new damage
	 **/
	float AdjustDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );
	
	/**
	 * Called when we died, used to prevent double notifications on DeathDelegate
	 *
	 * @param forceNotifies Forces our notifies to be sent anyway
	 */
	void Died( bool forceNotifies = false );
protected:
	// Interested listeners for the adjust damage delegates
	UPROPERTY()
	TArray< FAdjustDamageDelegate > mOnAdjustDamage;

	/** Our maximum health */
	UPROPERTY( SaveGame, Replicated, EditDefaultsOnly, Category = "Health" )
	float mMaxHealth;

	/** Our current health */
	UPROPERTY( SaveGame, Replicated)
	float mCurrentHealth;

	/** Scale of max health to use when respawning */
	UPROPERTY( SaveGame, Replicated, EditDefaultsOnly, Category = "Health" )
	float mRespawnHealthFactor;

	/** If true, then we are dead. This is replicated to clients and they get the death event based on this. */
	UPROPERTY( SaveGame, Replicated )
	uint8 mIsDead:1;

	/** If true, then the client will trigger the following events: OnTakeAnyDamageDelegate, OnTakePointDamageDelegate, OnTakeRadialDamageDelegate */
	UPROPERTY()
	uint8 mReplicateDamageEvents:1;

	/** If true, then the client will trigger the following event: DeathDelegate */
	UPROPERTY()
	uint8 mReplicateDeathEvents:1;
};
