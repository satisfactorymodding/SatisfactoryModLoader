// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGHUDBase.h"
#include "FGMainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGMainMenuHUD : public AFGHUDBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void Native_ShowMainMenu();
	UFUNCTION( BlueprintImplementableEvent, Category = "HUD" )
	void ShowMainMenu();
	
};
