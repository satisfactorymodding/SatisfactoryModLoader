#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGRecipe.h"
#include "AssetLinting.generated.h"

UENUM(BlueprintType)
enum class ELintingResultSeverity : uint8 {
	// Information for the developer about the asset
	NOTICE,
	// Could confuse end users, but asset will still behave as expected of Satisfactory assets
	WARNING,
	// Will lead to unexpected/edge-case asset behavior
	ERROR,
	// Will almost certainly prevent the asset from being usable
	CRITICAL
};

// For reflection system visibility
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class URecipeLintingCheckInterface : public UInterface {
	GENERATED_BODY()
};


class SMLEDITOR_API IRecipeLintingCheckInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	const bool CheckRecipe(TSubclassOf<UFGRecipe> recipe, FString &out_message, ELintingResultSeverity &out_severity);
};
