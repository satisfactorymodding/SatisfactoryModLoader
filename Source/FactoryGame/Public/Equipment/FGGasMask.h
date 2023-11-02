// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FactoryGame.h"
#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "FGGasMask.generated.h"

UCLASS()
class FACTORYGAME_API AFGGasMask : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGGasMask();
	virtual void Tick( const float deltaTime ) override;

	// Start FGEquipment interface
	virtual float AdjustDamage_Implementation( const float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser ) override;
	// End FGEquipment interface

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
	void EnablePostProcessing( const bool isEnabled );

protected:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	UFUNCTION()
	void PostProcessEnabled_OnRep();
	
	UPROPERTY( EditDefaultsOnly, Instanced, Category="DamageTypes" )
	TArray<UFGDamageType*> mDamageTypesToProtectAgainst;
	
	UPROPERTY( Replicated )
	bool mPostProcessEnabled = false;

	UPROPERTY( Replicated, BlueprintReadOnly )
	float mFilterCountdown = 0.0f;
	
	UPROPERTY( BlueprintReadOnly )
	float mFilterDuration = 240.0f;
	
	UPROPERTY( BlueprintReadOnly )
	bool mIsInPoisonGas = true;
	
private:
	UFUNCTION( BlueprintPure )
	bool IsInGasCloud() const;
	
	bool mHasNegatedDamage = false;
	bool mIsWorking = false;
	
	float mDisableEffectTimer = -1.0f;
	float mDamageNegated = 0.0f;
	float mTimer = 0.0f;
	
};

UCLASS()
class FACTORYGAME_API AFGGasMaskAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()
};
