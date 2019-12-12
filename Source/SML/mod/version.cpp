#pragma once
#include "version.h"
#include <regex>
#include "util/Utility.h"

using namespace SML::Versioning;

std::wregex versionRegex(TEXT("^(<=|<|>|>=|\\^)?(0|[1-9]\\d*)\\.(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:-((?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*)(?:\\.(?:0|[1-9]\\d*|\\d*[a-zA-Z-][0-9a-zA-Z-]*))*))?(?:\\+([0-9a-zA-Z-]+(?:\\.[0-9a-zA-Z-]+)*))?$"), std::regex::ECMAScript | std::regex::optimize);

void parseVersion(const std::wstring& string, FVersion& version, std::wstring* compareOp);

EComparisonOp parseComparisonOp(const std::wstring& type) {
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

FVersion::FVersion(const std::wstring& string) {
	std::wstring compareOp;
	parseVersion(string, *this, &compareOp);
	if (!compareOp.empty()) {
		throw std::invalid_argument("Unexpected comparison on version declaration");
	}
}

FVersionRange::FVersionRange() {}

FVersionRange::FVersionRange(const std::wstring& string) {
	std::wstring comparisonOp;
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

void parseVersion(const std::wstring& string, FVersion& version, std::wstring* compareOp) {
	std::wsmatch match;
	std::regex_match(string, match, versionRegex);
	if (match.empty()) {
		throw std::invalid_argument("Version string doesn't match the pattern");
	}
	if (compareOp != nullptr)
		*compareOp = match[1];
	version.major = std::stoull(match[2]);
	version.minor = std::stoull(match[3]);
	version.patch = std::stoull(match[4]);
	version.type = match[5];
	version.buildInfo = match[6];
}

std::wstring FVersion::string() const {
	std::wstring result;
	result.append(std::to_wstring(major)).append(TEXT("."));
	result.append(std::to_wstring(minor)).append(TEXT("."));
	result.append(std::to_wstring(patch));
	if (!type.empty())
		result.append(TEXT("-")).append(type);
	if (!buildInfo.empty())
		result.append(TEXT("+")).append(buildInfo);
	return result;
}

std::wstring FVersionRange::string() const {
	return SML::formatStr(comparisonString(this->op), myVersion.string());
}

int FVersion::compare(const FVersion& other) const {
	if (major != other.major)
		return major > other.major ? 1 : -1;
	if (minor != other.minor)
		return minor > other.minor ? 1 : -1;
	if (patch != other.patch)
		return patch > other.patch ? 1 : -1;
	return type.compare(other.type);
}