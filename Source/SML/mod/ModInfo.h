#pragma once

#include "mod/version.h"
#include "Json.h"

struct FModInfo {
	FString Modid;
	FString Name;
	FVersion Version;
	FString Description;
	TArray<FString> Authors;
	TMap<FString, FVersionRange> Dependencies;
	TMap<FString, FVersionRange> OptionalDependencies;

	static bool IsValid(const FJsonObject& Object, const FString& FilePath);
	static FModInfo CreateFromJson(const FJsonObject& Object);
	static FModInfo CreateDummyInfo(const FString& Modid);
	static bool IsModIdValid(const FString& ModId);
};