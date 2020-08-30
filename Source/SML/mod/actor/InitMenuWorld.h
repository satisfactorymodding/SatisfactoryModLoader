#pragma once

#include "GameFramework/Actor.h"
#include "InitMenuWorld.generated.h"

/**
 * This actor is spawned every time Menu world is loaded to allow
 * mods to modify menu world by adding additional objects to it
 * For SML to load your InitMenuWorld subclass, it should be located exactly at
 * /Game/YourModReference/InitMenuWorld/
 */
UCLASS(Abstract, Blueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API AInitMenuWorld : public AActor {
	GENERATED_BODY()
public:
	/**
	 * Called when menu world is being initialized
	 */
	UFUNCTION(BlueprintNativeEvent)
	void Init();
};