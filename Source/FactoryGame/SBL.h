// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SBL.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FACTORYGAME_API UDebugLogger : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = 1), Category = "SML|Log")
		static void logInfo(FString str, bool ignoreDebugMode);

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = 1), Category = "SML|Log")
		static void logWarning(FString str, bool ignoreDebugMode);

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = 1), Category = "SML|Log")
		static void logError(FString str, bool ignoreDebugMode);

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay = 1), Category = "SML|Log")
		static void logDebug(FString str, bool ignoreDebugMode);
};

UCLASS(Abstract)
class FACTORYGAME_API UModHandler : public UObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SML|Environment")
		static bool isDebugMode();

	UFUNCTION(BlueprintCallable, Category = "SML|Environment")
		static void broadcastEvent(FString event);

	UFUNCTION(BlueprintCallable, Category = "SML|Environment")
		static bool doesPakExist(FString pak);

	UFUNCTION(BlueprintCallable, Category = "SML|Environment")
		static bool isDllLoaded(FString dll);
};
