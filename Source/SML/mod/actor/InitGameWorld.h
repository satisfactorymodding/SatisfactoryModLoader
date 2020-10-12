#pragma once

#include "BasicModInit.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSchematic.h"
#include "FGResearchTree.h"
#include "command/ChatCommandLibrary.h"
#include "mod/ModSubsystems.h"
#include "InitGameWorld.generated.h"

enum class ELifecyclePhase : uint8;

/**
 * This actor is spawned every time game world is loaded
 * It will load schematics, resource trees, commands and other things your mod adds
 * You can also override various methods to modify world directly
 * For SML to load your InitGameWorld subclass, it should be located exactly at
 * /Game/YourModReference/InitGameWorld
 */
UCLASS(Abstract, Blueprintable)
class SML_API AInitGameWorld : public ABasicModInit {
	GENERATED_BODY()
public:
	/**
	 * Called after UWorld has been populated with actors for play
	 * Only basic initialization of world and actors has been performed at this point,
	 * so be very careful at what you do.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	/**
	 * Called when map has been fully loaded by the engine
	 * WARNING! Do not try to use PlayerController at this point -
	 * It's not initialized for clients connecting to the remote host yet
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void PostInit();

	/**
	 * Called prior to PostInit, and handles
	 * registering content in fields declared below automatically
	 */
	virtual void InitDefaultContent();

	/** Called at the same time as Init(), can be overriden in C++ */
	virtual void InitNative();

	/** Called at the same time as PostInit(), can be overriden in C++ */
	virtual void PostInitNative();
private:
    /** Called when mod loader dispatches new lifecycle phase */
    virtual void DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase) override;
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
	 * Table to use for obtaining AWESOME resource sink item point values
	 * for items added by this mod
	 */
	UPROPERTY(EditDefaultsOnly, Category = Advanced)
	TSoftObjectPtr<UDataTable> mResourceSinkItemPointsTable;
};