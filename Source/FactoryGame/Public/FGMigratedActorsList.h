// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "FGMigratedActorsList.generated.h"


USTRUCT( BlueprintType )
struct FACTORYGAME_API FMigratedActorFromTo
{
	GENERATED_BODY()

	FMigratedActorFromTo() {}
	FMigratedActorFromTo( const FString& fromLevel, const FString& toLevel, const FString& actorName ) : 
		FromLevel( fromLevel ), ToLevel( toLevel ), ActorName( actorName )
	{
	}

	UPROPERTY( VisibleAnywhere )
	FString FromLevel;

	UPROPERTY( VisibleAnywhere )
	FString ToLevel;

	UPROPERTY( VisibleAnywhere )
	FString ActorName;

};

/**
 * Class for holding a record of all migrations that occur via the actor migration tool. To keep a record of which actors have moved
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGMigratedActorsList : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category = "Level Migration" )
	static bool AddMigratedActor( TSubclassOf< UFGMigratedActorsList > inClass, FString& fromLevel, FString& toLevel, FString& actorName );

	UPROPERTY( VisibleAnywhere, Category = "Level Migration" )
	TArray< FMigratedActorFromTo > mMigratedActorData;
	
};
