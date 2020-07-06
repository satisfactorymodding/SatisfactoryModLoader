#pragma once
#include "CoreMinimal.h"
#include "SemVersion.generated.h"

enum EVersionComparisonOp {
	EQUALS,
	GREATER,
	GREATER_EQUALS,
	LESS,
	LESS_EQUALS,
	CARET
};

USTRUCT(BlueprintType)
struct FVersion {
	GENERATED_USTRUCT_BODY()
public:
	/** Major version number */
	UPROPERTY(BlueprintReadOnly)
    int64 Major;
	/** Minor version number */
	UPROPERTY(BlueprintReadOnly)
	int64 Minor;
	/** Patch number */
	UPROPERTY(BlueprintReadOnly)
	int64 Patch;
	/** Version type (alpha/beta/release) */
	UPROPERTY(BlueprintReadOnly)
	FString Type;
	/** Additional version build info */
	UPROPERTY(BlueprintReadOnly)
	FString BuildInfo;

	FVersion();
	FVersion(const FString& string);
public:
	/** Combines version data into the string */
    FString String() const;
	/** Compares this version with other version */
	int Compare(const FVersion& other) const;
};

class FVersionRange {
private:
    EVersionComparisonOp Op;
	FVersion MyVersion;
public:
    FVersionRange();
	inline FVersionRange(FVersion Version, EVersionComparisonOp Operator) : Op(Operator), MyVersion(Version) {}
	FVersionRange(const FString& string);

	FString String() const;
	bool Matches(const FVersion& version) const;
};
