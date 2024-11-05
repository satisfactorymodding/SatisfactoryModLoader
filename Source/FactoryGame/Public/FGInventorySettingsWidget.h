// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGInventorySettingsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnInventorySettingsWidgetClosed );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGInventorySettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ExposeOnSpawn = true))
	class AFGEquipment* mEquipment;

	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category = Settings )
	FOnInventorySettingsWidgetClosed OnInventorySettingsWidgetClosed;

};
