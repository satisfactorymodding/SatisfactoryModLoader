// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBoomBoxPlayer.h"
#include "DamageTypes/FGPointDamageType.h"
#include "Equipment/FGEquipment.h"
#include "FGEquipmentBoomBox.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentBoomBox : public AFGEquipment
{
	GENERATED_BODY()
	
public:
	AFGEquipmentBoomBox();

	void SetBoomBoxPlayer( class AFGBoomBoxPlayer* player );
	
protected:
	UFUNCTION( BlueprintImplementableEvent )
	void PlayStingerEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayEquipEffects();
	
	virtual void WasEquipped_Implementation() override;
	virtual void WasUnEquipped_Implementation() override;
	virtual void WasRemovedFromSlot_Implementation() override;
	virtual void WasSlottedIn_Implementation( class AFGCharacterPlayer* holder ) override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const;
	virtual bool ShouldSaveState() const override;

	UFUNCTION()
	void OnRep_BoomBoxPlayer( class AFGBoomBoxPlayer* oldPlayer );
		
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing=OnRep_BoomBoxPlayer, SaveGame )
	class AFGBoomBoxPlayer* mBoomBoxPlayer = nullptr;
private:
	friend class AFGBoomBoxPlayer;

	// Breaks the connection to the boombox player. This should only be called by the boombox player when it gets placed down in the world.
	void ReleaseBoomBoxPlayer();
};
