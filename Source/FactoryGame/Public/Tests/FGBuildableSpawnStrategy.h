// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGRecipe.h"
#include "Buildables/FGBuildable.h"
#include "UObject/Object.h"
#include "FGBuildableSpawnStrategy.generated.h"

class AFGBuildable;

/**
 * Buildable spawn strategy dictates how the buildable is spawned into the world
 * and connected with other buildables, or configured upon spawn.
 *
 * This is a base class for which subclasses can set additional properties or perform building-specific behaviors
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGBuildableSpawnStrategy : public UObject
{
	GENERATED_BODY()
public:
	UFGBuildableSpawnStrategy();
	
	// Returns true if the given buildable is compatible with this strategy.
	virtual bool IsCompatibleWith( AFGBuildable* buildable ) const;

	// Called before the buildable has finished spawning (e.g. before BeginPlay is dispatched)
	virtual void PreSpawnBuildable( AFGBuildable* buildable);

	// Called after the buildable has finished spawning (e.g. after BeginPlay)
	virtual void PostSpawnBuildable( AFGBuildable* buildable );

protected:
	// Called before the buildable has finished spawning (e.g. before BeginPlay is dispatched)
	UFUNCTION( BlueprintImplementableEvent, Category = "Buildable | Strategy", DisplayName = "Pre Spawn Buildable" )
	void K2_PreSpawnBuildable( AFGBuildable* buildable );

	// Called after the buildable has finished spawning (e.g. after BeginPlay)
	UFUNCTION( BlueprintImplementableEvent, Category = "Buildable | Strategy", DisplayName = "Post Spawn Buildable" )
	void K2_PostSpawnBuildable( AFGBuildable* buildable );

	// Returns to check if this strategy can handle the given buildable.
	UFUNCTION( BlueprintNativeEvent, Category = "Buildable | Strategy", DisplayName = "Is Compatible With Buildable" )
	bool K2_IsCompatibleWith( AFGBuildable* buildable ) const;
public:
	// Recipe that will be set on the buildable. This will be overriden the default recipe when constructing from a FGRecipe object
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Spawn" )
	TSubclassOf<UFGRecipe> mBuiltWithRecipe;

	// True if the build effect should be played when spawning the buildables
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Spawn" )
	bool mPlayBuildEffect{false};
};