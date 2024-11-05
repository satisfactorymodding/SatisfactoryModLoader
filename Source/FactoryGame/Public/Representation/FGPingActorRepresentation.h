// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "FGPingActorRepresentation.generated.h"

UCLASS()
class FACTORYGAME_API UFGPingActorRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
public:
	// Begin UFGActorRepresentation interface
	virtual UMaterialInterface* GetRepresentationCompassMaterial() const override;
	virtual float GetCompassHeightAlignment() const override;
	virtual void UpdateRepresentationCompassMaterial(UMaterialInstanceDynamic* compassMaterialInstance, APlayerController* ownerPlayerController) const override;
	virtual bool NeedsDynamicCompassRepresentationText() const override;
	virtual FText GetDynamicCompassRepresentationText(APlayerController* ownerPlayerController, float distanceToPlayer) const override;
	virtual bool IsImportantCompassRepresentation() const override;
	// End UFGActorRepresentation interface
};
