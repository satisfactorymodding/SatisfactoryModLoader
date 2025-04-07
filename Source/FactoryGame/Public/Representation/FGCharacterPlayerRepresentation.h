// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "FGCharacterPlayerRepresentation.generated.h"

UCLASS()
class FACTORYGAME_API UFGCharacterPlayerRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
public:
	UFGCharacterPlayerRepresentation();

	// <FL> [TranN]
	FText GetRepresentationText() const override;
	bool NeedsDynamicCompassRepresentationText() const override { return true; }

	UFUNCTION(BlueprintCallable)
	void ViewProfileOfOwningPlayer();

	UFUNCTION(BlueprintPure)
	bool IsCharacterOwnerOnSamePlatform();

private:
	bool ResolvePlatformIDFromString();
	// </FL>
};
