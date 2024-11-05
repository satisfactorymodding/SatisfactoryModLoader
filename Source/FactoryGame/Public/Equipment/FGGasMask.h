// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGEquipment.h"
#include "FGGasMask.generated.h"

/** Item state struct for the gas mask */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGGasMaskItemState
{
	GENERATED_BODY()

	/** How much filter charges are left in the currently loaded filter */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "ItemState|GasMask" )
	float FilterCountdown{};
};

UCLASS()
class FACTORYGAME_API AFGGasMask : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGGasMask();

	// Begin AFGEquipment Interface
	virtual void UnEquip() override;
	virtual FFGDynamicStruct SaveToItemState_Implementation() const override;
	virtual void LoadFromItemState_Implementation(const FFGDynamicStruct& itemState) override;
	virtual void Tick( const float deltaTime ) override;
	virtual float AdjustDamage_Implementation( const float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser ) override;
	// End AFGEquipment Interface

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

	UPROPERTY( Replicated, BlueprintReadOnly, SaveGame )
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
