// Copyright Coffee Stain Studios. All Rights Reserved.

/*

*/
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGVirtualCursorFunctionLibrary.generated.h"

/**
*
*/
UCLASS()
class FACTORYGAME_API UFGVirtualCursorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintCallable, Category = "Game" )
	static void EnableVirtualCursor( class APlayerController* PC );

	UFUNCTION( BlueprintCallable, Category = "Game" )
	static void DisableVirtualCursor( class APlayerController* PC );
};