// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "FGFoliageInstancedSMC.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGFoliageInstancedSMC : public UFoliageInstancedStaticMeshComponent, public IFGSignificanceInterface
{
	GENERATED_BODY()

	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	/*Begin IFGSignificanceInterface*/
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override;
	/* end IFGSignificanceInterface*/

	virtual bool ShouldCreatePhysicsState() const override;
	virtual bool ShouldRegisterToSignificanceManager() const { return !bDisableCollision; }

	bool mIsSignificant = false;
};
