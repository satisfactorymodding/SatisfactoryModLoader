// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimated.h"
#include "FGCreatureActionPull.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureActionPull : public UFGCreatureActionAnimated
{
	GENERATED_BODY()

	UFGCreatureActionPull( const FObjectInitializer& ObjectInitializer );

	virtual void PerformAction_Implementation() override;
	virtual void OnAnimNotify_Implementation( const UFGAnimNotify* Notify ) override;

protected:
	bool PerformPull();
	
private:
	
};
