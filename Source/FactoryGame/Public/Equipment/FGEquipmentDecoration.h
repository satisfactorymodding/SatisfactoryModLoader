// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
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
	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;
public:
	// Trace distance when building. * /
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Decoration" )
	float mPlaceDistanceMax;

public:
	FORCEINLINE ~AFGEquipmentDecoration() = default;
};
