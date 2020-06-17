#pragma once

#include "mod/SemVersion.h"
#include "Json.h"
#include "Engine/Blueprint.h"
#include "ModInfo.generated.h"

struct FModResources {
	/** Path to the small icon image relative to zip root as specified in data.json */
	FString ModIconPath;
};

struct FModRemoteVersion {
	FVersionRange RemoteVersion;
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
	/** Dependencies required for mod loading, not exposed to BPs */
	TMap<FString, FVersionRange> Dependencies;
	TMap<FString, FVersionRange> OptionalDependencies;

	static bool IsValid(const FJsonObject& Object, const FString& FilePath);
	static FModInfo CreateFromJson(const FJsonObject& Object);
	static FModInfo CreateDummyInfo(const FString& Modid);

	/** Returns true if provided ModId is valid */
	static bool IsModIdValid(const FString& ModId);
};