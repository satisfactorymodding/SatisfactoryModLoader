// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGRandomChanceDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGRandomChanceDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The random chance that this will trigger. Should be a value between 0-1 */
	UPROPERTY( EditDefaultsOnly, Category="Dependency", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1") )
	float mRandomChance;
	
};
