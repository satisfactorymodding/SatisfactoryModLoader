// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	
	static TArray<class UFGDynamicOptionsRow*> GetDynamicOptionsWidgets( UUserWidget* owningWidget, EOptionCategory category, TScriptInterface< class IFGOptionInterface > optionInterface );

	static void GetDynamicOptionData( TArray<FOptionRowData>& out_optionRowData );
	
	static TArray<class UFGDynamicOptionsRow*> SetupOptionRows( UUserWidget* owningWidget, TArray<FOptionRowData> optionRows, EOptionCategory optionCategory, TSubclassOf< class UFGDynamicOptionsRow > optionsRowWidgetClass, TScriptInterface< class IFGOptionInterface > optionInterface );
	
	static UFGDynamicOptionsRow* SetupUserSetting( UUserWidget* owningWidget, class UFGUserSetting* userSetting, TScriptInterface< class IFGOptionInterface > optionInterface );

};
