// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGUnlockPickup.h"
#include "FGUnlockPickup_Customization.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGUnlockPickup_Customization : public AFGUnlockPickup
{
	GENERATED_BODY()

public:
	AFGUnlockPickup_Customization();

	// Begin AFGUnlockPickup interface
	virtual void UpdateVisuals_Implementation() override;
	// End AFGUnlockPickup interface

	virtual void StartIsLookedAt_Implementation( AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void StopIsLookedAt_Implementation( AFGCharacterPlayer* byCharacter, const FUseState& state)  override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif

private:
	void UpdateMesh();
	
protected:
	/** The mesh to display for this pickup, if specified. Otherwise one will be grabbed automatically from the schematic. */
	UPROPERTY( EditAnywhere, Category = "Pickup" )
	class UStaticMesh* mPickupMesh;

	/** Desired size of the pickup mesh. Will scale the mesh component automatically to match this based on the mesh itself. */
	UPROPERTY( EditAnywhere, Category = "Pickup" )
	float mPickupMeshSize;

private:
	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* mStaticMeshComponent;
	
	UPROPERTY( EditDefaultsOnly )
	class USphereComponent* mSphereComponent;
};
