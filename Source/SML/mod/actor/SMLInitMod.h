#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "FGResearchTree.h"
#include "FGPlayerController.h"
#include "SMLInitMod.generated.h"

UCLASS(Abstract, Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API ASMLInitMod : public AActor {
	GENERATED_BODY()
public:
	/** Called after map has been loaded and ga
	 * 
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	/** Called when the game is fully loaded and the player is spawned
	  * You don't have to load your schematics in here, they are loaded by SML
	  */
	UFUNCTION(BlueprintImplementableEvent)
	void PostInit();

	void LoadModContent();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerJoined(AFGPlayerController* Player);
public:
	/**
	 * List of schematics that will be automatically registered
	 * by the SML during the loading phase
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UFGSchematic>> mSchematics;

	/**
	 * List of MAM research trees that will be registered
	 * by the SML during the loading phase
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UFGResearchTree>> mResearchTrees;
};