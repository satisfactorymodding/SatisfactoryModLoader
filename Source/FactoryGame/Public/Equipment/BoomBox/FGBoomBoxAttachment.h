// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBoomboxListenerInterface.h"

#include "Equipment/FGEquipmentAttachment.h"
#include "FGBoomBoxAttachment.generated.h"

class IFGBoomboxListenerInterface;

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBoomBoxAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()
	friend class AFGEquipmentBoomBox;
	
protected:
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayPressPlayEffect();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayPressStopEffects();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayPressNextEffects();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayPressPreviousEffects();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayInspectEffects();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayTurboBassEffects();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayFireTurboBassEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayLoadTapeEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlaySwitchTapeEffect();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayLoadTapeEffect();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlaySwitchTapeEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressPlayEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressStopEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressNextEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayPressPrevEffect();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayInspectEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayTurboBassEffects();

	UFUNCTION( BlueprintImplementableEvent )
	void PlayFireTurboBassEffects();
};
