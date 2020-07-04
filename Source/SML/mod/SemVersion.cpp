#pragma once
#include "SemVersion.h"
#include "util/Utility.h"
#include "util/Logging.h"
#include <regex>

std::wregex VersionRegex(TEXT("^(<=|<|>|>=|\\^)?(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:-((?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\\.(?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\\+([0-9a-zA-Z-]+(?:\\.[0-9a-zA-Z-]+)*))?$"), std::regex::ECMAScript | std::regex::optimize);

void parseVersion(const FString& string, FVersion& version, FString* compareOp);

EVersionComparisonOp parseComparisonOp(const FString& type) {
	if (type == TEXT("<="))
		return EVersionComparisonOp::LESS_EQUALS;
	if (type == TEXT("<"))
		return EVersionComparisonOp::LESS;
	if (type == TEXT(">="))
		return EVersionComparisonOp::GREATER_EQUALS;
	if (type == TEXT(">"))
		return EVersionComparisonOp::GREATER;
	if (type == TEXT("^"))
		return EVersionComparisonOp::CARET;
	return EVersionComparisonOp::EQUALS;
}

const TCHAR* comparisonString(const EVersionComparisonOp op) {
	switch (op) {
	case EVersionComparisonOp::EQUALS: return TEXT("");
	case EVersionComparisonOp::GREATER: return TEXT(">");
	case EVersionComparisonOp::GREATER_EQUALS: return TEXT(">=");
	case EVersionComparisonOp::LESS: return TEXT("<");
	case EVersionComparisonOp::LESS_EQUALS: return TEXT("<=");
	case EVersionComparisonOp::CARET: return TEXT("^");
	default: return TEXT("");
	}	
}

FVersion::FVersion() {}

FVersion::FVersion(const FString& string) {
	FString compareOp;
	parseVersion(string, *this, &compareOp);
	if (!compareOp.IsEmpty()) {
		SML::Logging::error(TEXT("Unexpected comparison on version declaration"));
	}
}

FVersionRange::FVersionRange() {}

FVersionRange::FVersionRange(const FString& string) {
	FString comparisonOp;
	parseVersion(string, MyVersion, &comparisonOp);
	this->Op = parseComparisonOp(comparisonOp);
}

bool FVersionRange::Matches(const FVersion& version) const {
	int result = version.Compare(MyVersion);
	switch (Op) {
	case EVersionComparisonOp::GREATER_EQUALS: return result >= 0;
	case EVersionComparisonOp::GREATER: return result > 0;
	case EVersionComparisonOp::LESS_EQUALS: return result <= 0;
	case EVersionComparisonOp::LESS: return result < 0;
	case EVersionComparisonOp::CARET: {
		if(result < 0) {
			return false;
		}
		FVersion maxVersion;
		if(MyVersion.Major == 0) {
			if(MyVersion.Minor == 0) {
				maxVersion.Patch = MyVersion.Patch + 1;
			}
			else {
				maxVersion.Minor = MyVersion.Minor + 1;
			}
		}
		else {
			maxVersion.Major = MyVersion.Major + 1;
		}
		return version.Compare(maxVersion) < 0;
	}
	default: return result == 0;
	}
}

void parseVersion(const FString& string, FVersion& version, FString* compareOp) {
	std::wsmatch Match;
	const std::wstring WideString(*string);
	if (!std::regex_match(WideString, Match, VersionRegex)) {
		SML::Logging::error(*FString::Printf(TEXT("Version string \"%s\" doesn't match the pattern"), *string));
		return;
	}
	if (compareOp != nullptr)
		*compareOp = Match[1].str().c_str();
	version.Major = std::stoull(Match[2]);
	version.Minor = std::stoull(Match[3]);
	version.Patch = std::stoull(Match[4]);
	version.Type = Match[5].str().c_str();
	version.BuildInfo = Match[6].str().c_str();
}

FString FVersion::String() const {
	FString result;
	result.Append(FString::FromInt(Major)).Append(TEXT("."));
	result.Append(FString::FromInt(Minor)).Append(TEXT("."));
	result.Append(FString::FromInt(Patch));
	if (!Type.IsEmpty())
		result.Append(TEXT("-")).Append(Type);
	if (!BuildInfo.IsEmpty())
		result.Append(TEXT("+")).Append(BuildInfo);
	return result;
}

FString FVersionRange::String() const {
	return comparisonString(this->Op) + MyVersion.String();
}

int FVersion::Compare(const FVersion& other) const {
	if (Major != other.Major)
		return Major > other.Major ? 1 : -1;
	if (Minor != other.Minor)
		return Minor > other.Minor ? 1 : -1;
	if (Patch != other.Patch)
		return Patch > other.Patch ? 1 : -1;
	return Type.Compare(other.Type);
}