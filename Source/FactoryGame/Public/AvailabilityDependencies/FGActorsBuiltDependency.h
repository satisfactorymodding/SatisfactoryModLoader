// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGActorsBuiltDependency.generated.h"

UENUM( BlueprintType )
enum class EActorBuiltDependencyType : uint8
{
	ABT_Built				UMETA(displayName = "Built", ToolTip = "Triggers when we built the given amount of the given type in the world at the same time. EXCLUDING already dismantled actors"),
    ABT_BuiltTotal			UMETA(displayName = "Built Total", ToolTip = "Triggers when we built the given amount of the given type in the world at any time. INCLUDING already dismantled actors"),
    ABT_DismantledTotal		UMETA(displayName = "Dismantled Total", ToolTip = "Triggers when we dismantled the given amount of the given type in the world at any time")
};

/**
* Dependency that's met if we have built the given amount of actors
*/
UCLASS()
class FACTORYGAME_API UFGActorsBuiltDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	TMap< TSubclassOf< class AActor >, int32 > GetActorsBuiltCount() const { return mActorsBuiltCount; }

protected:
	/** The amount of the given actors that should have been built for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TMap< TSubclassOf< class AActor >, int32 > mActorsBuiltCount;

	/** The type of build action this dependency cares about */
	UPROPERTY( EditDefaultsOnly )
	EActorBuiltDependencyType mType;
};
