// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGWarningIndicatorRepresentation.h"
#include "FGWheeledVehicleRepresentation.generated.h"

UCLASS()
class FACTORYGAME_API UFGWheeledVehicleRepresentation : public UFGWarningIndicatorRepresentation
{
	GENERATED_BODY()
protected:
	UFGWheeledVehicleRepresentation();

	virtual bool GetShouldShowInCompass() const override;
	virtual bool IsWarningIndicatorVisible(AActor* realActor, FLinearColor& out_warningIndicatorColor) const override;
	virtual void UpdateActorRepresentation() override;
private:
	bool mIsLocallyControlledVehicle{false};
};
