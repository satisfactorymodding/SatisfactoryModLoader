// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGWarningIndicatorRepresentation.h"
#include "FGVehicleDockingStationRepresentation.generated.h"

UCLASS()
class FACTORYGAME_API UFGVehicleDockingStationRepresentation : public UFGWarningIndicatorRepresentation
{
	GENERATED_BODY()
protected:
	virtual bool IsWarningIndicatorVisible(AActor* realActor, FLinearColor& out_warningIndicatorColor) const override;
};
