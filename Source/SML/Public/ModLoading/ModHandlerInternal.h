#pragma once
#include "ModLoading/ModHandler.h"
#include "Util/TopologicalSort/DirectedGraph.h"

class FJsonValue;

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

struct FArchiveObjectInfo {
	FString ObjectPath;
	FString ObjectType;
	TSharedRef<FJsonObject> Metadata;
};

struct FModSortingSet {
	TMap<FString, uint64> ModIndices;
	TMap<uint64, FString> ModByIndex;
	TDirectedGraph<uint64> SortGraph;
	TArray<uint64> SortedIndices;
	TArray<FString> MissingDependencies;
};

class SML_API FModHandlerHelper {
public:
	/** Returns mods directory used for discovering mods */
	static FString GetModsDirectory();

	/** Returns cache directory used for mod loading */
	static FString GetCacheDirectory();
	
	/** Returns true if provided dependency is "virtual": e.g it's used only for sorting */
	static bool IsVirtualDependency(const FString& DependencyModId);

	/** Adds mod dependencies into the sorting graph (and optionally to missing dependencies, unless they are optional) */
	static void PopulateModSortingSet(FModSortingSet& SortingSet, const TMap<FString, FModLoadingEntry>& LoadingEntries);

	/** Finalizes sorting results by apply post-sorting virtual dependencies */
	static void FinalizeSortingResults(FModSortingSet& SortingSet, const TMap<FString, FModLoadingEntry>& LoadingEntries);

	/** Creates loading entry for SML with predefined settings */
	static FModLoadingEntry CreateSMLLoadingEntry();

	/** Creates loading entry for Satisfactory with predefined settings */
	static FModLoadingEntry CreateFactoryGameLoadingEntry();

	static FModPakLoadEntry DiscoverModInitializers(const FString& ModReference);

	/** Tries to guess correct mod reference by examining file path */
	static FString GetModReferenceFromFile(const FString& FilePath);

	/** Tries to parse mod information from zip archive data.json file, optionally outputting failure reason if returned bool is false */
	static bool ReadArchiveDataJson(const TSharedPtr<class FZipFile>& ZipFile, TArray<TSharedPtr<FJsonValue>>& OutJsonObjects, FModInfo& OutModInfo, FString& OutErrorMessage);

	/** Extracts archive objects into cache folder and populates mod loading entry with them */
	static bool ExtractArchiveObjects(const TSharedPtr<FZipFile>& ZipFile, const TArray<TSharedPtr<FJsonValue>>& JsonObjects, FModLoadingEntry& LoadingEntry, FString& OutErrorMessage);

	/** Extracts a single archive object with provided information */
	static bool ExtractArchiveObject(FZipFile& ZipHandle, const FArchiveObjectInfo& ObjectInfo, FModLoadingEntry& LoadingEntry, FString& OutErrorMessage);

	/** Extracts a single file from the archive, filling failure reason string if extraction failed */
	static bool ExtractArchiveFile(FZipFile& ZipHandle, const FString& OutFilePath, const FString& ArchiveFilePath, const FString& ModReference, FString& OutErrorMessage);
};
