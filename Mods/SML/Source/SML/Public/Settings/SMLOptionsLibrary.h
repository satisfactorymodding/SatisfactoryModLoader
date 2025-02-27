#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGOptionInterface.h"

#include "SMLOptionsLibrary.generated.h"

UCLASS()
class SML_API USMLOptionsLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
  	/** Set the option value for a string. Needs to be applied to take effect and/or get saved. */
	UFUNCTION(BlueprintCallable, Category = "Option")
	static void SetStringOptionValue(TScriptInterface<IFGOptionInterface> option, const FString& cvar, const FString& newValue) {
		option->SetOptionValueTyped<FString>(cvar, newValue);
	}

	/** Get the option value for a string. Note that in the session settings menu, this value doesn't reflect pending changes - use GetStringUIDisplayValue for that. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Option")
	static const FString GetStringOptionValue(const TScriptInterface<IFGOptionInterface> option, const FString& cvar) {
		return option->GetOptionValueTyped<FString>(cvar);
	}

	/** Get the current UI value for a string. Doesn't always match the active value. Should only be used in the session settings menu. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Option")
	static const FString GetStringUIDisplayValue(const TScriptInterface<IFGOptionInterface> option, const FString& cvar) {
		return option->GetOptionDisplayValueTyped<FString>(cvar);
	}
};
