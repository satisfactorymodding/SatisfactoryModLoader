
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "RuntimeBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SML_API URuntimeBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		// Tries to find a Class by Name 
		// Use Object->ObjectName.Append("_C") as input
		UFUNCTION(BlueprintCallable, Category = "SML | Class")
		static UClass * FindClassByName(FString ClassNameInput);

	
};
