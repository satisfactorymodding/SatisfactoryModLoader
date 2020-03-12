// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
#include "FGGolfCartDispenser.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGGolfCartDispenser : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGGolfCartDispenser();

	/** It's a tick! */
	virtual void Tick( float DeltaSeconds ) override;

	void BeginPlay();

	void SetMaterial( class UMaterialInterface* material );

	/** Called on the owner, client or server but not both. */
	void OnPrimaryFirePressed();

	/** Only the server handles the building. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	/** Handle the actual spawning */
	UFUNCTION( BlueprintImplementableEvent )
	void SpawnGolfCart( );
protected:
	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;
public:
	// Trace distance when building. * /
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Buildable" )
	float mPlaceDistanceMax;

	/** Material on hologram for valid placement. */
	UPROPERTY()
	class UMaterialInstance* mValidPlacementMaterial;

	/** Material on hologram for invalid placement. */
	UPROPERTY()
	class UMaterialInstance* mInvalidPlacementMaterial;

public:
	FORCEINLINE ~AFGGolfCartDispenser() = default;
};
