// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableFactory.h"
#include "FGColoredInstanceMeshProxy.h"
#include "FGProductionIndicatorInstanceManager.h"
#include "FGProductionIndicatorInstanceComponent.generated.h"

USTRUCT()
struct FFGIndicatorReaction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 FlashingPattern;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor mColor;
};

/**
 * Instanced production indicator, used on factories instead of the old non instanced variant.
 */
UCLASS( Blueprintable, ClassGroup = ( FactoryGame ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGProductionIndicatorInstanceComponent : public UFGColoredInstanceMeshProxy
{
	GENERATED_BODY()
public:
	UFGProductionIndicatorInstanceComponent();
	
	/** Called when the buildings indicator status changes. */
	UFUNCTION()
	void OnProductionStatusChanged( EProductionStatus newStatus );

	/** Forcefully applies the current state of the indicator to the mesh */
	void ForceUpdateVisuals();

	void SetVisuals( EProductionStatus newStatus );

protected:
	UPROPERTY(EditDefaultsOnly)
	FFGIndicatorReaction mStateNoneData;

	UPROPERTY(EditDefaultsOnly)
	FFGIndicatorReaction mStateActiveData;
	
	UPROPERTY(EditDefaultsOnly)
	FFGIndicatorReaction mStateActiveWithCrystalData;

	UPROPERTY(EditDefaultsOnly)
	FFGIndicatorReaction mStateErrorData;

	UPROPERTY(EditDefaultsOnly)
	FFGIndicatorReaction mStateStandbyData;

private:
	/** Save the state of the factory so that we don't change material excessively. */
	EProductionStatus mCachedIndicatorStatus;

};
