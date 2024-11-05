// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGActionScorer.h"
#include "FGActionScorerCompound.generated.h"

/**
 * Action scorer used to compound multiple scorers. Will return true if any of the scorers succeed, and combine their score as the resulting score.
 */
UCLASS( NotBlueprintable )
class FACTORYGAME_API UFGActionScorerCompound : public UFGActionScorer
{
	GENERATED_BODY()

public:
	// Begin UFGActionScorer Interface
	virtual void Initialize_Native( UFGAction* action ) override;
	virtual bool GetScore_Implementation( float& out_score ) const override;
	// End UFGActionScorer Interface
	
protected:
	/** The compounded scorer will succeed if all of these scorers succeed, and combine the score from every successful one. */
	UPROPERTY( EditDefaultsOnly, Instanced )
	TArray< UFGActionScorer* > mActionScorers;
};
