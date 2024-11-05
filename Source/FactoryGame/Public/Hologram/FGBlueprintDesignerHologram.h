// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGBlueprintDesignerHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBlueprintDesignerHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
	
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual void InitializeClearanceData() override;

protected:
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual void OnHologramTransformUpdated() override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	
private:
	/** component matching the location where the storage is placed */
	UPROPERTY()
	USceneComponent* mStorageLocation;
	
	/** The storage hologram */
	UPROPERTY( Replicated )
	class AFGBuildableHologram* mStorageHologram;
};
