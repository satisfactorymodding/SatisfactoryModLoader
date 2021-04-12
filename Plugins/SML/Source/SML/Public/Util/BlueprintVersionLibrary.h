#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Util/SemVersion.h"
#include "BlueprintVersionLibrary.generated.h"

UCLASS()
class SML_API UBlueprintVersionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /** Constructs SemVer Version from version string */
    UFUNCTION(BlueprintPure, Category = "SML|Versioning", meta = (BlueprintThreadSafe))
    static bool ParseVersionString(const FString& String, FVersion& OutVersion, FString& ErrorMessage);

    /** Converts version data to the string */
    UFUNCTION(BlueprintPure, Category = "SML|Versioning", meta = (DisplayName = "ToString (Version)", CompactNodeTitle = "->", ScriptMethod="ToString", BlueprintThreadSafe))
    static FString Conv_VersionToString(const FVersion& Version);

    /** Constructs SemVer Version Range from version string */
    UFUNCTION(BlueprintPure, Category = "SML|Versioning", meta = (BlueprintThreadSafe))
    static bool ParseVersionRangeString(const FString& String, FVersionRange& OutVersionRange, FString& OutErrorMessage);

    /** Converts version data to the string */
    UFUNCTION(BlueprintPure, Category = "SML|Versioning", meta = (DisplayName = "ToString (VersionRange)", CompactNodeTitle = "->", ScriptMethod="ToString", BlueprintThreadSafe))
    static FString Conv_VersionRangeToString(const FVersionRange& VersionRange);

    /** Compares the version against range and returns true if it satisfies version range */
    UFUNCTION(BlueprintPure, Category = "SML|Versioning", meta = (DisplayName = "Matches (Version)", BlueprintThreadSafe))
    static bool Matches(const FVersionRange& VersionRange, const FVersion& Version);
};
