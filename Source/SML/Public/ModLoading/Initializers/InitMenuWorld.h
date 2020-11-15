#pragma once
#include "BasicModInit.h"
#include "InitMenuWorld.generated.h"

enum class ELifecyclePhase : uint8;

/**
 * This actor is spawned every time Menu world is loaded to allow
 * mods to modify menu world by adding additional objects to it
 * For SML to load your InitMenuWorld subclass, it should be located exactly at
 * /Game/YourModReference/InitMenuWorld/
 */
UCLASS(Abstract, Blueprintable)
class SML_API AInitMenuWorld : public ABasicModInit {
	GENERATED_BODY()
public:
	/** Called when menu world is fully initialized */
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	/** Called prior to Init, allows C++ functionality */
	virtual void InitNative();
private:
	/** Called when mod loader dispatches new lifecycle phase */
	virtual void DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase) override;
};