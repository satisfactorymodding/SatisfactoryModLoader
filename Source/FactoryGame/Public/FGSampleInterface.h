// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGSampleInterface.generated.h"

class UFGRecipe;

UINTERFACE(Blueprintable)
class FACTORYGAME_API UFGSampleInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGSampleInterface
{
	GENERATED_BODY()
public:
	/** Returns true if the actor can currently be sampled by the build gun */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Sample" )
	bool CanSample() const;

	/** Returns the recipe that the build gun should sample */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Sample" )
	TSubclassOf<UFGRecipe> GetSampledRecipe() const;
};
