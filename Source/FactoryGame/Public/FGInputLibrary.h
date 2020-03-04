// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"
#include "TextProperty.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Input/Events.h"
#include "FGInputLibrary.generated.h"


USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGKeyMapping
{
	GENERATED_BODY()

	FFGKeyMapping() : 
		IsAxisMapping( false )
	{
	}
	
	UPROPERTY( BlueprintReadOnly, Category = "Input" )
	FInputActionKeyMapping ActionKeyMapping;
	
	UPROPERTY( BlueprintReadOnly, Category = "Input" )
	FInputAxisKeyMapping AxisKeyMapping;

	UPROPERTY( BlueprintReadOnly, Category = "Input" )
	bool IsAxisMapping;


public:
	FORCEINLINE ~FFGKeyMapping() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGInputLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	/** Check if action mappings is using the same relevant keys */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsActionMappingUsingSameKeys( const FInputActionKeyMapping& mappingA, const FInputActionKeyMapping& mappingB );

	/** Check if axis mappings is using the same relevant keys */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsAxisMappingUsingSameKeys( const FInputAxisKeyMapping& mappingA, const FInputAxisKeyMapping& mappingB );

	/** Check if an action and axis mapping is using the same relevant keys */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsActionAndAxisMappingUsingSameKeys( const FInputActionKeyMapping& actionMapping, const FInputAxisKeyMapping& axisMapping );

	/** Create new FG key mapping struct */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FFGKeyMapping CreateFGKeyMappingStruct( FName actionName, bool isAxisMapping, bool positiveAxisScale, FInputEvent inputEvent, FKey keyPressed );

	/** Find and set overlapping key mapping to none */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void NullKeyMappingWithSameKeyCombo( APlayerController* playerController, const FFGKeyMapping& keyMapping );

	/** Check if a FG key mapping is available */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsFGKeyMappingAvailable( APlayerController* playerController, const FFGKeyMapping& keyMapping );

	/** Check if a action key mapping is available */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsActionKeyMappingAvailable( APlayerController* playerController, const FFGKeyMapping& keyMapping );

	/** Check if a axis key mapping is available */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsAxisKeyMappingAvailable( APlayerController* playerController, const FFGKeyMapping& keyMapping );

	/** Returns the key mapping that uses the same relevant keys */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FFGKeyMapping GetOverlappingKeyMapping( APlayerController* playerController, const FFGKeyMapping& keyMapping );

	/** Rebind a key mapping */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static bool RebindKey( APlayerController* playerController, const FFGKeyMapping& newKeyMapping );

	/** Update the provided playercontrollers input mappings */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	static void UpdateInputMappings( APlayerController* playerController );

	/** Returns the action key mapping for the action we specify */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FInputActionKeyMapping GetKeyMappingForAction( APlayerController* playerController, FName inAction, bool getGamepadKey );

	/** Returns readable name for an action */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText GetKeyNameForAction( APlayerController* playerController, FName actionName, bool getGamepadKey, bool abbreviateKeyName = true);
	
	/** Returns the FKey for the axis we specify */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FKey GetKeyForAxis( APlayerController* playerController, FName axisName, bool positiveAxisScale, bool getGamepadKey );

	/** Returns readable name for an axis */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText GetKeyNameForAxis( APlayerController* playerController, FName axisName, bool positiveAxisScale, bool getGamepadKey );

	/** Returns a shortened name for a key */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText GetAbbreviatedKeyName( FKey key );

	/** Replaces action names in the provided text with the corresponding key e.g. ({PrimaryFire} = LMB) */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static FText FormatStringWithKeyNames( APlayerController* playerController, FText textToFormat, bool abbreviateKeyNames = true );

	/** Check if a key mapping is relevant for rebinding */
	UFUNCTION( BlueprintPure, Category = "Input" )
	static bool IsKeyMappingRelevant( FName keyMappingName );

private:
	static const TArray<FString> IRRELEVANT_PREFIXES;

public:
	FORCEINLINE ~UFGInputLibrary() = default;
};
