// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEventsSubsystem.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "FGErrorHandlingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGErrorHandlingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	void HandleGameplayEvent(const FGameplayEvent& GameplayEvent);
};
