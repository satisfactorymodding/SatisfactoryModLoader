#pragma once
#include "UnrealString.h"

#include "Engine/EngineBaseTypes.h"
#include "FactoryTick.generated.h"

/**
 * Tick function that calls AFGBuildable::TickFactory
 */
USTRUCT()
struct FACTORYGAME_API FFactoryTickFunction : public FTickFunction
{
	GENERATED_USTRUCT_BODY()

	/** Buildable that is the target of this tick. */
	class AFGBuildableSubsystem* Target;

	/**
	 * Abstract function actually execute the tick.
	 * @param DeltaTime - frame time to advance, in seconds
	 * @param TickType - kind of tick for this frame
	 * @param CurrentThread - thread we are executing on, useful to pass along as new tasks are created
	 * @param MyCompletionGraphEvent - completion event for this task. Useful for holding the completetion of this task until certain child tasks are complete.
	 */
	virtual void ExecuteTick( float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent ) override;
	/** Abstract function to describe this tick. Used to print messages about illegal cycles in the dependency graph **/
	virtual FString DiagnosticMessage() override;

public:
	FORCEINLINE ~FFactoryTickFunction() = default;
};

template<>
struct FACTORYGAME_API TStructOpsTypeTraits<FFactoryTickFunction> : public TStructOpsTypeTraitsBase2<FFactoryTickFunction>
{
	enum
	{
		WithCopy = false
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits<FFactoryTickFunction>() = default;
};