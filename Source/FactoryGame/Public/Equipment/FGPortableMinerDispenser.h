// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildable.h"
#include "FGEquipment.h"
#include "GameFramework/Actor.h"
#include "Resources/FGItemDescriptor.h"
#include "FGPortableMinerDispenser.generated.h"

UCLASS()
class FACTORYGAME_API AFGPortableMinerDispenser : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGPortableMinerDispenser();

	void BeginPlay();

	void SetMaterial( class UMaterialInterface* material );

	UFUNCTION( BlueprintImplementableEvent )
	void SpawnPortableMiner( class AFGResourceNode* resourceNode );

protected:
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent ) override;
	
public:
	/** What form can the overlapping resources be in. */
	UPROPERTY( EditDefaultsOnly )
	TArray< EResourceForm > mAllowedResourceForms;

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
