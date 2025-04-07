// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FGDropPodSubsystem.generated.h"

class UFGDropPodRefundsLootPool;
class AFGCrashSiteBaseActor;

/**
 * Manages refund rewards (dismantle rewards) for dismantling crash site-related actors, and allows modifying their loot pools in runtime
 * Also makes sure to keep the data in memory to avoid hitching the async loading on level streaming (since crash sites are streamed in)
 */
UCLASS( BlueprintType )
class FACTORYGAME_API UFGDropPodSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	// Begin UWorldSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	// End UWorldSubsystem interface

	/**
	 * Returns the drop pod refunds loot pool for the actor with the given type
	 * Will automatically attempt to look up loot pool for parent class if there is no override for the child class
	 * The returned object is a transient copy made by drop pod subsystem, so it can be modified freely
	 * to adjust the drop pod loots in runtime.
	 */
	UFUNCTION( BlueprintPure, Category = "Drop Pod Subsystem" )
	UFGDropPodRefundsLootPool* GetDropPodLootPoolForActorClass( TSubclassOf<AFGCrashSiteBaseActor> ActorClass ) const;

	/**
	 * Creates the drop pod loot pool for the given actor class, or returns the existing one
	 * The returned entry will be automatically populated with the entries from it's parent loot pool (if such pool exists)
	 */
	UFUNCTION( BlueprintCallable, Category = "Drop Pod Subsystem" )
	UFGDropPodRefundsLootPool* CreateDropPodLootPool( TSubclassOf<AFGCrashSiteBaseActor> ActorClass, TSubclassOf<UFGDropPodRefundsLootPool> LootPoolClass );
protected:
	UPROPERTY()
	TMap<UClass*, UFGDropPodRefundsLootPool*> mDropPodLootPools;
};
