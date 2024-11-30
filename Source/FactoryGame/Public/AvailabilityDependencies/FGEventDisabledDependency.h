// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGEventSubsystem.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGEventDisabledDependency.generated.h"
/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGEventDisabledDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
public:
	virtual bool AreDependenciesMet( UObject* worldContext ) const override;

	const TArray< EEvents >& GetEvents() const { return mEvents; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	TArray< EEvents > mEvents;
};
