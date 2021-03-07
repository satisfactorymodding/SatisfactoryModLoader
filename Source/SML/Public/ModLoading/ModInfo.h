#pragma once
#include "Util/SemVersion.h"
#include "ModInfo.generated.h"

/** Structure holding information about resources used by mod. Not exposed to BPs directly */
struct SML_API FModResources {
	/** Path to the small icon image relative to zip root as specified in data.json */
	FString ModIconPath;
};

/** Structure holding information about remote versions accepted by mod */
USTRUCT(BlueprintType)
struct SML_API FModRemoteVersion {
	GENERATED_USTRUCT_BODY()
	
	/** Remote version this mod requires cline to have */
	UPROPERTY(BlueprintReadOnly)
	FVersionRange RemoteVersion;
	UPROPERTY(BlueprintReadOnly)
	bool bAcceptAnyRemoteVersion;
};

/**
 * Describes general purpose information about the mod loaded
 */
USTRUCT(BlueprintType)
struct SML_API FModInfo {
	GENERATED_USTRUCT_BODY()
	
	/** ModReferebce of the mod */
	UPROPERTY(BlueprintReadOnly)
	FString ModReference;
	/** Display name of the mod */
	UPROPERTY(BlueprintReadOnly)
	FString Name;
	/** Installed version of the mod */
	UPROPERTY(BlueprintReadOnly)
	FVersion Version;
	/** Description of the mod displayed in the mod list */
	UPROPERTY(BlueprintReadOnly)
	FString Description;
	/** Authors of the mod */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Authors;
	/** Credits provided in data.json */
	UPROPERTY(BlueprintReadOnly)
	FString Credits;
	/** Predicate specifying which remote mod version are accepted */
	FModRemoteVersion RemoteVersion;
	
	/** General-purpose resources of the mod specified in data.json */
	FModResources ModResources;
	
	/** Dependencies required for mod loading */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FVersionRange> Dependencies;
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FVersionRange> OptionalDependencies;

	/** Parses JSON object to initialize mod information from it, reporting potential failure reasons in the argument */
	static bool CreateFromJson(const TSharedPtr<class FJsonObject>& Object, FModInfo& OutModInfo, FString& OutErrorMessage);

	/** Creates dummy mod information object using provided mod reference as name, and setting version to 1.0.0 */ 
	static FModInfo CreateDummyInfo(const FString& ModReference);

	/** Returns true if provided ModId is valid */
	static bool IsModIdValid(const FString& ModId);
};
