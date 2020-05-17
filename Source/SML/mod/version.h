#pragma once
#include "CoreMinimal.h"

enum EVersionComparisonOp {
	EQUALS,
    GREATER,
    GREATER_EQUALS,
    LESS,
    LESS_EQUALS
};
		
class FVersion {
public:
    uint64_t Major;
	uint64_t Minor;
	uint64_t Patch;
	FString Type;
	FString BuildInfo;

	FVersion();
	FVersion(const FString& string);
public:
    FString String() const;
	int Compare(const FVersion& other) const;
};
class FVersionRange {
private:
    EVersionComparisonOp Op;
	FVersion MyVersion;
public:
    FVersionRange();
	FVersionRange(const FString& string);

	FString String() const;
	bool Matches(const FVersion& version) const;
};
