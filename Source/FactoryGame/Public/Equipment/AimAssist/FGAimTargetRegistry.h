// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGAimTargetRegistry.generated.h"

class UFGAimTargetComponent;

// <FL> [MartinC] Class that manages all the aim assist targets currently active in the game
UCLASS()
class FACTORYGAME_API UFGAimTargetRegistry : public UObject
{
	GENERATED_BODY()

public:

	// <FL> [MartinC] Adds a new aim assist target to the registry
	UFUNCTION( BlueprintCallable )
	void AddAimTarget( UFGAimTargetComponent* AimTarget );

	// <FL> [MartinC] Removes an aim assist target from the registry
	UFUNCTION( BlueprintCallable )
	void RemoveAimTarget( UFGAimTargetComponent* AimTarget );

	const TSet< TObjectPtr< UFGAimTargetComponent > >& GetAimTargets() const { return AimTargets; }

private:
	// <FL> [MartinC] Set of aim assit target components that are currently active in the game
	UPROPERTY()
	TSet< TObjectPtr< UFGAimTargetComponent > > AimTargets;


};
