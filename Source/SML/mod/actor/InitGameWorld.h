#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "FGResearchTree.h"
#include "command/ChatCommandLibrary.h"
#include "mod/ModSubsystems.h"
#include "InitGameWorld.generated.h"

/**
 * This actor is spawned every time game world is loaded
 * It will load schematics, resource trees, commands and other things your mod adds
 * You can also override various methods to modify world directly
 * For SML to load your InitGameWorld subclass, it should be located exactly at
 * /Game/YourModReference/InitGameWorld
 */
UCLASS(Abstract, Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API AInitGameWorld : public AActor {
	GENERATED_BODY()
public:
	/**
	 * Called before subsystem initialization early during the world init
	 * Most things are unsafe to do here, so use carefully
	 * @deprecated Due to presence of InitGameInstance and not obvious ordering behavior
	 */
	UFUNCTION(BlueprintNativeEvent, meta = (DeprecatedFunction, DeprecationMessage = "Use InitGameInstance instead."))
	void PreInit();

	/**
	 * Called at the same time as PreInit, and initializes
	 * schematic holders.
	 * @deprecated Due to presence of InitGameInstance and not obvious ordering behavior
	 */
	UE_DEPRECATED(4.23, "Use InitGameInstance for early initialization instead")
	virtual void PreLoadModContent();
	
	/**
	 * Called after map has been loaded and subsystems are initialized
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Init();

	/**
	 * Called when the game save is fully loaded and the player is spawned
	 * You don't have to load your schematics in here, they are loaded by SML
	 */
	UFUNCTION(BlueprintNativeEvent)
	void PostInit();

	/**
	 * Called roughly in the same time as PostInit, and handles
	 * registering content in fields declared below automatically
	 */
	virtual void LoadModContent();

	/**
	 * Called when player controller is created
	 * Called on both client and server
	 */
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
	 * @deprecated Use InitGameInstance instead, this will be removed soon
	 */
	UPROPERTY()
	TArray<TSubclassOf<UModSubsystemHolder>> mModSubsystems_DEPRECATED;

	/**
	 * List of classes for objects implementing ISMLItemTooltipProvider
	 * These will be registered on startup and used to obtain additional description
	 * text/widget for all items
	 * @deprecated Use InitGameInstance instead, this will be removed soon
	 */
	UPROPERTY()
	TArray<UClass*> GlobalItemTooltipProviders_DEPRECATED;

	/**
	 * Table to use for obtaining AWESOME resource sink item point values
	 * for items added by this mod
	 */
	UPROPERTY(EditDefaultsOnly, Category = Advanced)
	TSoftObjectPtr<UDataTable> mResourceSinkItemPointsTable;
};