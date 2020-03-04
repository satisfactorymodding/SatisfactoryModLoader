#pragma once
#include "version.h"
#include <regex>
#include "util/Utility.h"
#include "util/Logging.h"

using namespace SML::Versioning;

std::wregex versionRegex(TEXT("^(<=|<|>|>=|\\^)?(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:-((?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\\.(?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\\+([0-9a-zA-Z-]+(?:\\.[0-9a-zA-Z-]+)*))?$"), std::regex::ECMAScript | std::regex::optimize);

void parseVersion(const FString& string, FVersion& version, FString* compareOp);

EComparisonOp parseComparisonOp(const FString& type) {
	if (type == TEXT("<="))
		return EComparisonOp::LESS_EQUALS;
	if (type == TEXT("<"))
		return EComparisonOp::LESS;
	if (type == TEXT(">="))
		return EComparisonOp::GREATER_EQUALS;
	if (type == TEXT(">"))
		return EComparisonOp::GREATER;
	return EComparisonOp::EQUALS;
}

const TCHAR* comparisonString(const EComparisonOp op) {
	switch (op) {
	case EComparisonOp::EQUALS: return TEXT("");
	case EComparisonOp::GREATER: return TEXT(">");
	case EComparisonOp::GREATER_EQUALS: return TEXT(">=");
	case EComparisonOp::LESS: return TEXT("<");
	case EComparisonOp::LESS_EQUALS: return TEXT("<=");
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
	parseVersion(string, myVersion, &comparisonOp);
	this->op = parseComparisonOp(comparisonOp);
}

bool FVersionRange::matches(const FVersion& version) const {
	int result = version.compare(myVersion);
	switch (op) {
	case EComparisonOp::GREATER_EQUALS: return result >= 0;
	case EComparisonOp::GREATER: return result > 0;
	case EComparisonOp::LESS_EQUALS: return result <= 0;
	case EComparisonOp::LESS: return result < 0;
	default: return result == 0;
	}
}

void parseVersion(const FString& string, FVersion& version, FString* compareOp) {
	std::wsmatch match;
	const std::wstring wstr(*string);
	std::regex_match(wstr, match, versionRegex);
	if (match.empty()) {
		SML::Logging::error(*FString::Printf(TEXT("Version string \"%s\" doesn't match the pattern"), *version.string()));
	}
	if (compareOp != nullptr)
		*compareOp = match[1].str().c_str();
	version.major = std::stoull(match[2]);
	version.minor = std::stoull(match[3]);
	version.patch = std::stoull(match[4]);
	version.type = match[5].str().c_str();
	version.buildInfo = match[6].str().c_str();
}

FString FVersion::string() const {
	FString result;
	result.Append(FString::FromInt(major)).Append(TEXT("."));
	result.Append(FString::FromInt(minor)).Append(TEXT("."));
	result.Append(FString::FromInt(patch));
	if (!type.IsEmpty())
		result.Append(TEXT("-")).Append(type);
	if (!buildInfo.IsEmpty())
		result.Append(TEXT("+")).Append(buildInfo);
	return result;
}

FString FVersionRange::string() const {
	return comparisonString(this->op) + myVersion.string();
}

int FVersion::compare(const FVersion& other) const {
	if (major != other.major)
		return major > other.major ? 1 : -1;
	if (minor != other.minor)
		return minor > other.minor ? 1 : -1;
	if (patch != other.patch)
		return patch > other.patch ? 1 : -1;
	return type.Compare(other.type);
}