// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "FGEnvQueryTest_CreatureFood.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEnvQueryTest_CreatureFood : public UEnvQueryTest
{
	GENERATED_UCLASS_BODY()

protected:
	/** This is where we actually check for the ItemDescriptor class */
	virtual void RunTest( FEnvQueryInstance& QueryInstance ) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
};
