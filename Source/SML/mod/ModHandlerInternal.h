#pragma once
#include "ModHandler.h"
#include "Json.h"
#include "util/TopologicalSort.h"
#include "util/ZipFile.h"

using namespace SML;

struct FFileHash {
	uint64 FileSize;
	int64 ModificationTime;

	FORCEINLINE bool operator==(const FFileHash& Other) const {
		return FileSize == Other.FileSize && ModificationTime == Other.ModificationTime;
	}

	FORCEINLINE bool operator!=(const FFileHash& Other) const {
		return !operator==(Other);
	}
};

void IterateDependencies(TMap<FString, FModLoadingEntry>& loadingEntries,
	TMap<FString, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	TArray<FString>& missingDependencies,
	TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const TMap<FString, FVersionRange>& dependencies,
	bool optional);

void FinalizeSortingResults(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices);

void PopulateSortedModList(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices,
	TArray<FModLoadingEntry>& sortedModLoadingList);

IModuleInterface* InitializeSMLModule();

FModPakLoadEntry CreatePakLoadEntry(const FString& Modid);

FModLoadingEntry CreateSmlLoadingEntry();

FString GetModIdFromFile(const FString& FilePath);

TSharedPtr<FJsonObject> ReadArchiveDataJson(FZipFile& ZipFile);

struct FArchiveObjectInfo {
	FString ObjectPath;
	FString ObjectType;
	TSharedRef<FJsonObject> Metadata;
};

bool ExtractArchiveObjects(FZipFile& ZipHandle, const FJsonObject& DataJson, FModLoadingEntry& LoadingEntry);
