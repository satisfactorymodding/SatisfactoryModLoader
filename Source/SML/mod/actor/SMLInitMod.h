#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "FGResearchTree.h"
#include "command/ChatCommandLibrary.h"
#include "mod/ModSubsystems.h"
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

	/**
	 * List of chat commands to register automatically on startup
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AChatCommandInstance>> mChatCommands;

	/**
	 * List of subsystem holders to register
	 */
	UPROPERTY(EditDefaultsOnly, Category = Advanced)
	TArray<TSubclassOf<UModSubsystemHolder>> mModSubsystems;
};