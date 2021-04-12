// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGDebugOverlayWidget.generated.h"

UENUM( BlueprintType )
enum class EDebugOverlayType : uint8
{
	DOT_Default,
    DOT_Story,
	DOT_Options
};

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

	void SetDebugOverlayType( EDebugOverlayType type );

	UFUNCTION( BlueprintPure, Category = "Debug" )
	FORCEINLINE EDebugOverlayType GetCurrentDebugOverlayType() const { return mCurrentDebugOverlayType; }

protected:
	UFUNCTION()
    void GetDefaultOverlayData( TArray<FString>& out_debugOverlayData );

	UFUNCTION()
	void GetStoryOverlayData( TArray<FString>& out_debugOverlayData );

	UFUNCTION()
	void GetOptionsOverlayData( TArray<FString>& out_debugOverlayData );
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Debug" )
	void UpdateDebugOverlayData( const TArray<FString>& debugOverlayData );

private:
	FTimerHandle mUpdateDebugOverlayTimerHandle;

	EDebugOverlayType mCurrentDebugOverlayType;
};
