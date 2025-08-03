#include "FGFallbackProfanityFilter.h"

#include "Internationalization/Regex.h"

UFGWordList* UFGFallbackProfanityFilterSettings::GetWordList() const{ return nullptr; }
const FRegexPattern& UFGFallbackProfanityFilterSettings::GetRegex() const{ return mRegex.GetValue(); }
FString UFGFallbackProfanityFilter::FilterString(const FString& UnfilteredString){ return FString(); }
TArray<FString> UFGFallbackProfanityFilter::FilterStrings(const TArray<FString>& UnfilteredStrings){ return TArray<FString>(); }