// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGMapBlueprintHelper.generated.h"

class UWidget;

UCLASS()
class FACTORYGAME_API UFGMapBlueprintHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Map" )
	static bool IsOverlapping( UWidget* currentWidget, UWidget* widgetToCheck);
};
