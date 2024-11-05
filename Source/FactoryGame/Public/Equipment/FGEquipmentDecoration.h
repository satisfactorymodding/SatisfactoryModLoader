// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGEquipmentDecoration.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentDecoration : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGEquipmentDecoration();

	/** It's a tick! */
	virtual void Tick( float DeltaSeconds ) override;

	/** Called on the owner, client or server but not both. */
	void OnPrimaryFirePressed();

	/** Only the server handles the building. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	/** Handle the actual spawning */
	UFUNCTION( BlueprintImplementableEvent )
	void SpawnDecoration();

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
	
public:
	// Trace distance when building. * /
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Decoration" )
	float mPlaceDistanceMax;
};
