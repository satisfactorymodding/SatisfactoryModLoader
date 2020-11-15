#pragma once
#include "GameFramework/Actor.h"
#include "BasicModInit.generated.h"

/** Describes lifecycle phase of the world aware initializer actor */
enum class ELifecyclePhase : uint8 {
    /** Dispatched right after mod actor is spawned */
    CONSTRUCTION,
    /** Dispatched when all mod actors are spawned in dependency order */
    INITIALIZATION,
    /** Dispatched when world is initialized in dependency order */
    POST_INITIALIZATION
};

/**
 * Basic class for actors capable of reacting to mod lifecycle events
 */
UCLASS(Abstract, NotBlueprintable, HideCategories = ("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class SML_API ABasicModInit : public AActor {
    GENERATED_BODY()
    friend class FModHandler;
public:
    /** ModReference of the mod this Init Actor belongs to */
    UFUNCTION(BlueprintPure)
    FORCEINLINE FString GetOwnerModReference() const { return OwnerModReference; }
protected:
    /** Called by mod loader when lifecycle events occurs */
    virtual void DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase);
private:
    /** Private field holding owner mod reference, accessible directly only by mod loader */
    FString OwnerModReference;
};
