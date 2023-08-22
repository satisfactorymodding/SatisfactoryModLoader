// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGUserSettingLibrary.generated.h"

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
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ) )
	static bool GetBoolValue( class UFGUserSetting* setting, bool& out_displayValue );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ) )
	static int32 GetInt32Value( class UFGUserSetting* setting, int32& out_displayValue );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ) )
	static float GetFloatValue( class UFGUserSetting* setting, float& out_displayValue );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ) )
	static void SetBoolValue( class UFGUserSetting* setting, bool value, bool forceSet );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ) )
	static void SetInt32Value( class UFGUserSetting* setting, int32 value, bool forceSet );
	UFUNCTION (BlueprintCallable, meta=( BlueprintInternalUseOnly="true" ) )
	static void SetFloatValue( class UFGUserSetting* setting, float value, bool forceSet );
};
