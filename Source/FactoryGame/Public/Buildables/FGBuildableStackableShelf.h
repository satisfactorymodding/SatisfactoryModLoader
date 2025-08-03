// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableStackableShelf.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableStackableShelf : public AFGBuildable
{
	GENERATED_BODY()
	
public:
	AFGBuildableStackableShelf();

	const FVector& GetSize() const { return mSize; }

private:
	UPROPERTY( EditDefaultsOnly, Category = "Shelf" )
	FVector mSize;
};
