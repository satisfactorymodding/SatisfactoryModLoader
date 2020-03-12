#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "SMLInitMod.generated.h"

UCLASS(Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API ASMLInitMod : public AActor {
	GENERATED_BODY()
public:
	/** Called before anything in the game has been loaded */
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	/** Called when the game is fully loaded and the player is spawned
	  * You don't have to load your schematics in here, they are loaded by SML
	  */
	UFUNCTION(BlueprintImplementableEvent)
	void PostInit();

	void LoadSchematics();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UFGSchematic>> mSchematics;
};