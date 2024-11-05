// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineInteractionHandlers.h"
#include "GameFramework/HUD.h"
#include "UI/FGDebugOverlayWidget.h"
#include "FGHUDBase.generated.h"

/** Z-order values for sub widgets. */
enum EWidgetOrder
{
	EWO_GameUI = 0,
	EWO_Respawn = 1,
	EWO_DebugOverlay = 2,
	EWO_Cheatmenu = 10, // Changed to 10 to be above game UI otherwise you can't interact with it
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGHUDBase : public AHUD, public ISessionCreationInteractionHandler
{
	GENERATED_BODY()
public:
	/** Sets the base UI */
	void SetBaseUI( class UFGBaseUI* newUI );

	/** Returns base ui */
	UFUNCTION( BlueprintPure, Category = "HUD" )
	FORCEINLINE class UFGBaseUI* GetBaseUI() { return mBaseUI; }

	virtual void ShowSessionCreationFailurePopup( FOnlineSessionPromptResultKnown delegate ) override;
	virtual void HideSessionCreationFailurePopup() override;

	// We want these exec functions here instead of in the FGHUD since we only have a FGHUDBase in the main menu. Don't want to change that for the moment
	void ToggleDebugOverlayWidget( UWorld* world, EDebugOverlayType type );
	UFUNCTION( Exec )
	void ToggleDebugOverlay();
	UFUNCTION( Exec )
	void ToggleStoryDebugOverlay();
	UFUNCTION( Exec )
	void ToggleOptionsDebugOverlay();
	UFUNCTION( Exec )
	void ToggleAdvancedGameSettingsDebugOverlay();
	UFUNCTION( Exec )
	void ToggleStatisticsDebugOverlay();
	UFUNCTION( Exec )
	void ToggleShoppingListDebugOverlay();
	UFUNCTION( Exec )
	void ToggleOnlineInfoDebugOverlay();
	UFUNCTION( Exec )
	void QuickSwitchLanguage();
	
private:
	/** Reference to the UI widget */
	UPROPERTY()
	class UFGBaseUI* mBaseUI;
	
};
