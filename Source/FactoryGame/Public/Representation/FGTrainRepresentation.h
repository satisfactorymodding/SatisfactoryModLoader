// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGWarningIndicatorRepresentation.h"
#include "FGTrainRepresentation.generated.h"

UCLASS()
class FACTORYGAME_API UFGTrainRepresentation : public UFGWarningIndicatorRepresentation
{
	GENERATED_BODY()
protected:
	UFGTrainRepresentation();

	virtual bool GetShouldShowInCompass() const override;
	virtual bool IsWarningIndicatorVisible(AActor* realActor, FLinearColor& out_warningIndicatorColor) const override;
	virtual void UpdateActorRepresentation() override;
private:
	/** True if this train is controlled by a local player */
	bool mIsLocallyControlledTrain{false};
};
