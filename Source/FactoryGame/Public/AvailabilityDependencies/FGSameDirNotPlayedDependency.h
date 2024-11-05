// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGSameDirNotPlayedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSameDirNotPlayedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	bool AreLocalDependenciesMet( UObject* worldContext ) const override;

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	UPROPERTY( EditDefaultsOnly, Category="Dependency", meta = ( Units="s" ) )
	float mTimeInterval;
	
};
