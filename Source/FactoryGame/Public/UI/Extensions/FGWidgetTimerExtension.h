// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/TimerHandle.h"
#include "Extensions/UserWidgetExtension.h"
#include "FGWidgetTimerExtension.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FTickDynamicDelegate, float, DeltaTime, float, LerpAlpha);
/**
 * This extension allows adding timer functionality to any FGUSerWidget, with a possibility to tick for some small specified duration and be automatically removed on widget destruction.
 */
UCLASS()
class FACTORYGAME_API UFGWidgetTimerExtension : public UUserWidgetExtension
{
	GENERATED_BODY()
public:
	virtual void Destruct() override;

	virtual bool RequiresTick() const  override;

	virtual void Tick(const FGeometry& MyGeometry, float InDeltaTime)  override;
	
	void StartTickForDuration( FTickDynamicDelegate Delegate, float inDuration );
	void Finish();
	
private:
	FTickDynamicDelegate TickDelegate;
	float DurationToTick { 0.0f };
	float AccumulatedTickTime { 0.0f };
};
