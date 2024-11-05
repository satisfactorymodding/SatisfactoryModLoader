// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes/FGPointDamageType.h"
#include "Equipment/FGEquipment.h"
#include "FGBoomBoxPlayer.h"
#include "FGEquipmentBoomBox.generated.h"

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

	UFUNCTION( BlueprintImplementableEvent )
	void OnBeginTurbobassSequence();

	UFUNCTION( BlueprintImplementableEvent )
	void OnMenuOpen();
	
	virtual void WasEquipped_Implementation() override;
	virtual void WasUnEquipped_Implementation() override;
	virtual void WasRemovedFromSlot_Implementation() override;
	virtual void WasSlottedIn_Implementation( class AFGCharacterPlayer* holder ) override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const;
	virtual FFGDynamicStruct SaveToItemState_Implementation() const override;
	virtual void LoadFromItemState_Implementation(const FFGDynamicStruct& itemState) override;

	UFUNCTION()
	void OnRep_BoomBoxPlayer( class AFGBoomBoxPlayer* oldPlayer );
		
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing=OnRep_BoomBoxPlayer, SaveGame )
	class AFGBoomBoxPlayer* mBoomBoxPlayer = nullptr;

	/** Cached item state, stored here in case we do not have a boombox when we receive LoadFromItemState. In that case we will load again in BeginPlay */
	UPROPERTY( Transient )
	FFGDynamicStruct mCachedItemState{};

	virtual void AddEquipmentActionBindings() override;

	/** Input Actions */
	void Input_PlayPause( const FInputActionValue& actionValue );
	void Input_Turbobass( const FInputActionValue& actionValue );
	void Input_ToggleMenu( const FInputActionValue& actionValue );
	void Input_PutDown( const FInputActionValue& actionValue );

private:
	friend class AFGBoomBoxPlayer;

	// Breaks the connection to the boombox player. This should only be called by the boombox player when it gets placed down in the world.
	void ReleaseBoomBoxPlayer();
	static void TransferMontagesToNewBoomBoxPlayer( AFGBoomBoxPlayer* oldPlayer, AFGBoomBoxPlayer* newPlayer );
};
