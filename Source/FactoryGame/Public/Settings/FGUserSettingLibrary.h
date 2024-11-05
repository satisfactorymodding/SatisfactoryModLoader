// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGUserSettingLibrary.generated.h"

class UFGUserSetting;
class IFGOptionInterface;

/**
 * Blueprintlibrary with BlueprintInternalUseOnly getter functions for settings.
 * These are used by custom node UFGK2Node_GetSettingValue.
 * NOTE: Renaming these functions or changing signatures might also require changes to FGK2Node_GetSettingValue and FGK2Node_SetSettingValue
 */
UCLASS()
class FACTORYGAME_API UFGUserSettingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true", WorldContext = "worldContext" ) )
	static bool GetBoolValue( TScriptInterface<IFGOptionInterface> optionInterface, UFGUserSetting* setting, bool& out_displayValue, UObject* worldContext );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true", WorldContext = "worldContext" ) )
	static int32 GetInt32Value( TScriptInterface<IFGOptionInterface> optionInterface, UFGUserSetting* setting, int32& out_displayValue, UObject* worldContext );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true", WorldContext = "worldContext" ) )
	static float GetFloatValue( TScriptInterface<IFGOptionInterface> optionInterface, UFGUserSetting* setting, float& out_displayValue, UObject* worldContext );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true", WorldContext = "worldContext" ) )
	static void SetBoolValue( TScriptInterface<IFGOptionInterface> optionInterface, UFGUserSetting* setting, bool value, bool forceSet, UObject* worldContext );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true", WorldContext = "worldContext" ) )
	static void SetInt32Value( TScriptInterface<IFGOptionInterface> optionInterface, UFGUserSetting* setting, int32 value, bool forceSet, UObject* worldContext );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true", WorldContext = "worldContext" ) )
	static void SetFloatValue( TScriptInterface<IFGOptionInterface> optionInterface, UFGUserSetting* setting, float value, bool forceSet, UObject* worldContext );
};
