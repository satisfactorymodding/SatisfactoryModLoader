// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGCalendarOpenedDependency.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCalendarOpenedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	virtual bool AreDependenciesMet( UObject* worldContext ) const override;

	bool IsFirstTimeOnly() const { return mFirstTimeOnly; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** Whether or not this dependency should trigger only the first time a player opens the calendar. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	bool mFirstTimeOnly;
};
