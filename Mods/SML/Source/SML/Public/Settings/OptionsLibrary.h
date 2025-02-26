#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGOptionInterface.h"

#include "OptionsLibrary.generated.h"

UCLASS()
class SML_API UOptionsLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
  	/** Set the option value for a string, will need to be applied to take effect and/or get saved */
	UFUNCTION(BlueprintCallable, Category = "Option")
	static void SetStringOptionValue(TScriptInterface<IFGOptionInterface> options, const FString& cvar, const FString& newValue) {
		options->SetOptionValueTyped<FString>(cvar, newValue);
	}

	UFUNCTION(BlueprintCallable, Category = "Option")
	static FString GetStringOptionValue(const TScriptInterface<IFGOptionInterface> options, const FString& cvar) { 
		return options->GetOptionValueTyped<FString>(cvar); 
	}

	/** Get the current UI value for an string. Doesn't always match the active value. Should only be used in the session settings menu. */
	UFUNCTION(BlueprintCallable, Category = "Option")
	static FString GetStringUIDisplayValue(const TScriptInterface<IFGOptionInterface> options, const FString& cvar) {
		return options->GetOptionDisplayValueTyped<FString>(cvar); 
	}
};
