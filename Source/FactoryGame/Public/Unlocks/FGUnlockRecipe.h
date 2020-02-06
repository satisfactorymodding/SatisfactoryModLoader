// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockRecipe.generated.h"

/**
 * Unlocks the specified recipes
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockRecipe : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

#if WITH_EDITORONLY_DATA
	void Init( TArray< TSubclassOf< class UFGRecipe > > recipes ) { mRecipes = recipes; }
#endif

protected:
	UFUNCTION( BlueprintPure, Category=Unlocks )
	FORCEINLINE TArray< TSubclassOf< class UFGRecipe > > GetRecipes() const { return mRecipes; }

protected:
	/** The recipes you get from this unlock */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGRecipe > > mRecipes;

};
