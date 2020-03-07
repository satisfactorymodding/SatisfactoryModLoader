#pragma once
#include "ModHandler.h"
#include "Json.h"
#include "zip/ttvfs/ttvfs.h"
#include "hooking.h"
#include "util/TopologicalSort.h"

using namespace SML;
using namespace Mod;

typedef std::string FileHash;

void iterateDependencies(TMap<FString, FModLoadingEntry>& loadingEntries,
	TMap<FString, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	TArray<FString>& missingDependencies,
	TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const TMap<FString, FVersionRange>& dependencies,
	bool optional);

void finalizeSortingResults(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices);

void populateSortedModList(TMap<uint64_t, FString>& modByIndex,
	TMap<FString, FModLoadingEntry>& loadingEntries,
	TArray<uint64_t>& sortedIndices,
	TArray<FModLoadingEntry>& sortedModLoadingList);

IModuleInterface* InitializeSMLModule();

FModPakLoadEntry CreatePakLoadEntry(const FString& modid);

FModLoadingEntry createSMLLoadingEntry();

FString getModIdFromFile(const FString& filePath);

bool extractArchiveFile(const FString& outFilePath, ttvfs::File* obj);

TSharedPtr<FJsonObject> readArchiveJson(ttvfs::File* obj);

FileHash hashArchiveFileContents(ttvfs::File* obj);

bool extractArchiveObject(ttvfs::Dir& root, const std::string& objectType, const std::string& archivePath, SML::Mod::FModLoadingEntry& loadingEntry, const FJsonObject* metadata);

bool extractArchiveObjects(ttvfs::Dir& root, const FJsonObject& dataJson, SML::Mod::FModLoadingEntry& loadingEntry);
