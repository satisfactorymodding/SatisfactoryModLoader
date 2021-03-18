// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGOptionsSettings.h"
#include "FGOptionsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGOptionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION( BlueprintPure, Category="Options" )
	static TArray<class UFGDynamicOptionsRow*> GetDynamicOptionsWidgets( UUserWidget* owningWidget, EOptionCategory category );

	static void GetDynamicOptionData( TArray<FOptionRowData>& out_optionRowData );

private:
	
	static TArray<class UFGDynamicOptionsRow*> SetupOptionRows( UUserWidget* owningWidget, TArray<FOptionRowData> optionRows, EOptionCategory optionCategory, TSubclassOf< class UFGDynamicOptionsRow > optionsRowWidgetClass );

};
