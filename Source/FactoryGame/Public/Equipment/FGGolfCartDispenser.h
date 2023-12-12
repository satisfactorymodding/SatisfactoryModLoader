// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGEquipment.h"
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

	void BeginPlay();

	void SetMaterial( class UMaterialInterface* material );

	/** Handle the actual spawning */
	UFUNCTION( BlueprintImplementableEvent )
	void SpawnGolfCart( );

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
	
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
};
