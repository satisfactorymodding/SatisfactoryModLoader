#include "Util/BlueprintVersionLibrary.h"

bool UBlueprintVersionLibrary::ParseVersionString(const FString& String, FVersion& OutVersion, FString& ErrorMessage) {
    return OutVersion.ParseVersion(String, ErrorMessage);
}

FString UBlueprintVersionLibrary::Conv_VersionToString(const FVersion& Version) {
    return Version.ToString();
}

bool UBlueprintVersionLibrary::ParseVersionRangeString(const FString& String, FVersionRange& OutVersionRange, FString& OutErrorMessage) {
    return OutVersionRange.ParseVersionRange(String, OutErrorMessage);
}

FString UBlueprintVersionLibrary::Conv_VersionRangeToString(const FVersionRange& VersionRange) {
    return VersionRange.ToString();
}

bool UBlueprintVersionLibrary::Matches(const FVersionRange& VersionRange, const FVersion& Version) {
    return VersionRange.Matches(Version);
}
