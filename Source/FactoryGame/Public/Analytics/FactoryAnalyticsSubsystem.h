// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "FactoryAnalyticsSubsystem.generated.h"

/**
 * Performs initialization of analytics and error reporting services. 
 */
UCLASS()
class FACTORYGAME_API UFactoryAnalyticsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize( FSubsystemCollectionBase& Collection ) override;

private:
	void ConfigureTags( class USentrySubsystem* Sentry );
};
