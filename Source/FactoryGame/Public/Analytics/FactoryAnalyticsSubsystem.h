// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "FactoryAnalyticsSubsystem.generated.h"

//@todo-telemetry This name is now outdated, lets rename this class to make it clearer that this is about error reporting within the game.
/**
 * Performs initialization of analytics and error reporting services. 
 */
UCLASS()
class FACTORYGAME_API UFactoryAnalyticsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize( FSubsystemCollectionBase& Collection ) override;
	virtual bool ShouldCreateSubsystem( UObject* Outer ) const override; // <FL> [ZimmermannA] Added to prevent a non-fatal ensure error on console on game start-up.

private:
	void ConfigureTags( class USentrySubsystem* Sentry );
};
