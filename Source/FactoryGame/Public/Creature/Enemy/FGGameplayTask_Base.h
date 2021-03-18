// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "FGGameplayTask_Base.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameplayTask_Base : public UGameplayTask
{
	GENERATED_BODY()
public:
	virtual void InitSimulatedTask( UGameplayTasksComponent& InGameplayTasksComponent ) override;
public:
	/** Cache the pawn that we have */
	UPROPERTY()
	class AFGEnemy* mCachedPawn;
	
};
