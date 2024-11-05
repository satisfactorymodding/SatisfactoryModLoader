// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildablePortalBase.h"
#include "FGBuildablePortalSatellite.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePortalSatellite : public AFGBuildablePortalBase
{
	GENERATED_BODY()
public:
	AFGBuildablePortalSatellite();

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_TickProducing(float dt) override;
	virtual void Factory_StopProducing() override;
	// End AFGBuildableFactory interface

	/**
	 * Returns the heat up progress of the main portal
	 * If there is no main portal connected to this satellite node, this will return zero.
	 */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	virtual float GetMainPortalHeatUpProgress() const;
protected:
	virtual EFGPortalLinkCandidateState CanLinkToPortal(AFGBuildablePortalBase* otherPortal) const override;
	virtual float GetProducingPowerConsumptionBase_ForPortal() const override;
private:
	UPROPERTY( SaveGame )
	bool mWasHeatingUpLastTick;
};
