// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGHUDBase.h"
#include "FGMainMenuHUD.generated.h"

//<FL>[KonradA]
DECLARE_MULTICAST_DELEGATE( FOnGameStartupSequenceDone );
//</FL>
/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGMainMenuHUD : public AFGHUDBase
{
	GENERATED_BODY()

public:
	//<FL>
	FOnGameStartupSequenceDone OnGameStartupSequenceDone;

	UFUNCTION(BlueprintCallable)
	void DispatchOnGameStartupSequenceDone() { OnGameStartupSequenceDone.Broadcast(); };
	//</FL>

	virtual void BeginPlay() override;

	void Native_ShowMainMenu();
	UFUNCTION( BlueprintImplementableEvent, Category = "HUD" )
	void ShowMainMenu();
	
};
