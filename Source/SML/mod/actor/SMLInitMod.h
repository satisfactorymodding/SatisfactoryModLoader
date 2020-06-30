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
	/**
	 * Called before subsystem initialization early during the world init
	 * Most things are unsafe to do here, so use carefully
	 */
	UFUNCTION(BlueprintNativeEvent)
	void PreInit();

	virtual void PreLoadModContent();
	
	/**
	 * Called after map has been loaded and subsystems are initialized
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Init();

	/** Called when the game save is fully loaded and the player is spawned
	  * You don't have to load your schematics in here, they are loaded by SML
	  */
	UFUNCTION(BlueprintNativeEvent)
	void PostInit();

	virtual void LoadModContent();

	UFUNCTION(BlueprintNativeEvent)
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

	/**
	 * List of classes for objects implementing ISMLItemTooltipProvider
	 * These will be registered on startup and used to obtain additional description
	 * text/widget for all items
	 */
	UPROPERTY(EditDefaultsOnly, Category = Advanced)
	TArray<UClass*> GlobalItemTooltipProviders;

	/**
	 * Table to use for obtaining AWESOME resource sink item point values
	 * for items added by this mod
	 */
	UPROPERTY(EditDefaultsOnly, Category = Advanced)
	TSoftObjectPtr<UDataTable> mResourceSinkItemPointsTable;
};