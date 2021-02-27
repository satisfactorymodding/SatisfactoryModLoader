// Copyright 2016-2020 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGDebugOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGDebugOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Begin UUsserwidget interface 
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;
	virtual void RemoveFromParent() override;
	// End UUserwidget interface
	
	UFUNCTION()
    void UpdateDebugOverlay();

	UFUNCTION( BlueprintImplementableEvent, Category = "Debug" )
	void UpdateDebugOverlayData( const TArray<FString>& debugOverlayData );

private:
	FTimerHandle mUpdateDebugOverlayTimerHandle;
};
