// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FGHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGHUDBase : public AHUD
{
	GENERATED_BODY()
public:
	/** Sets the base UI */
	void SetBaseUI( class UFGBaseUI* newUI );

	/** Returns base ui */
	UFUNCTION( BlueprintPure, Category = "HUD" )
	FORCEINLINE class UFGBaseUI* GetBaseUI() { return mBaseUI; }
private:
	/** Reference to the UI widget */
	UPROPERTY()
	class UFGBaseUI* mBaseUI;
	
};
