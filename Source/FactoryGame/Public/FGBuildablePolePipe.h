// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildablePole.h"
#include "CoreMinimal.h"
#include "FGBuildablePolePipe.generated.h"

/**
 * Base class for variable length pipe supports
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePolePipe : public AFGBuildablePole
{
	GENERATED_BODY()
public:
	AFGBuildablePolePipe();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface

	/** Set the pole's height. */
	void SetVerticalAngle( float angle );

	/** Sets the connection component to be at correct height and registers */
	virtual void SetupConnectionComponent() override;
	
	virtual TArray<struct FInstanceData> GetActorLightweightInstanceData_Implementation() const override;

public:
	/** This supports length. */
	UPROPERTY( SaveGame, Replicated )
	float mVerticalAngle;

	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	FInstanceData mSupportMeshInstanceData;
};
