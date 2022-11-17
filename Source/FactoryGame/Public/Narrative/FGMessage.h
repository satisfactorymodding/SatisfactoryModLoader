// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FGMessage.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGMessage : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mTitle;

	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Dependencies" )
	class UFGAvailabilityDependency* mTrigger;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Message" )
	FText mMessage;
	
};
