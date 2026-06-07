// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGNetSignificanceInterface.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "FGFoliageInstancedSMC.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGFoliageInstancedSMC : public UFoliageInstancedStaticMeshComponent, public IFGNetSignificanceInterface
{
	GENERATED_BODY()

	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	// Begin IFGNetSignificanceInterface
	virtual float GetNetSignificanceRange_Implementation() const override;
	virtual void GainedNetSignificance_Implementation() override;
	virtual void LostNetSignificance_Implementation() override;
	// End IFGNetSignificanceInterface

	virtual bool ShouldCreatePhysicsState() const override;
	virtual bool ShouldRegisterToSignificanceManager() const;
	
	
	bool mIsSignificant = false;
};
