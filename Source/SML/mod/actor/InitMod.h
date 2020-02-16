#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "InitMod.generated.h"

UCLASS(Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API AInitMod : public AActor {
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
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UFGSchematic>> mSchematics;
};