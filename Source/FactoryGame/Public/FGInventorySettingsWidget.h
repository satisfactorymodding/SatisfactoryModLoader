// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UI/FGUserWidget.h"
#include "FGInventorySettingsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventorySettingsWidgetClosed );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGInventorySettingsWidget : public UFGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ExposeOnSpawn = true))
	class AFGEquipment* mEquipment;

	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category = Settings )
	FOnInventorySettingsWidgetClosed OnInventorySettingsWidgetClosed;

};
