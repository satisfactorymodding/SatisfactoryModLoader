#pragma once

#include "mod/SemVersion.h"
#include "Json.h"
#include "Engine/Blueprint.h"
#include "ModInfo.generated.h"

/** Structure holding information about resources used by mod. Not exposed to BPs directly */
struct FModResources {
	/** Path to the small icon image relative to zip root as specified in data.json */
	FString ModIconPath;
};

/** Structure holding information about remote versions accepted by mod */
USTRUCT(BlueprintType)
struct FModRemoteVersion {
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
struct FModInfo {
	GENERATED_USTRUCT_BODY()
	
	/** ModId of the mod */
	UPROPERTY(BlueprintReadOnly)
	FString Modid;
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

	static bool CreateFromJson(const FJsonObject& Object, FModInfo& OutModInfo, FString& OutFailureReason);
	static FModInfo CreateDummyInfo(const FString& Modid);

	/** Returns true if provided ModId is valid */
	static bool IsModIdValid(const FString& ModId);
};