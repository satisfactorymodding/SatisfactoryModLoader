// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGVirtualKeyboardLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams( FFGOnVirtualKeyboardClosedDelegate, bool, bCanceled, FText, NewText );

UENUM( BlueprintType )
enum class EFGVirtualKeyboardType : uint8
{
	DEFAULT = 0    UMETA( DisplayName = "Default" ),
	NUMBER  = 1    UMETA( DisplayName = "Number" )
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGVirtualKeyboardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	static void ShowVirtualKeyboard( FText InitialText, FFGOnVirtualKeyboardClosedDelegate ClosedDelegate, EFGVirtualKeyboardType KeyboardType = EFGVirtualKeyboardType::DEFAULT );
};
