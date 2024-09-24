#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SMLBlueprintStringLibrary.generated.h"

UCLASS()
class SML_API USMLBlueprintStringLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "string < string", CompactNodeTitle = "<", Keywords = "< less"), Category = "Utilities | String")
	static bool Less_StringString(const FString& A, const FString& B);

	/** Returns true if A is greater than B (A > B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "string > string", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Utilities | String")
	static bool Greater_StringString(const FString& A, const FString& B);

	/** Returns true if A is less than B (A < B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "string <= string", CompactNodeTitle = "<=", Keywords = "< less"), Category = "Utilities | String")
	static bool LessEqual_StringString(const FString& A, const FString& B);

	/** Returns true if A is greater than or equal to B (A >= B) */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "string >= string", CompactNodeTitle = ">=", Keywords = ">= greater"), Category = "Utilities | String")
	static bool GreaterEqual_StringString(const FString& A, const FString& B);
};
