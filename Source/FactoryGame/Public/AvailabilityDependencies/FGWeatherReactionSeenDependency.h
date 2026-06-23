// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGWeatherReactionSeenDependency.generated.h"

/**
 * @class UFGWeatherReactionSeenDependency
 * @brief A class that handles availability dependencies based on whether a specific weather reaction has been seen.
 *
 * This class derives from UFGAvailabilityDependency and is used to determine the availability of certain features
 * or actions based on the visibility of a specific weather reaction class. It links a weather reaction class
 * to its availability dependency, primarily used within the game Factory Game.
 *
 * @note This class focuses on server-side and player-specific dependency checks related to weather reactions.
 */
UCLASS()
class FACTORYGAME_API UFGWeatherReactionSeenDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
public:
	bool DoesWeatherReactionMatch( const TSubclassOf< class AFGWeatherReaction >& weatherReactionClass ) const;
	
	#if WITH_EDITOR
		/** This should return the dependency parsed to a string"   */
		virtual FString ToString() const;
		// Populates this dependency with the given string
		virtual void FromString( const FString& inString );
	#endif
	
protected:
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TSubclassOf< class AFGWeatherReaction > mWeatherReactionClass;
};
