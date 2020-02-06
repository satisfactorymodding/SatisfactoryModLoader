#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "../Resources/FGItemDescriptor.h"
#include "FGEquipment.h"
#include "../Buildables/FGBuildable.h"
#include "FGPortableMinerDispenser.generated.h"

UCLASS()
class FACTORYGAME_API AFGPortableMinerDispenser : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGPortableMinerDispenser();

	/** It's a tick! */
	virtual void Tick( float DeltaSeconds ) override;

	void BeginPlay();

	void SetMaterial( class UMaterialInterface* material );

	/** Called on the owner, client or server but not both. */
	void OnPrimaryFirePressed();

	/** Only the server handles the building. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	UFUNCTION( BlueprintImplementableEvent )
	void SpawnPortableMiner( class AFGResourceNode* resourceNode );
protected:
	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;
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