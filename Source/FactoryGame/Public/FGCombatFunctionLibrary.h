// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FGCombatFunctionLibrary.generated.h"


UCLASS()
class FACTORYGAME_API UFGCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**
	 * Try get a pawn from a damage causer in take damage
	 */
	UFUNCTION( BlueprintCallable, Category = "Damage" )
	static class AFGCharacterBase* TryGetCharacterFromDamageCauser( class AActor* damageCauser );
};