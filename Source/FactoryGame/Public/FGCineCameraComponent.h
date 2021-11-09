// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "CineCameraComponent.h"
#include "FGCineCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCineCameraComponent : public UCineCameraComponent
{
	GENERATED_BODY()

public:
	UFGCineCameraComponent();
	
	void Photo_SetManualFocusDistance( float manualFocusDistance );
	void Photo_SetAperture( float aperture );
	void Photo_FocusTrackLookedAtObject();
	void Photo_ResetToDefault();

	void StartDelayedDestruction();
	void StopDelayedDestruction();

	void GetDebugStrings( TArray<FString>& out_debugText );

private:
	UFUNCTION()
	void ShowDebug();

	void TraceForObjects(struct FHitResult& out_hitResult );

	FTimerHandle mDelayedDestructionTimer;

};
